#pragma once

#include <cstring>
#include <vector>

namespace lp {
    struct Dictionary;

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

    private:
        static void multiply_by(std::vector<double> &v, double value);
        static bool is_feasible(const Dictionary &dict);
        static SolutionInfo initialize(Dictionary &dict);
        static SolutionInfo optimize(Dictionary &dict);
    };
}
