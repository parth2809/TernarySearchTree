/**
 * This is the Dictionary Trie cpp file. It has the implementation for all the
 * methods for the dictionary trie class in the hpp file.
 * Authors: Parth Shah,Quylan Mac
 * Sources used: CSE100 PA2 write-up, Stepik Textbook
 */
#include "DictionaryTrie.hpp"
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
using namespace std;
// Initialized a pririoty queue to store pairs. Used in PredictCompletions
typedef std::priority_queue<pair<string, int>*, vector<pair<string, int>*>,
                            Tcompare>
    pq;
// Initialized a pririoty queue to store pairs. Used in PredictUnderscores
typedef std::priority_queue<pair<string, int>*, vector<pair<string, int>*>,
                            Compare>
    rpq;

/**
 * Default constructor.
 * Initialize an empty DictionaryTrie where the root is a null ptr.
 * Initialized the queues for the min and max heap
 */
DictionaryTrie::DictionaryTrie() : root(nullptr) {
    queue = new pq();
    rqueue = new rpq();
}

/**
 * insert method.
 * Inserts a new node in the TST.
 * parameters - word - the word to be inserted in the trie (letters inserted
 * as nodes)
 *            - frequency - frequency of the word in the trie
 */
bool DictionaryTrie::insert(string word, unsigned int freq) {
    // initialize variable position to get char from word
    int position = 0;
    // checks if the root is null to create the root
    if (root == nullptr) {
        root = new TrieNode(word[position], freq, false);
    }
    // get char from word using position
    char c = word[position];
    // stores the root in a temporary pointer variable called node
    TrieNode* node = root;

    while (true) {
        //// checks if char is less then the node's value to traverse right
        if (c < node->getVal()) {
            // checks if the left child is not a null pointer to traverse left
            if (node->left != nullptr) {
                // set node to its left child
                node = node->left;
            } else {
                // if the left child is a null ptr then create a node over there
                node->left = new TrieNode(c, freq, false);
                // set node to its left child
                node = node->left;
                // for loop to traverse to the middle child of the nodes
                // in order to store a new word in the TST
                for (int i = position + 1; i < word.length(); i++) {
                    // creates new node as the middle child of node
                    node->middle = new TrieNode(word[i], freq, false);
                    // sets node to its midddle child
                    node = node->middle;
                }
                // at the end of the word sets the boolean of end word to true
                node->setFinalLetter(true);
                return true;
            }
            //// checks if char is less then the node's value to traverse right
        } else if (c > node->getVal()) {
            // checks if the right child is not a null pointer to traverse right
            if (node->right != nullptr) {
                // set node to its right child
                node = node->right;
            } else {
                // if the right child is a null ptr then create a node over
                // there
                node->right = new TrieNode(c, freq, false);
                // set node to its right child
                node = node->right;
                // for loop to traverse to the middle child of the nodes
                // in order to store a new word in the TST
                for (int i = position + 1; i < word.length(); i++) {
                    // creates new node as the middle child of node
                    node->middle = new TrieNode(word[i], freq, false);
                    // sets node to its midddle child
                    node = node->middle;
                }
                // at the end of the word sets the boolean of end word to true
                node->setFinalLetter(true);
                return true;
            }
            // checks if char is the same as node's value to traverse down
        } else {
            // checks if the position is equal to the length of the word
            if (position == word.length() - 1) {
                // sets the node to a word node
                node->setFinalLetter(true);
                // gives frequency to the node
                node->setFreq(freq);
                return true;
            } else {
                // checks if the middle node is not null
                if (node->middle != nullptr) {
                    // makes node its middle child
                    node = node->middle;
                    // increments position
                    ++position;
                    // get new char from new position
                    c = word[position];
                } else {
                    // traverse down the middle child by forming new nodes
                    for (int i = position + 1; i < word.length(); i++) {
                        // creates new nodes as middle child
                        node->middle = new TrieNode(word[i], freq, false);
                        // makes node its middle child
                        node = node->middle;
                    }
                    // set the boolean for the end of the word
                    node->setFinalLetter(true);
                    return true;
                }
            }
        }
    }
    return false;
}

/**
 * find method.
 * returns a boolean for whether the word exists in the tree
 * parameters - word - the word that needs to be looked for in the trie
 */
bool DictionaryTrie::find(string word) const {
    // checks if trie is empty
    if (root == nullptr) {
        return false;
    }
    // store the root in a new node
    TrieNode* node = root;
    // create position to get next character in a word
    int position = 0;
    // gets char using the position
    char c = word[position];

    while (true) {
        // checks if char is smaller the value of the node
        if (c < node->getVal()) {
            // the left child is not null
            if (node->left != nullptr) {
                // sets node to the left child
                node = node->left;
                // if it is null it returns false
            } else {
                return false;
            }
            // checks if char is greater the value of the node
        } else if (c > node->getVal()) {
            // the right child is not null
            if (node->right != nullptr) {
                // sets node to the right child
                node = node->right;
                // if it is null it returns false
            } else {
                return false;
            }
            // checks if char is equal to the value of the node
        } else {
            // checks if the position is equal to the length of the word
            // and if the node is an end letter.
            if (position == word.length() - 1 &&
                node->getFinalLetter() == true) {
                return true;
            } else {
                // checks if the middle child is not null
                if (node->middle != nullptr) {
                    // makes the node the middle child
                    node = node->middle;
                    // increment position
                    ++position;
                    // char at the position of the word
                    c = word[position];
                } else {
                    return false;
                }
            }
        }
    }
    return false;
}
/**
 * Helper method to find the pointer to a node
 * Returns the pointer of a node of a string
 * Parameter: the word wanting to find in the trie
 */
TrieNode* DictionaryTrie::findNode(string word) const {
    // Base case
    if (root == nullptr) {
        return nullptr;
    }
    TrieNode* node = root;
    int position = 0;
    char c = word[position];

    while (true) {
        // Looks if is smaller than given node
        if (c < node->getVal()) {
            // Moves to left subtree
            if (node->left != nullptr) {
                node = node->left;
            } else {
                return nullptr;
            }
        }
        // Looks if bigger than given node
        else if (c > node->getVal()) {
            if (node->right != nullptr) {
                // Sets node to right subtree if valid
                node = node->right;
            } else {
                return nullptr;
            }
        }  // Checks if end of the word
        else {
            if (position == word.length() - 1) {
                return node;
            }  // Moves down the trie and looks to next character in string
            else {
                if (node->middle != nullptr) {
                    node = node->middle;
                    ++position;
                    c = word[position];
                } else {
                    return nullptr;
                }
            }
        }
    }
}
/**
 * Helper method to traverse through a trie and push
 * pairs to a priority queue
 * Parameters: node to look at where we are in the trie;
 * prefix, the current string we are looking to find;
 * numCompletions, how many times we are going to push to a prio queue
 */
void DictionaryTrie::traversal(TrieNode* node, string prefix,
                               int numCompletions) {
    // make queue up to size of numcompletions, then replace min with next one
    if (node != nullptr) {
        traversal(node->left, prefix, numCompletions);

        // Found a word, then creates a pair and adds to priority queue
        if (node->getFinalLetter() == true) {
            if (queue->size() < numCompletions) {
                // Creates pair with string and frequency
                pair<string, int>* pair1 = new pair<string, int>();
                pair1->first = prefix + node->getVal();
                int value = node->getFreq();
                pair1->second = value;
                // Pushes the pair into the queue
                queue->push(pair1);
            } else {
                // Current node greater than min freq in queue
                if (node->getFreq() > queue->top()->second) {
                    // Creates and pushes pair while replacing the minimum
                    pair<string, int>* pair1 = new pair<string, int>();
                    pair1->first = prefix + node->getVal();
                    pair1->second = node->getFreq();
                    queue->push(pair1);
                    pair<string, int>* hold = queue->top();
                    queue->pop();
                    delete (hold);
                }  // Compares alphabetically if freq is same
                else if (node->getFreq() == queue->top()->second) {
                    if ((prefix + node->getVal()) > queue->top()->first) {
                        // Creates and pushes pair while replacing the minimum
                        pair<string, int>* pair1 = new pair<string, int>();
                        pair1->first = prefix + node->getVal();
                        pair1->second = node->getFreq();
                        queue->push(pair1);
                        pair<string, int>* hold = queue->top();
                        queue->pop();
                        delete (hold);
                    }
                }
            }
        }
        // If going down, then it includes the character and continues
        // traversing recursively down the middle
        traversal(node->middle, prefix + node->getVal(), numCompletions);
        // Recursivey calls to the right subtree
        traversal(node->right, prefix, numCompletions);
    }
}

/**
 * Finds a given number of strings in the trie that match the given prefix
 * Returns a vector of strings containing the most frequent strings of a given
 * prefix Parameters: prefix, the substring we are looking to match
 * numCompletions, how many strings to find
 */
vector<string> DictionaryTrie::predictCompletions(string prefix,
                                                  unsigned int numCompletions) {
    // Helper to finds end node of input prefix
    TrieNode* node = findNode(prefix);
    // Base cases to return empty vector
    if (node == nullptr || numCompletions == 0) {
        vector<string> empty;
        return empty;
    }
    // Prefix itself is a word
    if (node->getFinalLetter() == true) {
        // Creates pair and pushes to queue
        pair<string, int>* pair1 = new pair<string, int>();
        pair1->first = prefix;
        int hold = node->getFreq();
        pair1->second = hold;
        queue->push(pair1);
    }
    // Uses helper method to find all words that include
    // the prefix and pushes to queue
    traversal(node->middle, prefix, numCompletions);
    vector<string> result;
    // Loops and inserts strings from greatest priority / alphabetical
    for (int i = 0; i < numCompletions; i++) {
        if (queue->size() == 0) {
            break;
        }
        pair<string, int>* hold = queue->top();
        string store = hold->first;
        result.push_back(store);
        queue->pop();
        delete (hold);
    }
    // Clears the queue by popping and deleting
    while (!queue->empty()) {
        pair<string, int>* hold = (queue->top());
        queue->pop();
        delete (hold);
    }
    // Reverses the vector since we need to have descending order of frequency
    reverse(result.begin(), result.end());
    return result;
}

/**
 * Finds the most frequent strings that follow a given pattern
 * Parameters: pattern, which includes underscores that can be filled by any
 * value Returns a vector of strings from most frequent order that follow a
 * pattern
 */
std::vector<string> DictionaryTrie::predictUnderscores(
    string pattern, unsigned int numCompletions) {
    // No completions exist
    if (numCompletions == 0) {
        vector<string> empty;
        return empty;
    }
    TrieNode* node = root;
    vector<string> finished;
    // Inserts all words with length into the queue
    traversalLength(node, "", pattern.length());
    // Now check words in queue that match the pattern
    while (!rqueue->empty() && finished.size() < numCompletions) {
        string word = rqueue->top()->first;
        // Uses helper to find if the word matches the pattern
        bool result = recurse(pattern, word);
        // Adds to vector if word matches
        if (result == true) {
            finished.push_back(word);
        }
        // Deletes and pops the pair
        pair<string, int>* hold = rqueue->top();
        rqueue->pop();
        delete (hold);
    }
    // Clears the queue and memory
    while (!rqueue->empty()) {
        pair<string, int>* hold = rqueue->top();
        rqueue->pop();
        delete (hold);
    }
    return finished;
}
/**
 *  pushes all words with set length into queue starting from root
 * Parameters: node, the current node looking at ;
 * word, the word to match;
 * length, how long the word is
 */
void DictionaryTrie::traversalLength(TrieNode* node, string word, int length) {
    // Base case
    if (word.length() >= length) {
        return;
    }
    if (node != nullptr) {
        // Recursive call to left child
        traversalLength(node->left, word, length);

        // Found a word, then creates a pair and adds to priority queue
        if (node->getFinalLetter() == true && (word.length() + 1 == length)) {
            // Creates pair with string and frequency
            pair<string, int>* pair1 = new pair<string, int>();
            pair1->first = word + node->getVal();
            pair1->second = node->getFreq();
            // Pushes the pair into the queue
            rqueue->push(pair1);
        }
        // If going down, then it includes the character and continues
        // traversing
        traversalLength(node->middle, word + node->getVal(), length);
        // Recursive call to right child
        traversalLength(node->right, word, length);
    }
}
/**
 * Checks if pattern matches a word
 * parmaters: pattern, the pattern to match with underscores;
 * word, the word to match to pattern
 */
bool DictionaryTrie::recurse(string pattern, string word) {
    bool flag = true;
    // Loops through
    for (int i = 0; i < pattern.length(); i++) {
        // Case where a character doesn't match
        if (flag == false) {
            break;
        }
        // Character matches, continues to look at next
        if (pattern.at(i) != '_' && pattern.at(i) == word.at(i)) {
            continue;
        }
        // If underscore, any character works
        else if (pattern.at(i) == '_') {
            continue;
        }
        flag = false;
    }
    return flag;
}

/**
 * Destructor to delete trie and the prio queue
 */
DictionaryTrie::~DictionaryTrie() {
    deleteAll(root);
    delete queue;
    delete rqueue;
}
/**
 * Helper to delete all trie nodes recursively
 * Parameter: n, current node
 */
void DictionaryTrie::deleteAll(TrieNode* n) {
    // Base case where nothing to delete
    if (n == nullptr) {
        return;
    }
    deleteAll(n->left);
    deleteAll(n->middle);
    deleteAll(n->right);
    delete (n);
}