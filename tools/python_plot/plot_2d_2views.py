import matplotlib.pyplot as pl
import numpy as np


x = np.linspace(start=0.0, stop=10.0, num=300)




y1 = np.sin(x)
y2 = np.cos(x)




def apply_style():
    pl.grid(True)
    pl.xticks(np.arange(min(x), max(x) + 1, 1.0))

pl.subplot(211) # 2rows 1col plot1
apply_style()
pl.plot(x, y1)

pl.subplot(212) # 2rows 1col plot2
apply_style()
pl.plot(x, y2)

pl.show()

