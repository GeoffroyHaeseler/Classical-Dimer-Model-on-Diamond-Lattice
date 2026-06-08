#include <iostream>
#include <iomanip>
#include <time.h>
#include <stdlib.h>

#include "defs.h"
#include "initialise.h"
#include "addAWorm.h"
#include "measure.h"


int main() {
	time_t initial_time = time(NULL);
	time_t time_stamp_1;

	initialise();

	double T=Ti;
	int i, j;
	
	if (DoYouWantNeutronScatteringPlot) {
		if (probaInitialisation(T, Theta, Phi, true)) { //Is there a Kasteleyn transition possible for this temperature ? If yes, probas are set

			time_stamp_1 = time(NULL);

			std::cout << "System is being equilibrate...";
			for (i = 0; i < 500 * Neq; i++) { addAWorm(); }
			std::cout << " It took " << time(NULL) - time_stamp_1 << " seconds to equilibrate the system." << std::endl << std::endl; time_stamp_1 = time(NULL);

			time_stamp_1 = time(NULL);

			std::cout << "System at T=" << T << " K, theta=" << Theta << " rad and phi=" << Phi << " rad is now being measured..." << std::endl;
			latticeMeasure(false); //set system thermodynamical values.
			for (i = 0; i < NSpinConfig; i++) {
				for (j = 0; j < Neq; j++) { addAWorm(); }
				latticeMeasure(true);
			}
			endMeasure(T, NSpinConfig);
		}
	}
		

	else {

		for (T = Ti; T < Tf; T += dT) {
			if (probaInitialisation(T, Theta, Phi, true)) { //Is there a Kasteleyn transition possible for this temperature ? If yes, probas are set

				time_stamp_1 = time(NULL);

				std::cout << "System is being equilibrate...";
				for (i = 0; i < 10 * Neq; i++) { addAWorm(); }
				std::cout << " It took " << time(NULL) - time_stamp_1 << " seconds to equilibrate the system." << std::endl << std::endl; time_stamp_1 = time(NULL);

				time_stamp_1 = time(NULL);

				std::cout << "System at T = " << T << " K, B = " << B << " K, theta = " << Theta << " rad and phi = " << Phi << " rad is now being measured..." << std::endl;
				latticeMeasure(false); //set system thermodynamical values.
				for (i = 0; i < Nmeas; i++) {
					for (j = 0; j < Neq; j++) { addAWorm(); }
					latticeMeasure(false);
				}

				endMeasure(T, Nmeas + 1);
				std::cout << "Measurments took       " << time(NULL) - time_stamp_1 << " seconds to complete" << std::endl;
				std::cout << std::endl;
				std::cout << std::endl;
			}

			else {
				std::cout << std::setprecision(9) << T << std::endl;
				std::cout << "System at T=" << T << " K, theta=" << Theta << " rad and phi=" << Phi << " rad cannot support Kasteleyn transition." << std::endl;
				latticeMeasure(false);
				endMeasure(T, 1);
			}
		}
	}


	
	//viewer();
	std::cout << "The program took " << time(NULL) - initial_time << " seconds to complete" << std::endl;
	std::cout << std::endl;
	std::cout << "________________________________________________________________________" << std::endl;
	std::cout << std::endl;
	return(0);
}
