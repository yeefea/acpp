# High Performance Computing

## 绑核: `taskset` 命令

## 绑核: `sched_setaffinity`系统调用

```bash
time -p ./src/hpc/demo_affinity 0 0 1000000000  # same core, same thread
# real 5.07
# user 5.07
# sys 0.00
time -p ./src/hpc/demo_affinity 0 1 1000000000  # same core, different threads
# real 2.53
# user 5.04
# sys 0.00
time -p ./src/hpc/demo_affinity 0 2 1000000000  # different cores
# real 2.53
# user 5.05
# sys 0.00
```

## Isolate CPU

https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux/7/html/performance_tuning_guide/sect-red_hat_enterprise_linux-performance_tuning_guide-cpu-configuration_suggestions

3.3.6.2. Isolating CPUs

You can isolate one or more CPUs from the scheduler with the isolcpus boot parameter. This prevents the scheduler from scheduling any user-space threads on this CPU. Once a CPU is isolated, you must manually assign processes to the isolated CPU, either with the CPU affinity system calls or the numactl command.

隔离cpu对用户空间的进程有效，但是对内核的进程无效，所以被隔离的cpu并不是完全空闲的。（内核线程无法绑核）

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

## Hyper-Threading
Hyperthreading is an Intel processor technology that allows a physical CPU processor core to function as two logical cores, executing two independent threads simultaneously. Hyperthreading allows for better system throughput for certain workload types where parallel processing is beneficial. The default OKD configuration expects hyperthreading to be enabled by default.

For telecommunications applications, it is important to design your application infrastructure to minimize latency as much as possible. Hyperthreading can slow performance times and negatively affect throughput for compute intensive workloads that require low latency. Disabling hyperthreading ensures predictable performance and can decrease processing times for these workloads.


## References

- Low latency tunning, Hyper-Threading: https://docs.okd.io/4.11/scalability_and_performance/cnf-low-latency-tuning.html