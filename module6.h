#ifndef MODULE6_H
#define MODULE6_H

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <fstream>
#include "structures.h"

using namespace std;

//-------------------- Module 6: Euler & Hamilton Path Check --------------------
class PathChecker
{
public:
    void checkEulerPath(const vector<vector<int>>& distances, const vector<Room>& rooms)
    {
        int n = rooms.size();
        if (n == 0)
            return;

        vector<int> degree(n, 0);
        int oddCount = 0;

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (distances[i][j] > 0 && distances[i][j] != 999)
                    degree[i]++;
            }
            if (degree[i] % 2 != 0)
                oddCount++;
        }

        cout << "\n--- Module 6: Euler Path Check ---\n";
        if (oddCount == 0 || oddCount == 2)
        {
            cout << "Euler Path exists.\n";
            vector<int> eulerPath = findEulerPath(distances);
            cout << "Euler Path: ";
            for (size_t i = 0; i < eulerPath.size(); ++i)
            {
                cout << rooms[eulerPath[i]].roomName;
                if (i != eulerPath.size() - 1) 
                    cout << " -> ";
            }
            cout << endl;

            ofstream fout("files/euler_path.txt");
            for (size_t i = 0; i < eulerPath.size(); ++i)
            {
                fout << rooms[eulerPath[i]].roomName;
                if (i != eulerPath.size() - 1) fout << " -> ";
            }
            fout.close();
        }
        else
        {
            cout << "No Euler Path exists in this graph.\n";
        }
        cout << "======================================================\n";
    }

    void checkHamiltonianPath(const vector<vector<int>>& distances, const vector<Room>& rooms)
    {
        int n = rooms.size();
        if (n == 0) return;

        cout << "\n--- Module 6: Hamiltonian Path Check ---\n";

        vector<int> path;
        vector<bool> visited(n, false);
        bool found = false;

        for (int start = 0; start < n && !found; ++start)
        {
            visited.assign(n, false);
            path.clear();
            path.push_back(start);
            visited[start] = true;

            if (hamiltonianBacktrack(start, path, visited, distances))
            {
                found = true;
                cout << "Hamiltonian Path found: ";
                for (size_t i = 0; i < path.size(); ++i)
                {
                    cout << rooms[path[i]].roomName;
                    if (i != path.size() - 1) cout << " -> ";
                }
                cout << endl;

                ofstream fout("files/hamilton_path.txt");
                for (size_t i = 0; i < path.size(); ++i)
                {
                    fout << rooms[path[i]].roomName;
                    if (i != path.size() - 1) fout << " -> ";
                }
                fout.close();
                break;
            }
        }

        if (!found)
            cout << "No Hamiltonian Path exists (graph too complex or disconnected).\n";

        cout << "======================================================\n";
    }

private:
    vector<int> findEulerPath(const vector<vector<int>>& distances)
    {
        int n = distances.size();
        vector<vector<int>> adj(n);
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (distances[i][j] > 0 && distances[i][j] != 999)
                    adj[i].push_back(j);
            }
        }

        stack<int> currPath;
        vector<int> circuit;

        int start = 0;
        for (int i = 0; i < n; ++i)
        {
            if (adj[i].size() % 2 != 0)
            {
                start = i;
                break;
            }
        }

        currPath.push(start);
        vector<vector<int>> tempAdj = adj;

        while (!currPath.empty())
        {
            int curr = currPath.top();
            if (!tempAdj[curr].empty())
            {
                int next = tempAdj[curr].back();
                tempAdj[curr].pop_back();
                auto& vec = tempAdj[next];
                vec.erase(find(vec.begin(), vec.end(), curr)); 
                currPath.push(next);
            }
            else
            {
                circuit.push_back(curr);
                currPath.pop();
            }
        }

        reverse(circuit.begin(), circuit.end());
        return circuit;
    }

    bool hamiltonianBacktrack(int curr, vector<int>& path, vector<bool>& visited, const vector<vector<int>>& distances)
    {
        int n = distances.size();
        if (path.size() == n)
            return true;

        for (int next = 0; next < n; ++next)
        {
            if (!visited[next] && distances[curr][next] > 0 && distances[curr][next] != 999)
            {
                visited[next] = true;
                path.push_back(next);

                if (hamiltonianBacktrack(next, path, visited, distances))
                    return true;

                visited[next] = false;
                path.pop_back();
            }
        }
        return false;
    }
};

#endif // MODULE6_H
