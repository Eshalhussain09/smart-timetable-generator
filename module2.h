#ifndef MODULE2_H
#define MODULE2_H

#include <iostream>
#include <vector>
#include <string>
#include "structures.h"
using namespace std;

class GraphBuilder
{
public:
     vector<Session> sessions;
     vector< vector<int>> adjList; 

    void createSessions(const  vector<ClassInfo>& classes,
        const  vector<Teacher>& teachers,
        const  vector<Room>& rooms,
        const  vector<TimeSlot>& slots)
    {
        
        size_t roomCount = rooms.size();
        size_t slotCount = slots.size();

        sessions.clear();
        for (size_t i = 0; i < classes.size(); ++i)
        {
            const auto& c = classes[i]; 

             string assignedTeacher = "TBD"; 
            for (const auto& t : teachers) 
            {
                for (const auto& s : t.subjects)
                {
                    if (s == c.subject) 
                    {
                        assignedTeacher = t.name; 
                        break;
                    }
                }
                if (assignedTeacher != "TBD")
                    break;
            }
            string assignedRoom;
            if (roomCount > 0)
            {
                assignedRoom = rooms[i % roomCount].roomName; 
            }
            else 
            {
                assignedRoom = "None";
            }

            string assignedSlot;
            if (slotCount > 0) 
            {
                assignedSlot = slots[i % slotCount].slotName;
            }
            else 
            {
                assignedSlot = "None";
            }

            Session sess;
            sess.className = c.className;
            sess.subject = c.subject;
            sess.teacher = assignedTeacher;
            sess.room = assignedRoom;
            sess.timeslot = assignedSlot;
            sess.studentGroup = c.className;
            sessions.push_back(sess);
        }
    }

    void buildGraph()
    {
        int n = sessions.size();
        adjList.clear();
        adjList.resize(n);

        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
               
                bool sameTeacher = (sessions[i].teacher == sessions[j].teacher);

                bool sameRoom = (sessions[i].room == sessions[j].room);

                bool sameGroup = (!sessions[i].studentGroup.empty() &&
                    sessions[i].studentGroup == sessions[j].studentGroup);

                if (sameTeacher || sameRoom || sameGroup)
                {
                    adjList[i].push_back(j);
                    adjList[j].push_back(i);
                }
            }
        }
    }

    void printSessions()
    {
         cout << "\n--- Sessions ---\n";
        for (size_t i = 0; i < sessions.size(); ++i) 
        {
            const auto& s = sessions[i];
             cout << i << ": " << s.className << " (" << s.subject << ") | "
                << s.teacher << " | " << s.room << " | " << s.timeslot << "\n";
        }
    }

    void printGraph()
    {
         cout << "\n--- Conflict Graph (Constraints Map) ---\n";
         cout << "Connected sessions share a resource and CANNOT be at the same time.\n";
        for (size_t i = 0; i < sessions.size(); ++i) 
        {
             cout << "Session " << i << " : ";
            for (int nb : adjList[i])  
                cout << nb << " ";
             cout << "\n";
        }
    }
};

#endif // MODULE2_H