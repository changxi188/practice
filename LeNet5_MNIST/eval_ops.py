import tensorflow as tf
import numpy as np
from dataloader import dataLoader
from net import leNet5
from config import *
from matplotlib import pyplot as plt

class EvalOp(object):
	def __init__(self, FLAGS):
		self.flags = FLAGS
	
	def build_eval_graph(self):
		with tf.name_scope("dataLoader"):
			self.x_, self.y_, global_step = dataLoader()

		with tf.name_scope("net"):
			self.y, end_points = leNet5(self.x_)

		with tf.name_scope("validate_op"):
			correct_prediction = tf.equal(tf.argmax(self.y, 1), tf.argmax(self.y_, 1))
			self.accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))
	
	def inference(self, mnist):
		self.build_eval_graph()
		saver = tf.train.Saver()
		config = tf.ConfigProto()
		config.gpu_options.allow_growth = True
		with tf.Session(config = config) as sess:
			model_path = tf.train.latest_checkpoint(self.flags.checkpoints_dir)
			print(11111111)
			print(model_path)
			saver.restore(sess, model_path)

			x = mnist.validation.images
			reshaped_x = np.reshape(x, (-1,
										FLAGS.image_size,
										FLAGS.image_size,
										FLAGS.num_channels))

			validate_feed = {self.x_ : reshaped_x, 
							 self.y_ : mnist.validation.labels}

			fetches = {"accuracy" : self.accuracy,
					   "pred_y"	  : self.y}

			result = sess.run(fetches, feed_dict = validate_feed)
			print("after %d steps, accuracy : %g" %(self.flags.training_steps, result["accuracy"]))
			for i in result["pred_y"][100]:
				print(i)

			image = reshaped_x[100]
			image.shape = 28, 28

			plt.imshow(image)
			plt.show()


