import tensorflow as tf
import numpy as np


global_step = tf.Variable(0, name='global_stp', trainable = False)
incre_global_step = tf.assign(global_step, global_step+1)

sess = tf.Session()

sess.run(tf.global_variables_initializer())
for i in range(10):
	print(sess.run(global_step))
	
	#global_step = 1 + global_step
	sess.run(incre_global_step)

