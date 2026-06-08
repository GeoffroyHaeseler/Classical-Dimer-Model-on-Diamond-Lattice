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


PHI=[0, 10, 20, 30, 40, 45, 50, 55, 58, 59, 59.6, 60]
#Tc=[1.2089, 1.2059, 1.1959, 1.1550, 1.0891, 01.012, 1.0003, 1.0711, 1.2468, 1.3486, 1.3686, 1.3766]
N=len(PHI)

print('------Compute figure------')
insert1=ax.inset_axes((0.38, 0.43, 0.60, 0.34))
ax.add_patch(Rectangle((0, 0), 1, 0.08, facecolor= 'None', edgecolor='k'))
for i in range(N):

    phi=PHI[i]*math.pi/180
    thetac=math.acos(1/(math.sqrt(3+2*math.tan(phi)**2)))
    theta = 1 * thetac

    print(i, "   φ=", phi, "   θ=", theta)

    T = np.linspace(0.00165, Tf, num=NUM)

    Entropy = ReturnEntropy(theta, phi, T)

    if PHI[i]!=40:
        ax.plot     (T, Entropy, '-', color=(0.8*i/(N-1), 0, 0.8*(N-1-i)/(N-1)), label=r'$\phi=$'+str(PHI[i])+r'$\degree$')
        if PHI[i]>40:
            insert1.plot(T, Entropy, '-', color=(0.8*i/(N-1), 0, 0.8*(N-1-i)/(N-1)))

    else:
        ax.plot     (T, Entropy, '-', color=(0, 0, 0), linewidth=2, label=r'$\phi=$'+str(PHI[i])+r'$\degree$')


ax.set_xlabel(r'$T$', fontsize=20)
ax.set_ylabel(r'$E$', fontsize=20)
ax.set_xlim(0,Tf)
ax.set_ylim(0,0.14)
ax.set_yticks([0, 0.02, 0.04, 0.06, 0.08, 0.10, 0.12, 1/2*math.log(4/3), 0.14], [r'$0$', r'$0.02$', r'$0.04$', r'$0.06$', r'$0.08$', r'$0.10$', r'$0.12$', r'$\frac{1}{2}\ln \frac{4}{3}$', r'$0.14$'])

insert1.set_xlim(0,1)
insert1.set_ylim(0,0.08)
insert1.set_yticks([0, 0.02, 0.04, 0.06, 0.08], [r'$0$', r'$0.02$', r'$0.04$', r'$0.06$', r'$0.08$'])

ax.legend(loc='lower right', ncols=4)


print('------Saving figure------')
plt.savefig('KT3HusimiTree Entropy.png', bbox_inches='tight')
plt.clf()
plt.close('all')