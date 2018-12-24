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

