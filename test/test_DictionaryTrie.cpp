/**
 * TODO: File HEADER
 *
 * Author:
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "DictionaryTrie.hpp"
#include "util.hpp"

using namespace std;
using namespace testing;

/* Empty test */
TEST(DictTrieTests, EMPTY_TEST) {
    DictionaryTrie dict;
    ASSERT_EQ(dict.find("abrakadabra"), false);
}
TEST(DictTrieTests, TEST_1) {
    DictionaryTrie dict;
    ASSERT_TRUE(dict.insert("food", 10));
    // ASSERT_FALSE(dict.insert("food", 1));
    ASSERT_TRUE(dict.find("food"));
    dict.insert("a", 10);
    dict.insert("am", 8);
    dict.insert("momy", 6);
    dict.insert("momys", 8);
    dict.insert("foody", 8);
    dict.insert("foob", 10);
    dict.insert("foobs", 1000);
    dict.insert("foooo", 20);
    dict.insert("fart", 103);
    dict.insert("asdfop", 100);
    vector<string> result = dict.predictCompletions("foo", 2);
    ASSERT_TRUE(dict.find("food"));
    ASSERT_TRUE(dict.find("am"));
    ASSERT_FALSE(dict.find("foo"));
    ASSERT_TRUE(dict.find("momy"));
    ASSERT_TRUE(dict.find("momys"));
    ASSERT_TRUE(dict.find("foody"));
    ASSERT_TRUE(dict.find("a"));
    ASSERT_FALSE(dict.find("momyss"));

    vector<string> result2 = dict.predictCompletions("foo", 5);
    vector<string> result0 = dict.predictCompletions("a", 5);
    vector<string> resultt = dict.predictCompletions("foob", 5);

    vector<string> result20 = dict.predictCompletions("momy", 5);

    vector<string> result3 = dict.predictUnderscores("f__", 5);
    vector<string> result4 = dict.predictUnderscores("____", 10);
    vector<string> result5 = dict.predictUnderscores("foo", 5);
    vector<string> result6 = dict.predictUnderscores("m___", 0);
    vector<string> result7 = dict.predictUnderscores("m___", 3);
    vector<string> result10 = dict.predictUnderscores("f__", 1);

    vector<string> result8 = dict.predictUnderscores("m___", 10);
}
/* TODO */
