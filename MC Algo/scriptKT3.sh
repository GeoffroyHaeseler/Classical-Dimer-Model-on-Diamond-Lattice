#!/bin/bash

#OAR -n Test
#OAR -l /core=1,walltime=48:00:00
#OAR --project pr-qmc
#OAR --stdout KT3.out
#OAR --stderr KT3.err
#OAR --notify [RUNNING,END,ERROR]mail:geoffroy.haeseler@lpmmc.cnrs.fr

cd ~/test
make
./KT3
