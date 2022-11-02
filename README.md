这是一个清除工具：
（1）提供文件粉碎功能
（2）提供对浏览器的cookit和历史记录一键清除功能
（3）提供主机和系统的基本信息

粉碎规则：
	其中粉碎功能中提供粉碎规则，可以根据粉碎规则自定义粉碎文件。

	粉碎规则使用：安装路径下的rules文件夹下有conf文件夹，
	将规则文件加入到文件夹下即可。
	tab_label.conf文件可自由定义显示标题

粉碎文件规则的添加：
	粉碎文件分为两大块[info]显示信息和[path]粉碎路径规则
	
	其中[info]规则写法：
		[info]
		title:xxx
		info:xxx
		label:xxx
		content:xxx
	
	[info]的标题必须在tab_label.conf文件中有对应格式才会显示
	tab_label.conf格式:##title##info##label##content##
	标题格式没有循序要求，但必须存在才会显示


	其中[path]规则写法：
	[path]
	-f##/home/red/open/01.txt         //粉碎绝对路径文件
	-f##%HOME%open/01.txt             //%HOME%为env环境变量的值,进行路径替换
	-f##%HOME%open/work/cpp/*.txt     //匹配可变文件名
	-f##%HOME%open/*/cpp/*.txt        //匹配可变文件名,加可变路径

	-r##%HOME%open/*/cpp/*.txt        //递归子目录
	-r##%HOME%open/work/*/???.txt     //递归子目录,匹配三个字符的文件名

	-R##%HOME%open/work/cpp/          //粉碎绝对路径文件夹
	-R##%HOME%open/*/cpp/             //粉碎匹配成功的文件夹

	-A##/hhoe/red/work/cpp##^abc??.*  //启动参数##绝对路径##正则表达式

	语法解析:-f为操作参数,##为分隔符,后面的是粉碎条件
		条件开始固定也可以是可变的，-A为正则表达式
		不参与分析，需要手动指定绝对路径，第二个##后为正则表达式
	可变路径：路径存在通配符
	可变文件：文件名存在通配符	

	参数:
	-f:粉碎文件，不递归子目录
	-r:粉碎文件，进入子目录寻找符合条件的文件
	-R:粉碎文件夹
	-A:指定高级正则表达式通道

编译环境:
QT5.14.2 + GCC64 + kylin.x86-generic






