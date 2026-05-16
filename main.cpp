#include <iostream>
#include <limits>
#include <sstream>
#include <vector>
#include <iomanip>
#include "module1.h"
#include "module2.h"
#include "module3.h"
#include "module4.h"
#include "module5.h"
#include "module6.h"
#include "module7.h"
#include "module8.h"

using namespace std;
int getSafeIntInput(const string& prompt)
{
    int choice;
    cout << prompt;
    while (!(cin >> choice))
    {
        cout << "Invalid input. Please enter a number.\n";
        cout << prompt;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice;
}

void displayWelcome()
{
    cout << "\n";
    cout << "=====================================================\n";
    cout << "  SMART TIMETABLE GENERATOR & ROUTE PLANNER\n";
    cout << "\n";
    cout << "=====================================================\n";
}

void displayMainMenu()
{
    cout << "\n" << setfill('-') << setw(50) << "-" << setfill(' ') << "\n";
    cout << "                    MAIN MENU\n";
    cout << setfill('-') << setw(50) << "-" << setfill(' ') << "\n";
    cout << "1.  View Data from Files\n";
    cout << "2.  Create & Validate Timetable (Module 2 & 3)\n";
    cout << "3.  Graph Coloring & Conflict Resolution (Module 4)\n";
    cout << "4.  Optimal Route Planning (MST) (Module 5)\n";
    cout << "5.  Path Analysis (Euler & Hamiltonian) (Module 6)\n";
    cout << "6.  Advanced Scheduling (Backtracking) (Module 7)\n";
    cout << "7.  Complete Pipeline (All Modules)\n";
    cout << "8.  Export All Results\n";
    cout << "9.  Project Summary & Documentation\n";
    cout << "10. Exit Application\n";
    cout << setfill('-') << setw(50) << "-" << setfill(' ') << "\n";
}

FileHandling fh;
GraphBuilder* globalGB = nullptr;
GraphColoring* globalGC = nullptr;

int main()
{
    displayWelcome();

    cout << "\nLoading data from files...\n";
    fh.readAllData();

    bool running = true;
    bool scheduleGenerated = false;

    while (running)
    {
        displayMainMenu();
        int choice = getSafeIntInput("Enter your choice (1-10): ");

        switch (choice)
        {
        case 1:
        {
            int subChoice;
            cout << "\n--- VIEW DATA MENU ---\n";
            cout << "1. View Teachers\n";
            cout << "2. View Classes\n";
            cout << "3. View Rooms\n";
            cout << "4. View Time Slots\n";
            cout << "5. View Room Distances\n";
            cout << "6. View ALL Data\n";
            cout << "0. Back to Main Menu\n";
            cout << "Which file do you want to read? ";
            cin >> subChoice;

            switch (subChoice)
            {
            case 1: 
                fh.displayTeachers();
                break;
            case 2:
                fh.displayClasses();
                break;
            case 3:
                fh.displayRooms();
                break;
            case 4: 
                fh.displayTimeSlots();
                break;
            case 5:
                fh.displayDistances(); 
                break;
            case 6:
                fh.displayAll(); 
                break;
            case 0:
                break;
            default: 
                cout << "Invalid option.\n";
            }
            break;
        }

        case 2:
        {
            // ----- MODULE 2 & 3: CREATE & VALIDATE -----
            cout << "\n" << setfill('=') << setw(50) << "=" << setfill(' ') << "\n";
            cout << "MODULE 2 & 3: TIMETABLE CREATION & VALIDATION\n";
            cout << setfill('=') << setw(50) << "=" << setfill(' ') << "\n";

            if (fh.classesArr.empty() || fh.teachers.empty() || fh.rooms.empty() || fh.slots.empty())
            {
                cout << "ERROR: Missing essential data (classes/teachers/rooms/slots).\n";
                break;
            }

            globalGB = new GraphBuilder();
            globalGB->createSessions(fh.classesArr, fh.teachers, fh.rooms, fh.slots);
            globalGB->printSessions();
            globalGB->buildGraph();
            globalGB->printGraph();

            Validator v;
            v.validateSchedule(globalGB->sessions);
            break;
        }

        case 3:
        {
            // ----- MODULE 4: GRAPH COLORING -----
            cout << "\n" << setfill('=') << setw(50) << "=" << setfill(' ') << "\n";
            cout << "MODULE 4: GRAPH COLORING & CONFLICT RESOLUTION\n";
            cout << setfill('=') << setw(50) << "=" << setfill(' ') << "\n";

            if (!globalGB)
            {
                cout << "Please create timetable first (Menu 2).\n";
                break;
            }

            globalGC = new GraphColoring();
            if (globalGC->assignTimeslots(globalGB->sessions, globalGB->adjList, (int)fh.slots.size()))
            {
                cout << "\nSUCCESS: Graph coloring completed!\n";
                vector<string> slotNames;
                for (const auto& s : fh.slots)
                    slotNames.push_back(s.slotName);

                globalGC->applySlots(globalGB->sessions, slotNames);
                globalGC->printSchedule(globalGB->sessions);
                scheduleGenerated = true;

                Validator v;
                v.validateSchedule(globalGB->sessions);
            }
            else
            {
                cout << "ERROR: Could not assign timeslots (insufficient time slots).\n";
            }
            break;
        }

        case 4:
        {
            // ----- MODULE 5: MST -----
            cout << "\n" << setfill('=') << setw(50) << "=" << setfill(' ') << "\n";
            cout << "MODULE 5: OPTIMAL ROUTE PLANNING (MST)\n";
            cout << setfill('=') << setw(50) << "=" << setfill(' ') << "\n";

            if (fh.rooms.empty() || fh.distances.empty())
            {
                cout << "ERROR: Missing room or distance data.\n";
                break;
            }

            cout << "Select algorithm:\n";
            cout << "1. Prim's Algorithm\n";
            cout << "2. Kruskal's Algorithm\n";
            int mstChoice = getSafeIntInput("Enter choice: ");

            RoutePlanner rp;
            if (mstChoice == 1)
            {
                cout << "Computing MST using Prim's Algorithm...\n";
                rp.computeMST_Prim(fh.rooms, fh.distances);
            }
            else if (mstChoice == 2)
            {
                cout << "Computing MST using Kruskal's Algorithm...\n";
                rp.computeMST_Kruskal(fh.rooms, fh.distances);
            }
            else
            {
                cout << "Invalid choice. Using Prim's by default.\n";
                rp.computeMST_Prim(fh.rooms, fh.distances);
            }

            rp.printMST(fh.rooms);
            break;
        }

        case 5:
        {
            // ----- MODULE 6: EULER & HAMILTONIAN -----
            cout << "\n" << setfill('=') << setw(50) << "=" << setfill(' ') << "\n";
            cout << "MODULE 6: PATH ANALYSIS (EULER & HAMILTONIAN)\n";
            cout << setfill('=') << setw(50) << "=" << setfill(' ') << "\n";

            if (fh.rooms.empty() || fh.distances.empty())
            {
                cout << "ERROR: Missing room or distance data.\n";
                break;
            }

            PathChecker pc;
            pc.checkEulerPath(fh.distances, fh.rooms);
            pc.checkHamiltonianPath(fh.distances, fh.rooms);
            break;
        }

        case 6:
        {
            // ----- MODULE 7: BACKTRACKING -----
            cout << "\n" << setfill('=') << setw(50) << "=" << setfill(' ') << "\n";
            cout << "MODULE 7: RECURSIVE SCHEDULING (BACKTRACKING)\n";
            cout << setfill('=') << setw(50) << "=" << setfill(' ') << "\n";

            if (fh.classesArr.empty() || fh.teachers.empty() || fh.rooms.empty() || fh.slots.empty())
            {
                cout << "ERROR: Missing essential data.\n";
                break;
            }

            if (!globalGB)
            {
                globalGB = new GraphBuilder();
                globalGB->createSessions(fh.classesArr, fh.teachers, fh.rooms, fh.slots);
                globalGB->buildGraph();
            }

            Scheduler sched;
            sched.initialize(globalGB->sessions, globalGB->adjList, fh.slots);
            sched.assignTimeSlots();
            scheduleGenerated = true;
            break;
        }

        case 7:
        {
           
            cout << "\n" << setfill('=') << setw(50) << "=" << setfill(' ') << "\n";
            cout << "COMPLETE PIPELINE: ALL MODULES\n";
            cout << setfill('=') << setw(50) << "=" << setfill(' ') << "\n";

            if (fh.classesArr.empty() || fh.teachers.empty() || fh.rooms.empty() || fh.slots.empty())
            {
                cout << "ERROR: Missing essential data.\n";
                break;
            }

            // Module 2 & 3
            cout << "\n[STEP 1] Creating sessions and validating...\n";
            globalGB = new GraphBuilder();
            globalGB->createSessions(fh.classesArr, fh.teachers, fh.rooms, fh.slots);
            globalGB->buildGraph();
            Validator v;
            v.validateSchedule(globalGB->sessions);

            // Module 4
            cout << "\n[STEP 2] Applying graph coloring...\n";
            globalGC = new GraphColoring();
            if (globalGC->assignTimeslots(globalGB->sessions, globalGB->adjList, (int)fh.slots.size()))
            {
                vector<string> slotNames;
                for (const auto& s : fh.slots)
                    slotNames.push_back(s.slotName);
                globalGC->applySlots(globalGB->sessions, slotNames);
                scheduleGenerated = true;
            }

            // Module 5
            cout << "\n[STEP 3] Computing optimal routes (MST)...\n";
            if (!fh.rooms.empty() && !fh.distances.empty())
            {
                RoutePlanner rp;
                rp.computeMST_Prim(fh.rooms, fh.distances);
            }

            // Module 6
            cout << "\n[STEP 4] Analyzing Euler and Hamiltonian paths...\n";
            if (!fh.rooms.empty() && !fh.distances.empty())
            {
                PathChecker pc;
                pc.checkEulerPath(fh.distances, fh.rooms);
                pc.checkHamiltonianPath(fh.distances, fh.rooms);
            }

            cout << "\n" << setfill('=') << setw(50) << "=" << setfill(' ') << "\n";
            cout << "COMPLETE PIPELINE FINISHED SUCCESSFULLY!\n";
            cout << setfill('=') << setw(50) << "=" << setfill(' ') << "\n";
            break;
        }

        case 8:
        {
            cout << "\n" << setfill('=') << setw(50) << "=" << setfill(' ') << "\n";
            cout << "EXPORTING ALL RESULTS\n";
            cout << setfill('=') << setw(50) << "=" << setfill(' ') << "\n";

            if (!scheduleGenerated || !globalGB)
            {
                cout << "ERROR: Please generate schedule first (use Complete Pipeline).\n";
                break;
            }

            OutputManager om;
            om.displayTimetable(globalGB->sessions);
            om.exportTimetable(globalGB->sessions, "files/timetable.txt");

            if (!fh.rooms.empty() && !fh.distances.empty())
            {
                RoutePlanner rp;
                rp.computeMST_Prim(fh.rooms, fh.distances);
                vector<pair<string, string>> routes;
                for (auto& edge : rp.mstEdges)
                {
                    routes.push_back({ fh.rooms[edge.first].roomName, fh.rooms[edge.second].roomName });
                }
                om.exportMST(rp.totalDistance, routes, "files/mst.txt");
            }

            cout << "\nAll results exported to files/ directory.\n";
            break;
        }

        case 9:
        {
            // ----- PROJECT DOCUMENTATION -----
            cout << "\n" << setfill('=') << setw(60) << "=" << setfill(' ') << "\n";
            cout << "      SMART TIMETABLE GENERATOR - PROJECT SUMMARY\n";
            cout << setfill('=') << setw(60) << "=" << setfill(' ') << "\n";

            cout << "\nOBJECTIVES:\n";
            cout << "   Generate conflict-free timetables automatically\n";
            cout << "   Apply Discrete Mathematical concepts for validation\n";
            cout << "   Optimize teacher movement routes\n";
            cout << "   Provide interactive console interface\n";

            cout << "\nDISCRETE MATHEMATICS CONCEPTS USED:\n";
            cout << "   Logic & Propositions: Constraint validation\n";
            cout << "   Set Theory: Represent teachers, classes, rooms, slots\n";
            cout << "   Relations & Functions: Dependency modeling\n";
            cout << "   Recursion & Induction: Backtracking algorithms\n";
            cout << "   Graph Theory: Conflict detection and coloring\n";
            cout << "   MST Algorithms: Optimal routing (Prim's, Kruskal's)\n";
            cout << "   Euler Path: Continuous patrol routes\n";
            cout << "   Hamiltonian Path: Full coverage verification\n";

            cout << "\nMODULES:\n";
            cout << "  1. Data Input & File Handling\n";
            cout << "  2. Graph Construction (Conflict Modeling)\n";
            cout << "  3. Logic Checking & Validation\n";
            cout << "  4. Graph Coloring (Slot Assignment)\n";
            cout << "  5. Optimal Route Finder (MST)\n";
            cout << "  6. Euler & Hamiltonian Path Check\n";
            cout << "  7. Recursive Scheduling (Backtracking)\n";
            cout << "  8. Output & Export\n";

            cout << "\nINPUT FILES:\n";
            cout << "   teachers.txt: Teacher names and subjects\n";
            cout << "   classes.txt: Class names and subjects\n";
            cout << "   rooms.txt: Classroom names\n";
            cout << "   timeslots.txt: Available time slots\n";
            cout << "   distances.txt: Room-to-room distance matrix\n";

            cout << "\nOUTPUT FILES:\n";
            cout << "   files/timetable.txt: Final schedule\n";
            cout << "   files/mst.txt: Optimal routes\n";
            cout << "   files/euler_path.txt: Patrol route\n";
            cout << "   files/hamilton_path.txt: Coverage path\n";

            cout << "\n" << setfill('=') << setw(60) << "=" << setfill(' ') << "\n";
            break;
        }

        case 10:
            running = false;
            cout << "\n\n\n" << setfill('=') << setw(50) << "=" << setfill(' ') << "\n";
            cout << "Thank you for using Smart Timetable Generator!\n";
            cout << setfill('=') << setw(50) << "=" << setfill(' ') << "\n\n";
            break;

        default:
            cout << "Invalid choice. Please select 1-10.\n";
        }
    }

    if (globalGB)
        delete globalGB;
    if (globalGC)
        delete globalGC;

    return 0;
}