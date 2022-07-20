import tensorflow as tf



config = tf.ConfigProto()
config.gpu_options.allow_growth = True

a = tf.get_variable("a", shape = (), initializer = tf.ones_initializer)


print(1111111111111111111111111111)
for variable in tf.global_variables():
	print(variable)
print(tf.global_variables())

with tf.Session(config = config) as sess:
	sess.run(tf.global_variables_initializer())
	print(1111111111111111111111111111)
	print(a)
	print(sess.run(a))
	
	

