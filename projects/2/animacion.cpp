
#include <vector>
#include <utility>
#include <assert.h>
#include <iostream>
#include <algorithm>
#include "IrregularPolygon.h"
#include "Coordenada.h"
#include "Ellipse.h"

#include <unistd.h>  // required for gfx
#include "gfx.h"

#include <X11/Xlib.h>  // get width and height of screen by calling s->height, s->screen


using namespace std;

typedef pair<double, double> dpair;

void plot(Ellipse &ellipse) {
    unsigned n = ellipse.coordinates.size();
    for (unsigned i = 0; i < n - 1; ++i) {
        const auto c1 = ellipse.coordinates[i];
        const auto c2 = ellipse.coordinates[i + 1];
        gfx_line(c1.x, c1.y, c2.x, c2.y);
        gfx_flush();
        // usleep(41666);  //24 por segundo
        // usleep(1024);
        cout << c1 << endl;
        cout << c2 << endl; 
        cout << endl;
    }

    cout << "a: " << ellipse.a << ", b: " << ellipse.b << endl;

    Coordenada c1 = ellipse.coordinates[n - 2], c2 = ellipse.coordinates[n - 1];
    gfx_line(c1.x, c1.y, c2.x, c2.y);
    gfx_flush();
}

void plot_animation(const int width, const int height, const char *title) {
    const int h = width >> 1, k = height >> 1;
    const int a = h >> 1, b = k >> 1;
    Ellipse ellipse(a, b);
    ellipse.set_contour(20);
    ellipse.move(h, k);

    gfx_open(width, height, title);
    gfx_color(0,200,100);
    gfx_clear();

    plot(ellipse);

    for (int i = 63; i; --i) {
        ellipse.rotate(0.5, ellipse.h, ellipse.k);
        plot(ellipse);
        usleep(41666);
    }

    gfx_wait();
}

int main(int argc, const char *argv[])
{
    Display *d = XOpenDisplay(NULL);
    Screen *s = DefaultScreenOfDisplay(d);
    const int w = ((int) s->width) * 0.75;
    const int h = ((int) s->height) * 0.75;
    plot_animation(w, h, "Angelino");
    cout << "Width: " << w << " Height: " << h << endl;
    return 0;
}

