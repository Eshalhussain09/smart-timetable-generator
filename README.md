# Smart Timetable Generator with Optimal Class Routing

> A C++ Data Structures final project that automatically generates conflict-free university timetables and computes optimal teacher routing paths across classrooms.

---

## Overview

This project tackles the real-world university scheduling problem using core graph theory and algorithmic concepts. It reads teacher, class, room, and time slot data from files, builds a conflict graph, and applies graph coloring + backtracking to generate a valid, clash-free timetable. It also finds minimum-distance routes for teachers to move between rooms using MST, Euler, and Hamiltonian path algorithms.

---

## Features

| Module | Description |
|--------|-------------|
| **Module 1 – File Handling** | Reads teachers, classes, rooms, time slots, and room distance matrix from text files |
| **Module 2 – Graph Builder** | Creates sessions and builds a conflict graph (edges = shared teacher/room/student group) |
| **Module 3 – Validator** | Detects and reports schedule violations (same-time clashes) |
| **Module 4 – Graph Coloring** | Uses backtracking-based graph coloring to assign conflict-free time slots |
| **Module 5 – Route Planner (MST)** | Computes minimum spanning tree via Prim's and Kruskal's algorithms for optimal teacher movement |
| **Module 6 – Path Checker** | Finds Euler and Hamiltonian paths across the room graph for efficient traversal |
| **Module 7 – Recursive Scheduler** | Assigns time slots via recursive backtracking with constraint propagation |
| **Module 8 – Output Manager** | Displays and exports timetable, MST, Euler path, and Hamiltonian path to files |

---

## Algorithms Used

- **Graph Coloring** (backtracking) — conflict-free timetable generation
- **Prim's Algorithm** — Minimum Spanning Tree for room routing
- **Kruskal's Algorithm** — Alternative MST with Union-Find
- **Euler Path** (Hierholzer's Algorithm) — traverses every corridor once
- **Hamiltonian Path** (backtracking) — visits every room exactly once
- **Constraint Satisfaction / Backtracking** — recursive scheduling engine

---

## Project Structure

```
├── main.cpp               # Entry point and module orchestration
├── structures.h           # Core data structures (Teacher, Room, Session, etc.)
├── module1.h              # File Handling
├── module2.h              # Graph Builder
├── module3.h              # Validator
├── module4.h              # Graph Coloring
├── module5.h              # MST Route Planner
├── module6.h              # Euler & Hamiltonian Path Checker
├── module7.h              # Recursive Scheduler
├── module8.h              # Output Manager
├── files/
│   ├── teachers.txt       # Teacher names and subjects
│   ├── classes.txt        # Class groups and subjects
│   ├── rooms.txt          # Room names
│   ├── timeslots.txt      # Available time slots
│   └── distances.txt      # Room-to-room distance matrix (NxN)
└── output/
    ├── timetable.txt
    ├── mst.txt
    ├── euler_path.txt
    └── hamilton_path.txt
```

---

## Input File Formats

**teachers.txt**
```
Ali Math Physics
Sara CS OOP
```

**classes.txt**
```
BCS-1A Math
BCS-1B CS
```

**rooms.txt**
```
MathLab CsLab1 Room12 Room22
```

**timeslots.txt**
```
8:00AM 9:00AM 10:00AM 11:00AM
```

**distances.txt** — N×N matrix of integer distances between rooms (999 = no direct path)

---

## Sample Output

**Hamiltonian Path (room traversal):**
```
MathLab -> CsLab1 -> Room12 -> Room22 -> Room6 -> CSLab3 -> SELab8 -> Room16 -> Room7 -> DLDLab
```

**Timetable (excerpt):**
```
Class  | Subject | Teacher | Room    | Time Slot
BCS-1A | Math    | Ali     | MathLab | 8:00AM
BCS-1B | CS      | Sara    | CsLab1  | 9:00AM
```

---

## How to Build & Run

```bash
# Compile
g++ -o timetable main.cpp -std=c++17

# Run
./timetable
```

Make sure the `files/` and `output/` directories exist before running.

---

## Technologies

- **Language:** C++17
- **Paradigm:** Object-Oriented Programming
- **Concepts:** Graph Theory, Backtracking, Greedy Algorithms, File I/O

---

## Authors

- **Muhammad Ali Irfan** — 24F-0517
- **Eshal Hussain** — 24F-0597

*DS Final Project — FAST NUCES*
