#include <vector>
#include <cmath>

using namespace std;

class Force{
public:
	vector<Force*> forces;
	vector<double> ks;
	Force(){
		vector <double> s;
		ks = s;
	}
	
	virtual double operator()(double t, double x, double v, double m = 0) = 0;
};

class Force_System{
public:
	Force* x_force;
	Force* y_force;
	Force* z_force;
	Force_System(Force* f1, Force* f2, Force* f3) : x_force(f1), y_force(f2), z_force(f3){}
	Force_System(){}
};

class Bounce : public Force{
public:
    Bounce(double h, double fr_k)
    {
        ks.push_back(h);
        ks.push_back(fr_k);
    }
    double operator()(double t, double x, double v, double m){
        if (abs(x-ks[0]) < 1 && (x-ks[0])*v < 0)
            return 2000;
        else return 0;
    }
};

class Elastic : public Force{
public:
    Elastic(double k, double y){
        ks.push_back(k);
        ks.push_back(y);
    }
    double operator ()(double t, double x, double v, double m){
        return (-ks[0]*(x - ks[1])/m);
    }
};

class Gravity : public Force{
public:
	Gravity(double g){
		ks.push_back(g);
	}
	double operator()(double t, double x, double v, double m){
        return(-ks.at(0));
	}
};

class Viscous_Drag : public Force{
public:
	Viscous_Drag(double k_drag){
		ks.push_back(k_drag);
	}
	double operator()(double t, double x, double v, double m){
		return(- ks.at(0) * v / m);
	}
};

class NoForce : public Force{
public:
	double operator()(double t, double x, double v, double m){
		return(0);
	}
};

class Force_Sum :public Force{
public:
	Force_Sum(vector<Force*> fs){
		this->forces = fs;
	}
	double operator()(double t, double x, double v, double m){
		double res = 0;
		for (auto i : this->forces){
			res += (*i)(t, x, v, m);
		}
		return res;
	}
};

class Vel : public Force{
public:
	double operator()(double t, double x, double v, double m){
		return(v);
	}
};


/*class Spring : Force{
	double k_s;		//spring constant
	double k_d;		//damping constant

	double r;		//rest length
	double l;		//length

public:
	Spring(double k_drag) : k_drag(k_drag) {}
	double operator()(double v){
		return(-k_drag * v);
	}
};*/
/*
double f0(double m, double t, double x, double v){
	return 0;
}

double f1(double m, double t, double x, double v){
	return m * 9.8;
}

double f2(double m, double t, double x, double v){
	return -0.5 * v;
}

double force_sum(vector<double(*)(double m, double t, double x, double v)> fs, double m, double t, double x, double v){
	double res;
	for (int i = 0; i != fs.size(); i++){
		res += fs.at(i)(m, t, x, v);
	}
	return res;
}*/
