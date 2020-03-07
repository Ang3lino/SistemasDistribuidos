
#include <vector>
#include <utility>
#include <assert.h>
#include <iostream>
#include <algorithm>
#include "IrregularPolygon.h"
#include "Coordenada.h"

#include <unistd.h>  // required for gfx
#include "gfx.h"

#include <X11/Xlib.h>  // get width and height of screen by calling s->height, s->screen


using namespace std;

typedef pair<double, double> dpair;

void example() {
    int t;
    gfx_open(800, 600, "Ejemplo Micro Animacion GFX");
    gfx_color(0,200,100);
    for(t = 0; t < 100; t++){
        gfx_clear();
        gfx_line( t*1+80, t*2+40, t*2+40, t*3+80 );
        gfx_line(t*5+80, t*3+40, t*3+40, t*5+80);
        cout << t   + 80 << endl;
        cout << t*2 + 40 << endl;
        cout << t*3 + 80 << endl << endl;
        gfx_flush();
        usleep(41666);  //24 por segundo
    }
}



void move(IrregularPolygon &ip, const int dx, const int dy) {
    transform(ip.coordinates.begin(), ip.coordinates.end(), ip.coordinates.begin(), 
    [&](Coordenada c) {
        c.x += dx;
        c.y += dy;
        return c;
    });
}

template<typename T>
std::vector<double> linspace(T start_in, T end_in, int num_in) {
  std::vector<double> linspaced;
  double start = static_cast<double>(start_in);
  double end = static_cast<double>(end_in);
  double num = static_cast<double>(num_in);
  if (num == 0) { return linspaced; }
  if (num == 1) {
      linspaced.push_back(start);
      return linspaced;
  }
  double delta = (end - start) / (num - 1);
  for (int i = 0; i < num-1; ++i) {
      linspaced.push_back(start + delta * i);
  }
  linspaced.push_back(end); // I want to ensure that start and end
                            // are exactly the same as the input
  return linspaced;
}

// a: big axis, b: small axis.
inline double ellipse(const double x, const double a, const double b) {
    assert (x <= a);
    return b*sqrt(1 - (x/a)*(x/a));
}

IrregularPolygon Ellipse(int samples, int a, int b) {
    vector<double> x_values = linspace<double>(-a, a, samples);
    IrregularPolygon ip(samples);
    transform(x_values.begin(), x_values.end(), ip.coordinates.begin(), [&](double x_i) {
        return Coordenada(x_i, ellipse(x_i, a, b)); 
    });
    unsigned i = ip.coordinates.size();
    while (i--) {
        const Coordenada c = ip.coordinates[i];
        ip.coordinates.emplace_back(c.x, -c.y);
    }
    return ip;
}

void plot_ellipse(const int width, const int height, const char *title) {
    const int a = width >> 1, b = height >> 1;
    auto ip = Ellipse(20, a, b);
    move(ip, a, b);

    gfx_open(width, height, title);
    gfx_color(0,200,100);
    gfx_clear();
    unsigned n = ip.coordinates.size();
    for (unsigned i = 0; i < n - 1; ++i) {
        Coordenada c1 = ip.coordinates[i], c2 = ip.coordinates[i + 1];
        gfx_line(c1.x, c1.y, c2.x, c2.y);
        gfx_flush();
        usleep(41666);  //24 por segundo
        cout << c1 << endl;
        cout << c2 << endl;
        cout << endl;
    }

    cout << "a: " << a << ", b: " << b << endl;

    Coordenada c1 = ip.coordinates[n - 2], c2 = ip.coordinates[n - 1];
    gfx_line(c1.x, c1.y, c2.x, c2.y);
    gfx_flush();
    gfx_wait();
}

int main(int argc, const char *argv[])
{
    Display *d = XOpenDisplay(NULL);
    Screen *s = DefaultScreenOfDisplay(d);
    const int w = ((int) s->width) >> 1;
    const int h = ((int) s->height) >> 1;
    plot_ellipse(w, h, "Angelino");
    cout << "Width: " << w << " Height: " << h << endl;
    return 0;
}

