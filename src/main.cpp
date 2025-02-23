#include "pbwt.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    vector<vector<int>> X = {
        {0, 1, 0, 1, 0, 1},
        {1, 1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1},
        {0, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 1, 0},
        {1, 1, 0, 0, 0, 1},
        {0, 1, 0, 1, 1, 0}
    };

    PBWT pbwt(X);
    string mode = "separate";

    if (argc > 1) {
        mode = argv[1];
    }

    if (mode == "single") {
        cout << "Running algos in single-sweep mode\n";
        pbwt.runAlgorithmsSingleSweep();
    } 
    else {
        cout << "Running algos in separate mode\n";
        pbwt.runAlgoritmsSeparate();
    }

    return 0;
}
