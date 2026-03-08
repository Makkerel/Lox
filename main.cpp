#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>

void run(std::string &content) {
  std::cout << content << '\n';
  return;
}

void run_file(std::string_view file_path) {
  std::ifstream file(file_path.data());

  if (!file.is_open()) {
    std::cerr << "Problem Opeing File" << '\n';
    return;
  }
  auto file_size = std::filesystem::file_size(file_path.data());
  std::string file_content;
  file_content.resize(file_size);
  file.read(&file_content[0], file_size);
  file.close();

  run(file_content);
}

void run_prompt() {
  std::cout << "> ";
  std::string line;

  while (std::getline(std::cin, line)) {
    std::cout << line << '\n';
    run(line);
    std::cout << "> ";
  }
}

int main(int argc, char **argv) {
  if (argc > 2) {
    std::cerr << "Usage clox [script]" << '\n';
    return 1;
  } else if (argc == 2) {
    run_file(argv[1]);
  } else {
    run_prompt();
  }
  return 0;
}
