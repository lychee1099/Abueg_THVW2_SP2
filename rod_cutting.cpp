#include <iostream>
#include <vector>

#include "rod_cutting.h"

using namespace std;

// Rod Cutting Problem
// rod of n length and an price per length array
// maximize price

pair<vector<int>, vector<int>> rod_cutting(vector<int>& price_per_length, int length) {
    vector<int> table;
    vector<int> sol;

    // to include 0
    table.resize(length + 1);
    sol.resize(length + 1);
    for (int i = 1; i <= length; i++) {
        // gist: get best price per length by either checking its price as a whole
        // or cutting it into smaller rods, which have optimal solution
        // basically, when we cut it, one of the pieces can further be cut based on the table
        for (int j = 1; j <= i; j++) {
            int cur_value = 0;
            // "price_per_length[j]"" is the whole price of one piece
            // "table[i-j]" is the price of the other piece, which may be already cut into several pieces
            cur_value = price_per_length[j - 1] + table[i - j];
            if (cur_value > table[i]) {
                table[i] = cur_value;
                sol[i] = j;
            }
        }
    }

    return {table, sol};
}

void processRodCut(pair<vector<int>, vector<int>>& table_sol, int length) {
    vector<int>& table = table_sol.first;
    vector<int>& sol = table_sol.second;

    int n_table = table.size();
    int n_sol = sol.size();

    cout << "Maximum value: " << table[n_table - 1] << endl;

    vector<int> what_to_sell;
    for (int i = n_sol - 1; length > 0 && i > 0;) {
        what_to_sell.push_back(sol[i]);
        i = length - sol[i];
        length = length - sol[i];
    }

    cout << "Rod should be cut into: ";
    for (int i = 0; i < what_to_sell.size(); i++) {
        cout << what_to_sell[i] << " ";
    }
    cout << endl;
}

void doRodCut() {
    // Input handling
    int n_length;
    cout << "Enter length of rod: ";
    cin >> n_length;

    cout << "Enter prices per (integer) length of rod: ";
    vector<int> price_per_length;
    price_per_length.resize(n_length);
    for (int i = 0; i < n_length; i++) {
        cin >> price_per_length[i];
    }

    pair<vector<int>, vector<int>> table_sol = rod_cutting(price_per_length, n_length);
    processRodCut(table_sol, n_length);
}