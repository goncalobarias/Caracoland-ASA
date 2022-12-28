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

typedef long long ll;

/**
 * Disjointed set data structure used by the modified Kruskal algorithm to
 * identify if adding an edge will cause any cycles in the tree.
 */
class DisjointedSet {
  private:
    std::vector<ll> _parents, _ranks;

  public:
    DisjointedSet(const ll numV) {
        _parents.resize(numV);
        _ranks.resize(numV);
        makeSet(numV);
    }

    void makeSet(const ll numV) {
        for (ll i = 0; i < numV; i++) {
            _parents.at(i) = i;
            _ranks.at(i) = 0;
        }
    }

    ll findSet(const ll x) {
        if (_parents.at(x) != x) {
            _parents.at(x) = findSet(_parents.at(x));
        }
        return _parents.at(x);
    }

    void merge(const ll x, const ll y) { link(findSet(x), findSet(y)); }

    void link(const ll x, const ll y) {
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
    ll vertice1, vertice2, weight;

    bool operator<(const Edge &e) const { return weight > e.weight; }
};

/**
 * Modified Kruskal algorithm that gets the maximum weight of the edges instead
 * of the minimum.
 */
ll kruskalMaximumWeight(const ll numV, std::vector<Edge> *edges) {
    DisjointedSet *disjointedSet = new DisjointedSet(numV);

    // Sorts the edges by their weight in decreasing order
    std::sort(edges->begin(), edges->end());

    ll maximumTrades = 0;
    for (auto edge = edges->begin(); edge != edges->end(); ++edge) {
        if (disjointedSet->findSet(edge->vertice1) !=
            disjointedSet->findSet(edge->vertice2)) {
            disjointedSet->merge(edge->vertice1, edge->vertice2);
            maximumTrades += edge->weight;
        }
    }

    delete disjointedSet;
    return maximumTrades;
}

int main() {
    ll numV, numE; // numV = number of vertices and numE = number of edges
    std::vector<Edge> edges; // contains all the graph edges

    std::cin >> numV >> numE;

    // When we have 1 vertice, or 0 edges, or invalid input the maximum trade
    // value is always 0
    if (numV <= 1 || numE <= 0) {
        std::cout << 0 << "\n";
        return 0;
    }

    // Reads the edge information and stores it all
    ll v, u, w;
    for (ll i = 0; i < numE; i++) {
        std::cin >> v >> u >> w;
        if (v <= 0 || v > numV || u <= 0 || u > numV) {
            std::cout << "ERROR: vertice identifier is incorrect\n";
            return 1;
        }
        Edge edge = {.vertice1 = v - 1, .vertice2 = u - 1, .weight = w};
        edges.push_back(edge);
    }

    std::cout << kruskalMaximumWeight(numV, &edges) << "\n";

    return 0;
}
