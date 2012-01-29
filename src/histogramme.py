#!/usr/bin/env python
import numpy as np
import matplotlib.pyplot as plt

N = 6
menMeans = (0.0550621, 0.0132359, 0.013154, 0.0127567, 0.0162488, 0.044538, )
menStd = (0.00147655, 0.000644819, 0.000672862, 0.00211036, 0.000691535, 0.00365513, )

menMeans2 = (0.26552, 0.0565255, 0.0566587, 0.0753496, 0.0715155, 0.199985, )
menStd2 = (0.00270784, 0.000429853, 0.000815052, 0.0554412, 0.00174922, 0.0731905, )

menMeans3 = (0.000872804, 0.000191297, 0.00019374, 0.000212658, 0.0017259, 0.000410442, )
menStd3 = (3.43957e-05, 6.44661e-06, 7.71777e-06, 6.65779e-05, 3.03403e-05, 0.000130155, )

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
