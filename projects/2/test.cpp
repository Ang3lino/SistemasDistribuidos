
#include <iostream>
#include <vector>
#include <algorithm>
#include <experimental/random>


void print_vector(std::vector<double> &v) {
    std::cout << std::endl << std::endl;
    for (auto &x: v) std::cout << x << std::endl;
}

std::vector<double> linspace_random(const int a, const int b, const int samples) {
    std::vector<double> x;
    x.reserve(samples);
    for (int i = samples; i; --i) {
        const double sample = std::experimental::randint(a, b);
        x.push_back(sample);
    }
    print_vector(x);
    std::sort(x.begin(), x.end());
    print_vector(x);
    return x;
}

int main(int argc, const char *argv[])
{
    auto x = linspace_random(-8, 8, 10);
    return 0;
}
