import tensorflow as tf
from config import *


def dataLoader():
	#x_ = tf.placeholder(tf.float32, [None, FLAGS.input_node], name = 'x_input')
	x_ = tf.placeholder(tf.float32, [None, FLAGS.image_size, FLAGS.image_size, FLAGS.num_channels], name = 'x_input')
	y_ = tf.placeholder(tf.float32, [None, FLAGS.num_labels], name = 'y_input')
	global_step = tf.Variable(0, trainable=False)
	return x_, y_, global_step
	
#use for debug
#dataLoader()

