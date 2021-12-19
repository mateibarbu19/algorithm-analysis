#include "task2.h"
#include <fstream>
#include <list>
#include <vector>

using namespace std;

void Task2::solve() {
  read_problem_data();
  formulate_oracle_question();
  ask_oracle();
  decipher_oracle_answer();
  write_answer();
}

void Task2::read_problem_data() {
  ifstream f_in(in_filename);

  f_in >> n >> m >> k;
  adj_matrix.resize(n, vector<bool>(n, false));
  clique.clear();

  for (int i = 0; i < m; i++) {
    int u, v;
    f_in >> u >> v;
    adj_matrix[u - 1][v - 1] = true;
    adj_matrix[v - 1][u - 1] = true;
  }

  f_in.close();
}

void Task2::formulate_oracle_question() {
  int i, j, t, u;
  int nr_clauses;
  ofstream f_oracle_in(oracle_in_filename);

  nr_clauses = k * (1 + n * (n - 1) / 2);
  nr_clauses += (n * (n - 1) / 2 - m) * k * (k - 1);
  f_oracle_in << "p cnf " << k * n << ' ' << nr_clauses;
  f_oracle_in << '\n';

  // for each node of the clique
  for (j = 0; j < k; j++) {
    // the node belongs to the original graph
    for (i = 0; i < n; i++) {
      f_oracle_in << n * j + i + 1 << ' ';
    }
    f_oracle_in << "0\n";

    // and that node is unique
    for (i = 0; i < n - 1; i++) {
      for (t = i + 1; t < n; t++) {
        f_oracle_in << -(n * j + i + 1) << ' ' << -(n * j + t + 1) << " 0\n";
      }
    }
  }

  // for each node
  for (i = 0; i < n; i++) {
    // cannot appear twice in the clique
    for (j = 0; j < k - 1; j++) {
      for (t = j + 1; t < k; t++) {
        f_oracle_in << -(n * j + i + 1) << ' ' << -(n * t + i + 1) << " 0\n";
      }
    }
  }
  // this prevents generting cliques of size less than k

  for (i = 0; i < n - 1; i++) {
    for (j = i + 1; j < n; j++) {
      // for each non-edge
      if (adj_matrix[i][j] == false) {
        // both of the nodes cannot belong to the clique
        for (t = 0; t < k - 1; t++) {
          for (u = t + 1; u < k; u++) {
            f_oracle_in << -(n * t + i + 1) << ' ' << -(n * u + j + 1)
                        << " 0\n";
            f_oracle_in << -(n * u + i + 1) << ' ' << -(n * t + j + 1)
                        << " 0\n";
          }
        }
      }
    }
  }

  f_oracle_in.close();
}

void Task2::decipher_oracle_answer() {
  ifstream f_oracle_out(oracle_out_filename);
  string is_sat;

  clique.clear();
  getline(f_oracle_out, is_sat);
  if (is_sat == "True") {
    int var;
    f_oracle_out >> var;

    for (int j = 0; j < k; j++) {
      for (int i = 0; i < n; i++) {
        f_oracle_out >> var;
        if (var > 0) {
          clique.push_back(i); // -var
        }
      }
    }
  }

  f_oracle_out.close();
}

void Task2::write_answer() {
  ofstream f_out(out_filename);

  if (!clique.empty()) {
    f_out << "True" << '\n';
    for (auto it = clique.begin(); it != clique.end(); it++) {
      f_out << (*it) + 1 << " ";
    }
  } else {
    f_out << "False";
  }
  f_out << '\n';

  f_out.close();
}