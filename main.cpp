#include <iostream>

#include "act_selection.h"
#include "knapsack.h" // contains 0/1 and fractional
#include "kruskal.h"
#include "rod_cutting.h"

using namespace std;

int main() {
    bool run = true;
    while (run) {
        int choice;
        cout << "Choose which problem to do: " << endl;
        cout << "(0) Activity Selection\n(1) 0/1 Knapsack\n(2) Fractional Knapsack\n" <<
        "(3) Kruskal Algorithm\n(4) Rod Cutting Problem" << endl;
        cout << "Choice: ";
        cin >> choice;

        switch(choice) {
            case 0:
                doActSelection();
                run = false;
                break;
            case 1:
                do_kp_01();
                run = false;
                break;
            case 2:
                doFractionalKP();
                run = false;
                break;
            case 3:
                doKruskalAlgo();
                run = false;
                break;
            case 4:
                doRodCut();
                run = false;
                break;
            default:
                cout << "You chose none of the choices!" << endl;
        }
    }   
}