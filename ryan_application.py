from matplotlib import pyplot as plt
import numpy as np
import time
from matplotlib.animation import FuncAnimation

x = 0
y = 0

plt.ion()

figure = plt.figure()
axes = figure.add_axes([0.1, 0.1, 0.8, 0.8])

line, = axes.plot(x, y)

plt.scatter(x, y)

for p in range(5000):
    x = x + 1
    y = y + 1
    plt.scatter(x, y)

    plt.pause(0.01)
    figure.clear()

# 이제 figure을 월드 사이즈에 고정시킬 차례임\



