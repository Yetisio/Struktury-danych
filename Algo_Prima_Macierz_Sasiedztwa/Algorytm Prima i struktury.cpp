#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;
int const V = 9;
// Funkcja zwracająca minimalną wagę krawędzi
int minKey(int key[], bool mstSet[], int V)
{
    // Inicjalizuj minimum jako nieskończony
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

// Funkcja wyświetlająca wynik
void printMST(int parent[], int n, int graph[][9])
{
    cout << "Krawedz    Waga\n";
    for (int i = 1; i < n; i++)
        cout << parent[i] << " - " << i << "    " << graph[i][parent[i]] << "\n";
}

// Funkcja generująca MST dla grafu podanego w postaci macierzy sąsiedztwa
int primMST(int graph[][V])
{
    int parent[V]; // tablica przechowująca rozpięte drzewo
    int key[V];   // tablica przechowująca połączone krawędzie
    bool mstSet[V];  // tablica wskazująca, czy wierzchołek należy już do MST

    // Inicjalizuj wszystkie klucze jako nieskończone i mstSet[] jako false
    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;

    // Ustaw klucz na 0 dla pierwszego wierzchołka
    key[0] = 0;
    parent[0] = -1; // To wierzchołek jest korzeniem MST

    // Przeglądaj wszystkie wierzchołki
    for (int count = 0; count < V - 1; count++)
    {
        // Wybierz najmniejszy klucz wierzchołka, który nie należy jeszcze do MST
        int u = minKey(key, mstSet, V);

        // Dodaj wierzchołek do MST
        mstSet[u] = true;

        // Aktualizuj klucze dla wszystkich sąsiadów wybranego wierzchołka.
        // Jeśli krawędź z wierzchołkiem u do sąsiada v jest mniejsza od obecnego
        // klucza dla v, to zaktualizuj klucz dla sąsiada.
        for (int v = 0; v < V; v++)
        {
            // graph[u][v] nie jest równy 0
            // mstSet[v] jest false
            // graph[u][v] jest mniejsze od dotychczasowego klucza dla wierzchołka v
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
            {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // Wyświetl wynik
   // printMST(parent, V, graph);
    // Obliczamy sumę wag dla MST
    int sum = 0;
    for (int i = 1; i < V; i++)
        sum += key[i];

    return sum;
}
// Driver program
int main()
{
    // Macierz sąsiedztwa dla grafu w postaci tablicy dwuwymiarowej
    int V = 9;
    int graph[9][9] = { {0, 4, 0, 0, 0, 0, 0, 8, 0},
                       {4, 0, 8, 0, 0, 0, 0, 11, 0},
                       {0, 8, 0, 7, 0, 4, 0, 0, 2},
                       {0, 0, 7, 0, 9, 14, 0, 0, 0},
                       {0, 0, 0, 9, 0, 10, 0, 0, 0},
                       {0, 0, 4, 14, 10, 0, 2, 0, 0},
                       {0, 0, 0, 0, 0, 2, 0, 1, 6},
                       {8, 11, 0, 0, 0, 0, 1, 0, 7},
                       {0, 0, 2, 0, 0, 0, 6, 7, 0}
    };

    // Wywołanie algorytmu
    cout<<primMST(graph);

    return 0;
}

