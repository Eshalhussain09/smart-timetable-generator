#ifndef MODULE1_H
#define MODULE1_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip> 
#include "structures.h" 

using namespace std;

//-------------------- Module 1: File Handling --------------------
class FileHandling
{
public:
    vector<Teacher> teachers;
    vector<ClassInfo> classesArr;
    vector<Room> rooms;
    vector<TimeSlot> slots;
    vector<vector<int>> distances;

    void readTeachers(const string& filename = "files/teachers.txt")
    {
        ifstream fin(filename);
        if (!fin) 
        {
            cout << "Error: " << filename << " not found.\n";
            return; 
        }
        teachers.clear();
        string line;
        while (getline(fin, line))
        {
            istringstream ss(line); 
            Teacher t;
            if (!(ss >> t.name)) 
                continue;
            string subj;
            while (ss >> subj)
                t.subjects.push_back(subj);
            teachers.push_back(t);
        }
        fin.close();
    }

    void readClasses(const string& filename = "files/classes.txt")
    {
        ifstream fin(filename);
        if (!fin)
        { 
            cout << "Error: " << filename << " not found.\n"; 
        return; 
        }
        classesArr.clear();
        string line;
        while (getline(fin, line))
        {
            istringstream ss(line);
            ClassInfo c;
            if (!(ss >> c.className >> c.subject))
                continue;
            classesArr.push_back(c);
        }
        fin.close();
    }

    void readRooms(const string& filename = "files/rooms.txt")
    {
        ifstream fin(filename);
        if (!fin) 
        {
            cout << "Error: " << filename << " not found.\n"; 
            return; 
        }
        rooms.clear();
        string name;
        while (fin >> name)
        {
            Room r;
            r.roomName = name;
            rooms.push_back(r);
        }
        fin.close();
    }

    void readTimeSlots(const string& filename = "files/timeslots.txt")
    {
        ifstream fin(filename);
        if (!fin) 
        {
            cout << "Error: " << filename << " not found.\n"; 
            return;
        }
        slots.clear();
        string name;
        while (fin >> name)
        {
            TimeSlot t;
            t.slotName = name;
            slots.push_back(t);
        }
        fin.close();
    }

    void readDistances(const string& filename = "files/distances.txt")
    {
        if (rooms.empty()) 
            return;

        ifstream fin(filename);
        if (!fin)
        {
            cout << "Error: " << filename << " not found.\n"; 
            return;
        }

        int rCount = rooms.size(); 
        distances.clear(); 
        distances.resize(rCount, vector<int>(rCount, 0));

        for (int i = 0; i < rCount; i++)
        {
            for (int j = 0; j < rCount; j++)
            {
                if (!(fin >> distances[i][j]))
                {
                    distances.clear();
                    break; 
                }
            }
        }
        fin.close();
    }

    void readAllData()
    {
        readTeachers();
        readClasses();
        readRooms();
        readTimeSlots();
        readDistances(); 
    }


    void displayTeachers()
    {
        cout << "\n--- Teachers List (" << teachers.size() << ") ---\n";
        if (teachers.empty())
            cout << "(No data)\n";
        for (size_t i = 0; i < teachers.size(); ++i)
        {
            cout << i + 1 << ". " << teachers[i].name << " -> ";
            for (const auto& s : teachers[i].subjects)
                cout << "[" << s << "] ";
            cout << endl;
        }
    }

    void displayClasses()
    {
        cout << "\n--- Classes List (" << classesArr.size() << ") ---\n";
        if (classesArr.empty())
            cout << "(No data)\n";
        for (size_t i = 0; i < classesArr.size(); ++i)
        {
            cout << i + 1 << ". Group: " << classesArr[i].className
                << " | Subject: " << classesArr[i].subject << endl;
        }
    }

    void displayRooms()
    {
        cout << "\n--- Rooms List (" << rooms.size() << ") ---\n";
        if (rooms.empty())
            cout << "(No data)\n";
        for (size_t i = 0; i < rooms.size(); ++i)
            cout << i + 1 << ". " << rooms[i].roomName << endl;
    }

    void displayTimeSlots()
    {
        cout << "\n--- Time Slots (" << slots.size() << ") ---\n";
        if (slots.empty()) 
            cout << "(No data)\n";
        for (size_t i = 0; i < slots.size(); ++i)
            cout << i + 1 << ". " << slots[i].slotName << endl;
    }

    void displayDistances()
    {
        cout << "\n--- Room Distances Matrix ---\n";
        if (distances.empty())
        {
            cout << "(No data)\n"; 
            return;
        }

        cout << "      ";
        for (const auto& r : rooms) 
            cout << setw(5) << r.roomName << " ";
        cout << endl;

        for (size_t i = 0; i < distances.size(); i++)
        {
            cout << setw(5) << rooms[i].roomName << " ";
            for (int d : distances[i])
                cout << setw(5) << d << " ";
            cout << endl;
        }
    }

    void displayAll()
    {
        displayTeachers();
        displayClasses();
        displayRooms();
        displayTimeSlots();
        displayDistances();
    }
};

#endif