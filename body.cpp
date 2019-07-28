#include "body.h"

Particle::Particle(vector<double> x0, vector<double> v0, double m, Force_System f){
	this->m = m;
	this->f = f;
	x.push_back(x0.at(0));
	y.push_back(x0.at(1));
	z.push_back(x0.at(2));

	vx.push_back(v0.at(0));
	vy.push_back(v0.at(1));
	vz.push_back(v0.at(2));
}

/*void Particle::calculate(double t0, double t1, double h){

	RKS rks1;
    Vel v();
	vector<double> x0 = { x.at(0), vx.at(0) };
	vector<Force*> funs = { &v, f.x_force };
	vector<vector<double>> res = rks1(funs, t0, t1, x0, this->m, h);
	this->t = res[0];
	this->x = res[1];
	this->vx = res[2];

	RKS rks2;
	x0 = { y.at(0), vy.at(0) };
	funs = { &v, f.y_force };
	res = rks2(funs, t0, t1, x0, this->m, h);
	this->y = res[1];
	this->vy = res[2];

	RKS rks3;
	x0 = { z.at(0), vz.at(0) };
	funs = { &v, f.z_force };
	res = rks3(funs, t0, t1, x0, this->m, h);
	this->z = res[1];
	this->vz = res[2];
}*/

void Particle::calculate(double t0, double t1, double h){

    RKS rks;
    Vel Vx('x');
    Vel Vy('y');
    Vel Vz('z');
    vector<double> x0 = { x.at(0), y.at(0), z.at(0), vx.at(0), vy.at(0), vz.at(0) };
    vector<Force*> funs = { &Vx, &Vy, &Vz, f.x_force, f.y_force, f.z_force };
    vector<vector<double>> res = rks(funs, t0, t1, x0, this->m, h);
    this->t = res[0];
    this->x = res[1];
    this->y = res[2];
    this->z = res[3];
    this->vx = res[4];
    this->vy = res[5];
    this->vz = res[6];
}

Particle_System::Particle_System(vector <Particle*> ps){
    this->ps = ps;
}

void Particle_System::calculate(double t0, double t1, double h){

}
