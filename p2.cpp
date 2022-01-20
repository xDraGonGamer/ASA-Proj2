#include <iostream>
#include <vector>
#include <algorithm>

void printGraph(std::vector<std::vector<int>> &graph, int size);
void computeInput();
std::vector<int> topologicalSort(std::vector<std::vector<int>> &graph, std::vector<bool> &visited);

int main() {
    computeInput();
    return 0;
}

typedef struct Node {
    std::vector<int> parents;
    std::vector<int> children;
} node;

/**
 * @brief 
 *      Computes the input given, processing it for the
 *      actual algorithm
 * 
 *  v1, v2:
 *      Vertice identifiers.
 * 
 *  n_vertices:
 *      Number of vertices of the tree.
 *  n_edges:
 *      Number of edges.
 */
void computeInput() {
    int v1, v2, n_vertices, n_edges;

    if (scanf("%d %d", &v1, &v2) != 2) { // le o v1 e o v2
        std::cout << 0;
        return;
    }

    if (scanf("%d %d", &n_vertices, &n_edges) != 2) { // le o numero de vertices e o n de arcos
        std::cout << 0;
        return;
    }

    int u, v;
    // Graph used to represent the tree (adjacency list)
    std::vector<node> graph(n_vertices);

    for (int i = 0; i < n_edges; i++) {
        if (scanf("%d %d", &u, &v) != 2) {
            std::cout << 0;
            return;   
        }

        // 1 2
        
        // graph[u-1] because the identifiers go from 1 to n_vetices
        graph[u-1].children.push_back(v);
        graph[v-1].parents.push_back(u);
    }

    // Vector used to know if a certain node has been visited or not
    std::vector<bool> visited(n_vertices, false);

    printGraph(graph, n_vertices);

    std::vector<int> sorted_graph = topologicalSort(graph, visited, n_vertices);


}


/**
 * @brief 
 *      Sorts the given graph, topologically
 * 
 * @param graph
 * @return
 *      the sorted graph
 */
std::vector<int> topologicalSort(std::vector<node> &graph, std::vector<bool> &visited, int size) {
    std::vector<int> sorted_graph;

    for(int i = 0; i < size; i++){

        for(int son: graph[i].children){
            if(!visited[son - 1]){
                visited[son - 1] = true;
                sorted_graph.push_back(son);
            }
        }

        if(!visited[i]){ //if the vertice has not been visited
            visited[i] = true;
            sorted_graph.push_back(i + 1);
        }

    }
    std::reverse(sorted_graph.begin(), sorted_graph.end());
    return sorted_graph;
}


void printGraph(std::vector<node> &graph, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << i+1 << " ->";

        for (auto val: graph[i].children)
            std::cout << " " << val;
        
        std::cout << "\n";
    }  
}
