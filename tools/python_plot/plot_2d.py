import matplotlib.pyplot as pl
import numpy as np


x = np.linspace(start=0.0, stop=10.0, num=300)




y = np.sin(x)
y2 = np.cos(x)




pl.plot(x, y)
pl.plot(x, y2)

pl.grid(True)
pl.xticks(np.arange(min(x), max(x) + 1, 1.0))
pl.show()

