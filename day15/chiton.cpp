#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cmath>

#define INF 0xf000000
// Will print the path if true
#define DEBUG false

using std::vector;
using std::ifstream;
using std::pair;
using std::string;
using std::array;
using std::priority_queue;


/* Graph representation as adjacency list:
 * int (Node)  ->  List of Pairs (Edges)
 * Each Pair: (weight, Node)
 *
 * Note: Implementation only works if input is a square matrix
 * */

void print_path(const vector<int>& prev, int source, int current) {
    vector<int> path;
    while(current != source) {
        path.push_back(prev[current]);
        current = prev[current];
    }
    std::cout << "Found path to target: " << std::endl;
    for(auto i = path.rbegin(); i != path.rend(); ++i) std::cout << *i << " ";
    std::cout << std::endl;
}

int a_star(const vector<vector<pair<int, int>>>& graph) {
    int size = graph.size();
    int source = 0;
    int target = size - 1;

    int dim = sqrt(size);
    auto manhattan = [=](int a) { return abs((a % dim) - (target % dim)) \
                                 + abs(ceil(a / dim) - ceil(target / dim));};

    priority_queue<pair<int, int>, vector<pair<int, int>>, std::greater<pair<int, int>>> heap;
    vector<int> dist;
    vector<int> prev;
    dist.push_back(source);
    prev.push_back(-1);
    heap.push(std::make_pair(manhattan(source), source));
    for(int i = 1; i<size; i++) { 
        dist.push_back(INF);
        prev.push_back(-1);
        heap.push(std::make_pair(INF, i));
    }

    while(!heap.empty()) {
        pair<int, int> minNode = heap.top();
        heap.pop();
        if (minNode.second == target) {
            if (DEBUG) print_path(prev, source, target);
            return dist[minNode.second];
        }
        for(const auto& neighbor: graph[minNode.second]) {
            int tempDist = dist[minNode.second] + neighbor.first;
            if (dist[neighbor.second] > tempDist) {
                dist[neighbor.second] = tempDist;
                prev[neighbor.second] = minNode.second;
                // Not really efficient, but apparently the standard priority queue does
                // not support decrease key directly and I cba implementing this
                heap.push(std::make_pair(tempDist + manhattan(neighbor.second), neighbor.second));
            }
        }
    }
    return -1;
}

int floyd_warshall(const vector<vector<pair<int, int>>>& graph) {
    int size = graph.size();
    int source = 0;
    int target = size-1;

    int **dist = new int*[size];
    for(auto i = 0; i<size; i++) {
        *(dist+i) = new int[size]();
        std::fill(*(dist+i), *(dist+i)+size, INF);
    }
    for(auto i = 0; i<size; i++) {
        dist[i][i] = 0;
        for(int j = 0; j<graph[i].size(); j++) {
            dist[i][graph[i][j].second] = graph[i][j].first;
        }
    }

    for(int node1 = 0; node1<size; node1++) {
        for(int node2 = 0; node2<size; node2++) {
            for(int node3 = 0; node3<size; node3++) {
                int tempDist = dist[node2][node1] + dist[node1][node3];
                if (tempDist < dist[node2][node3]) dist[node2][node3] = tempDist;
            }
        }
    }

    int result = dist[source][target];
    for(auto i = 0; i<size; i++) delete[] *(dist+i);
    delete[] dist;
    return result;
}


vector<int> bellmann_ford_impl(const vector<vector<pair<int, int>>>& graph, int source) {
    int size = graph.size();
    vector<int> dist;
    vector<int> prev;

    for(int i = 0; i<size; i++) { 
        dist.push_back(INF);
        prev.push_back(-1);
    }
    dist[source] = 0;

    for(int i = 0; i<size; i++) {
        for(int node1 = 0; node1<size; node1++) {
            for(const auto& edge: graph[node1]) {
                int node2 = edge.second;
                int tempDist = dist[node1] + edge.first;
                if (tempDist < dist[node2]) {
                    dist[node2] = tempDist;
                    prev[node2] = node1;
                }
            }
        }
    }

    // Check for negative cycle
    for(int node1 = 0; node1<size; node1++) {
        for(const auto& edge: graph[node1]) {
            int node2 = edge.second;
            int tempDist = dist[node1] + edge.first;
            if (tempDist < dist[node2]) {
                std::cout << "Negative cycle found" << std::endl;
                return dist;
            }
        }
    }

    return dist;
}

int bellmann_ford(const vector<vector<pair<int, int>>>& graph) {
    int target = graph.size() - 1;
    vector<int> dist = bellmann_ford_impl(graph, 0);
    return dist[target];
}

vector<int> djkstra_impl(const vector<vector<pair<int, int>>>& graph, int source) {
    int size = graph.size();
    priority_queue<pair<int, int>, vector<pair<int, int>>, std::greater<pair<int, int>>> heap;
    vector<int> dist;
    vector<int> prev;

    dist.push_back(source);
    prev.push_back(-1);
    heap.push(std::make_pair(0, source));
    for(int i = 1; i<size; i++) { 
        dist.push_back(INF);
        prev.push_back(-1);
        heap.push(std::make_pair(INF, i));
    }

    while(!heap.empty()) {
        pair<int, int> minNode = heap.top();
        heap.pop();
        //if (minNode.second == target) return minNode.first;
        for(const auto& neighbor: graph[minNode.second]) {
            int tempDist = minNode.first + neighbor.first;
            if (dist[neighbor.second] > tempDist) {
                dist[neighbor.second] = tempDist;
                prev[neighbor.second] = minNode.second;
                // Not really efficient, but apparently the standard priority queue does
                // not support decrease key directly and I cba implementing this
                heap.push(std::make_pair(tempDist, neighbor.second));
            }
        }
    }
    if (DEBUG) print_path(prev, source, size-1);
    return dist;
}

int djkstra(const vector<vector<pair<int, int>>>& graph) {
    int target = graph.size() - 1;
    vector<int> dist = djkstra_impl(graph, 0);
    return dist[target];
}

int johnson(const vector<vector<pair<int, int>>>& graph_in) {
    auto graph = graph_in;
    int size = graph.size();
    int source = 0;
    int target = size-1;

    vector<vector<pair<int, int>>> temp = graph;
    vector<pair<int, int>> edges;
    for(int i = 0; i<size; i++) edges.push_back(std::make_pair(0, i));
    temp.push_back(edges);

    vector<int> dist = bellmann_ford_impl(temp, temp.size()-1);
    for(auto i = 0; i<graph.size(); i++) {
        for(auto j = 0; j<graph[i].size(); j++) {
            graph[i][j].first += (dist[i] - dist[graph[i][j].second]);
        }
    }

    int **finalDist = new int*[size];
    for(auto i = 0; i<size; i++) *(finalDist+i) = new int[size]();

    for(auto i = 0; i<size; i++) {
        auto temp = djkstra_impl(graph, i);
        for(int j = 0; j<size; j++) {
            finalDist[i][j] = temp[j] + (dist[graph[i][j].second] - dist[i]);
        }
    }

    int result = finalDist[source][target];
    for(auto i = 0; i<size; i++) delete[] *(finalDist+i);
    delete[] finalDist;
    return result;
}

int main(int argc, char** argv) {
    ifstream file(argv[1]);
    int size = std::stoi(argv[2]);
    int scaledSize = size*5;
    string line;
    vector<vector<pair<int, int>>> graph;
    int input[scaledSize][scaledSize];
    int i = 0;
    while(std::getline(file, line)) {
        for(auto j = 0; j<line.size(); j++) {
            input[i][j] = line[j] - '0';
            for(int k = 1; k<5; k++) {
                int newResult = (input[i][j+size*(k-1)] + 1) % 10;
                input[i][j+size*k] = newResult > 0 ? newResult : 1;
            }
        }
        for(int k = 1; k<5; k++) {
            for(int l = 0; l<i+1; l++) {
                for(int j = 0; j<scaledSize; j++) {
                    int newResult = (input[(k-1)*size+l][j] + 1) % 10;
                    input[k*size+l][j] = newResult > 0 ? newResult : 1;
                }
            }
        }
        i++;
    }
    for(auto i = 0; i<scaledSize; i++) {
        for(auto j = 0; j<scaledSize; j++) {
            vector<pair<int, int>> edges;
            if ( j < scaledSize - 1) edges.push_back({input[i][j+1], i*scaledSize+j+1});
            if ( i < scaledSize - 1) edges.push_back({input[i+1][j], (i+1)*scaledSize+j});
            if ( i > 0) edges.push_back({input[i-1][j], (i-1)*scaledSize+j});
            if ( j > 0) edges.push_back({input[i][j-1], i*scaledSize+j-1});
            graph.push_back(edges);
        }
    }
    //std::cout << djkstra(graph) << std::endl;
    std::cout << a_star(graph) << std::endl;
    //std::cout << johnson(graph) << std::endl;
    //std::cout << bellmann_ford(graph) << std::endl;
    //std::cout << floyd_warshall(graph) << std::endl;
}
