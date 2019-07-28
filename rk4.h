#ifndef RK4_H
#define RK4_H

#include "newfunctions.h"

class RK4
{
    vector<double> t; // time
    vector<vector<double>> x; // unknown variables

    vector<Function*> funs; //functions

    double h; // step
    long n; // number of steps

    double k1(int i, Function* f);
    double k2(int i, Function* f);
    double k3(int i, Function* f);
    double k4(int i, Function* f);

    vector<vector<double>> solve();
public:
    vector<vector<double>> operator() (vector<Function*>& funs, double t0, double t1, vector<double>& x0, double h = 0.01);

};

#endif // RK4_H
