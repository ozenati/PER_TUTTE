#!/usr/bin/env python
import numpy as np
import matplotlib.pyplot as plt

N = 5
menMeans = (0.272529, 0.0577969, 0.0575821, 0.0725789, 0.0711396)
menStd = (0.00160762, 0.000884534, 0.000716025, 0.000748211, 0.00917466)

ind = np.arange(N)  # the x locations for the groups
width = 0.35       # the width of the bars


plt.subplot(111)
rects1 = plt.bar(ind, menMeans, width,
                 color='r',
                 yerr=menStd)
# error_kw=dict(elinewidth=6, ecolor='pink'))

# 0.288603 s
# ecart type : 0.452873s

# add some
plt.ylabel('Scores')
plt.title('Scores by group and gender')
plt.xticks(ind+width/2, ('sequentiel asynchrone', 
                         'sequentiel asynchrone 2',
                         'sequentiel asynchrone 2 (vec2f)',
                         'sequentiel asynchrone 3',
                         'parallele synchrone' )) 
# plt.xticks(ind, ('G1', 'G2', 'G3', 'G4', 'G5') )

# plt.legend( (rects1[0], rects1[0]), ('Men', 'Men') )

def autolabel(rects):
    # attach some text labels
    for rect in rects:
        height = rect.get_height()
        plt.text(rect.get_x()+rect.get_width()/2., 1.05*height, '%d'%int(height),
                ha='center', va='bottom')

autolabel(rects1)
# autolabel(rects2)

plt.show()
