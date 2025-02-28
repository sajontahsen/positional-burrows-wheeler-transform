#include "pbwt.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

string trim(const string &str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == string::npos) return ""; // all spaces, return empty
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, last - first + 1);
}

vector<vector<int>> readHaplotypeData(const string &filename) {
    ifstream infile(filename);
    if (!infile) {
        cerr << "error: cannot open input file " << filename << endl;
        exit(1);
    }

    vector<string> raw_data;  
    string line;

    while (getline(infile, line)) {
        line = trim(line);  // for whitespaces
        if (!line.empty()) {
            raw_data.push_back(line);
        }
    }
    infile.close();

    int num_sites = raw_data.size();
    int num_haplotypes = raw_data[0].size();
    cout << "data size: " << num_haplotypes << ' ' << num_sites << endl;

    vector<vector<int>> haplotypes(num_haplotypes, vector<int>(num_sites));

    // transpose data to match my existing pipeline
    for (int i = 0; i < num_sites; i++) {
        for (int j = 0; j < num_haplotypes; j++) {
            haplotypes[j][i] = raw_data[i][j] - '0';  
        }
    }

    return haplotypes;
}

int main(int argc, char* argv[]) {

    string filename = "../bin_1k_1k.txt";  
    vector<vector<int>> sample_data = readHaplotypeData(filename);

    PBWT pbwt(sample_data);
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
        pbwt.runAlgoritmsSeparate(20);
    }

    return 0;
}
