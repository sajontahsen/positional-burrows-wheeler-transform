#ifndef PBWT_H
#define PBWT_H

#include <vector>
#include <iostream>
using namespace std;

class PBWT {
public:
    PBWT(const vector<vector<int>>& X): X(X) { }

    void runAlgoritmsSeparate(int L = 3);

    void runAlgorithmsSingleSweep(int L = 3);

private:
    vector<vector<int>> X;  // input 

    // PBWT algos 1-4  
    void buildPrefixAndDivergenceArrays(vector<int>& pos_prefix_array, vector<int>& div_array, int k, bool debug = false);
    void reportLongMatches(vector<int>& pos_prefix_array, vector<int>& div_array, int k, int L);
    void reportSetMaximalMatches(vector<int>& pos_prefix_array, vector<int>& div_array, int k);
    void reportLongMatchesWithStart(vector<int>& pos_prefix_array, vector<int>& div_array, int k, int L, bool lastrun = false);

    // util fns
    void print_LongMatches(vector<int>& a, vector<int>& b, int k);
    void saveLongMatchesWithStart(int a, int b, int start, int end, string filename="output/LongMatches.out");
    void print_SetMaximalMatches(int a_k_i, int a_k_j, int d_k, int k);
    void saveSetMaximalMatches(int a_k_i, int a_k_j, int d_k, int k, string filename="output/SetMaximalMatches.out");
    void concatenate(vector<int>& dst, vector<int>& a, vector<int>& b);
    void print_columns_upto_index(int k, const vector<int>& pos_prefix_array);

};

#endif 
