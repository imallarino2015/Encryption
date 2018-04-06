#include<fstream>
#include<string>

typedef unsigned long long randNum_t;

randNum_t rnd(randNum_t seed=0){
    static randNum_t rand=0;
    const unsigned SHIFT=25,
        BOUND=8*sizeof(rand)-1;
    if(seed)
        rand=seed;
    else{
        rand^=(rand<<(SHIFT%BOUND+1))|
            (rand>>(BOUND-SHIFT%BOUND));
        rand+=0xC5C5;
    }
    return rand;
}

int toInt(std::string str){
    int num=0;
    for(int a=0;str[a];a++){
        if('0'>str[a]||str[a]>'9')
            return 0;
        num*=10;
        num+=str[a]-'0';
    }
    return num;
}

std::string toHex(unsigned num,int base=16){
    std::string hex="";

    while(num){
        if(num%base<=9)
            hex=static_cast<char>((num%base)+'0')+hex;
        else
            hex=static_cast<char>((num%base)-10+'A')+hex;
        num/=base;
    }

    return hex;
}

std::string extractString(std::ifstream& in){
    std::string currentLine,str;
    while(!in.eof()){
        getline(in,currentLine);
        str+=in.eof()?currentLine:currentLine+'\n';
    }
    return str;
}

bool processFile(std::string ifName,std::string ofName,int key){
    std::ifstream inFile(ifName);
    if(inFile){
        std::ofstream outFile(ofName);
        std::string data=extractString(inFile);

        rnd(key);
        for(unsigned a=0;a<data.size();a++)
            outFile<<static_cast<char>(static_cast<int>(data[a])^rnd()%256);

        inFile.close();
        outFile.close();
        return true;
    }
    return false;
}

bool validateFile(std::string originalName,std::string processedName,int key){
    std::ifstream originalFile(originalName);
    std::ifstream processedFile(processedName);

    if(originalFile&&processedFile){
        std::string originalData=extractString(originalFile);
        std::string processedData=extractString(processedFile);

        if(originalData.size()==processedData.size()){
            rnd(key);
            for(unsigned a=0;a<originalData.size();a++)
                if(originalData[a]!=static_cast<char>(static_cast<int>(processedData[a])^rnd()%256))
                    return false;
        }else{
            return false;
        }
    }else
        return false;

    return true;
}

bool outputHex(std::string ifName,std::string ofName){
    std::ifstream inFile(ifName);
    if(inFile){
        std::ofstream outFile(ofName);
        std::string data=extractString(inFile);

        for(unsigned a=0;a<data.size();a++)
            outFile<<toHex(static_cast<unsigned char>(data[a]))<<(a<data.size()-1?" ":"");

        inFile.close();
        outFile.close();
        return true;
    }
    return false;
}