#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class PriorityQueue {
private:
    struct Node {
        T value;
        int priority;
        Node* next;
        Node(T val, int pri) : value(val), priority(pri), next(nullptr) {}
    };
    Node* head;

public:
    PriorityQueue() : head(nullptr) {}

    ~PriorityQueue() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

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

    void pop() {
        if (head == nullptr) {
            throw runtime_error("Queue is empty.");
        }
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    T top() {
        if (head == nullptr) {
            throw runtime_error("Queue is empty.");
        }
        return head->value;
    }

    bool empty() {
        return head == nullptr;
    }
};

#define V 5
void primMST(int graph[V][V]) {
    int parent[V];
    int key[V];
    bool mstSet[V];
    for (int i = 0; i < V; i++) {
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
        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
                pq.push(v, key[v]);
            }
        }
    }
    cout << "Minimalne drzewo rozpinajace: " << endl;
    cout << "Krawedzie     Waga" << endl;
    for (int i = 1; i < V; i++) {
        cout << parent[i] << " - " << i <<" \t\t" << graph[i][parent[i]] << endl;
    }
}

int main() {
    int graph[V][V] = { { 0, 2, 0, 6, 0 },
                        { 2, 0, 3, 8, 5 },
                        { 0, 3, 0, 0, 7 },
                        { 6, 8, 0, 0, 9 },
                        { 0, 5, 7, 9, 0 } };
    primMST(graph);
    return 0;
}