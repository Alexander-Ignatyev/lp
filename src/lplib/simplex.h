#pragma once

#include <cstring>
#include <vector>

#include "basic_types.h"

namespace lp {
    struct Dictionary;

    class Simplex {
        static const double EPSILON;
        static const double MVAL;
    public:
        // return offsets
        static Move blands_rule(const Dictionary &dict);
        static void pivot(const Move &offsets, Dictionary &dict);
        static SolutionInfo solve(const Dictionary &dict);
        static Dictionary get_dual_dictionary(const Dictionary &dict);

        static void transpose(const std::vector<double> &from, size_t cols, std::vector<double> &to);

        static bool is_feasible(const Dictionary &dict);
        static SolutionInfo initialize(Dictionary &dict);
        static SolutionInfo optimize(Dictionary &dict);

    private:
        static void multiply_by(std::vector<double> &v, double value);
    };
}
