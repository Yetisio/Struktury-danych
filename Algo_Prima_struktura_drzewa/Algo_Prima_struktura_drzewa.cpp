#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;
int const V = 9;
// Struktura drzewa
struct Tree
{
    int rank;
    int parent;
};

// Funkcja tworząca zbiór z wierzchołka i
int makeSet(int i, vector<Tree>& sets)
{
    Tree newSet;
    newSet.rank = 0;
    newSet.parent = i;

    sets.push_back(newSet);
    return sets.size() - 1;
}

// Funkcja zwracająca reprezentanta zbioru wierzchołka i
int findSet(int i, vector<Tree>& sets)
{
    if (sets[i].parent != i)
        sets[i].parent = findSet(sets[i].parent, sets);

    return sets[i].parent;
}

// Funkcja łącząca 2 zbiory
void unionSet(int i, int j, vector<Tree>& sets)
{
    int i_id = findSet(i, sets);
    int j_id = findSet(j, sets);

    if (i_id == j_id)
        return;

    if (sets[i_id].rank > sets[j_id].rank)
        sets[j_id].parent = i_id;
    else
    {
        sets[i_id].parent = j_id;
        if (sets[i_id].rank == sets[j_id].rank)
            sets[j_id].rank++;
    }
}

// Funkcja wyznaczająca minimalne drzewo rozpinające (MST)
// dla grafu nieskierowanego o wagach
int PrimMST(vector<pair<int, int> > adj[])
{
    vector<pair<int, pair<int, int> > > edges;

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < adj[i].size(); j++)
        {
            int v = adj[i][j].first;
            int weight = adj[i][j].second;
            edges.push_back(make_pair(weight, make_pair(i, v)));
        }
    }

    sort(edges.begin(), edges.end());

    vector<Tree> sets(V);
    for (int i = 0; i < V; i++)
        makeSet(i, sets);

    int sumWeight = 0;
    vector<pair<int, pair<int, int> > >::iterator it;
    for (it = edges.begin(); it != edges.end(); it++)
    {
        int u = it->second.first;
        int v = it->second.second;

        int set_u = findSet(u, sets);
        int set_v = findSet(v, sets);

        if (set_u != set_v)
        {
            sumWeight += it->first;
            unionSet(set_u, set_v, sets);
        }
    }

    return sumWeight;
}

void addEdge(vector<pair<int, int> > adj[], int u, int v, int w)
{
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
}
int main()
{
   
    vector<pair<int, int> > adj[V];

    // dodaj krawędzie
    addEdge(adj, 0, 1, 4);
    addEdge(adj, 0, 7, 8);
    addEdge(adj, 1, 2, 8);
    addEdge(adj, 1, 7, 11);
    addEdge(adj, 2, 3, 7);
    addEdge(adj, 2, 8, 2);
    addEdge(adj, 2, 5, 4);
    addEdge(adj, 3, 4, 9);
    addEdge(adj, 3, 5, 14);
    addEdge(adj, 4, 5, 10);
    addEdge(adj, 5, 6, 2);
    addEdge(adj, 6, 7, 1);
    addEdge(adj, 6, 8, 6);
    addEdge(adj, 7, 8, 7);

    cout<<PrimMST(adj);

    return 0;
}