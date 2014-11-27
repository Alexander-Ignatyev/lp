#pragma once

#include <cstddef>

namespace lp {
    struct Move {
        size_t basic;
        size_t non_basic;
    };

    struct SolutionInfo {
        double value;
        size_t num_steps;
        enum {
            Infeasible = 1,
            Feasible = 4,
            Unbounded = 5,
            Bounded = 6,
            Final = 8
        } state;
    };

}
