# 快速清空数组的方式memset()函数

存放在<cstring>头文件中

```C++
void *memset(void *s, int ch, size_t n);
/*百度百科解释：
	将s中当前位置后面的n个字节 （typedef unsigned int size_t ）用 ch 替换并返回 s 。
	
memset：作用是在一段内存块中填充某个给定的值，它是对较大的结构体或数组进行清零操作的一种最快方法。

memset()函数原型是extern void *memset(void *buffer, int c, int count) buffer：为指针或是数组,c：是赋给buffer的值,count：是buffer的长度.
*/
```

##### memset是**按照字节**进行赋值的

例如：一个int就是4个字节(32bit)，清空一个4元素数组为0的方式如下

```C++
int a [4];
memset(a, 0, 16); //4(个元素) * 4(字节 / 元素)
memset(a, 0, sizeof a);//等效写法 
//sizeof a 用于求数组a占用字节大小
```



### 使用memset易出现的错误：

因为操作的单位是字节，所以第二个参数赋值，实际上也是按字节赋值，因此容易出现以下错误：

```C++
int a[4];
memset(a, 0, 16); //{0, 0, 0, 0}
memset(a, 1, 16); //{16843009, 16843009, 16843009, 16843009} 16843009 转换为二进制如下：
//00000001 00000001 00000001 00000001
```

因此一般memset一般只用于赋值全零或全一





# 快速复制数组的方式memcpy()函数

定义在<cstring>中

```C++
//来源百度百科
void *memcpy(void *destin, void *source, unsigned n);
/*
参数
destin-- 指向用于存储复制内容的目标数组，类型强制转换为 void* 指针。

source-- 指向要复制的数据源，类型强制转换为 void* 指针。

n-- 要被复制的字节数。

返回值
该函数返回一个指向目标存储区destin的指针。

功能
从源source所指的内存地址的起始位置开始拷贝n个字节到目标destin所指的内存地址的起始位置中。*/
```



举例：拷贝数组a到b中

```C++
int a[4], b[4];
memcpy(b, a, 16);//按字节执行
memcpy(b, a, sizeof a);//等效写法
```



