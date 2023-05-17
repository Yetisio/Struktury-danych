#include <iostream>
#include <stdexcept>

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

#define V 5
//algorytm prima
void primMST(int graph[V][V]) {
    //tworzymy tablice dla rodzica, wagi i zbioru wierzcholkow mst
    int parent[V];
    int key[V];
    bool mstSet[V];
    //ustwianie wartosci poczatkowych
    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }
    //tworzymy kolejke wg template
    PriorityQueue<int> pq;
    pq.push(0, 0); //dodajemy pierwszy wierzcholek 0 z waga 0
    key[0] = 0;
    parent[0] = -1;
    //dopoki kolejka nie jest pusta, pobieramy wierzcholek o najmniejszym prio i oznaczamy go ze nalezy juz do MST
    //dla kazdego sasiada "v" wierzcholka "u" jezeli "v" nie jest jeszcze w MST a waga jest mniejsza niz aktualna waga 
    //dodajemy wierzcholek "v" do kolejki z nowa waga
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
    //wypisuje mst
    cout << "Minimalne drzewo rozpinajace: " << endl;
    cout << "Krawedzie     Waga" << endl;
    for (int i = 1; i < V; i++) {
        cout << parent[i] << " - " << i <<" \t\t" << graph[i][parent[i]] << endl;
    }
}

int main() {
    //macierz sasiedztwa
    //wartosc w komorce oznacza wage miedzy wierzcholkami k i w, gdzie k to kolumna a w to wiersz
    //jezeli krawedzi nie ma wpisywane jest 0 
    int graph[V][V] = { { 0, 2, 0, 6, 0 },
                        { 2, 0, 3, 8, 5 },
                        { 0, 3, 0, 0, 7 },
                        { 6, 8, 0, 0, 9 },
                        { 0, 5, 7, 9, 0 } };
    primMST(graph);
    return 0;
}