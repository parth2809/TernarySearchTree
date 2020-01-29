/**
 * TODO: File Header
 *
 * Author:
 */
#ifndef DICTIONARY_TRIE_HPP
#define DICTIONARY_TRIE_HPP

#include <string>
#include <utility>
#include <vector>

using namespace std;

/**
 * The class for a dictionary ADT, implemented as either
 * a mulit-way trie or a ternary search tree.
 */
class DictionaryTrie {
    class TrieNode {
      private:
        int frequency;
        char value;
        bool endWord;

      public:
        TrieNode* left;
        TrieNode* middle;
        TrieNode* right;

        TrieNode(const char& c) : value(c) { left = middle = right = 0; }
        void setVal(const char& c) { value = c; }
        char getVal() { return value; }
        void setFreq(const int& a) { frequency = a; }
        int getFreq() { return frequency; }
        void setFreq(const bool& b) { endWord = b; }
        bool getFreq() { return endWord; }
    };

  private:
    // TODO: add private members and helper methods here
  public:
    /* TODO: add function header */
    DictionaryTrie();

    /* TODO: add function header */
    bool insert(string word, unsigned int freq);

    /* TODO: add function header */
    bool find(string word) const;

    /* TODO: add function header */
    vector<string> predictCompletions(string prefix,
                                      unsigned int numCompletions);

    /* TODO: add function header */
    vector<string> predictUnderscores(string pattern,
                                      unsigned int numCompletions);

    /* TODO: add function header */
    ~DictionaryTrie();
};

#endif  // DICTIONARY_TRIE_HPP
