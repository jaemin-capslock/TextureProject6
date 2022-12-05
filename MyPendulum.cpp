#include "MyPendulum.h"
#include "MathMisc.h"


MyPendulum::MyPendulum(const Pendulum& upper, const Pendulum& lower, double dt, double g) :
	m_theta1(upper.theta),
	m_omega1(upper.omega),
	m_l1(upper.len),
	m_m1(upper.mass),
	m_v1(upper.v),
	m_r1(upper.r),
	m_k1(upper.k),

	m_theta2(lower.theta),
	m_omega2(lower.omega),
	m_l2(lower.len),
	m_m2(lower.mass),

	m_v2(lower.v),
	m_r2(lower.r),
	m_k2(lower.k),

	m_dt(dt),
	m_g(g),
	m_time(0.0)
{}


void MyPendulum::update() {
	//assert(newTime >= m_time);

	
		const double yin[NUM_EQNS] = { m_theta1, m_omega1, m_v1, m_r1, m_theta2, m_omega2, m_v2, m_r2 };
		double yout[NUM_EQNS];

		solveODEs(yin, yout);

		m_theta1 = yout[THETA_1];
		m_omega1 = yout[OMEGA_1];
		m_v1 = yout[V_1];
		m_r1 = yout[R_1];
		m_theta2 = yout[THETA_2];
		m_omega2 = yout[OMEGA_2];
		m_v2 = yout[V_2];
		m_r2 = yout[R_2];
	
}

void MyPendulum::derivs(const double* yin, double* dydx) {

	double delta = yin[THETA_1] - yin[THETA_2];
	dydx[THETA_1] = yin[OMEGA_1];
	

	dydx[OMEGA_1] = (m_k2 * (m_l2 - yin[R_2]) * sin(delta) - (m_m1 * m_g * sin(yin[THETA_1])) - (2.0 * m_m1 * yin[V_1] * yin[OMEGA_1])) / (m_m1 * yin[R_1]);

	dydx[R_1] = yin[V_1];

	dydx[V_1] = (m_k1 * (m_l1 - yin[R_1]) - m_k2 * (m_l2 - yin[R_2]) * cos(delta) + m_m1 * m_g * cos(yin[THETA_1]) + (m_m1 * yin[R_1] * yin[OMEGA_1] * yin[OMEGA_1])) / (m_m1);


	dydx[THETA_2] = yin[OMEGA_2];

	dydx[OMEGA_2] = ((-2.0 * yin[V_2] * yin[OMEGA_2]) - m_k1 * (m_l1 - m_r1) * sin(delta)) / (m_m1 * yin[R_2]);

	dydx[R_2] = yin[V_2];

	dydx[V_2] = (m_k2 * (m_m1 + m_m2) * (m_l2 - yin[R_2]) + (m_m1 * m_m2 * yin[R_2] * yin[OMEGA_2] * yin[OMEGA_2]) - m_m2 * m_k1 * (m_l1 - yin[R_1]) * cos(delta)) / (m_m1 * m_m2);

	 

}

void MyPendulum::solveODEs(const double* yin, double* yout) {

	// RK4 Method.

	double dydx[NUM_EQNS], dydxt[NUM_EQNS], yt[NUM_EQNS];
	double k1[NUM_EQNS], k2[NUM_EQNS], k3[NUM_EQNS], k4[NUM_EQNS];

	derivs(yin, dydx);

	for (int i = 0; i < NUM_EQNS; ++i) {
		k1[i] = m_dt * dydx[i];
		yt[i] = yin[i] + 0.5 * k1[i];
	}

	derivs(yt, dydxt);

	for (int i = 0; i < NUM_EQNS; ++i) {
		k2[i] = m_dt * dydxt[i];
		yt[i] = yin[i] + 0.5 * k2[i];
	}
	derivs(yt, dydxt);

	for (int i = 0; i < NUM_EQNS; ++i) {
		k3[i] = m_dt * dydxt[i];
		yt[i] = yin[i] + k3[i];
	}

	derivs(yt, dydxt);

	for (int i = 0; i < NUM_EQNS; ++i) {
		k4[i] = m_dt * dydxt[i];
		yout[i] = yin[i] + (k1[i] / 6.0) + (k2[i] / 3.0) + (k3[i] / 3.0) + (k4[i] / 6.0);
	}
}