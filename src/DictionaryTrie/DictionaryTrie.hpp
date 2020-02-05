/**
 * TODO: File Header
 *
 * Author:
 */
#ifndef DICTIONARY_TRIE_HPP
#define DICTIONARY_TRIE_HPP

#include <queue>
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

struct Tcompare {
    bool operator()(pair<string, int>* w1, pair<string, int>* w2) const {
        // Frequencies not equal
        if (w1->second != w2->second) {
            // Checks if first frequency is greater
            return w1->second > w2->second;
        }
        // Checks if first string is greater
        return w1->first < w2->first;
    }
};
struct Compare {
    bool operator()(pair<string, int>* w1, pair<string, int>* w2) const {
        // Frequencies not equal
        if (w1->second != w2->second) {
            // Checks if first frequency is greater
            return w1->second < w2->second;
        }
        // Checks if first string is greater
        return w1->first > w2->first;
    }
};
typedef std::priority_queue<pair<string, int>*, vector<pair<string, int>*>,
                            Tcompare>
    pq;
typedef std::priority_queue<pair<string, int>*, vector<pair<string, int>*>,
                            Compare>
    rpq;
class DictionaryTrie {
  private:
    TrieNode* root;
    int treeHeight;
    int treeSize;
    pq* queue;
    rpq* rqueue;

  public:
    /* TODO: add function header */
    DictionaryTrie();

    /* TODO: add function header */
    bool insert(string word, unsigned int freq);

    TrieNode* findNode(string word) const;

    void traversal(TrieNode* node, string prefix, int numCompletions);

    /* TODO: add function header */
    bool find(string word) const;

    /* TODO: add function header */
    vector<string> predictCompletions(string prefix,
                                      unsigned int numCompletions);

    /* TODO: add function header */
    vector<string> predictUnderscores(string pattern,
                                      unsigned int numCompletions);
    void traversalLength(TrieNode* node, string word, int length);
    bool recurse(string pattern, string word);
    /* TODO: add function header */
    ~DictionaryTrie();

    void deleteAll(TrieNode* n);
};

#endif  // DICTIONARY_TRIE_HPP
