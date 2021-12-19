#include "bonus.h"
#include <fstream>
#include <list>
#include <utility>

using namespace std;

void Bonus::solve() {
  read_problem_data();
  formulate_oracle_question();
  ask_oracle();
  decipher_oracle_answer();
  write_answer();
}

void Bonus::read_problem_data(void) {
  ifstream f_in(in_filename);

  f_in >> n >> m;
  adj_list.clear();
  vertex_cover.clear();
  for (int i = 0; i < m; i++) {
    int u, v;
    f_in >> u >> v;
    adj_list.push_back(make_pair(u - 1, v - 1));
  }

  f_in.close();
}

void Bonus::formulate_oracle_question() {
  ofstream f_oracle_in(oracle_in_filename);

  f_oracle_in << "p wcnf " << n << ' ';
  f_oracle_in << n + m << ' ' << n + 1 << '\n';

  // maximize the number of nodes not covered
  for (int i = 0; i < n; i++) {
    f_oracle_in << "1 " << -(i + 1) << " 0\n";
  }

  // for each edge
  for (auto it = adj_list.begin(); it != adj_list.end(); it++) {
    int i = (*it).first;
    int j = (*it).second;
    // at least one of the nodes should be in the vertex cover
    f_oracle_in << n + 1 << ' ' << i + 1 << ' ' << j + 1 << " 0\n";
  }

  f_oracle_in.close();
}

void Bonus::decipher_oracle_answer() {
  ifstream f_oracle_out(oracle_out_filename);
  int var;

  vertex_cover.clear();
  f_oracle_out >> var >> var;
  for (int i = 0; i < n; i++) {
    f_oracle_out >> var;
    if (var > 0) {
      vertex_cover.push_back(i);
    }
  }

  f_oracle_out.close();
}

void Bonus::write_answer() {
  ofstream f_out(out_filename);

  for (auto it = vertex_cover.begin(); it != vertex_cover.end(); it++) {
    f_out << (*it) + 1 << " ";
  }
  f_out << '\n';

  f_out.close();
}