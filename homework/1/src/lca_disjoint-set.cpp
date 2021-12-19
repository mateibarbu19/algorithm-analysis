#include "algo.h"
#include <cstddef>
#include <cstdio>
#include <map>
#include <stack>
#include <type_traits>
#include <utility>
#include <vector>

using namespace std;

class dijoint_set {
private:
  int size;
  vector<int> parent;
  vector<int> rank;

public:
  explicit dijoint_set(size_t capacity) {
    size = capacity;
    parent.resize(size, -1);
    rank.resize(size);
  }

  void make_set(int node) {
    parent[node] = node;
    rank[node] = 1;
  }

  int find(int node) {
    int root = node;
    while (root != parent[root]) {
      root = parent[root];
    }

    while (node != root) {
      int aux = parent[node];
      parent[node] = root;
      node = aux;
    }

    return root;
  }

  void union_set(int x, int y) {
    int dadx = find(x), dady = find(y);
    if (dadx == dady) {
      return;
    }

    if (rank[dadx] > rank[dady]) {
      parent[dady] = dadx;
    } else {
      parent[dadx] = dady;
    }

    if (rank[dadx] == rank[dady]) {
      rank[dady]++;
    }
  }

  void set_ancestors(int node, int ancestor) {
    int root = find(node);
    parent[root] = ancestor;
    parent[ancestor] = ancestor;
    if (rank[root] > rank[ancestor]) {
      rank[ancestor] = rank[root] + 1;
    }
  }
};

static pair<int, int> order_pair(pair<int, int> p) {
  return make_pair(min(p.first, p.second), max(p.first, p.second));
}

vector<int> lca(const vector<vector<int>> &graph,
                const vector<pair<int, int>> &queries) {
  vector<vector<int>> questions(graph.size());
  pair<int, int> query_pair;
  vector<int> answers(queries.size());
  stack<pair<int, int>> st;
  vector<bool> visited(graph.size(), false);

  size_t i;

  dijoint_set forest(graph.size());
  for (i = 0; i < graph.size(); i++) {
    forest.make_set(i);
  }

  for (i = 0; i < queries.size(); i++) {
    questions[queries[i].first].push_back(i);
    questions[queries[i].second].push_back(i);
  }

  st.push(make_pair(0, 1));
  while (!st.empty()) {
    int node = st.top().first;
    int index = st.top().second;

    // if node has no more unprocessed sons
    if ((size_t)index == graph[node].size()) {
      visited[node] = true;

      // iterate through the list of questions
      for (const int &pos : questions[node]) {
        query_pair = order_pair(queries[pos]);
        int other = (node == query_pair.first) ? query_pair.second : query_pair.first;

        // if we have note processed any answers for this query
        if (visited[other]) {
          answers[pos] = forest.find(other);
        }
      }

      // unite node with his father
      forest.union_set(node, graph[node][0]);
      // set the ancestor of node's dijoint set to be the node's parent
      forest.set_ancestors(node, graph[node][0]);

      // finished processing node
      st.pop();
    } else {
      // apply the recursive algorithm on the first son
      st.top().second++;
      st.push(make_pair(graph[node][index], 1));
    }
  }

  return answers;
}
