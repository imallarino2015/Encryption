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

int encryptDriver(int argc,char** argv){
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

    return 0;   ///TODO: GUI
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
