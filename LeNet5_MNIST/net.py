import tensorflow as tf
import tensorflow.contrib.slim as slim
from tensorflow.contrib.layers.python.layers import utils
from config import *

def leNet5(inputs, is_training = True):
	#tf.reshape(inputs, [1, 28, 28, 1])
	H = inputs.get_shape()[1].value 
	W = inputs.get_shape()[2].value
	with tf.variable_scope('leNet5') as sc:
		end_points_collection = sc.original_name_scope + '_end_points'
		with slim.arg_scope([slim.conv2d], 
							normalizer_fn = None,
							weights_regularizer = slim.l2_regularizer(0.05),
							activation_fn = tf.nn.relu,
							padding = 'SAME',
							outputs_collections = end_points_collection):
			cnv1 = slim.conv2d(inputs, 32, [5, 5], stride = 1,  scope = 'cnv1')
			print(cnv1)
			pool1 = slim.max_pool2d(cnv1, [2, 2], stride = 2, padding = 'same', scope = 'pool1') 
			print(pool1)
			cnv2 = slim.conv2d(pool1, 64, [5, 5], stride = 1, scope = 'cnv2')
			print(cnv2)
			pool2 = slim.max_pool2d(cnv2, [2, 2], stride = 2, padding = 'same', scope = 'pool2')
			print(pool2)
			flatten = slim.flatten(pool2, scope='flatten')
			print(flatten)
			fc = slim.fully_connected(flatten, FLAGS.fc_size, activation_fn = tf.nn.relu, scope = 'fc')
			print(fc)
			if is_training:
				fc = slim.dropout(fc, keep_prob = 0.5, is_training = is_training, scope = 'fc_dropout')
			print(fc)

			output = slim.fully_connected(fc, FLAGS.num_labels, activation_fn = None, normalizer_fn = None, scope = 'fco')
			print(output)
			
			end_points = utils.convert_collection_to_dict(end_points_collection)

			return output, end_points


