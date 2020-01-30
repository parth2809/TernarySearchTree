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
    ASSERT_TRUE(dict.insert("food", 1));
    //   ASSERT_FALSE(dict.insert("food", 1));
    ASSERT_TRUE(dict.find("food"));
    dict.insert("a", 1);
    dict.insert("am", 2);
    dict.insert("momy", 2);
    dict.insert("momys", 3);
    dict.insert("foody", 2);
    ASSERT_TRUE(dict.find("food"));
    ASSERT_TRUE(dict.find("am"));
    ASSERT_FALSE(dict.find("foo"));
    ASSERT_TRUE(dict.find("momy"));
    ASSERT_TRUE(dict.find("momys"));
    ASSERT_TRUE(dict.find("foody"));
    ASSERT_TRUE(dict.find("a"));
    ASSERT_FALSE(dict.find("momyss"));
}
/* TODO */
