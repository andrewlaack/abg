#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <unistd.h>

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

std::vector<uint32_t> getScreenSize() {
    Display* dpy;
    Screen* screen;
    dpy = XOpenDisplay(NULL);
    int count = ScreenCount(dpy);
    if (count == 0) {
        throw std::runtime_error{"Unable to find screens."};
    }
    screen = ScreenOfDisplay(dpy, 0);
    std::vector<uint32_t> res{(uint32_t)screen->width,
                              (uint32_t)screen->height};
    XCloseDisplay(dpy);
    return res;
}

void sendToBg(std::string name) {
    Display* d = XOpenDisplay(nullptr);
    Window root = DefaultRootWindow(d), r, p, *kids;
    uint32_t n;

    XQueryTree(d, root, &r, &p, &kids, &n);
    for (unsigned i = 0; i < n; i++) {
        char* wn = nullptr;
        XFetchName(d, kids[i], &wn);

        if (wn == nullptr) {
            continue;
        }

        bool hit = name == wn;
        XFree(wn);

        if (!hit) {
            continue;
        }

        XSetWindowAttributes a;

        a.override_redirect = True;
        XChangeWindowAttributes(d, kids[i], CWOverrideRedirect, &a);

        // have to do unmap / map to make it bg for all tags
        XUnmapWindow(d, kids[i]);
        XMapWindow(d, kids[i]);

        XLowerWindow(d, kids[i]);
        break;
    }

    XFree(kids);
    XCloseDisplay(d);
}
