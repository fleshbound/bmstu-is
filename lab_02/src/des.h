//
// Created by sheglar on 02.11.24.
//

#ifndef DES_H
#define DES_H
#include <cstdint>
#include <string>

class DES {
    uint64_t keys[16];
    std::string run(const std::string& data);

public:
    DES();
    explicit DES(const std::string& key);
    explicit DES(const uint64_t &key);
    ~DES() = default;
    void setkey(const std::string& key);
    std::string encrypt(const std::string& data);
    std::string decrypt(const std::string& data);
    unsigned int blocksize() const;
};

#endif //DES_H
