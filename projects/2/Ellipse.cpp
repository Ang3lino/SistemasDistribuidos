
#include "Ellipse.h"

// a: big axis, b: small axis.
inline double ellipse(const double x, const double a, const double b) {
    assert (x <= a);
    return b*sqrt(1 - (x/a)*(x/a));
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

void Ellipse::move(const int dx, const int dy) {
    transform(coordinates.begin(), coordinates.end(), coordinates.begin(), 
        [&](Coordenada c) {
            c.x += dx;
            c.y += dy;
            return c;
    });
}

Ellipse::Ellipse(const int a_, const int b_): a(a_), b(b_ ) { }

Ellipse::Ellipse(const int a_, const int b_, const int h, const int k): 
        Ellipse::Ellipse(a_, b_) {
    move(h, k);
}

// void rotate(const double);
// void scale(const double);



void Ellipse::set_contour(const int samples) {
    vector<double> x_values = linspace<double>(-a, a, samples);
    IrregularPolygon ip(samples);
    transform(x_values.begin(), x_values.end(), coordinates.begin(), [&](double x_i) {
        return Coordenada(x_i, ellipse(x_i, a, b)); 
    });
    unsigned i = coordinates.size();
    while (i--) {
        const Coordenada c = coordinates[i];
        coordinates.emplace_back(c.x, -c.y);
    }
}

ostream & operator << (ostream &out, Ellipse &ellipse) {
    out << "(h, k) = " << "( " << ellipse.h << ", " << ellipse.k << ")" << endl;
    out << "a = " << ellipse.a << endl;
    out << "b = " << ellipse.b << endl;
    for (auto &c: ellipse.coordinates) out << c << endl;
    return out;
}



