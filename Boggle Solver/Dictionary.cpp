#include "Dictionary.h"

Node* Dictionary::getNode(Node* node)
// pre: Takes uninitialized node as parameter
// post: Initializes all the aspects of the node
{
	node = new Node;
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		node->alphabet_link[i] = NULL;
	}
	node->endOfWord = false;
	return node;
}

Dictionary::Dictionary()
// pre: Dictionary is not created
// post: Dictionary is constructed with default parameters.
{
	root = getNode(root);
	numWords = 0;
}

Dictionary::Dictionary(string file)
// pre: Dictionary is not created
// post: Dictionary is constructed by adding words from the input file
{
	root = getNode(root);
	numWords = 0;
	ifstream inFile(file.c_str());
	string word;
	while (inFile >> word) {
		addWord(word);
		numWords++;
	}
}

void Dictionary::addWord(string word)
// pre: dictionary is initialized. And takes word string as parameter
// post: adds word to the dictionary
{
	Node* curr = root;
	for (int i = 0; i < word.length(); i++) {
		int index = word[i] - 'a';
		if (!curr->alphabet_link[index]) {
			curr->alphabet_link[index] = new Node();
		}
		curr = curr->alphabet_link[index];
	}
	curr->endOfWord = true;
}

bool Dictionary::isWord(string word)
// pre: dictionary is initialized
// post: returns true if word is present in dictionary
{
	Node* curr = root;
	for (int i = 0; i < word.length(); i++) {
		int index = word[i] - 'a';
		if (!curr->alphabet_link[index]) {
			return false;
		}
		curr = curr->alphabet_link[index];
	}
	return (curr != NULL && curr->endOfWord);
}

bool Dictionary::hasChildren(Node* node)
// pre: dictionary is initialized
// post: returns true if node is not a leaf node.(end of word)
{
	for (int i = 0; i < ALPHABET_SIZE; i++)
		if (node->alphabet_link[i])
			return true;
	return false;
}

bool Dictionary::isPrefix(string word)
// pre: dictionary is initialized
// post: returns true if word is a prefic in the dictionary
{
	Node* curr = root;
	for (int i = 0; i < word.length(); i++) {
		int index = word[i] - 'a';
		if (!curr->alphabet_link[index]) {
			return false;
		}
		curr = curr->alphabet_link[index];
	}
	return (hasChildren(curr));
}

int Dictionary::wordCount()
// pre: dictionary is initialized
// post: returns the number of words in the dictionary
{
	return numWords;
}
