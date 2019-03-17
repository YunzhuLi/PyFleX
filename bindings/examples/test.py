import numpy as np
import pyflex
import time
import torch


pyflex.init()

scene_params = np.array([])
pyflex.set_scene(11, scene_params, 0)

print("Scene Upper:", pyflex.get_scene_upper())
print("Scene Lower:", pyflex.get_scene_lower())

for i in range(150):
    pyflex.step()

    if i == 0:
        time.sleep(2)

pyflex.clean()
