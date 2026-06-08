from mpl_toolkits.axes_grid1.inset_locator import inset_axes
from matplotlib.patches import Rectangle
import matplotlib.pyplot as plt
import numpy as np
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
ax1storder= axes[0].inset_axes((0.4, 0.45, 0.50, 0.50))
ax1storder.tick_params(axis='both', labelsize = 9)
for i in range(len(FileNames)):

    File_Name = 'φ=0_θ=' + FileNames[i]
    print(File_Name)
    x = np.loadtxt(File_Name + '.txt', skiprows=1, usecols=(2))
    y = np.loadtxt(File_Name + '.txt', skiprows=1, usecols=(16))

    axes[0].plot(   x,y,'-+')
    ax1storder.plot(x,y)

axes[0].legend(LegendList, prop={'size': 11}, loc=(0.75, 0.05))

axes[0].set_xlabel(r'$T$', fontsize=24)
axes[0].set_ylabel(r'$\chi_{\hat{z}}$', fontsize=24)
axes[0].set_title(r'$\phi=0\degree$', fontsize=24)

axes[0].set_xlim(0,10)
axes[0].set_ylim(0,4)

axes[0].add_patch(Rectangle((2, -0.5), 0.6, 0.05, facecolor= 'None', edgecolor='k'))
ax1storder.set_xlim(1, 3)
ax1storder.set_xticks([1, 1.50, 2, 2.5, 3])

ax1storder.set_ylim(0, 4)
ax1storder.set_yticks([0, 1, 2, 3, 4])
ax1storder.yaxis.tick_right()

#---------------------------------------------------------------------------------------------------------------------------------------------------

print('20')
ax1storder= axes[1].inset_axes((0.4, 0.45, 0.50, 0.50))
ax1storder.tick_params(axis='both', labelsize = 9)
for i in range(len(FileNames)):

    File_Name = 'φ=20_θ=' + FileNames[i]
    print(File_Name)
    x = np.loadtxt(File_Name + '.txt', skiprows=1, usecols=(2))
    y = np.loadtxt(File_Name + '.txt', skiprows=1, usecols=(16))

    axes[1].plot(   x,y,'-+')
    ax1storder.plot(x,y)

axes[1].legend(LegendList, prop={'size': 11}, loc=(0.75, 0.05))

axes[1].set_xlabel(r'$T$', fontsize=24)
axes[1].set_title(r'$\phi=20\degree$', fontsize=24)

axes[1].set_xlim(0,10)
axes[1].set_ylim(0,4)

axes[1].add_patch(Rectangle((2, -0.5), 0.6, 0.05, facecolor= 'None', edgecolor='k'))
ax1storder.set_xlim(1, 3)
ax1storder.set_xticks([1, 1.50, 2, 2.5, 3])

ax1storder.set_ylim(0, 4)
ax1storder.set_yticks([0, 1, 2, 3, 4])
ax1storder.yaxis.tick_right()

#---------------------------------------------------------------------------------------------------------------------------------------------------

print('40')
ax1storder= axes[2].inset_axes((0.4, 0.45, 0.50, 0.50))
ax1storder.tick_params(axis='both', labelsize = 9)
for i in range(len(FileNames)):

    File_Name = 'φ=40_θ=' + FileNames[i]
    print(File_Name)
    x = np.loadtxt(File_Name + '.txt', skiprows=1, usecols=(2))
    y = np.loadtxt(File_Name + '.txt', skiprows=1, usecols=(16))

    axes[2].plot(   x,y,'-+')
    ax1storder.plot(x,y)

axes[2].legend(LegendList, prop={'size': 11}, loc=(0.75, 0.05))

axes[2].set_xlabel(r'$T$', fontsize=24)
axes[2].set_title(r'$\phi=40\degree$', fontsize=24)

axes[2].set_xlim(0,10)
axes[2].set_ylim(0,5)

axes[2].add_patch(Rectangle((2, -0.5), 0.6, 0.05, facecolor= 'None', edgecolor='k'))
ax1storder.set_xlim(0, 2)
ax1storder.set_xticks([0, 0.5, 1, 1.50, 2, 2.5, 3])

ax1storder.set_ylim(0, 5)
ax1storder.set_yticks([0, 1, 2, 3, 4, 5])
ax1storder.yaxis.tick_right()

#---------------------------------------------------------------------------------------------------------------------------------------------------

print('60')
ax1storder= axes[3].inset_axes((0.4, 0.45, 0.50, 0.50))
ax1storder.tick_params(axis='both', labelsize = 9)
for i in range(len(FileNames)):

    File_Name = 'φ=60_θ=' + FileNames[i]
    print(File_Name)
    x = np.loadtxt(File_Name + '.txt', skiprows=1, usecols=(2))
    y = np.loadtxt(File_Name + '.txt', skiprows=1, usecols=(16))

    axes[3].plot(   x,y,'-+')
    ax1storder.plot(x,y)

axes[3].legend(LegendList, prop={'size': 11}, loc=(0.75, 0.05))

axes[3].set_xlabel(r'$T$', fontsize=24)
axes[3].set_title(r'$\phi=60\degree$', fontsize=24)

axes[3].set_xlim(0,10)
axes[3].set_ylim(0,5)

axes[3].add_patch(Rectangle((2, -0.5), 0.6, 0.05, facecolor= 'None', edgecolor='k'))
ax1storder.set_xlim(0, 2)
ax1storder.set_xticks([0, 0.5, 1, 1.50, 2, 2.5, 3])

ax1storder.set_ylim(0, 5)
ax1storder.set_yticks([0, 1, 2, 3, 4, 5])
ax1storder.yaxis.tick_right()



plt.rcParams['text.usetex'] = False


print('saving figure')
fig.tight_layout()
fig.savefig('KT3TiltedSusceptibilityZ.png')
plt.clf()
plt.close()



