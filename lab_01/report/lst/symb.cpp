uint8_t Enigma::encrypt(uint8_t symbol) {
    uint64_t rotor_queue = 1;
    uint8_t new_code = this->_encoder->encode(symbol);;
    if (new_code > _size_rotor) {
        throw std::out_of_range("Code bigger than size of rotor");
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
        if (_counter % rotor_queue == 0) {
            _rotor_shift(i);
        }
        rotor_queue *= _size_rotor;
    }
    new_code = _commutator[new_code];
    return this->_encoder->decode(new_code);
}
