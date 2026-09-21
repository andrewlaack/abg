#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>
#include <unistd.h>

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

std::vector<uint32_t> getScreenSizeAndOffsets() {
    Display* dpy;
    dpy = XOpenDisplay(NULL);

    if (dpy == NULL) {
        throw std::runtime_error{"Unable to open display."};
    }

    int count = ScreenCount(dpy);

    if (count == 0) {
        throw std::runtime_error{"Unable to find screens."};
    }

    XRRMonitorInfo* mons =
        XRRGetMonitors(dpy, DefaultRootWindow(dpy), True, &count);

    if (count == 0) {
        throw std::runtime_error{"Unable to find monitors."};
    }

    XRRMonitorInfo* m = &mons[0];
    for (int i = 0; i < count; ++i) {
        if (mons[i].primary) {
            m = &mons[i];
            break;
        }
    }

    std::vector<uint32_t> res{(uint32_t)m->width, (uint32_t)m->height,
                              (uint32_t)m->x, (uint32_t)m->y};

    XRRFreeMonitors(mons);
    XCloseDisplay(dpy);
    return res;
}

void sendToBg(std::string name, uint32_t xOffset, uint32_t yOffset) {
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
        XMoveWindow(d, kids[i], xOffset, yOffset);
        XLowerWindow(d, kids[i]);
        XMapWindow(d, kids[i]);

        XLowerWindow(d, kids[i]);
        break;
    }

    XFree(kids);
    XCloseDisplay(d);
}
