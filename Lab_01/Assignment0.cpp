
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
void UploadToFile(string, string);
int HigherValue(string, string);

// Linked List
template<class Type>
class Node
{
	public:
		Type data;
		Node<Type> *next;
		Node<Type>(const Type& 	d): data(d), next() {}
		Node<Type>(const Node<Type>& copyNode) : data(copyNode.data),next() {}

	private:
		Node<Type>& operator=(const Node<Type>&);

};

template<class Type>
class LinkedList
{
public:
	Node<Type> * head;
	Node<Type> * tail;

	LinkedList(const LinkedList& LL);
	LinkedList(): head(NULL), tail(NULL) {} ;
	LinkedList(Node<Type> * newNode) : head (newNode), tail(newNode) {};
	~LinkedList();

	void InsertToTail (Type val);
	void InsertToHead (Type val);
	void Print();
	void PrintBackwards();
	void ReadFile(string);
	void WriteFile(string);
	void Swap(Node<Type> *,Node<Type> *,Node<Type> *);
	void OrderList();
};




template<class Type>
LinkedList<Type>::LinkedList(const LinkedList<Type>& LL) : head(NULL), tail(NULL)
{
    const Node<Type> * curr = LL.head;

    if (!head && curr)
    {
        head = new Node<Type>(curr->data);
        tail = head;
        curr = curr->next;
    }

    while (curr)
    {
        Node<Type> * newNode = new Node<Type>(curr->data);
        tail->next = newNode;
        tail = newNode;
        curr = curr->next;
    }
}


template<class Type>
LinkedList<Type>::~LinkedList()
{
    Node<Type> * curr = head;
    while (head)
    {
        head = head->next;
        delete curr;
        curr = head;
    }
}

template<class Type>
void LinkedList<Type>::InsertToTail(Type val)
{
    Node<Type> * newNode = new Node<Type>(val);
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

template<class Type>
void LinkedList<Type>::InsertToHead(Type val)
{
    Node<Type> * newNode = new Node<Type>(val);
    newNode->next = head;
    head = newNode;
    if (head->next == NULL)
        tail = newNode;
}

template<class Type>
void LinkedList<Type>::Print()
{
    Node<Type> * curr = head;
    while (curr)
    {
        cout<<curr->data<<" --> ";
        curr = curr->next;
    }
    cout<<"NULL"<<endl;
}

template<class Type>
void LinkedList<Type>::PrintBackwards()
{
    Node<Type> * curr;
    LinkedList ReversedList(new Node<Type>(head->data));
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
template<class Type>
void LinkedList<Type>::ReadFile(string FileName)
{
	fstream FS;
	
	string output;
	Node<Type> * curr = head;

	FS.open(FileName,fstream::in | fstream::out);
	FS >> output;
	while(!FS.eof() )
	{
		
		Node<Type> * newNode = new Node<Type>(output);
	    newNode->next = head;
	    head = newNode;
	    if (head->next == NULL)
	        tail = newNode;
	    FS >> output;
	}
	FS.close();
	

}

// Puts the List in a file starting with the head.
template<class Type>
void LinkedList<Type>::WriteFile(string FileName)
{
	fstream FS;

	FS.open(FileName,fstream::in | fstream::out | fstream::trunc);

	Node<Type> * curr = head;
    while (curr)
    {
        FS<<curr->data << endl;
        curr = curr->next;
    }
	FS.close();
}

template<class Type>
void LinkedList<Type>::Swap(Node<Type> * first,Node<Type> *second,Node<Type> *third)
{
	if(head == second)
		head = third;
	if(tail == third)
		tail = second;
	first -> next = third;
	second -> next = third->next;
	third -> next = second;
}

template<class Type>
void LinkedList<Type>::OrderList()
{
   	Node<Type> * curr = head;
   	Node<Type> * prev = head;
   	Node<Type> * pnext = head->next;
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
	int l=300,w=3;
	srand(time(0));
	a = RandomParagraph(l,w);
	b = RandomParagraph(l,w);
	c = RandomParagraph(l,w);
	UploadToFile(a, "RandomA.txt");
	UploadToFile(b, "RandomB.txt");
	UploadToFile(c, "RandomC.txt");
	
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

	chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

	chrono::duration<double> time_span = chrono::duration<double>(t2 - t1);
	cout << "It took me " << time_span.count() << " seconds.";
  	cout << endl;




	return 0;
}


// Returns One if string zero is ahead of string one in alphabetical order
// if 1 no swap, if 0 swap

int HigherValue(string zero, string one)
{
	char zero_char,one_char;
	zero_char = zero[0];
	one_char = one[0];
	if(zero_char == one_char)
		return 1;
	else if(zero_char < one_char)
		return 1;
	else if (one_char < zero_char)
		return 0;
	else
		return HigherValue(zero.substr(1,zero.size()), one.substr(1,one.size()) );
}

string RandomParagraph(int NumberOfLines, int LengthOfEachLine)
{
	string Paragraph = "";
	int i;

	for(i=0;i<=(NumberOfLines-1);i++)
	{
		Paragraph = Paragraph + RandomString(LengthOfEachLine) + "\n";
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


void UploadToFile(string text, string FileName)
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

