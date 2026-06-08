This set of files implement algorithms used to studied the Crystal of charge manifolds of pyrochlore, in which each 'up' tetrahedron has three spins pointing inward and one outward while all 'down' tetrahedra have three spins out and one in





## Monte Carlo Algorithm



The "MC Algo" folder contains the C++ code implementing a Metropolis-Hasting approach (in main.cpp and initialise.\*) completed with a loop algorithm (in next.\*, addAWorm.\* and growTheWorm.\*) to make it efficient and chargeless.



This code produces order parameters (like magnetisation) depending on temperature (implemented in measure.\*). The resulting file, evolution.txt, can be read using the python script called "Plot.py".



It also produces elastic neutron scattering figures (called "NSP" in the code, for Neutron Scattering Plots) at a given temperature and field direction (implemented in nspFunctions.\*). The resulting file, NSP.txt can be read using the python script called "PlotNSP.py".



The code settings are contained in the defs.h file. It is primordial in order to modify the parameters of a run. Especially, it contains the Boolean selecting whether the code will compute NSP or order parameters.



There is a Makefile to compile the code as well as two bash scripts, scriptKT3.sh and scriptKT3\_SLURM.sh, used to launch the code on a cluster ran respectively using [OAR](https://oar.imag.fr/docs/2.5/#ref-user-docs) and [SLURM](https://slurm.schedmd.com/documentation.html).



The two subfolders contain scripts to launch multiple code instances on different cluster nodes.





### NSP



Contain a folder "SourceKT3" which includes the code which will be multiply on different nodes

Contain a folder "Results" which store the results when the computations are done and the Python scripts to read them.

MultiScriptLauncher.sh creates different folders with modified code according to given parameters. Each folder will then be launched independently on different nodes

MultiScriptInterpreter.sh gather the different NSP.txt produced by MultiScriptLauncher.sh. These two files must be sync manually in order to create and look at the same folders.

You can modify the parameter at your will by modifying accordingly phi, thetac, Theta, Tc, T in MultiScriptLauncher.sh and in MultiScriptInterpreter.sh and then the Python scripts



Before using this folder:

&#x09;Verify the cluster you are using is scheduled by OAR. If not modify SourceKT3/scriptKT3.sh and MultiScriptLauncher.sh. If yes, modify MultiScriptLauncher.sh with your own mail address and project. 

&#x09;Verify your bash environment accept Greek letters. If not, check [that](https://www.linuxquestions.org/questions/linux-newbie-8/typing-or-pasting-greek-characters-in-a-bash-script-4175669577/?__cf_chl_tk=xXiz2_6xIyLIr6zlyFVZ2DlXCeYUq3TwnyR.LhlGZrI-1780854566-1.0.1.1-b0f4jS8zzcDukw0Z35Ne0Oez3QNuE9OPRPaM9NjQIIE).

&#x09;Verify that your file matches the current one (which now is \~/KT3/SourceKT3...). If not, modify your file tree or modify the path in the python scripts located in Results, as well as MultiScriptInterpreter.sh, MultiScriptLauncher.sh

&#x09;Add to bash scripts the right to be executed: "chmod +x NameOfScript.sh"





### OrderParameter



Contain a folder "SourceKT3" which includes the code which will be multiply on different nodes

Contain a folder "Results" which store the results when the computations are done and the Python scripts to read them.

MultiScriptLauncher.sh creates different folders with modified code according to given parameters. Each folder will then be launched independently on different nodes

MultiScriptInterpreter.sh gather the different NSP.txt produced by MultiScriptLauncher.sh. These two files must be sync manually in order to create and look at the same folders.

You can modify the parameter at your will by modifying accordingly phi, Phi, thetac, Theta and Tc in MultiScriptLauncher.sh and in MultiScriptInterpreter.sh and then the Python scripts



Before using this folder:

&#x09;Verify the cluster you are using is scheduled by OAR. If not modify SourceKT3/scriptKT3.sh and MultiScriptLauncher.sh. If yes, modify MultiScriptLauncher.sh with your own mail address and project.

&#x09;Verify your bash environment accept Greek letters. If not, check [that](https://www.linuxquestions.org/questions/linux-newbie-8/typing-or-pasting-greek-characters-in-a-bash-script-4175669577/?__cf_chl_tk=xXiz2_6xIyLIr6zlyFVZ2DlXCeYUq3TwnyR.LhlGZrI-1780854566-1.0.1.1-b0f4jS8zzcDukw0Z35Ne0Oez3QNuE9OPRPaM9NjQIIE).

&#x09;Verify that your file matches the current one (which now is \~/KT3/SourceKT3...). If not, modify your file tree or modify the path in the python scripts located in Results, as well as MultiScriptInterpreter.sh, MultiScriptLauncher.sh

&#x09;Add to bash scripts the right to be executed: "chmod +x NameOfScript.sh"





## Husimi Tree



The "Husimi Tree" folder contains the python codes implementing a Husimi tree approach for the studied problem. To use it, run HusimiTreeFunctions.py. Then, after changing the path in Try1.py (path which should lead to HusimiTreeFunctions.py), you can execute Try1.py to obtain the Energy.



The list of functions and what they do is given in HusimiCactusFunctions.py. The most useful functions take the form: "Return\*(theta, phi, X)". Here, \* refers to the order parameter you want. theta and phi are two floats which give the field direction (in rad) while X is a numpy ndarray which contains the temperature at which you want the order parameter.



Pay Attention: the algorithm is unstable near T=0. You cannot simply take T=0 as initial temperature.



The folder Probing Critical Line show how to use these functions.





### Probing Critical Line



After executed HusimiCuctusFunctions.py, you can simply execute the desired script.



