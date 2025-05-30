#include <iostream>
#include <algorithm>
#include <vector>

#include "knapsack.h"

using namespace std;

// used this website to check
// https://augustineaykara.github.io/Knapsack-Calculator/

// for printing purposes
struct Item {
    double value;
    int weight;
    int identifier;
};

// Fractional KP Problem
// maximize a knapsack of n capacity
// get highest value per weight of items

bool compare(Item a, Item b) {
    return a.value > b.value;
}

// return list of items to be put in knapsack
vector<Item> frac_kp(vector<Item>& items, int capacity) {
    // get value per weight of items
    int n_items = items.size();

    // we will also use this vector to represent the final knapsack
    vector<Item> value_per_weight;
    value_per_weight.resize(n_items);

    for (int i = 0; i < n_items; i++) {
        value_per_weight[i].value = items[i].value / items[i].weight;
        value_per_weight[i].weight= items[i].weight;
        value_per_weight[i].identifier = items[i].identifier;
    }

    // sort value per weight in increasing order
    sort(value_per_weight.begin(), value_per_weight.end(), compare);

    // iterate through all value per weight starting from highest
    int i = 0;
    for (; i < n_items; i++) {
        // put as much of the item as we can
        // whole item can be fit
        if (capacity >= value_per_weight[i].weight) {
            // we can safely do this since we do not need to check this item again
            value_per_weight[i].value = value_per_weight[i].value * value_per_weight[i].weight;
            capacity -= value_per_weight[i].weight;
        } else {
            // only a fraction of item can be fit
            value_per_weight[i].value = value_per_weight[i].value * double(capacity);
            value_per_weight[i].weight = capacity;
            break;

            // we know it is full since we filled it up with only the fraction of an item
            // or kapag binaliktad, we fill up the bag with a fraction of the item
            // like the dice game in LE2 hehehhe
        }
    }

    // remove items
    value_per_weight.resize(i + 1);
    
    return value_per_weight;
}

void doFractionalKP() {
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

    vector<Item> greedy_knapsack = frac_kp(items, n_capacity);
    double max_value = 0;
    int weight = 0;

    cout << "Items included are: " << endl;
    for (int i = 0; i < greedy_knapsack.size(); i++) {
        cout << greedy_knapsack[i].weight << " kg of Item #" << greedy_knapsack[i].identifier << endl;
        max_value += greedy_knapsack[i].value;
        weight += greedy_knapsack[i].weight;
    }

    cout << "Maximum value: " << max_value << endl;
    cout << "Weight of items: " << weight << endl;

    cout << "--DONE--" << endl;
}