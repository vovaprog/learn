import numpy as np
import matplotlib.pyplot as plt
from os import listdir
from os.path import isfile, join
import re
import sys

folderName = "./build_release/plots"

if len(sys.argv) > 1:
    folderName = sys.argv[1]

files = [join(folderName, f)
         for f in listdir(folderName) if isfile(join(folderName, f))]

for fl in files:
    x, y = np.loadtxt(fl, dtype='int', delimiter='|', unpack=True)

    m = re.search("/([^/.]+).txt$", fl)

    plt.plot(x, y, label=m.group(1))

plt.legend()

plt.xlabel("items")
plt.ylabel("microseconds")

plt.show()
