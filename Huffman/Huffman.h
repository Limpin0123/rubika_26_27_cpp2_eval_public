#pragma once

#include <string>
#include <vector>

// Feel free to add anything you need

struct Node
{
	char Token;
	float Frequency;

	Node* Left;
	Node* Right;
};

class Huffman
{
public:
	~Huffman();

	bool GenerateTree(const std::string& inputMessage);

	std::string Encode(const std::string& message);

	std::string Decode(std::string encodedMessage);

private:
	Node* RootNode;

	void DestroyAllChildrenNodes(Node* currentNode);

	bool FindCharacterNode(std::string& path, Node* currentNode, char c);
	char GetFirstFoundCharacter(std::string& path);
};