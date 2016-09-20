#include <iostream>
#include <stdlib.h>
using namespace std;

class Node
{
public:
	Node();
	string data;
	Node* next;

};

class LinkedList
{
public:
	void Delete_Last();
	void Add_Last(string);
	void PrintOut();
	LinkedList();
private:
	Node* header;
	Node* tail;

};



LinkedList::LinkedList()
{
	header = NULL;
	tail = NULL;

}
void LinkedList::Add_Last(string new_data)
{
	if(tail != NULL) {
		Node* new_node = new Node();

		new_node->data = new_data;

		tail->next = new_node;
		tail = new_node;

	}else{

		Node* new_node = new Node();
		new_node->data = new_data;
		tail = new_node;
		header = new_node;
	}
}

void LinkedList::PrintOut()
{	
	Node *cur;

	cur = header;

	while(cur)
	{
		cout << cur->data << endl;
		cur = cur->next;
	}


}


Node::Node()
{
	data = "";
	next = NULL;

}

int main() 
{
	LinkedList l;
	//Node node1;

	l.Add_Last("obj 1");
	l.Add_Last("obj 2");
	l.Add_Last("obj 3");
	l.PrintOut();

	return 0;
}