#include "simplex.h"
#include "dictionary.h"

#include <cmath>
#include <iostream>

namespace lp {
    const double Simplex::EPSILON = 1e-15;
    const double Simplex::MVAL = 1e9;

    Move Simplex::blands_rule(const Dictionary &dict) {
        Move offsets = {dict.m, dict.n};
        Move indices = {dict.m+dict.n+1, dict.m+dict.n+1};

        // select entering variable
        for (size_t j = 0; j < dict.n; ++j) {
            if (dict.c[j] > 0.0) {
                if (dict.non_basic_indices[j] < indices.non_basic) {
                    indices.non_basic = dict.non_basic_indices[j];
                    offsets.non_basic = j;
                }
            }
        }

        if (offsets.non_basic == dict.n) {
            return offsets;
        }

        // select leaving variable
        double min_value = MVAL;
        for (size_t i = 0; i < dict.m; ++i) {
            if (dict.a[i*dict.n + offsets.non_basic] < -EPSILON) {
                double value = -1.0 * dict.b[i]/dict.a[i*dict.n + offsets.non_basic] ;

                if (value < min_value) {  // less
                    min_value = value;
                    indices.basic = dict.basic_indices[i];
                    offsets.basic = i;
                } else if (fabs(value-min_value) < EPSILON) {  // the same
                    if (indices.basic > dict.basic_indices[i]) {
                        min_value = value;
                        indices.basic = dict.basic_indices[i];
                        offsets.basic = i;
                    }
                }
            }
        }
        return offsets;
    }

    void Simplex::pivot(const Move &offsets, Dictionary &dict) {
        using std::swap;
        swap(dict.basic_indices[offsets.basic], dict.non_basic_indices[offsets.non_basic]);

        //  leaves row of matrix A and vector b
        double factor = -dict.a[offsets.basic*dict.n + offsets.non_basic];
        dict.a[offsets.basic*dict.n + offsets.non_basic] = -1;
        dict.b[offsets.basic] /= factor;
        for (size_t j = 0; j < dict.n; ++j) {
            dict.a[offsets.basic*dict.n + j] /= factor;
        }

        // matrix A and vector b
        for (size_t i = 0; i < dict.m; ++i) {
            if (i == offsets.basic) {
                continue;
            }
            factor = dict.a[i*dict.n + offsets.non_basic];
            dict.a[i*dict.n + offsets.non_basic] = 0;
            for (size_t j = 0; j < dict.n; ++j) {
                dict.a[i*dict.n + j] += dict.a[offsets.basic*dict.n + j] * factor;
            }
            dict.b[i] += dict.b[offsets.basic]*factor;
        }

        // vector c and objective value
        factor = dict.c[offsets.non_basic];
        dict.c[offsets.non_basic] = 0;
        for (size_t j = 0; j < dict.n; ++j) {
            dict.c[j] += dict.a[offsets.basic*dict.n + j] * factor;
        }
        dict.value += dict.b[offsets.basic]*factor;
    }

    SolutionInfo Simplex::solve(const Dictionary &initial_dict) {
        Dictionary dict = initial_dict;
        std::clog << "Initial dictionary:" << std::endl;
        lp::store(std::clog, dict);
        std::clog << std::endl;
        Move offsets = blands_rule(dict);
        SolutionInfo info = {0};
        while (offsets.basic < dict.m && offsets.non_basic < dict.n) {
            pivot(offsets, dict);
            std::clog << "enters: x" << dict.non_basic_indices[offsets.non_basic];
            std::clog << ", leaves: x" << dict.basic_indices[offsets.basic] << std::endl;
            lp::store(std::clog, dict);
            std::clog << std::endl;
            ++info.num_steps;
            offsets = blands_rule(dict);
        }
        if (offsets.non_basic < dict.n) {
            info.unbounded = true;
        } else {
            info.value = dict.value;
        }

        return info;
    }
}
