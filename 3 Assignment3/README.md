# 作业三：被动网络测量

## 登录虚拟机

之前配置完成的虚拟机已经能符合本作业的要求，无需另外调整。通过 ```vagrant ssh``` 登陆虚拟机。

## 启动 Jupyter Notebook 服务

在虚拟机中，执行 ```sudo jupyter notebook &``` 命令。这将在后台启动新的 Jupyter Notebook 服务器。即使是这样在后台运行，它有时也会将信息消息打印到终端。要关闭 Notebook，运行 ```fg```，然后按 Control-C 两次。

当 Notebook 在运行时，在你的主机上打开浏览器，在地址栏中输入' 127.0.0.1:8888 '。这将能够带你去 Jupyter Notebook 的文件选择窗口。Juypter Notebook 是运行在虚拟机的8888端口上的，但是你可以通过你的主机访问它，因为我们已经做了虚拟机和主机之间的端口转发。在文件选择窗口中，进入作业三的目录，然后打开 Assignment3_Notebook.ipynb 。这将打开一个有详细说明的 Notebook，你将在这个Notebook 的指导下完成剩下的作业。

> 关于 Jupyter Notebook：双击以编辑代码块，选中代码块并 Shift + Enter 运行代码块。

## 一些提示

* 请在Assignment3_Notebook.ipynb的顶部填写你的姓名和学号
* 每次从浏览器关闭 Jupyter Notebook 之前请确保对文件的改动已经保存。(右上角 Save and Checkpoint 图标按钮)
* 对于作业的 Part C 分析部分，你可以直接在 Notebook 上作答，之后可能需要你将相关的题目答案提交到其他网站中去，请参照老师的具体要求
* Assignment3_Notebook,ipynb 描述了作业三的基本要求，但作业三事实上是一个开放问题。如果你认为文件中的实验对于回答 Part C 中的问题来说实验尚不充足，或者你出于好奇想作进一步的探究，你可以在原实验的基础上任意修改实验设置，并体现在 Assignment3_Notebook.ipynb 文件中。