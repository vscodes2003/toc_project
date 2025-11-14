#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>

using namespace std;

// State: 0 = A, 1 = B, 2 = C, 3 = D, etc.
// Special state: -1 = HALT
const int HALT = -1;

struct Transition {
    int writeSymbol;  // 0 or 1
    int moveDir;      // -1 = left, 1 = right
    int nextState;    // next state or HALT
};

class TuringMachine {
private:
    map<int, int> tape;  // position -> symbol
    int head;
    int currentState;
    int numStates;
    vector<vector<Transition>> transitions;  // [state][symbol]

public:
    TuringMachine(int n, const vector<vector<Transition>>& trans) 
        : numStates(n), transitions(trans), head(0), currentState(0) {}
    
    pair<int, int> run(int maxSteps) {
        int steps = 0;
        
        while (currentState != HALT && steps < maxSteps) {
            int symbol = tape[head];  // default 0 if not in map
            
            Transition t = transitions[currentState][symbol];
            
            tape[head] = t.writeSymbol;
            head += t.moveDir;
            currentState = t.nextState;
            steps++;
        }
        
        // Count ones on tape
        int ones = 0;
        for (const auto& p : tape) {
            if (p.second == 1) ones++;
        }
        
        return {steps, ones};
    }
    
    bool halted() const {
        return currentState == HALT;
    }
};

void generateAllMachines(int n, int state, int symbol, 
                         vector<vector<Transition>>& current,
                         vector<vector<vector<Transition>>>& allMachines) {
    if (state == n) {
        allMachines.push_back(current);
        return;
    }
    
    int nextState = state;
    int nextSymbol = symbol + 1;
    if (nextSymbol == 2) {
        nextSymbol = 0;
        nextState++;
    }
    
    // Try all possible transitions
    // writeSymbol: 0 or 1
    for (int write = 0; write <= 1; write++) {
        // moveDir: -1 (left) or 1 (right)
        for (int move = -1; move <= 1; move += 2) {
            // nextState: HALT or states 0 to n-1
            for (int next = HALT; next < n; next++) {
                Transition t = {write, move, next};
                current[state][symbol] = t;
                generateAllMachines(n, nextState, nextSymbol, current, allMachines);
            }
        }
    }
}

int busyBeaver(int n, int& maxOnes) {
    cout << "Computing BB(" << n << ")..." << endl;
    
    // Generate all possible n-state machines
    // Each state has 2 symbols, each transition has 3 choices:
    // write (2), move (2), next state (n+1 including HALT)
    vector<vector<Transition>> current(n, vector<Transition>(2));
    vector<vector<vector<Transition>>> allMachines;
    
    generateAllMachines(n, 0, 0, current, allMachines);
    
    cout << "Total machines to test: " << allMachines.size() << endl;
    
    int maxStepsHalted = 0;
    maxOnes = 0;
    int haltedCount = 0;
    
    // Maximum steps to simulate (heuristic to detect non-halting)
    int maxSimSteps = (int)pow(10, n + 3);
    
    for (size_t i = 0; i < allMachines.size(); i++) {
        TuringMachine tm(n, allMachines[i]);
        pair<int, int> result = tm.run(maxSimSteps);
        int steps = result.first;
        int ones = result.second;
        
        if (tm.halted()) {
            haltedCount++;
            if (steps > maxStepsHalted) {
                maxStepsHalted = steps;
            }
            if (ones > maxOnes) {
                maxOnes = ones;
            }
        }
        
        if ((i + 1) % 100000 == 0) {
            cout << "  Progress: " << i + 1 << " / " << allMachines.size() << endl;
        }
    }
    
    cout << "Machines that halted: " << haltedCount << " / " << allMachines.size() << endl;
    
    return maxStepsHalted;
}

int main() {
    cout << "=== Busy Beaver Problem ===" << endl << endl;
    
    // Known BB values
    vector<int> knownBB = {1, 6, 21, 107};  // BB(1), BB(2), BB(3), BB(4)
    vector<int> knownSigma = {1, 4, 6, 13}; // Sigma(1), Sigma(2), Sigma(3), Sigma(4)
    
    cout << "Note: BB(n) is the maximum steps, Sigma(n) is the maximum 1's" << endl;
    cout << "Computing for n=1 to 4 (larger n takes exponentially longer)" << endl << endl;
    
    for (int n = 1; n <= 4; n++) {
        int maxOnes = 0;
        int maxSteps = busyBeaver(n, maxOnes);
        
        cout << "BB(" << n << ") = " << maxSteps;
        cout << " (known: " << knownBB[n-1] << ")";
        if (maxSteps == knownBB[n-1]) cout << " ✓";
        cout << endl;
        
        cout << "Sigma(" << n << ") = " << maxOnes;
        cout << " (known: " << knownSigma[n-1] << ")";
        if (maxOnes == knownSigma[n-1]) cout << " ✓";
        cout << endl << endl;
    }
    
    cout << "Warning: BB(5) and beyond are computationally intractable!" << endl;
    cout << "BB(5) > 47,176,870 and requires examining 10^19 machines." << endl;
    
    return 0;
}
