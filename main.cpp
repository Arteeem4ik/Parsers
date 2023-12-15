#include "earley.h"
#include <iostream>

int main() {
  int num_rules;
  std::cin >> num_rules;
  char from;
  std::string to;
  Earley earley;
  std::string rule;
  while (num_rules--) {
    std::cin >> rule;
    from = rule[0];
    to = rule.substr(3);
    earley.AddRule(from, to);
  }
  std::string word;
  std::cin >> word;
  earley.AddWord(word);
  if (earley.InLanguage()) {
    std::cout << "Yes";
  } else {
    std::cout << "No";
  }
}
