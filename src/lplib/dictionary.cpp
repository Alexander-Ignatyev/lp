#include "dictionary.h"

#include <iostream>

namespace lp {
    void alloc_dictionary(size_t m, size_t n, Dictionary &dict) {
        dict.m = n;
        dict.n = n;
        dict.basic_indices.resize(m);
        dict.non_basic_indices.resize(n);
        dict.b.resize(m);
        dict.a.resize(m*n);
        dict.c.resize(n);
        dict.value = 0;
    }

    bool load(std::istream &is, Dictionary &dict) {
        size_t m, n;
        is >> m;
        is >> n;
        if (m == 0 || n == 0) {
            return false;
        }
        //alloc_dictionary(m, n, dict);
        dict.m = m;
        dict.n = n;
        double v;
        // loading vector of basic_indices
        for (size_t i = 0; i < m; ++i) {
            is >> v;
            dict.basic_indices.push_back(v);
        }

        // loading vector of non_basic_indices
        for (size_t i = 0; i < n; ++i) {
            is >> v;
            dict.non_basic_indices.push_back(v);
        }

        // loading vector b
        for (size_t i = 0; i < m; ++i) {
            is >> v;
            dict.b.push_back(v);
        }

        // loading matrix A
        for (size_t i = 0; i < m*n; ++i) {
            is >> v;
            dict.a.push_back(v);
        }

        // loading objective value
        is >> dict.value;

        // loading vector c
        for (size_t i = 0; i < n; ++i) {
            is >> v;
            dict.c.push_back(v);
        }
        return is;
    }

    void draw_hr_line(std::ostream &os, size_t length) {
        for (size_t k = 0; k < length; ++k) {
            os << '-';
        }
        os << std::endl;
    }

    void store(std::ostream &os, const Dictionary &dict) {
        for (size_t i = 0; i < dict.m; ++i) {
            os << "x" << dict.basic_indices[i] << " =\t" << dict.b[i];
            for (size_t j = 0; j < dict.n; ++j) {
                os << "\t"<< std::showpos << dict.a[i*dict.n + j] << std::noshowpos << "*x" << dict.non_basic_indices[j];
            }
            os << std::endl;
        }
        draw_hr_line(os, 80);
        os << "z =\t" << dict.value;
        for (size_t j = 0; j < dict.n; ++j) {
            os << "\t"<< std::showpos << dict.c[j] << std::noshowpos << "*x" << dict.non_basic_indices[j];
        }
    }
}
