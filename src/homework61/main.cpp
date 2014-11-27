#include <iostream>
#include <fstream>

#include <lplib/dictionary.h>
#include <lplib/cutting_plane.h>

int main(int argc, char **argv) {
    using lp::SolutionInfo;

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
        SolutionInfo info = lp::ilp::CuttingPlane::solve(dict, 10);
        switch(info.state) {
        case SolutionInfo::Unbounded:
            std::cout << "UNBOUNDED" << std::endl;
            break;
        case SolutionInfo::Infeasible:
            std::cout << "INFEASIBLE" << std::endl;
            break;
        case SolutionInfo::Final:
            std::cout << info.value << std::endl;
            break;
        default:
            std::cout << "unexpected error";
        }
    }
    return 0;
}
