#include<iostream>

#include"include.h"

using namespace std;

int main(int argc,char** argv){
    string in="",out="output";
    int key=1;
    bool validate=false,hex=false;  //various flags

    for(int a=1;a<argc;a++){    //set up program arguments
        if(argv[a]==(string)"--help"||argv[a]==(string)"-h"){  ///help
            cout<<"Usage: "<<argv[0]<<" [option] <argument>"<<endl
                <<"Available options: \n"
                <<"-i <path>: \t Path/Name of the desired file to encrypt/decrypt \n"
                <<"-o <path>: \t Path/Name of the resultant file \n"
                <<"-k <integer>: \t Give the program a starting key \n"
                <<"-v: \t Verify the correctness of the output files \n"
                <<"-x: \t Create a hexadecimal representation file \n";
            return 0;
        }
        if(argv[a]==(string)"-k"){  ///-k for key
            a++;
            key=toInt(argv[a]);
            continue;
        }
        if(argv[a]==(string)"-i"){  ///-i for the input filename
            a++;
            in=argv[a];
            continue;
        }
        if(argv[a]==(string)"-o"){  ///-o for the output filename
            a++;
            out=argv[a];
            continue;
        }
        if(argv[a]==(string)"-v"){  ///-v for validation
            validate=true;
            continue;
        }
        if(argv[a]==(string)"-x"){  ///-x for hex output
            hex=true;
            continue;
        }
    }

    if(processFile(in,out,key)){
        if(validate){
            cout<<validateFile(in,out,key)<<endl;
        }
        if(hex){
            outputHex(out,"data/hexOut.txt");
        }
    }else{
        rnd(key);
        for(unsigned a=0;a<in.size();a++)
            in[a]^=rnd()%256;
        cout<<in<<endl;
    }
    return 0;   ///TODO: GUI
}