#pragma once

#include <cstdint>
#include <string>
#include <vector>
void setBackground(std::string filePath);
std::vector<uint32_t> getScreenSize();
void sendToBg(std::string name);
