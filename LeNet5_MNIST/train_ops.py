import os
import sys
import cv2
import tensorflow as tf
import numpy as np
from net import leNet5
from dataloader import dataLoader
from config import *


class TrainOp(object):
	def __init__(self, FLAGS):
		self.flags = FLAGS
	
	
	def build_train_graph(self):
		with tf.name_scope("dataLoader"):
			self.x_, self.y_, self.global_step = dataLoader()

		with tf.name_scope("net"):
			y, end_points = leNet5(self.x_)

		with tf.name_scope("compute_loss"):
			cross_entropy = tf.nn.sparse_softmax_cross_entropy_with_logits(
								logits = y, labels = tf.argmax(self.y_, 1))
			self.loss = tf.reduce_mean(cross_entropy)


		with tf.name_scope("train_op"):
			self.learning_rate = tf.train.exponential_decay(self.flags.learning_rate_base,
							self.global_step, self.flags.steps_per_epoch,
							self.flags.learning_rate_decay)
			self.train_op = tf.train.GradientDescentOptimizer(self.learning_rate).\
								minimize(self.loss, global_step = self.global_step)

		#return train_op, loss, x_, y_, learning_rate, global_step
	
	def train(self):

		self.build_train_graph()

		saver = tf.train.Saver()

		config = tf.ConfigProto()
		config.gpu_options.allow_growth = True
		sv = tf.train.Supervisor(logdir = self.flags.checkpoints_dir,
								save_summaries_secs = 0,
								saver = None)

		with sv.managed_session(config = config) as sess:
			fetchs = {"loss" : self.loss,
					  "learning_rate" : self.learning_rate,
					  "global_step" : self.global_step}

			# loop to optimize 
			for i in range(self.flags.training_steps):
				xs, ys = mnist.train.next_batch(self.flags.batch_size)
				xs = np.reshape(xs, (self.flags.batch_size, 
									 self.flags.image_size, 
									 self.flags.image_size,
									 self.flags.num_channels))
				if i % 100 == 0:
					result = sess.run(fetchs, feed_dict = {self.x_ : xs, self.y_ : ys})
					print("steps : %d\tloss : %g\tlearning_rate : %g\tglobal_step : %d\t"\
						%(i, result["loss"], result["learning_rate"], result["global_step"]))
				sess.run(self.train_op, feed_dict = {self.x_ : xs, self.y_ : ys})

				if i % self.flags.steps_latest_freq == 0:
					saver.save(sess, os.path.join(self.flags.checkpoints_dir, 'model.latest'))
					print("step : %s, save checkpoint : %s" % \
							('latest', os.path.join(self.flags.checkpoints_dir, 'model.latest')))

				if i % self.flags.steps_per_epoch == 0:
					saver.save(sess, os.path.join(self.flags.checkpoints_dir, 'model'), global_step = i)
					print("step : %d, save checkpoint : %s" % \
							(i, os.path.join(self.flags.checkpoints_dir, 'model' + str(i))))


