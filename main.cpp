#include <iostream>
#include <cstring>

using namespace std;

/**
 * @purpose:
 * @param pattern - the pattern you are looking for in a particular text
 * @param text - the text that you are parsing to find a particular pattern
 * @param prime - a large prime number to help prevent integer overflow in hashing
 */
void search(char pattern[], char text[], int prime)
{
    int ASCII = 256; //total possible number of characters that could be in a char []
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
        hash = (hash * ASCII) % prime;

    //calculates the hash value of the pattern and first text window
    for (int i = 0; i < patternLength; i++)
    {
        hashPattern = (ASCII * hashPattern + pattern[i]) % prime;
        hashText = (ASCII * hashText + text[i]) % prime;
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
            hashText = (ASCII * (hashText - text[i] * hash) + text[i + patternLength]) % prime;

            //if we have a case where the hash text is negative,
            //we'll make it positive
            if (hashText < 0)
                hashText = (hashText + prime);
        }
    }

    if(!patternFound)
        cout << "Pattern was not found in the text" << endl;
}

int main()
{
    //A large prime number to help prevent integer overflow in hashing
    int primeNum = 503;

    /**
     * EXAMPLE 1
     */
    char text1[] = "CS2341 AND CS 3353";
    char pattern1[] = "CS";
    search(pattern1, text1, primeNum);
    cout << endl;

    /**
     * EXAMPLE 2
     */
    char text2[] = "Hello World";
    char pattern2[] = "Hello World!";
    search(pattern2, text2, primeNum);
    cout << endl;

    /**
     * EXAMPLE 3
     */
    char text3[] = "Han shot first";
    char pattern3[] = "shot";
    search(pattern3, text3, primeNum);
    cout << endl;

    /**
     * EXAMPLE 4
     */
    char text4[] = "Buster and Winston are the best DOGS";
    char pattern4[] = "dog";
    search(pattern4, text4, primeNum);
    cout << endl;

    return 0;
}