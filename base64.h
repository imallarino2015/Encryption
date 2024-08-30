#include <bits/stdc++.h>
#include <string>
#include <map>

namespace base64{
    std::map<char, unsigned> generate_map(char arr[]){
        std::map<char, unsigned> generated_map;
        for(unsigned idx=0; arr[idx]; idx += 1){
            generated_map.insert({arr[idx], idx});
        }
        return generated_map;
    }

    unsigned get_index(char arr[], char val){
        for(unsigned idx=0; arr[idx]; idx+=1){
            if(arr[idx]==val){
                return idx;
            }
        }
    }

    char DIGIT_ARR[] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
        'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
        'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
        'Y', 'Z',
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
        'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
        'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
        'y', 'z',
        '0', '1', '2', '3', '4', '5', '6', '7',
        '8', '9',
        '+', '/'
    };
    std::map<char, unsigned> DIGIT_MAP = generate_map(DIGIT_ARR);

    std::string encode(std::string bytes){
        std::string encoded = "";
        for(unsigned a=0; a<bytes.length(); a+=3){
            int32_t chunk = 0;
            for(unsigned b=0; b<3; b++)
                chunk += bytes[a+b] << 8*(2-b);

            std::string encodedChunk = "";
            for(unsigned b=0; b<4;b++){
                encodedChunk = DIGIT_ARR[chunk%64] + encodedChunk;
                chunk /= 64;
            }
            encoded += encodedChunk;
        }

        // Padding
        switch(bytes.length()%3) {
            case 1:
                encoded.replace(encoded.length()-2,2,"==");
                break;
            case 2:
                encoded.replace(encoded.length()-1,1,"=");
                break;
        }

        return encoded;
    }

    std::string decode(std::string b64){
        if(b64.length()%4 != 0)
            throw std::runtime_error("Invalid Base64 string");
        b64.erase(remove(b64.begin(), b64.end(), '='), b64.end());

        std::string decoded = "";

        for(unsigned i=0;i<b64.length();i+=4){
            char current_chunk[3] = {0, 0, 0};
            if(i+0<b64.length()){
                char val = DIGIT_MAP[b64[i+0]];
                current_chunk[0] += (val & 0b00111111) << 2;
            }
            if(i+1<b64.length()){
                char val = DIGIT_MAP[b64[i+1]];
                current_chunk[0] += (val & 0b00110000) >> 4;
                current_chunk[1] += (val & 0b00001111) << 4;
            }
            if(i+2<b64.length()){
                char val = DIGIT_MAP[b64[i+2]];
                current_chunk[1] += (val & 0b00111100) >> 2;
                current_chunk[2] += (val & 0b00000011) << 6;
            }
            if(i+3<b64.length()){
                char val = DIGIT_MAP[b64[i+3]];
                current_chunk[2] += (val & 0b00111111) >> 0;
            }
            decoded += current_chunk;
        }

        return decoded;
    }
}
