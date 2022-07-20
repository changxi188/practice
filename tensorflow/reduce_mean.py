import tensorflow as tf

x = [[1, 2, 3], [1, 2, 3]]
y = [[4, 5, 6], [4, 5, 6]]
z = [[7, 8, 9], [7, 8, 9]]

x_t = tf.stack([x, y, z], axis = 0)
x_t_e  = tf.expand_dims(x_t, axis = -1)

mean_0 = tf.reduce_mean(x_t, axis = 0)
mean_1 = tf.reduce_mean(mean_0, axis = 0)
mean_0_1 = tf.reduce_mean(x_t, axis = [0, 1])

mean_x_t_e = tf.reduce_mean(x_t_e, axis = -1)


with tf.Session() as sess:
	print("00000000000000000000000000000000000000000000")
	
	print(x_t)
	print(sess.run(x_t))
	print(sess.run(mean_x_t_e))
	#print(sess.run(mean_0))
	print(sess.run(mean_1))
	print(sess.run(mean_0_1))


