// Copyright 2020
// Authors: Radu Nichita, Matei Simtinică

#ifndef TASK_H_
#define TASK_H_

#include <array>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>

class Task {
protected:
  std::string in_filename;
  std::string oracle_in_filename;
  std::string oracle_out_filename;
  std::string out_filename;

public:
  virtual ~Task() = default;

  virtual void solve() = 0;
  virtual void read_problem_data() = 0;
  void formulate_oracle_question(){};
  void decipher_oracle_answer(){};
  virtual void write_answer() = 0;

  /*
   * Stores the files paths as class attributes.
   *
   * @param in_filename:         the file containing the problem input
   * @param oracle_in_filename:  the file containing the oracle input
   * @param oracle_out_filename: the file containing the oracle output
   * @param out_filename:        the file containing the problem output
   */
  void add_files(std::string in, std::string oracle_in, std::string oracle_out,
                 std::string out);

  /*
   * Asks the oracle for an answer to the formulated question.
   */
  void ask_oracle();
};

#endif // TASK_H_
