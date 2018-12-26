#理解
一直账户就是一个对象。用状态来描述对象
智能合约：账户提供其他对象（人，其他账户）来改变自己状态的方法（依附于对象）。所以智能合约是私有的
账户状态：通过这个账户能够得到的数据

#注意点
1.一个账户只能部署一个合约
2.

#执行合约入口

1.init:部署合约的时候执行一次，用于初始化数据
2.apply(re,code,action)// re:执行人，code 合约（合约的所有者）， action：合约一个方法（条款）

获取被调用合约的参数
```c++
buffer = max_stack_buffer_size < size ? malloc(size) : alloca(size);
read_action_data( buffer, size );
//参数列表
auto args = unpackstd::tuple<std::decay_t<account_name>>( (char*)buffer, size );
print(" ||buffer=");
print(name{std::get<0>(args)});
```

# 数据持久化

# ECC算法

由于ECC算法数学原理部分看不懂，有空研究。但是还是有黑箱的理解方式。

参考：https://www.freebuf.com/articles/database/155912.html

描述椭圆曲线 ，常用到六个参量：T=(p,a,b,n,x,y)

1. **（p ，a ，b）用来确定一条椭圆曲线**，p为素数域内点的个数，a和b是其内的两个大数；

2.  **x,y为G基点**的坐标，也是两个大数；

3. **$n$为点G基点的阶**；

   ##### 加密过程：

   1、A机器选定一条椭圆曲线 Ep(a,b) 并取椭圆曲线上一点，作为基点G。

   2、A机器选择一个私有密钥k，并生成公开密钥 <u>**K=kG**</u>。

   3、A机器将 Ep(a,b) 和点K，G传给用户B。

   4、B机器接到信息后 ，将待传输的明文编码到Ep(a,b)上一点M（编码方法很多，这里不作讨论），并产生一个随机整数r。

   5、B机器计算

   ​                  $C1 = M + rK;     C2 = rG;$

#####         解密过程：

​        6、B机器将点C1、C2传给A机器。

，    7、A接到信息后，计算C1-kC2，结果就是点M。因为

​                        $C1 - kC2 = M + rK  -  krG  =  M + rK - r(kG) = M$

再对点M进行解码就可以得到明文。

在这个加密通信中，如果有一个偷窥者H ，他只能看到Ep(a,b)、K、G、C1、C2，而通过K、G 求k 或通过C2、G求r 都是相对困难的，因此，H无法得到A、B间传送的明文信息。