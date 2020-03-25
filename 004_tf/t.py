# -*-coding:utf-8 -*-
import tensorflow as tf
import os
 
# 使用Tensorflow Python API线下定义模型和训练
def tain_model():
    train_dir = os.path.join('./demo_model/', "demo")
    a = tf.compat.v1.placeholder(dtype=tf.int32, shape=None, name='a')
    b = tf.compat.v1.placeholder(dtype=tf.int32, shape=None, name='b')
    y = tf.Variable(tf.ones(shape=[1], dtype=tf.int32), dtype=tf.int32, name='y')
    res = tf.add(tf.multiply(a, b), y, name='res')
    with tf.Session() as sess:
        feed_dict = dict()
        feed_dict[a] = 2
        feed_dict[b] = 3
        fetch_list = [res]
        sess.run(tf.compat.v1.global_variables_initializer())
        saver = tf.compat.v1.train.Saver()
        # 训练和保存模型
        res = sess.run(feed_dict=feed_dict, fetches=fetch_list)
        saver.save(sess, train_dir)
        print("result: ", res[0])
 
#使用Tensorflow Python API 载入和运行模型
def load_model():
    with tf.Session() as sess:
        saver = tf.compat.v1.train.import_meta_graph('./demo_model/demo.meta')
        saver.restore(sess, tf.train.latest_checkpoint('./demo_model/'))
        # sess.run()
        graph = tf.compat.v1.get_default_graph()
        a = graph.get_tensor_by_name("a:0")
        b = graph.get_tensor_by_name("b:0")
        feed_dict = {a: 2, b: 3}
        op_to_restore = graph.get_tensor_by_name("res:0")
        print(sess.run(fetches=op_to_restore, feed_dict=feed_dict))
 
if __name__ == '__main__':
    #先训练模型
    tain_model()
    #导入训练好的模型测试结果
    load_model()
 
 