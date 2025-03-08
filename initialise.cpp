#include <iostream>
#include <fstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <cmath>

#include "initialise.h"
#include "nspFunctions.h"
#include "defs.h"

extern int g_lattice[L][L][L][4];
extern double g_proba[4][4];
extern double g_magneticField[3];

extern double g_energy;
extern double g_energy_sq;
extern double g_mag;
extern double g_mag_sq;
extern int N_external_loop;

extern int g_Nspins;

extern double g_energyDifference[4][4];
extern double g_magnetisationDifference[4][4];

void initialise() {
	//Initialise the random seed.
	srand(time(NULL));
	double A = (double)rand() / RAND_MAX;

	//initialise the magnetic field (in the ux, uy, uz base, cf next.cpp).
	magFieldInitialisation(Theta, Phi);

	//Initialise the measure doubles
	g_energy = 0;
	g_energy_sq = 0;
	g_mag = 0;
	g_mag_sq = 0;
	N_external_loop = 0;

	g_Nspins = 16 * L * L * L;

	//Initialise the lattice.
	latticeInitialisation();

	//Calculate g_energyDifference and g_magnetisationDifference.
	differenceInitialisation();


	//Initialise the probability matrix.
	probaInitialisation(Ti, Theta, Phi);

	//Initialise the objects requiered for NSP
	if (DoYouWantNeutronScatteringPlot) { nspInitialisation(); }

	//Initialise the results files.
	std::remove("evolution.txt");

	std::fstream myfile;
	myfile.open("evolution.txt", std::fstream::out | std::fstream::app);
	myfile << "Phi\tTheta\tT\t\t<E>\t<E²>\tCb\t\t<mx>\t<m>\t<m²>\tChi\tT*Chi\t\tL = "<< L << "\tNspins = " << g_Nspins << "\tNmeas = " << Nmeas << "\tNeq = " << Neq << std::endl;
	myfile.close();

	std::remove("results.ply");
	std::remove("cube.ply");


}

/// <summary>
/// initialise the magnetic field (in the ux, uy, uz base, cf next.cpp).
/// </summary>
/// <param name="theta"></param>
/// <param name="phi"></param>
void magFieldInitialisation(double theta, double phi) {
	g_magneticField[0] = B * sin(theta) * cos(phi);
	g_magneticField[1] = B * sin(theta) * sin(phi);
	g_magneticField[2] = B * cos(theta);
}

/// <summary>
/// Intialise the lattice. All dimers point toward 0.
/// </summary>
void latticeInitialisation() {
	int ix, iy, iz, tetra;
	for (ix = 0; ix < L; ix++) {
		for (iy = 0; iy < L; iy++) {
			for (iz = 0; iz < L; iz++) {
				for (tetra = 0; tetra < 4; tetra++) {
					g_lattice[ix][iy][iz][tetra] = 0;
				}
			}
		}
	}
}

/// <summary>
/// Calculate the energy difference matrix, used to calculate the energy variation after adding a loop.
/// </summary>
/// <param name="kT"></param>
/// <returns></returns>
void differenceInitialisation() {
	double e[4]; //e[i] will contain the Zeeman energy of the spin i when they're in.

	int ispin;
	for (ispin = 0; ispin < 4; ispin++) {
		e[ispin] = -(S[ispin][0] * g_magneticField[0] + S[ispin][1] * g_magneticField[1] + S[ispin][2] * g_magneticField[2]);
	}

	//g_energyDifference[f][i] is the energy difference Ef-Ei, where Ej is the energy of a tetrahedron when the dimer points out at j.
	g_energyDifference[0][0] = 0;
	g_energyDifference[0][1] = 2 * (e[1] - e[0]);
	g_energyDifference[0][2] = 2 * (e[2] - e[0]);
	g_energyDifference[0][3] = 2 * (e[3] - e[0]);

	g_energyDifference[1][0] = 2 * (e[0] - e[1]);
	g_energyDifference[1][1] = 0;
	g_energyDifference[1][2] = 2 * (e[2] - e[1]);
	g_energyDifference[1][3] = 2 * (e[3] - e[1]);

	g_energyDifference[2][0] = 2 * (e[0] - e[2]);
	g_energyDifference[2][1] = 2 * (e[1] - e[2]);
	g_energyDifference[2][2] = 0;
	g_energyDifference[2][3] = 2 * (e[3] - e[2]);

	g_energyDifference[3][0] = 2 * (e[0] - e[3]);
	g_energyDifference[3][1] = 2 * (e[1] - e[3]);
	g_energyDifference[3][2] = 2 * (e[2] - e[3]);
	g_energyDifference[3][3] = 0;


	double m[4]; //m[i] will contain the magnetisation of the spin i when they're in.

	for (ispin = 0; ispin < 4; ispin++) {
		m[ispin] =	(S[ispin][0] * g_magneticField[0] + S[ispin][1] * g_magneticField[1] + S[ispin][2] * g_magneticField[2]);
	}

	//g_magnetisationDifference[f][i] is the magnetisation difference Mf-Mi, where Mj is the magnetisation of a tetrahedron when the dimer points out at j.
	g_magnetisationDifference[0][0] = 0;
	g_magnetisationDifference[0][1] = 2 * (m[1] - m[0]);
	g_magnetisationDifference[0][2] = 2 * (m[2] - m[0]);
	g_magnetisationDifference[0][3] = 2 * (m[3] - m[0]);

	g_magnetisationDifference[1][0] = 2 * (m[0] - m[1]);
	g_magnetisationDifference[1][1] = 0;
	g_magnetisationDifference[1][2] = 2 * (m[2] - m[1]);
	g_magnetisationDifference[1][3] = 2 * (m[3] - m[1]);

	g_magnetisationDifference[2][0] = 2 * (m[0] - m[2]);
	g_magnetisationDifference[2][1] = 2 * (m[1] - m[2]);
	g_magnetisationDifference[2][2] = 0;
	g_magnetisationDifference[2][3] = 2 * (m[3] - m[2]);

	g_magnetisationDifference[3][0] = 2 * (m[0] - m[3]);
	g_magnetisationDifference[3][1] = 2 * (m[1] - m[3]);
	g_magnetisationDifference[3][2] = 2 * (m[2] - m[3]);
	g_magnetisationDifference[3][3] = 0;
}

/// <summary>
/// Initialise the probability matrix. Return true if the T>Tc
/// </summary>
bool probaInitialisation(double kT, double theta, double phi) {
	//initialise the magnetic field.
	magFieldInitialisation(theta, phi);

	//initialise the differences of tetrahedron thermodynamical values between two states.
	differenceInitialisation();

	//Initialise the different probability involved
	double mu0, mu1, mu2, mu3;
	double e0, e1, e2, e3;
	double z0, z1, z2, z3;
	mu0 = +2 * B * cos(theta);
	mu1 = -2 * B * (+cos(theta) - 2 * sqrt(2) * sin(theta) * cos(phi)) / 3;
	mu2 = -2 * B * (+cos(theta) + sqrt(2) * sin(theta) * (cos(phi) - sqrt(3) * sin(phi))) / 3;
	mu3 = -2 * B * (+cos(theta) + sqrt(2) * sin(theta) * (cos(phi) + sqrt(3) * sin(phi))) / 3;

	e0 = -mu0;
	e1 = -mu1;
	e2 = -mu2;
	e3 = -mu3;

	z0 = exp(mu0 / kT);
	z1 = exp(mu1 / kT);
	z2 = exp(mu2 / kT);
	z3 = exp(mu3 / kT);

	double p0 = z0 / (z1 + z2 + z3);



	g_proba[0][0] = z0 / (z0 + z1 + z2 + z3);
	g_proba[1][0] = z1 / (z0 + z1 + z2 + z3);
	g_proba[2][0] = z2 / (z0 + z1 + z2 + z3);
	g_proba[3][0] = z3 / (z0 + z1 + z2 + z3);

	g_proba[0][1] = z0 / (z0 + z1 + z2 + z3);
	g_proba[1][1] = z1 / (z0 + z1 + z2 + z3);
	g_proba[2][1] = z2 / (z0 + z1 + z2 + z3);
	g_proba[3][1] = z3 / (z0 + z1 + z2 + z3);

	g_proba[0][2] = z0 / (z0 + z1 + z2 + z3);
	g_proba[1][2] = z1 / (z0 + z1 + z2 + z3);
	g_proba[2][2] = z2 / (z0 + z1 + z2 + z3);
	g_proba[3][2] = z3 / (z0 + z1 + z2 + z3);

	g_proba[0][3] = z0 / (z0 + z1 + z2 + z3);
	g_proba[1][3] = z1 / (z0 + z1 + z2 + z3);
	g_proba[2][3] = z2 / (z0 + z1 + z2 + z3);
	g_proba[3][3] = z3 / (z0 + z1 + z2 + z3);





	/*
	//if we come from spin 0 :g_proba[0][0] = 0;
	g_proba[1][0] = z1 / (z1 + z2 + z3);
	g_proba[2][0] = z2 / (z1 + z2 + z3);
	g_proba[3][0] = z3 / (z1 + z2 + z3);

	//if we came from spin 1 :
	g_proba[0][1] = p0;
	g_proba[1][1] = 0;
	g_proba[2][1] = (+z1 + z2 - z3) * (1 - p0) / (2 * z1);
	g_proba[3][1] = (+z1 - z2 + z3) * (1 - p0) / (2 * z1);

	//if we came from spin 2 :
	g_proba[0][2] = p0;
	g_proba[1][2] = (+z1 + z2 - z3) * (1 - p0) / (2 * z2);
	g_proba[2][2] = 0;
	g_proba[3][2] = (-z1 + z2 + z3) * (1 - p0) / (2 * z2);

	//if we came from spin 3 :
	g_proba[0][3] = p0;
	g_proba[1][3] = (+z1 - z2 + z3) * (1 - p0) / (2 * z3);
	g_proba[2][3] = (-z1 + z2 + z3) * (1 - p0) / (2 * z3);
	g_proba[3][3] = 0;*/
	return(true);
}