#include "body2.h"
#include <iterator>

Particle::Particle(vector<double>& x0, vector<double>& v0, double m, Function_System& f){
    this->m = m;
    this->f = f;
    x.push_back(x0.at(0));
    y.push_back(x0.at(1));
    z.push_back(x0.at(2));

    vx.push_back(v0.at(0));
    vy.push_back(v0.at(1));
    vz.push_back(v0.at(2));
}

Particle_System::Particle_System(vector <Particle*>& ps){
    this->ps = ps;
}

void Particle_System::calculate(double t0, double t1, double h){
    RKS_SYS rks;

    vector<double>X0;
	vector<double>M;
    vector<Function*> Funs;

    for(int i = 0; i != this->ps.size(); i++){
        Velocity* Vx = new Velocity(i, 0);
        Velocity* Vy = new Velocity(i, 1);
        Velocity* Vz = new Velocity(i, 2);
        vector<double> x0 = { this->ps.at(i)->x.at(0), this->ps.at(i)->y.at(0), this->ps.at(i)->z.at(0),
                              this->ps.at(i)->vx.at(0), this->ps.at(i)->vy.at(0), this->ps.at(i)->vz.at(0)};
        X0.insert(X0.end(), x0.begin(), x0.end());
        vector<Function*> funs = { Vx, Vy, Vz, this->ps.at(i)->f.x_force,
                                   this->ps.at(i)->f.y_force, this->ps.at(i)->f.z_force };
        //Funs.insert(Funs.end(), funs.begin(), funs.end());
		copy(funs.begin(), funs.end(), back_inserter(Funs));
		M.push_back(ps.at(i)->m);
    }

    vector<vector<double>> res = rks(Funs, t0, t1, X0, M, h);
    for(int i = 0; i != this->ps.size(); i++){
        this->ps.at(i)->t = res.at(0);
        this->ps.at(i)->x = res.at(1 + 6 * i);
        this->ps.at(i)-> y = res.at(1 + 6 * i + 1);
        this->ps.at(i)-> z = res.at(1 + 6 * i + 2);
        this->ps.at(i)-> vx = res.at(1 + 6 * i + 3);
        this->ps.at(i)-> vy = res.at(1 + 6 * i + 4);
        this->ps.at(i)-> vz = res.at(1 + 6 * i + 5);
    }
}

