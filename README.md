# Theory of Computation Project: The Busy Beaver Problem

This repository contains a project for a **Theory of Computation** course, exploring the **Busy Beaver (BB) problem**.  
The project includes C/C++ implementations to simulate and analyze Busy Beaver machines, along with a detailed report connecting the BB problem to the **Halting Problem**.

---

## Project Components

### **1. `bb(n).pdf`**
A comprehensive presentation covering:
- What the Busy Beaver problem is  
- Its connection to the **Halting Problem**  
- Known values of BB(1) to BB(5)  
- Explanation of the C++ simulation for the 3-state Busy Beaver  

### **2. `bbn.cpp`**
A C++ program that **generates and simulates all possible n-state Turing machines** to compute:
- **BB(n)** → maximum number of steps before halting  
- **Σ(n)** → maximum number of 1s printed  

Tested for **n = 1, 2, 3, 4**.

### **3. `bb.c`**
A simple C program that **visually simulates** a 3-state Busy Beaver Turing Machine for **21 steps** (the known BB(3) value).

---

## Background: The Busy Beaver Problem

Introduced by **Tibor Radó (1962)**, the Busy Beaver problem asks:

> **Among all halting n-state, 2-symbol Turing machines, what is the maximum number of 1s or steps it can produce before halting?**

### Key functions:
- **Σ(n):** Maximum number of 1s printed  
- **BB(n) or S(n):** Maximum number of steps before halting  

These functions grow **faster than any computable function** — faster than exponentials, towers of exponentials, or anything algorithmically definable.

### Connection to the Halting Problem
Because the **Halting Problem is undecidable**, there is **no general algorithm** that can compute Busy Beaver values for all n.  
For small n (1–4), values are known, but beyond that, computation becomes infeasible or impossible.

---

## Compilation and Execution

You need:
- A **C++ compiler** (e.g., g++)
- A **C compiler** (e.g., gcc)

---

### 1. Busy Beaver Finder (`bbn.cpp`)

This program enumerates and tests all machines for n = 1 to 4.

```bash
# Compile
g++ bbn.cpp -o bbn -std=c++11

# Run
./bbn
```
### 2. 3-State Visualizer (bb.c)

Runs a 3-state Busy Beaver for exactly 21 steps.
```
# Compile
gcc bb.c -o bb

# Run
./bb
```
### Authors

This project was created by:
- PRIYANSHU DIXIT – BT23CSE003
- SAKSHAM AGRAWAL – BT23CSE004
- VARUN SINGH – BT23CSE009
- YOGESH BHIVSANE – BT23CSE013
- YASH VERMA – BT23CSE019
