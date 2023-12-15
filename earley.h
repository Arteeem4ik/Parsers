#ifndef PARSERS__EARLEY_H_
#define PARSERS__EARLEY_H_

#include <string>
#include <set>
#include <vector>
#include <tuple>

struct Rule {
  char from;
  std::string to;
};

bool operator<(const Rule&, const Rule&);

struct Configuration {
  Rule rule;
  int dot_position = 0;
  int index = 0;
  bool IsSymbolAfterDot() const;
  char SymbolAfterDot() const;
  Configuration ShiftDot() const;
};

bool operator<(const Configuration&, const Configuration&);

class Earley {
 public:
  Earley();
  bool InLanguage();
  void AddRule(char, const std::string&);
  void AddWord(const std::string&);

 private:
  std::string word_;
  std::set<Rule> grammar_;
  std::vector<std::set<Configuration>> configurations_;
  const char start_ = '\0';

  void Scan(int);
  void Predict(int);
  void Complete(int);
};

#endif //PARSERS__EARLEY_H_
