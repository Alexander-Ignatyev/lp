#include "simplex.h"
#include "dictionary.h"

#include <cmath>

namespace lp {
    const double Simplex::EPSILON = 1e-3;
    const double Simplex::MVAL = 1e9;

    Move Simplex::blandsRule(const Dictionary &dict) {
        Move offsets = {dict.m, dict.n};
        Move indices = {dict.m+dict.n, dict.m+dict.n};

        // select entering variable
        for (size_t j = 0; j < dict.n; ++j) {
            if (dict.c[j] > EPSILON) {
                if (dict.non_basic_indices[j] < indices.non_basic) {
                    indices.non_basic = dict.non_basic_indices[j];
                    offsets.non_basic = j;
                }
            }
        }

        // select leaving variable
        double min_value = MVAL;
        for (size_t i = 0; i < dict.m; ++i) {
            if (dict.a[i*dict.n + offsets.non_basic] < -EPSILON) {
                double value = -1.0 * dict.b[i]/dict.a[i*dict.n + offsets.non_basic] ;
                // 1. the same
                if (fabs(value-min_value) < EPSILON) {
                    if (indices.basic > dict.basic_indices[i]) {
                        min_value = value;
                        indices.basic = dict.basic_indices[i];
                        offsets.basic = i;
                    }
                }
                // 2. less
                else if (value < min_value) {
                    min_value = value;
                    indices.basic = dict.basic_indices[i];
                    offsets.basic = i;
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
}
