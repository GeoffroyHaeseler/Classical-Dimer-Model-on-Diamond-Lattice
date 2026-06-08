import matplotlib.colors as mcolors
import matplotlib.pyplot as plt
from numpy import trapz
import numpy as np
import math
import os


os.chdir("D:/3A/KT3/results/Thermo/Test 8- PSMN - multi θ and φ L=48")
plt.rcParams['text.usetex'] = True
plt.style.use('classic')



LegendList=[]

File_Name = 'φ=60_θ=0.9'
print(File_Name)
x1 = np.loadtxt(File_Name + '.txt', skiprows=1, usecols=(2))
y1 = np.loadtxt(File_Name + '.txt', skiprows=1, usecols=(4))
y1=y1/x1
LegendName = 'new PBC L=9 Heated AllTS'
LegendList.append(LegendName)
print(trapz(y1,x=x1))

Y1=[]
for i in range (len(x1)):
    Y1.append(trapz(y1[0:i],x=x1[0:i]))
plt.plot(x1, Y1)

x=np.zeros(1000)+8/(3*math.log(3))
y=np.linspace(0,0.14,1000)
plt.plot(x,y)
x=np.linspace(0,10,1000)
y=np.zeros(1000)+0.116
plt.plot(x,y)

#plt.ylim(0,0.2)

plt.xlabel("T")
plt.ylabel(r'$S$')

#plt.legend(LegendList, prop={'size': 10})

plt.rcParams['text.usetex'] = False


print(0.116*8/(3*math.log(3))*1.380649/1.602)

print('saving figure')
plt.savefig('test.png');
plt.clf();


