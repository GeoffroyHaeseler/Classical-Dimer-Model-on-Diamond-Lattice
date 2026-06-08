from matplotlib.patches import Rectangle
import matplotlib.pyplot as plt
import numpy as np
import math
import os

os.chdir("D:/KT3/Husimi Tree/Probing Critical Line")
plt.rcParams['text.usetex'] = True
plt.style.use('classic')
fig, ax = plt.subplots(nrows=1, ncols=1, figsize=(10, 10))

Tf=10
NUM=5000


PHI=[0, 10, 20, 30, 40, 45, 50, 55, 58, 59, 59.8, 60]
#Tc=[1.2089, 1.1959, 1.1550, 1.0891, 1.012, 1.0003, 1.0711, 1.2468, 1.3486, 1.3686, 1.2059, 1.3766]
N=len(PHI)

print('------Compute figure------')
insert1=ax.inset_axes((0.58, 0.48, 0.40, 0.50))
ax.add_patch(Rectangle((0, 0.15), 0.5, 0.15, facecolor= 'None', edgecolor='k'))
for i in range(N):

    phi=PHI[i]*math.pi/180
    thetac=math.acos(1/(math.sqrt(3+2*math.tan(phi)**2)))
    theta = 1 * thetac

    print(i, "   φ=", phi, "   θ=", theta)

    T = np.linspace(0.00165, Tf, num=NUM)

    Magnetisation=ReturnMagnetisation(theta, phi, T)

    if PHI[i]!=40:
        ax.plot(T, Magnetisation, '-', color=(0.8*i/(N-1), 0,  0.8*(N-1-i)/(N-1)), label=r'$\phi=$'+str(PHI[i])+r'$\degree$')
        if PHI[i]>40:
            insert1.plot(T, Magnetisation, '-', color=(0.8*i/(N-1), 0, 0.8*(N-1-i)/(N-1)))

    else:
        ax.plot(T, Magnetisation, '-', color=(0, 0, 0), linewidth=2, label=r'$\phi=$'+str(PHI[i])+r'$\degree$')


ax.set_xlabel(r'$T$', fontsize=20)
ax.set_ylabel(r'$m$', fontsize=20)
ax.set_xlim(0,Tf)
ax.set_ylim(0,0.3)
ax.set_yticks([0, 0.05, 0.1, 0.15, 1/6, 0.2, 0.25, 1/(2*math.sqrt(3)), 0.3], [r'$0$', r'$0.05$', r'$0.1$', r'$0.15$', r'$1/6$', r'$0.2$', r'$0.25$', r'$1/2\sqrt{3}$', r'$0.3$'])

insert1.set_xlim(0,0.5)
insert1.set_ylim(0.15,0.3)
insert1.set_yticks([0.15, 1/6, 0.2, 0.25, 1/(2*math.sqrt(3)), 0.3], [r'$0.15$', r'$1/6$', r'$0.2$', r'$0.25$', r'$1/2\sqrt{3}$', r'$0.3$'])

ax.legend(loc='lower left', ncols=4, title=r'$\theta=\theta_c^{01}(\phi)$')


print('saving figure')
plt.savefig('KT3HusimiTree Magnetisation.png', bbox_inches='tight')
plt.clf()
plt.close('all')