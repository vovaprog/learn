import numpy as np
import matplotlib.pyplot as plt
from os import listdir
from os.path import isfile, join
import re

files = [join("./build_release/plots", f) for f in listdir("./build_release/plots") if isfile(join("./build_release/plots", f))]

for fl in files:
    x,y = np.loadtxt(fl,dtype='int', delimiter='|', unpack=True)
    
    m = re.search("/([^/.]+).txt$", fl)
    
    plt.plot(x, y, label=m.group(1))

plt.legend()

plt.xlabel("items")
plt.ylabel("microseconds")

plt.show()

