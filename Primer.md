# C++ Primer 笔记

## Markdown教程

<https://thisdavej.com/build-an-amazing-markdown-editor-using-visual-studio-code-and-pandoc/>

---

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
    - **同样可以接受C风格字符串**
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
  
  ---

## 第十章 泛型算法

- 题目
  - 10.1(count 定义在头文件 algorithm 里)

    ```C++
    int main()
    {
      vector<int> num_list {1,2,2,2,2,2,3,4};
      cout<<std::count(num_list.cbegin(),num_list.cend(),2)<<endl;
      cin.get();
      return 0;
    }
    ```

  - 10.2

    ```C++
    int main()
    {
      list<string> word_list {"a","b","c","c","d","d","e"};
      cout<<std::count(word_list.cbegin(),word_list.cend(),"c")<<endl;
      cin.get();
      return 0;
    }
    ```

  - 10.3

    ```C++
    int main()
    {
      vector<int> second_list{1,2,3,4,555,6};
      cout<<accumulate(second_list.cbegin(),second_list.cend(),0)<<endl;
      cin.get();
      return 0;
    }
    ```

  - 10.4: 将初值设定为0，表明返回值为int类型，使用之后，会将double转换为int，损失精度
  - 10.5: 一切正常，但是C风格字符串的比较最好还是利用strcmp()，strcmp()是专门用来比的const char*的
  - 10.6

    ```C++
    #include <bits/stdc++.h>//fill_in在这个头文件里
    int main()
    {
      vector<int> num_list(11,2);
      std::fill_n(num_list.begin(),num_list.size(),0);
      for(auto i: num_list)
        cout<<i<<endl;
      return 0;
    }
    ```

  - 10.7
    1. vec是空序列，所含元素比输入序列lst的元素少

        ```C++
        int main()
        {
          vector<int>vec;
          list<int> lst;
          int i;
          while(cin>>i)
            lst.push_back(i);
          vec.resize(lst.size()); //改正
          copy(lst.cbegin(),lst.cend(),vec.begin());
          return 0;
        } 
        ```

    2. reserve是预留容量，vec本身的容量还是0，所以用fill_in重设10个元素会出错

        ```C++
        int main()
        {
          vector<int>vec;
          vec.resize(10);//改正
          std::fill_n(vec.begin(),10,0);
          return 0;
        }
        ```

  - 10.8: 算法只是通过back_insertor插入数据而并没有直接改变容器大小
  - 10.9

    ```C++
    void elimDups(vector<string> &words)
    {
      sort(words.begin(),words.end());
      auto end_itr = unique(words.begin(),words.end());
      words.erase(end_itr,words.end());
    }
    int main()
    {
      ifstream in("input.txt");
      string temp;
      vector<string> words;
      while(in>>temp)
        words.push_back(temp);
      elimDups(words);
      for(auto s:words)
        cout<<s<<endl;
      return 0;
    }
    ```

  - 10.10: 因为算法是运行于迭代器之上的
  - 10.11: sort是纯按字典顺序排列（使用<），这个版本是先按长度排序，然后通过stable_sort令相同长度的单词按字典顺序排序

    ```C++
    void elimDups(vector<string> &words)
    {
      sort(words.begin(),words.end());
      auto end_itr = unique(words.begin(),words.end());
      words.erase(end_itr,words.end());
    }
    bool isShorter(const string& s1, const string &s2)
    {
      return s1.size()<s2.size();
    }
    int main()
    {
      ifstream in("input.txt");
      vector<string> words;
      string temp;
      while(in>>temp)
        words.push_back(temp);
      elimDups(words);
      stable_sort(words.begin(),words.end(),isShorter);
      for(const auto& s: words)
        cout<<s<<endl;
      return 0;
    } 
    ```

  - 10.12: 本题需要用到头文件 Sales_data.h

    ```C++
    #include "Sales_data.h"
    bool compareIsbn( const Sales_data& s1,  const Sales_data& s2)
    {
      return s1.isbn()<s2.isbn();//按isbn的字典顺序排序
    }
    int main()
    {
      ifstream in("input.txt");
      vector<Sales_data> data_list;
      string isbn;
      while(in>>isbn)
        data_list.emplace_back(isbn);
      sort(data_list.begin(),data_list.end(),compareIsbn);
      for(const auto& s: data_list)
        cout<<s.isbn()<<endl;
      return 0;
    } 
    ```
  
  - 10.13

    ```C++
    bool moreThanFive (const string& s)
    {
      return s.size()>=5;
    }
    int main()
    {
      ifstream in("input.txt");
      vector<string> words;
      string temp;
      while(in>>temp)
        words.push_back(temp);
      auto end_of_five = partition(words.begin(),words.end(),moreThanFive);
      for(auto itr=words.begin();itr!=end_of_five;++itr)
      {
        cout<<*itr<<endl;
      }
      return 0;
    }
    ```

  - 10.14

    ```C++
    int main()
    {
      auto sum = [](int a, int b){return a+b;};
      cout<<sum(1,2)<<endl;
      return 0;
    }
    ```
  
  - 10.15

    ```C++
    int main()
    {
      int a=3;
      auto sum = [a](int b){return a+b;};
      cout<<sum(2)<<endl;
      return 0;
    }
    ```

  - 10.16

    ```C++
    void biggies(vector<string> &words, vector<string>::size_type sz)
    {
      elimDups(words);
      auto end_sz = partition(words.begin(),words.end(),[sz](const string& s){return s.size()>=sz;});
      sort(words.begin(),end_sz);//保证输出结果是按字典顺序排序的
      for_each(words.begin(),end_sz,[](const string& s){cout<<s<<" ";});
    }
    int main()
    {
      ifstream in("input.txt");
      string word;
      vector<string> words;
      while(in>>word)
        words.push_back(word);
      biggies(words,6);
      return 0;
    }
    ```

  - 10.17

    ```C++
    #include "Sales_data.h"
    int main()
    {
      ifstream in("input.txt");
      vector<Sales_data> data_list;
      string isbn;
      while(in>>isbn)
        data_list.emplace_back(isbn);
      sort(data_list.begin(),data_list.end(),[](const Sales_data& s1, const Sales_data& s2){return s1.isbn()<s2.isbn();});
      for(const auto& s: data_list)
        cout<<s.isbn()<<endl;
      return 0;
    }
    ```

  - 10.18: 见10.16
  - 10.19

    ```C++
    void biggies(vector<string> &words, vector<string>::size_type sz)
    {
      elimDups(words);
      auto end_sz = stable_partition(words.begin(),words.end(),[sz](const string& s){return s.size()>=sz;});
      for_each(words.begin(),end_sz,[](const string& s){cout<<s<<" ";});
    }
    int main()
    {
      ifstream in("input.txt");
      string word;
      vector<string> words;
      while(in>>word)
        words.push_back(word);
      biggies(words,3);
      return 0;
    }
    ```
  
  - 10.20

    ```C++
    int main()
    {
      ifstream in("input.txt");
      string word;
      vector<string> words;
      while(in>>word)
        words.push_back(word);
      auto count = count_if(words.cbegin(),words.cend(),[](const string& s){return s.size()>6;});
      cout<<count<<endl;
      return 0;
    }
    ```

  - 10.21

    ```C++
    int main()
    {
      ifstream in("input.txt");
      string word;
      vector<string> words;
      while(in>>word)
        words.push_back(word);
      int i=4;
      auto f = [&]()->bool{return i==0?true:!(--i);};
      if(f())//以下为检验代码
      {
        cout<<"i equals to 0!"<<endl;
      }
      else
      {
        cout<<i<<endl;
      }
      return 0;
    }
    ```

  - 10.22

    ```C++
    bool check_sz(const string& s, vector<string>::size_type sz)
    {
      return s.size()>sz;
    }
    int main()
    {
      ifstream in("input.txt");
      vector<string> word_list;
      string temp;
      while(in>>temp)
        word_list.push_back(temp);
      elimDups(word_list);//删除重复的词
      stable_sort(word_list.begin(),word_list.end(),isShorter);//按长度排序
      auto biggy = find_if(word_list.cbegin(),word_list.cend(),bind(check_sz,_1,6));//找出第一个长度大于6的单词的位置
      cout<<biggy-word_list.cbegin()<<endl;
      return 0;
    }
    ```

  - 10.23: bind接受（可调用对象参数数量+1）个参数，多出来的那个参数是可调用对象本身
  - 10.24

    ```C++
    bool check_sz(const string& s, vector<string>::size_type sz)
    {
      return sz>s.size();
    }
    int main()
    {
      ifstream in("input.txt");
      vector<int> num_list;
      int temp;
      while(in>>temp)
        num_list.push_back(temp);
      sort(num_list.begin(),num_list.end()); //对vector按从小到大顺序排序
      string target = "Hellojjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj";
      auto biggy = find_if(num_list.cbegin(),num_list.cend(),bind(check_sz,target,_1));
      cout<<*biggy<<endl;
      return 0;
    }
    ```

  - 10.25

    ```C++
    void biggies2(vector<string> &words, vector<string>::size_type sz)
    {
      elimDups(words);//删除重复的单词
      auto end_sz = stable_partition(words.begin(),words.end(),bind(check_sz,_1,sz));
      for_each(words.begin(),end_sz,[](const string& s){cout<<s<<" ";});
    }
    ```
  
  - 10.26：inserter指定一个特定的位置并插入到这个位置之前。back_inserter在容器尾部插入元素。front_inserter在容器开头插入元素
  - 10.27

    ```C++
    int main()
    {
      ifstream in("input.txt");
      vector<string> word_list;
      list<string> copy_list;
      string temp;
      while(in>>temp)
        word_list.push_back(temp);
      unique_copy(word_list.cbegin(),word_list.cend(),back_inserter(copy_list));
      for_each(copy_list.cbegin(),copy_list.cend(),[](const string& s){cout<<s<<" ";});//实验代码
      return 0;
    }
    ```

  - 10.28

    ```C++
    int main()
    {
      vector<int> oneToNine{1,2,3,4,5,6,7,8,9};
      list<int> list1, list2, list3;
      copy(oneToNine.cbegin(),oneToNine.cend(),inserter(list1,list1.end())); //将oneToNine按原顺序拷贝进list1
      copy(oneToNine.cbegin(),oneToNine.cend(),back_inserter(list2)); //将oneToNine按原顺序拷贝进list2
      copy(oneToNine.cbegin(),oneToNine.cend(),front_inserter(list3)); //将oneToNine的顺序颠倒过来拷贝进list3
      for_each(list1.cbegin(),list1.cend(),[](int s){cout<<s<<" ";}); //测试代码
      cout<<endl;
      for_each(list2.cbegin(),list2.cend(),[](int s){cout<<s<<" ";}); //测试代码
      cout<<endl;
      for_each(list3.cbegin(),list3.cend(),[](int s){cout<<s<<" ";}); //测试代码
      return 0;
    }
    ```

  - 10.29

    ```C++
    int main()
    {
      ifstream in ("input.txt");
      istream_iterator<string> str_in(in),end_in;
      ostream_iterator<string> out_in(cout," ");
      vector<string> words;
      copy(str_in,end_in,back_inserter(words));//将input.txt内容存入vector中
      copy(words.cbegin(),words.cend(),out_in);//将vector中内容打印到标准输出
      return 0;
    }
    ```

  - 10.30

    ```C++
    int main()
    {
      istream_iterator<int> num_itr(cin),end_in;
      ostream_iterator<int> out_in(cout," ");
      vector<int> num_list;
      copy(num_itr,end_in,back_inserter(num_list));//暂存到一个vector里，因为不能直接对input排序
      sort(num_list.begin(),num_list.end());
      copy(num_list.cbegin(),num_list.cend(),out_in);
      return 0;
    }
    ```

  - 10.31

    ```C++
    int main()
    `{
      istream_iterator<int> num_itr(cin),end_in;
      ostream_iterator<int> out_in(cout," ");
      vector<int> num_list;
      copy(num_itr,end_in,back_inserter(num_list));//暂存到一个vector里，因为不能直接对input排序
      sort(num_list.begin(),num_list.end());
      unique_copy(num_list.cbegin(),num_list.cend(),out_in);//筛选出不重复的元素
      return 0;
    }
    ```

  - 10.32: 因为没有Sales_item.h 头文件，到网上抄了一个别人的

    ```C++
    int main(void)
    {
      ifstream file_in("book_sales");
      istream_iterator<Sales_item> in_iter(file_in), eof;
      ostream_iterator<Sales_item> out(cout, "\n");

      vector<Sales_item> data(in_iter, eof);
      sort(data.begin(), data.end());

      cout << "input: " << endl;
      copy(data.begin(), data.end(), out);

      cout << "output: " << endl;
      auto begin = data.begin();
      while( begin != data.end() ){
              auto next = find_if_not(begin, data.end(),
                              bind(compareIsbn, _1, *begin));
              *out++ = accumulate(begin, next, Sales_item(begin->isbn()));//**第三个参数是string的初始值
              begin = next;
      }
      return 0;
    }
    ```

  - 10.33

    ```C++
    int main()
    {
      ifstream in("input.txt");
      ofstream out1("output.txt"),out2("output2.txt");
      istream_iterator<int> num_itr(in),end_in;
      ostream_iterator<int> odd_out(out1," "),even_out(out2,"\n");
      while(num_itr!=end_in)
      {
        if(*num_itr%2==0)
          *even_out++=*num_itr++;//虽然没必要，但按规范写更好
        else
          *odd_out++=*num_itr++;//虽然没必要，但按规范写更好
      }
      return 0;
    }
    ```

  - 10.34

    ```C++
    int main()
    {
      ifstream in("input.txt");
      vector<int> numbers;
      ostream_iterator <int> os(cout," ");
      istream_iterator<int> num_itr(in),end_in;
      copy(num_itr,end_in,back_inserter(numbers));
      copy(numbers.crbegin(),numbers.crend(),os);
      return 0;
    }
    ```

  - 10.35

    ```C++
    int main()
    {
      ifstream in("input.txt");
      vector<int> numbers;
      istream_iterator<int> num_itr(in),end_in;
      copy(num_itr,end_in,back_inserter(numbers));
      for(auto itr = numbers.end();itr!=numbers.begin();--itr)
      {
        cout<<*(itr-1)<<" "; //itr-1妙啊
      }
      return 0;
    }
    ```

  - 10.36

    ```C++
    int main()
    {
      ifstream in("input.txt");
      list<int> numbers;
      istream_iterator<int> num_itr(in),end_in;
      copy(num_itr,end_in,back_inserter(numbers));
      auto czero = find(numbers.crbegin(),numbers.crend(),0);
      return 0;
    }
    ```

  - 10.37

    ```C++
    int main()
    {
      ifstream in("input.txt");
      vector<int> numbers;
      list<int> copiedNumbers;
      istream_iterator<int> num_itr(in),end_in;
      ostream_iterator<int> num_out(cout," ");
      copy(num_itr,end_in,back_inserter(numbers));//将input.txt内容拷贝到vector
      vector<int>::reverse_iterator reverse_end_itr(numbers.begin()+2),reverse_begin_itr(numbers.begin()+7);//创建下标3和7对应的逆序迭代器
      copy(reverse_begin_itr,reverse_end_itr,back_inserter(copiedNumbers));//将内容拷贝到list
      for(auto i: copiedNumbers)//以下为测试代码
        cout<<i<<" ";
      return 0;
    }
    ```

  - 10.38: 见书P366-367
  - 10.39：list的迭代器属于双向迭代器，vector的属于随机访问迭代器
  - 10.40：copy的前两个参数至少是输入迭代器，第三个参数至少是输出迭代器。reverse的两个参数要求至少双向迭代器，unique需要随机访问迭代器
  - 10.41
    - replace(beg, end, old_val, new_val): 将beg和end序列中所有的old_val替换为new_val
    - replace_if(beg, end, pred, new_val): 将beg和end中把所有令pred返回true的元素替换为new_val
    - replace_copy(beg, end, dest, old_val, new_val): 将beg和end中所有old_val替换为new_val然后拷贝到dest中（不改变输入序列）
    - replace_copy_if(beg, end, dest, pred, new_val): 将beg和end中所有令pred返回true的元素替换为new_val然后拷贝到dest中（不改变输入序列）
  - 10.42

    ```C++
    void elimDups_list(list<string>& words)
    {
      words.sort();
      words.unique();
    }
    int main()
    {
      ifstream in("input.txt");
      istream_iterator<string> str_in (in),end_in;
      ostream_iterator<string> os(cout," ");
      list<string> words;
      copy(str_in,end_in,back_inserter(words));
      elimDups_list(words);
      copy(words.cbegin(),words.cend(),os);//测试代码
      return 0;
    }
    ```

- 心得
  - const对象不能使用非常量成员函数。从原理上解释就是调用静态函数时对象把自己的this指针传到成员函数里，所以我们不能把一个非顶层const的this指针指向一个const的对象
  - stable_sort 只有在对纯string序列排序时才有效
  - partition 不带排序功能
  - stable_sort 有一个缺陷是它不能保证第一组相同的字符串是按字典顺序排列的
  - 不保证字典顺序的排列算法会打乱之前的字典排序
    - Eg: partition会打乱之前sort的字典排序
  - **在launch.json中的args的中括号里可以对main函数传实参**
    - 注意，只能按F5调试才有效，直接运行exe或使用code runner都无法对main传入实参
  - inserter 迭代器不接受 const_iterator
  - vscode 如果你ofstream流想打开的文件不存在，会自动帮你创建一个叫这个的文件
  - 正向/逆向迭代器相互转换
    - reverse_iterator转换成iterator用.base()，转换过后所指位置向右移一个位置
    - 正向迭代器转换成逆向迭代器：

      ```C++
      std::reverse_iterator iter_name ( iterator_type x );
      ```

    - 转换过后所指位置向左移一格
  - Get an iterator from a specific index

    ```C++
    vector<Type>::iterator nth = v.begin() + index;
    ```

---

## 第十一章 关联容器

- 题目
  - 11.1: vector储存单个连续元素，用下标访问元素。map储存关键字-值对，可以用关键字找到对应的值。
  - 11.2
    - list: 需要在容器任何位置删添元素
    - vector: 只需要在容器尾部删添元素，有随机访问需求
    - deque: 只需要在容器首尾删添元素，有随机访问需求
    - map: 储存字典型数据
    - set: 坏值检验
  - 11.3: 照抄作业

    ```C++
    int main()
    {
      ifstream in ("input.txt");
      map<string, size_t> word_count;
      string word;
      while(in>>word)
        ++word_count[word];
      for(const auto &w : word_count)
        cout<<w.first<<" occurs "<<w.second<<(w.second>1?" times":" time")<<endl;
      return 0;
    }
    ```

  - 11.4

    ```C++
    int main()
    {
      ifstream in ("input.txt");
      map<string, size_t> word_count;
      string word;
      while(in>>word)
      {
        for(auto& c: word)
          c = tolower(c);//消灭大小写
        word.erase(remove_if(word.begin(),word.end(),ispunct),word.end());//消灭标点符号
        ++word_count[word];
      }
      for(const auto &w : word_count)
        cout<<w.first<<" occurs "<<w.second<<(w.second>1?" times":" time")<<endl;
      return 0;
    }
    ```

  - 11.5: 当只需要使用关键字时使用set，需要使用元素对，则应该使用map
  - 11.6: set中关键字不能有重复，只使用关键字用set，要有更多操作用list
  - 11.7

    ```C++
    int main()
    {
      map<string, vector<string>> families;
      string firstName,lastName;
      char flag = ' ';
      while(true)
      {
        cout<<"Input the last name of the family: ";
        cin>>lastName;
        cout<<"Input the fist name of each family member: ";
        while(cin>>firstName)
        {
          families[lastName].push_back(firstName);
        }
        cin.clear();
        cout<<"More family? (Y/N)";
        cin>>flag;
        if(flag=='N')
          break;
      }
      for(auto itr = families.begin(); itr!=families.end(); ++itr)
      {
        cout<<itr->first<<endl;
        for(auto sitr = itr->second.begin();sitr!=itr->second.end();++sitr)
          cout<<*sitr<<" ";
        cout<<endl;
      }
      return 0;
    }
    ```

  - 11.8 (可能是这样？)

    ```C++
    int main()
    {
      ifstream in("input.txt");
      istream_iterator<string> str_itr(in),end_in;
      set<string> word_map(str_itr,end_in);
      vector<string> words;
      copy(word_map.cbegin(),word_map.cend(),back_inserter(words));
      for(auto s: word_map)
        cout<<s<<endl;
      return 0;
    }
    ```

  - 11.9

    ```C++
    map<string,list<size_t>> connect; 
    ```

  - 11.10: 能，因为vector < int >>::iterator有<运算符
  - 11.11

    ```C++
    multiset<Sales_data, bool (*)(const Sales_data& lhs, const Sales_data& rhs)> bookstore(compareIsbn);
    ```

  - 11.12

    ```C++
    int main()
    {
      string word;
      int num = 0;
      ifstream in("input.txt");
      vector<pair<string, int>> pair_vec;
      while(in>>word>>num&&word!="end")
      {
        pair_vec.push_back({word,num});
      }
      for(auto p: pair_vec)
      cout<<p.first<<" "<<p.second<<endl;
      return 0;
    }
    ```

  - 11.13: 三种方法
    1. push_back(make_pair(v1,v2));
    2. push_back({v1,v2});
    3. emplace_back(v1,v2); //直接构造我认为最直观
  - 11.14

    ```C++
    int main()
    {
      ifstream in("input.txt");
      map<string, vector<pair<string,string>>> families;
      string firstName,lastName,birthDay;
      while(in>>lastName)
      {
        while(in>>firstName>>birthDay && firstName!="end")
        {
          families[lastName].emplace_back(firstName,birthDay);
        }
      }
      //以下为打印测试代码
      for(auto itr = families.begin(); itr!=families.end(); ++itr)
      {
        cout<<itr->first<<endl;
        for(auto sitr = itr->second.begin();sitr!=itr->second.end();++sitr)
          cout<<sitr->first<<" "<<sitr->second<<" ";
        cout<<endl;
      }
      return 0;
    }
    ```

  - 11.15
    - mapped_type:

    ```C++
    pair<int,vector<int>>
    ```

    - key_type: int
    - value_type:

    ```C++
    vector<int>
    ```

  - 11.16

  ```C++
  int main()
  {
    map<string,int> sear{{"hh",3}};
    auto itr = sear.begin();
    itr->second = 4;
    cout<<sear["hh"]<<endl;
    return 0;
  }
  ```

  - 11.17:
    - 第一个调用：对multiset使用inserter合法
    - 第二个调用：back_inserter需要用到push_back，multiset没有push_back，不合法
    - 第三个嗲用：将关联容器拷贝到另一个容器合法
    - 第四个调用：将关联容器拷贝到另一个容器合法
  - 11.18

    ```C++
    map<string,size_t>::iterator map_it
    ```

  - 11.19

  ```C++
  using compareType = bool(*)(const Sales_data& lhs, const Sales_data& rhs);
  multiset<Sales_data,compareType> bookstore(compareIsbn);
  multiset<Sales_data, compareType>::iterator c_itr = bookstore.begin();
  ```

  - 11.20: 我觉得11.20的这个比11.3的更好理解

  ```C++
  int main()
  {
    map<string,size_t> word_count;
    string word;
    while(cin>>word)
    {
      auto ret = word_count.insert({word,1});
      if(!ret.second)
        ++ret.first->second;
    }
    return 0;
  }
  ```

  - 11.21：将word_count插入{word,0}后返回的pair的第一个元素（指向新元素的迭代器）指向的元素的second成员（size_t)加一
  - 11.22：

    ```C++
    pair<map<string,vector <int>>::iterator,bool>
    ```
  
  - 11.23

  ```C++
  int main()
  {
    std::ifstream in("input.txt");
    multimap<string,vector<string>> family;
    string lastName,firstName;
    vector<string> child;
    while(in>>lastName)
    {
      while(in>>firstName&& firstName!="end")
      {
        child.push_back(firstName);
      }
      family.insert({lastName,child});
      child.clear();
    }
    string surname;
    return 0;
  }
  ```

- 11.24: 在m中搜索关键字为0的元素，没找到。插入一个关键字为0的元素，关联值进行值初始化，然后将1赋给关联值。
- 11.25：该程序会报错。因为v本来是空的，而且vector的下标操作不会插入元素，所以访问v的第一个元素会报错
- 11.26: 可以用key_type对map来进行下标操作。下标运算符返回的是mapped_type。
  - eg: map<string, int> kk; //可以用来对map进行下标操作的是string，下标运算符将会返回的类型是int
- 11.27: 不需要计数的时候使用find，需要计数的时候使用count
- 11.28: map<string,int>::iterator target;
- 11.29: upper_bound和lower_bound会返回相同的安全插入位置（不打乱容器顺序），equal_range会返回两个都指向关键字可以插入位置的迭代器
- 11.30：pos.first就是equal_range返回的pair的第一个迭代器，也就是lower_bound。lower_bound访问second成员，就是map的关联值
- 11.31

  ```C++
  int main()
  {
    multimap<string,string> author{{"Eric","PVZ"},{"Eric","KouB"},{"XYL","WXTL"}};
    string target = "Eric";
    auto itr = author.find(target);
    while(itr!=author.end())
    {
      cout<<"Author "<<itr->first<<"'s book "<<itr->second<<" has been eliminated"<<endl;
      author.erase(itr);
      itr = author.find(target);
    }
    return 0;
  }
  ```

- 11.32

  ```C++
  int main()
  {
    multimap<string,string> author{{"XYL","WXTL"},{"Eric","PVZ"},{"Eric","Abc"}};
    map<string,set<string>> library;
    auto it2 = author.begin();
    for(it2;it2!=author.end();++it2)
    {
      library[it2->first].insert(it2->second);//因为set会自动排序，这样可以给作者的书名也按字典顺序排序
    }
    ostream_iterator<string> oitr (cout," ");
    for(auto itr = library.cbegin();itr!=library.cend();++itr)
    {
      cout<<"Author: "<<itr->first<<" has books: ";
      copy(itr->second.begin(),itr->second.end(),oitr);
      cout<<endl;
    }
    return 0;
  }
  ```

- 11.33

  ```C++
  #include <stdexcept>
  #include <sstream>
  using std::runtime_error;
  using std::istringstream;
  map<string,string> buildMap(ifstream &map_file)
  {
    map<string,string> trans_map;
    string key, value;
    while(map_file>>key && getline(map_file,value))
    {
      if(value.size()>1)
        trans_map[key] = value.substr(1);
      else
        throw runtime_error("no rule for "+key);
    }
    return trans_map;
  }
  const string& transform(const string& s, const map<string,string>& m)
  {
    auto target_itr = m.find(s);
    if(target_itr != m.cend())
      return target_itr->second;
    else
      return s;
  }
  void word_transform(ifstream& map_file, ifstream& input)
  {
    auto trans_map = buildMap(map_file);
    string text;
    while(getline(input, text))
    {
      istringstream stream(text);
      string word;
      bool first = true;
      while(stream>>word)
      {
        if(first)
          first = false;
        else
          cout<<" ";
        cout<<transform(word,trans_map);
      }
      cout<<endl;
    }
  }

  int main()
  {
    ifstream map_file("input.txt"),input("input2.txt");
    if(!map_file.is_open() || !input.is_open())
      throw runtime_error("files cannot be opened!");
    word_transform(map_file,input); //注意本程序有个漏洞是如果要替换的词在句子结尾，最后一位会是标点符号，这样程序就无法检测到要替换它因为标点符号和单词读取到一个string里了
    return 0;
  }
  ```

- 11.34: 下标运算符在关键字不在map中的情况下会自动创建这个键值对，把值值初始化。所以会修改map
- 11.35: 如果重复出现多次同样的key值 ，用下标操作后面的value会替换前面的value，而insert则不会替换
- 11.36：会抛出runtime_error "no rule for xxx"
- 11.37：在关键字类型的元素没有明显的序关系的情况下，无序容器是非常有用的。在某些应用中，维护元素的序的代价非常高昂，此时无序容器也很有用，使用无序容器通常更为简单，不需要多余时间维护序列（通常也有更好的性能）。有序版本在key有明显顺序时更有用，容器自动维护序列（字典序）
- 11.38
  - 单词计数

  ```C++
  #include <unordered_map>
  using std::unordered_map;
  int main()
  {
    unordered_map<string, size_t> word_count;
    string word;
    while(cin>>word)
    {
      ++word_count[word];
    }
    for(const auto& s: word_count)
      cout<<s.first<<" occurs "<<s.second<<(s.second>1?" times":" time")<<endl;
    return 0;
  }
  ```

  - 单词转换：只用改buildMap和transform的参数

  ```C++
  unordered_map<string,string> buildMap(ifstream &map_file)
  {
    unordered_map<string,string> trans_map;
    string key, value;
    while(map_file>>key && getline(map_file,value))
    {
      if(value.size()>1)
        trans_map[key] = value.substr(1);
      else
        throw runtime_error("no rule for "+key);
    }
    return trans_map;
  }
  const string& transform(const string& s, const unordered_map<string,string>& m)
  {
    auto target_itr = m.find(s);
    if(target_itr != m.cend())
      return target_itr->second;
    else
      return s;
  }
  ```

- 心得
  - 头文件cctype，ispunct() 函数用来检测一个字符是否为标点符号或特殊字符
  - 目前在头文件iostream中也可以使用，C++ 5.11已证明。把字符转换成小写字母,非字母字符不做出处理用法:

    ```C++
    int tolower(int c);
    ```

  - 关联容器，在映射类型中，标准库使用**关键字**<运算符来比较两个关键字
  - 关联容器支持基本迭代器操作
  - set可以便捷的过滤掉相同的元素
  - 关键字是const类型的，无法被修改
  - multimap和multiset没有下标操作，因为有相同元素

---

## 第十二章 动态内存

### 题目

- 12.1: b1 b2各包含4个元素
- 12.2

  ```C++
  class StrBlob
  {
      typedef vector<string>::size_type size_type;
  public:
      StrBlob():data(std::make_shared<vector<string>>()){ }
      StrBlob(initializer_list<string> il):data(std::make_shared<vector<string>>(il)){ }
      size_type size() const {return data->size();}
      bool empty() const {return data->empty();}
      void push_back(const string& t){data->push_back(t);}
      void pop_back()
      {
          check(0,"pop_back on empty StrBlob");
          data->pop_back();
      }
      string& front() const
      {
          check(0, "front on empty StrBlob");
          return data->front();
      }
      string& back() const
      {
          check(0, "back on empty StrBlob");
          return data->back();
      }
  private:
      shared_ptr<vector<string>> data;
      void check(size_type i, const string &msg) const
      {
          if(i >= data->size())
              throw out_of_range(msg);
      }

  };
  ```

- 12.3: 不需要，因为 **pop_back** 和 **push_back** 改变了vector，一个常量对象不应该能够去改变成员
- 12.4：因为i是size_type类型，即使是负数也会自动转换成非负
- 12.5
  - 优点：抑制了隐式转换，必须清楚的知道类型
  - 缺点：不够简单方便
- 12.6

  ```C++
  vector<int>* vecFactory()
  {
    return new vector<int>;
  }
  vector<int>* read_vec(vector<int>* v,istream& is)
  {
    int num=0;
    while(is>>num)
      (*v).push_back(num);
    return v;
  }
  void print_vec(vector<int>* v, ostream& os)
  {
    for(auto n: (*v))
      os<<n<<" ";
    delete v;
  }
  ```

- 12.7

  ```C++
  shared_ptr<vector<int>> vecFactory()
  {
    return std::make_shared<vector<int>>();
  }
  shared_ptr<vector<int>> read_vec(shared_ptr<vector<int>> v,istream& is)
  {
    int num=0;
    while(is>>num)
      (*v).push_back(num);
    return v;
  }
  void print_vec(shared_ptr<vector<int>> v, ostream& os)
  {
    for(auto n: (*v))
      os<<n<<" ";
  }
  ```

- 12.8: 有错，return时将指针转换成bool，导致其他函数已经无法使用new int这个在动态内存中的对象了，这样的话new int将永远无法被释放
- 12.9
  - r 和 q最后都指向new int(42)，r一开始指向的new int(100)永远无法被释放，造成内存泄露
  - r2和q2最后都指向interesting（42），r2一开始指向的int(100)因为没有智能指针指向它了自动被释放。
- 12.10: 调用是正确的，但p本身就是智能指针不用在传递参数时显示转换，多此一举了
- 12.11: 这样会使两个独立的智能指针指向相同的内存，函数结束后内存会被释放，p将会变成空悬指针
- 12.12
  1. 合法
  2. 不合法，内置指针和智能指针不能隐式转换
  3. 不合法，内置指针和智能指针不能隐式转换
  4. 合法，但内存会被释放，p变成空悬指针
- 12.13: 使用get返回的指针的代码不能delete此指针
- 12.14: 见书上的答案
- 12.15

  ```C++
  [](connection* c){delete c;}
  ```

- 12.16: 无法引用 函数

  ```C++
  std::unique_ptr<_Tp, _Dp>::unique_ptr(const std::unique_ptr<_Tp, _Dp> &) [其中 _Tp=int, _Dp=std::default_delete<int>]
  ```

  它是已删除的函数
- 12.17
  1. 不合法，不能直接通过一个对象创建unique_ptr
  2. 不合法，必须将unique_ptr绑定到一个new返回的指针上，普通指针不行
  3. 合法
  4. 不合法，必须将unique_ptr绑定到一个new返回的指针上，普通指针不行
  5. 合法
  6. 不合法，不使用get()初始化另一个智能指针
- 12.18: release()函数的作用就是放弃对指针指向对象的控制权，但shared_ptr是多对一的关系，其他的智能指针仍然可以删除这个对象，所以这个函数的话对shared_ptr没意义
- 12.19: 照着书上抄的  
  StrBlobPtr类：

  ```C++
  class StrBlobPtr
  {
  private:
      weak_ptr<vector<string>> wptr;
      std::size_t curr;
      shared_ptr<vector<string>>
      check (std::size_t i, const string& msg) const
      {
          auto ret = wptr.lock();
          if(!ret)
              throw runtime_error("unbound StrBlobPtr");
          if(i>=ret->size())
              throw out_of_range(msg);
          return ret;
      }
  public:
      StrBlobPtr(): curr(0){}
      StrBlobPtr(StrBlob& a, std::size_t sz = 0): 
      wptr(a.data), curr(sz){}
      string& deref() const
      {
          auto p = check(curr, "dereference past end");
          return (*p)[curr];
      }
      StrBlobPtr& incr()
      {
          check(curr,"increment past end of StrBlobPtr");
          ++curr;
          return *this;
      }
      std::size_t getCurr() const
      {
          return curr;
      }

  };
  ```
  
  StrBlob的更新

  ```C++
  class StrBlobPtr;
  class StrBlob
  {
    friend class StrBlobPtr;
  public:
    StrBlobPtr begin();
    StrBlobPtr end();
  }
  StrBlobPtr StrBlob::begin()//注意前向声明问题，函数定义得在StrBlobPtr后面
  {
      return StrBlobPtr(*this);
  }
  StrBlobPtr StrBlob::end()
  {
      return StrBlobPtr(*this, data->size());
  }
  ```

- 12.20

  ```C++
  int main()
  {
    ifstream in ("input.txt");
    string line;
    StrBlob blob;
    while(getline(in,line))
      blob.push_back(line);
    auto itr = blob.begin();
    while(itr.getCurr()!=blob.size())
    {
      cout<<itr.deref()<<endl;
      itr.incr();
    }
    return 0;
  }
  ```

- 12.21：我觉得之前的版本更好，题目中的版本虽然一个语句就能实现，但太复杂、可读性太差了
- 12.22

  ```C++
  class ConstStrBlobPtr
  {
  private:
      weak_ptr<vector<string>> wptr;
      std::size_t curr;
      shared_ptr<vector<string>>
      check (std::size_t i, const string& msg) const
      {
          auto ret = wptr.lock();
          if(!ret)
              throw runtime_error("unbound StrBlobPtr");
          if(i>=ret->size())
              throw out_of_range(msg);
          return ret;
      }
  public:
      ConstStrBlobPtr(): curr(0){}
      ConstStrBlobPtr(const StrBlob& a, std::size_t sz = 0): 
      wptr(a.data), curr(sz){}
      const string& deref() const
      {
          auto p = check(curr, "dereference past end");
          return (*p)[curr];
      }
      ConstStrBlobPtr& incr()
      {
          check(curr,"increment past end of StrBlobPtr");
          ++curr;
          return *this;
      }
      std::size_t getCurr() const
      {
          return curr;
      }
  };
  ```

- 12.23

  ```C++
  int main()
  {
    char word1[] = "hello";
    char word2[] = "haha";
    auto itr = new char[2];//这个长度一点不重要，动态数组后面可以改的
    strcpy(itr,word1);
    strcat(itr,word2);
    cout<<itr<<endl;
    delete [] itr;
    return 0;
  }
  ```

  ```C++
  int main()
  {
    string word1 = "hello";
    string word2 = "haha";
    auto itr = new char[0];
    strcpy(itr,(word1+word2).c_str());
    cout<<itr<<endl;
    delete [] itr;
    return 0;
  }
  ```

- 12.24: 动态数组对于超出数组长度的对象会自动分配内存
- 12.25

  ```C++
  delete [] pa;
  ```

- 12.26
  
  ```C++
  int main()
  {
    char word1[] = "hello";
    char word2[] = "haha";
    allocator<char> space;
    auto p = space.allocate(9);
    auto a = uninitialized_copy_n(word1,strlen(word1),p); //a指向最后构造的元素之后的位置
    a = uninitialized_copy_n(word2,strlen(word2),a);
    cout<<p<<endl;
    string w1 = "helbo", w2 = "haha";
    while(a!=p)
      space.destroy(--a);
    auto b = strcpy(p,w1.c_str()); //b指向最后构造的元素之后的位置
    b = strcat(b,w2.c_str());
    cout<<p<<endl;
    while(b!=p)
      space.destroy(--b);
    space.deallocate(p,9);//释放内存
    return 0;
  }
  ```

  ```C++
  int main()
  {
    string word;
    allocator<string> list;
    auto begin = list.allocate(10), end = begin;
    while(cin>>word && end != begin+10)
      list.construct(end++,word);
    while(end != begin)
      list.destroy(--end);
    list.deallocate(begin,10);//释放内存
    return 0;
  }
  ```

  allocator对于超出长度的对象也会自动分配内存  
  先destroy再deallocate释放内存
- 12.27

  ```C++
  class QueryResult;
  class TextQuery
  {
      friend class QueryResult;
  private:
      shared_ptr<vector<string>> v_ptr;
      shared_ptr<map<string,set<size_t>>> dic_ptr;
  public:
      TextQuery(ifstream& in):v_ptr(make_shared<vector<string>>()), dic_ptr(make_shared<map<string,set<size_t>>>())
      {
          string line,word;
          int line_num = 1;
          while(getline(in,line))
          {
              v_ptr->push_back(line);
              istringstream str_in(line);
              while(str_in>>word)
              {
                  word.erase(remove_if(word.begin(),word.end(),ispunct),word.end()); //删除标点符号
                  (*dic_ptr)[word].insert(line_num);
              }
              ++line_num;
          }
      }
      TextQuery():v_ptr(make_shared<vector<string>>()), dic_ptr(make_shared<map<string,set<size_t>>>()) {}
      void printVec()//测试代码
      {
          for(auto s: (*v_ptr))
              cout<<s<<endl;
      }
      void printMap()//测试代码
      {
          for(auto m: (*dic_ptr))
          {
              cout<<m.first<<" ";
              for(auto i: m.second)
                  cout<<i<<" ";
              cout<<endl;
          }
      }
      unsigned query(string s) //检测单词是否在文本中，并返回单词在文本中出现的次数
      {
          if(dic_ptr->find(s) == dic_ptr->end())
              throw std::runtime_error("Input word is not in the text"); //如果单词不在文本中，抛出异常
          unsigned count = 0;
          string word;
          for(auto line : (*v_ptr))
          {
              istringstream str_in(line);
              while(str_in>>word)
              {
                  word.erase(remove_if(word.begin(),word.end(),ispunct),word.end()); //删除标点符号
                  if(s == word)
                      ++count;
              }
          }
          return count;
      }
  };

  class QueryResult
  {
  private:
      weak_ptr<vector<string>> v_ptr;
      weak_ptr<map<string,set<size_t>>> dic_ptr;
      string word;
      unsigned count = 0;
      void check()
      {
          if(!v_ptr.lock() || !dic_ptr.lock())
              throw std::runtime_error("memory has been released!");
      }
  public:
      QueryResult():v_ptr(make_shared<vector<string>>()), dic_ptr(make_shared<map<string,set<size_t>>>()) {}
      QueryResult(const TextQuery& tq, unsigned c, const string& s): v_ptr(tq.v_ptr), dic_ptr(tq.dic_ptr), count(c), word(s) {}
      void print()
      {
          check();
          auto sv_ptr = v_ptr.lock();
          auto sdic_ptr = dic_ptr.lock();
          cout<<word<<" occurs "<<count<<" times"<<endl;
          for(auto i: (*sdic_ptr)[word])
              cout<<"(line "<<i<<") "<<(*sv_ptr)[i-1]<<endl;
      }
  };
  ```

- 12.28: 没有自定义类管理起变量好麻烦

  ```C++
  void build (vector<string>& v_ptr, map<string, set<size_t>>& dic_ptr, istream& in)
  {
    string line,word;
    int line_num = 1;
    while(getline(in,line))
    {
        v_ptr.push_back(line);
        istringstream str_in(line);
        while(str_in>>word)
        {
            word.erase(remove_if(word.begin(),word.end(),ispunct),word.end()); //删除标点符号
            dic_ptr[word].insert(line_num);
        }
        ++line_num;
    }
  }

  unsigned query(vector<string>& v_ptr, map<string, set<size_t>>& dic_ptr, string s)
  {
    if(dic_ptr.find(s) == dic_ptr.end())
        throw std::runtime_error("Input word is not in the text"); //如果单词不在文本中，抛出异常
    unsigned count = 0;
    string word;
    for(auto line : v_ptr)
    {
        istringstream str_in(line);
        while(str_in>>word)
        {
            word.erase(remove_if(word.begin(),word.end(),ispunct),word.end()); //删除标点符号
            if(s == word)
                ++count;
        }
    }
    return count;
  }

  void print(vector<string>& v_ptr, map<string, set<size_t>>& dic_ptr, string word, unsigned count, ostream& os)
  {
    os<<word<<" occurs "<<count<<" times"<<endl;
    for(auto i: dic_ptr[word])
        os<<"(line "<<i<<") "<<v_ptr[i-1]<<endl; 
  }

  int main()
  {
    ifstream in("input.txt");
    ofstream os("output.txt");
    vector<string> vec;
    map<string, set<size_t>> dic;
    build(vec, dic, in);
    while(true)
    {
      cout<<"enter word to look for, or q to quit: ";
      string s;
      if(!(cin>>s) || s == "q")
        break;
      unsigned count = query(vec, dic, s);
      print(vec, dic, s, count, cout);
    }
    return 0;
  }
  ```

- 12.29: 交互过程中让用户先输入单词，显然do while更合适，因为一开始不用判断条件。不过本题中条件是true，不管用哪个都是无限循环，所以两种循环在效果上没区别的
- 12.30: 照抄树上的版本，属实是妙

  ```C++
  class QueryResult;
  class TextQuery{
  public:
      using line_no = vector<string>::size_type;
      TextQuery(ifstream&);
      QueryResult query (const string&) const;
  private:
      shared_ptr<vector<string>> file;
      map<string, shared_ptr<set<line_no>>> wm;
  };
  TextQuery::TextQuery(ifstream &is): file(make_shared<vector<string>>())
  {
      string text;
      while(getline(is, text))
      {
          file->push_back(text);
          int n= file->size() - 1;
          istringstream line(text);
          string word;
          while(line>>word)
          {
              word.erase(remove_if(word.begin(),word.end(),ispunct),word.end());
              auto &lines = wm[word];
              if(!lines)
                  lines.reset(new set<line_no>);
              lines->insert(n);
          }
      }
  }

  class QueryResult
  {
      friend std::ostream& print(std::ostream&, const QueryResult&); //friend declaration for print
  public:
      QueryResult(string s,
                  shared_ptr<set<TextQuery::line_no>> p,
                  shared_ptr<vector<string>> f,
                  unsigned c): sought(s), lines(p), file(f), count(c) {}
  private:
      string sought;
      shared_ptr<set<TextQuery::line_no>> lines;
      shared_ptr<vector<string>> file;
      unsigned count;
  };

  QueryResult TextQuery::query(const string &sought) const
  {
      static shared_ptr<set<TextQuery::line_no>> nodata (make_shared<set<TextQuery::line_no>>());
      auto loc = wm.find(sought);
      string word;
      unsigned count = 0;
      if(loc == wm.end())
          return QueryResult(sought, nodata, file, 0);
      else
      {
          for(auto line:(*file))
          {
              istringstream lines(line);
              while(lines>>word)
              {
                  word.erase(remove_if(word.begin(),word.end(),ispunct),word.end());
                  if(word == sought)
                      ++count;
              }
          }
          return QueryResult(sought, loc->second, file, count);
      }
  }
  ```

- 12.31：肯定set更好，vector不会自动排序的
- 12.32

  ```C++
  class QueryResult;
  class TextQuery{
  public:
      using line_no = vector<string>::size_type;
      TextQuery(ifstream&);
      QueryResult query (const string&);
  private:
      StrBlob file;
      map<string, shared_ptr<set<line_no>>> wm;
  };
  TextQuery::TextQuery(ifstream &is): file()
  {
      string text;
      while(getline(is, text))
      {
          file.push_back(text);
          int n = file.size() - 1;
          istringstream line(text);
          string word;
          while(line>>word)
          {
              word.erase(remove_if(word.begin(),word.end(),ispunct),word.end());
              auto &lines = wm[word];
              if(!lines)
                  lines.reset(new set<line_no>);
              lines->insert(n);
          }
      }
  }

  class QueryResult
  {
      friend std::ostream& print(std::ostream&, QueryResult&); //friend declaration for print
  public:
      QueryResult(string s,
                  shared_ptr<set<TextQuery::line_no>> p,
                  StrBlob f,
                  unsigned c): sought(s), lines(p), file(f), count(c) {}
  private:
      string sought;
      shared_ptr<set<TextQuery::line_no>> lines;
      StrBlob file;
      unsigned count;
  };

  QueryResult TextQuery::query(const string &sought)
  {
      static shared_ptr<set<TextQuery::line_no>> nodata (make_shared<set<TextQuery::line_no>>());
      auto loc = wm.find(sought);
      string word;
      unsigned count = 0;
      if(loc == wm.end())
          return QueryResult(sought, nodata, file, 0);
      else
      {
          for(auto begin = file.begin(); begin.getCurr() != file.size(); begin.incr())
          {
              istringstream lines(begin.deref());
              while(lines>>word)
              {
                  word.erase(remove_if(word.begin(),word.end(),ispunct),word.end());
                  if(word == sought)
                      ++count;
              }
          }
          return QueryResult(sought, loc->second, file, count);
      }
  }
  ```

  ```C++
  string make_plural(size_t ctr, const string &word, const string &ending)
  {
    return (ctr>1)? word+ending : word;
  }
  std::ostream& print(std::ostream& os, QueryResult& qr) //definition for print
  {
      os<<qr.sought<<" occurs "<<qr.count<<" "
      <<make_plural(qr.count, "times", "s")<<endl;
      for(auto num : *qr.lines)
          os<<"\t(Line "<<num+1<<") "<<qr.file.get(num)<<endl;
      return os;
  }

  void runQueries(ifstream &infile)
  {
    TextQuery tq(infile);
    do
    {
      /* code */
      cout<<"enter word to look for, or q to quit: ";
      string s;
      if(!(cin>>s) || s== "q") break;
      auto qr = tq.query(s); //不能把引用绑定在一个右值上
      print(cout, qr)<<endl; 
    } while (true);
  }
  ```

- 12.33: 题目的意思好像是把 ```shared_ptr<vector<string>>``` 改成  ```shared_ptr<StrBlob>``` 不过两个版本差别不大，指针版本就把所有地方加个解引用就是了

  ```C++
  set<TextQuery::line_no>::iterator begin()
  {
      return lines->begin();
  }
  set<TextQuery::line_no>::iterator end()
  {
      return lines->end();
  }
  shared_ptr<StrBlob> get_file()
  {
      return make_shared<StrBlob>();
  }
  ```

### 心得

- 类定义中的类型别名必须在使用前就出现过，但成员变量和函数不需要。
- 标准库容器的指针直接在前面加上解引用就可以像往常一样使用，注意运算符优先级，解引用符有时要加上括号
- 对哑类定义的智能指针，第一个参数必须是一个指向哑类对象的指针，而不是直接一个哑类对象。可以在哑类对象前面加上&
- 内置字符数组或指针可以直接打印
- shared_ptr声明后不分配内存，得用make_shared初始化
- reset的参数只能用new，不能用make_shared
- 头文件之间最好别相互include
- 如果编译器给的错误信息太过模糊，可以运行下程序会给你更多更详细的错误信息
