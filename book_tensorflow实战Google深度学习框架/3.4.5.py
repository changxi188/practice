import tensorflow as tf
from numpy.random import RandomState


# parameters
learning_rate = 0.01

steps = 5000
dataset_size = 128
batch_size = 8

# dataset
rdm = RandomState(1)
x_data = rdm.rand(dataset_size, 2)
y_data = [[int(x1 + x2 < 1)] for (x1, x2) in x_data]
print(x_data)
print(y_data)
	
def build_train_graph():
	with tf.name_scope("data_loader"):
		x_ = tf.placeholder(tf.float32, shape = [None, 2], name = 'input')
		x_e_ = tf.expand_dims(x_, axis = 0)
		y_ = tf.placeholder(tf.float32, shape = [None, 1], name = 'output')
	
	with tf.name_scope("hidden_layer"):
		w1 = tf.Variable(tf.random_normal([2, 3], stddev = 1), name = 'w1')
		w2 = tf.Variable(tf.random_normal([3, 1], stddev = 1), name = 'w2')
	
		a = tf.matmul(x_e_, w1)
		y = tf.matmul(a, w2)
	
	with tf.name_scope("compute_loss"):
		cross_entropy = -tf.reduce_mean(y_ * tf.log(tf.clip_by_value(y, 1e-10, 1.0)))
	
	with tf.name_scope("train_op"):
		train_step = tf.train.AdamOptimizer(learning_rate).minimize(cross_entropy)

	return train_step, cross_entropy, x_, y_, w2, w1
		
	
def train():
	train_step, cross_entropy, x_, y_, w2, w1 = build_train_graph()
	init_op = tf.global_variables_initializer()	

	config = tf.ConfigProto()
	config.gpu_options.allow_growth = True
	with tf.Session(config = config) as sess:
		sess.run(init_op)
		for i in range(steps):
			start = (i * batch_size) % dataset_size;
			end = min(start + batch_size, dataset_size)
			sess.run(train_step, feed_dict = {x_ : x_data[start : end], y_ : y_data[start : end]})

			if i % 100 == 0:
				total_cross_entropy = sess.run(cross_entropy, feed_dict = {x_ : x_data, y_ : y_data})
				print("step : %d, loss : %f" % (i, total_cross_entropy))

		print(sess.run(w1))
		print(sess.run(w2))
		print(tf.trainable_variables())


train()
	
