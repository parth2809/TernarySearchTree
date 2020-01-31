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
                            compare>
    pq;
/* TODO */
DictionaryTrie::DictionaryTrie() : root(nullptr), treeSize(0), treeHeight() {}

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

TrieNode* DictionaryTrie::traversal(TrieNode* node, string prefix,
                                    pq* queue) const {
    if (node != nullptr) {
        traversal(node->left, prefix, queue);
        // Found a word, then creates a pair and adds to priority queue
        if (node->getFinalLetter() == true) {
            string newString = prefix + node->getVal();
            queue->push(&make_pair(prefix, node->getFreq()));
        }
        // If going down, then it includes the character and continues
        // traversing
        traversal(node->middle, prefix + node->getVal(), queue);
        traversal(node->right, prefix, queue);
    }
}

/* TODO */
vector<string> DictionaryTrie::predictCompletions(string prefix,
                                                  unsigned int numCompletions) {
    // Finds end node of input prefix
    TrieNode* node = findNode(prefix);
    pq queue;
    // Prefix itself is a word
    if (node->getFinalLetter() == true) {
        queue.push(&make_pair(prefix, node->getFreq()));
    }
    // Uses helper method to find all words that include the prefix
    traversal(node, prefix, &queue);
    vector<string> result;
    while (result.size() < numCompletions) {
        result.push_back((queue.top()->first));
    }
    return result;
}

/* TODO */
std::vector<string> DictionaryTrie::predictUnderscores(
    string pattern, unsigned int numCompletions) {
    return {};
}

/* TODO */
DictionaryTrie::~DictionaryTrie() {}