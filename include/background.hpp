#pragma once

#include <cstdint>
#include <string>
#include <vector>
std::vector<uint32_t> getScreenSizeAndOffsets();
void sendToBg(std::string name, uint32_t xOffset, uint32_t yOffset);
