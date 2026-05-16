#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>
#include <vector>

using namespace std;

//-------------------- Structures --------------------
struct Teacher
{
    string name;
    vector<string> subjects;
};

struct ClassInfo
{
    string className;
    string subject;
};

struct Room
{
    string roomName;
};

struct TimeSlot
{
    string slotName;
};

struct Session
{
    string className;
    string subject;
    string teacher;
    string room;
    string timeslot;
    string studentGroup;
};

#endif // STRUCTURES_H