## webrtc的peerconnection工程
[x] windows上转化成cmake构建完成，client需要release启动
[x] windows上直接调用camera并且渲染

### win
[x] windows上转化成cmake构建完成，client需要release启动
[x] windows上直接调用camera并且渲染
### ubuntu18.04
cmake可以跨平台构建peerconnection
环境安装
```shell
$ sudo apt install cmake gcc g++ libx11-dev pkg-config libgtk-3-dev -y
```


## 更新日志
    - 2020/08/11 wnidows上client release通过cmake编译完成
    - 2020/08/12 windows上直接调用camera并且渲染 完成
    - 2021/11/10 ubuntu18.04 完成cmake跨平台构建
    - 2021/11/11 屏幕捕获 基础功能
    - 2021/11/11 peerconnection 摄像头数据改为桌面共享
    - 2021/11/12 远程桌面线程安全问题解决，通过cotorn可以正常通信。(之前的线程 在远程端peer SetLocalDescription的时候会卡住)


屏幕共享： https://segmentfault.com/a/1190000040001557
屏幕共享设置到peerconnection: https://blog.csdn.net/weixin_29405665/article/details/107320004

服务器：https://github.com/konoui/kurento-coturn-docker.git
