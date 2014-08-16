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
	(cd repository/Linux;ls)#divide by ';'
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
IFSofUse_and_loop()
{
	read data
	for x in $data;
	do
	echo $x
	sleep 1
	done

    line="root:x:0:0:root:/root:/bin/bash"
    oldIFS=$IFS
    IFS=":"
    count=0
    for item in $line;
    do
    [ $count -eq 0 ] && user=$item
    [ $count -eq 6 ] && shell=$item
    let count++
    done;
    IFS=$oldIFS
    echo $user\'s shell is $shell
	x=0
	while [ $x -lt 10 ]
	do
	echo $x
	let x++
	x=$(($x+1))
	done
    until [ $x -lt 10 ]
	do
	echo $x
	let x--
	done
#(())内用于支持C语言的语法
    for((i = 0;i < 10;i ++))
    {
    	echo -n $i
    }

	x=1
	if((x < 2))
	then
		echo $x
	fi
}
getDir()
{
#获取当前目录下文件夹且不包含当前目录和父目录
	ls -l | grep ^d | awk '{print $9}' | grep ^[^.]
#打印第2行第一列
	sed -n "2, 1p"
}
Find()
{
	find . \( -name "*.sh" -o -name "*.py" \) -print
	find . -regex ".*\(\.py\|\.sh\)$" #运用正则表达式查找
	find . ! -name "*.txt"  #查找不符合要求的
	find . -maxdepth 1 -type l #搜索最大深度为1,搜索类型是符号链接
	#atime 用户最后一次访问时间
	#mtime 修改时间
	#ctime 变化时间，指权限所有权
	find . -type f atime -7 #-是小于的意思
}

