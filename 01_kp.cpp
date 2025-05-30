#include <iostream>
#include <algorithm>
#include <vector>

#include "knapsack.h"

using namespace std;

// used this website to check
// https://augustineaykara.github.io/Knapsack-Calculator/

// 0/1 KP Problem
// like fractional but you can only get the whole item or not

// for printing purposes
struct Item {
    double value;
    int weight;
    int identifier;
};

// bottom-up approach dynamic prog
vector<vector<int>> kp_01(vector<Item>& items, int capacity) {
    vector<vector<int>> table;

    int n_items = items.size();

    // n_items + 1 since we need the "0" item
    // 0 items means 0 val
    table.resize(n_items + 1);
    table[0].resize(capacity + 1);

    // start at the n = 1 row (from slides)
    for (int i = 1; i <= n_items; i++) {
        // 0 to "capacity" capacity
        table[i].resize(capacity + 1);

        // skip the 0 column since a bag of 0 cap cannot fit anything
        // j is cap of bag
        for (int j = 1; j <= capacity; j++) {
            int cur_value = 0;

            // kasya yung item
            if (items[i - 1].weight <= j) {
                int natitirang_cap = j - items[i - 1].weight;
                // logic here is since we have picked this item
                // we get the value in table of prev item when 
                // capacity is "natitirang_cap" and add to the value of this item
                cur_value = items[i - 1].value + table[i - 1][natitirang_cap];
            }

            // compare the cur_value and the value at the same capacity
            // but different item
            if (cur_value > table[i - 1][j]) {
                table[i][j] = cur_value;
            } else {
                table[i][j] = table[i - 1][j];
            }
        }
    }

    return table;
}

void processTable(vector<vector<int>>& table, vector<Item>& items) {
    int n_rows = table.size();
    int n_columns = table[0].size();

    cout << "Maximum value: " << table[n_rows - 1][n_columns - 1] << endl;
    
    // start at bottom-rightmost
    cout << "Items included are: " << endl;
    for (int i = n_rows - 1; i > 0;) {
        for (int j = n_columns - 1; i > 0;) {
            if (table[i][j] == table[i - 1][j]) {
                i = i - 1;
            } else {
                // this i-item is part of knapsack
                cout << "Item #" << i << endl;

                j = j - items[i - 1].weight;
                i = i - 1;
            }
        }
    }
}

void do_kp_01() {
    // input handling
    int n_capacity;
    cout << "Enter capacity of knapsack: ";
    cin >> n_capacity;

    int n_items;
    cout << "Enter number of items: ";
    cin >> n_items;

    vector<Item> items;
    items.resize(n_items);

    cout << "Enter value of each item (space-separated): ";
    for (int i = 0; i < n_items; i++) {
        cin >> items[i].value;
        items[i].identifier = i + 1;
    }

    cout << "Enter weight of each item (space-separated): ";
    for (int i = 0; i < n_items; i++) {
        cin >> items[i].weight;
    }

    vector<vector<int>> table = kp_01(items, n_capacity);
    processTable(table, items);

    cout << "--DONE--" << endl;
}