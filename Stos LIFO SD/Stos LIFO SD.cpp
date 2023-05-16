#include <iostream>
#include <climits>

using namespace std;

class Node {
public:
    int dest;
    int weight;
    Node* next;
};

class Stack {
private:
    int topIndex;
    int size;
    Node** data;
public:
    Stack(int size) {
        topIndex = -1;
        this->size = size;
        data = new Node * [size];
    }

    ~Stack() {
        for (int i = 0; i <= topIndex; i++) {
            delete data[i];
        }
        delete[] data;
    }

    void push(Node* node) {
        data[++topIndex] = node;
    }

    Node* peek() {
        return data[topIndex];
    }

    void pop() {
        delete data[topIndex--];
    }

    bool isEmpty() {
        return topIndex == -1;
    }
};

class Stack_Graph {
private:
    int V;
    Node** adjList;
public:
    Stack_Graph(int V) {
        this->V = V;
        adjList = new Node * [V];
        for (int i = 0; i < V; i++) {
            adjList[i] = nullptr;
        }
    }

    ~Stack_Graph() {
        for (int i = 0; i < V; i++) {
            Node* temp = adjList[i];
            while (temp != nullptr) {
                Node* next = temp->next;
                delete temp;
                temp = next;
            }
        }
        delete[] adjList;
    }

    void addEdge(int src, int dest, int weight) {
        Node* newNode = new Node;
        newNode->dest = dest;
        newNode->weight = weight;
        newNode->next = adjList[src];
        adjList[src] = newNode;

        newNode = new Node;
        newNode->dest = src;
        newNode->weight = weight;
        newNode->next = adjList[dest];
        adjList[dest] = newNode;
    }

    void primMST() {
        int* parent = new int[V];
        int* key = new int[V];
        bool* mstSet = new bool[V];

        for (int i = 0; i < V; i++) {
            parent[i] = -1;
            key[i] = INT_MAX;
            mstSet[i] = false;
        }

        key[0] = 0;
        Stack pq(V);
        pq.push(new Node{ 0, 0, nullptr });

        while (!pq.isEmpty()) {
            int u = pq.peek()->dest;
            pq.pop();

            if (mstSet[u]) continue;
            mstSet[u] = true;

            Node* temp = adjList[u];
            while (temp != nullptr) {
                int v = temp->dest;
                int weight = temp->weight;

                if (!mstSet[v] && key[v] > weight) {
                    key[v] = weight;
                    parent[v] = u;
                    pq.push(new Node{ v, key[v], nullptr });
                }
                temp = temp->next;
            }
        }
        cout << "Minimalne drzewo rozpinajace: " << endl;
        cout << "Krawedzie     Waga" << endl;
        for (int i = 1; i < V; i++) {
            cout << parent[i] << " - " << i << " \t\t" << key[i] << endl;
        }

        delete[] parent;
        delete[] key;
        delete[] mstSet;
    }
};

int main() {
    int V = 5;
    Stack_Graph graph(V);

    graph.addEdge(0, 1, 2);
    graph.addEdge(0, 3, 6);
    graph.addEdge(1, 2, 3);
    graph.addEdge(1, 3, 8);
    graph.addEdge(1, 4, 5);
    graph.addEdge(2, 4, 7);
    graph.addEdge(3, 4, 9);

    graph.primMST();

    return 0;
}