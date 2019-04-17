#include "Trie.h"

Node::Node() {
	this->ch = ' ';
	this->isLeaf = false;
	this->str = "";
	this->children = std::vector<Node*>(ALPHABET_SIZE, NULL);
}

Node::~Node() {
	delete this;
}

std::string Node::getString() {
	return this->str;
}

void Node::setString(std::string _str) {
	this->str.assign(_str);
}


char Node::getChar() {
	return this->ch;
}

void Node::setChar(char _ch) {
	this->ch = _ch;
}

bool Node::getType() {
	return this->isLeaf;
}

void Node::setType(bool _isLeaf) {
	this->isLeaf = _isLeaf;
}

Node* Node::getChild(char c) {	
	
	int index = INDEX_CHAR(c);

	return this->children[index];
}

void Node::addChild(Node* child) {
	
	int index = INDEX_CHAR(child->getChar());
	
	this->children[index] = child;
}

std::vector<Node*> Node::getChilds() {
	return this->children;
}

bool Node::hasChild() {

	for (auto n : this->children) {
		if (n != NULL) {
			return true;
		}
			
	}

	return false;
}

void Node::setParent(Node* node) {
	this->parent = node;
}

Node* Node::getParent() {
	return this->parent;
}

Trie::Trie() {
	this->root = new Node();
}

Trie::~Trie() {
	delete this;
}

void Trie::addString(std::string str) {

	Node* current = this->root;

	for (int level = 0; level < str.length(); level++) {
		
		Node* child = current->getChild(str.at(level));

		if (child != NULL) {
			current = child;
		}
		else {
			Node* temp = new Node();
			
			temp->setChar(str.at(level));
			
			current->addChild(temp);

			std::string new_str = current->getString();
			new_str += temp->getChar();
			temp->setString(new_str);

			current->getChilds()[INDEX_CHAR(temp->getChar())]->setParent(current);

			current = temp;
		}

		if (level == str.length() - 1) {
			current->setType(true);
		}
	}
}

bool Trie::searchString(std::string str) {

	Node* current = this->root;
	
	for (int level = 0; level < str.length(); level++) {
		Node* temp = current->getChild(str.at(level));
		if (temp == NULL) {
			return false;
		}
		current = temp;
	}

	return current->getType();
}

Node* Trie::getLeafNode(std::string str) {
	
	if (this->searchString(str)) {
		Node* current = this->root;

		for (int level = 0; level < str.length(); level++) {
			Node* temp = current->getChild(str.at(level));
			current = temp;
		}
		return current;
	}

	return NULL;
}



void Trie::deleteString(std::string str) {

	if (this->searchString(str)) {

		Node* current = this->root;

		for (int level = 0; level < str.length(); level++) {
			Node* temp = current->getChild(str.at(level));
			current = temp;
		}

		current->setType(false);
	}

}

std::vector<std::string> Trie::getAllStringsStartsWithPrefix(std::string prefix) {
	
	std::vector<Node*> stack;
	std::vector<std::string> prefix_string;

	Node* current = this->root;
	for (int level = 0; level < prefix.length(); level++) {
		Node *temp = current->getChild(prefix.at(level));
		current = temp;
	}

	stack.push_back(current);

	while (!stack.empty()) {

		Node* curr = stack.back();
		
		stack.pop_back();

		if (curr->getType()) {
			prefix_string.push_back(curr->getString());
		}

		for (int child_index = curr->getChilds().size() - 1; child_index >= 0; child_index--) {
			if (curr->getChilds()[child_index] != NULL) {
				stack.push_back(curr->getChilds()[child_index]);
			}
		}

	}

	return prefix_string;
}

std::vector<std::string> Trie::getNStringStartsWithPrefix(std::string prefix, int n) {

	std::vector<Node*> stack;
	std::vector<std::string> prefix_string;

	Node* current = this->root;
	for (int level = 0; level < prefix.length(); level++) {
		Node *temp = current->getChild(prefix.at(level));
		current = temp;
	}

	stack.push_back(current);

	while (!stack.empty() && prefix_string.size() < n) {

		Node* curr = stack.back();

		stack.pop_back();

		if (curr->getType()) {
			prefix_string.push_back(curr->getString());
		}

		if (prefix_string.size() == n) {
			break;
		}

		for (int child_index = curr->getChilds().size() - 1; child_index >= 0; child_index--) {
			if (curr->getChilds()[child_index] != NULL) {
				stack.push_back(curr->getChilds()[child_index]);
			}
		}

	}

	return prefix_string;
}
