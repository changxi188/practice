import tensorflow as tf
import numpy as np


def euler2mat(rz, ry, rx):
	B, _ = rz.get_shape().as_list()
	N = 1
	z = tf.clip_by_value(rz)
	y = tf.clip_by_value(ry)
	x = tf.clip_by_value(rx)

	# Expand to B * N * 1 * 1
	#z = 

def pose_vec2mat(pose):
	batch_size, _ = vec.get_shape().as_list()
	translation = tf.slice(vec, [0, 0], [-1, 3])
	rx = tf.slice(vec, [0, 3], [-1, 1])
	ry = tf.slice(vec, [0, 4], [-1, 1])
	rz = tf.slice(vec, [0, 5], [-1, 1])
	rot_mat = euler2mat(rz, ry, rx)




#img : [B, H, W, 3]
#depth : [B, H, W]
#pose : [B, 6] in order of tx, ty, tz, rx, ry, rz
def proj_inverse_map(img, depth, pose, intrinsics):
	batch, height, width, _ = img.get_shape().as_list()
	pose = pose_vec2mat(pose)

