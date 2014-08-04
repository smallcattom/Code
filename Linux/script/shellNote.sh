#!/bin/bash 
fname()
{
	echo 'hello'
}

reference()
{
#反引用
	cmd_output=$(ls | grep *.txt)
	echo $cmd_output
}

sonShell()
{
#用括号生成一个子shell
	(cd repository/Linux;ls)
}

Read()
{
   #以不按回车方式读取n个字符
   read -n 2 var
   #以不输出回车方式打印
   echo -n $var
   #不回显方式读取密码
   read -s var
   echo $var
   #显示提示信息
   read -p "Enter input:" var
   #在特定时限内读取输入
   read -t 3
   #通过定界符号结束输入
   read -d ':' var
   echo $var
}
read data
for x in $data;
do
echo $x
sleep 1
done
