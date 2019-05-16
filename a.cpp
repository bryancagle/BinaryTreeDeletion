/***************
Name: Bryan Cagle
Course: CSCE 3110.001
Assignment: Programming Assignment 3 - Binary Tree Deletion
Due Date: March 26, 2016 11:59pm

Desciprtion: the purpose of this program is to implement
a program that will remove nodes from a binary tree from the
root (in order to test the effectiveness of deleting nodes with
two children) and measuring the number of recursion and function
calls required.

This program deletes nodes from the largest value in the left subtree
first
***************/

#include <iostream>
#include <cstdlib>

using namespace  std;

class BinaryTree
{
	private:
	
		struct node
		{
			int data;
			node* left;
			node* right;
		};

		node* root;

		void AddLeafPrivate(int data, node* Ptr);
		void PrintInOrderPrivate(node* Ptr);
		void RemoveNodePrivate(int data, node* parent);
		void RemoveRootMatch();
		int FindSmallestPrivate(node* Ptr);
		int FindLargestPrivate(node* Ptr);
		void RemoveMatch(node* parent, node* found, bool left);
	public:
		static int recCount;
		BinaryTree();
		node* CreateLeaf(int data);
		void AddLeaf(int data);
		void PrintInOrder();
		void RemoveNode(int data);
		int FindSmallest();
		int FindLargest();
		int getRoot();
};

int BinaryTree::recCount=0;

int BinaryTree::getRoot()
{
	return root->data;
}
void BinaryTree::RemoveMatch(node* parent, node* found, bool left)
{
	recCount+=1;
	if(root != NULL)
	{
		node* delPtr;
		int foundData = found->data;
		int largestInLeftSubtree;

		//0 children
		if(found->left==NULL&&found->right==NULL)
		{
			delPtr=found;
			left==true ? parent->left = NULL: parent->right = NULL;
			delete delPtr;
			cout << "The node containing data " << foundData << " was removed" << endl;
		}

		//1 child
		else if(found->left == NULL && found->right !=NULL)
		{
			left == true ? parent->left = found->right : parent->right = found->right;
			found->right=NULL;
			delPtr=found;
			delete delPtr;
			cout << "The node containing data " << foundData << " was removed" << endl;
		}
		
		else if(found->right == NULL && found->left !=NULL)
		{
			left == true ? parent->left = found->left : parent->right = found->left;
			found->left=NULL;
			delPtr=found;
			delete delPtr;
			cout << "The node containing data " << foundData << " was removed" << endl;
		}

		//2 children
		else
		{
			largestInLeftSubtree = FindLargestPrivate(found->left); //finds smallest in tree
			RemoveNodePrivate(largestInLeftSubtree, found); //deletes the smallest node in subtree
			found->data = largestInLeftSubtree; //replaces the current data with the smallest in right tree
		}
	}
	else
	{
		cout << "Tree is empty" << endl;
	}
}

int BinaryTree::FindLargestPrivate(node* Ptr)
{
	recCount+=1;
	if(root == NULL)
	{
		cout << "Tree is empty" << endl;
		return -1;
	}
	else
	{
		if(Ptr->right != NULL)
		{
			return FindLargestPrivate(Ptr->right);
		}
		else
		{
			return Ptr->data;
		}
	}
}

int BinaryTree::FindLargest()
{
	return FindLargestPrivate(root);
}

int BinaryTree::FindSmallestPrivate(node* Ptr)
{
	recCount+=1;
	if(root == NULL)
	{
		cout << "Tree is empty" << endl;
		return -1;
	}
	else
	{
		if(Ptr->left != NULL)
		{
			return FindSmallestPrivate(Ptr->left);
		}
		else
		{
			return Ptr->data;
		}
	}
}

int BinaryTree::FindSmallest()
{
	return FindSmallestPrivate(root);
}

void BinaryTree::RemoveRootMatch()
{
	recCount+=1;
	if(root != NULL) //if tree  is empty
	{
		node* delPtr=root;
		int rootData = root->data;
		int largestInLeftSubtree;

		//case where 0 children present
		if(root->left == NULL && root->right == NULL)
		{
			root = NULL;
			delete delPtr;
		}

		//case where 1 child present
		else if(root->left==NULL && root->right != NULL)
		{
			root = root->right;
			delPtr->right = NULL; //disconnecting old root from tree
			delete delPtr;
			cout << "The root node with data " << rootData << " was deleted. " << "new root contains data " << root->data << endl;
		}
		else if(root->right==NULL && root->left != NULL)
		{
			root = root->left;
			delPtr->left = NULL; //disconnecting old root from tree
			delete delPtr;
			cout << "The root node with data " << rootData << " was deleted. " << "new root contains data " << root->data << endl;
		}
		//case where 2 children present
		else
		{
			largestInLeftSubtree = FindLargestPrivate(root->left);
			RemoveNodePrivate(largestInLeftSubtree, root);
			root->data = largestInLeftSubtree;
			cout << "The root data containing data " << rootData << " was overwritten with data " << root->data << endl;
		}
	}
	else
	{
		cout << "Tree is empty" << endl;
	}
}

void BinaryTree::RemoveNode(int data)
{
	RemoveNodePrivate(data,root);
}

void BinaryTree::RemoveNodePrivate(int data, node* parent)
{
	recCount+=1;
	if(root != NULL) //checks if tree is empty
	{
		if(root->data==data) //in case the root is the node to be deleted
		{
			RemoveRootMatch();
		}
		else
		{
			if(data < parent->data && parent->left!=NULL) //if data has a value less the current node, then look down left pointer as long as there is one
			{
				(parent->left->data==data) ?
				RemoveMatch(parent, parent->left,true):
				RemoveNodePrivate(data,parent->left);
			}
			else if(data > parent->data && parent->right!=NULL) //if data has a value less the current node, then look down left pointer as long as there is one
			{
				(parent->right->data==data) ?
				RemoveMatch(parent, parent->right,false):
				RemoveNodePrivate(data,parent->right);
			}
			else
			{
				cout << "The data" << data << " was not found in the tree" << endl;
			}		
		}
	}
	else
	{
		cout << "Tree is empty" << endl;
	}
}

void BinaryTree::PrintInOrder()
{
	PrintInOrderPrivate(root);
}

void BinaryTree::PrintInOrderPrivate(node* Ptr)
{
	if(root != NULL)
	{
		if(Ptr->left != NULL)
		{
			PrintInOrderPrivate(Ptr->left); //always goes left recursively if available
		}
		cout << Ptr->data << " ";
		if(Ptr->right != NULL)
		{
			PrintInOrderPrivate(Ptr->right);
		}
	}
	else
	{
		cout << "The tree is empty" << endl;
	}
}

void BinaryTree::AddLeaf(int data)
{
	AddLeafPrivate(data, root);
}

void BinaryTree::AddLeafPrivate(int data, node* Ptr)
{
	if(root == NULL) //if tree is empty then the root is created
	{
		root = CreateLeaf(data);
	}

	else if(data < Ptr->data) //if data is less than current value
	{
		if(Ptr->left != NULL)
		{
			AddLeafPrivate(data, Ptr->left); //recursively moves down the left pointer
		}
		else //if left pointed isn't pointing at anything
		{
			Ptr->left = CreateLeaf(data);
		}
	}
	else if(data > Ptr->data) //if data is greater than current value
	{
		if(Ptr->right != NULL)
		{
			AddLeafPrivate(data, Ptr->right); //recursively moves down the right pointer
		}
		else //if right pointer isn't pointing at anything
		{
			Ptr->right = CreateLeaf(data);
		}
	}
	else //when data is equal to the current node
	{
		cout << "Value is already in tree" << endl;
	}
}

BinaryTree::BinaryTree()
{
	root = NULL; //makes sure root isn't pointing to anything when tree is created
}

BinaryTree::node* BinaryTree::CreateLeaf(int data)
{
	node* n = new node;
	n->data=data;
	n->left=NULL;
	n->right=NULL;

	return n;
}

int main()
{
	int TreeDatas[15] = {46,21,62,16,34,49,75,3,20,24,42,48,60,70,96};
	BinaryTree tree;
	char menu;
	int rootN,delNode,addNode;
	double runavg=0;

	while(1){
	cout << "\n1:Insert default input sequence then delete each individually from the root: 46,21,62,16,34,49,75,3,20,24,42,48,60,70,96\n2: Add Your Own Leaf\n3: Remove Leaf\n4: Print inorder of tree\nOther: exit program" << endl;
	cout << "\nEnter your choice: ";
	cin >> menu;
	switch(menu)
	{
		case '1':
			for(int i=0;i<15;i++)
			{
				tree.AddLeaf(TreeDatas[i]);
			}
			for(int i=0;i<15;i++)
			{
				rootN=tree.getRoot();
				tree.RemoveNode(rootN);
			}
			cout << "\nTotal number of function calls including recursions: " << tree.recCount << endl << endl;
			tree.recCount=0;
			break;
		case '2': 
				cout << "Enter the data of the node to add: ";
				cin >> addNode;
				tree.AddLeaf(addNode);break;
		case '3': 	
				cout << "Enter the data of the node to delete: ";
				cin >> delNode;
				tree.RemoveNode(delNode);
				cout << "\nTotal number of function calls including recursions: " << tree.recCount << endl << endl;
				tree.recCount=0;
				break;
		case '4': 	tree.PrintInOrder(); cout << "\n" << endl; break;
		default: return 0;
	}
	}
	return 0;
}