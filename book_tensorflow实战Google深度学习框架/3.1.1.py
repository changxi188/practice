import os
import tensorflow as tf


g1 = tf.Graph()
with g1.as_default():
	v = tf.get_variable('v', shape = [1], initializer = tf.zeros_initializer())
	print(tf.global_variables())
print(11111111111111)
print(tf.global_variables())

g2 = tf.Graph()
with g2.as_default():
	v = tf.get_variable('v', shape = [1], initializer = tf.ones_initializer())
	print(tf.global_variables())
print(tf.global_variables())

with tf.Session(graph = g1) as sess:
	sess.run(tf.global_variables_initializer())
	#tf.initialize_all_variables().run()
	with tf.variable_scope("", reuse=True):
		print(sess.run(tf.get_variable("v")))
	print(tf.global_variables())
	

with tf.Session(graph = g2) as sess:
	sess.run(tf.global_variables_initializer())
	#tf.initialize_all_variables().run()
	with tf.variable_scope("", reuse=True):
		print(sess.run(tf.get_variable("v")))
	print(tf.global_variables())
	print(tf.trainable_variables())
