from mpl_toolkits.axes_grid1.inset_locator import inset_axes
from matplotlib.patches import Rectangle
import matplotlib.pyplot as plt
import numpy as np
import math
import os

os.chdir("D:/3A/KT3/results/Thermo/Test 8- PSMN - multi θ and φ L=48")
plt.rcParams['text.usetex'] = True
plt.style.use('classic')



FileNames = ['0', '0.25', '0.5', '0.75', '0.9']

LegendList=[]
LegendList.append(r'$\theta=0\theta_c$')
LegendList.append(r'$\theta=0.25\theta_c$')
LegendList.append(r'$\theta=0.5\theta_c$')
LegendList.append(r'$\theta=0.75\theta_c$')
LegendList.append(r'$\theta=0.9\theta_c$')



fig, axes = plt.subplots(nrows=1, ncols=4, figsize=(23.25, 5))

Tc = 8/(3*math.log(3))

print('00')
for i in range(len(FileNames)):

    File_Name = 'φ=0_θ=' + FileNames[i]
    print(File_Name)
    x = np.loadtxt(File_Name + '.txt', skiprows=1, usecols=(2))
    y = np.loadtxt(File_Name + '.txt', skiprows=1, usecols=(12))

    axes[0].plot(   x,y,'-+')

axes[0].set_xlabel(r'$T$', fontsize=24)
axes[0].set_ylabel(r'$m_{\hat{y}}$', fontsize=24)
axes[0].set_title(r'$\phi=0\degree$', fontsize=24)

axes[0].set_xlim(0,10)
axes[0].set_ylim(-0.001,0.1)

#---------------------------------------------------------------------------------------------------------------------------------------------------

print('20')
for i in range(len(FileNames)):

    File_Name = 'φ=20_θ=' + FileNames[i]
    print(File_Name)
    x = np.loadtxt(File_Name + '.txt', skiprows=1, usecols=(2))
    y = np.loadtxt(File_Name + '.txt', skiprows=1, usecols=(12))

    axes[1].plot(   x,y,'-+')


axes[1].set_xlabel(r'$T$', fontsize=24)
axes[1].set_title(r'$\phi=20\degree$', fontsize=24)


axes[1].set_xlim(0,10)
axes[1].set_ylim(-0.001,0.1)


axes[1].legend(LegendList, prop={'size': 15}, loc=(0.62, 0.55))


#---------------------------------------------------------------------------------------------------------------------------------------------------

print('40')
for i in range(len(FileNames)):

    File_Name = 'φ=40_θ=' + FileNames[i]
    print(File_Name)
    x = np.loadtxt(File_Name + '.txt', skiprows=1, usecols=(2))
    y = np.loadtxt(File_Name + '.txt', skiprows=1, usecols=(12))

    axes[2].plot(x,y,'-+')

axes[2].set_xlabel(r'$T$', fontsize=24)
axes[2].set_title(r'$\phi=40\degree$', fontsize=24)

axes[2].set_xlim(0,10)
axes[2].set_ylim(-0.001,0.1)


#---------------------------------------------------------------------------------------------------------------------------------------------------

print('60')
for i in range(len(FileNames)):

    File_Name = 'φ=60_θ=' + FileNames[i]
    print(File_Name)
    x = np.loadtxt(File_Name + '.txt', skiprows=1, usecols=(2))
    y = np.loadtxt(File_Name + '.txt', skiprows=1, usecols=(12))

    axes[3].plot(x,y,'-+')

axes[3].set_xlabel(r'$T$', fontsize=24)
axes[3].set_title(r'$\phi=60\degree$', fontsize=24)

axes[3].set_xlim(0,10)
axes[3].set_ylim(-0.001,0.1)







plt.rcParams['text.usetex'] = False


print('saving figure')
fig.tight_layout()
fig.savefig('KT3TiltedMagnetisationY.png')
plt.clf()
plt.close()



