#ifndef BONUS_H_
#define BONUS_H_

#include "task.h"
#include <list>

/*
 * Bonus Task
 * You have to implement 4 methods:
 * read_problem_data         - read the problem input and store it however you
 * see fit formulate_oracle_question - transform the current problem instance
 * into a SAT instance and write the oracle input decipher_oracle_answer    -
 * transform the SAT answer back to the current problem's answer write_answer -
 * write the current problem's answer
 */
class Bonus : public Task {
protected:
  int n, m;
  std::list<std::pair<int, int>> adj_list;
  std::list<int> vertex_cover;

public:
  void solve() override;

  void read_problem_data() override;
  // TODO: read the problem input (in_filename) and store the data in the
  // object's attributes

  void formulate_oracle_question();
  // TODO: transform the current problem into a SAT problem and write it
  // (oracle_in_filename) in a format
  //  understood by the oracle

  void decipher_oracle_answer();
  // TODO: extract the current problem's answer from the answer given by the
  // oracle (oracle_out_filename)

  void write_answer() override;
  // TODO: write the answer to the current problem (out_filename)
};

#endif // BONUS_H_
