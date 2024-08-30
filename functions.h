#include <fstream>
#include <vector>
#include <functional>

#include "prng.h"

namespace file{
    std::string load_Str(const char* fileName){
        std::ifstream inFile = std::ifstream(fileName);
        if(inFile){
            std::string contents = "";

            while(!inFile.eof()){
                contents += inFile.get();
            }
            contents = contents.substr(0, contents.length()-1);

            inFile.close();
            return contents;
        }else{
            throw std::runtime_error("Unable to load file");
        }
    }

    int* load_IntArr(const char* fileName){
        std::ifstream inFile = std::ifstream(fileName);
        if(inFile){
            inFile.seekg(0, inFile.end);
            uint32_t fileLength = inFile.tellg();
            inFile.seekg(0, inFile.beg);

            int* contents = new int[fileLength];
            contents[0] = fileLength;

            for(unsigned i = 1;!inFile.eof();i++){
                contents[i] = inFile.get();
            }

            inFile.close();
            return contents;
        }else{
            throw std::runtime_error("Unable to load file");
        }
    }
}

void encryptFile(std::string inputFN, std::string outputFN, rand_T seed=0){
    std::cout<<"File "<<inputFN<<" found"<<std::endl;
    std::string contents=file::load_Str(inputFN.c_str());

    PRNG gen=PRNG(seed);

    std::ofstream outFile(outputFN);
    outFile<<encrypt::changeStrBin(contents, gen);
    outFile.close();
}

int encryptDriver(int argc, char** argv){
    std::string str="";

    for(int argumentIdx=1;argumentIdx<argc;argumentIdx++){    //set up program arguments
        std::cout<<argumentIdx+1<<":"<<argv[argumentIdx]<<"\n";

        if(argv[argumentIdx]==std::string("-h")){  //help
            argumentIdx++;
            /**
                TODO: check for specified commands
                if none, general command list, what they do, etc.
            */
            break;
        }

        if(argv[argumentIdx]==std::string("-k")){  //-k denotes the keys
            argumentIdx++;
            //key=argv[a]-'0';
            continue;
        }

        if(argv[argumentIdx]==std::string("-s")){  //
            argumentIdx++;
            str=argv[argumentIdx];
            continue;
        }
       std::cout<<""<<"\n";
    }

    std::cout<<str<<std::endl;
    encryptFile(str, "data/output");
    encryptFile("data/output", "data/outputReversed");  //Test reversability

    return 0;
}

int encryptDriver2(int argc, char** argv){
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
}

void encryptTest(std::string str, std::function<std::string(std::string, PRNG&)> func, rand_T startSeed=0){
    std::cout<<str<<std::endl;
    std::cout<<std::endl<<"vvvvvvvvvvvvvvvvvv"<<std::endl<<std::endl;

    PRNG rng=PRNG(startSeed);
    std::string processedString = func(str, rng);
    std::cout<<processedString<<std::endl;
    std::cout<<std::endl<<"vvvvvvvvvvvvvvvvvv"<<std::endl<<std::endl;

    rng=PRNG(startSeed);
    processedString = func(processedString, rng);
    std::cout<<processedString<<std::endl;

    std::cout<<(str==processedString)<<std::endl;
}
