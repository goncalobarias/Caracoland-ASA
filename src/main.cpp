/*
 *      File: main.cpp
 *      Author: Gonçalo Sampaio Bárias (ist1103124)
 *      Group: al013
 *      Description: Kruskal algorithm in c++ to get the maximum trades in an
 *                   imaginary city.
 */

#include <algorithm>
#include <iostream>
#include <vector>

/**
 * Disjointed set data structure used by the modified Kruskal algorithm to
 * identify if adding an edge will cause any cycles in the tree.
 */
class DisjointedSet {
  private:
    std::vector<int> _parents, _ranks;

  public:
    DisjointedSet(const int numV) { makeSet(numV); }

    void makeSet(const int numV) {
        for (int i = 0; i < numV; i++) {
            _parents.push_back(i);
            _ranks.push_back(0);
        }
    }

    int findSet(const int x) {
        if (_parents.at(x) != x) {
            _parents.at(x) = findSet(_parents.at(x));
        }
        return _parents.at(x);
    }

    void merge(const int x, const int y) { link(findSet(x), findSet(y)); }

    void link(const int x, const int y) {
        if (_ranks.at(x) > _ranks.at(y)) {
            _parents.at(y) = x;
        } else {
            _parents.at(x) = y;
            if (_ranks.at(x) == _ranks.at(y)) {
                _ranks.at(y)++;
            }
        }
    }
};

/**
 * Stores the two vertices the edge is attached to and its corresponding weight.
 */
struct Edge {
    int source, dest, weight;

    bool operator<(const Edge &e) const { return weight > e.weight; }
};

/**
 * Modified Kruskal algorithm that gets the maximum weight of the edges instead
 * of the minimum.
 */
int kruskalMaximumWeight(const int numV, std::vector<Edge> &edges) {
    DisjointedSet *disjointedSet = new DisjointedSet(numV);

    // Sorts the edges by their weight in decreasing order
    std::sort(edges.begin(), edges.end());

    int maxTrades = 0;
    for (Edge edge : edges) {
        if (disjointedSet->findSet(edge.source) !=
            disjointedSet->findSet(edge.dest)) {
            disjointedSet->merge(edge.source, edge.dest);
            maxTrades += edge.weight;
        }
    }

    delete disjointedSet;
    return maxTrades;
}

int main() {
    int numV, numE; // numV = number of vertices and numE = number of edges
    std::vector<Edge> edges; // contains all the graph edges

    scanf("%d %d", &numV, &numE);

    // When we have 1 vertice, or 0 edges, or invalid input the maximum trade
    // value is always 0
    if (numV <= 1 || numE <= 0) {
        printf("0\n");
        return 0;
    }

    // Reads the edge information and stores it all
    int v, u, w;
    for (int i = 0; i < numE; i++) {
        scanf("%d %d %d", &v, &u, &w);
        if (v <= 0 || v > numV || u <= 0 || u > numV) {
            printf("ERROR: vertice identifier is incorrect\n");
            return 0;
        }
        Edge edge = {.source = v - 1, .dest = u - 1, .weight = w};
        edges.push_back(edge);
    }

    printf("%d\n", kruskalMaximumWeight(numV, edges));
    return 0;
}
