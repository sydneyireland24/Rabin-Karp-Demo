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
    bool patternFound = false;

    if(patternLength > textLength)
    {
        cout << "No pattern found - pattern length is longer than text length." << endl;
        return;
    }

    // The value of h would be "pow(d, M-1)%q"
    for (int i = 0; i < patternLength - 1; i++)
    {
        hash = (hash * ASCII) % prime;
        cout << "HASH AT INDEX " << i << ": " << hash << endl;
    }

    cout << endl;
    // Calculate the hash value of pattern and first
    // window of text
    for (int i = 0; i < patternLength; i++)
    {
        hashPattern = (ASCII * hashPattern + pattern[i]) % prime;
        hashText = (ASCII * hashText + text[i]) % prime;
        cout << "HASH PATTERN AT INDEX " << i << ": " << hashPattern << endl;
        cout << "HASH TEXT AT INDEX " << i << ": " << hashText << endl;
    }

    cout << endl;

    // Slide the pattern over text one by one
    for (int i = 0; i <= textLength - patternLength; i++)
    {
        //Check the hash values of current window of text
        //and pattern. If the hash values match then only
        //check for characters on by one
        if ( hashPattern == hashText )
        {
            for (int j = 0; j < patternLength; j++)
            {
                if (text[i + j] != pattern[j])
                {
                    break;
                }

                if (j == patternLength - 1)
                {
                    cout << "Pattern found at index " << i <<endl;
                    patternFound = true;
                }
            }
        }

        // Calculate hash value for next window of text: Remove
        // leading digit, add trailing digit
        if ( i < textLength - patternLength )
        {
            hashText = (ASCII * (hashText - text[i] * hash) + text[i + patternLength]) % prime;

            // We might get negative value of t, converting it
            // to positive
            if (hashText < 0)
                hashText = (hashText + prime);
        }
    }

    if(!patternFound)
        cout << "Pattern was not found in the text" << endl;
}

/* Driver code */
int main()
{
    char text[] = "GEEKS FOR GEEKS";
    char pattern[] = "GEEKS";

    //A large prime number to help prevent integer overflow in hashing
    int primeNum = 503;

    search(pattern, text, primeNum);
    return 0;
}