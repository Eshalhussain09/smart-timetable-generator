#ifndef MODULE3_H
#define MODULE3_H

#include <iostream>
#include <vector>
#include "structures.h"

using namespace std;

//-------------------- Module 3: Logic Checking & Validation --------------------
class Validator
{
public:
    void validateSchedule(const vector<Session>& sessions)
    {
        cout << "\n--- Module 3: Validation Report ---\n";

        int totalConflicts = 0;

        for (size_t i = 0; i < sessions.size(); ++i)
        {
            for (size_t j = i + 1; j < sessions.size(); ++j)
            {
                const Session& c1 = sessions[i];
                const Session& c2 = sessions[j];

                bool sameTeacher = (c1.teacher == c2.teacher);
                bool sameRoom = (c1.room == c2.room);
                bool sameStudentGroup = (!c1.studentGroup.empty() && c1.studentGroup == c2.studentGroup);

                bool resourceConflict = sameTeacher || sameRoom || sameStudentGroup;

                bool sameTime = (c1.timeslot == c2.timeslot);

                if (resourceConflict && sameTime)
                {
                    totalConflicts++;
                    cout << " VIOLATION (Sessions " << i << " & " << j << ") at Slot: " << c1.timeslot << "\n";
                    cout << " Reason(s): ";

                    if (sameTeacher)
                       cout << "[SameTeacher] ";
                    if (sameRoom) 
                        cout << "[SameRoom] ";
                    if (sameStudentGroup)
                        cout << "[SameGroup] ";

                    cout << endl;
                }
            }
        }

        cout << "\n--- Final Summary ---\n";
        if (totalConflicts == 0)
        {
            cout << " PASS: The schedule is valid (No time clashes).\n";
        }
        else
        {
            cout << " FAIL: Found " << totalConflicts << " schedule conflicts.\n";
        }
        cout << "======================================================\n";
    }
};

#endif // MODULE3_H