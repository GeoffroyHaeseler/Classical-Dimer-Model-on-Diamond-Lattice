import matplotlib.pyplot as plt
import numpy as np
import math
import os

os.chdir("D:/3A/KT3")
plt.rcParams['text.usetex'] = True
plt.style.use('classic')

# What do you want to plot?
# <E>       5
# Cb        7
# r3r3      9
# χ         11
# |m_z|     13
# χm_z      14
# nA        28
# nB        29
# nC        30

Data=13
if Data == 3:
    title='E'
    DataName=r'$<E>$'

elif Data == 4:
    title='Cb'
    DataName=r'$C_b$'

elif Data == 5:
    title='BC'
    DataName=r'$V_E$'

elif Data == 6:
    title='m'
    DataName=r'$<m>$'

elif Data == 7:
    title='χm'
    DataName=r'$\chi$'

elif Data == 8:
    title='mBC'
    DataName=r'$V_m$'

elif Data == 9:
    title='m_x'
    DataName=r'$m_x$'

elif Data == 10:
    title='χx'
    DataName=r'$\chi_{m_x}$'

elif Data == 11:
    title='m_xBC'
    DataName=r'$V_{m_x}$'

elif Data == 12:
    title='m_y'
    DataName=r'$m_y$'

elif Data == 13:
    title='χy'
    DataName=r'$\chi_{m_y}$'

elif Data == 14:
    title='m_yBC'
    DataName=r'$V_{m_y}$'

elif Data == 15:
    title='m_z'
    DataName=r'$m_z$'

elif Data == 16:
    title='χz'
    DataName=r'$\chi_{m_z}$'

elif Data == 17:
    title='m_zBC'
    DataName=r'$V_{m_z}$'


FileName = ['6', '9', '12', '18', '24', '30', '48']


LegendList=[]


Tc=8/(3*math.log(3))


for size in FileName:
    L = float(size)

    File_Name = 'L=' + size
    print(File_Name)
    x = np.loadtxt(File_Name + '.txt', skiprows=1, usecols=(2))
    y = np.loadtxt(File_Name + '.txt', skiprows=1, usecols=(Data))

    LegendName = 'L=' + size
    plt.plot(x,y, '-+', label=LegendName)
    #plt.yscale("log")
    #LegendList.append(LegendName)



plt.xlabel(r'$T$')
plt.ylabel(DataName)

plt.xlim(2,20)
#plt.ylim(0.665, 2/3)

#plt.legend(LegendList, prop={'size': 10})
plt.legend(loc ='upper right')

print('saving figure')
plt.savefig(title + '.png', bbox_inches='tight');
plt.clf();


plt.rcParams['text.usetex'] = False



