#include "earley.h"

Earley::Earley() {
  configurations_.resize(1);
  configurations_[0].insert(Configuration{Rule{start_, std::string{'S'}}, 0, 0});
}

bool Earley::InLanguage() {
  for (int i = 0; i <= word_.size(); ++i) {
    Scan(i);
    size_t prev_size;
    do {
      prev_size = configurations_[i].size();
      Complete(i);
      Predict(i);
    } while (prev_size != configurations_[i].size());
  }
  return configurations_[word_.length()].count(Configuration{Rule{start_, std::string{'S'}}, 1, 0});
}

void Earley::AddRule(char from, const std::string& to) {
  grammar_.insert({from, to});
}

void Earley::AddWord(const std::string& word) {
  word_ = word;
  configurations_.resize(word.size() + 1);
}

void Earley::Scan(int idx) {
  if (idx == 0) {
    return;
  }
  for (auto& conf : configurations_[idx - 1]) {
    if (conf.IsSymbolAfterDot() && conf.SymbolAfterDot() == word_[idx - 1]) {
      configurations_[idx].insert(conf.ShiftDot());
    }
  }
}

void Earley::Complete(int idx) {
  for (auto& conf : configurations_[idx]) {
    if (conf.IsSymbolAfterDot()) {
      continue;
    }
    for (auto& index_conf : configurations_[conf.index]) {
      if (index_conf.IsSymbolAfterDot() && index_conf.SymbolAfterDot() == conf.rule.from) {
        configurations_[idx].insert(index_conf.ShiftDot());
      }
    }
  }
}

void Earley::Predict(int index) {
  for (auto& conf : configurations_[index]) {
    if (!conf.IsSymbolAfterDot()) {
      continue;
    }
    for (auto& rule : grammar_) {
      if (rule.from == conf.SymbolAfterDot()) {
        configurations_[index].insert(Configuration{rule, 0, index});
      }
    }
  }
}

bool operator<(const Rule& lhs, const Rule& rhs) {
  return std::make_pair(lhs.from, lhs.to) < std::make_pair(rhs.from, rhs.to);
}

bool operator<(const Configuration& lhs, const Configuration& rhs) {
  return std::tuple<Rule, int, int>(lhs.rule, lhs.dot_position, lhs.index)
  < std::tuple<Rule, int, int>(rhs.rule, rhs.dot_position, rhs.index);
}

bool Configuration::IsSymbolAfterDot() const {
  return dot_position < rule.to.length();
}

char Configuration::SymbolAfterDot() const {
  return rule.to[dot_position];
}

Configuration Configuration::ShiftDot() const {
  Configuration conf = *this;
  conf.dot_position += 1;
  return conf;
}

