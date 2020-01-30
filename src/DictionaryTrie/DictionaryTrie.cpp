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
    // Current node does not exist
    if (temp == nullptr) {
        // Reached last char of input word and exits function
        if (position == word.length() - 1) {
            temp = new TrieNode(c, freq, true);
            return;
        }
        temp = new TrieNode(c, freq, false);
        position++;
        insertLetterNode(temp->middle, nextCharacter(word, position), freq,
                         position, word);
    }
    if (temp->getVal() < c) {
        insertLetterNode(temp->right, c, freq, position, word);
    } else if (temp->getVal() > c) {
        insertLetterNode(temp->left, c, freq, position, word);
    } else if (temp->getVal() == c) {
        // Found last letter of word
        if (position == word.length() - 1) {
            return;
        }
        position++;
        insertLetterNode(temp->middle, nextCharacter(word, position), freq,
                         position, word);
    }
    return;
}

/* TODO */
bool DictionaryTrie::find(string word) const {
    TrieNode* temp = root;
    // Empty trie
    if (temp == nullptr) {
        return false;
    }
    int counter = 0;
    // Current node val is less than first char
    while (counter != word.length() - 1) {
        if (temp->getVal() < word[counter]) {
            temp = temp->right;
        } else if (temp->getVal() > word[counter]) {
            temp = temp->left;
        } else {
            temp = temp->middle;
        }
        counter++;
    }
    if (temp->getFinalLetter() == true && temp->getVal() == word[counter]) {
        return true;
    }
    return false;
}

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