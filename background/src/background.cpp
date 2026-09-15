#include <string>

void setBackground(std::string filePath) {
    std::string command = "/usr/bin/feh --no-fehbg --bg-scale " + filePath;
    system(command.c_str());
}
