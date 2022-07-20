import tensorflow as tf
from config import *

def net(inputs):
	with tf.variable_scope('layer1', reuse = FLAGS.reuse):
		weights1 = tf.Variable(tf.random_normal([FLAGS.input_node, FLAGS.layers1_node], stddev = 0.1))
		biases1 = tf.Variable(tf.constant(0.1, shape=[FLAGS.layers1_node]))
		layer1 = tf.nn.relu(tf.matmul(inputs, weights1) + biases1)
	with tf.variable_scope('layer2', reuse = FLAGS.reuse):
		weights2 = tf.Variable(tf.random_normal([FLAGS.layers1_node, FLAGS.output_node], stddev = 0.1))
		biases2 = tf.Variable(tf.constant(0.1, shape=[FLAGS.output_node]))
		layer2 = tf.matmul(layer1, weights2) + biases2
	return layer2, weights1, weights2

