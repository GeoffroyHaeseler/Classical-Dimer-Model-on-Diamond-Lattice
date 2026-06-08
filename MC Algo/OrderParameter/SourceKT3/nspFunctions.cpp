#include <iostream>
#include <stdexcept>
#include <fstream>
#include <stdlib.h>     /* srand, rand */
#include <cmath>
#include <math.h>
#include <complex.h>
#include <string>
#include <time.h>

#include "nspFunctions.h"
#include "defs.h"

extern int g_lattice[L][L][L][4];
extern int g_Nspins;

extern double g_spinUsefull[2 * xdiv][2 * xdiv][4][3];
extern double g_SpinPosition[L][L][L][4][4][3];
extern double g_Q[2 * xdiv][2 * xdiv][3];
extern double g_X[2 * xdiv][2 * xdiv];
extern double g_Y[2 * xdiv][2 * xdiv];
extern double g_QHat[2 * xdiv][2 * xdiv][3];
extern double g_UnpolarisedNSP[2 * xdiv][2 * xdiv];
extern double g_DipolarFragment[2 * xdiv][2 * xdiv];
extern double g_AllInAllOutOrderFragment[2 * xdiv][2 * xdiv];
extern double g_BraggsPeak[2 * xdiv][2 * xdiv];

extern double pi2;
extern double g_qlim;
extern int g_nspCount;

using namespace std::complex_literals;


/// <summary>
/// Initialise g_Q and g_QHat
/// </summary>
void nspInitialisation() {
	g_nspCount = 0;

	//print the NSP x and y axis
	switch (NSPdirections) {
	case 0://(h, h, 0)  (0, 0, l)
		std::cout << "NSP axis are in the (h,  h, 0)  (0, 0, l) direction\n";
		break;
	case 1://(h, -h, 0)  (0, 0, l)
		std::cout << "NSP axis are in the (h, -h, 0)  (0, 0, l) direction\n";
		break;
	case 2://(h, -h, 0)  (k, k, -2k)
		std::cout << "NSP axis are in the (h, -h, 0)  (k, k, -2k) direction\n";
		break;
	case 3://(h, -h, 0)  (l, l, l)
		std::cout << "NSP axis are in the (h, -h, 0)  (l, l, l) direction\n";
		break;
	case 4://(h,  h, 0)  (l, -l, l)
		std::cout << "NSP axis are in the (h,  h, 0)  (l, -l, l) direction\n";
		break;
	case 5://(h, h, 0)  (-k, k, 2k)
		std::cout << "NSP axis are in the (h, h, 0)  (-k, k, 2k) direction\n";
		break;
	case 6://(k,-k,-2k)  ( l,-l,  l)
		std::cout << "NSP axis are in the (k, -k, -2k)  ( l, -l, l) direction\n";
		break;
	default:
		throw std::invalid_argument("NSPDirections out of range");
	}

	//Initialise the Reciprocal Lattice
	int q0, q1;
	double Q0, Q1;
	double normsq;

	for (q0 = 0; q0 < 2 * xdiv; q0++) {//We go through the whole reciprocal lattice
		for (q1 = 0; q1 < 2 * xdiv; q1++) {
			
			//Q0 and Q1 describe a pixel position on final NSP figure
			Q0 = xlim * (double(q0) - xdiv) / (double(xdiv)); //-xmult to xmult (-4;4) in 2*xdiv steps
			Q1 = ylim * (double(q1) - ydiv) / (double(ydiv)); //-ymult to ymult (-4;4) in 2*ydiv steps
			//Compute the different interesting wave vectors.
			switch (NSPdirections) {
			case 0://(h, h, 0)  (0, 0, l)
				Q0 = Q0 / sqrt(2);
				Q1 = Q1 / sqrt(1);
				g_Q[q0][q1][0] = 1.0*pi2*Q0 +0.0*pi2*Q1;
				g_Q[q0][q1][1] = 1.0*pi2*Q0 +0.0*pi2*Q1;
				g_Q[q0][q1][2] = 0.0*pi2*Q0 +1.0*pi2*Q1;
				break;

			case 1://(h, -h, 0)  (0, 0, l)
				Q0 = Q0 / sqrt(2);
				Q1 = Q1 / sqrt(1);
				g_Q[q0][q1][0] = +1.0*pi2*Q0 +0.0*pi2*Q1;
				g_Q[q0][q1][1] = -1.0*pi2*Q0 +0.0*pi2*Q1;
				g_Q[q0][q1][2] = +0.0*pi2*Q0 +1.0*pi2*Q1;
				break;

			case 2://(h, -h, 0)  (k, k, -2k)
				Q0 = Q0 / sqrt(2);
				Q1 = Q1 / sqrt(6);
				g_Q[q0][q1][0] = +1.0*pi2*Q0 +1.0*pi2*Q1;
				g_Q[q0][q1][1] = -1.0*pi2*Q0 +1.0*pi2*Q1;
				g_Q[q0][q1][2] = +0.0*pi2*Q0 -2.0*pi2*Q1;
				break;

			case 3://(h, -h, 0)  (l, l, l)
				Q0 = Q0 / sqrt(2);
				Q1 = Q1 / sqrt(3);
				g_Q[q0][q1][0] = +1.0*pi2*Q0 + 1.0*pi2*Q1;
				g_Q[q0][q1][1] = -1.0*pi2*Q0 + 1.0*pi2*Q1;
				g_Q[q0][q1][2] = +0.0*pi2*Q0 + 1.0*pi2*Q1;
				break;

			case 4://(h,  h, 0)  (l, -l, l)
				Q0 = Q0 / sqrt(2);
				Q1 = Q1 / sqrt(3);
				g_Q[q0][q1][0] = +1.0 * pi2 * Q0 + 1.0 * pi2 * Q1;
				g_Q[q0][q1][1] = +1.0 * pi2 * Q0 - 1.0 * pi2 * Q1;
				g_Q[q0][q1][2] = +0.0 * pi2 * Q0 + 1.0 * pi2 * Q1;
				break;

			case 5://(h, h, 0)  (-k, k, 2k)
				Q0 = Q0 / sqrt(2);
				Q1 = Q1 / sqrt(6);
				g_Q[q0][q1][0] = +1.0 * pi2 * Q0 - 1.0 * pi2 * Q1;
				g_Q[q0][q1][1] = +1.0 * pi2 * Q0 + 1.0 * pi2 * Q1;
				g_Q[q0][q1][2] = +0.0 * pi2 * Q0 + 2.0 * pi2 * Q1;
				break;

			case 6://(k,-k,-2k)  ( l,-l,  l)
				Q0 = Q0 / sqrt(6);
				Q1 = Q1 / sqrt(3);
				g_Q[q0][q1][0] = +1.0 * pi2 * Q0 + 1.0 * pi2 * Q1;
				g_Q[q0][q1][1] = -1.0 * pi2 * Q0 - 1.0 * pi2 * Q1;
				g_Q[q0][q1][2] = -2.0 * pi2 * Q0 + 1.0 * pi2 * Q1;
				break;
			}


			//Qhat
			normsq = norm(g_Q[q0][q1]);
			if (normsq < 0.00001) {	
				g_QHat[q0][q1][0] = 0;
				g_QHat[q0][q1][1] = 0;
				g_QHat[q0][q1][2] = 0;
			}
			else {
				g_QHat[q0][q1][0] = g_Q[q0][q1][0] / (sqrt(normsq));
				g_QHat[q0][q1][1] = g_Q[q0][q1][1] / (sqrt(normsq));
				g_QHat[q0][q1][2] = g_Q[q0][q1][2] / (sqrt(normsq));
			}


			g_UnpolarisedNSP[q0][q1] = 0;
			g_DipolarFragment[q0][q1] = 0;
			g_AllInAllOutOrderFragment[q0][q1] = 0;
			g_BraggsPeak[q0][q1] = 0;

			//Compute the usefull spin component
			int ispin;
			double ScalarProduct;
			double spinParallele[3] = { 0, 0, 0 };
			double spinProjectedOnQ[3] = { 0, 0, 0 };
			double n[3] = { 0, 0, 0 };
			// Compute the normal vector to the NSP plan
			switch (NSPdirections) {
			case 0://(h, h, 0)  (0, 0, l)
				n[0] =-1 / sqrt(2);
				n[1] = 1 / sqrt(2);
				n[2] = 0;
				break;
			case 1://(h, -h, 0)  (0, 0, l)
				n[0] = 1 / sqrt(2);
				n[1] = 1 / sqrt(2);
				n[2] = 0;
				break;

			case 2://(h, -h, 0)  (k, k, -2k)
				n[0] = 1 / sqrt(3);
				n[1] = 1 / sqrt(3);
				n[2] = 1 / sqrt(3);
				break;

			case 3://(h, -h, 0)  (l, l, l)
				n[0] = 1 / sqrt(6);
				n[1] = 1 / sqrt(6);
				n[2] =-2 / sqrt(6);
				break;

			case 4://(h,  h, 0)  (l, -l, l)
				n[0] =-1 / sqrt(6);
				n[1] = 1 / sqrt(6);
				n[2] = 2 / sqrt(6);
				break;

			case 5://(h, h, 0)  (-k, k, 2k)
				n[0] = 1 / sqrt(3);
				n[1] = -1 / sqrt(3);
				n[2] = 1 / sqrt(3);
				break;

			case 55://(k,-k,-2k)  ( l,-l,  l)
				n[0] = 1 / sqrt(2);
				n[1] = 1 / sqrt(2);
				n[2] = 0;
				break;
			}

			double _r3 = 0.57735026919; // 1/sqrt(3)
			double S_NSP[4][3] = { { -_r3 , -_r3 , -_r3 }, { _r3 , _r3 , -_r3  }, { -_r3 , _r3 , _r3  }, { _r3 , -_r3 , _r3  } };
			for (ispin = 0; ispin < 4; ispin++) {
				//keep the component of the spin in the scattering plane(new spin is spinParallele)
				ScalarProduct = dotProduct(n, S_NSP[ispin]);
				spinParallele[0] = S_NSP[ispin][0] - ScalarProduct * n[0];
				spinParallele[1] = S_NSP[ispin][1] - ScalarProduct * n[1];
				spinParallele[2] = S_NSP[ispin][2] - ScalarProduct * n[2];

				//keep the component of spinParallele perpendicular to Q
				ScalarProduct = dotProduct(g_QHat[q0][q1], spinParallele);
				g_spinUsefull[q0][q1][ispin][0] = spinParallele[0] - ScalarProduct * g_QHat[q0][q1][0];
				g_spinUsefull[q0][q1][ispin][1] = spinParallele[1] - ScalarProduct * g_QHat[q0][q1][1];
				g_spinUsefull[q0][q1][ispin][2] = spinParallele[2] - ScalarProduct * g_QHat[q0][q1][2];
			}
		}
	}



	//Initialise the Real Lattice
	int i0, i1, i2;
	int itri, ispin;
	for (i0 = 0; i0 < L; i0++) {//We go through the whole real lattice
		for (i1 = 0; i1 < L; i1++) {
			for (i2 = 0; i2 < L; i2++) {
				for (itri = 0; itri < 4; itri++) {
					for (ispin = 0; ispin < 4; ispin++) {

						g_SpinPosition[i0][i1][i2][itri][ispin][0] = i0;
						g_SpinPosition[i0][i1][i2][itri][ispin][1] = i1;
						g_SpinPosition[i0][i1][i2][itri][ispin][2] = i2;

						if (itri == 1) {
							g_SpinPosition[i0][i1][i2][itri][ispin][0] += 0.5;
							g_SpinPosition[i0][i1][i2][itri][ispin][1] += 0.5;
							g_SpinPosition[i0][i1][i2][itri][ispin][2] += 0.0;
						}
						if (itri == 2) {
							g_SpinPosition[i0][i1][i2][itri][ispin][0] += 0.0;
							g_SpinPosition[i0][i1][i2][itri][ispin][1] += 0.5;
							g_SpinPosition[i0][i1][i2][itri][ispin][2] += 0.5;
						}
						if (itri == 3) {
							g_SpinPosition[i0][i1][i2][itri][ispin][0] += 0.5;
							g_SpinPosition[i0][i1][i2][itri][ispin][1] += 0.0;
							g_SpinPosition[i0][i1][i2][itri][ispin][2] += 0.5;
						}

						if (ispin == 1) {
							g_SpinPosition[i0][i1][i2][itri][ispin][0] -= 0.25;
							g_SpinPosition[i0][i1][i2][itri][ispin][1] -= 0.25;
							g_SpinPosition[i0][i1][i2][itri][ispin][2] -= 0.00;
						}
						if (ispin == 2) {
							g_SpinPosition[i0][i1][i2][itri][ispin][0] -= 0.00;
							g_SpinPosition[i0][i1][i2][itri][ispin][1] -= 0.25;
							g_SpinPosition[i0][i1][i2][itri][ispin][2] -= 0.25;
						}
						if (ispin == 3) {
							g_SpinPosition[i0][i1][i2][itri][ispin][0] -= 0.25;
							g_SpinPosition[i0][i1][i2][itri][ispin][1] -= 0.00;
							g_SpinPosition[i0][i1][i2][itri][ispin][2] -= 0.25;
						}


					}
				}
			}
		}
	}

	g_qlim = 4 * pi2;

}

/// <summary>
/// Update the g_correlation and the g_avSpins arrays.
/// </summary>
void updateNSP() {
	g_nspCount++;
	std::cout << "Enter update nsp function n " << g_nspCount << ".";
	time_t time_stamp_1 = time(NULL);

	int q0, q1, i0, i1, i2;
	int itri, ispin;
	double normsq, sign;

	const std::complex<double> i(0, 1);
	std::complex<double> phase = 0;
	std::complex<double> braggspeak = 0;
	std::complex<double> unpolarised[3] = { 0, 0, 0 };
	std::complex<double> DipolarFragment[3] = { 0, 0, 0 };
	std::complex<double> AllInAllOutOrderFragment[3] = { 0, 0, 0 };
	for (q0 = 0; q0 < 2 * xdiv; q0++) {//loop over the reciprocal lattice
		for (q1 = 0; q1 < 2 * xdiv; q1++) {
			
			normsq = norm(g_Q[q0][q1]);

			if (sqrt(normsq) < g_qlim) {

				for (i0 = 0; i0 < L; i0++) {//loop over the real lattice
					for (i1 = 0; i1 < L; i1++) {
						for (i2 = 0; i2 < L; i2++) {
							for (itri = 0; itri < 4; itri++) {
								for (ispin = 0; ispin < 4; ispin++) {

									if (g_lattice[i0][i1][i2][itri] == ispin) { sign = -1; }
									else { sign = +1; }


									phase = std::exp(i * dotProduct(g_Q[q0][q1], g_SpinPosition[i0][i1][i2][itri][ispin]));

									braggspeak += phase;

									//the whole neutron spin is taken into account (unpolarised neutrons)
										//The whole pyrochlore spin is considered
									unpolarised[0] += sign * g_spinUsefull[q0][q1][ispin][0] * phase;
									unpolarised[1] += sign * g_spinUsefull[q0][q1][ispin][1] * phase;
									unpolarised[2] += sign * g_spinUsefull[q0][q1][ispin][2] * phase;

										//The neutron interact with only the dipolar fragment of the pyrochore spin.
									DipolarFragment[0] += (sign - 1.0 / 2.0) * g_spinUsefull[q0][q1][ispin][0] * phase;
									DipolarFragment[1] += (sign - 1.0 / 2.0) * g_spinUsefull[q0][q1][ispin][1] * phase;
									DipolarFragment[2] += (sign - 1.0 / 2.0) * g_spinUsefull[q0][q1][ispin][2] * phase;

										//The neutron interact with only the all in all out fragment of the pyrochore spin (Bragg's peak at (2;2;0).
									AllInAllOutOrderFragment[0] += (1.0 / 2.0) * g_spinUsefull[q0][q1][ispin][0] * phase;
									AllInAllOutOrderFragment[1] += (1.0 / 2.0) * g_spinUsefull[q0][q1][ispin][1] * phase;
									AllInAllOutOrderFragment[2] += (1.0 / 2.0) * g_spinUsefull[q0][q1][ispin][2] * phase;

								}
							}
						}
					}
				}//end of the loop on the real lattice
			}

			g_BraggsPeak[q0][q1] = std::abs(std::conj(braggspeak) * braggspeak);
			braggspeak = 0;

			//The whole spin is considered (Unpolarised Neutron Scattering)
			g_UnpolarisedNSP[q0][q1] += std::abs(norm(unpolarised));
			g_DipolarFragment[q0][q1] += std::abs(norm(DipolarFragment));
			g_AllInAllOutOrderFragment[q0][q1] += std::abs(norm(AllInAllOutOrderFragment));


			DipolarFragment[0] = 0;
			DipolarFragment[1] = 0;
			DipolarFragment[2] = 0;

			AllInAllOutOrderFragment[0] = 0;
			AllInAllOutOrderFragment[1] = 0;
			AllInAllOutOrderFragment[2] = 0;

			unpolarised[0] = 0;
			unpolarised[1] = 0;
			unpolarised[2] = 0;
		}
	}
	std::cout << " It tooks " << time(NULL) - time_stamp_1 << " seconds to finish the NSP update" << std::endl;
}

/// <summary>
/// Edit the NSP.txt file which contains the data requiered to plot the figure with the plot_AHC matlab's function.
/// </summary>
void endNSPMeasures() {

	std::cout << g_nspCount << " configurations have been used to calculated the NSP." << std::endl << std::endl;

	std::remove("NSP.txt");

	std::fstream myfile;
	myfile.open("NSP.txt", std::fstream::out | std::fstream::app);
	myfile << NSPdirections << std::endl; //tell plotNSP which 

	int q0, q1;
	double X, Y;
	double normsq;
	//go through the whole reciprocal lattice to print the result in the NSP.txt file
	for (q0 = 0; q0 < 2 * xdiv; q0++) {
		for (q1 = 0; q1 < 2 * xdiv; q1++) {

			//Compute each NSP pixel (X,Y) using corresponding wave vector(q_Q)
			switch (NSPdirections) {
			case 0://(h, h, 0)  (0, 0, l)
				X = g_Q[q0][q1][0] / pi2;
				Y = g_Q[q0][q1][2] / pi2;
				break;
			case 1://(h, -h, 0)  (0, 0, l)
				X = g_Q[q0][q1][0] / pi2;
				Y = g_Q[q0][q1][2] / pi2;
				break;
			case 2://(h, -h, 0)  (k, k, -2k)
				X =+0.5 * (g_Q[q0][q1][0] - g_Q[q0][q1][1]) / pi2;
				Y =-0.5 * g_Q[q0][q1][2] / pi2;
				break;
			case 3://(h, -h, 0)  (l, l, l)
				X =+0.5 * (g_Q[q0][q1][0] - g_Q[q0][q1][1]) / pi2;
				Y = g_Q[q0][q1][2] / pi2;
				break;
			case 4://(h, h, 0)  (l, -l, l)
				X =+0.5 * (g_Q[q0][q1][0] + g_Q[q0][q1][1]) / pi2;
				Y = g_Q[q0][q1][2] / pi2;
				break;
			case 5://(h, h, 0)  (-k, k, 2k)
				X =+0.5 * (g_Q[q0][q1][0] + g_Q[q0][q1][1]) / pi2;
				Y =+0.5 * g_Q[q0][q1][2] / pi2;
				break;
			case 6://(k,-k,-2k)  ( l,-l,  l)
				X = (g_Q[q0][q1][0] - g_Q[q0][q1][2]) / (3.0 * pi2);
				Y = (2.0 * g_Q[q0][q1][0] + g_Q[q0][q1][2]) / (3.0 * pi2);
				break;
			}

			normsq = norm(g_Q[q0][q1]);

			if (sqrt(normsq) < g_qlim) {
				g_UnpolarisedNSP[q0][q1] /= double(g_Nspins) * g_nspCount;
				g_DipolarFragment[q0][q1] /= double(g_Nspins) * g_nspCount;
				g_AllInAllOutOrderFragment[q0][q1] /= double(g_Nspins) * g_nspCount;
				g_BraggsPeak[q0][q1] /= double(g_Nspins) * g_nspCount;
				myfile << X << " " << Y << " " << g_UnpolarisedNSP[q0][q1] << " " << g_DipolarFragment[q0][q1] << " " << g_AllInAllOutOrderFragment[q0][q1] << " " << g_BraggsPeak[q0][q1] << std::endl;

				g_UnpolarisedNSP[q0][q1] = 0;
				g_BraggsPeak[q0][q1] = 0;
			}

			else {
				myfile << X << " " << Y << " " << 0 << " " << 0 << " " << 0 << " " << 0 << std::endl;

				g_UnpolarisedNSP[q0][q1] = 0;
				g_BraggsPeak[q0][q1] = 0;
			}

		}
	}

	myfile.close();
	g_nspCount = 0;
}



/// <summary>
/// Return the dot product of two vectors of length 3 made of doubles and const doubles.
/// </summary>
/// <param name="A"></param>
/// <param name="B"></param>
/// <returns></returns>
double dotProduct(double A[3], const double B[3]) {
	return(A[0] * B[0] + A[1] * B[1] + A[2] * B[2]);
}

/// <summary>
/// Return the dot product of two vectors of length 3 made of doubles.
/// </summary>
/// <param name="A"></param>
/// <param name="B"></param>
/// <returns></returns>
double dotProduct(double A[3], double B[3]) {
	return(A[0] * B[0] + A[1] * B[1] + A[2] * B[2]);
}

/// <summary>
/// Return the dot product of two vectors of length 3 made of complexes.
/// </summary>
/// <param name="A"></param>
/// <param name="B"></param>
/// <returns></returns>
std::complex<double> dotProduct(std::complex<double> A[3], std::complex<double> B[3]) {
	return(std::conj(A[0]) * B[0] + std::conj(A[1]) * B[1] + std::conj(A[2]) * B[2]);
}

/// <summary>
/// Return A' . A
/// </summary>
/// <param name="A"></param>
/// <param name="B"></param>
/// <returns></returns>
double norm(double A[3]) {
	return(A[0] * A[0] + A[1] * A[1] + A[2] * A[2]);
}

/// <summary>
/// Return A' . A
/// </summary>
/// <param name="A"></param>
/// <param name="B"></param>
/// <returns></returns>
std::complex<double> norm(std::complex<double> A[3]) {
	return(std::conj(A[0]) * A[0] + std::conj(A[1]) * A[1] + std::conj(A[2]) * A[2]);
}