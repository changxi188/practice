import tensorflow as tf

a = tf.constant([1.0, 2.0], name='a')

b = tf.constant([2.0, 3.], name='b')

b2 = tf.constant([3., 4.], name = 'b')

result = a+b

print(a)
print(b)
print(b2)
print(result)
