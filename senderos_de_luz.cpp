#include <iostream>
#include <string>
#include <sstream>
using namespace std;

/*
Estructuras de datos, Lista y Cola, utilizadas para el codigo de dijkstra (Preferi no usar la libreria de C++ porque quise tener un mayor
control sobre los nodos)
*/

template <typename T>
class Node {
    public:
        T payload;
        Node<T>* prev;
        Node<T>* next;

        Node(T v) {
            payload = v;
            prev = nullptr;
            next = nullptr;
        }
};

template <typename T>
class List
{
    private:
        Node<T>* _first;
        Node<T>* _last;

    public:
        List() {
            _first = _last = nullptr;
        }

        ~List() {
            while (!isEmpty()) {
            remove(first());
            }
        }

        bool isEmpty() {
            return _first == nullptr;
        }

        T* get(Node<T>* p) {
            if (p == nullptr) return nullptr;
            return &(p->payload);
        }

        void next(Node<T>* &p) {
            if (p == nullptr) return;
            p = p->next;
        }
        void prev(Node<T>* &p) {
            if (p == nullptr) return;
            p = p->prev;
        }
        
        Node<T>* first() {
            return _first;
        }
        
        Node<T>* last() {
            return _last;
        }
        
        void preInsert(Node<T> *p, T v) {
            Node<T>* newnode = new Node<T>(v);

            if (_first == p) _first = newnode;
            

            if (_last == nullptr) _last = newnode;
            newnode->next = p;

            if (p == nullptr) return;
            newnode->prev = p->prev;

            if (p->prev != nullptr) p->prev->next = newnode;
            p->prev = newnode;
        }

        void postInsert(Node<T>* p, T v) {
            Node<T>* newnode = new Node<T>(v);

            if (_last == p) _last = newnode;
            
            if (_first == nullptr) _first = newnode;
            newnode->prev = p;

            if (p == nullptr) return;
            newnode->next = p->next;

            if (p->next != nullptr) p->next->prev = newnode;
            p->next = newnode;
        }

        void remove(Node<T>* p) {
            if (p == nullptr) return;

            if (p->prev != nullptr) p->prev->next = p->next;
        
            if (p->next != nullptr) p->next->prev = p->prev;

            if (p == _first) _first = p->next;

            if (p == _last) _last = p->prev;
        
            delete p;
        }
};

template <typename T>
class Queue : List<T> {
    public:
        bool isEmpty() {
            return List<T>::isEmpty();
        }
        void push(T v) {
            List<T>::postInsert(List<T>::last(), v);
        }
        T* first() {
            if (isEmpty()) return nullptr;
            return &List<T>::first()->payload;
        }
        T pop() {
            T x = List<T>::first()->payload;
            List<T>::remove(List<T>::first());
        return x;
        }
};

struct Delivery{
    int endSantuary;
    int weightFragment;
};

struct Sanctuary {
    int tag;
    int time;
    int maxLoad;
    string road;
};

struct Route {
    int time = 0;
    string roadLog = "";
};

Route Dijkstra (int init, int end, int load, int &weight, int countSanctuary, int **conectionMatrix, int **stabilityMatrix) {
    List<Sanctuary> adjacency;
    List<Sanctuary> solution;
    int roadTime = 0;
    string road = "";

    while (init != end) {
        
        for (int i = 1; i < countSanctuary + 1; i++) {
            bool isVisited = false;

            if (conectionMatrix[init][i] == 0) isVisited = true;

            Node<Sanctuary> *q = solution.first();
            while (q != nullptr) {
                if(q->payload.tag == i) {
                    isVisited = true;
                    break;
                }
                q = q->next;
            }

            if(isVisited == true) continue;

            Sanctuary sanctuary;
            sanctuary.tag = i;
            sanctuary.time = roadTime + conectionMatrix[init][i];
            sanctuary.maxLoad = stabilityMatrix[init][i];
            sanctuary.road = road;

            adjacency.postInsert(adjacency.last(),sanctuary);
        
        }
        
        Node<Sanctuary> *q = adjacency.first();
        if (q == nullptr) break;

        Sanctuary auxQ;
        int auxTime = INT32_MAX;
        bool foundPath = false;

        while (q != nullptr) {

            if (q->payload.maxLoad >= weight && q->payload.time < auxTime) {
                auxTime = q->payload.time;
                auxQ = q->payload;
                foundPath = true;
            }
            q = q->next;
        }

        if (!foundPath) break;

        q = adjacency.first();
        
        while (q != nullptr) {
            if (auxQ.tag == q->payload.tag) {
                Node<Sanctuary> *auxD = q;
                q = q->next;
                adjacency.remove(auxD);
            } else {
                q = q->next;
            }

        }

        init = auxQ.tag;
        roadTime = auxQ.time;
        road = auxQ.road + to_string(init) + " ";

        solution.postInsert(solution.last(), auxQ);

    }

    Route endPoint;
    endPoint.roadLog = road;
    endPoint.time = roadTime;
    weight -= load;
    return endPoint;

}

int main () {
    string line;
    Queue<Delivery> list_delivery;
    int totalWeight = 0;
    int countSanctuary = 0;
    int startSanctuary;
    bool isCreated = 0;
    int **conectionMatrix;
    int **stabilityMatrix;
    string finalRoad = "";
    int time = 0;

    int maxSanctuary = 0; 
    Queue<int> list_senderos; 

    while (getline(cin, line)) {
        stringstream ss(line);
        int number = 0;
        int count = 0;
        Queue<int> data_line;

        while (ss >> number) {
            count++;
            data_line.push(number);
        }

        if(count == 2) {
            Delivery delivery;
            int id = data_line.pop();
            int weight = data_line.pop();
            
            delivery.endSantuary = id;
            delivery.weightFragment = weight;
            totalWeight += weight;
            list_delivery.push(delivery);

            if (id > maxSanctuary) maxSanctuary = id; 
        }

        if(count == 4) {
            int u = data_line.pop();
            int v = data_line.pop();
            int t = data_line.pop();
            int w = data_line.pop();

            list_senderos.push(u);
            list_senderos.push(v);
            list_senderos.push(t);
            list_senderos.push(w);

            if (u > maxSanctuary) maxSanctuary = u;
            if (v > maxSanctuary) maxSanctuary = v;
        }

        if(count == 1) {
            startSanctuary = data_line.pop();
            finalRoad += to_string(startSanctuary) + " ";
            if (startSanctuary > maxSanctuary) maxSanctuary = startSanctuary;
            
            break; 
        }
    }

    countSanctuary = maxSanctuary; 

    conectionMatrix = new int*[countSanctuary + 1];
    stabilityMatrix = new int*[countSanctuary + 1];

    for (int i = 0; i < countSanctuary + 1; i++) {
        conectionMatrix[i] = new int[countSanctuary + 1];
        stabilityMatrix[i] = new int[countSanctuary + 1];
        for (int j = 0; j < countSanctuary + 1; j++) {
            conectionMatrix[i][j] = 0; 
            stabilityMatrix[i][j] = 0; 
        }
    }

    while(!list_senderos.isEmpty()) {
        int i = list_senderos.pop();
        int j = list_senderos.pop();
        int time = list_senderos.pop();
        int admitedWeight = list_senderos.pop();

        conectionMatrix[i][j] = time;
        conectionMatrix[j][i] = time;
        stabilityMatrix[i][j] = admitedWeight;
        stabilityMatrix[j][i] = admitedWeight;
    }

    Route route;
    Delivery q = list_delivery.pop();
    
    route = Dijkstra(startSanctuary, q.endSantuary, q.weightFragment, totalWeight, countSanctuary, conectionMatrix, stabilityMatrix);
    time = route.time;
    finalRoad = finalRoad + route.roadLog;

    while(!list_delivery.isEmpty()) {
        int startSanctuaryNext = q.endSantuary; 
        
        q = list_delivery.pop(); 
        
        route = Dijkstra(startSanctuaryNext, q.endSantuary, q.weightFragment, totalWeight, countSanctuary, conectionMatrix, stabilityMatrix);
        time += route.time;
        finalRoad = finalRoad + route.roadLog;
    }

    cout << finalRoad << endl;
    cout << time;
}