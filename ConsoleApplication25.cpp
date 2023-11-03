#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>
using namespace std;

vector<vector<int>> generateRandomGraph(int n) {
    vector<vector<int>> graph(n, vector<int>(n, 0));
    srand(time(0));

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int random = rand() % 2;
            graph[i][j] = random;
            graph[j][i] = random;
        }
    }

    return graph;
}

void DFSUsingMatrix(vector<vector<int>>& graph, vector<bool>& visited, int vertex) {
    visited[vertex] = true;
    cout << vertex << " ";

    for (int i = 0; i < graph.size(); i++) {
        if (graph[vertex][i] == 1 && !visited[i]) {
            DFSUsingMatrix(graph, visited, i);
        }
    }
}

void DFSUsingLists(vector<vector<int>>& graph, vector<bool>& visited, int vertex) {
    visited[vertex] = true;
    cout << vertex << " ";

    for (int i = 0; i < graph[vertex].size(); i++) {
        int adjacentVertex = graph[vertex][i];
        if (!visited[adjacentVertex]) {
            DFSUsingLists(graph, visited, adjacentVertex);
        }
    }
}

void nonRecursiveDFSUsingMatrix(vector<vector<int>>& graph, vector<bool>& visited, int startVertex) {
    stack<int> stack;
    stack.push(startVertex);
    visited[startVertex] = true;

    while (!stack.empty()) {
        int currentVertex = stack.top();
        stack.pop();
        cout << currentVertex << " ";

        for (int i = 0; i < graph.size(); i++) {
            if (graph[currentVertex][i] == 1 && !visited[i]) {
                stack.push(i);
                visited[i] = true;
            }
        }
    }
}

void printAdjacencyList(vector<vector<int>>& graph) {
    cout << "Список смежности:" << endl;
    for (int i = 0; i < graph.size(); i++) {
        cout << i << ": ";
        for (int j = 0; j < graph[i].size(); j++) {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    int n;
    cout << "Введите количество вершин: ";
    cin >> n;

    vector<vector<int>> adjacencyMatrix = generateRandomGraph(n);

    cout << "Матрица смежности:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << adjacencyMatrix[i][j] << " ";
        }
        cout << endl;
    }

    vector<bool> visited(n, false);
    cout << "Обход в глубину через матрицу смежности: ";
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            DFSUsingMatrix(adjacencyMatrix, visited, i);
        }
    }
    cout << endl;

    vector<vector<int>> adjacencyList(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adjacencyMatrix[i][j] == 1) {
                adjacencyList[i].push_back(j);
            }
        }
    }

    printAdjacencyList(adjacencyList);

    visited.assign(n, false);
    cout << "Обход в глубину через список смежности: ";
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            DFSUsingLists(adjacencyList, visited, i);
        }
    }
    cout << endl;

    visited.assign(n, false);
    cout << "Нерекурсивный обход в глубину: ";
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            nonRecursiveDFSUsingMatrix(adjacencyMatrix, visited, i);
        }
    }
    cout << endl;

    return 0;
}
