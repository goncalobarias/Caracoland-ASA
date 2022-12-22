#include <algorithm>
#include <iostream>
#include <vector>

typedef unsigned long long ull;

class DisjointedSet {
  public:
    std::vector<ull> _parent, _rank;

    DisjointedSet(ull numV) {
        _parent.resize(numV);
        _rank.resize(numV);
        _makeSet(numV);
    }

    void _makeSet(ull numV) {
        for (ull i = 0; i < numV; i++) {
            _parent.at(i) = i;
            _rank.at(i) = 0;
        }
    }

    ull _findSet(ull x) {
        ull parent = _parent.at(x);
        if (parent != x) {
            parent = _findSet(_parent.at(x));
        }
        return parent;
    }

    void _union(ull x, ull y) { _link(_findSet(x), _findSet(y)); }

    void _link(ull x, ull y) {
        if (_rank.at(x) > _rank.at(y)) {
            _parent.at(y) = x;
        } else {
            _parent.at(x) = y;
            if (_rank.at(x) == _rank.at(y)) {
                _rank.at(y)++;
            }
        }
    }
};

struct Edge {
    ull _vertice1, _vertice2, _weight;

    bool operator<(const Edge &a) const { return _weight > a._weight; }
};

ull kruskalMaximumWeight(int numV, std::vector<Edge> edges) {
    DisjointedSet *disjointedSet = new DisjointedSet(numV);

    std::sort(edges.begin(), edges.end());

    ull maximumTrades = 0;
    for (Edge edge : edges) {
        if (disjointedSet->_findSet(edge._vertice1) !=
            disjointedSet->_findSet(edge._vertice2)) {
            disjointedSet->_union(edge._vertice1, edge._vertice2);
            maximumTrades += edge._weight;
        }
    }

    return maximumTrades;
}

int main() {
    ull numV, numE;
    std::vector<Edge> edges;

    std::cin >> numV >> numE;

    if (numV <= 0 || numE <= 0) {
        std::cout << 0 << "\n";
        return 0;
    }

    ull vertice1, vertice2, weight;
    for (ull i = 0; i < numE; i++) {
        std::cin >> vertice1 >> vertice2 >> weight;
        Edge edge = {._vertice1 = vertice1 - 1,
                     ._vertice2 = vertice2 - 1,
                     ._weight = weight};
        edges.push_back(edge);
    }

    std::cout << kruskalMaximumWeight(numV, edges) << "\n";

    return 0;
}
