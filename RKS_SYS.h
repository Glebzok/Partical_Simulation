#ifndef RKS_SYS_H
#define RKS_SYS_H

#include "functions_sys.h"

class RKS_SYS
{
    vector<double> t; // time
    vector<vector<double>> x; // unknown variables
	vector<double> m; // mass

    vector<Function*> funs; //functions

    double h; // step
    long n; // number of steps

    double k1(int i, Function* f);
    double k2(int i, Function* f);
    double k3(int i, Function* f);
    double k4(int i, Function* f);

    vector<vector<double>> solve();
public:
    vector<vector<double>> operator() (vector<Function*>& funs, double t0, double t1, vector<double>& x0, vector<double>& m, double h = 0.01);

};

#endif // RKS_SYS_H
