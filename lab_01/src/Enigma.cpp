//
// Created by sheglar on 04.10.24.
//

#include "Enigma.h"

#include <filesystem>
#include <iostream>
#include <fstream>

Enigma::Enigma(uint8_t size_rotor,
               uint8_t num_rotors,
               const std::vector<uint8_t>& reflector_place,
               const std::vector<std::vector<uint8_t>>& _rotors_place,
               const std::vector<uint8_t>& commutator_place,
               const std::string &new_alphabet) :
    _size_rotor{size_rotor}, _num_rotors{num_rotors} {

    _reflector.reserve(_size_rotor);
    for (const auto &reflect: reflector_place) {
        _reflector.push_back(reflect);
    }
    for (const auto &rotor: _rotors_place) {
        _rotors.push_back(rotor);
    }
    for (const auto &comm: commutator_place) {
        _commutator.push_back(comm);
    }

    Encoder encoder(new_alphabet.size(), new_alphabet);
    this->_encoder = std::make_unique<Encoder>(encoder);
}


Enigma::Enigma(uint8_t size_rotor,
               uint8_t num_rotors,
               const std::vector<uint8_t>& reflector_place,
               const std::vector<std::vector<uint8_t>>& _rotors_place,
               const std::vector<uint8_t>& commutator_place,
               const std::vector<uint8_t>& new_alphabet) :
    _size_rotor{size_rotor}, _num_rotors{num_rotors} {

    _reflector.reserve(_size_rotor);
    for (const auto &reflect: reflector_place) {
        _reflector.push_back(reflect);
    }
    for (const auto &rotor: _rotors_place) {
        _rotors.push_back(rotor);
    }
    for (const auto &comm: commutator_place) {
        _commutator.push_back(comm);
    }

    Encoder encoder(new_alphabet.size(), new_alphabet);
    this->_encoder = std::make_unique<Encoder>(encoder);
}


uint8_t Enigma::_find_rotor(uint8_t num, uint8_t code) {
    for (int i = 0; i < _size_rotor; ++i) {
        if (_rotors[num][i] == code) {
            return i;
        }
    }
    return code;
}

void Enigma::_rotor_shift(uint8_t num) {
    uint8_t temp = _rotors[num][_size_rotor - 1];
    for (int i = _size_rotor - 1; i > 0; --i) {
        _rotors[num][i] = _rotors[num][i - 1];
    }
    _rotors[num][0] = temp;
}

void Enigma::encrypt(const std::string& filename_in, const std::string& filenameOut) {
    std::ifstream file(filename_in, std::ios::binary);
    if (!file.is_open()) {
        std::cout << "input file open error" << std::endl;
        return;
    }

    std::ofstream output(filenameOut, std::ios::binary);
    if (!output.is_open()) {
        std::cout << "output file open error" << std::endl;
        return;
    }

    size_t filesize = std::filesystem::file_size(filename_in);
    size_t curr_byte = 0;

    while (curr_byte != filesize) {
        curr_byte++;
        char byte;
        file.read(&byte, sizeof(byte));

        unsigned char hi = (byte >> 4) & 0x0F;
        unsigned char lo = byte & 0x0F;

        char encrypt_hi = static_cast<char>(this->encrypt(hi));
        char encrypt_lo = static_cast<char>(this->encrypt(lo));
        char encrypt_byte = static_cast<char>((encrypt_hi << 4) | encrypt_lo);
        output.write(&encrypt_byte, sizeof(encrypt_byte));
    }

    file.close();
    output.close();
}

uint8_t Enigma::encrypt(uint8_t symbol) {
    uint64_t rotor_queue = 1;
    uint8_t new_code = this->_encoder->encode(symbol);;

    if (new_code > _size_rotor) {
        std::cout << "Code bigger than size of rotor" << std::endl;
        return symbol;
    }
    new_code = _commutator[new_code];

    for (auto &rotor: _rotors) {
        new_code = rotor[new_code];
    }
    new_code = _reflector[new_code];

    for (int i = _num_rotors - 1; i >= 0; --i) {
        try {
            new_code = _find_rotor(i, new_code);
        }
        catch (const std::overflow_error& e) {
            std::cout << e.what() << std::endl;
        }
    }

    _counter++;
    for (int i = 0; i < _num_rotors; ++i) {
        if (_counter % rotor_queue == 0)
            _rotor_shift(i);
        rotor_queue *= _size_rotor;
    }
    new_code = _commutator[new_code];

    return this->_encoder->decode(new_code);
}

std::vector<uint8_t> Enigma::encrypt(std::vector<uint8_t> message) {
    std::vector<uint8_t> new_message;

    for (auto &symbol: message) {
        auto new_symbol = this->encrypt(symbol);
        new_message.push_back(new_symbol);
    }

    return new_message;
}

std::vector<uint8_t> Enigma::encrypt(const std::string& message) {
    std::vector<uint8_t> new_message;

    for (auto &symbol: message) {
        auto new_symbol = this->encrypt(symbol);
        new_message.push_back(new_symbol);
    }

    return new_message;
}
