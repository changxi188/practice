import tensorflow as tf
from config import *


def dataLoader():
	x_ = tf.placeholder(tf.float32, [None, FLAGS.input_node], name = 'x_input')
	y_ = tf.placeholder(tf.float32, [None, FLAGS.output_node], name = 'y_input')
	global_step = tf.Variable(0, trainable=False)
	return x_, y_, global_step
	
