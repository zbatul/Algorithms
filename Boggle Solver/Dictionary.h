#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int ALPHABET_SIZE = 26;

struct Node {
	// Your data structure goes here
	Node* alphabet_link[ALPHABET_SIZE];
	bool endOfWord;
};

class Dictionary
{
public:
	Dictionary();
	Dictionary(string file);
	void addWord(string word);
	bool isWord(string word);
	bool isPrefix(string word);
	int wordCount();
	bool hasChildren(Node* node);

private:
	Node* root;
	int numWords;
	// Any private methods you need/want
	Node* getNode(Node* node);
};