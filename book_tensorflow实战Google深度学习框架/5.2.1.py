import tensorflow as tf
import os
import sys
import cv2
from tensorflow.examples.tutorials.mnist import input_data

# parameters
mnist = input_data.read_data_sets("/home/mr/Downloads/MNIST/", one_hot=True)
input_node = 784
output_node = 10

layers1_node = 500
batch_size = 100

learning_rate_base = 0.8
learning_rate_decay = 0.99

regularization_rate = 0.0001
training_steps = 30000
moving_average_decay = 0.99

avg_class = False

reuse = True

checkpoints_dir = "./checkpoints"
steps_latest_freq = 5000

steps_per_epoch = mnist.train.num_examples/batch_size

# 创建占位符用以读取数据
def data_loader():
	x_ = tf.placeholder(tf.float32, [None, input_node], name = 'x_input')
	y_ = tf.placeholder(tf.float32, [None, output_node], name = 'y_input')
	global_step = tf.Variable(0, trainable=False)
	return x_, y_, global_step

# 共用的网络模块
def net(inputs):
	with tf.variable_scope('layer1', reuse = reuse):
		weights1 = tf.Variable(tf.random_normal([input_node, layers1_node], stddev = 0.1))
		biases1 = tf.Variable(tf.constant(0.1, shape=[layers1_node]))
		layer1 = tf.nn.relu(tf.matmul(inputs, weights1) + biases1)
	with tf.variable_scope('layer2', reuse = reuse):
		weights2 = tf.Variable(tf.random_normal([layers1_node, output_node], stddev = 0.1))
		biases2 = tf.Variable(tf.constant(0.1, shape=[output_node]))
		layer2 = tf.matmul(layer1, weights2) + biases2
	return layer2, weights1, weights2
	
# 创建训练网络的计算图
def build_train_graph(avg_class, decay_steps):
	
	with tf.name_scope("data_loader"):
		x_, y_, global_step = data_loader()

	with tf.name_scope("net"):
		y, weights1, weights2 = net(x_)

	with tf.name_scope("compute_loss"):
		cross_entropy = tf.nn.sparse_softmax_cross_entropy_with_logits(
						logits = y, labels = tf.argmax(y_, 1))
		cross_entropy_mean = tf.reduce_mean(cross_entropy)

		regularizer = tf.contrib.layers.l2_regularizer(regularization_rate)
		regularization = regularizer(weights1) + regularizer(weights2)
		loss = cross_entropy_mean + regularization

	
	with tf.name_scope("train_op"):
		learning_rate = tf.train.exponential_decay(learning_rate_base,
						global_step, decay_steps,
						learning_rate_decay)

		train_op = tf.train.GradientDescentOptimizer(learning_rate).minimize(loss, global_step=global_step) #这里每运行一次学习率都加1
	
	return train_op, loss, x_, y_, learning_rate, global_step
	
# 创建验证网络的计算图
def build_eval_graph(avg_class):

	with tf.name_scope("data_loader"):
		x_, y_, global_step = data_loader()
	
	with tf.name_scope("net"):
		y, weights1, weights2 = net(x_)
	
	with tf.name_scope("validate_op"):
		correct_prediction = tf.equal(tf.argmax(y, 1), tf.argmax(y_, 1))
		accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))
	
	return accuracy, y, x_, y_, global_step
	

# 训练网络模型
def train(mnist):

	train_op, loss, x_, y_, learning_rate, global_step = build_train_graph(avg_class, steps_per_epoch)

	#saver = tf.train.Saver([var for var in tf.model_variables()] + [global_step])
	saver = tf.train.Saver()
	for var in tf.model_variables():
		print(var)
	for var in tf.all_variables():
		print(var)

	config = tf.ConfigProto()
	config.gpu_options.allow_growth = True
	sv = tf.train.Supervisor(logdir = checkpoints_dir,
							 save_summaries_secs = 0,
							 saver = None)
	with sv.managed_session(config=config) as sess:
		fetchs = {"loss" : loss,
				  "learning_rate" : learning_rate,
				  "global_step" : global_step}

		for i in range(training_steps):	
			xs, ys = mnist.train.next_batch(batch_size)
			if i % 100 == 0:
				result = sess.run(fetchs, feed_dict = {x_ : xs, y_ : ys})
				print("steps : %d, loss : %g, learning_rate : %g, global_step : %d" %(i, result["loss"], result["learning_rate"], result["global_step"]))

			sess.run(train_op, feed_dict = {x_ : xs, y_ : ys})
			
			if i % steps_latest_freq == 0:
				save(sess, saver, checkpoints_dir, 'latest')

			if i % steps_per_epoch == 0:
				save(sess, saver, checkpoints_dir, i)

# 前向传播部分
def inference(mnist):
	accuracy, y, x_, y_, global_step = build_eval_graph(avg_class)

	saver = tf.train.Saver()
	config = tf.ConfigProto()
	config.gpu_options.allow_growth = True
	with tf.Session(config = config) as sess:
		print(222222222222222222222222222222222222222222)
		
		model_path = tf.train.latest_checkpoint(checkpoints_dir)
		saver.restore(sess, model_path)

		validate_feed = {x_ : mnist.validation.images,
						 y_ : mnist.validation.labels}

		fetchs = {"accuracy" : accuracy,
				  "pred_y"   : y}

		result = sess.run(fetchs, feed_dict = validate_feed)
		print("after %d steps, accuracy : %g" %(training_steps, result["accuracy"]))
		print(result['pred_y'][0].shape)
		y_truth = mnist.validation.labels
		x_truth = mnist.validation.images
		for a in result['pred_y'][0]:
			print(a)

	#return result


def save(sess, saver, checkpoint_dirs, step):
	model_name = 'model'
	if step == 'latest':
		saver.save(sess, os.path.join(checkpoint_dirs, model_name + '.latest'))
		#saver.export_meta_graph(os.path.join(checkpoint_dirs, model_name + '.latest' + '.json'))
		print("steps : %s, save checkpint : %s" %(step, str(os.path.join(checkpoints_dir + 'model.latest'))))
	else:
		saver.save(sess, os.path.join(checkpoint_dirs, model_name), global_step=step)
		print("steps : %d, save checkpint : %s" %(step, str(os.path.join(checkpoints_dir, model_name + str(step)))))

def train_main(arg=None):
	train(mnist)

def eval_main(arg=None):
	inference(mnist)

#train_main()
eval_main()	
