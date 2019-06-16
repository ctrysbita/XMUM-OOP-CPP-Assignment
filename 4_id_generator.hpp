#pragma once
#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

/**
 * @brief An random ID generator to prevent duplicated ID.
 * @return Generated ID (composed by 4 hex number)
 */
std::string GenerateID() {
  std::stringstream ss;

  // Use 4 random hex number to construct ID.
  // Length should be increased as user grows.
  for (auto i = 0; i < 4; i++) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);
    auto rc = static_cast<unsigned char>(dis(gen));
    std::stringstream hexstream;
    hexstream << std::hex << int(rc);
    auto hex = hexstream.str();
    ss << (hex.length() < 2 ? '0' + hex : hex);
  }
  return ss.str();
}