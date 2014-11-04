#include <iostream>
#include <fstream>

#include <lplib/dictionary.h>
#include <lplib/simplex.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "ERROR: Please spicify directory filepath";
        return 1;
    }
    for (int i = 1; i < argc; ++i) {
        std::ifstream ifs(argv[i]);
        if (!ifs) {
            std::cerr << "ERROR: Cannot open file " << argv[i] << std::endl;
            continue;
        }
        lp::Dictionary dict;
        if (!lp::load(ifs, dict)) {
            std::cerr << "ERROR: Cannot load dictionary from " << argv[i] << std::endl;
        }
        std::clog << "Initial dictionary:" << std::endl;
        lp::store(std::clog, dict);
        std::clog << std::endl;
        lp::Move offsets = lp::Simplex::blandsRule(dict);
        if (offsets.basic >= dict.m || offsets.non_basic >= dict.n) {
            std::cout << "UNBOUNDED";
        } else {
            std::cout << dict.non_basic_indices[offsets.non_basic] << std::endl;
            std::cout << dict.basic_indices[offsets.basic] << std::endl;

            lp::Simplex::pivot(offsets, dict);
            std::clog << "enters: x" << dict.basic_indices[offsets.basic];
            std::clog << ", leaves: x" << dict.non_basic_indices[offsets.non_basic] << std::endl;
            std::clog << "Dictionary after pivoting:" << std::endl;
            lp::store(std::clog, dict);
            std::clog << std::endl;

            std::cout << dict.value;
        }
    }
    return 0;
}
