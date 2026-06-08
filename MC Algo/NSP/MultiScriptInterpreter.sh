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


source=~/KT3/Results

phi=0
thetac=0.95531661812
Theta=( 0 0.25 0.50 0.75 0.90 )
Tc=( 2.42 2.34 2.07 1.59 1.15 )
T=( 1 2 5 )
NSPDirection=( 0 6 )

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
			
			cd ~/KT3
			CurrentFolder=φ=0_θ=${Theta[i]}_T=${T[j]}_$Qx\;$Qy
			echo "	Current NSP Direction is $Qx;$Qy"

			cp $CurrentFolder/NSP.txt $source/$CurrentFolder.txt	
			echo "	File Copied!"

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
                        cd ~/KT3

                        CurrentFolder=φ=60_θ=${Theta[i]}_T=${T[j]}_$Qx\;$Qy 
 			echo "	Current NSP Direction is $Qx;$Qy"
                        
			cp $CurrentFolder/NSP.txt $source/$CurrentFolder.txt	
			echo "	File Copied!"

			cd
                done
        echo
        done
done

