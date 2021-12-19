#include "algo.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;

void read_data(const char *in_file, vector<vector<int>> &graph,
               vector<pair<int, int>> &queries) {
  unsigned int N, M, i, j, k;

  if (in_file != NULL) {
    if (freopen(in_file, "rt", stdin) == NULL) {
      exit(1);
    }
  }

  scanf("%u%u", &N, &M);
  graph.resize(N, vector<int>(1));

  for (i = 2; i <= N; i++) {
    scanf("%u", &j); // we read the father of node i
    // because we index at 0 we read j-1 is the father of i - 1
    graph[i - 1][0] = j - 1;
    graph[j - 1].push_back(i - 1);
  }

  for (i = 0; i < M; i++) {
    scanf("%u%u", &j, &k);
    queries.push_back(make_pair(j - 1, k - 1));
  }

  fclose(stdin);
}

void print_data(const char *out_file, const vector<int> &answers) {
  unsigned int i;

  if (out_file != NULL) {
    if (freopen(out_file, "wt", stdout) == NULL) {
      exit(2);
    }
  }

  for (i = 0; i < answers.size(); i++) {
    printf("%d\n", answers[i] + 1);
  }

  fclose(stdout);
}

int main(int argc, char *argv[]) {
  vector<vector<int>> graph;
  vector<pair<int, int>> queries;
  vector<int> answers;

  if (argc > 3) {
    perror("Please use maximum two files\n");
    return -1;
  }

  read_data(argv[1], graph, queries);
  answers = lca(graph, queries);
  print_data(argv[2], answers);

  return 0;
}