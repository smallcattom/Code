#!/bin/bash
#从一个微博看来的，开始觉得好神奇啊。。。。。而且还伴随一些函数不懂
#原理其实很简单的，数字是几就开一个程出来让它睡几秒，睡好了输出，有点计数排序的感觉-_-这里就当学wait吧没有实际用处的排序，时间复杂度跟最大值有关系
#而且不能是负数,对于需要排序的数组（就是本来乱序）用时一定大于1秒，这对计算机而言就太慢了
fun()
{
	sleep $1
	echo $1
}
while [ -n "$1" ]
do
fun $1 &
shift
done
wait

