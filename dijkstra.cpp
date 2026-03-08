#include <iostream>
using namespace std;
// CODIGO UNICAMENTE CON EL DIJKSTRA

void dijkstra (int init, int end, int load, int &weight, int countSanctuary, int **conectionMatrix, int **stabilityMatrix) {

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
    while (current != init) {
        roadTrip += " " + parent[current] + current;
        current = parent[current];
    }

}