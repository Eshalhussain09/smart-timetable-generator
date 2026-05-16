#ifndef MODULE8_H
#define MODULE8_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "structures.h"

using namespace std;

//-------------------- Module 8: Output & Display --------------------
class OutputManager
{
public:
    void displayTimetable(const vector<Session>& sessions)
    {
        cout << "\n--- FINAL TIMETABLE ---\n";
        cout << "Class | Subject | Teacher | Room | Time Slot\n";
        cout << "--------------------------------------------\n";
        for (const auto& s : sessions)
        {
            cout << s.className << " | "
                << s.subject << " | "
                << s.teacher << " | "
                << s.room << " | "
                << s.timeslot << endl;
        }
        cout << "--------------------------------------------\n";
    }

    void exportTimetable(const vector<Session>& sessions, const string& filename = "output/timetable.txt")
    {
        ofstream fout(filename);
        if (!fout)
        {
            cout << "ERROR: Cannot open " << filename << " for writing.\n";
            return;
        }

        fout << "Class | Subject | Teacher | Room | Time Slot\n";
        fout << "--------------------------------------------\n";
        for (const auto& s : sessions)
        {
            fout << s.className << " | "
                << s.subject << " | "
                << s.teacher << " | "
                << s.room << " | "
                << s.timeslot << "\n";
        }
        fout.close();
        cout << "INFO: Timetable exported to " << filename << endl;
    }

    void displayMST(int totalDistance, const vector<pair<string, string>>& routes)
    {
        cout << "\n--- MST (Minimal Teacher Movement) ---\n";
        cout << "Total Distance: " << totalDistance << "\n";
        cout << "Routes:\n";
        for (const auto& r : routes)
        {
            cout << r.first << " -> " << r.second << endl;
        }
        cout << "--------------------------------------------\n";
    }

    void exportMST(int totalDistance, const vector<pair<string, string>>& routes, const string& filename = "output/mst.txt")
    {
        ofstream fout(filename);
        if (!fout)
        {
            cout << "ERROR: Cannot open " << filename << " for writing.\n";
            return;
        }

        fout << "Total Distance: " << totalDistance << "\n";
        fout << "Routes:\n";
        for (const auto& r : routes)
        {
            fout << r.first << " -> " << r.second << "\n";
        }
        fout.close();
        cout << "INFO: MST exported to " << filename << endl;
    }

    void displayEulerPath(const vector<string>& path)
    {
        cout << "\n--- Euler Path ---\n";
        for (size_t i = 0; i < path.size(); i++)
        {
            cout << path[i];
            if (i != path.size() - 1) 
                cout << " -> ";
        }
        cout << "\n--------------------------------------------\n";
    }

    void exportEulerPath(const vector<string>& path, const string& filename = "output/euler_path.txt")
    {
        ofstream fout(filename);
        if (!fout)
        {
            cout << "ERROR: Cannot open " << filename << " for writing.\n";
            return;
        }
        for (size_t i = 0; i < path.size(); i++)
        {
            fout << path[i];
            if (i != path.size() - 1) fout << " -> ";
        }
        fout.close();
        cout << "INFO: Euler path exported to " << filename << endl;
    }

    void displayHamiltonPath(const vector<string>& path)
    {
        cout << "\n--- Hamiltonian Path ---\n";
        for (size_t i = 0; i < path.size(); i++)
        {
            cout << path[i];
            if (i != path.size() - 1) cout << " -> ";
        }
        cout << "\n--------------------------------------------\n";
    }

    void exportHamiltonPath(const vector<string>& path, const string& filename = "output/hamilton_path.txt")
    {
        ofstream fout(filename);
        if (!fout)
        {
            cout << "ERROR: Cannot open " << filename << " for writing.\n";
            return;
        }
        for (size_t i = 0; i < path.size(); i++)
        {
            fout << path[i];
            if (i != path.size() - 1) fout << " -> ";
        }
        fout.close();
        cout << "INFO: Hamilton path exported to " << filename << endl;
    }
};

#endif // MODULE8_H
