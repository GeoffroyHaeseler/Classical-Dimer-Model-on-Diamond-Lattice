import numpy as np
import math


#Defines important global variable used across the module
A=1/3
B=1/3
C=1/3
D=1/3

S0x=0
S0y=0
S0z=-1

S1x=-2*math.sqrt(2)/3
S1y=0
S1z=1/3

S2x=math.sqrt(2)/3
S2y=math.sqrt(6)/3
S2z=1/3

S3x=math.sqrt(2)/3
S3y=-math.sqrt(6)/3
S3z=1/3

j=0




def ComputeEnergyAndMagField(theta, phi, T):
    #Compute the Boltzmann weight associated with an up tetrahedron i pointing
    #toward, 0, 1, 2 or 3 at θ=theta, φ=phi and β=1/T
    hx=math.cos(phi)*math.sin(theta)
    hy=math.sin(phi)*math.sin(theta)
    hz=math.cos(theta) #Magnetic Field

    global E0
    global eE0
    global E1
    global eE1
    global E2
    global eE2
    global E3
    global eE3
    E0=hx*(-S0x+S1x+S2x+S3x)+hy*(-S0y+S1y+S2y+S3y)+hz*(-S0z+S1z+S2z+S3z)
    E1=hx*( S0x-S1x+S2x+S3x)+hy*( S0y-S1y+S2y+S3y)+hz*( S0z-S1z+S2z+S3z)
    E2=hx*( S0x+S1x-S2x+S3x)+hy*( S0y+S1y-S2y+S3y)+hz*( S0z+S1z-S2z+S3z)
    E3=hx*( S0x+S1x+S2x-S3x)+hy*( S0y+S1y+S2y-S3y)+hz*( S0z+S1z+S2z-S3z)
    E0=-E0
    E1=-E1
    E2=-E2
    E3=-E3 #Zeeman energy

    eE0=math.exp(-E0/T)
    eE1=math.exp(-E1/T)
    eE2=math.exp(-E2/T)
    eE3=math.exp(-E3/T) #Boltzmann weight


def UpdateSequence():
    #Iterate the sequence An, Bn, Cn and Dn
    global A
    global B
    global C
    global D
    a=A
    b=B
    c=C
    d=D
    A = eE0/(eE1/(a+c+d) + eE2/(a+b+d) + eE3/(a+b+c))
    B = eE1/(eE0/(b+c+d) + eE2/(a+b+d) + eE3/(a+b+c))
    C = eE2/(eE0/(b+c+d) + eE1/(a+c+d) + eE3/(a+b+c))
    D = eE3/(eE0/(b+c+d) + eE1/(a+c+d) + eE2/(a+b+d))


def ComputeEnergy():
    #Compute the energy using the limite of the sequences A, B, C and D
    alpha=eE0/(B+C+D)
    beta =eE1/(A+C+D)
    gamma=eE2/(A+B+D)
    delta=eE3/(A+B+C)

    energy=(E0*alpha+E1*beta+E2*gamma+E3*delta)/(alpha+beta+gamma+delta)
    return(energy/4)


def ComputeMx():
    #Compute Mx using the limite of the sequences A, B, C and D
    alpha=eE0/(B+C+D)
    beta =eE1/(A+C+D)
    gamma=eE2/(A+B+D)
    delta=eE3/(A+B+C)

    Mx=-2*(S0x*alpha+S1x*beta+S2x*gamma+S3x*delta)/(alpha+beta+gamma+delta)
    return(Mx/4)


def ComputeMy():
    #Compute Mz using the limite of the sequences A, B, C and D
    alpha=eE0/(B+C+D)
    beta =eE1/(A+C+D)
    gamma=eE2/(A+B+D)
    delta=eE3/(A+B+C)

    My=-2*(S0y*alpha+S1y*beta+S2y*gamma+S3y*delta)/(alpha+beta+gamma+delta)
    return(My/4)


def ComputeMz():
    #Compute Mz using the limite of the sequences A, B, C and D
    alpha=eE0/(B+C+D)
    beta =eE1/(A+C+D)
    gamma=eE2/(A+B+D)
    delta=eE3/(A+B+C)

    Mz=-2*(S0z*alpha+S1z*beta+S2z*gamma+S3z*delta)/(alpha+beta+gamma+delta)
    return(Mz/4)


def ComputeSpecificHeat(X, Energy):
    #Compute Specific Heat by numerically derivate the average energy
    NUM=len(X)
    SpecificHeat=np.empty(NUM)
    SpecificHeat[0]=0
    for i in range(1, len(X)-1):
        SpecificHeat[i]=(Energy[i+1]-Energy[i])/(X[i+1]-X[i])
    SpecificHeat[-1]=SpecificHeat[-2]
    return(SpecificHeat)


def ComputeEntropy(X, SpecificHeat):
    #Compute Entropy by numerically integrate the specific heat
    NUM=len(X)
    Entropy=np.empty(NUM)
    Entropy[0]=0
    for i in range(1, len(X)):
        Entropy[i] = Entropy[i-1] + (X[i]-X[i-1])*SpecificHeat[i-1]/X[i-1]
    return(Entropy)

def ReturnEnergy(theta, phi, X):
    #Call this function to obtain the Energy
    global A
    global B
    global C
    global D
    NUM=len(X)
    Energy=np.empty(NUM)

    j=0
    for T in X:
        ComputeEnergyAndMagField(theta, phi, T)
        A=1/3
        B=1/3
        C=1/3
        D=1/3
        for k in range (0,500,1):
            UpdateSequence()
        X[j]=T
        Energy[j]=ComputeEnergy()

        j=j+1

    return(Energy)


def ReturnMx(theta, phi, X):
    #Call this function to obtain Mx
    global A
    global B
    global C
    global D
    NUM=len(X)
    MagnetisationX=np.empty(NUM)

    j=0
    for T in X:
        ComputeEnergyAndMagField(theta, phi, T)
        A=1/3
        B=1/3
        C=1/3
        D=1/3
        for k in range (0,100,1):
            UpdateSequence()
        X[j]=T
        MagnetisationX[j]=ComputeMx()

        j=j+1

    return(MagnetisationX)


def ReturnMy(theta, phi, X):
    #Call this function to obtain My
    global A
    global B
    global C
    global D
    NUM=len(X)
    MagnetisationY=np.empty(NUM)

    j=0
    for T in X:
        ComputeEnergyAndMagField(theta, phi, T)
        A=1/3
        B=1/3
        C=1/3
        D=1/3
        for k in range (0,1000,1):
            UpdateSequence()
        X[j]=T
        MagnetisationY[j]=ComputeMy()

        j=j+1

    return(MagnetisationY)


def ReturnMz(theta, phi, X):
    #Call this function to obtain Mz
    global A
    global B
    global C
    global D
    NUM=len(X)
    MagnetisationZ=np.empty(NUM)

    j=0
    for T in X:
        ComputeEnergyAndMagField(theta, phi, T)
        A=1/3
        B=1/3
        C=1/3
        D=1/3
        for k in range (0,1000,1):
            UpdateSequence()
        X[j]=T
        MagnetisationZ[j]=ComputeMz()

        j=j+1

    return(MagnetisationZ)


def ReturnMagnetisation(theta, phi, X):
    #Call this function to obtain Mz
    global A
    global B
    global C
    global D
    NUM=len(X)
    MagnetisationX=np.empty(NUM)
    MagnetisationY=np.empty(NUM)
    MagnetisationZ=np.empty(NUM)

    j=0
    for T in X:
        ComputeEnergyAndMagField(theta, phi, T)
        A=1/3
        B=1/3
        C=1/3
        D=1/3
        for k in range (0,1000,1):
            UpdateSequence()
        X[j]=T
        MagnetisationX[j]=ComputeMx()
        MagnetisationY[j]=ComputeMy()
        MagnetisationZ[j]=ComputeMz()

        j=j+1
    Magnetisation=np.sqrt(MagnetisationX*MagnetisationX+MagnetisationY*MagnetisationY+MagnetisationZ*MagnetisationZ)
    return(Magnetisation)


def ReturnSpecificHeat(theta, phi, X):
    #Call this function to obtain Cb
    Energy = ReturnEnergy(theta, phi, X)
    SpecificHeat=ComputeSpecificHeat(X, Energy)
    return(SpecificHeat)

def ReturnEntropy(theta, phi, X):
    #Call this function to obtain E
    Energy = ReturnEnergy(theta, phi, X)
    SpecificHeat=ComputeSpecificHeat(X, Energy)
    Entropy=ComputeEntropy(X, SpecificHeat)
    return(Entropy)