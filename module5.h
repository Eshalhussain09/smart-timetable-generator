#ifndef MODULE5_H
#define MODULE5_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <numeric>
#include "structures.h"

using namespace std;

//-------------------- Module 5: Optimal Route Finder (MST) --------------------
class RoutePlanner
{
public:
    int totalDistance; 

    vector<pair<int, int>> mstEdges; 

    RoutePlanner() : totalDistance(0) {}

    //-------------------- Prim's Algorithm --------------------
    void computeMST_Prim(const vector<Room>& rooms, const vector<vector<int>>& distances)
    {
        int n = rooms.size();
        if (n == 0) 
            return;

        vector<int> key(n, INT_MAX); 
        vector<int> parent(n, -1);
        vector<bool> inMST(n, false);

        key[0] = 0;

        for (int count = 0; count < n - 1; ++count)
        {
            int u = minKey(key, inMST, n);
            inMST[u] = true;

            for (int v = 0; v < n; ++v)
            {
                if (!inMST[v] && distances[u][v] && distances[u][v] < key[v])
                {
                    key[v] = distances[u][v];
                    parent[v] = u;
                }
            }
        }

        mstEdges.clear();
        totalDistance = 0;
        for (int i = 1; i < n; ++i)
        {
            mstEdges.push_back({ parent[i], i });
            totalDistance += distances[parent[i]][i];
        }
    }

    //-------------------- Kruskal's Algorithm --------------------
    void computeMST_Kruskal(const vector<Room>& rooms, const vector<vector<int>>& distances)
    {
        int n = rooms.size();
        if (n == 0) 
            return;

        vector<tuple<int, int, int>> edges;
        for (int i = 0; i < n; ++i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                if (distances[i][j] > 0 && distances[i][j] != 999)
                    edges.push_back({ distances[i][j], i, j });
            }
        }

        sort(edges.begin(), edges.end());

        vector<int> parent(n);
        iota(parent.begin(), parent.end(), 0);

        auto findParent = [&](int x) 
            {
            while (parent[x] != x)
                x = parent[x];
            return x;
            };

        auto unionSet = [&](int x, int y) 
            {
            int px = findParent(x);
            int py = findParent(y);
            parent[px] = py;
            };

        mstEdges.clear();
        totalDistance = 0;
        for (auto& e : edges)
        {
            int w, u, v;
            tie(w, u, v) = e;
            if (findParent(u) != findParent(v))
            {
                mstEdges.push_back({ u, v });
                totalDistance += w;
                unionSet(u, v);
            }
        }
    }

    void printMST(const vector<Room>& rooms)
    {
        cout << "\n--- Module 5: MST (Optimal Teacher Movement) ---\n";
        cout << "Total Distance: " << totalDistance << "\n";
        for (auto& edge : mstEdges)
        {
            cout << rooms[edge.first].roomName << " -> " << rooms[edge.second].roomName << endl;
        }
        cout << "======================================================\n";
    }

private:
    int minKey(const vector<int>& key, const vector<bool>& inMST, int n)
    {
        int minVal = INT_MAX, minIndex = -1;
        for (int v = 0; v < n; ++v)
        {
            if (!inMST[v] && key[v] < minVal)
            {
                minVal = key[v];
                minIndex = v;
            }
        }
        return minIndex;
    }
};

#endif // MODULE5_H
