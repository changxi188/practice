import tensorflow as tf


with tf.variable_scope("layer1", reuse= True):
	weights = tf.Variable(tf.random_normal([1, 2], stddev = 0.1))

with tf.variable_scope("layer2", reuse = True):
	weights = tf.Variable(tf.random_normal([1, 2], stddev = 0.1))


for var in tf.model_variables():
	print(var)

for var in tf.all_variables():
	print(var)


print(weights)
