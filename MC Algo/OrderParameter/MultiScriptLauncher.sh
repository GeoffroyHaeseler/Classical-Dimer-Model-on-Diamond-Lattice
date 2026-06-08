#!/bin/bash

source=~/KT3/SourceKT3/*

rm -r ~/KT3/phi*
rm -r ~/KT3/T=*
rm -r ~/KT3/Results

cd ~/KT3
mkdir Results
cd

phi=(0 20 40 60 )
Phi=( 0 0.3490658504 0.6981317008 1.0471975512 )
thetac=( 0.95531661 0.98432087 1.07436696 1.2309594173 ) #Depends on phi

Theta=( 0 0.25 0.50 0.75 0.90 )

Tc00=( 2.4 2.0 2.0 1.5 1.0 0.05 )
Tc20=( 2.4 1.8 1.5 1.0 0.8 0.05 )
Tc40=( 2.4 1.5 1.0 0.7 0.2 0.05 )
Tc60=( 2.4 1.8 1.5 1.0 0.2 0.05 )
Tc=( Tc00 Tc20 Tc40 Tc60 )

for i in {0..3} #Loop over phi
do
	declare -n Temperature="${Tc[i]}" #bash black magic

	echo "___________________________________________________"
	echo
	echo "φ="${phi[i]}
	echo "___________________________________________________"

        for j in {0..4} #Loop over theta
        do


		theta=$(bc -l <<<"${thetac[i]}*${Theta[j]}")

        	InitialTemperature=${Temperature[j]}

                cd ~/KT3
                CurrentFolder=φ=${phi[i]}_θ=${Theta[j]}
                mkdir $CurrentFolder

                CurrentPath=~/KT3/φ=${phi[i]}_θ=${Theta[j]}/
                cd $CurrentPath
                echo "We are in "$CurrentPath
        	echo "	phi="${phi[i]}" and θ="$theta
        	echo "	Starting temperature is :"${InitialTemperature}

                cp $source $CurrentPath
                echo "	Files Copied!"


                #Change phi:
                sed -i '11d' defs.h
                newLine="constexpr double Phi   = ${Phi[i]};"
                sed -i "11i\\$newLine" defs.h

                #Change θ:
                sed -i '10d' defs.h
                newLine="constexpr double Theta = $theta;"
                sed -i "10i\\$newLine" defs.h

                #Change Ti:
                sed -i '14d' defs.h
                newLine="constexpr double Ti = ${InitialTemperature};"
                sed -i "14i\\$newLine" defs.h


                #Change Script:
                sed -i '3d' scriptKT3.sh
                newLine="#OAR -n KT3_Thermo_$CurrentFolder"
                sed -i "3i\\$newLine" scriptKT3.sh
                sed -i '10d' scriptKT3.sh
                newLine="cd $CurrentPath"
                sed -i "10i\\$newLine" scriptKT3.sh

                echo "	Files Modified!"
		echo

                oarsub -S ./scriptKT3.sh
                
		cd
        done
	echo
done

oarstat -u YOURNAME

