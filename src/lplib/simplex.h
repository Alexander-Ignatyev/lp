#pragma once

#include <cstring>

namespace lp {
    struct Dictionary;

    struct Move {
        size_t basic;
        size_t non_basic;
    };

    class Simplex {
        static const double EPSILON;
        static const double MVAL;
    public:
        // return offsets
        static Move blandsRule(const Dictionary &dict);
        static void pivot(const Move &offsets, Dictionary &dict);
    };
}
