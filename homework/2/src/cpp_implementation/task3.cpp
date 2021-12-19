#include "task3.h"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

static unsigned int log_2(unsigned int n) {
  unsigned int lg;
  for (lg = 1; lg <= n; lg <<= 1)
    ;
  lg >>= 1;
  return lg;
}

void Task3::compute_complement_graph() {
  comp_adj_list.clear();
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      if (adj_matrix[i][j] == false) {
        comp_adj_list.push_back(make_pair(i, j));
      }
    }
  }
}

void Task3::solve() {
  task2_in_filename = in_filename + "_t2";
  task2_out_filename = out_filename + "_t2";
  Task2 task2_solver = Task2();
  task2_solver.add_files(task2_in_filename, oracle_in_filename,
                         oracle_out_filename, task2_out_filename);
  read_problem_data();
  compute_complement_graph();

  k_min = n;
  for (int lg = log_2(n); lg > 0; lg >>= 1) {
    reduce_to_task2(k_min - lg);
    task2_solver.solve();
    if (extract_truth_val_from_task2()) {
      k_min -= lg;
    }
  }

  reduce_to_task2(k_min);
  task2_solver.solve();
  extract_answer_from_task2();
  write_answer();
}

void Task3::read_problem_data() {
  ifstream f_in(in_filename);
  f_in >> n >> m;
  adj_matrix.resize(n, vector<bool>(n, false));
  comp_adj_list.clear();

  for (int i = 0; i < m; i++) {
    int u, v;
    f_in >> u >> v;
    adj_matrix[u - 1][v - 1] = true;
    adj_matrix[v - 1][u - 1] = true;
  }
  f_in.close();
}

void Task3::reduce_to_task2(int k) {
  ofstream f_task2_in(task2_in_filename);
  f_task2_in << n << ' ' << n * (n - 1) / 2 - m << ' ' << n - k << '\n';
  for (auto it = comp_adj_list.begin(); it != comp_adj_list.end(); it++) {
    f_task2_in << (*it).first + 1 << ' ' << (*it).second + 1 << '\n';
  }
  f_task2_in.close();
}

bool Task3::extract_truth_val_from_task2() {
  ifstream f_task2_out(task2_out_filename);
  string is_sat;
  getline(f_task2_out, is_sat);
  return is_sat == "True";
}

void Task3::extract_answer_from_task2() {
  ifstream f_task2_out(task2_out_filename);
  string is_sat;

  getline(f_task2_out, is_sat);
  if (is_sat == "True") {
    vector<bool> appearence(n, false);
    int node;

    while (f_task2_out >> node) {
      appearence[node - 1] = true;
    }

    for (node = 0; node < n; node++) {
      if (!appearence[node]) {
        vertex_cover.push_back(node);
      }
    }
  }
}

void Task3::write_answer() {
  ofstream f_out(out_filename);
  for (auto it = vertex_cover.begin(); it != vertex_cover.end(); it++) {
    f_out << (*it) + 1 << " ";
  }
  f_out << '\n';
  f_out.close();
}
