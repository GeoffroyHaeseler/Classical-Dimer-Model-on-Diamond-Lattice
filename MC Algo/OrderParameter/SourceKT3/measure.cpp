#include <iostream>
#include <fstream>

#include "measure.h"
#include "nspFunctions.h"
#include "defs.h"

extern int g_lattice[L][L][L][4];
extern double g_magneticField[3];
extern double S[4][3];

extern double g_energy;
extern double g_energy_sq;
extern double g_energy_qa;

extern double g_mag;
extern double g_mag_sq;
extern double g_mag_qa;

extern double g_mag_x;
extern double g_mag_y;
extern double g_mag_z;

extern double g_mag_x_sq;
extern double g_mag_y_sq;
extern double g_mag_z_sq;

extern double g_mag_x_qa;
extern double g_mag_y_qa;
extern double g_mag_z_qa;

extern int g_Nspins;
extern int N_external_loop;
extern int wormSize;

extern double g_systemEnergy;
extern double g_systemMagnetisation;

extern int g_length;

/// <summary>
/// Measure the lattice properties and store it in the evolution.txt file.
/// </summary>
/// <param name="T"></param> Lattice temperature
void latticeMeasure(bool spin_configUpdate) {

	int ix, iy, iz, itetra, ispin;

	double ener = 0;
	double magx = 0;
	double magy = 0;
	double magz = 0;
	for (ix = 0; ix < L; ix++) {
		for (iy = 0; iy < L; iy++) {
			for (iz = 0; iz < L; iz++) {
				for (itetra = 0; itetra < 4; itetra++) {
					for (ispin = 0; ispin < 4; ispin++) {
						ener += calculateEnergy(ix, iy, iz, itetra, ispin);
						magx += calculateMagX  (ix, iy, iz, itetra, ispin);
						magy += calculateMagY  (ix, iy, iz, itetra, ispin);
						magz += calculateMagZ  (ix, iy, iz, itetra, ispin);
					}
				}
			}
		}
	}

	magx /= g_Nspins;
	magy /= g_Nspins;
	magz /= g_Nspins;
	double mag = magx * g_magneticField[0] + magy * g_magneticField[1] + magz * g_magneticField[2];

	g_mag    += mag;
	g_mag_sq += mag * mag;
	g_mag_qa += mag * mag * mag * mag;

	g_mag_x    += magx;
	g_mag_x_sq += magx * magx;
	g_mag_x_qa += magx * magx * magx * magx;

	g_mag_y    += magy;
	g_mag_y_sq += magy * magy;
	g_mag_y_qa += magy * magy * magy * magy;

	g_mag_z    += magz;
	g_mag_z_sq += magz * magz;
	g_mag_z_qa += magz * magz * magz * magz;


	ener /= g_Nspins;

	g_energy    += ener;
	g_energy_sq += ener * ener;
	g_energy_qa += ener * ener * ener * ener;



	if (spin_configUpdate) { updateNSP(); }
}

/// <summary>
/// Average all the measures done on the lattice.
/// </summary>
void endMeasure(double T, int Nmeasurment) {

	//Average over the measurments by dividing by Nmeas and on all the spins by dividing by the number of spins.
	g_energy    /= Nmeasurment;
	g_energy_sq /= Nmeasurment;
	g_energy_qa /= Nmeasurment;
	double energyBinderCumulent = 1.0 - g_energy_qa / (3.0 * g_energy_sq * g_energy_sq);
	double Cb = g_energy_sq - g_energy * g_energy;
	Cb *= g_Nspins;
	Cb /= T;
	Cb /= T;



	g_mag    /= Nmeasurment;
	g_mag_sq /= Nmeasurment;
	g_mag_qa /= Nmeasurment;
	double magBinderCumulent = 1.0 - g_mag_qa / (3.0 * g_mag_sq * g_mag_sq);
	double Chi = g_mag_sq - g_mag * g_mag;
	Chi *= g_Nspins;
	Chi /= T;


	g_mag_x    /= Nmeasurment;
	g_mag_x_sq /= Nmeasurment;
	g_mag_x_qa /= Nmeasurment;
	double magXBinderCumulent = 1.0 - g_mag_x_qa / (3.0 * g_mag_x_sq * g_mag_x_sq);
	double XChi = g_mag_x_sq - g_mag_x * g_mag_x;
	XChi *= g_Nspins;
	XChi /= T;


	g_mag_y    /= Nmeasurment;
	g_mag_y_sq /= Nmeasurment;
	g_mag_y_qa /= Nmeasurment;
	double magYBinderCumulent = 1.0 - g_mag_y_qa / (3.0 * g_mag_y_sq * g_mag_y_sq);
	double YChi = g_mag_y_sq - g_mag_y * g_mag_y;
	YChi *= g_Nspins;
	YChi /= T;


	g_mag_z    /= Nmeasurment;
	g_mag_z_sq /= Nmeasurment;
	g_mag_z_qa /= Nmeasurment;
	double magZBinderCumulent = 1.0 - g_mag_z_qa / (3.0 * g_mag_z_sq * g_mag_z_sq);
	double ZChi = g_mag_z_sq - g_mag_z * g_mag_z;
	ZChi *= g_Nspins;
	ZChi /= T;


	std::cout << std::endl;
	std::cout << "<E>  = " << g_energy << std::endl;
	std::cout << "Cb   = " << Cb << std::endl;
	std::cout << "EBC  = " << energyBinderCumulent << std::endl;
	std::cout << std::endl;
	std::cout << "<m>  = " << g_mag << std::endl;
	std::cout << "Chi  = " << Chi << std::endl;
	std::cout << "<mx> = " << g_mag_x << std::endl;
	std::cout << std::endl;

	// g_length / Nmeasurments is the average length of an added worm in the system.

	//Save the equillibrium value
	std::fstream myfile;
	myfile.open("evolution.txt", std::fstream::out | std::fstream::app);
	myfile << Phi << "\t" << Theta << "\t" << T << "\t\t";
	myfile << g_energy<< "\t" <<   Cb << "\t" <<energyBinderCumulent<< "\t\t";
	myfile << g_mag   << "\t" <<  Chi << "\t" <<  magBinderCumulent << "\t\t";
	myfile << g_mag_x << "\t" << XChi << "\t" << magXBinderCumulent << "\t\t";
	myfile << g_mag_y << "\t" << YChi << "\t" << magYBinderCumulent << "\t\t";
	myfile << g_mag_z << "\t" << ZChi << "\t" << magZBinderCumulent << "\n";
	myfile.close();

	if (DoYouWantNeutronScatteringPlot) { endNSPMeasures(); }


	g_energy    = 0;
	g_energy_sq = 0;
	g_energy_qa = 0;
	
	g_mag    = 0;
	g_mag_sq = 0;
	g_mag_qa = 0;
	
	g_mag_x    = 0;
	g_mag_x_sq = 0;
	g_mag_x_qa = 0;

	g_mag_y    = 0;
	g_mag_y_sq = 0;
	g_mag_y_qa = 0;

	g_mag_z    = 0;
	g_mag_z_sq = 0;
	g_mag_z_qa = 0;
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
