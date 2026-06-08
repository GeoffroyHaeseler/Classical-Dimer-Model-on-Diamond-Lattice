#!/bin/bash

source=~/KT3/Results

cd ~/KT3
mkdir Results
cd

phi=(0 20 40 60 )
Theta=( 0 0.25 0.50 0.75 0.90 )


for i in {0..3} #Loop over phi
do
	echo "___________________________________________________"
	echo
	echo "φ="${phi[i]}
	echo "___________________________________________________"

        for j in {0..4} #Loop over theta
        do

                cd ~/KT3
                CurrentPath=~/KT3/φ=${phi[i]}_θ=${Theta[j]}
                cd $CurrentPath

                echo "we are in "$CurrentPath
                cp ${CurrentPath}/evolution.txt ${source}/${CurrentPath}
                echo "	File copied!"
		echo
		cd

        done
	echo
done

