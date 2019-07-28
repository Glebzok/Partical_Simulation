#ifndef RKS_S_H
#define RKS_S_H

#include "functions3d.h"


class RKS{
    vector<double> t; // time
    vector<vector<double>> x; // unknown variables
    double m; //mass

    vector<Force*> funs; //functions

    double h; // step
    long n; // number of steps

    double k1(int i, Force* f);
    double k2(int i, Force* f);
    double k3(int i, Force* f);
    double k4(int i, Force* f);

    vector<vector<double>> solve();
public:
    vector<vector<double>> operator() (vector<Force*> funs, double t0, double t1, vector<double>& x0, double m,  double h = 0.01);
};

class RKS_S{
    vector<double> t; // time
    vector<vector<double>> x; // unknown variables
    double m; //mass

    vector<Force*> funs; //functions

    double h; // step
    long n; // number of steps

    double k1(int i, Force* f);
    double k2(int i, Force* f);
    double k3(int i, Force* f);
    double k4(int i, Force* f);

    vector<vector<double>> solve();
public:
    vector<vector<double>> operator() (vector<Force*> funs, double t0, double t1, vector<double>& x0, double m,  double h = 0.01);
};

#endif // RKS_S_H
