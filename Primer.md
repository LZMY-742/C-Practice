# C++ Primer 笔记

## Markdown教程

<https://thisdavej.com/build-an-amazing-markdown-editor-using-visual-studio-code-and-pandoc/>

## 第九章 顺序容器

### 9.5 额外的string操作

- **string是可以直接相加的**
- 9.45习题:

  ```C++
  string combine (const string& prefix, const string& name, const string& suffix)
  {
    return prefix+" "+name+" "+suffix;
  }
  ```

- **insert 俩版本能插入的arg不一样**
- 9.46

    ```C++
    string combine2 (const string& prefix, string& name, const string& suffix)
    {
      name.insert(0,prefix);
      name.insert(name.size(),suffix);
      return name;
    }
  ```

- 搜索操作
  - find函数: find 函数完成最简单的搜索。它查找参数指定的字符串，若找到，则返回第一个匹配位置的下标，否则返回 npos
  - 搜索（以及其他 string操作）是大小写敏感的
  - 表9.14∶ string 搜索操作 P325
  - 指定在哪里搜索：我们可以传递给find操作一个可选的开始位置。这个可选的参数指出从哪个位置开
    始进行搜索。默认情况下，此位置被置为0。
  - 逆向搜索
  - 9.47 version1 (using find_first_of)

    ```C++
    int main()
    {
      string target = "ab2c3d7R4E6",number="1234567890",character="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
      string::size_type pos = 0;
      while((pos=target.find_first_of(number,pos))!=string::npos)
      {
        cout<<"Found number at the index "<<pos<<" the element is: "<<target[pos]<<endl;
        ++pos;
      }
      pos=0;
      while((pos=target.find_first_of(character,pos))!=string::npos)
      {
        cout<<"Found letter at the index "<<pos<<" the element is: "<<target[pos]<<endl;
        ++pos;
      }
      return 0; 
    }
    ```
  
  - 9.47 version2 (using find_first_not_of)

    ```C++
    int main()
    {
      string target = "ab2c3d7R4E6",number="1234567890",character="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
      string::size_type pos = 0;
      while((pos=target.find_first_not_of(character,pos))!=string::npos)
      {
        cout<<"Found number at the index "<<pos<<" the element is: "<<target[pos]<<endl;
        ++pos;
      }
      pos=0;
      while((pos=target.find_first_not_of(number,pos))!=string::npos)
      {
        cout<<"Found letter at the index "<<pos<<" the element is: "<<target[pos]<<endl;
        ++pos;
      }
      return 0; 
    }
    ```

  - 9.48: 返回string::npos
  - 9.49

    ```C++
    int main()
    {
      string ascender="bdfhijklt",descender="gjpqy";
      vector<string> word_list,output_list;
      ifstream in("input.txt");
      if(!in)
      {
        cout<<"Can't open the file!"<<endl;
        return 0;
      }
      string word;
      while(in>>word)
        word_list.push_back(word);
      for(auto s:word_list)
      {
        if(s.find_first_of(ascender)==string::npos&&s.find_first_of(descender)==string::npos)
          output_list.push_back(s);
      }
      string longestWord="";
      for(auto s:output_list)
      {
        if(s.size()>longestWord.size())
          longestWord=s;
      }
      cout<<longestWord<<endl;
      return 0; 
    }
    ```

- compare函数
  - 用于比较string
  - 返回0，正数，或负数
  - 表9.15: s.compare的几种参数形式(9.15) P9.15
- 数值转换
  - 实现数值数据与标准库string之间的转换
  - **to_string(int)**实现整数转换为string
  - **stod(string)**实现string转换为double
    - string参数中第一个非空白符必须是以符号+或-或数字。它可以以0x或0X开头来表示十六进制数。
    - 对那些将字符串转换为浮点值的函数，string参数也可以以小数点（.）开头
    - 根据基数不同，string参数可以包括字母字符，对应大于数字9的数
    - **如果string不能转换为一个数值，这些函数抛出一个invalid_argument异常**
    - **如果转换得到的数无法用任何类型来表示，则抛出一个out_of_range异常**
    -表9.16：string和数值之间的转换 P328
    - *s,p,b的参数形式用不了？*
  - 9.50
    - version1

    ```C++
    int main()
    {
      vector<string> num_list{"1","34","44"};
      int sum=0;
      for(auto s: num_list)
        sum+=stoi(s);
      cout<<sum<<endl;
      return 0;
    }
    ```

    - version2

    ```C++
    int main()
    {
      vector<string> num_list{"1.34","34.555","44.33"};
      double sum=0;
      for(auto s: num_list)
        sum+=stod(s);
      cout<<sum<<endl;
      return 0;
    }
    ```

  - 9.51 (format month/day/year)

    ```C++
    int main()
    {
      unsigned year=0,month=0,day=0;
      string date="1/1/1990";
      size_t pos=0;
      month = stoi(date.substr(pos));
      pos=date.find_first_of("/",pos);
      ++pos;
      day = stoi(date.substr(pos));
      pos=date.find_first_of("/",pos);
      ++pos;
      year=stoi(date.substr(pos));
      cout<<"Year: "<<year<<" Month: "<<month<<" Day: "<<day<<endl;
      return 0;
    }
    ```

### 9.6 容器适配器

- 本质上，一个适配器是一种机制，能使某种事物的行为看起来像另外一种事物一样
- 表9.17：所有容器适配器都支持的操作和类型
- 定义一个适配器
  - 每个适配器都定义两个构造函数
    1. **默认构造函数创建一个空对象**
    2. **接受一个容器的构造函数拷贝该容器来初始化适配器**  
    Eg:

    ```C++
    stack<int> stk(deq);//从deq拷贝元素到stk，deq是一个deq<int>
    ```

  - 默认情况下，stack和quene是基于deque实现的，priority_queue是在vector之上实现的。
  - 我们可以在创建一个适配器时将一个命名的顺序容器作为第二个类型参数，来重载默认容器类型
    - Eg

    ```C++
    stack<string,vecotr<string>> str_stk2(svec);//str_stk2在vector上实现，初始化时保存svec的拷贝
    ```

  - 所有适配器都要求容器具有添加和删除元素的能力，因此，适配器不能构造在**array**上
  - 类似的我们也不能用**forward_list**来构造适配器，因为所有适配器都要求容器具有添加、删除以及访问尾元素的能力
  - stack要求push_back,pop_back和back操作，因此可以使用**除array和forward_list**以外的任何容器来构造
  - queue适配器要求back,push_back,front和push_front，因此它可以构造于**list和deque**之上，但不能基于vector构造
  - priority_queue除了push_back,pop_back和front操作还要求随机访问的能力，因此它可以构建于**vector或deque**之上，但不能基于list构造
- 栈适配器(stack)
  - stack类型定义在**stack头文件**中
  - 表9.18：表9.17未列出的stack操作 P330
  - 我们只可以使用适配器操作，而不能使用底层容器类型的操作
  - **push等同于底层容器的push_back**
- 队列适配器(queue and priority_queue)
  - 表9.19∶表9.17未列出的queue 和priority_queue操作 P330
  - 标准库 queue 使用一种先进先出（first-in，first-out，FIFO）的存储和访问策略。进入队列的对象被放置到队尾，而离开队列的对象则从队首删除。饭店按客人到达的顺序来为他们安排座位，就是一个先进先出队列的例子。
  - priority _queue 允许我们为队列中的元素建立优先级。新加入的元素会排在所有优先级比它低的已有元素之前。饭店按照客人预定时间而不是到来时间的早晚来为他们安排座位，就是一个优先队列的例子。默认情况下，标准库在元素类型上使用<运算符来确定相对优先级。
- 9.52(自己理解的版本)
  
  ```C++
  string jia(int a, int b)
  {
    return std::to_string(a+b);
  }
  string jian(int a, int b)
  {
    return std::to_string(a-b); 
  }
  string cheng(int a,int b)
  {
    return std::to_string(a*b);
  }
  string chu(int a,int b)
  {
    return std::to_string(a/b);
  }
  int main()
  {
    vector<string> v1{"10", "(", "25", "/", "5", ")", "7", "6"};
    string linshi;
    stack<string, vector<string>> stack1(v1); //新建stack stack1
    while (!stack1.empty())
    {
      if (stack1.top() == ")") //如果栈顶是右括号
      {
        stack1.pop(); //弹出右括号
        while (stack1.top() != "(") //在到左括号之前
        {
          linshi.insert(0, stack1.top()); //把每个元素插到linshi里
          stack1.pop(); //把元素弹出
          if (stack1.empty()) //如果没遇见左括号直接退出整个循环
            break;
        }
      }
      else //;如果没遇见右括号
      {
        stack1.pop(); //弹出元素
      }
    }
    string shuzi = "0123456789";
    size_t first_not_of = linshi.find_first_not_of(shuzi);//找出第一个不是数字的地方
    string jieguo;
    string a = linshi.substr(0, first_not_of);//第一个数字
    string b = linshi.substr(first_not_of + 1);//运算符右边的数字
    if (linshi[first_not_of] == '+')
      jieguo = jia(stoi(a), stoi(b));
    if (linshi[first_not_of] == '-')
      jieguo = jian(stoi(a), stoi(b));
    if (linshi[first_not_of] == '*')
      jieguo = cheng(stoi(a), stoi(b));
    if (linshi[first_not_of] == '/')
      jieguo = chu(stoi(a), stoi(b));
    stack1.push(jieguo);
    cout << stack1.top()<<endl;
    return 0;
  }
  ```
  