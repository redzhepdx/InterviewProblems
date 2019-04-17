#ifndef TRIE_H
#define TRIE_H

#include<iostream>
#include<string>
#include<vector>
#include<memory>

#define ALPHABET_SIZE 26
#define INDEX_CHAR(c) ((int)c - (int)'a')

class Node{

public:

	Node();
	~Node();
	char getChar();
	void setChar(char ch);
	std::string getString();
	void setString(std::string str);
	bool getType();
	void setType(bool isLeaf);
	Node* getChild(char c);
	void addChild(Node* child);
	bool hasChild();
	std::vector<Node*> getChilds();
	
	void setParent(Node* node);
	Node* getParent();
	std::vector<int> occurances;

private:
	char ch;
	bool isLeaf;
	std::string str;
	Node* parent;
	std::vector<Node*> children;
};

class Trie {

public:

	Trie();
	~Trie();
	void addString(std::string str);
	bool searchString(std::string str);
	void deleteString(std::string str);
	Node* getLeafNode(std::string str);
	std::vector<std::string> getAllStringsStartsWithPrefix(std::string prefix);
	std::vector<std::string> getNStringStartsWithPrefix(std::string prefix, int n);

private:
	Node* root;

};

#endif TRIE_H
