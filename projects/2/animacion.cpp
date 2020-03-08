
#include <vector>
#include <utility>
#include <assert.h>
#include <iostream>
#include <algorithm>
#include <thread>
#include <experimental/random>
#include "IrregularPolygon.h"
#include "Coordenada.h"
#include "Ellipse.h"

#include <unistd.h>  // required for gfx
#include "gfx.h"

#include <X11/Xlib.h>  // get width and height of screen by calling s->height, s->screen


using namespace std;

void plot(const Ellipse &ellipse) {
    unsigned n = ellipse.coordinates.size();
    for (unsigned i = 0; i < n - 1; ++i) {
        const auto c1 = ellipse.coordinates[i];
        const auto c2 = ellipse.coordinates[i + 1];
        gfx_line(c1.x, c1.y, c2.x, c2.y);
        gfx_flush();
    }
    Coordenada c1 = ellipse.coordinates[n - 2], c2 = ellipse.coordinates[n - 1];
    gfx_line(c1.x, c1.y, c2.x, c2.y);
    gfx_flush();
}

struct MeteorAttributes {
    int x, y;
    double omega;
    MeteorAttributes(int x0, int y0, double omega0):
        x(x0), y(y0), omega(omega0) {}
};


Ellipse meteor_test(const int width, const int height) {
    const int h = width >> 1, k = height >> 1;
    const int size = 2;
    const int a = h >> size, b = k >> size;
    Ellipse m(a, b);
    m.set_contour(16);
    m.move(h, k);
    m.x = 8;
    m.y = 8;
    m.omega = 0.4;
    return m;
}

vector<Ellipse> build_meteors(const int n, int width, int height, const int resolution) {
    MeteorAttributes attrs[3] = {
        MeteorAttributes(4, 4, 0.1),
        MeteorAttributes(8, 8, 0.2),
        MeteorAttributes(16, 16, 0.4),
    };
    vector<Ellipse> meteors;
    meteors.reserve(n);
    for (int i = 0; i < n; ++i) {
        const int choice = experimental::randint(0, 2);
        const int h = experimental::randint(0, width) >> 1;
        const int k = experimental::randint(0, height) >> 1;
        const int size = choice + 2;
        const int a = h >> size, b = k >> size;
        const MeteorAttributes attr = attrs[choice];
        Ellipse m(a, b);
        m.set_contour(resolution);  // CALL set_countour immediately after instantiation
        cout << choice << endl;
        m.move(h, k);
        m.x = attr.x;
        m.y = attr.y;
        m.omega = attr.omega;
        meteors.push_back(m);
    }
    return meteors;
}

void meteor_transition(Ellipse &m, const int &width, const int &height) {
    plot(m);
    m.rotate(m.omega, m.h, m.k);
    m.move(m.x, m.y);
    if (m.h < 0 || m.h > width) m.x *= -1;
    if (m.k < 0 || m.k > height) m.y *= -1;
}

/**
 * size: 2 big, 3 medium, 4 small
 */
void plot_animation(const int &width, const int &height, const char *title, const int n, const int resolution) {
    auto meteors = build_meteors(n, width, height, 15);
    // auto m = meteor_test(width, height);
    // auto m = meteors[0];
    gfx_open(width, height, title);
    gfx_color(0,200,100);
    gfx_clear();
    for (int i = 2000; i; --i) {
        gfx_clear();
        for (auto &m: meteors) 
            meteor_transition(m, width, height);
        usleep(10416);
    }
    gfx_wait();
}

int main(int argc, const char *argv[])
{
    const int meteor_count = 32, resolution = 15;
    Display *d = XOpenDisplay(NULL);
    Screen *s = DefaultScreenOfDisplay(d);
    const double k = 1;
    const int w = ((int) s->width) * k;
    const int h = ((int) s->height) * k;
    plot_animation(w, h, "Angelino", meteor_count, resolution);
    cout << "Width: " << w << " Height: " << h << endl;
    return 0;
}

