#include "cutting_plane.h"

#include <cmath>
#include <iostream>

#include "dictionary.h"
#include "simplex.h"

// #define ENABLE_LOGGING

namespace lp {
namespace ilp {
    SolutionInfo CuttingPlane::solve(const Dictionary &initial_dict, size_t max_iters) {
        Dictionary dict = initial_dict;
        double obj_factor = 1.0;
        scale(dict, obj_factor);
        if (!Simplex::is_feasible(dict)) {
            SolutionInfo info = Simplex::initialize(dict);
            if (info.state == SolutionInfo::Unbounded) {
                info.state = SolutionInfo::Infeasible;
                return info;
            }
        }
        SolutionInfo info = Simplex::optimize(dict);
        if (info.state != SolutionInfo::Final) {
            return info;
        }
        bool to_cont = true;
        for (size_t k = 0; k < max_iters && to_cont; ++k) {
            to_cont = false;
            size_t initial_m = dict.m;
            for (size_t i =0; i < initial_m; ++i) {
                if (is_frac(dict.b[i])) {
                    double value = dict.b[i];
                    to_cont = true;
                    dict.add_new_constraints(1);
                    size_t index_new = dict.m - 1;
                    dict.b[index_new] = -frac(dict.b[i]);
                    for (size_t j = 0; j < dict.n; ++j) {
                        dict.a[index_new*dict.n + j] = frac(-dict.a[i*dict.n + j]);
                    }
                }
            }
#ifdef ENABLE_LOGGING
            std::clog << "added " << (dict.m - initial_m) << " constraints" << std::endl;
            lp::store(std::clog, dict);
            std::clog << std::endl << std::endl;
#endif  // ENABLE_LOGGING
            dict = Simplex::get_dual_dictionary(dict);
            info = Simplex::optimize(dict);
            dict = Simplex::get_dual_dictionary(dict);
#ifdef ENABLE_LOGGING
            std::clog << "obtained final dictionary: " << std::endl;
            lp::store(std::clog, dict);
            std::clog << std::endl << std::endl;
#endif  // ENABLE_LOGGING
            if (info.state == SolutionInfo::Unbounded) {
                info.state = SolutionInfo::Infeasible;
                return info;
            }
        }
        info.value /= obj_factor * -1;  // -1 due to duality
        return info;
    }

    bool CuttingPlane::scale(Dictionary &dict, double &obj_factor) {
        // stub
        obj_factor = 1.0;
        return false;
    }

    bool  CuttingPlane::is_frac(double value) {
        static const double EPS = 1e-4;
        //return frac(value) > EPS;
        //return fabs(value - static_cast<long long>(value)) > EPS;
        return fabs(value - floor(value)) > EPS && fabs(value - ceil(value)) > EPS;
    }

    double  CuttingPlane::frac(double value) {
        return value - floor(value);
    }
}
}
