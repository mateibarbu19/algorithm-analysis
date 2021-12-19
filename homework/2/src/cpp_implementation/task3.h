#ifndef TASK3_H_
#define TASK3_H_

#include "task.h"
#include "task1.h"
#include "task2.h"
#include <vector>

/*
 * Task3
 * This being an optimization problem, the solve method's logic has to work
 * differently. You have to search for the minimum number of arrests by
 * successively querying the oracle. Hint: it might be easier to reduce the
 * current task to a previously solved task
 */
class Task3 : public Task {
protected:
  std::string task2_in_filename;
  std::string task2_out_filename;
  int n, m, k_min;
  std::vector<std::vector<bool>> adj_matrix;
  std::list<std::pair<int, int>> comp_adj_list;
  std::list<int> vertex_cover;

  void compute_complement_graph();
  bool extract_truth_val_from_task2();

public:
  void solve() override;

  void read_problem_data() override;
  // TODO: read the problem input (in_filename) and store the data in the
  // object's attributes

  void reduce_to_task2(int k);
  // TODO: reduce the current problem to Task2

  void extract_answer_from_task2();
  // TODO: extract the current problem's answer from Task2's answer

  void write_answer() override;
  // TODO: write the answer to the current problem (out_filename)
};

#endif // TASK3_H_
