import matplotlib.pyplot as plt
from numpy import *

plt.style.use('seaborn-whitegrid')
plt.rcParams['mathtext.fontset'] = "cm"
plt.rcParams['font.family'] = "serif"

with open('graphdata.dat') as fp:
	tik10,tik20,tik30 = loadtxt(fp,unpack=True)

# Get total tick count at each timestep
tiktot = add(tik10,tik20)
tiktot = add(tiktot,tik30)

fig, (ax) = plt.subplots(1,1,figsize=(10,8))
ax.set_title('Lotteries won v. Total switches')
ax.set_ylabel('Ticks used (Lotteries won)')
ax.set_xlabel('Total ticks')
ax.plot(tiktot,tik10,c='r',label='10 Tickets')
ax.plot(tiktot,tik20,c='g',label='20 Tickets')
ax.plot(tiktot,tik30,c='b',label='30 Tickets')

plt.legend()
plt.show()
