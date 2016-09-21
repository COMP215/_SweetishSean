//
//  linkedlist.hpp
//  demo
//
//  Created by Tom Armstrong on 9/19/16.
//  Copyright © 2016 tarmstro. All rights reserved.
//

#ifndef linkedlist_hpp
#define linkedlist_hpp

#include <stdio.h>
#include <string>


class NodeLL
{
public:
	NodeLL();
	NodeLL(std::string);
	std::string data_;	// Holds data in the node
	NodeLL* Next_;		// Pointer attached to the node

};


class LinkedList
{
public:
	LinkedList();
	bool Insert(std::string);
	bool Search(std::string);
	bool Delete(std::string);
	NodeLL* Root_;		// Root of linked list
	NodeLL* Tail_;		// Tail of linked list


};


#endif /* linkedlist_hpp */