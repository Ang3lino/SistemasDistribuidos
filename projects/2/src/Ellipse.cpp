
#include "Ellipse.h"


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
inline double y_ellipse(const double x, const double a, const double b) {
    assert (x <= a);
    return b*sqrt(1 - (x/a)*(x/a));
}

void Ellipse::move(const int dx, const int dy) {
    h += dx;
    k += dy;
    for (auto &c: coordinates) c.move(dx, dy);
}

Ellipse::Ellipse(const int a_, const int b_): a(a_), b(b_ ) {
    h = 0;
    k = 0;
    x = 0;
    y = 0;
    omega = 0;
    rgb[0] = 0;
    rgb[1] = 255;
rgb[2] = 0;
}

Ellipse::Ellipse(const int a_, const int b_, const int h_, const int k_): 
        Ellipse::Ellipse(a_, b_) {
    move(h_, k_);
}

set<double> linspace_random(const int a, const int b, const unsigned samples) {
    set<double> unique_points;
    while (unique_points.size() < samples) {
        unique_points.insert(experimental::randint(a, b));
    }
    return unique_points;
}


void Ellipse::set_contour(const int samples) {
    const auto x_values = linspace(-a, a, samples);
    coordinates.resize(samples);
    // if the third argument is begin() we need to resize it previously
    transform(x_values.begin(), x_values.end(), coordinates.begin(), [&](double x_i) {
        return Coordenada(x_i, y_ellipse(x_i, a, b)); 
    });
    unsigned i = coordinates.size(); // n - 1 ? 
    cout << "Antes" << endl;;
    for (auto &c: coordinates) cout << c << endl;
    cout << endl;
    while (i--) {
        const Coordenada c = coordinates[i];
        coordinates.emplace_back(c.x, -c.y);
    }
    cout << "Despues" << endl;
    for (auto &c: coordinates) cout << c << endl;
    cout << endl;
    cout << endl;
}

// ostream & operator << (ostream &out, Ellipse &ellipse) {
//     out << "(h, k) = " << "( " << ellipse.h << ", " << ellipse.k << ")" << endl;
//     out << "a = " << ellipse.a << endl;
//     out << "b = " << ellipse.b << endl;
//     for (auto &c: ellipse.coordinates) out << c << endl;
//     return out;
// }

void Ellipse::rotate(const double theta) {
    for (auto &c: coordinates) {
        c.rotate(theta);
    }
}

void Ellipse::rotate(const double theta, const double dx, const double dy) {
    for (auto &c: coordinates) {
        c.move(-dx, -dy);
        c.rotate(theta);
        c.move(dx, dy);
    }
}


// void scale(const double);

