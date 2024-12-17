//
// Created by sheglar on 04.10.24.
//

#ifndef ENCODER_H
#define ENCODER_H

#include <cstdint>
#include <vector>

class Encoder {

public:
    explicit Encoder(uint8_t alphabet_size, std::string new_alphabet);
    explicit Encoder(uint8_t alphabet_size, std::vector<uint8_t> new_alphabet);

    uint8_t encode(uint8_t symbol);
    uint8_t decode(uint8_t code);
private:
    uint8_t size_alpha;
    std::vector<uint8_t> alphabet;
};


#endif //ENCODER_H
