#include <iostream>
#include <stdlib.h>
using namespace std;

class Node
{
public:
	Node();
	int data;
	Node* left;
	Node* right;

};

class Tree
{
public:
	Tree();
	void AddToTree(Node*, Node*);
	void FakeAddToTree(int);
	void PrintTree(Node*);
	void FakePrintTree();
private:
	Node* head;


};

Node::Node()
{
	data = 0;
	left = NULL;
	right = NULL;
}

Tree::Tree()
{
	head = NULL;

}

void Tree::AddToTree(Node* new_value, Node *curr)
{

	if(head == NULL)
	{
		head = new_value;
	}else
	{
		if(new_value->data < curr->data)
			if(curr->left == NULL)
			{
				curr->left = new_value;
			}
			else 
			{
				AddToTree(new_value,curr->left);
			}
		else if( new_value->data > curr ->data)
		{
			if(curr->right == NULL)
			{
				
				curr->right = new_value;
			}
			else
			{
				AddToTree(new_value,curr->right);
			}
		}
	}
}


void Tree::FakeAddToTree(int new_value)
{
	Node *new_node= new Node();
	new_node->data = new_value;
	Node *curr= new Node();
	curr = head;
	AddToTree(new_node,curr);


}


void Tree::PrintTree( Node *curr)
{
	if((curr->left == NULL) and (curr->right == NULL))
		cout << curr->data << endl;
	else
	{
		if (curr->left != NULL)
		{
			PrintTree(curr->left);
			cout << curr->data << endl;
		}else
		{
			cout << curr->data <<endl;
		}
		if(curr->right != NULL)
		{
			PrintTree(curr->right);
		}
	}
}
void Tree::FakePrintTree()
{
	Node *curr= new Node();
	curr = head;
	PrintTree(curr);


}

int main()
{
	Tree t;
	t.FakeAddToTree(77);
	t.FakeAddToTree(3);
	t.FakeAddToTree(4);
	t.FakeAddToTree(50);
	t.FakePrintTree();

	return 0;
}


