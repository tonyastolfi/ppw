#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

template <typename T> std::string to_string(const T &value) {
  std::ostringstream oss;
  oss << value;
  return oss.str();
}

int main() {
  std::random_device rnd;

  std::vector<std::string> words;
  {
    std::ifstream ifs("/usr/share/dict/words");
    if (!ifs.good()) {
      return 1;
    }
    std::string line;
    while (ifs.good()) {
      std::getline(ifs, line);
      if (line.length() >= 4 && line.length() <= 5) {
        words.emplace_back(line);
      }
    }
  }

  std::vector<std::string> parts;
  std::uniform_int_distribution<int> digit(0, 9);
  std::uniform_int_distribution<char> lower('a', 'z');
  std::uniform_int_distribution<char> upper('A', 'Z');
  std::string symbols = "!@,.<>?~$%^&*-=_+";
  std::uniform_int_distribution<int> symbol(0, symbols.length() - 1);
  std::uniform_int_distribution<std::size_t> word(0, words.size() - 1);

  for (int i = 0; i < 3; ++i) {
    parts.push_back(to_string(digit(rnd)));
    parts.push_back(to_string(lower(rnd)));
    parts.push_back(to_string(upper(rnd)));
    parts.push_back(symbols.substr(symbol(rnd), 1));
    parts.push_back(words[word(rnd)]);
    parts.back()[0] = std::toupper(parts.back()[0]);
  }

  std::shuffle(parts.begin(), parts.end(), rnd);
  for (const auto &part : parts) {
    std::cout << part;
  }
  std::cout << std::endl;

  return 0;
}
