import tensorflow as tf

from tensorflow.examples.tutorials.mnist import input_data

mnist = input_data.read_data_sets("/home/mr/Downloads/MNIST/", one_hot = True)

flags = tf.app.flags
flags.DEFINE_string("checkpoints_dir", "./checkpoints", "the file path of checkpoins")
flags.DEFINE_float("learning_rate_base", 0.8, "base learning rate")
flags.DEFINE_float("learning_rate_decay", 0.99, "learing rate decay percent")
flags.DEFINE_float("regularization_rate", 0.0001, "regularization_rate")
flags.DEFINE_float("moving_average_decay", 0.99, "....")
flags.DEFINE_integer("input_node", 784, "number input node")
flags.DEFINE_integer("output_node", 10, "number output node")
flags.DEFINE_integer("layers1_node", 500, "number layer1 node")
flags.DEFINE_integer("batch_size", 100, "batch size")
flags.DEFINE_integer("training_steps", 30000, "the maxmum training step")
flags.DEFINE_integer("steps_latest_freq", 5000, "the freqence of save latest model")
flags.DEFINE_integer("steps_per_epoch", int(mnist.train.num_examples/flags.FLAGS.batch_size), "the freqence to save model")
flags.DEFINE_boolean("avg_class", False, "use moving average ?")
flags.DEFINE_boolean("reuse", True, "reuse variable in tf.variable_scope ?")

FLAGS = flags.FLAGS

