/*
  Copyright 2019 SINTEF Digital, Mathematics and Cybernetics.
  License: CC-BY 4.0
*/

#include <cmath>
#include <stdexcept>
#include <iostream>


template <class F, class DF>
double newtonUpdate(F f, DF df, double x)
{
    // std::cout << "newtonUpdate(), x = " << x << std::endl;
    auto fx = f(x);
    auto dfx = df(x);
    return x - fx / dfx;
}

template <class F, class DF>
std::pair<double, int> newton(F f, DF df, double start)
{
    const double tol = 1e-13;
    const int max_iter = 20;
    int iter = 0;
    double x = start;
    while (fabs(f(x)) > tol && iter < max_iter) {
        x = newtonUpdate(f, df, x);
        ++iter;
    }
    if (iter == max_iter) {
        throw std::runtime_error("Too many Newton iterations");
    }
    return { x, iter};
}




int main()
{
    // Part 1
    {
        // Define function.
        auto f = [](auto x) { return sin(2*x) + x + 1; };
        // Define derivative function.
        auto df = [](auto x) { return 2*cos(2*x) + 1; };

        // Solve for a root.
        std::cout.precision(17);
        double start = 0.0;
        auto [root, iterations] = newton(f, df, start);
        std::cout << "Root = " << root << "   Iterations = " << iterations << std::endl;

        if (root == -0.3522884564608728) {
            std::cout << "Part 1 success!" << std::endl;
        } else {
            std::cout << "Part 1 failure!" << std::endl;
        }
    }

    // Part 2
    {
        // Define function.
        auto f = [](auto x) { return x/(sin(2*x) + 1.5)*cos(x) + 0.5; };
        // Define derivative function.
        auto df = [](auto x) { return ((cos(x) - x*sin(x))*(sin(2*x) + 1.5) - x*cos(x)*2*cos(2*x)) / ((sin(2*x) + 1.5)*(sin(2*x) + 1.5)); };

        // Solve for a root.
        std::cout.precision(16);
        double start = 0.0;
        auto [root, iterations] = newton(f, df, start);
        std::cout << "Root = " << root << "   Iterations = " << iterations << std::endl;

        if (root == -1.214838293477704) {
            std::cout << "Part 2 success!" << std::endl;
        } else {
            std::cout << "Part 2 failure!" << std::endl;
        }
    }
}
