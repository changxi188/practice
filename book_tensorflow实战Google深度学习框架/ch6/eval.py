import tensorflow as tf
from config import *
from eval_ops import EvalOp

def main():
	eval_op = EvalOp(FLAGS)
	eval_op.inference(mnist)

main()
	
