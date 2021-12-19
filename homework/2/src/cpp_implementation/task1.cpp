#include "task1.h"
#include <fstream>
#include <utility>
#include <vector>

using namespace std;

void Task1::solve() {
  read_problem_data();
  formulate_oracle_question();
  ask_oracle();
  decipher_oracle_answer();
  write_answer();
}

void Task1::read_problem_data(void) {
  ifstream f_in(in_filename);

  f_in >> n >> m >> k;
  adj_list.clear();
  colors.clear();
  for (int i = 0; i < m; i++) {
    int u, v;
    f_in >> u >> v;
    adj_list.push_back(make_pair(u - 1, v - 1));
  }

  f_in.close();
}

void Task1::formulate_oracle_question() {
  int i, j, t;
  ofstream f_oracle_in(oracle_in_filename);

  f_oracle_in << "p cnf " << n * k << ' ';
  f_oracle_in << n * (1 + k * (k - 1) / 2) + k * m;
  f_oracle_in << '\n';

  // for each node
  for (i = 0; i < n; i++) {
    // every node has assigned a color
    for (j = 0; j < k; j++) {
      f_oracle_in << k * i + j + 1 << ' ';
    }
    f_oracle_in << "0\n";

    // and that color is unique
    for (j = 0; j < k - 1; j++) {
      for (t = j + 1; t < k; t++) {
        f_oracle_in << -(k * i + j + 1) << ' ' << -(k * i + t + 1) << " 0\n";
      }
    }
  }

  // for each edge
  for (auto it = adj_list.begin(); it != adj_list.end(); it++) {
    i = (*it).first;
    j = (*it).second;
    // the nodes have different colors
    for (t = 0; t < k; t++) {
      f_oracle_in << -(k * i + t + 1) << ' ' << -(k * j + t + 1) << " 0\n";
    }
  }

  f_oracle_in.close();
}

void Task1::decipher_oracle_answer() {
  ifstream f_oracle_out(oracle_out_filename);
  string is_sat;

  colors.clear();
  getline(f_oracle_out, is_sat);
  if (is_sat == "True") {
    int var;
    f_oracle_out >> var;

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < k; j++) {
        f_oracle_out >> var;
        if (var > 0) {
          colors.push_back(j);
        }
      }
    }
  }

  f_oracle_out.close();
}

void Task1::write_answer() {
  ofstream f_out(out_filename);

  if (!colors.empty()) {
    f_out << "True" << '\n';
    for (auto it = colors.begin(); it != colors.end(); it++) {
      f_out << (*it) + 1 << ' ';
    }
  } else {
    f_out << "False";
  }
  f_out << '\n';

  f_out.close();
}