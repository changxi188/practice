import os
import tensorflow as tf
import cv2
from utils import *


def dataloader():
	#relative_pose_list = "./relative_pose_file.txt"
	#print(os.listdir("./color"))
	curr_path = os.getcwd()

	
	# create file lists for string_input_producer
	# color image file list
	color_image_list = os.listdir("./color")
	color_image_file_list = [os.path.join(curr_path,"color", x) for x in color_image_list]
	color_image_file_list.sort()

	# poses file list
	poses_list = os.listdir("./poses")
	poses_file_list = [os.path.join(curr_path, 'poses', x) for x in poses_list]
	poses_file_list.sort()

	# intrinsics file list
	intrinsics_list = os.listdir("./intrinsics")
	intrinsics_file_list = [os.path.join(curr_path, 'intrinsics', x) for x in intrinsics_list]
	intrinsics_file_list.sort()
	

	depth_file = os.path.join(curr_path, 'depth', '1.jpeg')
	depth_file_list = [depth_file]
	print(depth_file_list)

	color_paths_queue = tf.train.string_input_producer(
		color_image_file_list)
	depth_paths_queue = tf.train.string_input_producer(
		depth_file_list)
	poses_paths_queue = tf.train.string_input_producer(
		poses_file_list)
	intrinsics_paths_queue = tf.train.string_input_producer(
		intrinsics_file_list)

	# load color image
	img_reader = tf.WholeFileReader()
	_, image_contents = img_reader.read(color_paths_queue)
	color_image = tf.image.decode_jpeg(image_contents)

	img_reader2 = tf.WholeFileReader()
	_, depth_contents = img_reader2.read(depth_paths_queue)
	depth_image = tf.image.decode_image(depth_contents, 0)


	return depth_image, color_image
	

def main():
	"""
	with tf.name_scope("data_loader"):
		dataloader()
	"""	
	depth_image, color_image = dataloader()
	sv = tf.train.Supervisor()
	config = tf.ConfigProto()
	config.gpu_options.allow_growth = True
	with sv.managed_session(config=config) as sess:
		depth_image, color_image = sess.run([depth_image, color_image])
		cv2.imshow("bb", depth_image)
		cv2.imshow("aa", color_image)
		cv2.waitKey(0)


main()

