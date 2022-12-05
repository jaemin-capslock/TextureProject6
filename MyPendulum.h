#pragma once

/*
* Code based in https://freddie.witherden.org/tools/doublependulum/report.pdf, but with few alterations after on.
*/
struct Pendulum {

	Pendulum(double t, double o, double v, double l, double m, double r, double k) : theta(t), omega(o), v(v), len(l), mass(m), r(r), k(k)
	{}
	double theta; // angle
	double omega; // angular velocity 
	double v; // dot of r
	double r; // length of spring
	double len; // length of the pendulum
	double mass; // mass of the ball attached to the end of pendulum
	double k; // spring constant




};

class MyPendulum {
public:
	MyPendulum(const Pendulum& upper, const Pendulum& lower,
		double dt = 0.01, double g = 9.81);

	void update();
	double theta1() {
		return m_theta1;
	}
	
	double omega1() {
		return m_omega1;

	}

	double m1() {
		return m_m1;
	}

	double l1() {
		return m_l1;
	}

	double v1() {
		return m_v1;
	}

	double r1() {
		return m_r1;
	}

	double k1(){
		return m_k1;
	}

	double theta2() {
		return m_theta2;
	}

	double omega2() {
		return m_omega2;

	}

	double m2() {
		return m_m2;
	}

	double l2() {
		return m_l2;
	}

	double v2() {
		return m_v2;
	}

	double r2() {
		return m_r2;
	}

	double k2() {
		return m_k2;
	}

	double time() {
		return m_time;
	}

protected:

	enum {
		THETA_1,
		OMEGA_1,
		V_1,
		R_1,
		THETA_2,
		OMEGA_2,
		V_2,
		R_2,
		NUM_EQNS
	};

	void derivs(const double* yin, double* dydx);

	void solveODEs(const double* yin, double* yout);

	// Angle from the y axis, radians.
	double m_theta1;

	double m_omega1;

	double m_l1;

	double m_m1;

	double m_v1;

	double m_r1;

	double m_k1;

	double m_theta2;

	double m_omega2;

	double m_v2;

	double m_r2;

	double m_l2;

	double m_m2;

	double m_k2;

	const double m_dt;

	const double m_g;

	double m_time;
};