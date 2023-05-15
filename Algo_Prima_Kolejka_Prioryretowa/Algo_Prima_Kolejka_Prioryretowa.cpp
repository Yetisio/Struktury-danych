#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

#define INF 0x3f3f3f3f  //nieskocznosc dla poczatkowego wierzcholka, najwieksza wartosc int w syst 16
int const V = 9;
typedef pair<int, int> iPair;

// Tworzymy graf przy użyciu macierzy sąsiedztwa
void addEdge(vector<pair<int, int> > adj[], int u, int v, int wt)
{
    adj[u].push_back(make_pair(v, wt));
    adj[v].push_back(make_pair(u, wt));
}

// Funkcja PrimMST ()
// Zwraca sumę wag dla minimalnego drzewa rozpinającego
// wykorzystując algorytm Prima 
int PrimMST(vector<pair<int, int> > adj[])
{
    // wektor przechowujący czy został odwiedzony dany wierzchołek
    vector<bool> inMST(V, false);

    // tablica przechowująca krawędź o najmniejszej wadze
    // wychodzącą z danego wierzchołka
    int parent[V];

    // tablica przechowująca wagę danej krawędzi
    int key[V];

    // kolejka priorytetowa 
    priority_queue< iPair, vector <iPair>, greater<iPair> > pq;

    // inicjalizacja wszystkich wag na nieskończoność
    for (int i = 0; i < V; i++)
        key[i] = INF;

    // ustawienie wagi pierwszego wierzchołka na 0
    // aby był on pierwszym wybranym wierzchołkiem MST
    pq.push(make_pair(0, 0));
    key[0] = 0;
    parent[0] = -1; // Dla wierzchołka 0 nie ma rodzica

    // Główna pętla wykonująca algorytm Prima
    while (!pq.empty())
    {
        // Pobieramy krawędź z najmniejszą wagą z kolejki
        int u = pq.top().second;
        pq.pop();

        inMST[u] = true; // Dodajemy wierzchołek do MST

        // Przeglądamy wszystkie krawędzie wychodzące z wierzchołka u
        for (auto x : adj[u])
        {
            // v to wierzchołek do którego wychodzi krawędź
            int v = x.first;
            int weight = x.second;

            // Sprawdzamy czy krawędź v-u jest lepsza niż dotychczasowa
            if (inMST[v] == false && key[v] > weight)
            {
                // Uaktualniamy wagę krawędzi
                key[v] = weight;
                pq.push(make_pair(key[v], v));
                parent[v] = u;
            }
        }
    }

    // Obliczamy sumę wag dla MST
    int sum = 0;
    for (int i = 1; i < V; i++)
        sum += key[i];

    return sum;
}

// Funkcja główna
int main()
{
    
    vector<pair<int, int> > adj[V];

    // Dodajemy krawędzie
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

    cout << "Suma wag minimalnego drzewa rozpinającego wynosi: " << PrimMST(adj);

    return 0;
}