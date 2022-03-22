
/************************************************************
 * Author:           Sunil Rasaily
*  Email:            Sunilrasaily02@gmail.com
*  Label:            06-P02
*  Title:            Processing in Linear Time
*  Course:           CMPS-3013
*  Semester:         Spring 2022
*
*  Description:
*        
*
*  Usage:
*        g++ main.cpp -o main
         ./main
*
*  Files:           
* main.cpp
* List.hpp
* timer.hpp
* mygetch.hpp
* termcolor.hpp * dictionary.txt
* 
* ************************************************************************/
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

class wordNods {
    list<string> words; // list to store the words    
    int numberOfwords; // to store number of words in the list 
  
public:
    // constructor to set the the numberofwords to zero 
    wordNods()
    {
        numberOfwords = 0;
    }

    // this function will take the file name as parameter 
    // and will open it and load the words inside it 
    bool loadFile(string file_name)
    {
        fstream file(file_name);
        if (!file.is_open())
        {
            return false;
        }

        while (!file.eof())
        {
            string x;
            file >> x;
            numberOfwords++;
            words.push_back(x);
        }

        file.close();
        cout << "There is " <<BLUE <<numberOfwords<<RESET << " words in the file\n\n";


        return true;
    }

    // function to find the mathces
    void findMatches(string substr)
    {
        int numberOfMatches;
        list<string>  matches; // list to store the matches
        Timer T; // timer 
        numberOfMatches = 0; // set number of matches to zero 

        T.Start(); // start timer 
           for (auto &x : words) 
            {
               if (x.substr(0, substr.size()) == substr) // check if the substr is found in the begining of the word
               {
                   numberOfMatches++;
                   if(numberOfMatches<=10)
                   matches.push_back(x);
               }
            }
           T.End(); // end timer
           cout << RED << substr << endl;

           cout << numberOfMatches <<RESET<< " found in " <<BLUE <<T.MilliSeconds() / 1000.0 << RESET<<" Seconds\n";

            for(auto &x: matches) // print the first 10 matches 
           cout << RED << substr <<RESET << GREEN << x.substr(substr.size()) << " ";
            cout << endl;
    }
};


int main() {
    char k;                 // holder for character being typed
    string word = "";       // var to concatenate letters to
   
    wordNods node;
    Timer T; // timer 

    T.Start(); // start timimg 

    node.loadFile("dictionary.txt"); // load file   

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
        node.findMatches(word);
       
    }
    return 0;
}
