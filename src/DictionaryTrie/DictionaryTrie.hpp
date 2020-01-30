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
class TrieNode {
  private:
    int frequency;
    char value;
    bool endWord;

  public:
    TrieNode* left;
    TrieNode* middle;
    TrieNode* right;

    TrieNode() : value('\0'), frequency(0), endWord(false) {
        left = middle = right = nullptr;
    }

    TrieNode(const char& c, const int& a, const bool& b)
        : value(c), frequency(a), endWord(b) {
        left = middle = right = nullptr;
    }
    void setVal(const char& c) { value = c; }
    char getVal() { return value; }
    void setFreq(const int& a) { frequency = a; }
    int getFreq() { return frequency; }
    void setFinalLetter(const bool& b) { endWord = b; }
    bool getFinalLetter() { return endWord; }
};

class DictionaryTrie {
  private:
    TrieNode* root;
    int treeHeight;
    int treeSize;

  public:
    /* TODO: add function header */
    DictionaryTrie();

    char nextCharacter(string word, int position);

    /* TODO: add function header */
    bool insert(string word, unsigned int freq);

    TrieNode* insert(TrieNode* node, char c, unsigned int freq);

    TrieNode* insertChar(TrieNode* node, string word, unsigned int freq);

    TrieNode* insertLetterNode(TrieNode* node, char c, unsigned int freq,
                               int position, string word);

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
