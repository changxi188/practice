import os
import tensorflow as tf
import numpy as np
import cv2


def read_image():
	data_path = os.getcwd()
	depth_image = tf.read_file(data_path + "/depth/1.pgm")
	#depth_image = tf.read_file(data_path + "/color/1.png")
	depth_image = tf.image.decode_jpeg(depth_image)
	with tf.Session() as sess:
		image = sess.run(depth_image)
		cv2.imshow("aaa", image)
		cv2.waitKey(0)


read_image()
