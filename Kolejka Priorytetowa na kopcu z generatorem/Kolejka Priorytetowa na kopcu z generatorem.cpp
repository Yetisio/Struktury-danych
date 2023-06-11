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
        T value; // wartość elementu
        int priority; // priorytet
        Node(T val, int pri) : value(val), priority(pri) {} // konstruktor struktury Node
    };

    vector<Node> heap; // tablica przechowująca elementy kolejki

    void heapifyUp(int index) {
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (heap[index].priority < heap[parentIndex].priority) {
                swap(heap[index], heap[parentIndex]);
                index = parentIndex;
            }
            else {
                break;
            }
        }
    }

    void heapifyDown(int index) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int smallest = index;

        if (leftChild < heap.size() && heap[leftChild].priority < heap[smallest].priority) {
            smallest = leftChild;
        }
        if (rightChild < heap.size() && heap[rightChild].priority < heap[smallest].priority) {
            smallest = rightChild;
        }

        if (smallest != index) {
            swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    PriorityQueue() {}

    ~PriorityQueue() {}

    void push(T val, int pri) {
        Node newNode(val, pri);
        heap.push_back(newNode);
        heapifyUp(heap.size() - 1);
    }

    void pop() {
        if (heap.empty()) {
            throw runtime_error("Kolejka priorytetowa jest pusta");
        }
        swap(heap[0], heap[heap.size() - 1]);
        heap.pop_back();
        heapifyDown(0);
    }

    T top() {
        if (heap.empty()) {
            throw runtime_error("Kolejka priorytetowa jest pusta");
        }
        return heap[0].value;
    }

    bool empty() {
        return heap.empty();
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
    int numVertices = 10;  // Liczba wierzchołków grafu 5, 7, 3,10
    int numEdges = 15;     // Liczba krawędzi grafu 8, 12, 3,15
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
