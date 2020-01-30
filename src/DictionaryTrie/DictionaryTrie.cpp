/**
 * TODO: File Header
 *
 * Author:
 */
#include "DictionaryTrie.hpp"
#include <iostream>

/* TODO */
DictionaryTrie::DictionaryTrie() : root(0), treeSize(0), treeHeight() {}

/* TODO */
bool DictionaryTrie::insert(string word, unsigned int freq) {
    int position = 0;
    insertLetterNode(root, word[0], freq, position, word);
    return true;
}

char DictionaryTrie::nextCharacter(string word, int position) {
    return word[position];
}

/* TODO */
void DictionaryTrie::insertLetterNode(TrieNode* node, char c, unsigned int freq,
                                      int position, string word) {
    TrieNode* temp = node;
    if (temp == nullptr) {
        position++;
        if (position == word.length() - 1) {
            temp = new TrieNode(c, freq, true);
        } else {
            temp = new TrieNode(c, freq, false);
        }
        if (position != word.length()) {
            insertLetterNode(root, nextCharacter(word, position), freq,
                             position, word);
        }
    }
    if (temp->getVal() < c) {
        insertLetterNode(temp->left, c, freq, position, word);
    } else if (temp->getVal() > c) {
        insertLetterNode(temp->right, c, freq, position, word);
    } else if (temp->getVal() == c) {
        position++;
        if (position != word.length()) {
            insertLetterNode(temp->middle, nextCharacter(word, position), freq,
                             position, word);
        }
    }
    return;
}

/* TODO */
bool DictionaryTrie::find(string word) const { return false; }

/* TODO */
vector<string> DictionaryTrie::predictCompletions(string prefix,
                                                  unsigned int numCompletions) {
    return {};
}

/* TODO */
std::vector<string> DictionaryTrie::predictUnderscores(
    string pattern, unsigned int numCompletions) {
    return {};
}

/* TODO */
DictionaryTrie::~DictionaryTrie() {}