#include <vector>
#include <iostream>
#include <math.h>

using namespace std;


// Total number of subsets that can be generated are 2^n, because
// if we go over each element of a set we have two choices of what
// to do with it: include it or not. Since, there are n elements in
// a set we get 2^n.

// Complexity of the function getSubsets is O(n * 2^n)

vector<vector<int>> getSubsets(vector<int> set) {
    unsigned int len = set.size();
    unsigned int total_set_cnt = pow(2, len);
    vector<vector<int>> subset_collection;

    for (int setCnt = 0; setCnt < total_set_cnt; ++setCnt) {
        vector<int> subset;
        cout << "{ ";
        for (int mask = 0; mask < len; ++mask) {
            if (setCnt & (1 << (mask))){
                subset.push_back(set[mask]);
                cout << set[mask] << " ";
            }
        }
        cout << "}" << endl;
        subset_collection.push_back(subset);
    }

    return subset_collection;
}


int main() {
    cout << (3 & 7);
    int len, temp;
    vector<int> set;
    cin >> len;
    for (int i = 0; i < len; ++i) {
        cin >> temp;
        set.push_back(temp);
    }

    getSubsets(set);

    return 0;
}
