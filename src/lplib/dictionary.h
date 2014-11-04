#pragma once

#include <vector>
#include <iosfwd>

namespace lp {
    struct Dictionary {
        size_t m;  // # of basis variabless
        size_t n;  // # of non-basis variables
        std::vector<size_t> basic_indices;
        std::vector<size_t> non_basic_indices;
        std::vector<double> b;  // vector b[m]
        std::vector<double> a;  // matrix A[m*n]
        std::vector<double> c;  // objective coefficients c[n]
        double value;
    };

    bool load(std::istream &is, Dictionary &dict);
    void store(std::ostream &os, const Dictionary &dict);
}
