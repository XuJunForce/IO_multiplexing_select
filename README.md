### 多路复用-select


# 创建与初始化
fd_set rdset;
fd_set rdtemp;
FD_ZERO(&rdset);

储存原始列表--rdset
储存读写更改列表--rdtemp



maxfd = cfd > maxfd ? cfd : maxfd;
每次添加新的通信符之后,需要判断当前的最大通讯符

# select
int num = select(maxfd+1, &rdtemp, NULL, NULL, NULL);
参数1.最大通讯符+1
参数2.检测的可读文件的列表
参数3.检测的可写文件的列表
参数4.检测的异常文件的列表
参数5.一般为NULL
返回值:符合可读或可写的文件个数


# FD_ISSET(int i ,&fd_set)
在fd_set中,判断i是否为1

# FD_SET(fd, &rdset);
将新的文件通讯符添加到rdset中




