#include<iostream>

#include "encrypt.h"
#include "base64.h"
#include "prng.h"
#include "functions.h"

using namespace std;

int main(int argc,char** argv){
    string startingStr="";
    for(unsigned char a=0x20;a<0x7f;a++)
        startingStr += (char)a;
    startingStr += "\t\n";

    string testStr = "";
    for(unsigned a = 0; a < 1; a++)
        testStr += startingStr;

    cout << testStr << endl;

    string processedString;
    PRNG rng;
    cout << "------------------------------------------" << endl;
    encryptTest(testStr, &encrypt::changeStrBin);
    cout << "------------------------------------------" << endl;
    
    return 0;   ///TODO: GUI
}
