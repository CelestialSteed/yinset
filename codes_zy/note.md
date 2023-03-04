## 写在前面
//***为新增内容
## config
split 字符串分段
## vertex
函数后加const,只读函数，不改变类的成员
distance点间距离
insert加点，重复则不加
greater从大到小
## edge
&operator返回地址，用于运算符连用
## triangle
()
insert
erase
find
size
## model
deleteVertex
deleteEdge

## 问题
&operator有什么用

## 修边
长边取中点为新顶点
短边将端点合并至中点，或形成孔洞
### 前提条件
一条边最多在两个面内

## 关于Eigen的安装和使用
下载地址（3.3.8版本）： https://gitlab.com/libeigen/eigen/-/archive/3.3.8/eigen-3.3.8.zip 
下载后解压，mkdir build , cmake .. , make install, sudo cp -r /usr/local/include/eigen3 /usr/include, 
包含路径，task.json中加"-I'/usr/include/eigen3'"

这里我用的是eigen3/Eigen，原code用的是Eigen
