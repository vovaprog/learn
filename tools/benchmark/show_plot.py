import numpy as np
import matplotlib.pyplot as plt
from os import listdir
from os.path import isfile, join
import re
import sys

plotCounter = 0
lineStyles = ["-","--","-.",":"]
lineStyleIndex = 0

def plotFiles(files, benchSetName):
    global plotCounter
    global lineStyleIndex
    
    for fl in files:
        x, y = np.loadtxt(fl, dtype='int', delimiter='|', unpack=True)
    
        m = re.search("/([^/.]+).txt$", fl)
    
        plt.plot(x, y, label=benchSetName + m.group(1), linewidth=2, linestyle=lineStyles[lineStyleIndex])
        
        plotCounter += 1
        if plotCounter >= 7:
            plotCounter = 0
            lineStyleIndex += 1
            if lineStyleIndex >= len(lineStyles):
                lineStyleIndex = 0

folderName = "./build_release/plots"

if len(sys.argv) > 1:
    folderName = sys.argv[1]

files = [join(folderName, f)
         for f in listdir(folderName) if isfile(join(folderName, f))]

plotFiles(files, "")

dirs = [join(folderName, f)
        for f in listdir(folderName) if not isfile(join(folderName, f))]

print dirs

for folName in dirs:
    files = [join(folName, f)
             for f in listdir(folName) if isfile(join(folName, f))]
    m = re.search("/([^/]+)$", folName)
    plotFiles(files, m.group(1) + " ")

plt.legend()

plt.xlabel("items in map")
plt.ylabel("microseconds")

plt.show()
