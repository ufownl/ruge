简介

一个基于DX9和FMOD，采用COM组件方式架构的2D游戏引擎。整个RUGE引擎由六个COM组件（程序框架、渲染系统、音频系统、输入系统、随机数发生器、计时器）和一个渲染辅助类库（包括精灵、精灵动画、粒子系统、场景管理器、GUI系统等）组成。由于这些组件及类库对大量繁杂底层操作的封装，使得2D游戏的开发变得相当的容易。

RUGE Project Home：http://code.google.com/p/ruge/

下载

当前版本

v2.7.6.1：[ftp://ufownl.gicp.net/RUGE/v2.7.6.1/RUGE.rar](ftp://ufownl.gicp.net/RUGE/v2.7.6.1/RUGE.rar) （修改了场景切换机制）

历史版本

v2.7.5.1：[ftp://ufownl.gicp.net/RUGE/v2.7.5.1/RUGE.rar](ftp://ufownl.gicp.net/RUGE/v2.7.5.1/RUGE.rar) （修正了场景切换过程中的一个BUG）

v2.7.4.1：[ftp://ufownl.gicp.net/RUGE/v2.7.4.1/RUGE.rar](ftp://ufownl.gicp.net/RUGE/v2.7.4.1/RUGE.rar) （改进GUI中MouseMove的处理机制）

v2.7.3.1：[ftp://ufownl.gicp.net/RUGE/v2.7.3.1/RUGE.rar](ftp://ufownl.gicp.net/RUGE/v2.7.3.1/RUGE.rar) （修正GUI处理机制中关于MouseOver判定的一个BUG）

v2.7.2.1：[ftp://ufownl.gicp.net/RUGE/v2.7.2.1/RUGE.rar](ftp://ufownl.gicp.net/RUGE/v2.7.2.1/RUGE.rar) （改进了GUI处理机制）

v2.7.1.1：[ftp://ufownl.gicp.net/RUGE/v2.7.1.1/RUGE.rar](ftp://ufownl.gicp.net/RUGE/v2.7.1.1/RUGE.rar) （添加了ini文件API）

v2.6.2.1：[ftp://ufownl.gicp.net/RUGE/v2.6.2.1/RUGE.rar](ftp://ufownl.gicp.net/RUGE/v2.6.2.1/RUGE.rar) （隐藏了一些内部常量）

v2.6.1.1：[ftp://ufownl.gicp.net/RUGE/v2.6.1.1/RUGE.rar](ftp://ufownl.gicp.net/RUGE/v2.6.1.1/RUGE.rar) （修正纹理载入的一个BUG）

v2.6.0.1：[ftp://ufownl.gicp.net/RUGE/v2.6.0.1/RUGE.rar](ftp://ufownl.gicp.net/RUGE/v2.6.0.1/RUGE.rar) （顶点结构变更，解决了纹理坐标的半像素定位问题以及线性过滤时的纹理模糊问题）

v2.5.0.1：[ftp://ufownl.gicp.net/RUGE/v2.5.0.1/RUGE.rar](ftp://ufownl.gicp.net/RUGE/v2.5.0.1/RUGE.rar) （开始使用RUGE命名空间，添加了四个常用GUI控件，实现了自己的粒子系统编辑器）

v2.4.3.1：[ftp://ufownl.gicp.net/RUGE/v2.4.3.1/RUGE.rar](ftp://ufownl.gicp.net/RUGE/v2.4.3.1/RUGE.rar) （改进场景管理器）

v2.4.2.1：[ftp://ufownl.gicp.net/RUGE/v2.4.2.1/RUGE.rar](ftp://ufownl.gicp.net/RUGE/v2.4.2.1/RUGE.rar) （修正输入系统GetKey及GetChar函数的BUG）

v2.4.1.1：[ftp://ufownl.gicp.net/RUGE/v2.4.1.1/RUGE.rar](ftp://ufownl.gicp.net/RUGE/v2.4.1.1/RUGE.rar) （优化字体渲染效果）

v2.4.0.1：[ftp://ufownl.gicp.net/RUGE/v2.4.0.1/RUGE.rar](ftp://ufownl.gicp.net/RUGE/v2.4.0.1/RUGE.rar) （添加GUI系统）

v2.3.1.1：[ftp://ufownl.gicp.net/RUGE/v2.3.1.1/RUGE.rar](ftp://ufownl.gicp.net/RUGE/v2.3.1.1/RUGE.rar) （改善计时器精度）

v2.3.0.1：[ftp://ufownl.gicp.net/RUGE/v2.3.0.1/RUGE.rar](ftp://ufownl.gicp.net/RUGE/v2.3.0.1/RUGE.rar) （优化框架结构，添加动态设置引擎状态功能）

v2.2.8.1：[ftp://ufownl.gicp.net/RUGE/v2.2.8.1/RUGE.rar](ftp://ufownl.gicp.net/RUGE/v2.2.8.1/RUGE.rar) （添加场景管理器，修正Timer.h中的一处笔误）

v2.2.6.1：[ftp://ufownl.gicp.net/RUGE/v2.2.6.1/RUGE.rar](ftp://ufownl.gicp.net/RUGE/v2.2.6.1/RUGE.rar) （修改了CDistortionMesh::Render函数的BUG）

v2.2.5.1：[ftp://ufownl.gicp.net/RUGE/v2.2.5.1/RUGE.rar](ftp://ufownl.gicp.net/RUGE/v2.2.5.1/RUGE.rar) （修改了CColor赋值运算中的BUG）

v2.2.4.1：[ftp://ufownl.gicp.net/RUGE/v2.2.4.1/RUGE.rar](ftp://ufownl.gicp.net/RUGE/v2.2.4.1/RUGE.rar) （改进FOCUS判断机制）

v2.2.3.1：[ftp://ufownl.gicp.net/RUGE/v2.2.3.1/RUGE.rar](ftp://ufownl.gicp.net/RUGE/v2.2.3.1/RUGE.rar) （改写了主循环内部运行代码）

v2.2.2.1：[ftp://ufownl.gicp.net/RUGE/v2.2.2.1/RUGE.rar](ftp://ufownl.gicp.net/RUGE/v2.2.2.1/RUGE.rar) （改进了主循环的内部运行机制）

v2.2.1.1：[ftp://ufownl.gicp.net/RUGE/v2.2.1.1/RUGE.rar](ftp://ufownl.gicp.net/RUGE/v2.2.1.1/RUGE.rar) （修正了CDistortionMesh中的一处笔误）

v2.2.0.1：[ftp://ufownl.gicp.net/RUGE/v2.2.0.1/RUGE.rar](ftp://ufownl.gicp.net/RUGE/v2.2.0.1/RUGE.rar) （Released under GNU LGPL）

v2.1.0.1：[ftp://ufownl.gicp.net/RUGE/v2.1.0.1/RUGE.rar](ftp://ufownl.gicp.net/RUGE/v2.1.0.1/RUGE.rar) （增加渲染到纹理功能）

v2.0.2.1：[ftp://ufownl.gicp.net/RUGE/v2.0.2.1/RUGE.rar](ftp://ufownl.gicp.net/RUGE/v2.0.2.1/RUGE.rar)

v2.0.0.1：[ftp://ufownl.gicp.net/RUGE/v2.0.0.1/RUGE.rar](ftp://ufownl.gicp.net/RUGE/v2.0.0.1/RUGE.rar)