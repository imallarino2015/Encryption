#include <string>

#include "prng.h"

namespace encrypt{
    std::string changeStrBin(std::string toChange, PRNG& generator){
        for(unsigned a=0;a<toChange.size();a++){
            toChange[a]=toChange[a]^(generator.randXSA()%256);
        }
        return toChange;
    }
}
