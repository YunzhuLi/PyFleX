import numpy as np
import pyflex
import time
import torch


def rand_float(lo, hi):
    return np.random.rand() * (hi - lo) + lo


pyflex.init()

x = rand_float(0.15, 0.349)
y = rand_float(0.15, 0.349)
z = rand_float(0.15, 0.299)
px = rand_float(0.45, 1.2 - x)
pz = rand_float(0.02, 0.4 - z)

# x range [3, 7] --> [0.15, 0.399]
# y range [3, 7] --> [0.15, 0.399]
# z range [3, 6] --> [0.15, 0.349]
# x = 0.349
# y = 0.349
# z = 0.299
# px = 1.2 - x
# pz = 0.4 - z

scene_params = np.array([x, y, z, px, pz])
pyflex.set_scene(7, scene_params, 0)

print("Scene Upper:", pyflex.get_scene_upper())
print("Scene Lower:", pyflex.get_scene_lower())

for i in range(150):
    pyflex.step()
    time.sleep(0.1)

pyflex.clean()
