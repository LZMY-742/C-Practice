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
  