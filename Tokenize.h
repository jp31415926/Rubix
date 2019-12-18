#pragma once

#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> tokenize(const std::string& str, const std::string& delimiters=" \t\n\r") {
  std::vector<std::string> token_v;
  size_t start(str.find_first_not_of(delimiters)), end(start);

  while (start != std::string::npos) {
    // Find next occurence of delimiter
    end = str.find_first_of(delimiters, start);
    // Push back the token found into vector
    token_v.push_back(str.substr(start, end - start));
    // Skip all occurences of the delimiter to find new start
    start = str.find_first_not_of(delimiters, end);
  }
  return token_v;
}

/*
int main() {
  std::string s = "   AAa BBb  CCc\t\tDDd\n\rEEe \n FFf    ";
  std::vector<std::string> tokens(tokenize(s, " \t\n\r"));
  for (const std::string& str : tokens) {
    std::cout << str << std::endl;
  }
  std::cout << "The end" << std::endl;
}

*/
