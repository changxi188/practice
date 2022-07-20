import tensorflow as tf
import cv2
import matplotlib.pyplot as plt
from PIL import Image


def read_image():
	img_raw = tf.read_file("./1.png")
	img = tf.image.decode_png(img_raw)
	img_rs = tf.image.resize(img, [3, 5])
	with tf.Session() as sess:
		image = sess.run(img)
		image_rs = sess.run(img_rs)
		#cv2.imshow('img_raw', image)
		#cv2.imshow('img_rs', image_rs)
		#plt.imshow(image)
		#plt.show()
		#plt.imshow(image_rs)
		#plt.show()

		#cv2.waitKey(0)
		print(image)
		print(img)
		print(img_rs)
		print(image_rs)
	

read_image()
