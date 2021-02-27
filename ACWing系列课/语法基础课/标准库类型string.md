# 标准库类型string

可变长的字符序列，比字符数组更加好用。需要引入头文件： #include <string>



## 初始化string

```C++
string s1; //默认空字符串
string s2 = s1;  //s2是s1的一个副本
string s3 = "hiya";	 //s3是该字符串字面值的一个副本
string s4(10, 'c');  //s4的内容是：cccccccccc
```



## string 上的操作

### 1、string的读写

```C++
cin >> s1 >> s2;
cout << s1 << s2;
//不能用scanf输入
//也不能用printf直接输出string，需要写成：printf(“%s”, s.c_str());
//puts类似printf
```

### 	

### 2、使用getline读取一整行

```C++
getline(cin, s1);
```

### 	

### 3、string的empty和size操作

```C++
string s1 = "abc", s2;
cout << s1.empty() << endl;  //输出false
cout << s2.empty() << endl;  //输出true
cout << s1.size() << endl;   //输出 3
//注意size是无符号整数size_t，因此 s.size() <= -1 一定成立
//size()的时间复杂度是O(1)，实现是通过 尾后迭代器 - 开始迭代器
```

### 	

### 4、string 的比较

string重载过运算符 >=， <=，>，<，==，!=

比较同样是按照字典序比较



### 5、字面值和string对象相加

做加法运算时，字面值和字符都会被转化成string对象，因此直接相加就是将这些字面值串联起来

```C++
//string重载过的+号运算符
string s1 = "hello", s2 = "world";		// 在s1和s2中都没有标点符号
string s3 = s1 + ", " + s2 + '\n';
```



⚠️当把string对象和字符字面值及字符串字面值混在一条语句中使用时，必须确保每个加法运算符的两侧的运算对象至少有一个是string

```C++
string s4 = s1 + ",";	
// 正确：把一个string对象和有一个字面值相加
string s5 = "hello" + ","; 
// 错误：两个运算对象都不是string
string s6 = s1 + "," + "hello";  
// 正确，每个加法运算都有一个运算符是string
string s7 = "hello" + "," + s2;  
// 错误：不能把字面值直接相加，运算是从左到右进行的

```

