import matplotlib.pyplot as plt
import sys
import os
#sys.path.append(os.path.abspath("D:/Postdoc/GitHub/Husimi Tree"))
os.chdir("D:/KT3/Husimi Tree")
import HusimiCactusFunctions


Ti=0.3
Tf=5
X=np.linspace(Ti, Tf, num=5000)

phi=0*math.pi/180
thetac=math.acos(1/(math.sqrt(3+2*math.tan(phi)**2)))
theta=0.996*thetac
#phi=0
#theta=0

a=ReturnEnergy(theta, phi, X)
plt.plot(X, a)

print('saving figure')
plt.savefig('test.png', bbox_inches='tight')
plt.clf()
plt.close('all')