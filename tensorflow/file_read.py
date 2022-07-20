import tensorflow as tf
import numpy as np


pose_file = "./relative_pose_file.txt"

with open(pose_file) as f:
	relative_poses = f.readlines()



#print(relative_poses)


