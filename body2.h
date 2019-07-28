#ifndef BODY2_H
#define BODY2_H


#include "RKS_SYS.h"

using namespace std;

class Particle{
public:
    vector<double> t;	//time

    vector<double> x;	//position
    vector<double> y;
    vector<double> z;

    vector<double> vx;	//velocity
    vector<double> vy;
    vector<double> vz;

    double m;			//mass

    Function_System f;		//forces


    Particle(vector<double>& x0, vector<double>& v0, double m, Function_System& f);
    Particle(){;}
};

class Particle_System{
public:
    vector<Particle*> ps;		 //particles
    long n;						 //number of particles

    Particle_System(vector<Particle*>& ps);
    void calculate(double t0, double t1, double h = 0.01);
};


#endif // BODY2_H
