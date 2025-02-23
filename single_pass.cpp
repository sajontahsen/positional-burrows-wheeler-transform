#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void print_columns_upto_index(const vector<vector<int>>& X, int k, const vector<int>& pos_prefix_array) {
    cout << "\nMatrix till column " << k << ":\n";
    for (int idx : pos_prefix_array) {
        for (int col = 0; col <= k; col++) {
            cout << X[idx][col] << " ";
        }
        cout << "\n";
    }
}

void print_LongMatches(vector<int>& a, vector<int>& b, int k){
        cout << "reporting match for K: " << k;

        cout << "\na: ";
        for (int it: a) cout << it << " ";

        cout << "\nb: ";
        for (int it: b) cout << it << " ";
        cout << endl;  
}

void print_SetMaximalMatches(int a_k_i, int a_k_j, int d_k, int k){
    cout << "reporting maximal match of " 
        << a_k_i << " to " << a_k_j 
        << " from " << d_k << " to " << k 
        << " ->( " << a_k_i << ' ' << a_k_j << ' ' << d_k << ' ' << k << " )"
        <<endl;

}

void concatenate(vector<int>& dst, vector<int>& a, vector<int>& b){
    /* util fn: dst = a + b */
    dst.clear();
    dst.insert(dst.end(), a.begin(), a.end());
    dst.insert(dst.end(), b.begin(), b.end());
}

void PBWT_singlepass(const vector<vector<int>>& X, int L = 3){
    int M = X.size();
    int N = X[0].size();

    vector<int> pos_prefix_array(M);
    vector<int> div_array(M, 0);

    for (int i = 0; i < M; ++i) {
        pos_prefix_array[i] = i;
    }

    for (int k = 0; k < N; k++){
        vector<int> a, b, d, e, lma, lmb;
        int p = k + 1;
        int q = k + 1;

        div_array.push_back(k+1); // sentinel for set maximal match

        for (int i = 0; i < M; i++){
            /* report set maximal matches */

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

            if (flag) {
                continue;
            }

            for (int j = m + 1; j < i; j++){
                if (div_array[i] < k){  // added check for 0 length matches
                    print_SetMaximalMatches(pos_prefix_array[i], pos_prefix_array[j], div_array[i], k);
                }
            }

            for (int j = i + 1; j < n; j++){
                if (div_array[i+1] < k){ // added check for 0 length matches 
                    print_SetMaximalMatches(pos_prefix_array[i], pos_prefix_array[j], div_array[i+1], k);
                }
            }
        }

        for (int i = 0; i < M; i++){

            /* report long mathces */

            if (div_array[i] > k - L){
                if (lma.size() && lmb.size()){
                    print_LongMatches(lma, lmb, k);
                }
                lma.clear();
                lmb.clear();
            }

            /* build prefix and divergance arrays */
            
            if (div_array[i] > p) p = div_array[i];
            if (div_array[i] > q) q = div_array[i];

            int idx = pos_prefix_array[i];
            int val = X[idx][k];

            if (val == 0){
                a.push_back(idx);
                d.push_back(p);
                p = 0;

                lma.push_back(idx); // for long matches
            }
            else{
                b.push_back(idx);
                e.push_back(q);
                q = 0;

                lmb.push_back(idx); // for long matches

            }       

            concatenate(pos_prefix_array, a, b); // a_k = a + b
            concatenate(div_array, d, e); // div_k = d + e 

        }

        // added checking for any remaining long matches
        if (lma.size() && lmb.size()){ 
            print_LongMatches(lma, lmb, k);
        }
        lma.clear();
        lmb.clear();
    }

}

int main() {

    vector<vector<int>> X = {
        {0, 1, 0, 1, 0, 1},
        // {1, 0, 1, 0, 1, 0}
        {1, 1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1},
        {0, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 1, 0},
        {1, 1, 0, 0, 0, 1},
        {0, 1, 0, 1, 1, 0}
    };

    PBWT_singlepass(X);

    return 0;
}
