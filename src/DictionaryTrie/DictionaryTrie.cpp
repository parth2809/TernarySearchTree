/**
 * TODO: File Header
 *
 * Author:
 */
#include "DictionaryTrie.hpp"
#include <iostream>
#include <queue>
#include <string>
#include <utility>
using namespace std;

typedef std::priority_queue<pair<string, int>*, vector<pair<string, int>*>,
                            Tcompare>
    pq;
/* TODO */
DictionaryTrie::DictionaryTrie() : root(nullptr), treeSize(0), treeHeight() {
    queue = new pq();
}

/* TODO */
bool DictionaryTrie::insert(string word, unsigned int freq) {
    int position = 0;
    if (root == nullptr) {
        root = new TrieNode(word[position], freq, false);
    }
    char c = word[position];
    TrieNode* node = root;

    while (true) {
        if (c < node->getVal()) {
            if (node->left != nullptr) {
                node = node->left;
            } else {
                node->left = new TrieNode(c, freq, false);
                node = node->left;
                for (int i = position + 1; i < word.length(); i++) {
                    node->middle = new TrieNode(word[i], freq, false);
                    node = node->middle;
                }
                node->setFinalLetter(true);
                break;
            }
        } else if (c > node->getVal()) {
            if (node->right != nullptr) {
                node = node->right;
            } else {
                node->right = new TrieNode(c, freq, false);
                node = node->right;
                for (int i = position + 1; i < word.length(); i++) {
                    node->middle = new TrieNode(word[i], freq, false);
                    node = node->middle;
                }
                node->setFinalLetter(true);
                break;
            }
        } else {
            if (position == word.length() - 1) {
                node->setFinalLetter(true);
                return true;
            } else {
                if (node->middle != nullptr) {
                    node = node->middle;
                    ++position;
                    c = word[position];
                } else {
                    for (int i = position + 1; i < word.length(); i++) {
                        node->middle = new TrieNode(word[i], freq, false);
                        node = node->middle;
                    }
                    node->setFinalLetter(true);
                    break;
                }
            }
        }
    }
}
/*
TrieNode* DictionaryTrie::insertChar(TrieNode* node, string word,
                                     unsigned int freq) {
    char c = word[0];
    if (node == nullptr) {
        node = new TrieNode(c, freq, false);
    } else if (node->getVal() < c) {
        node->right = insertChar(node->right, word, freq);
    } else if (node->getVal() > c) {
        node->left = insertChar(node->right, word, freq);
    } else if (word.length() != 1) {
        word.erase(word[0]);
        node->middle = insertChar(node->right, word, freq);
    } else {
        node->setFinalLetter(true);
        node->setFreq(freq);
    }
    return node;
}

char DictionaryTrie::nextCharacter(string word, int position) {
    return word[position];
}


//TODO
DictionaryTrie::TrieNode* DictionaryTrie::insertLetterNode(
    TrieNode* node, char c, unsigned int freq, int position, string word) {
    TrieNode* temp = node;
    // Current node does not exist
    if (temp == nullptr) {
        // Reached last char of input word and exits function
        if (position == word.length() - 1) {
            temp->setVal(c);
            temp->setFreq(freq);
            temp->setFinalLetter(true);
            return temp;
        }
        temp->setVal(c);
        temp->setFreq(freq);
        temp->setFinalLetter(false);
        position++;
        temp->middle = insertLetterNode(
            temp->middle, nextCharacter(word, position), freq, position,
word); } else if (temp->getVal() < c) { temp->right =
insertLetterNode(temp->right, c, freq, position, word); } else if
(temp->getVal() > c) { temp->left = insertLetterNode(temp->left, c, freq,
position, word); } else if (temp->getVal() == c) {
        // Found last letter of word
        if (position == word.length() - 1) {
            return nullptr;
        }
        position++;
        temp->middle = insertLetterNode(
            temp->middle, nextCharacter(word, position), freq, position,
word);
    }
    return temp;
    ;
}
*/
/* TODO */
bool DictionaryTrie::find(string word) const {
    if (root == nullptr) {
        return false;
    }
    TrieNode* node = root;
    int position = 0;
    char c = word[position];

    while (true) {
        if (c < node->getVal()) {
            if (node->left != nullptr) {
                node = node->left;
            } else {
                return false;
            }
        } else if (c > node->getVal()) {
            if (node->right != nullptr) {
                node = node->right;
            } else {
                return false;
            }
        } else {
            if (position == word.length() - 1 &&
                node->getFinalLetter() == true) {
                return true;
            } else {
                if (node->middle != nullptr) {
                    node = node->middle;
                    ++position;
                    c = word[position];
                } else {
                    return false;
                }
            }
        }
    }
}

TrieNode* DictionaryTrie::findNode(string word) const {
    if (root == nullptr) {
        return nullptr;
    }
    TrieNode* node = root;
    int position = 0;
    char c = word[position];

    while (true) {
        if (c < node->getVal()) {
            if (node->left != nullptr) {
                node = node->left;
            } else {
                return nullptr;
            }
        } else if (c > node->getVal()) {
            if (node->right != nullptr) {
                node = node->right;
            } else {
                return nullptr;
            }
        } else {
            if (position == word.length() - 1) {
                return node;
            } else {
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

void DictionaryTrie::traversal(TrieNode* node, string prefix) {
    if (node != nullptr) {
        traversal(node->left, prefix);

        // Found a word, then creates a pair and adds to priority queue
        if (node->getFinalLetter() == true) {
            // Creates pair with string and frequency
            pair<string, int>* pair1 = new pair<string, int>();
            pair1->first = prefix + node->getVal();
            pair1->second = node->getFreq();
            // Pushes the pair into the queue
            queue->push(pair1);
        }
        // If going down, then it includes the character and continues
        // traversing
        traversal(node->middle, prefix + node->getVal());

        traversal(node->right, prefix);
    }
}

/* TODO */
vector<string> DictionaryTrie::predictCompletions(string prefix,
                                                  unsigned int numCompletions) {
    // Finds end node of input prefix
    TrieNode* node = findNode(prefix);
    if (node == nullptr) {
        vector<string> empty;
        return empty;
    }
    // Prefix itself is a word
    if (node->getFinalLetter() == true) {
        pair<string, int> pair1;
        pair1.first = prefix;
        pair1.second = node->getFreq();
        queue->push(&pair1);
    }
    // Uses helper method to find all words that include
    // the prefix and pushes to queue
    traversal(node->middle, prefix);
    vector<string> result;
    // Loops and inserts strings from greatest priority
    while (result.size() < numCompletions) {
        // Num completions greater than queue size
        if (queue->size() == 0) {
            break;
        }
        pair<string, int>* hold = queue->top();
        string store = hold->first;
        result.push_back(store);
        queue->pop();
        // delete (hold);
    }
    while (!queue->empty()) {
        pair<string, int>* hold = (queue->top());
        delete (hold);
        queue->pop();
    }
    return result;
}

/* TODO */
std::vector<string> DictionaryTrie::predictUnderscores(
    string pattern, unsigned int numCompletions) {
    return {};
}

/* TODO */
DictionaryTrie::~DictionaryTrie() {
    deleteAll(root);
    delete queue;
}

void DictionaryTrie::deleteAll(TrieNode* n) {
    if (n == nullptr) {
        return;
    }
    deleteAll(n->left);
    deleteAll(n->middle);
    deleteAll(n->right);
    delete (n);
}