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
}
/* TODO */
