#include <iostream>
#include <stdexcept>
#include <vector>
#include <time.h>
#include <climits>
using namespace std;

template <typename T>
class PriorityQueue {
private:
    struct Node {
        T value; //wartosc elementu
        int priority; //priorytet
        Node* next; //wskaznik na nastepny element
        Node(T val, int pri) : value(val), priority(pri), next(nullptr) {} //konstruktor struktury Node
    };
    Node* head; //wskaznik na pierwszy elemenet kolejki

public:
    PriorityQueue() : head(nullptr) {} //ustawianie wartosci head jako nic
    //zwalnianie pamieci dla kazdego elementu kolejki
    ~PriorityQueue() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    //dodawanie elementu do kolejki
    //element dodawany jest wg priorytetu
    //jezeli head ma wieksze prio nowy element staje nowym head
    //jezeli nie to przeszukuje sie kolejke aby wstawic dany element w odpowiednie miejsce
    void push(T val, int pri) {
        Node* new_node = new Node(val, pri);
        if (head == nullptr || pri < head->priority) {
            new_node->next = head;
            head = new_node;
        }
        else {
            Node* temp = head;
            while (temp->next != nullptr && temp->next->priority <= pri) {
                temp = temp->next;
            }
            new_node->next = temp->next;
            temp->next = new_node;
        }
    }
    //usuwa element
    void pop() {
        if (head == nullptr) {
            throw runtime_error("Pusta"); //wyjatek jesli kolejka jest pusta
        }
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    //zwraca nam wartosc elementu o najwyzszym prio
    T top() {
        if (head == nullptr) {
            throw runtime_error("Pusta"); //wyjatek jesli kolejka jest pusta
        }
        return head->value;
    }
    //sprawdzenie pustosci kolejki
    bool empty() {
        return head == nullptr;
    }
};


// Algorytm Prima dla macierzy sasiedztwa
void primMST_ms(int** graph, int numVertices) {
    int* parent = new int[numVertices];
    int* key = new int[numVertices];
    bool* mstSet = new bool[numVertices];

    for (int i = 0; i < numVertices; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    PriorityQueue<int> pq;
    pq.push(0, 0);
    key[0] = 0;
    parent[0] = -1;

    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();
        mstSet[u] = true;

        for (int v = 0; v < numVertices; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
                pq.push(v, key[v]);
            }
        }
    }

    cout << "Minimalne drzewo rozpinajace:" << endl;
    cout << "Krawedzie     Waga" << endl;
    for (int i = 1; i < numVertices; i++) {
        cout << parent[i] << " - " << i << " \t\t" << graph[i][parent[i]] << endl;
    }

    delete[] parent;
    delete[] key;
    delete[] mstSet;
}
//dla listy sasiedztwa
void primMST_ls(const vector<vector<pair<int, int>>>& adjacencyList) {
    int numVertices = adjacencyList.size();
    int* parent = new int[numVertices];
    int* key = new int[numVertices];
    bool* mstSet = new bool[numVertices];

    for (int i = 0; i < numVertices; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    PriorityQueue<int> pq;
    pq.push(0, 0);
    key[0] = 0;
    parent[0] = -1;

    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();
        mstSet[u] = true;

        for (const auto& neighbor : adjacencyList[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (!mstSet[v] && weight < key[v]) {
                parent[v] = u;
                key[v] = weight;
                pq.push(v, key[v]);
            }
        }
    }

    cout << "Minimalne drzewo rozpinajace:" << endl;
    cout << "Krawedzie     Waga" << endl;
    for (int i = 1; i < numVertices; i++) {
        cout << parent[i] << " - " << i << " \t\t" << key[i] << endl;
    }

    delete[] parent;
    delete[] key;
    delete[] mstSet;
}
struct Edge {
    int source;
    int destination;
    int weight;
};
//dla listy krawedzi
void primMST_lk(const vector<Edge>& edgeList, int numVertices, int numEdges) {
    int* parent = new int[numVertices];
    int* key = new int[numVertices];
    bool* mstSet = new bool[numVertices];

    for (int i = 0; i < numVertices; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    PriorityQueue<int> pq;
    pq.push(0, 0);
    key[0] = 0;
    parent[0] = -1;

    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();
        mstSet[u] = true;

        for (int i = 0; i < numEdges; i++) {
            const Edge& edge = edgeList[i];
            if ((edge.source == u || edge.destination == u) && !mstSet[edge.destination]) {
                int v = (edge.source == u) ? edge.destination : edge.source;
                if (edge.weight < key[v]) {
                    parent[v] = u;
                    key[v] = edge.weight;
                    pq.push(v, key[v]);
                }
            }
        }
    }

    cout << "Minimalne drzewo rozpinajace:" << endl;
    cout << "Krawedzie     Waga" << endl;
    for (int i = 1; i < numVertices; i++) {
        cout << parent[i] << " - " << i << " \t\t" << key[i] << endl;
    }

    delete[] parent;
    delete[] key;
    delete[] mstSet;
};
// Funkcja sprawdza, czy graf jest spójny
bool isConnected(bool* visited, int numVertices) {
    for (int i = 0; i < numVertices; ++i) {
        if (!visited[i]) {
            return false;
        }
    }
    return true;
}

// Funkcja generująca losowy graf nieskierowany i spójny
Edge* generateGraph(int numVertices, int numEdges) {
    srand(time(0));
    Edge* graph = new Edge[numEdges * 2];
    bool* visited = new bool[numVertices];
    for (int i = 0; i < numVertices; ++i) {
        visited[i] = false;
    }

    int edgeCount = 0;

    // Dodawanie losowych krawędzi, gwarantując spójność
    int currentVertex = 0;
    visited[currentVertex] = true;

    while (!isConnected(visited, numVertices)) {
        int destination = rand() % numVertices;
        if (!visited[destination]) {
            int weight = rand() % 100;  // Losowa waga krawędzi (można dostosować zakres)

            Edge edge;
            edge.source = currentVertex;
            edge.destination = destination;
            edge.weight = weight;

            graph[edgeCount] = edge;
            ++edgeCount;

            // Dodanie krawędzi dla drugiego wierzchołka dla utrzymania grafu nieskierowanego
            swap(edge.source, edge.destination);
            graph[edgeCount] = edge;
            ++edgeCount;

            visited[destination] = true;
        }
        currentVertex = destination;
    }

    delete[] visited;
    return graph;
}
// Funkcja tworząca macierz sąsiedztwa na podstawie grafu
int** createAdjacencyMatrix(const Edge* graph, int numVertices, int numEdges) {
    int** adjacencyMatrix = new int* [numVertices];
    for (int i = 0; i < numVertices; i++) {
        adjacencyMatrix[i] = new int[numVertices];
        for (int j = 0; j < numVertices; j++) {
            adjacencyMatrix[i][j] = 0;
        }
    }

    for (int i = 0; i < numEdges; i++) {
        int source = graph[i].source;
        int destination = graph[i].destination;
        int weight = graph[i].weight;

        adjacencyMatrix[source][destination] = weight;
        adjacencyMatrix[destination][source] = weight;
    }

    return adjacencyMatrix;
}
//tworzenie listy sasiedztwa
vector<vector<pair<int, int>>> createAdjacencyList(const Edge* graph, int numVertices, int numEdges) {
    vector<vector<pair<int, int>>> adjacencyList(numVertices);

    for (int i = 0; i < numEdges; i++) {
        int source = graph[i].source;
        int destination = graph[i].destination;
        int weight = graph[i].weight;

        adjacencyList[source].emplace_back(destination, weight);
        adjacencyList[destination].emplace_back(source, weight);
    }

    return adjacencyList;
}
//tworzenie listy krawedzi
vector<Edge> generateEdgeList(const Edge* graph, int numEdges) {
    vector<Edge> edgeList;
    for (int i = 0; i < numEdges * 2; i++) {
        edgeList.push_back(graph[i]);
    }
    return edgeList;
}





int main() {
    int numVertices = 7;  // Liczba wierzchołków grafu 5, 7, 3,10
    int numEdges = 12;     // Liczba krawędzi grafu 8, 12, 3,15
    Edge* graph = generateGraph(numVertices, numEdges);
    // Tworzenie macierzy sąsiedztwa na podstawie grafu
    int** adjacencyMatrix = createAdjacencyMatrix(graph, numVertices, numEdges);
    vector<vector<pair<int, int>>> adjacencyList = createAdjacencyList(graph, numVertices, numEdges);
    vector<Edge> edgeList = generateEdgeList(graph, numEdges);

    primMST_ms(adjacencyMatrix, numVertices);
    primMST_ls(adjacencyList);
    primMST_lk(edgeList, numVertices, numEdges);
    delete[] adjacencyMatrix;
    delete[] graph;

    return 0;
}
