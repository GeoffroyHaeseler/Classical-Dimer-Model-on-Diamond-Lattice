from matplotlib.colors import LinearSegmentedColormap, ListedColormap
import matplotlib.colors as colors
import matplotlib.pyplot as plt
import numpy as np
import math
import os

os.chdir("~/KT3/Results")
plt.rcParams['text.usetex'] = True
plt.style.use('classic')

Phi = '60'
THETA = ['0', '0.25', '0.50', '0.75', '0.90', '1']
TEMPERATURE = ['1', '2', '5', '+oo']
plane='hh0;-kk2k'
cutoff = 1

Nrows=len(THETA)
Ncols=len(TEMPERATURE)+1 #For the color bars


fig, axes = plt.subplots(nrows=Nrows, ncols=Ncols, figsize=(5*Ncols, 5*Nrows))

channel=3 #2:full 3:dipolar 4:aiao 5:bragg

for i in range(len(THETA)):
    Theta=THETA[i]

    for j in range(len(TEMPERATURE)):
        Temperature=TEMPERATURE[j]

        FileName = 'φ=' + Phi+ '_θ=' + Theta + '_T=' + Temperature + '_' + plane
        print(FileName)

        #Read Data
        NSP = np.loadtxt(FileName+ '.txt', skiprows=1)
        with open(FileName+ '.txt') as f:
            Type = int(f.readline().strip('\n'))

        #Compute the circle in which data are displayed (and were computed):
        if Type==0:
            PlottedData = np.argwhere( 2*NSP[:,0]**2 + 1*NSP[:,1]**2 < 16 )
        if Type==1:
            PlottedData = np.argwhere( 2*NSP[:,0]**2 + 1*NSP[:,1]**2 < 16 )
        if Type==2:
            PlottedData = np.argwhere( 2*NSP[:,0]**2 + 6*NSP[:,1]**2 < 16 )
        if Type==3:
            PlottedData = np.argwhere( 2*NSP[:,0]**2 + 3*NSP[:,1]**2 < 16 )
        if Type==4:
            PlottedData = np.argwhere( 2*NSP[:,0]**2 + 3*NSP[:,1]**2 < 16 )
        if Type==5:
            PlottedData = np.argwhere( 2*NSP[:,0]**2 + 6*NSP[:,1]**2 < 16 )
        if Type==6:
            PlottedData = np.argwhere( 6*NSP[:,0]**2 + 3*NSP[:,1]**2 < 16 )

        #Full Data
        x0 = NSP[PlottedData, 0]
        y0 = NSP[PlottedData, 1]
        z0 = NSP[PlottedData, channel]

        #Extract AIAO's peak
        if channel!=3:
            LogScale  = np.argwhere( z0[PlottedData] >= cutoff )
            x1=x0[LogScale]
            y1=y0[LogScale]
            z1=z0[LogScale]

        #Plot diffuse scattering
        PCMa = axes[i,j].scatter(x0, y0, c=z0, vmin=0, vmax=cutoff, s=3, cmap="CMRmap", edgecolor="none")

        #Plot all in all out peaks in log scale
        if channel!=3:
            PCMb = axes[i,j].scatter(x1, y1, c=z1, s=3, cmap="Greys", edgecolor="none", norm=colors.LogNorm(vmin=cutoff))

        #Set the axis (depends on the scattering directions)
        if Type==0:
            axes[i,j].set_xlim((-2*math.sqrt(2), 2*math.sqrt(2)))
            axes[i,j].set_ylim((-4, 4))
            axes[Nrows-1,j].set_xlabel(r'$(h,h,0)$', fontsize=24)
            axes[i,0].set_ylabel(r'$(0, 0, l)$', fontsize=24)
            px=-2.8
            py=3.5
        if Type==1:
            axes[i,j].set_xlim((-2*math.sqrt(2), 2*math.sqrt(2)))
            axes[i,j].set_ylim((-4, 4))
            axes[Nrows-1,j].set_xlabel(r'$(h,\bar{h},0)$', fontsize=24)
            axes[i,0].set_ylabel(r'$(0, 0, l)$', fontsize=24)
            px=-2.8
            py=3.5
        if Type==2:
            axes[i,j].set_xlim((-2*math.sqrt(2), 2*math.sqrt(2)))
            axes[i,j].set_ylim((-2*math.sqrt(2/3),2*math.sqrt(2/3)))
            axes[Nrows-1,j].set_xlabel(r'$(h,\bar{h},0)$', fontsize=24)
            axes[i,0].set_ylabel(r'$(k, k, 2\bar{k})$', fontsize=24)
            px=-2.8
            py=1.45
        if Type==3:
            axes[i,j].set_xlim((-2*math.sqrt(2), 2*math.sqrt(2)))
            axes[i,j].set_ylim((-2*math.sqrt(4/3),2*math.sqrt(4/3)))
            axes[Nrows-1,j].set_xlabel(r'$(h,\bar{h},0)$', fontsize=24)
            axes[i,0].set_ylabel(r'$(l,l,l)$', fontsize=24)
            px=-2.8
            py=2.05
        if Type==4:
            axes[i,j].set_xlim((-2*math.sqrt(2), 2*math.sqrt(2)))
            axes[i,j].set_ylim((-2*math.sqrt(4/3),2*math.sqrt(4/3)))
            axes[Nrows-1,j].set_xlabel(r'$(h,h,0)$', fontsize=24)
            axes[i,0].set_ylabel(r'$(l,\bar{l},l)$', fontsize=24)
            px=-1.6
            py=2.05
        if Type==5:
            axes[i,j].set_xlim((-2*math.sqrt(2), 2*math.sqrt(2)))
            axes[i,j].set_ylim((-2*math.sqrt(2/3),2*math.sqrt(2/3)))
            axes[Nrows-1,j].set_xlabel(r'$(h,h,0)$', fontsize=24)
            axes[i,0].set_ylabel(r'$(\bar{k},k,2k)$', fontsize=24)
            px=-2.8
            py=1.45
        if Type==6:
            axes[i,j].set_xlim((-2*math.sqrt(2/3),2*math.sqrt(2/3)))
            axes[i,j].set_ylim((-2*math.sqrt(4/3),2*math.sqrt(4/3)))
            axes[Nrows-1,j].set_xlabel(r'$(k,\bar{k},2\bar{k})$')
            axes[i,0].set_ylabel(r'$(l,\bar{l},l)$')
            px=-1.6
            py=2.05

        axes[i,0].text(px, py, r"$\theta="+Theta+"$" + r'$\theta_c$', wrap=True, fontsize=16)
        axes[Nrows-1,j].text(px, -py, r"$T=0$", wrap=True, fontsize=16)
        if j != Ncols-1:
            axes[0,j].set_title(r"$T="+Temperature+"$" + r'$T_c$', wrap=True, fontsize=16)
        axes[0,3].set_title(r'$H=0$', wrap=True, fontsize=16)
        if i!=Nrows-1:
            axes[i,j].set_xticklabels([])
        if j!=0:
            axes[i,j].set_yticklabels([])


    #Add color bars
    cbar = fig.colorbar(PCMa, ax=[axes[i,Ncols-1]], label=r"Intensity (arbitrary units)", location = 'left')
    if channel != 3:
        cbar = fig.colorbar(PCMb, ax=[axes[i,Ncols-1]], label=r"Intensity (arbitrary units)")

    axes[i,Ncols-1].remove()


plt.subplots_adjust(wspace=0, hspace=0)

plt.rcParams['text.usetex'] = False

print('Saving figure.... Please wait')
plt.savefig('φ=' + Phi + '°_' + plane + '.png', bbox_inches='tight')
plt.clf()
plt.close('all')