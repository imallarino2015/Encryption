#ifndef PRNG_H
#define PRNG_H

#include <chrono>

typedef uint64_t rand_T;

template<class t>
t bitwiseRotate(t val,bool dir=false,int amt=1){
    if(dir)
        val=(val<<amt)|(val>>(sizeof(val)*8-amt));    //rotate left
    else
        val=(val>>amt)|(val<<(sizeof(val)*8-amt));    //rotate right
    return val;
}

class PRNG{
    public:
        PRNG();
        PRNG(rand_T);
        virtual ~PRNG();
//        void setSeed(rand_T seed) {randNum=seed;}
        rand_T getNumber() {return randNum;}
        rand_T randXSA();
        rand_T randMSG();
        rand_T randLCG();
        rand_T randMTG();
    protected:
    private:
        rand_T randNum;
};

PRNG::PRNG(){
    randNum = (rand_T)std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
}

PRNG::PRNG(rand_T seed){
    randNum=seed;
}

PRNG::~PRNG()
{

}

rand_T PRNG::randXSA(){  //Xor-Shift-Add generator
    randNum=(randNum^bitwiseRotate(randNum))+0x9696;
    return randNum;
}

rand_T PRNG::randLCG(){   //Linear congruent generator
    const rand_T c=35276223423553;
    const rand_T a=2233;
    const rand_T m=18446744073709551557;
    randNum=(c*randNum+a)%m;
    return randNum;
}

rand_T PRNG::randMSG(){  //Middle square generator
    //Safe max digits:9
    randNum*=randNum;
    auto shaveNum=randNum/100000000000000;
    randNum/=shaveNum;
    randNum%=shaveNum;
    return randNum;
}

rand_T PRNG::randMTG(){   //Mersenne twister generator
    return randNum;
}

#endif // PRNG_H
