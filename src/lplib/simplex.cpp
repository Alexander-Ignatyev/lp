#include "simplex.h"
#include "dictionary.h"

#include <cmath>
#include <iostream>
#include <algorithm>

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
        if (!is_feasible(dict)) {
            SolutionInfo info = initialize(dict);
            if (info.state == SolutionInfo::Unbounded) {
                info.state = SolutionInfo::Infeasible;
                return info;
            }
        }
        return optimize(dict);
    }

    Dictionary Simplex::get_dual_dictionary(const Dictionary &dict) {
        Dictionary dual;
        dual.m = dict.n;
        dual.n = dict.m;
        dual.basic_indices = dict.non_basic_indices;
        dual.non_basic_indices = dict.basic_indices;
        dual.b = dict.c;
        dual.c = dict.b;
        transpose(dict.a, dict.n, dual.a);
        dual.value = dict.value;

        multiply_by(dual.a, -1);
        multiply_by(dual.b, -1);
        multiply_by(dual.c, -1);
        dual.value *= -1;
        return dual;
    }

    void Simplex::transpose(const std::vector<double> &from, size_t cols, std::vector<double> &to) {
        size_t rows = from.size()/cols;
        to.resize(from.size());
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                to[j*rows+i] = from[i*cols+j];
            }
        }
    }

    void Simplex::multiply_by(std::vector<double> &v, double value) {
        for (size_t i = 0; i < v.size(); ++i) {
            v[i] *= value;
        }
    }

    bool Simplex::is_feasible(const Dictionary &dict) {
        for (size_t i = 0; i < dict.m; ++i) {
            if (dict.b[i] < 0) {
                return false;
            }
        }
        return true;
    }

    SolutionInfo Simplex::initialize(Dictionary &dict) {
        Dictionary dual = get_dual_dictionary(dict);
        std::fill(dual.b.begin(), dual.b.end(), 1);
        SolutionInfo info = optimize(dual);
        if (info.state == SolutionInfo::Final) {
            Dictionary feas = get_dual_dictionary(dual);
            std::fill(feas.c.begin(), feas.c.end(), 0);

            std::vector<double> factors(dict.m+dict.n+1, 0);
            for (size_t i = 0; i < dict.n; ++i) {
                factors[dict.non_basic_indices[i]] = dict.c[i];
            }
            feas.value = dict.value;

            for (size_t i = 0; i < feas.m; ++i) {
                double factor = factors[feas.basic_indices[i]];
                if (fabs(factor) < EPSILON) {
                    continue;
                }
                for (size_t j = 0; j < feas.n; ++j) {
                    feas.c[j] += factor*feas.a[i*feas.n+j];
                }
                feas.value += factor*feas.b[i];
            }
            for (size_t j = 0; j < feas.n; ++j) {
                double factor = factors[feas.non_basic_indices[j]];
                if (fabs(factor) > EPSILON) {
                    feas.c[j] += factor;
                }
            }
            dict.swap(feas);
        }
        return info;
    }

    SolutionInfo Simplex::optimize(Dictionary &dict) {
        std::clog << "Initial feasible dictionary:" << std::endl;
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
            info.state = SolutionInfo::Unbounded;
        } else {
            info.state = SolutionInfo::Final;
            info.value = dict.value;
        }

        return info;
    }
}
