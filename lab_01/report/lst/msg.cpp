std::vector<uint8_t> Enigma::encrypt(const std::string& message) {
  std::vector<uint8_t> new_message;
  for (auto &symbol: message) {
    auto new_symbol = this->encrypt(symbol);
    new_message.push_back(new_symbol);
  }
  return new_message;
}
