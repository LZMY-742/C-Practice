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
  - 9.47 version1

    ```C++
    int main(){
      string target = "ab2c3d7R4E6",number="1234567890",character="abcdefghijklmnopqrstuvwxyz";
      string::size_type pos = 0;
      while((pos=target.find_first_of(number,pos))!=string::npos)
      {
        cout<<"Found number at the index "<<pos<<" the element is: "<<target[pos]<<endl;
        ++pos;
      }
      return 0; 
    }
    ```
  
  -  
  
