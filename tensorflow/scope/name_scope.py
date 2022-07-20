import tensorflow as tf

import numpy as np

with tf.name_scope('test1') as sc:
	v1 = tf.compat.v1.get_variable(name = 'v1', shape = [1], dtype = tf.float32)
	v11 = tf.Variable([0], name='v1', shape = [1], dtype = tf.float32)
	v111  = tf.Variable([0], name='v1', shape = [1], dtype = tf.float32)
	#test1_sc = sc.original_name_scope 
	#a = tf.constant



with tf.name_scope('test2'):
	#v1111 = tf.compat.v1.get_variable(name='v1', shape = [1], dtype = tf.float32)
	pass


with tf.variable_scope('test3') as sc:
	v3 = tf.get_variable(name = 'v3', shape = [1], dtype = tf.float32)
	v33 = tf.Variable([0], name = 'v3', shape = [1], dtype =  tf.float32)
	end_points_collection = sc.original_name_scope + '_end_point'

with tf.compat.v1.Session() as sess:
	sess.run(tf.compat.v1.global_variables_initializer())
	"""
	print("following information is v1")
	print("sess.run(v1) : ", sess.run(v1))
	print("v1 : ", v1)
	print("v1.name :", v1.name)


	print("following information is v11")
	print("sess.run(v11) : ", sess.run(v11))
	print("v11 : ", v11)
	print("v11.name : ", v11.name)


	print("v111.name :", v111.name)

	print("v1111.name : ", v1111.name)
	"""

	"""
	print("v3 : ", v3)
	print("v3.name : ", v3.name)
	print( "v33 : ", v33)
	print("v33.name : ", v33.name)
	sess.run(v3.initializer)
	print(sess.run(v3))
	"""
	#print(test1_sc)
	#print(end_points_collection)

	a
	print(a.name)

