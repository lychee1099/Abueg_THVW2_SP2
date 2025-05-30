#include <iostream>
#include <vector>

#include "act_selection.h"

// for ease of sort
#include <algorithm>

using namespace std;

// Activity Selection Problem
// sort end time from lowest to highest
// select the lowest end time that does not conflict with others

// some constraints:
// only integer start and end time but can easily be modified for floats
// assume that equal start time of one act and end time of another means conflict

vector<pair<int, int>> act_selection(vector<pair<int, int>> activities) {
    vector<pair<int, int>> schedule;
    int n_acts = activities.size();

    // sort activites here
    sort(activities.begin(), activities.end());

    // since sorted, first activity will be added immediately
    schedule.push_back(activities[0]);
    int last_endtime = activities[0].first;

    for (int i = 1; i < n_acts; i++) {
        // start time is greater than end time of last added
        // it means no conflict
        if (activities[i].second > last_endtime) {
            schedule.push_back(activities[i]);
            last_endtime = activities[i].first;
        }
    }

    return schedule;
}

void doActSelection() {
    // Input handling
    int n_acts;
    cout << "Enter number of activities: ";
    cin >> n_acts;

    // first - end time; second - start time
    // so sorting will be fine
    vector<pair<int, int>> activities;
    activities.resize(n_acts);

    cout << "Enter start time of each activies (space-separated): ";
    for (int i = 0; i < n_acts; i++) {
        cin >> activities[i].second;
    }

    cout << "Enter end time of each activies (space-separated): ";
    for (int i = 0; i < n_acts; i++) {
        cin >> activities[i].first;
    }

    vector<pair<int, int>> sched = act_selection(activities);
    cout << "Activities: " << endl;
    for (int i = 0; i < sched.size(); i++) {
        cout << sched[i].second << ", " << sched[i].first << endl;
    }

    cout << "No. of activities: " << sched.size() << endl;

    cout << "--DONE--" << endl;
}