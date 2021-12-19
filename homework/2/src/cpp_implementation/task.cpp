#include "task.h"

void Task::add_files(std::string in, std::string oracle_in,
                     std::string oracle_out, std::string out) {
  in_filename = std::move(in);
  oracle_in_filename = std::move(oracle_in);
  oracle_out_filename = std::move(oracle_out);
  out_filename = std::move(out);
}

void Task::ask_oracle() {
  auto command =
      "python3 sat_oracle.py " + oracle_in_filename + " " + oracle_out_filename;
  std::array<char, 512> buffer{};
  std::string output;

  auto pipe = popen(command.c_str(), "r");

  while (!feof(pipe)) {
    if (fgets(buffer.data(), 512, pipe) != nullptr) {
      output += buffer.data();
    }
  }

  auto rc = pclose(pipe);

  if (rc != EXIT_SUCCESS) {
    std::cerr << "Error encountered while running oracle" << std::endl;
    std::cerr << output << std::endl;
    exit(-1);
  }
}