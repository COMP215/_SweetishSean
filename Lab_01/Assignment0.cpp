
#include <fstream>  //  To take the words from the file to put into the array
#include <iostream>	//  This is to retrive information from the user
#include <cstdlib>
#include <ctime>
#include <assert.h>
#include <chrono>

using namespace std; //  Usual

char RandomChar();
string RandomString(int);
string RandomParagraph(int, int);
void Uploadtofile(string, string);
int HigherValue(string, string);

// Linked List
template<class type>
class Node
{
	public:
		type data;
		Node<type> *next;
		Node<type>(const type& 	d): data(d), next() {}
		Node<type>(const Node<type>& copyNode) : data(copyNode.data),next() {}

	private:
		Node<type>& operator=(const Node<type>&);

};

template<class type>
class LinkedList
{
public:
	Node<type> * head;
	Node<type> * tail;

	LinkedList(const LinkedList& LL);
	LinkedList(): head(NULL), tail(NULL) {} ;
	LinkedList(Node<type> * newNode) : head (newNode), tail(newNode) {};
	~LinkedList();

	void InsertToTail (type val);
	void InsertToHead (type val);
	void print();
	void printBackwards();
	void Insert_lexicographically (type val);
	void ReadFile(string);
	void WriteFile(string);
	void Swap(Node<type> *,Node<type> *,Node<type> *);
	void OrderList();
};




template<class type>
LinkedList<type>::LinkedList(const LinkedList<type>& LL) : head(NULL), tail(NULL)
{
    const Node<type> * curr = LL.head;

    if (!head && curr)
    {
        head = new Node<type>(curr->data);
        tail = head;
        curr = curr->next;
    }

    while (curr)
    {
        Node<type> * newNode = new Node<type>(curr->data);
        tail->next = newNode;
        tail = newNode;
        curr = curr->next;
    }
}


template<class type>
LinkedList<type>::~LinkedList()
{
    Node<type> * curr = head;
    while (head)
    {
        head = head->next;
        delete curr;
        curr = head;
    }
}

template<class type>
void LinkedList<type>::InsertToTail(type val)
{
    Node<type> * newNode = new Node<type>(val);
    if (tail == NULL)
    {
        newNode->next = tail;
        tail = newNode;
        head = newNode;
        return;
    }
    tail->next = newNode;
    tail = tail->next;
}

template<class type>
void LinkedList<type>::InsertToHead(type val)
{
    Node<type> * newNode = new Node<type>(val);
    newNode->next = head;
    head = newNode;
    if (head->next == NULL)
        tail = newNode;
}

template<class type>
void LinkedList<type>::print()
{
    Node<type> * curr = head;
    while (curr)
    {
        cout<<curr->data<<" --> ";
        curr = curr->next;
    }
    cout<<"NULL"<<endl;
}

template<class type>
void LinkedList<type>::printBackwards()
{
    Node<type> * curr;
    LinkedList ReversedList(new Node<type>(head->data));
    curr = head->next;
    while (curr)
    {
        ReversedList.insertToHead(curr->data);
        curr = curr->next;
    }

    curr = ReversedList.head;
    while (curr)
    {
        cout<<curr->data<<" --> ";
        curr = curr->next;
    }
    cout<<"NULL\n";
}

// Puts the Characters in the File in a List. First line is the end of the list
template<class type>
void LinkedList<type>::ReadFile(string FileName)
{
	fstream FS;
	
	string temp;
	Node<type> * curr = head;

	FS.open(FileName,fstream::in | fstream::out);
	FS >> temp;
	while(!FS.eof() )
	{
		
		Node<type> * newNode = new Node<type>(temp);
	    newNode->next = head;
	    head = newNode;
	    if (head->next == NULL)
	        tail = newNode;
	    FS >> temp;
	}
	FS.close();
	

}

// Puts the List in a file starting with the head.
template<class type>
void LinkedList<type>::WriteFile(string FileName)
{
	fstream FS;

	FS.open(FileName,fstream::in | fstream::out | fstream::trunc);

	Node<type> * curr = head;
    while (curr)
    {
        FS<<curr->data << endl;
        curr = curr->next;
    }
	FS.close();
}

template<class type>
void LinkedList<type>::Swap(Node<type> * a,Node<type> *b,Node<type> *c)
{
	if(head == b)
		head = c;
	if(tail == c)
		tail = b;
	a-> next = c;
	b-> next = c->next;
	c-> next = b;
}

template<class type>
void LinkedList<type>::OrderList()
{
   	Node<type> * curr = head;
   	Node<type> * prev = head;
   	Node<type> * pnext = head->next;
   	int changed = 0;
    while (pnext)
    {
        if(!HigherValue(curr->data,pnext->data))
         	{
         		Swap(prev,curr,pnext);
         		changed = 1;
         		prev = pnext;
         		pnext = curr->next;
         	}
        else
        {
        	prev = curr;
	        curr = pnext;
	        pnext = pnext ->next;
        }
    }
    if(changed)
    	OrderList();
}











// THIS IS THE MAIN FUNCTION


int main ()
{
	chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	// Create the Random String FIle
	string a,b,c;
	int l=30000,w=3;
	srand(time(0));
	a = RandomParagraph(l,w);
	b = RandomParagraph(l,w);
	c = RandomParagraph(l,w);
	Uploadtofile(a, "RandomA.txt");
	Uploadtofile(b, "RandomB.txt");
	Uploadtofile(c, "RandomC.txt");
	
	LinkedList<string> LL1,LL2,LL3;
	LL1.ReadFile("RandomA.txt");
	LL1.OrderList();
	LL1.WriteFile("OrderedRandomA.txt");
	LL2.ReadFile("RandomA.txt");
	LL2.OrderList();
	LL2.WriteFile("OrderedRandomB.txt");
	LL3.ReadFile("RandomA.txt");
	LL3.OrderList();
	LL3.WriteFile("OrderedRandomC.txt");

	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> time_span = std::chrono::duration<double>(t2 - t1);
	cout << "It took me " << time_span.count() << " seconds.";
  	cout << endl;




	return 0;
}


// Returns One if string zero is ahead of string one in alphabetical order
// if 1 no swap, if 0 swap

int HigherValue(string zero, string one)
{
	char z_zero,o_zero;
	z_zero = zero[0];
	o_zero = one[0];
	if(z_zero == o_zero)
		return 1;
	else if(z_zero < o_zero)
		return 1;
	else if (o_zero < z_zero)
		return 0;
	else
		return HigherValue(zero.substr(1,zero.size()), one.substr(1,one.size()) );
}

string RandomParagraph(int NumberofLines, int LengthofEachLine)
{
	string Paragraph = "";
	int i;

	for(i=0;i<=(NumberofLines-1);i++)
	{
		Paragraph = Paragraph + RandomString(LengthofEachLine) + "\n";
	}

	return Paragraph;
}


string RandomString(int length)
{
	string RandomStr = "";
	int i;

	for(i=0;i<=(length-1);i++)
	{
		RandomStr = RandomStr + string(1, RandomChar());

	}

	return RandomStr;
}



// outputs a random alphabet character - can be changed later to add more options

char RandomChar()
{
	char character;

	
	character = 97+ rand()%25;

	return character;
}


void Uploadtofile(string text, string FileName)
{

	fstream FS;
	FS.open (FileName,fstream::in | fstream::out |fstream::trunc);
	FS << text;
	FS.close();


}








// I have abided by the Wheaton College Honor Code in this assignment.
//
//
//
//
// Sean Weinstein

