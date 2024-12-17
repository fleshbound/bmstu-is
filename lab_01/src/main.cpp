#include <cstdint>
#include <iostream>
#include <vector>

#include "Enigma.h"

#define ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz"
#define POS_1 12
#define POS_2 15
#define POS_3 20
#define ROTOR_COUNT 3
#define TEST_STRING "What is dead may never die"

std::vector<uint8_t> get_reflector(const int alphabet_size) {
    int reflector_number = rand() % alphabet_size;
    std::vector<uint8_t> reflector;
    std::cout << "number: " << reflector_number << std::endl;
    for (int i = 0; i < alphabet_size; i++) {
        reflector.push_back((reflector_number + alphabet_size - i) % alphabet_size);
        std::cout << static_cast<int>(reflector[i]) << ", ";
    }
    std::cout << std::endl;
    return reflector;
}

std::vector<std::vector<uint8_t>> get_rotors(const int alphabet_size) {
    std::vector<std::vector<uint8_t>> rotors;
    for (int i = 0; i < ROTOR_COUNT; i++) {
        int rotor_number = rand() % alphabet_size;
        std::cout << "Rotor " << i + 1 << " number: " << rotor_number << std::endl;
        std::vector<uint8_t> rotor;
        for (int j = 0; j < alphabet_size; ++j) {
            rotor.push_back((rotor_number + j) % alphabet_size);
            std::cout << static_cast<int>(rotor[j]) << ", ";
        }
        rotors.push_back(rotor);
        std::cout << std::endl;
    }
    return rotors;
}

int main() {
    std::vector<uint8_t> alp1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    // std::cout << "Hello, World!" << std::endl;
    std::string alphabet(ALPHABET);
    int alphabet_size = alphabet.size();
    std::cout << "Reflector";
    std::vector<uint8_t> reflector = get_reflector(alphabet_size);
    std::cout << "Commutator";
    std::vector<uint8_t> commutator = get_reflector(alphabet_size);
    std::vector<std::vector<uint8_t>> rotors = get_rotors(alphabet_size);

    Enigma enigma1(alphabet_size, ROTOR_COUNT, reflector, rotors, commutator, alphabet);

    std::cout << "ИСХОДНАЯ СТРОКА: " << TEST_STRING << "\n";
    std::cout << "ЗАШИФРОВАННАЯ СТРОКА: ";
    auto res = enigma1.encrypt(TEST_STRING);
    for (auto c: res)
        std::cout << c;
    std::cout << std::endl;

    Enigma enigma2(alphabet_size, ROTOR_COUNT, reflector, rotors, commutator, alphabet);
    res = enigma2.encrypt(res);
    std::cout << "ЗАШИФРОВАННАЯ ЗАШИФРОВАННАЯ СТРОКА: ";
    for (auto c: res)
        std::cout << c;
    std::cout << std::endl;

    std::string archive_in = "/home/sheglar/bmstu/is/lab_01/src/data/in/1.zip";
    std::string text_in = "/home/sheglar/bmstu/is/lab_01/src/data/in/1.txt";
    std::string img_in = "/home/sheglar/bmstu/is/lab_01/src/data/in/1.png";

    std::string archive_out = "/home/sheglar/bmstu/is/lab_01/src/data/out/1_zip_encrypted.bin";
    std::string text_out = "/home/sheglar/bmstu/is/lab_01/src/data/out/1_txt_encrypted.bin";
    std::string img_out = "/home/sheglar/bmstu/is/lab_01/src/data/out/1_png_encrypted.bin";

    alphabet_size = alp1.size();
    reflector = get_reflector(alphabet_size);
    rotors = get_rotors(alphabet_size);
    commutator = get_reflector(alphabet_size);
    Enigma enigma3(alphabet_size, ROTOR_COUNT, reflector, rotors, commutator, alp1);
    enigma3.encrypt(archive_in, archive_out);

    Enigma enigma4(alphabet_size, ROTOR_COUNT, reflector, rotors, commutator, alp1);
    enigma3.encrypt(text_in, text_out);

    Enigma enigma5(alphabet_size, ROTOR_COUNT, reflector, rotors, commutator, alp1);
    enigma3.encrypt(img_in, img_out);

    std::string archive_out_out = "/home/sheglar/bmstu/is/lab_01/src/data/out/1_zip_encrypted_decrypted.zip";
    std::string text_out_out = "/home/sheglar/bmstu/is/lab_01/src/data/out/1_txt_encrypted_decrypted.txt";
    std::string img_out_out = "/home/sheglar/bmstu/is/lab_01/src/data/out/1_png_encrypted_decrypted.png";

    Enigma enigma6(alphabet_size, ROTOR_COUNT, reflector, rotors, commutator, alp1);
    enigma3.encrypt(archive_out, archive_out_out);

    Enigma enigma7(alphabet_size, ROTOR_COUNT, reflector, rotors, commutator, alp1);
    enigma3.encrypt(text_out, text_out_out);

    Enigma enigma8(alphabet_size, ROTOR_COUNT, reflector, rotors, commutator, alp1);
    enigma3.encrypt(img_out, img_out_out);

    return 0;
}
