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
        lp::SolutionInfo info = lp::Simplex::solve(dict);
        if (info.unbounded) {
            std::cout << "UNBOUNDED" << std::endl;
        } else {
            std::cout << info.value << std::endl;
            std::cout << info.num_steps;
        }
    }
    return 0;
}
