#ifndef MODULE4_H
#define MODULE4_H

#include <iostream>
#include <vector>
#include <string>
#include "structures.h"

using namespace std;

//-------------------- Module 4: Graph Coloring --------------------
class GraphColoring
{
public:
    vector<int> sessionColors;  
    int totalSlots;

    bool assignTimeslots(vector<Session>& sessions, const vector<vector<int>>& adjList, int numSlots)
    {
        totalSlots = numSlots;
        sessionColors.assign(sessions.size(), -1);
        return backtrackColoring(0, sessions, adjList);
    }

    void applySlots(vector<Session>& sessions, const vector<string>& slotNames)
    {
        for (size_t i = 0; i < sessions.size(); ++i)
        {
            int color = sessionColors[i];
            if (color >= 0 && color < (int)slotNames.size()) 
                sessions[i].timeslot = slotNames[color];
            else
                sessions[i].timeslot = "UNASSIGNED";
        }
    }

    void printSchedule(const vector<Session>& sessions)
    {
        cout << "\n--- Module 4: Conflict-Free Timetable ---\n";
        for (const auto& s : sessions)
        {
            cout << s.className << " | " << s.subject << " | "
                << s.teacher << " | " << s.room << " | " << s.timeslot << endl;
        }
        cout << "======================================================\n";
    }

private:
    bool backtrackColoring(int idx, vector<Session>& sessions, const vector<vector<int>>& adjList)
    {
        if (idx >= (int)sessions.size()) 
            return true;

        for (int slot = 0; slot < totalSlots; ++slot)
        {
            if (isSafe(idx, slot, adjList))
            {
                sessionColors[idx] = slot;
                if (backtrackColoring(idx + 1, sessions, adjList))
                    return true;
                sessionColors[idx] = -1; 
            }
        }
        return false; 
    }

    bool isSafe(int sessionIdx, int slot, const vector<vector<int>>& adjList)
    {
        for (int neighbor : adjList[sessionIdx])
        {
            if (sessionColors[neighbor] == slot)
                return false; 
        }
        return true;
    }
};

#endif // MODULE4_H

