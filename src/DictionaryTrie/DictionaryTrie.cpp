/**
 * TODO: File Header
 *
 * Author:
 */
#include "DictionaryTrie.hpp"
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
using namespace std;

typedef std::priority_queue<pair<string, int>*, vector<pair<string, int>*>,
                            Tcompare>
    pq;
typedef std::priority_queue<pair<string, int>*, vector<pair<string, int>*>,
                            Compare>
    rpq;
/* TODO */
DictionaryTrie::DictionaryTrie() : root(nullptr), treeSize(0), treeHeight() {
    queue = new pq();
    rqueue = new rpq();
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
                node->setFreq(freq);
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
                pair<string, int>* pair1 = new pair<string, int>();
                int value = node->getFreq();
                pair1->first = prefix + node->getVal();
                pair1->second = value;
                // Pushes the pair into the queue
                queue->push(pair1);
                pair<string, int>* hold = queue->top();
                queue->pop();
                delete (hold);
                // Current node greater than min freq in queue
                /*   if (node->getFreq() > queue->top()->second) {
                       pair<string, int>* pair1 = new pair<string, int>();
                       pair1->first = prefix + node->getVal();
                       pair1->second = node->getFreq();
                       pair<string, int>* hold = queue->top();
                       queue->pop();
                       delete (hold);
                       queue->push(pair1);
                   } else if (node->getFreq() == queue->top()->second) {
                       if ((prefix + node->getVal()) > queue->top()->first) {
                           pair<string, int>* pair1 = new pair<string, int>();
                           pair1->first = prefix + node->getVal();
                           pair1->second = node->getFreq();
                           pair<string, int>* hold = queue->top();
                           queue->pop();
                           delete (hold);
                           queue->push(pair1);
                       }
                   }*/
            }
        }

        // If going down, then it includes the character and continues
        // traversing
        traversal(node->middle, prefix + node->getVal(), numCompletions);

        traversal(node->right, prefix, numCompletions);
    }
}

/* TODO */
vector<string> DictionaryTrie::predictCompletions(string prefix,
                                                  unsigned int numCompletions) {
    // Finds end node of input prefix
    TrieNode* node = findNode(prefix);
    if (node == nullptr || numCompletions == 0) {
        vector<string> empty;
        return empty;
    }
    // Prefix itself is a word
    if (node->getFinalLetter() == true) {
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
    while (!queue->empty()) {
        pair<string, int>* hold = (queue->top());
        queue->pop();
        delete (hold);
    }
    reverse(result.begin(), result.end());
    return result;
}

/* TODO */
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
        bool result = recurse(pattern, word);
        if (result == true) {
            // add to vector
            finished.push_back(word);
        }
        pair<string, int>* hold = rqueue->top();
        rqueue->pop();
        delete (hold);
        // pop and delete
    }
    while (!rqueue->empty()) {
        pair<string, int>* hold = rqueue->top();
        rqueue->pop();
        delete (hold);
    }
    return finished;
    // pattern doesnt contain underscore?
}
// pushes all words with set length into queue starting from root
void DictionaryTrie::traversalLength(TrieNode* node, string word, int length) {
    if (word.length() >= length) {
        return;
    }
    if (node != nullptr) {
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

        traversalLength(node->right, word, length);
    }
}
// word is pattern including the underscores
bool DictionaryTrie::recurse(string pattern, string word) {
    bool flag = true;
    for (int i = 0; i < pattern.length(); i++) {
        if (flag == false) {
            break;
        }
        if (pattern.at(i) != '_' && pattern.at(i) == word.at(i)) {
            continue;
        } else if (pattern.at(i) == '_') {
            continue;
        }
        flag = false;
    }
    return flag;
}

/* TODO */
DictionaryTrie::~DictionaryTrie() {
    deleteAll(root);
    delete queue;
    delete rqueue;
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