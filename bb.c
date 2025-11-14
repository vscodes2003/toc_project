#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TAPE_SIZE 100
#define DELAY 150000

typedef enum { A, B, C, HALT } State;

typedef struct {
    int write;
    int move;  // -1=LEFT, 0=STAY, 1=RIGHT
    State next;
} Rule;

// Simple 3-state machine: A->B->C->A->B->C... for 21 steps then HALT
Rule rules[3][2] = {
    { {1, 1, B}, {1, 1, B} },  // A always goes to B
    { {1, 1, C}, {1, 1, C} },  // B always goes to C
    { {1, 1, A}, {1, 1, A} }   // C always goes to A
};

void printTape(int *tape, int head, State state, int step) {
#ifdef _WIN32
    system("cls");
#else
    //system("clear");
#endif
    
    printf("Step: %d | State: ", step, head);
    switch(state) {
        case A: printf("A\n"); break;
        case B: printf("B\n"); break;
        case C: printf("C\n"); break;
        case HALT: printf("HALT\n"); break;
    }
    
    printf("\nTape: ");
    for (int i = 40; i < 70; i++) {
        if (i == head)
            printf("[%d]", tape[i]);
        else
            printf(" %d ", tape[i]);
    }
    printf("\n\n");
}

int main() {
    int tape[TAPE_SIZE] = {0};
    int head = 50;
    State state = A;
    int steps = 0;
    
    // Run for exactly 21 steps then HALT
    while (steps < 21) {
        printTape(tape, head, state, steps);
        
        int read = tape[head];
        Rule r = rules[state][read];
        
        tape[head] = r.write;
        head += r.move;
        state = r.next;
        
        steps++;
        usleep(DELAY);
    }
    
    state = HALT;
    printTape(tape, head, state, steps);
    printf("HALTED after %d steps\n\n", steps);
    
    return 0;
}