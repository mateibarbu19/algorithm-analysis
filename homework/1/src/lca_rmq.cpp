#include "algo.h"
#include <bits/c++config.h>
#include <cstddef>
#include <cstdio>
#include <map>
#include <stack>
#include <type_traits>
#include <utility>
#include <vector>

using namespace std;


static pair<int, int> order_pair(int a, int b) {
  return make_pair(min(a, b), max(a, b));
}

static int my_log2(unsigned int n) {
  static vector<int> lookup(2, 0);
  if (n >= lookup.size()) {
    size_t old = lookup.size(), i;
    lookup.resize(n + 1);
    for(i = old; i <= n; i++) {
	  	lookup[i] = lookup[i >> 1] + 1;
    }
  }
  return lookup[n];
}

static void rmq_sparse_table(vector<vector<int>>& table, const vector<int> &array, const vector<int> &level) {
  size_t i, j;

  table.resize(array.size(), vector<int>(my_log2(array.size()) + 1));
  for (i = 0; i < array.size(); i++) {
    table[i][0] = array[i];
  }

  for (j = 1; (1u << j) <= array.size(); j++) {
    for (i = 0; i + (1 << j) - 1 < array.size(); i++) {
      if(level[table[i][j - 1]] < level[table[i + (1 << (j - 1))][j - 1]]) {
        table[i][j] = table[i][j - 1];
      }
      else {
        table[i][j] = table[i + (1 << (j - 1))][j - 1];
      }
    }
  }
}

static void euler_tour(vector<int> &tour, const vector<vector<int>> &graph,
                       vector<int> &level, vector<int> &first_occurrence) {
  stack<pair<int, int>> st;

  level.resize(graph.size(), 0);
  first_occurrence.resize(graph.size(), 0);
  st.push(make_pair(0, 1));
  level[0] = -1;
  while (!st.empty()) {
    int node = st.top().first;
    int index = st.top().second;
    if (index == 1) {
      first_occurrence[node] = tour.size();
      level[node] = level[graph[node][0]] + 1;
    }

    tour.push_back(node);
    // if we have finished processing this node
    if ((size_t)index == graph[node].size()) {
      st.pop();
    } else {
      // insert a son into the stack to be processed
      st.top().second++;
      st.push(make_pair(graph[node][index], 1));
    }
  }
}

vector<int> lca(const vector<vector<int>> &graph,
                const vector<pair<int, int>> &queries) {
  vector<int> answers(queries.size());
  vector<int> first;
  vector<int> level;
  vector<int> tour;
  vector<vector<int>> table;

  euler_tour(tour, graph, level, first);

  rmq_sparse_table(table, tour, level);

  my_log2(tour.size());

  for (size_t i = 0; i < queries.size(); i++) {
    pair<int, int> occ; // occurrence
    int len, log_len, node, other_pos;

    occ = order_pair(first[queries[i].first], first[queries[i].second]);
    len = occ.second - occ.first + 1;
    log_len = my_log2(len);

	node = table[occ.first][log_len];
	other_pos = occ.second - (1 << log_len) + 1;
    if(level[node] > level[table[other_pos][log_len]]) {
      node = table[other_pos][log_len];
    }
    answers[i] = node;
  }

  return answers;
}
