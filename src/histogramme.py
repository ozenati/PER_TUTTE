#!/usr/bin/env python
import numpy as np
import matplotlib.pyplot as plt

N = 6
menMeans = (0.068634, 0.0162732, 0.0162326, 0.0137414, 0.0202103, 0.050945, )
menStd = (0.000134027, 2.48238e-05, 2.15133e-05, 5.20517e-05, 4.77279e-05, 0.000306196, )

menMeans2 = (0.330761, 0.0703849, 0.0705067, 0.074734, 0.0882206, 0.207048, )
menStd2 = (0.00280537, 0.000108425, 6.23691e-05, 0.000228272, 0.000153175, 0.000457334, )

menMeans3 = (0.0010435, 0.000238641, 0.000240193, 0.000233299, 0.00214291, 0.000448204, )
menStd3 = (4.78756e-06, 1.49911e-06, 1.37312e-06, 1.38273e-05, 4.54968e-06, 3.44309e-05, )

ind = np.arange(N)  # the x locations for the groups
width = 0.20       # the width of the bars

def autolabel(rects):
    # attach some text labels
    for rect in rects:
        height = rect.get_height()
        a = str(height)
        # a=a.substring(0,5);
        plt.text(rect.get_x() + rect.get_width(), 1.05*height, '%.4f'%float(height),
                ha='center', va='bottom')


#plt.subplots_adjust(hspace=0.4)

plt.subplot(131)
rects1 = plt.bar(ind, menMeans, width,
                 color='r',
                 capsize=6,
                 yerr=menStd)
#                 error_kw=dict(elinewidth=6, ecolor='yellow'))

plt.ylabel('mean time of execution')
plt.title('Aiir_traffic')
plt.xticks(ind, ('SA 1', 
                         'SA 2',
                         'SA 2b',
                         'SA 3',
                         'PS', 
                         'PA' )) 

autolabel(rects1)

plt.subplot(132)
rects2 = plt.bar(ind, menMeans2, width,
                 color='y',
                 capsize=6,
                 yerr=menStd2)
# error_kw=dict(elinewidth=6, ecolor='pink'))

plt.ylabel('mean time of execution')
plt.title('Imdb')
plt.xticks(ind, ('SA 1', 
                         'SA 2',
                         'SA 2b',
                         'SA 3',
                         'PS', 
                         'PA' )) 

autolabel(rects2)

plt.subplot(133)
rects3 = plt.bar(ind, menMeans3, width,
                 color='g',
                 capsize=6,
                 yerr=menStd3)
  #error_kw=dict(elinewidth=6, ecolor='yellow'))

plt.ylabel('mean time of execution')
plt.title('Migration')
plt.xticks(ind, ('SA 1', 
                         'SA 2',
                         'SA 2b',
                         'SA 3',
                         'PS', 
                         'PA' )) 

#plt.legend( (rects1[0], rects2[0], rects3[0]), ('Aiir trafic', 'Imdb', 'Migration') )

autolabel(rects3)

plt.show()
