#pragma once

#include <cstring>

namespace lp {
    struct Dictionary;

    struct Move {
        size_t basic;
        size_t non_basic;
    };

    struct SolutionInfo {
        double value;
        bool unbounded;
        size_t num_steps;
    };

    class Simplex {
        static const double EPSILON;
        static const double MVAL;
    public:
        // return offsets
        static Move blands_rule(const Dictionary &dict);
        static void pivot(const Move &offsets, Dictionary &dict);
        static SolutionInfo solve(const Dictionary &dict);
    };
}
