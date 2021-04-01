#ifndef RABIN_KARP_DEMO_RABINKARP_H
#define RABIN_KARP_DEMO_RABINKARP_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <chrono>

using namespace std;
using namespace std::chrono;

class RabinKarp{
    private:
        int ASCII = 256; //total possible number of characters that could be in a char []
        int primeNum = 503; //A large prime number to help prevent integer overflow in hashing
        string pattern; //the pattern you want to search for in a particular text
        string fileName; //the file that you will get text from
        int numTests; //the number of times the algorithm will run and time
        ifstream inFS; //file input stream

    public:
        RabinKarp() = default; //default constructor

        /**
         * @purpose: constructor to initialize the RabinKarp Object
         * @param pattern: the pattern you want to search for in a particular text
         */
        RabinKarp(string pattern, string fileName)
        {
            this->fileName = fileName;

            cout << "Running small examples..." << endl;
            runSmallTests();
            cout << "File search with pattern " << pattern << endl;
            const char * searchPattern = pattern.c_str();
            const char * searchText = getText();
            search(searchPattern, searchText);
        }

        /**
         * @purpose: gets text from a file for pattern searching
         * @return the text from the file
         */
        const char * getText()
        {
            inFS.open(fileName);
            if(!inFS.is_open())
            {
                cout << "ERROR OPENING " << fileName << endl;
                exit(1);
            }
            string fullString = "";
            string stringPart;
            while(!inFS.eof())
            {
                getline(inFS, stringPart);
                fullString += stringPart;
            }
            inFS.close();
            return fullString.c_str();
        }

        void runSmallTests(){
            /**
             * EXAMPLE 1
             * A pattern should be found at index 0 and index 11
             */
            char pattern1[] = "CS";
            char text1[] = "CS2341 AND CS3353";
            cout << "======================================================" << endl;
            cout << "Running test with pattern " << pattern1 << " and text " << text1 << endl;
            search(pattern1, text1);
            cout << "======================================================" << endl;

            /**
             * EXAMPLE 2
             * No pattern should be found since the pattern is longer than the text
             */
            char pattern2[] = "Hello World!!";
            char text2[] = "Hello World";
            cout << "Running test with pattern " << pattern2 << " and text " << text2 << endl;
            search(pattern2, text2);
            cout << "======================================================" << endl;

            /**
             * EXAMPLE 3
             * No pattern should be found, since the algorithm is case-sensitive
             */
            char pattern3[] = "DOGS";
            char text3[] = "Buster and Winston are the best dogs";
            cout << "Running test with pattern " << pattern3 << " and text " << text3 << endl;
            search(pattern3, text3);
            cout << "======================================================" << endl;

            /**
             * EXAMPLE 4
             * Only one instance of the pattern should be found at index 5
             */
            char pattern4[] = "shot";
            char text4[] = "Han shot first";
            cout << "Running test with pattern " << pattern4 << " and text " << text4 << endl;
            search(pattern4, text4);
            cout << "======================================================" << endl;
        }

        /**
         * @purpose: runs the Rabin-Karp algorithm for a pattern and text
         * @param pattern - the pattern you are looking for in a particular text
         * @param text - the text that you are parsing to find a particular pattern
         * @return none
         * @source Geeksforgeeks
         */
        void search(const char pattern[], const char text[])
        {
            int patternLength = strlen(pattern); //the length of the pattern
            int textLength = strlen(text); //the length of the text that may or may not contain the pattern
            int hashPattern = 0; //hash value for pattern
            int hashText = 0; //hash value for txt
            int hash = 1; //not sure what this does yet
            bool patternFound = false; //bool flag on whether or not a pattern has been found

            //stops the algorithm is the pattern is longer than the text
            if(patternLength > textLength)
            {
                cout << "No pattern found - pattern length is longer than text length." << endl;
                return;
            }

            for (int i = 0; i < patternLength - 1; i++)
                hash = (hash * ASCII) % primeNum;

            //calculates the hash value of the pattern and first text window
            for (int i = 0; i < patternLength; i++)
            {
                hashPattern = (ASCII * hashPattern + pattern[i]) % primeNum;
                hashText = (ASCII * hashText + text[i]) % primeNum;
            }

            //slide the pattern over each text window
            for (int i = 0; i <= textLength - patternLength; i++)
            {
                //Check the hash values of current window of text
                //and pattern. If the hash values match then only
                //check for characters on by one
                if ( hashPattern == hashText )
                {
                    for (int j = 0; j < patternLength; j++)
                    {
                        //if the characters aren't equal,
                        //there's been a rare instance where
                        //the window has the same
                        //hash value as the pattern,
                        //but not the same characters
                        if (text[i + j] != pattern[j])
                            break;

                        //if we've gone through the whole pattern without
                        //unequal characters, a match is confirmed!
                        if (j == patternLength - 1)
                        {
                            cout << "Pattern found at index " << i << endl;
                            patternFound = true;
                        }
                    }
                }

                //Calculate hash value for next window of text:
                //Remove leading digit, add trailing digit
                if ( i < textLength - patternLength )
                {
                    hashText = (ASCII * (hashText - text[i] * hash) + text[i + patternLength]) % primeNum;

                    //if we have a case where the hash text is negative,
                    //we'll make it positive
                    if (hashText < 0)
                        hashText = (hashText + primeNum);
                }
            }

            if(!patternFound)
                cout << "Pattern was not found in the text" << endl;
        }
};
#endif //RABIN_KARP_DEMO_RABINKARP_H