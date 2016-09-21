//
//  linkedlist.cpp
//  demo
//
//  Created by Tom Armstrong on 9/19/16.
//  Copyright © 2016 tarmstro. All rights reserved.
//

#include "linkedlist.hpp"
#include <iostream>
#include <string>
using namespace std;

NodeLL::NodeLL()
{
	// Sets values to NULL or ""
	data_ = "";
	Next_ = NULL;
}

NodeLL::NodeLL(string value)
{
	// Sets Next to NULL and data to passed in value
	data_ = value;
	Next_ = NULL;
}

LinkedList::LinkedList()
{
	// Sets values to NULL or ""
	Root_ = NULL;
	Tail_ = NULL;

}

bool LinkedList::Insert(string value)
{
	if(Tail_!=NULL){
		NodeLL* temp = new NodeLL(value);
		Tail_->Next_ = temp;
		Tail_ = Tail_->Next_;
	}else{
		Tail_ = new NodeLL(value);
	}
	if(Root_ == NULL)
		Root_ = Tail_;
	return true;
}

bool LinkedList::Search(string value)
{
	NodeLL* curr = Root_;
	while(curr != NULL){
		if(curr->data_ == value)
		{
			cout<< "Found\n";
			return true;
		}else
		{
			curr = curr->Next_;
		}
		
	}
	cout << "Did not find the value!!\n";
	return false;
}

bool LinkedList::Delete(string value)
{
	NodeLL* curr = Root_;
	NodeLL* prev = Root_;
	while(curr != NULL){
		if(curr->data_ == value)
		{
			cout<< "Found\n";
			prev->Next_ = prev->Next_->Next_;
			return true;
		}else
		{
			prev = curr;
			curr = curr->Next_;
		}
		
	}
	cout << "Did not find the value!!\n";
	return false;
}