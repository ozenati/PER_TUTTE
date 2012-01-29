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

plt.subplot(111)
# rects3 = plt.bar(ind, menMeans3, width,
#                  color='g',
#                  yerr=menStd3)
# #error_kw=dict(elinewidth=6, ecolor='yellow'))

# rects1 = plt.bar(ind+width, menMeans, width,
#                  color='r',
#                  yerr=menStd)
# # error_kw=dict(elinewidth=6, ecolor='pink'))

rects2 = plt.bar(ind+2*width, menMeans2, width,
                 color='y',
                 yerr=menStd2)
  #error_kw=dict(elinewidth=6, ecolor='yellow'))

# add some
plt.ylabel('Scores')
plt.title('Scores by group and gender')
plt.xticks(ind + width, ('SA 1', 
                         'SA 2',
                         'SA 2 (vec2f)',
                         'SA 3',
                         'PS', 
                         'PA' )) 
# plt.xticks(ind, ('G1', 'G2', 'G3', 'G4', 'G5') )

#plt.legend( (rects1[0], rects2[0], rects3[0]), ('Aiir trafic', 'Imdb', 'Migration') )

def autolabel(rects):
    # attach some text labels
    for rect in rects:
        height = rect.get_height()
        a = str(height)
        # a=a.substring(0,5);
        plt.text(rect.get_x() + rect.get_width(), 1.05*height, '%f.4'%float(height),
                ha='center', va='bottom')

# autolabel(rects1)
# autolabel(rects2)
# autolabel(rects3)

plt.show()
