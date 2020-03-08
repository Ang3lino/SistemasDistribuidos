
#include <vector>
#include <thread>
#include <utility>
#include <assert.h>
#include <iostream>
#include <algorithm>
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
    pair<int, double> attrs[3] = { make_pair(8, 0.2), make_pair(16, 0.4), make_pair(32,0.8), };
    const double PI = 3.14159265;
    vector<Ellipse> meteors;
    meteors.reserve(n);
    for (int i = 0; i < n; ++i) {
        const int choice = experimental::randint(0, 2);
        const int size = choice + 2;
        const int h = experimental::randint(0, width) >> 1, k = experimental::randint(0, height) >> 1;
        const int a = h >> size, b = k >> size;
        const float omega = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * PI*2;
        const auto attr = attrs[choice];
        Ellipse m(a, b);
        m.set_contour(resolution);  // CALL set_countour immediately after instantiation
        m.move(h, k);
        m.x = attr.first * cos(omega);
        m.y = attr.first * sin(omega);
        m.omega = attr.second * omega;
        meteors.push_back(m);
    }
    return meteors;
}

void random_change_rgb() {
    const int r = (experimental::randint(0, 255));
    const int g = (experimental::randint(0, 255));
    const int b = (experimental::randint(0, 255));
    gfx_color(r, g, b);
}

void meteor_transition(Ellipse &m, const int &width, const int &height) {
    plot(m);
    m.rotate(m.omega, m.h, m.k);
    m.move(m.x, m.y);
    if (m.h < 0 || m.h > width) { 
        m.x *= -1;
        random_change_rgb();
    }
    if (m.k < 0 || m.k > height) {
        m.y *= -1;
        random_change_rgb();
    }
}

/**
 * size: 2 big, 3 medium, 4 small
 */
void plot_animation(const int &width, const int &height, const char *title, 
        const int n, const int resolution) {
    auto meteors = build_meteors(n, width, height, resolution);
    // auto m = meteor_test(width, height);
    gfx_open(width, height, title);
    gfx_color(0,200,100);
    gfx_clear();
    while (true) {
        gfx_clear();
        for (auto &m: meteors) 
            meteor_transition(m, width, height);
        usleep(41666);
    }
    // gfx_wait();
}

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        cout << "./animacion [N_ASTEROIDES]" << endl;
        exit(1);
    }
    const int meteor_count = atoi(argv[1]);
    cout << meteor_count << endl;
    const int resolution = 7;
    Display *d = XOpenDisplay(NULL);
    Screen *s = DefaultScreenOfDisplay(d);
    const double k = 0.75;
    const int w = ((int) s->width) * k;
    const int h = ((int) s->height) * k;
    plot_animation(w, h, "Angelino", meteor_count, resolution);
    cout << "Width: " << w << " Height: " << h << endl;
    return 0;
}

