#include <iostream>
#include <vector>
#include <algorithm>
#include "pbwt.h"

using namespace std;

void PBWT::buildPrefixAndDivergenceArrays(vector<int>& pos_prefix_array, vector<int>& div_array, int k, bool debug){
    /* algo 1 and 2 */

    int M = pos_prefix_array.size();
    int p = k + 1;
    int q = k + 1;

    vector<int> a, b, d, e;

    for(int i = 0; i < M; i++){
        if (div_array[i] > p) p = div_array[i];
        if (div_array[i] > q) q = div_array[i];

        int idx = pos_prefix_array[i];
        int val = X[idx][k];

        if (val == 0){
            a.push_back(idx);
            d.push_back(p);
            p = 0;
        }
        else{
            b.push_back(idx);
            e.push_back(q);
            q = 0;
        }

        // a_k = a + b
        concatenate(pos_prefix_array, a, b);
        // div_k = d + e
        concatenate(div_array, d, e);        
    }

    if (debug){
        // check current state
        cout << "At position " << k << ":\n";
        cout << "pos_prefix_array: ";
        for (int val : pos_prefix_array) cout << val << " ";
        cout << "\ndiv: ";
        for (int val : div_array) cout << val << " ";
        cout << endl;
        print_columns_upto_index(k, pos_prefix_array);
    }

}

void PBWT::reportLongMatches(vector<int>& pos_prefix_array, vector<int>& div_array, int k, int L){
    
    /* algo 3 */

    int M = pos_prefix_array.size();

    vector<int> a, b;

    for (int i = 0; i < M; i++){
        if (div_array[i] > k - L){
            if (a.size() && b.size()){
                print_LongMatches(a, b, k);
            }
            a.clear();
            b.clear();
        }

        int idx = pos_prefix_array[i];
        int val = X[idx][k];

        if (val == 0){
            a.push_back(idx);
        }
        else{
            b.push_back(idx);
        }
    }

    // added checking for any remaining matches
    if (a.size() && b.size()){ 
        print_LongMatches(a, b, k);
    }
}

void PBWT::reportLongMatchesWithStart(vector<int>& pos_prefix_array, vector<int>& div_array, int k, int L){
    
    /* algo 3 */

    int M = pos_prefix_array.size();

    vector<int> a, b;
    int ilast = 0;

    for (int i = 0; i < M; i++){
        if (div_array[i] > k - L){
            if (a.size() && b.size()){
                for (int ia = ilast; ia < i; ia++){
                    for (int ib = ia + 1, start = 0; ib < i; ib++){
                        start = max(start, div_array[ib]);
                        if (X[pos_prefix_array[ib]][k] != X[pos_prefix_array[ia]][k]){
                            saveLongMatchesWithStart(
                                pos_prefix_array[ia], 
                                pos_prefix_array[ib], 
                                start, 
                                k-1
                            );
                        }
                    }
                }
            }
            a.clear();
            b.clear();
            ilast = i;
        }

        int idx = pos_prefix_array[i];
        int val = X[idx][k];

        if (val == 0){
            a.push_back(idx);
        }
        else{
            b.push_back(idx);
        }
    }

    // added checking for any remaining matches
    if (a.size() && b.size()){ 
        for (int ia = ilast; ia < M; ia++){
            for (int ib = ia + 1, start = 0; ib < M; ib++){
                start = max(start, div_array[ib]);
                if (X[pos_prefix_array[ib]][k] != X[pos_prefix_array[ia]][k]){
                    saveLongMatchesWithStart(
                        pos_prefix_array[ia], 
                        pos_prefix_array[ib], 
                        start, 
                        k-1
                    );
                }
            }
        }
    }
}

void PBWT::reportSetMaximalMatches(vector<int>& pos_prefix_array, vector<int>& div_array, int k){

    /* algo 4 */

    div_array.push_back(k+1); // sentinel

    int M = pos_prefix_array.size();

    for (int i = 0; i < M; i++){
        int m = i - 1;
        int n = i + 1;
        int flag = 0;

        if (div_array[i] <= div_array[i+1]){
            while (div_array[m + 1] <= div_array[i] && m >= 0){ // added check for negative values
                if (X[pos_prefix_array[m]][k] == X[pos_prefix_array[i]][k]){
                    flag = 1;
                    break;
                }
                m -= 1;
            }
        }

        if (div_array[i] >= div_array[i+1]){
            while (div_array[n] <= div_array[i+1]){
                if (X[pos_prefix_array[n]][k] == X[pos_prefix_array[i]][k]){
                    flag = 1;
                    break;
                }
                n += 1;
            }
            
        }

        if (flag){
            continue;
        }

        for (int j = m + 1; j < i; j++){
            if (div_array[i] < k){  // added check for 0 length matches
                saveSetMaximalMatches(pos_prefix_array[i], pos_prefix_array[j], div_array[i], k);
            }
        }

        for (int j = i + 1; j < n; j++){
            if (div_array[i+1] < k){ // added check for 0 length matches 
                saveSetMaximalMatches(pos_prefix_array[i], pos_prefix_array[j], div_array[i+1], k);
            }
        }
    }
}

void PBWT::runAlgoritmsSeparate(int L) {

    int M = X.size();    
    int N = X[0].size(); 

    vector<int> pos_prefix_array(M);
    vector<int> div_array(M, 0);

    for (int i = 0; i < M; ++i) {
        pos_prefix_array[i] = i;
    }

    for (int i = 0; i < N; i++){
        reportLongMatchesWithStart(pos_prefix_array, div_array, i, L);
        reportSetMaximalMatches(pos_prefix_array, div_array, i);
        buildPrefixAndDivergenceArrays(pos_prefix_array, div_array, i);
    }
}
