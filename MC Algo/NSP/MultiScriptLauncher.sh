#!/bin/bash

GetNSPDirection() {
	case $1 in
		0)
			Qx=hh0
			Qy=00l
 			;;
    		1)
      			Qx=h-h0
			Qy=00l
			;;
		2)
			Qx=h-h0
			Qy=kk-2k
			;;
	  	3)
			Qx=h-h0
			Qy=lll
			;;
		4)
			Qx=hh0
			Qy=l-ll
			;;
		5)
			Qx=hh0
			Qy=-kk2k
			;;
		6)
			Qx=k-k-2k
			Qy=l-ll
			;;
	esac
}


source=~/KT3/SourceKT3NSP/*

phi=0
thetac=0.95531661812
Theta=( 0 0.25 0.50 0.75 0.90 )
Tc=( 2.42 2.34 2.07 1.59 1.15 )
T=( 1 2 5 )
NSPDirection=( 0 6 )

rm -r ~/KT3/phi*
rm -r ~/KT3/T=*
rm -r ~/KT3/Results

cd ~/KT3
mkdir Results
cd

echo "___________________________________________________"
echo
echo "phi="$phi
echo "___________________________________________________"

for i in {0..4}
do
	theta=$(bc -l <<<"${thetac}*${Theta[i]}")
        echo "θ="$theta"rad"
	echo

	for j in {0..2}
	do
		temperature=$(bc -l <<<"${Tc[i]}*${T[j]}")
		echo "Current temperature is "${T[j]}":"
		echo
		for nspdirection in "${NSPDirection[@]}"
		do
			
			GetNSPDirection $nspdirection
			echo "	Current NSP Direction is "$Qx";"$Qy
			
			cd ~/KT3
			CurrentFolder=φ=0_θ=${Theta[i]}_T=${T[j]}_$Qx\;$Qy
			mkdir $CurrentFolder
		
			CurrentPath=~/KT3/φ=0_θ=${Theta[i]}_T=${T[j]}_$Qx\;$Qy/
			cd $CurrentPath
			echo "	we are in "$CurrentPath
			
			cp $source $CurrentPath
			echo "	Files Copied!"
		

			#Change phi:
			sed -i '10d' defs.h
			newLine="constexpr double Phi   = $phi;"
			sed -i "10i\\$newLine" defs.h
	
			#Change θ:
		        sed -i '9d' defs.h
		        newLine="constexpr double Theta = $theta;"
        		sed -i "9i\\$newLine" defs.h
		
			#Change T:
			sed -i '13d' defs.h
                	newLine="constexpr double Ti = $temperature;"
                	sed -i "13i\\$newLine" defs.h

			#Change Orientation:
        		sed -i '36d' defs.h
        		newLine="constexpr int NSPdirections = $nspdirection;"
        		sed -i "36i\\$newLine" defs.h
		

			#Change Script:
			sed -i '3d' scriptKT3.sh
                	newLine="#OAR -n KT3_$CurrentFolder"
                	sed -i "3i\\$newLine" scriptKT3.sh	
			sed -i '10d' scriptKT3.sh
			newLine="cd $CurrentPath"
			sed -i "10i\\$newLine" scriptKT3.sh
		
			oarsub -S ./scriptKT3.sh
				
			cd
		echo
		done
	echo	
	done
done



phi=1.0471975512
thetac=1.2309594173
Theta=( 0 0.25 0.50 0.75 0.90 )
Tc=( 2.42 2.28 1.86 1.12 0.5 )
T=( 1 2 5 )
NSPDirection=( 4 5 )

echo "___________________________________________________"
echo
echo "phi="$phi
echo "___________________________________________________"

for i in {0..4}
do
        theta=$(bc -l <<<"${thetac}*${Theta[i]}")
        echo "θ="$theta"rad"
        echo

        for j in {0..2}
        do
                temperature=$(bc -l <<<"${Tc[i]}*${T[j]}")
                echo "Current temperature is "${T[j]}":"
                echo
                for nspdirection in "${NSPDirection[@]}"
                do

                        GetNSPDirection $nspdirection
                        echo "	Current NSP Direction is $Qx;$Qy"

                        cd ~/KT3
                        CurrentFolder=φ=60_θ=${Theta[i]}_T=${T[j]}_$Qx\;$Qy
                        mkdir $CurrentFolder

                        CurrentPath=~/KT3/φ=60_θ=${Theta[i]}_T=${T[j]}_$Qx\;$Qy/
                        cd $CurrentPath
                        echo "	we are in "$CurrentPath

                        cp $source $CurrentPath
                        echo "	Files Copied!"


                        #Change phi:
                        sed -i '10d' defs.h
                        newLine="constexpr double Phi   = $phi;"
                        sed -i "10i\\$newLine" defs.h

                        #Change θ:
                        sed -i '9d' defs.h
                        newLine="constexpr double Theta = $theta;"
                        sed -i "9i\\$newLine" defs.h

                        #Change T:
                        sed -i '13d' defs.h
                        newLine="constexpr double Ti = $temperature;"
                        sed -i "13i\\$newLine" defs.h

                        #Change Orientation:
                        sed -i '36d' defs.h
                        newLine="constexpr int NSPdirections = $nspdirection;"
                        sed -i "36i\\$newLine" defs.h


                        #Change Script:
                        sed -i '3d' scriptKT3.sh
                        newLine="#OAR -n KT3_NSP_$CurrentFolder"
                        sed -i "3i\\$newLine" scriptKT3.sh
                        sed -i '10d' scriptKT3.sh
                        newLine="cd $CurrentPath"
                        sed -i "10i\\$newLine" scriptKT3.sh

                        oarsub -S ./scriptKT3.sh

                        cd
                done
        echo
        done
done

oarstat -u YOURNAME

