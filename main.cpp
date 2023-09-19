// Description: This function implements Prim's algorithm to find the Minimum Spanning Tree (MST) of a graph.
// Pre-condition: The function requires a graph (in the form of an adjacency list) and the number of vertices in the graph. The graph should be connected and the weights of the edges should be non-negative.
// Post-condition: The function outputs the edges of the MST and their weights to the output file. It also outputs the total cost of the MST. The function does not modify the input graph.
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>
#include <string>
#include <climits>

using namespace std;
//edge struct definintion
struct Edge {
    int src, dest, weight;
};

struct Node {
    int vertex, weight;
};

class Graph {
public:
    vector<vector<Node>> adjList;
//function implementation
    Graph(vector<Edge> &edges, int N) {
        adjList.resize(N);
        for (auto &edge: edges) {
            adjList[edge.src].push_back({edge.dest, edge.weight});
            adjList[edge.dest].push_back({edge.src, edge.weight});
        }
        if (N == 0) {
            cout << "Empty Graph Will Be Created" << endl;
        }
    }

    void printAdjacencyList(ofstream &outputFile) {
        for (int i = 0; i < adjList.size(); ++i) {
            outputFile << "Adj[" << i << "] -> ";
            for (auto &node: adjList[i]) {
                outputFile << "(" << node.vertex << "," << node.weight << ") ";
            }
            outputFile << endl;
        }
    }
};
//primis algorithm def
void PrimsAlgorithm(Graph const &graph, int N, ofstream &outputFile) {
    vector<int> key(N, INT_MAX);
    vector<bool> inMST(N, false);
    vector<int> parent(N, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    key[0] = 0;
    pq.push({0, 0});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        inMST[u] = true;

        for (auto &node: graph.adjList[u]) {
            int v = node.vertex;
            int weight = node.weight;

            if (!inMST[v] && weight < key[v]) {
                parent[v] = u;
                key[v] = weight;
                pq.push({key[v], v});
            }
        }
    }

    int totalCost = 0;
    for (int i = 1; i < N; ++i) {
        outputFile << "Edge: " << parent[i] << " - " << i << " weight: " << key[i] << endl;
        totalCost += key[i];
    }
    outputFile << "Total cost of MST: " << totalCost << endl;
}

int main() {
    cout << "Welcome to the MST Test Program" << endl;

    string inputFileName, outputFileName;
    cout << "Enter the name of the input file: ";
    cin >> inputFileName;
    cout << "Enter the name of the output file: ";
    cin >> outputFileName;

    ifstream inputFile(inputFileName);
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open input file." << endl;
        return 1;
    }

    if (inputFile.peek() == ifstream::traits_type::eof()) {
        cerr << "Error: Input file is empty." << endl;
        return 1;
    }

    ofstream outputFile(outputFileName);
    if (!outputFile.is_open()) {
        cerr << "Error: Could not open output file." << endl;
        return 1;
    }

    outputFile << "Welcome to the MST Test Program" << endl;
    outputFile << "Testing Default Scenario" << endl;
    cout << "Testing Default Scenario" << endl;
    outputFile << "Testing File Data" << endl;
    cout << "Testing File Data" << endl;
    string line;
  //read input file
    getline(inputFile, line);
    stringstream ss(line);
    int N, E;
  
    if (!(ss >> N >> E)) {
        cerr << "Error: Invalid format in input file." << endl;
        return 1;
    }

    vector<Edge> edges;
    for (int i = 0; i < E; ++i) {
        getline(inputFile, line);
        stringstream ss(line);
        int src, dest, weight;
        if (!(ss >> src >> dest >> weight)) {
            outputFile << "Error: Invalid format in input file. Skipping line." << endl;
            continue;
        }
        if (src < 0 || src >= N || dest < 0 || dest >= N || weight <= 0) {
            outputFile << "Error: Invalid edge (" << src << ", " << dest << ", " << weight << "). Skipping." << endl;
            continue;
        }
        edges.push_back({src, dest, weight});
    }
//creating graph in outpuut file
    Graph graph(edges, N);
    outputFile << "Full Graph – Adjacency List:" << endl;
    graph.printAdjacencyList(outputFile);
    outputFile << endl;

    outputFile << "Results for " << inputFileName << ":" << endl;
    PrimsAlgorithm(graph, N, outputFile);
    outputFile << endl;

    inputFile.close();
    outputFile.close();

    cout << "Thank you for running the MST Test Program written by <your name>!" << endl;
    outputFile << "Thank you for running the MST Test Program written by <your name>!" << endl;

    return 0;
}
