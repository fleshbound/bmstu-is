//
// Created by sheglar on 04.10.24.
//

#include <string>
#include "Encoder.h"

#include <stdexcept>

Encoder::Encoder(uint8_t alphabet_size, std::string new_alphabet) : size_alpha{alphabet_size} {
    for (int i = 0; i < size_alpha; i++)
        alphabet.push_back(new_alphabet[i]);
}

Encoder::Encoder(uint8_t alphabet_size, std::vector<uint8_t> new_alphabet) : size_alpha{alphabet_size} {
    for (int i = 0; i < size_alpha; i++)
        alphabet.push_back(new_alphabet[i]);
}

uint8_t Encoder::encode(uint8_t symbol) {
    for (int i = 0; i < size_alpha; ++i)
        if (alphabet[i] == symbol)
            return i;
    return symbol;
}

uint8_t Encoder::decode(uint8_t code) {
    if (code >= size_alpha) {
        return code;
    }
    return alphabet[code];
}
