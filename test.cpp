#include <gtest/gtest.h>
#include "earley.h"

TEST(test_earley, bbs) {
  Earley earley;
  earley.AddRule('S', "");
  earley.AddRule('S', "(S)S");
  earley.AddWord("");
  EXPECT_TRUE(earley.InLanguage());
  earley.AddWord("()");
  EXPECT_TRUE(earley.InLanguage());
  earley.AddWord("(())()");
  EXPECT_TRUE(earley.InLanguage());
  earley.AddWord("(()())((()))");
  EXPECT_TRUE(earley.InLanguage());
  earley.AddWord(")(");
  EXPECT_FALSE(earley.InLanguage());
  earley.AddWord("()(()");
  EXPECT_FALSE(earley.InLanguage());
}

TEST(test_earley, anbn) {
  std::set<Rule> grammar = {
      Rule{'S', ""},
      Rule{'S', "aSb"}
  };
  Earley earley;
  earley.AddRule('S', "");
  earley.AddRule('S', "aSb");
  earley.AddWord("");
  EXPECT_TRUE(earley.InLanguage());
  earley.AddWord("ab");
  EXPECT_TRUE(earley.InLanguage());
  earley.AddWord("aab");
  EXPECT_FALSE(earley.InLanguage());
  earley.AddWord("aaaaabbbbb");
  EXPECT_TRUE(earley.InLanguage());
  earley.AddWord("ba");
  EXPECT_FALSE(earley.InLanguage());
  earley.AddWord("a");
  EXPECT_FALSE(earley.InLanguage());
  earley.AddWord("aabb");
  EXPECT_TRUE(earley.InLanguage());
}