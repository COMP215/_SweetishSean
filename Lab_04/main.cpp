//
//  main.cpp
//  classbst
//
//  Created by Tom Armstrong on 9/19/16.
//  Copyright © 2016 tarmstro. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "binarysearchtree.hpp"
#include "linkedlist.hpp"


void WriteToTree(BinarySearchTree*);
void SearchTree(BinarySearchTree*);

int main(int argc, const char * argv[]) {

    BinarySearchTree* words = new BinarySearchTree();

    WriteToTree(words);
    SearchTree(words);
    // people_names->Insert("gousie");
    // people_names->Insert("bloch");
    // people_names->Insert("armstrong");
    // people_names->Insert("decoste");


    // if(people_names->Search("armstrong"))
    // 	std::cout <<"IT WORKED!"<<endl;

    /*
	LinkedList* people_names = new LinkedList();
	people_names->Insert("gousie");
    people_names->Insert("bloch");
    people_names->Insert("armstrong");
    people_names->Insert("decoste");


    if(people_names->Search("armstrong"))
    	std::cout <<"IT WORKED! 1"<<std::endl;

    people_names->Delete("armstrong");
    if(people_names->Search("armstrong"))
    	std::cout <<"Armstrong Still Strong"<<std::endl;

    */

    
    return 0;
}

void WriteToTree(BinarySearchTree *Tree)
{
    std::string file_one = "foowords.txt";
    std::ifstream file_read;

    file_read.open(file_one.c_str());

    int num_lines = 0;              // Counter for lines in file.
    std::string one_line;

    if (file_read.is_open())
    {
        while (!file_read.eof())
        {
            getline(file_read, one_line);
            Tree->Insert(one_line);
            num_lines++;
        }
    }


}

void SearchTree(BinarySearchTree *Tree)
{
    std::string file_two = "words.txt";
    std::ifstream file_read;

    file_read.open(file_two.c_str());

    int num_lines = 0;              // Counter for lines in file.
    std::string one_line;
    if (file_read.is_open())
    {
        while (!file_read.eof())
        {
            getline(file_read, one_line);
            if(!Tree->Search(one_line))
                std::cout << "not here\n";
            num_lines++;
        }
    }

}

