from matplotlib.colors import LinearSegmentedColormap, ListedColormap
import matplotlib.colors as colors
import matplotlib.pyplot as plt
import numpy as np
import math
import os

os.chdir("D:/Postdoc/KT3")
plt.rcParams['text.usetex'] = True
plt.style.use('classic')

cutoff=10

fig, axes = plt.subplots(nrows=1, ncols=2, figsize=(10, 5))

channel=3 #2:full 3:dipolar 4:aiao 5:bragg

FileName = 'NSP'
print(FileName)

#Read Data
NSP = np.loadtxt(FileName+ '.txt', skiprows=1)
with open(FileName+ '.txt') as f:
    Type = int(f.readline().strip('\n'))
print(Type)

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
PCMa = axes[0].scatter(x0, y0, c=z0, vmin=0, vmax=cutoff  , s=20, cmap="CMRmap", edgecolor="none")

#Plot all in all out peaks in log scale
if channel!=3:
    PCMb = axes[0].scatter(x1, y1, c=z1, s=15, cmap="Greys" , edgecolor="none",norm=colors.LogNorm(vmin=cutoff))

#Set the axis (depends on the scattering directions)
if Type==0:
    axes[0].set_xlim((-2*math.sqrt(2), 2*math.sqrt(2)))
    axes[0].set_ylim((-4, 4))
    axes[0].set_xlabel(r'$(h,h,0)$')
    axes[0].set_ylabel(r'$(0, 0, l)$')
if Type==1:
    axes[0].set_xlim((-2*math.sqrt(2), 2*math.sqrt(2)))
    axes[0].set_ylim((-4, 4))
    axes[0].set_xlabel(r'$(h,\bar{h},0)$')
    axes[0].set_ylabel(r'$(0, 0, l)$')
if Type==2:
    axes[0].set_xlim((-2*math.sqrt(2), 2*math.sqrt(2)))
    axes[0].set_ylim((-2*math.sqrt(2/3),2*math.sqrt(2/3)))
    axes[0].set_xlabel(r'$(h,\bar{h},0)$')
    axes[0].set_ylabel(r'$(k, k, 2\bar{k})$')
if Type==3:
    axes[0].set_xlim((-2*math.sqrt(2), 2*math.sqrt(2)))
    axes[0].set_ylim((-2*math.sqrt(4/3),2*math.sqrt(4/3)))
    axes[0].set_xlabel(r'$(h,\bar{h},0)$')
    axes[0].set_ylabel(r'$(l,l,l)$')
if Type==4:
    axes[0].set_xlim((-2*math.sqrt(2), 2*math.sqrt(2)))
    axes[0].set_ylim((-2*math.sqrt(4/3),2*math.sqrt(4/3)))
    axes[0].set_xlabel(r'$(h,h,0)$')
    axes[0].set_ylabel(r'$(l,\bar{l},l)$')
if Type==5:
    axes[0].set_xlim((-2*math.sqrt(2), 2*math.sqrt(2)))
    axes[0].set_ylim((-2*math.sqrt(2/3),2*math.sqrt(2/3)))
    axes[0].set_xlabel(r'$(h,h,0)$')
    axes[0].set_ylabel(r'$(\bar{k},k,2k)$')
if Type==6:
    axes[0].set_xlim((-2*math.sqrt(2/3),2*math.sqrt(2/3)))
    axes[0].set_ylim((-2*math.sqrt(4/3),2*math.sqrt(4/3)))
    axes[0].set_xlabel(r'$(k,\bar{k},2\bar{k})$')
    axes[0].set_ylabel(r'$(l,\bar{l},l)$')

#Add color bars
cbar = fig.colorbar(PCMa, ax=[axes[1]], label=r"Intensity (arbitrary units)", location = 'left')
if channel != 3:
    cbar = fig.colorbar(PCMb, ax=[axes[1]], label=r"Intensity (arbitrary units)")

axes[1].remove()
plt.subplots_adjust(wspace=0, hspace=0)
plt.rcParams['text.usetex'] = False

print('Saving figure.... Please wait')
if channel==2:
    plt.savefig('NSP_full.png')
if channel==3:
    plt.savefig('NSP_dipolar.png')
if channel==4:
    plt.savefig('NSP_aiao.png')
if channel==5:
    plt.savefig('NSP_bragg.png')

plt.clf()
plt.close('all')