#include <iostream>
#include <fstream>

#include "measure.h"
#include "nspFunctions.h"
#include "defs.h"

extern int g_lattice[L][L][L][4];
extern double g_magneticField[3];

extern double g_mag_x;
extern double g_mag_y;
extern double g_mag_z;

extern int g_Nspins;
extern int N_external_loop;
extern int wormSize;

extern double g_systemEnergy;
extern double g_energy;
extern double g_energy_sq;

extern double g_systemMagnetisation;
extern double g_mag;
extern double g_magx;
extern double g_mag_sq;

extern int g_length;

/// <summary>
/// Measure the lattice properties and store it in the evolution.txt file.
/// </summary>
/// <param name="T"></param> Lattice temperature
void latticeMeasure(bool spin_configUpdate) {

	int ix, iy, iz, itetra, isubmit;

	double ener = 0;
	double mag = 0;
	double magx = 0;
	for (ix = 0; ix < L; ix++) {
		for (iy = 0; iy < L; iy++) {
			for (iz = 0; iz < L; iz++) {
				for (itetra = 0; itetra < 4; itetra++) {
					for (isubmit = 0; isubmit < 4; isubmit++) {
						 ener += calculateEnergy(ix, iy, iz, itetra, isubmit);
						 mag += calculateMag(ix, iy, iz, itetra, isubmit);
						 magx += calculateMagX(ix, iy, iz, itetra, isubmit);
					}
				}
			}
		}
	}

	if (spin_configUpdate) { updateNSP(); }

	g_energy += ener;
	g_energy_sq += ener * ener;
	g_mag += mag;
	g_magx += magx;
	g_mag_sq += mag * mag;
}

/// <summary>
/// Average all the measures done on the lattice.
/// </summary>
void endMeasure(double T, int Nmeasurment) {

	//Average over the measurments by dividing by Nmeas and on all the spins by dividing by the number of spins.
	g_energy /= Nmeasurment;
	g_energy /= g_Nspins;
	g_energy_sq /= Nmeasurment;
	g_energy_sq /= g_Nspins;
	g_energy_sq /= g_Nspins;

	g_mag /= Nmeasurment;
	g_mag /= g_Nspins;
	g_mag_sq /= Nmeasurment;
	g_mag_sq /= g_Nspins;
	g_mag_sq /= g_Nspins;

	g_magx /= Nmeasurment;
	g_magx /= g_Nspins;

	double Cb = g_energy_sq - g_energy * g_energy;
	Cb *= g_Nspins;
	Cb /= T;
	Cb /= T;

	double Chi = g_mag_sq - g_mag * g_mag;
	Chi *= g_Nspins;
	Chi /= T;

	std::cout << std::endl;
	std::cout << "<E>  = " << g_energy << std::endl;
	std::cout << "<E2> = " << g_energy_sq << std::endl;
	std::cout << "Cb   = " << Cb << std::endl;
	std::cout << std::endl;
	std::cout << "<m>  = " << g_mag << std::endl;
	std::cout << "<m2> = " << g_mag_sq << std::endl;
	std::cout << "Chi  = " << Chi << std::endl;
	std::cout << std::endl;

	// g_length / Nmeasurments is the average length of an added worm in the system.

	//Save the equillibrium value
	std::fstream myfile;
	myfile.open("evolution.txt", std::fstream::out | std::fstream::app);
	myfile << Phi << "\t" << Theta << "\t" << T << "\t\t" << g_energy << "\t" << g_energy_sq << "\t" << Cb << "\t";
	myfile << "\t" << g_magx << "\t" << g_mag << "\t" << g_mag_sq << "\t" << Chi << "\t" << T * Chi << std::endl;
	myfile.close();

	if (DoYouWantNeutronScatteringPlot) { endNSPMeasures(); }

	g_energy = 0;
	g_energy_sq = 0;

	g_mag = 0;
	g_magx = 0;
	g_mag_sq = 0;
}

/// <summary>
/// Calculate the Zeeman energy of the spin located at the given position.
/// </summary>
/// <param name="ix"></param>
/// <param name="iy"></param>
/// <param name="iz"></param>
/// <param name="itetra"></param>
/// <param name="ispin"></param>
/// <returns></returns>
double calculateEnergy(int ix, int iy, int iz, int itetra, int ispin) {
	double ener = - (S[ispin][0] * g_magneticField[0] + S[ispin][1] * g_magneticField[1] + S[ispin][2] * g_magneticField[2]);
	if (ispin == g_lattice[ix][iy][iz][itetra]) {//spin in
		ener = - ener;
	}
	return(ener);
}

/// <summary>
/// Calculate the magnetisation along the x axis of the spin located at the given position.
/// </summary>
/// <param name="ix"></param>
/// <param name="iy"></param>
/// <param name="iz"></param>
/// <param name="itetra"></param>
/// <param name="ispin"></param>
/// <returns></returns>
double calculateMagX(int ix, int iy, int iz, int itetra, int ispin) {
	double mag_x = S[ispin][0]; //True if spin in
	if (ispin == g_lattice[ix][iy][iz][itetra]) {//spin out
		return (-mag_x);
	}
	return (mag_x);
}

/// <summary>
/// Calculate the magnetisation along the x axis of the spin located at the given position.
/// </summary>
/// <param name="ix"></param>
/// <param name="iy"></param>
/// <param name="iz"></param>
/// <param name="itetra"></param>
/// <param name="ispin"></param>
/// <returns></returns>
double calculateMagY(int ix, int iy, int iz, int itetra, int ispin) {
	double mag_y = S[ispin][1]; //True if spin in
	if (ispin == g_lattice[ix][iy][iz][itetra]) {//spin out
		return (-mag_y);
	}
	return (mag_y);
}

/// <summary>
/// Calculate the magnetisation along the x axis of the spin located at the given position.
/// </summary>
/// <param name="ix"></param>
/// <param name="iy"></param>
/// <param name="iz"></param>
/// <param name="itetra"></param>
/// <param name="ispin"></param>
/// <returns></returns>
double calculateMagZ(int ix, int iy, int iz, int itetra, int ispin) {
	double mag_z = S[ispin][2]; //True if spin in
	if (ispin == g_lattice[ix][iy][iz][itetra]) {//spin out
		return (-mag_z);
	}
	return (mag_z);
}

/// <summary>
/// Calculate the magnetisation along the magnetic field axis of the spin located at the given position.
/// </summary>
/// <param name="ix"></param>
/// <param name="iy"></param>
/// <param name="iz"></param>
/// <param name="itetra"></param>
/// <param name="ispin"></param>
/// <returns></returns>
double calculateMag(int ix, int iy, int iz, int itetra, int ispin) {
	return(calculateMagX(ix, iy, iz, itetra, ispin) * g_magneticField[0] + calculateMagY(ix, iy, iz, itetra, ispin) * g_magneticField[1] + calculateMagZ(ix, iy, iz, itetra, ispin) * g_magneticField[2]);
}
