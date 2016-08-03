import matplotlib.pyplot as pl
import numpy as np

x = np.linspace(0.0, 10.0, 256, endpoint=True)

y = np.sin(x * 10.0) + np.cos(x * 3.0) + np.sin(x * 6.33)

pl.plot(x, y)

pl.show()

