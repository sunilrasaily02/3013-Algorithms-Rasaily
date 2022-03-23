/************************************************************
 *
 *    Author:           Sunil Rasailycom
 *    Email:            Sunilrasaily02@gmail.com
 *    Label:            P03
 *    Title:            Processing in Trie Tree Time
 *    Course:           CMPS 3013
 *    Semester:         Spring 2022
 *    Description:
 *        This software uses a trie data structure to calculate the 
 * time it takes to discover the words and display top ten 
 * results after reading the dictionary terms from a file.
 *    Files:
 *         main.cpp
 *         Timer.hpp
 *         mygetch.hpp
 *         termcolor.hpp
 *         dictionary.txt
 *
 *    Usage:
 *           main.cpp         : driver program
 *             
 *           dictionary.txt   : Input file
 *
 *           
 *
 ****************************************************************/
#include "mygetch.hpp"
#include "termcolor.hpp"
#include "timer.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <list>

using namespace std;

#define RED termcolor::red
#define RESET termcolor::reset
#define BLUE termcolor::blue
#define GREEN termcolor::green


// Define the character size
#define CHAR_SIZE 128

// A class to store a Trie node
class Trie
{
public:
    bool isLeaf;
    Trie* character[CHAR_SIZE];
    int numberOfMatches;
    // Constructor
    Trie()
    {
        numberOfMatches = 0;
        this->isLeaf = false;

        for (int i = 0; i < CHAR_SIZE; i++) {
            this->character[i] = nullptr;
        }
    }

    void insert(string);
    bool deletion(Trie*&, string);
    bool search(string);
    bool haveChildren(Trie const*);
    void display(Trie* root, char str[], int level, string key);

};

// Iterative function to insert a key into a Trie
void Trie::insert(string key)
{
    // start from the root node
    Trie* curr = this;
    for (int i = 0; i < key.length(); i++)
    {
        // create a new node if the path doesn't exist
        if (curr->character[key[i]] == nullptr) {
            curr->character[key[i]] = new Trie();
        }

        // go to the next node
        curr = curr->character[key[i]];
    }

    // mark the current node as a leaf
    curr->isLeaf = true;
}

// Iterative function to search a key in a Trie. It returns true
// if the key is found in the Trie; otherwise, it returns false
bool Trie::search(string key)
{
    
    // return false if Trie is empty
    if (this == nullptr) {
        return false;
    }

    Trie* curr = this;
    
    for (int i = 0; i < key.length(); i++)
    {
        // go to the next node
        curr = curr->character[key[i]];
        
        // if the string is invalid (reached end of a path in the Trie)
        if (curr == nullptr) {
            return false;
        }
    }

    numberOfMatches = 0;

    Trie* temp = curr;
    char arr[20] = {};
    
    cout <<"Key is " << RED << key << RESET << endl;

    display(curr, arr, 0, key); // function to search the Trie recursively 

    cout << "WE found " << RED << numberOfMatches << BLUE <<" matches" <<RESET<< " in the TRIE data_structure" << endl;
     

    // return true if the current node is a leaf and the
    // end of the string is reached
    return curr->isLeaf;
}

// Returns true if a given node has any children
bool Trie::haveChildren(Trie const* curr)
{
    for (int i = 0; i < CHAR_SIZE; i++)
    {
        if (curr->character[i]) {
            return true;    // child found
        }
    }

    return false;
}



void Trie::display(Trie* root, char str[], int level, string key)
{
    // If node is leaf node, it indicates end
    // of string, 
    
        if (root->isLeaf) // if the root is leaf that means there is a word that ends here 
        {
        if (numberOfMatches <= 10) // to print the first 10 matches 
        cout << RED << key << GREEN << str << RESET << endl;
        numberOfMatches++;
        }

    int i;
    for (i = 0; i < CHAR_SIZE; i++)
    {
        // if NON NULL child is found
        // add parent key to str and
        // call the display function recursively
        // for child node
        if (root->character[i])
        {
            str[level] = i;
            display(root->character[i], str, level + 1, key);
        }
    }
}



// Recursive function to delete a key in the Trie
bool Trie::deletion(Trie*& curr, string key)
{
    // return if Trie is empty
    if (curr == nullptr) {
        return false;
    }

    // if the end of the key is not reached
    if (key.length())
    {
        // recur for the node corresponding to the next character in the key
        // and if it returns true, delete the current node (if it is non-leaf)

        if (curr != nullptr &&
            curr->character[key[0]] != nullptr &&
            deletion(curr->character[key[0]], key.substr(1)) &&
            curr->isLeaf == false)
        {
            if (!haveChildren(curr))
            {
                delete curr;
                curr = nullptr;
                return true;
            }
            else {
                return false;
            }
        }
    }

    // if the end of the key is reached
    if (key.length() == 0 && curr->isLeaf)
    {
        // if the current node is a leaf node and doesn't have any children
        if (!haveChildren(curr))
        {
            // delete the current node
            delete curr;
            curr = nullptr;

            // delete the non-leaf parent nodes
            return true;
        }

        // if the current node is a leaf node and has children
        else {
            // mark the current node as a non-leaf node (DON'T DELETE IT)
            curr->isLeaf = false;

            // don't delete its parent nodes
            return false;
        }
    }

    return false;
}
 

int main() {
    char k;                 // holder for character being typed
    string word = "";       // var to concatenate letters to
   
    Trie* tree = new Trie;
    Timer T; // timer 
    fstream file("dictionary.txt");

    T.Start(); // start timimg 
    while (!file.eof())
    {
        string x;
        file >> x;
        tree->insert(x);
    }
     
    T.End(); // end timimg 
     
    // print how mush time it took to load the file 
    cout << "It took " <<RED <<T.NanoSeconds() / 1000000000.0 <<termcolor::reset<< " Seconds to load the file\n\n";
    
    cout << "Type keys and watch what happens. Type capital Z to quit." << endl;

    // While capital Z is not typed keep looping
    while ((k = getch()) != 'Z') {
         
      
        // Tests for a backspace and if pressed deletes
        // last letter from "word".
        if ((int)k == 127) {
            if (word.size() > 0) {
                word = word.substr(0, word.size() - 1);
            }
        }
        else {
            // Make sure a letter was pressed and only letter
            if (!isalpha(k) ) {
                cout << "Letters only!  " << endl;
             
                continue;
            }

            // We know its a letter, lets make sure its lowercase.
            // Any letter with ascii value < 97 is capital so we
            // lower it.
            if ((int)k < 97 ) {
                k += 32;
            }
          
            word += k; // append char to word
        }
        cout << endl;
        T.Start();
        tree->search(word);
        T.End();
        cout << "It to " << BLUE << T.MilliSeconds() / 1000.0 << RESET << " Seconds te search the file for the key " << RED << word << RESET << endl;
    }
    return 0;
}
