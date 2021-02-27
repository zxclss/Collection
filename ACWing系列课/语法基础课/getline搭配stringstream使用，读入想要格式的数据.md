# getline搭配stringstream使用，读入想要格式的数据

```C++
string s;
getline(cin, s);  //读入一整行数据存储为字符串

int a, b;
string str;
double c;		//这一整行数据中空格隔开的各个部分，读入你想要的类型

stringstream ssin(s);  //用s初始化stringstream流对象
ssin >> a >> str >> b >> c;  //写入各个部分

cout << a << endl << str << endl << b << endl << c << endl;

```



scanf的等效方法

```C++
char s [1000];
fgets(s, 1000, stdin); //读入一整行数据存储为字符串

int a, b;
string str;
double c;		//这一整行数据中空格隔开的各个部分，读入你想要的类型

sscanf(s, "%d%s%d%lf", &a, str, &b, &c);
printf("%d\n%s\n%d\n%lf\n", a, str, b, c);
```

