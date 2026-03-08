#include <iostream>
#include <string>
#include <sstream>
#include <queue>
using namespace std;

struct Delivery{
    int endSantuary;
    int weightFragment;
};

struct Route {
    int time = 0;
    string roadLog = "";
};

Route Dijkstra (int init, int end, int load, int &weight, int countSanctuary, int **conectionMatrix, int **stabilityMatrix) {
   
    int* dist = new int[countSanctuary + 1];
    bool* visited = new bool[countSanctuary + 1];
    int* parent = new int[countSanctuary + 1]; 

    for(int i = 1; i <= countSanctuary; i++) {
        dist[i] = INT32_MAX;
        visited[i] = false;
        parent[i] = -1;
    }

    dist[init] = 0;
    int minor = -1;

    while (visited[end] != true) { //Continua mientras el vertice final no esta en nuestro conjunto S de visitados
        int minDist = INT32_MAX;
        
        for (int i = 1; i <= countSanctuary; i++) {
            if(dist[i] < minDist && visited[i] == false) {
                minor = i;
                minDist = dist[i];
            }
        }
        
        if (minDist == INT32_MAX) break;
        
        visited[minor] = true;

        for (int i = 1; i <= countSanctuary; i++) {
            
            if(conectionMatrix[minor][i] == 0) continue;
            
            if(dist[minor] + conectionMatrix[minor][i] < dist[i] && stabilityMatrix[minor][i] >= weight) {
                parent[i] = minor;
                dist[i] = dist[minor] + conectionMatrix[minor][i];
            }       
        }

    }

    string roadTrip = "";
    int current = end;
    if (dist[end] != INT32_MAX) {
        while (current != init) {
            roadTrip = to_string(current) + " " + roadTrip;
            current = parent[current];
        }
    } else {
        dist[end] = -1;
        roadTrip = "";
    }

    Route endPoint;
    endPoint.roadLog = roadTrip;
    endPoint.time = dist[end];
    weight -= load;

    delete[] dist;
    delete[] visited;
    delete[] parent;

    return endPoint;

}

int main () {
    string line;
    queue<Delivery> list_delivery;
    int totalWeight = 0;
    int countSanctuary = 0;
    int startSanctuary;
    bool isCreated = 0;
    int **conectionMatrix;
    int **stabilityMatrix;
    string finalRoad = "";
    int time = 0;

    int maxSanctuary = 0; 
    queue<int> list_senderos; 

    while (getline(cin, line)) {
        stringstream ss(line);
        int number = 0;
        int count = 0;
        queue<int> data_line;

        while (ss >> number) {
            count++;
            data_line.push(number);
        }

        if(count == 2) {
            Delivery delivery;
            int id = data_line.front();
            data_line.pop();
            int weight = data_line.front();
            data_line.pop();
            
            delivery.endSantuary = id;
            delivery.weightFragment = weight;
            totalWeight += weight;
            list_delivery.push(delivery);

            if (id > maxSanctuary) maxSanctuary = id; 
        }

        if(count == 4) {
            int u = data_line.front();
            data_line.pop();
            int v = data_line.front();
            data_line.pop();
            int t = data_line.front();
            data_line.pop();
            int w = data_line.front();
            data_line.pop();

            list_senderos.push(u);
            list_senderos.push(v);
            list_senderos.push(t);
            list_senderos.push(w);

            if (u > maxSanctuary) maxSanctuary = u;
            if (v > maxSanctuary) maxSanctuary = v;
        }

        if(count == 1) {
            startSanctuary = data_line.front();
            data_line.pop();
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

    while(!list_senderos.empty()) {
        int i = list_senderos.front();
        list_senderos.pop();
        int j = list_senderos.front();
        list_senderos.pop();
        int time = list_senderos.front();
        list_senderos.pop();
        int admitedWeight = list_senderos.front();
        list_senderos.pop();

        conectionMatrix[i][j] = time;
        conectionMatrix[j][i] = time;
        stabilityMatrix[i][j] = admitedWeight;
        stabilityMatrix[j][i] = admitedWeight;
    }

    Route route;
    Delivery q = list_delivery.front();
    list_delivery.pop();
    
    route = Dijkstra(startSanctuary, q.endSantuary, q.weightFragment, totalWeight, countSanctuary, conectionMatrix, stabilityMatrix);

    if (route.time == -1) { // Condicion por si el caso es imposible, el tiempo de la ruta dara 0 ya que no pudo completarla
        cout << 0;
        return 1;
    }

    time = route.time;
    finalRoad = finalRoad + route.roadLog;

    while(!list_delivery.empty()) {
        int startSanctuaryNext = q.endSantuary; 
        
        q = list_delivery.front(); 
        list_delivery.pop();

        route = Dijkstra(startSanctuaryNext, q.endSantuary, q.weightFragment, totalWeight, countSanctuary, conectionMatrix, stabilityMatrix);

        if (route.time == -1) { // Condicion por si el caso es imposible, el tiempo de la ruta dara 0 ya que no pudo completarla
            cout << 0;
            return 1;
        }

        time += route.time;
        finalRoad = finalRoad + route.roadLog;
    }

    cout << finalRoad << endl;
    cout << time;
}