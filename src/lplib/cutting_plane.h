#pragma once

#include "basic_types.h"

namespace lp{
struct Dictionary;

namespace ilp {
    class CuttingPlane {
    public:
        static SolutionInfo solve(const Dictionary &dict, size_t max_iters = 10);
    private:
        static SolutionInfo iterate(Dictionary &dict);
        static bool scale(Dictionary &dict, double &obj_factor);
        static bool is_frac(double value);
        static double frac(double value);
    };
}
}
