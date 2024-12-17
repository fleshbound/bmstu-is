//
// Created by sheglar on 04.10.24.
//

#ifndef ENIGMA_H
#define ENIGMA_H

#include <cinttypes>
#include <string>
#include <vector>
#include <bits/unique_ptr.h>

#include "Encoder.h"


class Enigma {
public:
    explicit Enigma(uint8_t size_rotor,
           uint8_t num_rotors,
           const std::vector<uint8_t>& reflector_place,
           const std::vector<std::vector<uint8_t>>& rotors_place,
           const std::vector<uint8_t>& commutator_place,
           const std::string &new_alphabet);
    explicit Enigma(uint8_t size_rotor,
               uint8_t num_rotors,
               const std::vector<uint8_t>& reflector_place,
               const std::vector<std::vector<uint8_t>>& _rotors_place,
               const std::vector<uint8_t>& commutator_place,
               const std::vector<uint8_t>& new_alphabet);

    std::vector<uint8_t> encrypt(std::vector<uint8_t> message);
    std::vector<uint8_t> encrypt(const std::string& message);
    uint8_t encrypt(uint8_t code);
    void encrypt(const std::string& filename_in, const std::string& filenameOut);

private:
    uint8_t _find_rotor(uint8_t num, uint8_t code);
    void _rotor_shift(uint8_t num);
    uint64_t _counter = 0;
    uint8_t _size_rotor;
    uint8_t _num_rotors;
    std::vector<uint8_t> _reflector;
    std::vector<uint8_t> _commutator;
    std::vector<std::vector<uint8_t>> _rotors;
    std::unique_ptr<Encoder> _encoder;
};


#endif //ENIGMA_H