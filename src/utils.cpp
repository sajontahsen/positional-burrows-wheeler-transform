#include <algorithm>
#include "pbwt.h"

using namespace std;

void PBWT::print_LongMatches(vector<int>& a, vector<int>& b, int k){
    cout << "reporting match for K: " << k;

    cout << "\na: ";
    for (int it: a) cout << it << " ";

    cout << "\nb: ";
    for (int it: b) cout << it << " ";
    cout << endl;  
}

void PBWT::print_SetMaximalMatches(int a_k_i, int a_k_j, int d_k, int k){
    cout << "reporting maximal match of " 
        << a_k_i << " to " << a_k_j 
        << " from " << d_k << " to " << k 
        << " ->( " << a_k_i << ' ' << a_k_j << ' ' << d_k << ' ' << k << " )"
        <<endl;

}

void PBWT::concatenate(vector<int>& dst, vector<int>& a, vector<int>& b){
    // dst = a + b 

    dst.clear();
    dst.insert(dst.end(), a.begin(), a.end());
    dst.insert(dst.end(), b.begin(), b.end());
}

void PBWT::print_columns_upto_index(int k, const vector<int>& pos_prefix_array) {
    cout << "\nMatrix till column " << k << ":\n";
    for (int idx : pos_prefix_array) {
        for (int col = 0; col <= k; col++) {
            cout << X[idx][col] << " ";
        }
        cout << "\n";
    }
}