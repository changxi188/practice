import tensorflow as tf
from dataloader import dataLoader
from net import net


class EvalOp(object):
	def __init__(self, FLAGS):
		self.flags = FLAGS
	
	def build_eval_graph(self):
		with tf.name_scope("dataLoader"):
			self.x_, self.y_, global_step = dataLoader()

		with tf.name_scope("net"):
			self.y, weights1, weights2 = net(self.x_)

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
			saver.restore(sess, model_path)

			validate_feed = {self.x_ : mnist.validation.images, 
							 self.y_ : mnist.validation.labels}

			fetches = {"accuracy" : self.accuracy,
					   "pred_y"	  : self.y}

			result = sess.run(fetches, feed_dict = validate_feed)
			print("after %d steps, accuracy : %g" %(self.flags.training_steps, result["accuracy"]))


