#include <iostream>
#include <climits>

using namespace std;

class Node {
public:
    int dest; //wierzcholek
    int weight; //waga
    Node* next; //wskaznik na nastepny wierzcholek
};
//stos do przechowywania wezlow nie uzytywych jeszcze w drzewie
class Stack {
private:
    int topIndex; //element na gorze stosu
    int size; // rozmiar stosu
    Node** data; //tablica obiektow Node
public:
    //konstruktor przyjmujacy maks rozmiar 
    Stack(int size) {
        topIndex = -1;
        this->size = size;
        data = new Node * [size]; //alokowanie pamieci
    }
    //zwalanianie pamieci obiektow w tablicy jak i samej tablicy
    ~Stack() {
        for (int i = 0; i <= topIndex; i++) {
            delete data[i];
        }
        delete[] data;
    }
    //funkcja dodaje element do stosu
    void push(Node* node) {
        data[++topIndex] = node;
    }
    //zwraca gore stosu
    Node* peek() {
        return data[topIndex];
    }
    //usuwa element w stosie
    void pop() {
        delete data[topIndex--];
    }
    //sprawdzanie czy stos jest pusty 
    bool isEmpty() {
        return topIndex == -1;
    }
};
class Stack_Graph {
private:
    int V; //liczba wierzcholkow
    Node** adjList; //tablica na obiekty Node
public:
    //konstrktor przyjmuje liczbe wierzcholkow
    //alokuje pamiec dla adjList o podanym rozmiarze
    //przypisuje nullptr dla kazdej wartosci co daje nam graf bez krawedzi i wierzcholki bez sasiadow
    Stack_Graph(int V) {
        this->V = V;
        adjList = new Node * [V];
        for (int i = 0; i < V; i++) {
            adjList[i] = nullptr;
        }
    }
    //destrukor ususwa elementy z listy a nastepnie cala liste
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
    //dodawanie krawedzi miedzy src a dest o wadze weight
    //tworzymy nowy wezel i dodajemy src do sasiadow dest i na odwrot
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
    //algorytm prima
    void primMST() {
        //tworzenie tablic dynamicznych dla kazdego z wierzcholkow
        int* parent = new int[V]; 
        int* key = new int[V];
        bool* mstSet = new bool[V];
        //ustawianie wartosci poczatkwoych
        for (int i = 0; i < V; i++) {
            parent[i] = -1;
            key[i] = INT_MAX;
            mstSet[i] = false;
        }

        key[0] = 0;
        Stack stos(V); //tworzenie pustego stosu
        stos.push(new Node{ 0, 0, nullptr }); //dodawany wierzcholek 0 z waga 0
        //warunek ze dopoki stos nie jest pusty szukamy wierzcholka z najnmiejsza waga
        while (!stos.isEmpty()) { 
            int u = stos.peek()->dest;
            stos.pop();
            //sprawdzenie czy wierzcholek jest juz w drzewie
            if (mstSet[u]) continue;
            mstSet[u] = true;

            Node* temp = adjList[u];
            //sprawdzamy czy dla kazdego sasiada "v" i wierzcholka "u" ktore jeszcze nie naleza do drzewa
            //i maja wage mniejsza niz dotychczasowa to wierzcholek "v" dodawany jest do stosu
            while (temp != nullptr) {
                int v = temp->dest;
                int weight = temp->weight;

                if (!mstSet[v] && key[v] > weight) {
                    key[v] = weight;
                    parent[v] = u;
                    stos.push(new Node{ v, key[v], nullptr });
                }
                temp = temp->next;
            }
        }
        //wypisywanie mst
        cout << "Minimalne drzewo rozpinajace: " << endl;
        cout << "Krawedzie     Waga" << endl;
        for (int i = 1; i < V; i++) {
            cout << parent[i] << " - " << i << " \t\t" << key[i] << endl;
        }
        //usuwanie pamieci
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