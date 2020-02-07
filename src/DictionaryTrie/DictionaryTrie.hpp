/**
 * This is the Dictionary Trie hpp file. It has the classes for a trieNode and
 * DictionaryTrie along with structs for the priority queues.
 * Authors: Parth Shah, Quylan Mac
 * Sources used: CSE100 PA2 write-up, Stepik Textbook
 */

#ifndef DICTIONARY_TRIE_HPP
#define DICTIONARY_TRIE_HPP

#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;

/**
 * This is a Ternary Search Tree Node class called TrieNode, which has a
 * character value (its value), a frequency, and a boolean signifying if it is a
 * end word or not. In addition, it has a pointer to its left child, right
 * child, and the middle child. It also has the following methods: setVal,
 * getVal, setFreq, getFreq, setFinalLetter and getFinalLetter.
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
    /**
     * Default constructor.
     * Initialize an empty TST Node, with its right child, left child, and
     * middle child are null.
     */
    TrieNode() : value('\0'), frequency(0), endWord(false) {
        left = middle = right = nullptr;
    }
    /**
     * Constructor.
     * Initialize an empty TST Node, with its right child, left child, and
     * middle child are null.
     * parameters - c - the character value of the node
     *            - a - the frequency at the node
     *            - b - boolean for whether the node is the end of the word
     */
    TrieNode(const char& c, const int& a, const bool& b)
        : value(c), frequency(a), endWord(b) {
        left = middle = right = nullptr;
    }
    /** Set the value of parameter value
     * Paramater: c - the character to set the node with
     */
    void setVal(const char& c) { value = c; }
    /** returns the value of the parameter value */
    char getVal() { return value; }
    /** Set the value of frequency
     * Paramater: a - the integer to set the frequency of the node with
     */
    void setFreq(const int& a) { frequency = a; }
    /** returns the value of the frequency of the node */
    int getFreq() { return frequency; }
    /** Set the value of the boolean showing whether is it the final letter
     * Paramater: b - the boolean to set the node with to check if the node ends
     * in a word
     */
    void setFinalLetter(const bool& b) { endWord = b; }
    /** returns the boolean value which depends of whether the node is the end
     * of a word*/
    bool getFinalLetter() { return endWord; }
};
/**
 * This is a struct that contains a function compare which compares two pairs,
 * i.e. compares its frequency first and then the alphabetical ordering of its
 * string. It is used to create a max heap
 */
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
/**
 * This is a struct that contains a function compare which compares two pairs,
 * i.e. compares its frequency first and then the alphabetical ordering of its
 * string. It is used to create a min heap
 */
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
// Initialized a pririoty queue to store pairs. Used in PredictCompletions
typedef std::priority_queue<pair<string, int>*, vector<pair<string, int>*>,
                            Tcompare>
    pq;
// Initialized a pririoty queue to store pairs. Used in PredictUnderscores
typedef std::priority_queue<pair<string, int>*, vector<pair<string, int>*>,
                            Compare>
    rpq;

/**
 * This is DictionaryTrie class, which has a root and two queues ( one for a min
 * heap and one for a max heap, since theyre used by predictCompletions and
 * predict Underscore respctively). It also has the
 * following methods: insert, findNode, traversal, find, predictCompletions,
 * predictUnderscores, traverselength, recurse and deleteAll.
 */
class DictionaryTrie {
  private:
    TrieNode* root;
    pq* queue;
    rpq* rqueue;

  public:
    /**
     * Default constructor.
     * Initialize an empty DictionaryTrie
     */
    DictionaryTrie();

    /**
     * insert method.
     * Inserts a new node in the TST.
     * parameters - word - the word to be inserted in the trie (letters inserted
     * as nodes)
     *            - frequency - frequency of the word in the trie
     */
    bool insert(string word, unsigned int freq);
    /**
     * findNode method.
     * returns the pointer to a node that is the last letter of a word.
     * parameters - word - the word that needs to be looked for in the trie
     */
    TrieNode* findNode(string word) const;
    /**
     * traversal method.
     * method that performs a depth first search on the trie. used to fill the
     * priority queue
     *  parameters - node -the node where you begin the traversal
     *             - prefix - the prefix which is used to get all words
     *             - numCompletions - denotes the maximum number of completions
     * that need to be returned
     */
    void traversal(TrieNode* node, string prefix, int numCompletions);

    /**
     * find method.
     * returns a boolean for whether the word exists in the tree
     * parameters - word - the word that needs to be looked for in the trie
     */
    bool find(string word) const;

    /**
     * predictCompletions method.
     * returns a vector with the the number of completions required that have
     * the highest frequency
     * parameters - prefix - the prefix which is used to get all words
     *            - numCompletions - denotes the maximum number of completions
     */
    vector<string> predictCompletions(string prefix,
                                      unsigned int numCompletions);

    /**
     * predictCompletions method.
     * returns a vector with the the number of completions required that have
     * the highest frequency and can be produced from the pattern
     * parameters - pattern - the pattern with underscores that is being
     * searched for
     *            - numCompletions - denotes the maximum number of completions
     */
    vector<string> predictUnderscores(string pattern,
                                      unsigned int numCompletions);

    /**
     * traversalLrngth method.
     * method that performs a depth first search on the trie. used to fill the
     * priority queue with words of a fixed length
     *  parameters - node -the node where you begin the traversal
     *             - word - the prefix which is used to get all words
     *             - length - the length of the words being needed
     */
    void traversalLength(TrieNode* node, string word, int length);

    /**
     * recurse method.
     * method use to check if the word fits with the pattern perfectly
     *  parameters - pattern - the pattern with underscores that is being
     * searched for
     *             - word - the prefix which is used to get all words
     */
    bool recurse(string pattern, string word);

    /**
     * Destructor.
     * Deletes every node in the TST. Uses helper method deleteAll
     */
    ~DictionaryTrie();
    /**
     * A helper method for destructor. Recursively deletes every node in the
     * tree. Deletes nothing if root is nullptr.
     * Paramater: n - a pointer to the root of the tree.
     */
    void deleteAll(TrieNode* n);
};

#endif  // DICTIONARY_TRIE_HPP
