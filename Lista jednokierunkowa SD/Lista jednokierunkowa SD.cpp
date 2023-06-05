#include <iostream>
#include <climits>

using namespace std;

class Node {
public:
    int dest; //wierzcholek
    int weight; //waga krawedzi
    Node* next; //wskaznik na nastepny wezel
};

class List {
private:
    int V; //liczba wierzcholkow grafu
    Node** adjList; //lista sasiedztwa
    int* parent; //tablica rodzica 
    int* key; // tablica wag krawedzi
    bool* mstSet; // tablica sprawdzajaca czy wierzcholek juz jest
public:
    //konstruktor przyjmujacy liczbe wierzcholkow, tworzocy tablice i przypisanie im konkretynch wartosci
    List(int V) {
        this->V = V;
        adjList = new Node * [V];
        for (int i = 0; i < V; i++) {
            adjList[i] = nullptr;
        }
        parent = new int[V];
        key = new int[V];
        mstSet = new bool[V];
        for (int i = 0; i < V; i++) {
            parent[i] = -1;
            key[i] = INT_MAX;
            mstSet[i] = false;
        }
    }
    //usuawanie zaalakowanej pamieci tablic i listy
    ~List() {
        delete[] parent;
        delete[] key;
        delete[] mstSet;
        for (int i = 0; i < V; i++) {
            Node* curr = adjList[i];
            while (curr != nullptr) {
                Node* tmp = curr;
                curr = curr->next;
                delete tmp;
            }
        }
        delete[] adjList;
    }
    //dodawanie krawedzi miedzy wierzcholkami poczatkowym a nastepnym wskaznaym i przypisujacy jej wage 
    void addEdge(int src, int dest, int weight) {
        Node* newNode = new Node();
        newNode->dest = dest;
        newNode->weight = weight;
        newNode->next = adjList[src];
        adjList[src] = newNode;
    }
    //funkcja zwracajaca wierzcholek o najmniejszej wadze ktory jeszcze nie jest w Minimalnym Drzewie Rozpinajacym
    int minKey() {
        int min = INT_MAX, minIndex;
        for (int v = 0; v < V; v++) {
            if (mstSet[v] == false && key[v] < min) {
                min = key[v];
                minIndex = v;
            }
        }
        return minIndex;
    }
    //wypisanie minimalnego drzewa rozpinajacego 
    void printMST() {
        cout << "Minimalne drzewo rozpinajace: " << endl;
        cout << "Krawedzie     Waga" << endl;
        for (int i = 1; i < V; i++) {
            cout << parent[i] << " - " << i << " \t\t" << key[i] << endl;
        }
    }
    //algorytm prima
    //szukamy wierzcholka o najmniejszej wadze ktory jeszcze nie jest w MST
    //nastepnie dodajemy ten wierzcholek i odhaczamy go jako ze byl juz odwiedzony
    //sprawdzemy liste sasiedztwa dla danego wierzcholka i ponownie sprawdzamy wage dla tych sasiednich wierzcholkow
    //tak do uzyskania MST
    void primMST() {
        key[0] = 0;
        parent[0] = -1;
        for (int count = 0; count < V - 1; count++) {
            int u = minKey();
            mstSet[u] = true;
            Node* curr = adjList[u];
            while (curr != nullptr) {
                int v = curr->dest;
                int weight = curr->weight;
                if (mstSet[v] == false && weight < key[v]) {
                    parent[v] = u;
                    key[v] = weight;
                }
                curr = curr->next;
            }
        }
        printMST();
    }
};
//2 formy kolejki prio, 3 reprezentacje grafow
//generator grafow
int main() {
    int V = 5;
    List graph(V);

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
