import sys
sys.path.append('./tools')
from _parser import parse
from crosscorrelation import find_pixels_shifts
from colormap import colormap
import matplotlib.pyplot as plt
import matplotlib
matplotlib.rc("font", family="Liberation Sans")
import copy as cp
import numpy as np
from copy import deepcopy

print "Executing MAIN..."

PIR_data, IMUU_reduced_data, LOG_inflated_data = parse()
#colormap(PIR_data, IMUU_reduced_data, LOG_inflated_data, -1,
#         save_fig=False, smooth=False)

threshold = 2
Uson = cp.deepcopy(IMUU_reduced_data)
Uson_grad = [y-x for x, y in zip(Uson[:-1], Uson[1:])] 
Veh = []
for x in Uson_grad:
    if x < -threshold:
        Veh.append(1) # Vehicle enters
    elif x > threshold:
        Veh.append(-1) # Vehicle leaves
    else:
        Veh.append(0)
#plt.figure()
#plt.plot(Uson, label="Ultrasonic signal")
#plt.plot(Uson_grad, label="Differentiated signal")
#plt.legend()
#plt.show()

idx = 0
count = []
enter = 0
exit = 0
while idx < len(Veh):
    if Veh[idx] == 1:
        enter = idx
        if idx+1 < len(Veh):
            idx += 1
        else:
            break
        while Veh[idx] == 0:
            if idx+1 < len(Veh):
                idx += 1
            else:
                break
        if Veh[idx] == 1:
            print "Missing exit condition at index:", idx
        else:
            exit = idx
            count.append([enter, exit])
            idx += 1
    elif Veh[idx] == -1:
        print "Missing enter condition at index:", idx
        idx += 1
    else:
        idx += 1

cumulat = [0]*len(Veh)
for x in count:
    cumulat[x[1]] = 1
single = deepcopy(cumulat[0:15000])
for i in range(len(cumulat)-1):
    cumulat[i+1] += cumulat[i]
Log = cp.deepcopy(LOG_inflated_data)
cLog = np.array(Log)/10.
for i in range(len(cLog)-1):
    cLog[i+1] += cLog[i]
Log = [x/10 for x in Log[0:15000]]

#print find_pixels_shifts(PIR_data, [960, 990, 0, 15], 
#                         center_cc=True, time_cc=True, diff=True)

if True:
    T = []
    D = []
    V = []
    for x in count:
        t = find_pixels_shifts(PIR_data, [x[0]-8,x[1]+8,0,191],
                               center_cc=True, time_cc=True, diff=True)
        print "Time shift:", t
        d= np.min(Uson[x[0]:x[1]+1])
        v = 4*d/t
        T.append(t)
        D.append(d)
        V.append(v)

    #print T
    #print D
    #print V
    V = np.array(V)
    v_mean = np.mean(V[~np.isinf(V)])
    print "Average speed: ", v_mean 
    plt.figure()
    #plt.plot(T, label="Time shift")
    #plt.plot(D, label="Normal distance")
    plt.plot(V, label="Estimated speed")
    plt.xlabel("Vehicle Count (Veh)")
    plt.ylabel("Speed (mph)")
    plt.title("Speed Estimation with Average of %.2f mph" % v_mean)
    plt.legend()
    plt.show()