#include "Huffman.h"
#include <map>
#include <algorithm>
#include <functional>
#include "MemoryTrack.h"

Huffman::~Huffman()
{
	DestroyAllChildrenNodes(RootNode);
}

bool Huffman::GenerateTree(const std::string& inputMessage)
{
	std::map<char, Node*> nodes;
	for (char c : inputMessage)
	{
		auto it = nodes.find(c);
		if (it == nodes.end())
		{
			auto value = nodes.emplace(c, DBG_NEW Node());
			value.first->second->Token = c;
			value.first->second->Frequency = 1;
		}
		else
		{
			it->second->Frequency += 1;
		}
	}

	std::vector<Node*> sortedNodes;
	for (auto& kvp : nodes)
	{
		sortedNodes.push_back(kvp.second);
	}

	std::function<bool(Node*, Node*)> nodeComparator = [](Node* a, Node* b) -> bool {
		return a->Frequency < b->Frequency;
		};

	std::sort(sortedNodes.begin(), sortedNodes.end(), nodeComparator);

	while (sortedNodes.size() > 1)
	{
		Node* smallest = sortedNodes.at(0);
		sortedNodes.erase(sortedNodes.begin());

		Node* smallest2 = sortedNodes.at(0);
		sortedNodes.erase(sortedNodes.begin());

		Node* parent = DBG_NEW Node();
		parent->Frequency = smallest->Frequency + smallest2->Frequency;

		parent->Left = smallest;
		parent->Right = smallest2;

		auto insertionPos = std::lower_bound(sortedNodes.begin(), sortedNodes.end(), parent, nodeComparator);
		sortedNodes.insert(insertionPos, parent);

	}

	RootNode = sortedNodes.at(0);
	return true;
}

std::string Huffman::Encode(const std::string& message)
{
	std::string value;
	for (char c : message)
	{
		std::string path;
		FindCharacterNode(path, RootNode, c);
		
		for (int i = path.size() - 1; i >= 0; i--)
		{
			value.push_back(path[i]);
		}
	}
	return value;
}

//passing message via copy
std::string Huffman::Decode(std::string encodedMessage)
{
	std::string value;
	while (encodedMessage.size() > 0)
	{
		value.push_back(GetFirstFoundCharacter(encodedMessage));
	}
	return value;
}

char Huffman::GetFirstFoundCharacter(std::string& path)
{
	Node* currentNode = RootNode;
	while (currentNode->Left != nullptr || currentNode->Right != nullptr)
	{
		char nextMove = path.at(0);
		path.erase(path.begin());
		if (nextMove == '0')
		{
			if (currentNode->Left == nullptr) {
				throw;
			}
			currentNode = currentNode->Left;
		}
		else
		{
			if (currentNode->Right== nullptr) {
				throw;
			}
			currentNode = currentNode->Right;
		}
	}
	return currentNode->Token;
}

void Huffman::DestroyAllChildrenNodes(Node* currentNode)
{
	if (currentNode->Left != nullptr)
	{
		DestroyAllChildrenNodes(currentNode->Left);
	}
	if (currentNode->Right != nullptr)
	{
		DestroyAllChildrenNodes(currentNode->Right);
	}

	delete currentNode;
	//currentNode = nullptr;
}

bool Huffman::FindCharacterNode(std::string& path, Node* currentNode, char c)
{
	if (currentNode->Token == c) return true; //value found !

	else if (currentNode->Left == nullptr && currentNode->Right == nullptr) return false;

	else
	{
		if (currentNode->Left != nullptr)
		{
			if (FindCharacterNode(path, currentNode->Left, c))//value found on left
			{
				path.push_back('0');
				return true;
			}

			if (currentNode->Right != nullptr)
			{
				if (FindCharacterNode(path, currentNode->Right, c))//value found on right
				{
					path.push_back('1');
					return true;
				}
			}
			//not on the good path
			return false;
		}
		if (FindCharacterNode(path, currentNode->Right, c))//value found on right
		{
			path.push_back('1');
			return true;
		}
		return false;
	}
}
