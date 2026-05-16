#ifndef MODULE7_H
#define MODULE7_H

#include <iostream>
#include <vector>
#include <string>
#include "structures.h"

using namespace std;

//-------------------- Module 7: Recursive Scheduling (Backtracking) --------------------
class Scheduler
{
public:
    vector<Session> sessions;      
    vector<vector<int>> adjList;    
    vector<string> timeSlots;        
    bool scheduleFound = false;      

    void initialize(const vector<Session>& sess, const vector<vector<int>>& graph, const vector<TimeSlot>& slots)
    {
        sessions = sess;
        adjList = graph;
        timeSlots.clear();
        for (const auto& t : slots) timeSlots.push_back(t.slotName);
    }

    void assignTimeSlots()
    {
        if (sessions.empty() || timeSlots.empty())
        {
            cout << "No sessions or time slots available for scheduling.\n";
            return;
        }

        vector<string> assigned(sessions.size(), "");
        scheduleFound = backtrack(0, assigned);

        if (scheduleFound)
        {
            cout << "\n--- Module 7: Recursive Scheduling Completed ---\n";
            for (size_t i = 0; i < sessions.size(); ++i)
            {
                sessions[i].timeslot = assigned[i];
                cout << sessions[i].className << " | " << sessions[i].subject
                    << " | " << sessions[i].teacher
                    << " | " << sessions[i].room
                    << " | " << sessions[i].timeslot << endl;
            }
            cout << "Schedule successfully generated!\n";
            cout << "======================================================\n";
        }
        else
        {
            cout << "No conflict-free schedule could be generated with available time slots.\n";
        }
    }

private:
    bool backtrack(int sessionIndex, vector<string>& assigned)
    {
        if (sessionIndex == sessions.size())
            return true;

        for (const auto& slot : timeSlots)
        {
            if (canAssign(sessionIndex, slot, assigned))
            {
                assigned[sessionIndex] = slot;
                if (backtrack(sessionIndex + 1, assigned))
                    return true;
                assigned[sessionIndex] = "";
            }
        }
        return false; 
    }

    bool canAssign(int sessionIndex, const string& slot, const vector<string>& assigned)
    {
        for (int neighbor : adjList[sessionIndex])
        {
            if (!assigned[neighbor].empty() && assigned[neighbor] == slot)
            {
                return false; 
            }
        }
        return true;
    }
};

#endif // MODULE7_H
