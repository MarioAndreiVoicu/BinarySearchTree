#pragma once
#include<queue>  //used for levelOrder traversal
#include<iostream>

template <typename T>
class BinarySearchTree
{
	struct TreeNode
	{
		T key;
		TreeNode* leftNode;
		TreeNode* rightNode;
		TreeNode* parentNode;

		TreeNode(const T& keyValue = T{}, TreeNode* left = nullptr, TreeNode* right = nullptr, TreeNode* parent = nullptr)
			: key(keyValue), leftNode(left), rightNode(right), parentNode(parent) {}
	};

	TreeNode* root;


	void displayPreOrder(TreeNode* node)
	{
		if (node != nullptr)
		{
			std::cout << node->key << " ";
			displayPreOrder(node->leftNode);
			displayPreOrder(node->rightNode);
		}
	}

	void displayInOrder(TreeNode* node)
	{
		if (node != nullptr)
		{
			displayInOrder(node->leftNode);
			std::cout << node->key << " ";
			displayInOrder(node->rightNode);
		}
	}

	void displayPostOrder(TreeNode* node)
	{
		if (node != nullptr)
		{
			displayPostOrder(node->leftNode);
			displayPostOrder(node->rightNode);
			std::cout << node->key << " ";
		}
	}

public:
	BinarySearchTree() : root(nullptr) {}

	void insert(const T& value)
	{
		if (root == nullptr)
		{
			TreeNode* node = new TreeNode;
			node->key = value;
			root = node;
			return;
		}

		TreeNode* node = root;
		while (node != nullptr)  //searches the tree for the right spot to insert the value
		{
			if (value == node->key)
				return;

			if (value > node->key)  //if the value is higher than the node key,it will be inserted in the right subtree
			{
				if (node->rightNode == nullptr)  //if the node is a leaf node,then a new node with the value will be made and it will become a leaf node
				{
					TreeNode* newNode = new TreeNode;
					newNode->key = value;
					newNode->parentNode = node;
					node->rightNode = newNode;
				}
				else  //if the node is not a leaf node,then it keeps searching for the correct spot to insert the value in the right subtree
					node = node->rightNode;
			}
			else  //if the value is lower than the node key,it will be inserted in the left subtree
			{
				if (node->leftNode == nullptr)  //if the node is a leaf node,then a new node with the value will be made and it will become a leaf node
				{
					TreeNode* newNode = new TreeNode;
					newNode->key = value;
					newNode->parentNode = node;
					node->leftNode = newNode;
				}
				else  //if the node is not a leaf node,then it keeps searching for the correct spot to insert the value in the left subtree
					node = node->leftNode;
			}
		}
	}

	void erase(TreeNode* nodeDeleted)  //3 cases:  case 1)the node doesn't have children  case 2)the node has one child  case 3)the node has 2 children
	{
		if (nodeDeleted->leftNode == nullptr && nodeDeleted->rightNode == nullptr)  //case 1) if the node doesn't have children,it becomes nullptr
		{
			if (nodeDeleted == root)
			{
				delete root;
				root = nullptr;
				return;
			}

			if (nodeDeleted->parentNode->leftNode == nodeDeleted)  //if the node is the left child
			{
				nodeDeleted->parentNode->leftNode = nullptr;
			}
			else   //if the node is the right child
			{
				nodeDeleted->parentNode->rightNode = nullptr;
			}
			delete nodeDeleted;
		}
		else if (nodeDeleted->leftNode != nullptr && nodeDeleted->rightNode == nullptr)  //case 2) the node has only a left child
		{
			if (nodeDeleted == root)
			{
				root = nodeDeleted->leftNode;
				root->parentNode = nullptr;
			}
			else
			{
				nodeDeleted->parentNode->leftNode = nodeDeleted->leftNode;
				nodeDeleted->leftNode->parentNode = nodeDeleted->parentNode;
			}
			delete nodeDeleted;
		}
		else if (nodeDeleted->rightNode != nullptr && nodeDeleted->leftNode == nullptr)   //case 2) the node has only a right child
		{
			if (nodeDeleted == root)
			{
				root = nodeDeleted->rightNode;
				root->parentNode = nullptr;
			}
			else
			{
				nodeDeleted->parentNode->rightNode = nodeDeleted->rightNode;
				nodeDeleted->rightNode->parentNode = nodeDeleted->parentNode;
			}
			delete nodeDeleted;
		}
		else  //case 4) the node has two children
		{
			TreeNode* successorNode = successor(nodeDeleted);  //in this case the node takes the key of the successor and the successor is deleted.The successor will have either one or no children
			nodeDeleted->key = successorNode->key;
			erase(successorNode);
		}
	}

	void deleteKey(const T& key)
	{
		TreeNode* nodeDeleted = find(key);
		if (nodeDeleted == nullptr)
			return;

		erase(nodeDeleted);
	}

	void clear()
	{
		while (!empty())
			erase(root);
	}

	TreeNode* max(TreeNode* node)  //it returns a pointer to the node with the maximum key from the subtree with the node from the parameter as the root
	{
		if (node == nullptr)
			return nullptr;

		while (node->rightNode != nullptr)
			node = node->rightNode;
		return node;
	}

	TreeNode* min(TreeNode* node)
	{
		if (node == nullptr)
			return nullptr;

		while (node->leftNode != nullptr)
			node = node->leftNode;

		return node;
	}

	TreeNode* successor(TreeNode* node)  //returns a pointer to the successor of the node
	{
		if (node->rightNode != nullptr)  //if the node has a right child,it's successor is in the right subtree
		{
			node = node->rightNode;
			while (node->leftNode != nullptr)
				node = node->leftNode;

			return node;
		}
		else   //if the node doesn't have a right child,the successor is the first parent node that has contains the node in the left subtree
		{
			while (node->parentNode != nullptr)
			{
				if (node->parentNode->leftNode == node)
					return node->parentNode;
				node = node->parentNode;
			}
			return nullptr;
		}
	}

	TreeNode* predecessor(TreeNode* node)  //returns a pointer to the predecessor of the node
	{
		if (node->leftNode != nullptr)  //if the node has a left child,it's predecessor is in the left subtree
		{
			node = node->leftNode;
			while (node->rightNode != nullptr)
				node = node->rightNode;

			return node;
		}
		else   //if the node doesn't have a left child,the predecessor is the first parent node that has contains the node in the right subtree
		{
			while (node->parentNode != nullptr)
			{
				if (node->parentNode->rightNode == node)
					return node->parentNode;
				node = node->parentNode;
			}
			return nullptr;
		}
	}

	TreeNode* find(const T& keySearch)
	{
		TreeNode* node = root;
		while (node != nullptr)
		{
			if (keySearch == node->key)
				return node;

			if (keySearch > node->key)  //if the value is higher than the node key,it will search in the right subtree
			{
				if (node->rightNode == nullptr)
					return nullptr;
				else  //if the node is not a leaf node,then it keeps searching in the right subtree
					node = node->rightNode;
			}
			else  //if the value is lower than the node key,it will search in the left subtree
			{
				if (node->leftNode == nullptr)
					return nullptr;
				else  //if the node is not a leaf node,then it keeps searching in the left subtree
					node = node->leftNode;
			}
		}
		return nullptr;
	}

	void displayPreOrder()
	{
		displayPreOrder(root);
	}

	void displayInOrder()
	{
		displayInOrder(root);
	}

	void displayPostOrder()
	{
		displayPostOrder(root);
	}

	void displayLevelOrder()
	{
		if (root == nullptr)
			return;
		if (root->leftNode == nullptr && root->rightNode == nullptr)
		{
			std::cout << "Level 0: ";
			std::cout << root->key;
			return;
		}

		int levelCount = 0;
		std::queue<TreeNode*> prevLevel;
		std::cout << "Level 0: " << root->key << "\n";
		levelCount++;

		TreeNode* node;
		std::queue<TreeNode*> currentLevel;
		std::cout << "Level 1: ";
		if (root->leftNode != nullptr)
		{
			std::cout << root->leftNode->key << " ";
			currentLevel.push(root->leftNode);
		}
		if (root->rightNode != nullptr)
		{
			std::cout << root->rightNode->key << " ";
			currentLevel.push(root->rightNode);
		}
		while (!currentLevel.empty())
		{
			while (!prevLevel.empty())
				prevLevel.pop();

			prevLevel = currentLevel;

			while (!currentLevel.empty())
				currentLevel.pop();

			std::cout << "\nLevel " << ++levelCount << ": ";
			bool isEmpty = true;
			while (!prevLevel.empty())
			{
				node = prevLevel.front();
				prevLevel.pop();

				if (node->leftNode != nullptr)
				{
					std::cout << node->leftNode->key << " ";
					currentLevel.push(node->leftNode);
					isEmpty = false;
				}
				if (node->rightNode != nullptr)
				{
					std::cout << node->rightNode->key << " ";
					currentLevel.push(node->rightNode);
					isEmpty = false;
				}
			}
			if (isEmpty)
				std::cout << "this level is empty";
		}
	}

	void constructTree(std::vector<T> keyVector)
	{
		for (const T& data : keyVector)
			insert(data);
	}

	bool empty()
	{
		return root == nullptr;
	}
};