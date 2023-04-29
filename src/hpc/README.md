# High Performance Computing

## `sched_setaffinity`


## Isolate CPU

隔离cpu对用户空间的进程有效，但是对内核的进程无效，所以被隔离的cpu并不是完全空闲的。

1. 在/etc/default/grub中的下面一行添加最后的isolcpus参数
GRUB_CMDLINE_LINUX_DEFAULT="quiet splash isolcpus=1,3"（这里表示1和3两个cpu被隔离,cpu序号从0开始）
也可以添加GRUB_CMDLINE_LINUX="isolcpus=1,3"

2. 更新/boot/grub/grub.cfg文件
```bash
sudo update-grub
```
如果报错，需要安装
```bash
sudo apt-get update
sudo apt-get install --reinstall grub
```
执行完update-grub之后，看一下/boot/grub/grub.cfg的时间戳，如果更新了说明成功了。我用这个命令没能成功更新。没成功的话试试
```bash
sudo grub-mkconfig -o /boot/grub/grub.cfg
```

3. 重启系统