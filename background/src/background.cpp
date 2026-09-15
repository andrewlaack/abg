#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>
#include <X11/Xlib.h>

void setBackground(std::string filePath) {
    std::string command = "/usr/bin/feh --no-fehbg --bg-scale " + filePath;
    system(command.c_str());
}

std::vector<uint32_t> getScreenSize() {
    Display* dpy;
    Screen* screen;
    dpy = XOpenDisplay(NULL);
    int count = ScreenCount(dpy);
    if(count == 0) {
        throw std::runtime_error{"Unable to find screens."};
    }
    screen = ScreenOfDisplay(dpy, 0);
    std::vector<uint32_t> res {(uint32_t)screen->width, (uint32_t)screen->height};
    return res;
}
