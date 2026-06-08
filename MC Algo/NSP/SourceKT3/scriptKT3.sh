#!/bin/bash

#OAR -n Test
#OAR -l /core=1,walltime=48:00:00
#OAR --project YourProjectName
#OAR --stdout KT3.out
#OAR --stderr KT3.err
#OAR --notify [RUNNING,END,ERROR]mail:name.lastname@research.org

cd ~/test
make
./KT3
