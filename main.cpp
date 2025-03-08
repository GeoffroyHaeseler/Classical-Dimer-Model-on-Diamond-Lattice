#include <iostream>
#include <iomanip>
#include <time.h>
#include <stdlib.h>

#include "defs.h"
#include "initialise.h"
#include "addAWorm.h"
#include "viewer.h"
#include "measure.h"


int main() {
	time_t initial_time = time(NULL);
	time_t time_stamp_1;

	initialise();

	double T=Ti;
	int i, j;
	
	for (T = 0.000001; T < 4; T += 0.1) {
		if (probaInitialisation(T, Theta, Phi)) { //Is there a Kasteleyn transition possible for this temperature ? If yes, probas are set
			
			time_stamp_1 = time(NULL);

			std::cout << "System is being equilibrate...";
			for (i = 0; i < Neq; i++) { addAWorm(); }
			std::cout << " It took " << time(NULL) - time_stamp_1 << " seconds to equilibrate the system." << std::endl << std::endl; time_stamp_1 = time(NULL);

			time_stamp_1 = time(NULL);

			std::cout << "System at T=" << T << " K, theta=" << Theta << " rad and phi=" << Phi << " rad is now being measured..." << std::endl;
			latticeMeasure(false); //set system thermodynamical values.
			if (DoYouWantNeutronScatteringPlot) {
				for (i = 0; i < NSpinConfig; i++) {
					for (j = 0; j < Neq; j++) { addAWorm(); }
					latticeMeasure(true);
				}
			}
			else {
				for (i = 0; i < Nmeas; i++) {
					for (j = 0; j < Neq; j++) { addAWorm(); }
					latticeMeasure(false);
				}
			} //do the measures

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



	for (T = 4; T < 20; T += 1) {
		if (probaInitialisation(T, Theta, Phi)) { //Is there a Kasteleyn transition possible for this temperature ? If yes, probas are set

			time_stamp_1 = time(NULL);

			std::cout << "System is being equilibrate...";
			for (i = 0; i < Neq; i++) { addAWorm(); }
			std::cout << " It took " << time(NULL) - time_stamp_1 << " seconds to equilibrate the system." << std::endl << std::endl; time_stamp_1 = time(NULL);

			time_stamp_1 = time(NULL);

			std::cout << "System at T=" << T << " K, theta=" << Theta << " rad and phi=" << Phi << " rad is now being measured..." << std::endl;
			latticeMeasure(false); //set system thermodynamical values.
			if (DoYouWantNeutronScatteringPlot) {
				for (i = 0; i < NSpinConfig; i++) {
					for (j = 0; j < Neq; j++) { addAWorm(); }
					latticeMeasure(true);
				}
			}
			else {
				for (i = 0; i < Nmeas; i++) {
					for (j = 0; j < Neq; j++) { addAWorm(); }
					latticeMeasure(false);
				}
			} //do the measures

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



	for (T = 20; T < 21; T += 10) {
		if (probaInitialisation(T, Theta, Phi)) { //Is there a Kasteleyn transition possible for this temperature ? If yes, probas are set

			time_stamp_1 = time(NULL);

			std::cout << "System is being equilibrate...";
			for (i = 0; i < Neq; i++) { addAWorm(); }
			std::cout << " It took " << time(NULL) - time_stamp_1 << " seconds to equilibrate the system." << std::endl << std::endl; time_stamp_1 = time(NULL);

			time_stamp_1 = time(NULL);

			std::cout << "System at T=" << T << " K, theta=" << Theta << " rad and phi=" << Phi << " rad is now being measured..." << std::endl;
			latticeMeasure(false); //set system thermodynamical values.
			if (DoYouWantNeutronScatteringPlot) {
				for (i = 0; i < NSpinConfig; i++) {
					for (j = 0; j < Neq; j++) { addAWorm(); }
					latticeMeasure(true);
				}
			}
			else {
				for (i = 0; i < Nmeas; i++) {
					for (j = 0; j < Neq; j++) { addAWorm(); }
					latticeMeasure(false);
				}
			} //do the measures

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



	/*for (T = 1; T < 2.42; T += 0.1) {
		if (probaInitialisation(T, Theta, Phi)) { //Is there a Kasteleyn transition possible for this temperature ? If yes, probas are set
			
			time_stamp_1 = time(NULL);

			std::cout << "System is being equilibrate...";
			for (i = 0; i < Neq1; i++) { addAWorm(); }
			std::cout << " It took " << time(NULL) - time_stamp_1 << " seconds to equilibrate the system." << std::endl << std::endl; time_stamp_1 = time(NULL);

			time_stamp_1 = time(NULL);

			std::cout << "System at T=" << T << " K, theta=" << Theta << " rad and phi=" << Phi << " rad is now being measured..." << std::endl;
			latticeMeasure(false); //set system thermodynamical values.
			if (DoYouWantNeutronScatteringPlot) {
				for (i = 0; i < NSpinConfig; i++) {
					for (j = 0; j < Neq2; j++) { addAWorm(); }
					latticeMeasure(true);
				}
			}
			else {
				for (i = 0; i < Nmeas; i++) {
					addAWorm();
					latticeMeasure(false);
				}
			} //do the measures

			endMeasure(T, Nmeas + 1);
			std::cout << "Measurments took       " << time(NULL) - time_stamp_1 << " seconds to complete" << std::endl;
			std::cout << std::endl;
			std::cout << std::endl;
		}

		else {
			std::cout << "System at T=" << T << " K, theta=" << Theta << " rad and phi=" << Phi << " rad cannot support Kasteleyn transition." << std::endl;
			latticeMeasure(false);
			endMeasure(T, 1);
		}
	}
	
	for (T = 2.42; T < 2.52; T += 0.01) {
		if (probaInitialisation(T, Theta, Phi)) { //Is there a Kasteleyn transition possible for this temperature ? If yes, probas are set

			time_stamp_1 = time(NULL);

			std::cout << "System is being equilibrate...";
			for (i = 0; i < Neq1; i++) { addAWorm(); }
			std::cout << " It took " << time(NULL) - time_stamp_1 << " seconds to equilibrate the system." << std::endl << std::endl; time_stamp_1 = time(NULL);

			time_stamp_1 = time(NULL);

			std::cout << "System at T=" << T << " K, theta=" << Theta << " rad and phi=" << Phi << " rad is now being measured..." << std::endl;
			latticeMeasure(false); //set system thermodynamical values.
			if (DoYouWantNeutronScatteringPlot) {
				for (i = 0; i < NSpinConfig; i++) {
					for (j = 0; j < Neq2; j++) { addAWorm(); }
					latticeMeasure(true);
				}
			}
			else {
				for (i = 0; i < Nmeas; i++) {
					addAWorm();
					latticeMeasure(false);
				}
			} //do the measures

			endMeasure(T, Nmeas + 1);
			std::cout << "Measurments took       " << time(NULL) - time_stamp_1 << " seconds to complete" << std::endl;
			std::cout << std::endl;
			std::cout << std::endl;
		}

		else {
			std::cout << "System at T=" << T << " K, theta=" << Theta << " rad and phi=" << Phi << " rad cannot support Kasteleyn transition." << std::endl;
			latticeMeasure(false);
			endMeasure(T, 1);
		}
	}

	for (T = 2.52; T < 2.92; T += 0.05) {
		if (probaInitialisation(T, Theta, Phi)) { //Is there a Kasteleyn transition possible for this temperature ? If yes, probas are set

			time_stamp_1 = time(NULL);

			std::cout << "System is being equilibrate...";
			for (i = 0; i < Neq1; i++) { addAWorm(); }
			std::cout << " It took " << time(NULL) - time_stamp_1 << " seconds to equilibrate the system." << std::endl << std::endl; time_stamp_1 = time(NULL);

			time_stamp_1 = time(NULL);

			std::cout << "System at T=" << T << " K, theta=" << Theta << " rad and phi=" << Phi << " rad is now being measured..." << std::endl;
			latticeMeasure(false); //set system thermodynamical values.
			if (DoYouWantNeutronScatteringPlot) {
				for (i = 0; i < NSpinConfig; i++) {
					for (j = 0; j < Neq2; j++) { addAWorm(); }
					latticeMeasure(true);
				}
			}
			else {
				for (i = 0; i < Nmeas; i++) {
					addAWorm();
					latticeMeasure(false);
				}
			} //do the measures

			endMeasure(T, Nmeas + 1);
			std::cout << "Measurments took       " << time(NULL) - time_stamp_1 << " seconds to complete" << std::endl;
			std::cout << std::endl;
			std::cout << std::endl;
		}

		else {
			std::cout << "System at T=" << T << " K, theta=" << Theta << " rad and phi=" << Phi << " rad cannot support Kasteleyn transition." << std::endl;
			latticeMeasure(false);
			endMeasure(T, 1);
		}
	}
	
	for (T = 2.92; T < 5; T += 0.1) {
		if (probaInitialisation(T, Theta, Phi)) { //Is there a Kasteleyn transition possible for this temperature ? If yes, probas are set

			time_stamp_1 = time(NULL);

			std::cout << "System is being equilibrate...";
			for (i = 0; i < Neq1; i++) { addAWorm(); }
			std::cout << " It took " << time(NULL) - time_stamp_1 << " seconds to equilibrate the system." << std::endl << std::endl; time_stamp_1 = time(NULL);

			time_stamp_1 = time(NULL);

			std::cout << "System at T=" << T << " K, theta=" << Theta << " rad and phi=" << Phi << " rad is now being measured..." << std::endl;
			latticeMeasure(false); //set system thermodynamical values.
			if (DoYouWantNeutronScatteringPlot) {
				for (i = 0; i < NSpinConfig; i++) {
					for (j = 0; j < Neq2; j++) { addAWorm(); }
					latticeMeasure(true);
				}
			}
			else {
				for (i = 0; i < Nmeas; i++) {
					addAWorm();
					latticeMeasure(false);
				}
			} //do the measures

			endMeasure(T, Nmeas + 1);
			std::cout << "Measurments took       " << time(NULL) - time_stamp_1 << " seconds to complete" << std::endl;
			std::cout << std::endl;
			std::cout << std::endl;
		}

		else {
			std::cout << "System at T=" << T << " K, theta=" << Theta << " rad and phi=" << Phi << " rad cannot support Kasteleyn transition." << std::endl;
			latticeMeasure(false);
			endMeasure(T, 1);
		}
	}*/
	
	//viewer();
	std::cout << "The program took " << time(NULL) - initial_time << " seconds to complete" << std::endl;
	std::cout << std::endl;
	std::cout << "________________________________________________________________________" << std::endl;
	std::cout << std::endl;
	return(0);
}
