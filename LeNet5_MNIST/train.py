import os
import sys
import cv2
import tensorflow as tf
from config import *
from train_ops import TrainOp


def main():
	train_op = TrainOp(FLAGS)
	train_op.train()

main()
#if __name__ == '__main__':
#	tf.app.run()



