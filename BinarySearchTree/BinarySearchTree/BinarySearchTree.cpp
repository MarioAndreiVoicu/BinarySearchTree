#include "BinarySearchTree.h"
#include<iostream>

int main()
{
	BinarySearchTree<int> BST;  //change data type here
	std::vector<int> keyVector = { 20,17,13,18,10,14,25,22,33,30,45 };  //used for constructTree   //change data type here
	BST.constructTree(keyVector);

	int option;
	int key;                //change data type here
	std::cout << "0 for exit\n1 for insert\n2 for deleteKey\n3 for erase\n4 for max\n5 for min\n6 for successor\n7 for predecessor\n8 for find\n9 for display InOrder\n10 for display PreOrder\n11 for display PostOrder\n12 for display LevelOrder\n13 for empty\n14 for clear\n";
	std::cout << "Chose an option: ";
	while (std::cin >> option && option != 0)
	{
		switch (option)
		{
		case 0:
			break;
		case 1:
			std::cout << "What key do you want to insert: ";
			std::cin >> key;
			BST.insert(key);
			break;
		case 2:
			std::cout << "What key do you want to delete: ";
			std::cin >> key;
			BST.deleteKey(key);
			break;
		case 3:
			std::cout << "What key do you want to delete: ";
			std::cin >> key;
			if (BST.find(key))
				BST.erase(BST.find(key));
			else
				std::cout << "There is no node with the key " << key << " in the BST\n";
			break;
		case 4:
			std::cout << "Insert the key for the subtree where the search for the max key will be made: ";
			std::cin >> key;
			if (BST.find(key) != nullptr)
				std::cout << "The max value from the subtree is " << BST.max(BST.find(key))->key << "\n";
			else
				std::cout << "The key is not in the BST\n";
			break;
		case 5:
			std::cout << "Insert the key for the subtree where the search for the min key will be made: ";
			std::cin >> key;
			if (BST.find(key) != nullptr)
				std::cout << "The min value from the subtree is " << BST.min(BST.find(key))->key << "\n";
			else
				std::cout << "The key is not in the BST\n";
			break;
		case 6:
			std::cout << "Insert the key for which you want to find the successor: ";
			std::cin >> key;
			if (BST.find(key))
			{
				if (BST.successor(BST.find(key)) != nullptr)
					std::cout << "The successor of " << key << " is " << BST.successor(BST.find(key))->key << "\n";
				else
					std::cout << "The node with the key " << key << " does not have a successor\n";
			}
			else
				std::cout << "The key is not in the BST\n";
			break;
		case 7:
			std::cout << "Insert the key for which you want to find the predecessor: ";
			std::cin >> key;
			if (BST.find(key))
			{
				if (BST.predecessor(BST.find(key)) != nullptr)
					std::cout << "The predecessor of " << key << " is " << BST.predecessor(BST.find(key))->key << "\n";
				else
					std::cout << "The node with the key " << key << " does not have a predecessor\n";
			}
			else
				std::cout << "The key is not in the BST\n";
			break;
		case 8:
			std::cout << "What key do you want to find: ";
			std::cin >> key;
			if (BST.find(key))
				std::cout << "The key is in the BST\n";
			else
				std::cout << "The key is not in the BST\n";
			break;
		case 9:
			std::cout << "InOrder display: ";
			BST.displayInOrder();
			std::cout << "\n";
			break;
		case 10:
			std::cout << "PreOrder display: ";
			BST.displayPreOrder();
			std::cout << "\n";
			break;
		case 11:
			std::cout << "PostOrder display: ";
			BST.displayPostOrder();
			std::cout << "\n";
			break;
		case 12:
			std::cout << "LevelOrder display\n";
			BST.displayLevelOrder();
			std::cout << "\n";
			break;
		case 13:
			if (BST.empty())
				std::cout << "The BST is empty\n";
			else
				std::cout << "The BST is not empty\n";
			break;
		case 14:
			BST.clear();
			break;
		default:
			std::cout << "Invalid option\n";
		}
		std::cout << "Insert an option: ";
	}

	BST.clear();
	return 0;
}