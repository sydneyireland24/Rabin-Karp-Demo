#include <iostream>
#include "RabinKarp.h"
using namespace std;

int main(int argc, char * argv[])
{
    string pattern = argv[1];
    string file = argv[2];
    cout << "RUNNING THE RABIN-KARP ALGORITHM TESTS: " << endl;
    cout << "===================================" << endl;
    RabinKarp RKTest(pattern, file);
    cout << "===================================" << endl << endl;
    return 0;
}