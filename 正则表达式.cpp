#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <iomanip>

//正则表达式匹配与搜索
int main() {
    // 示例文本
    std::string text = "我的电子邮箱是example@gmail.com，电话号码是13812345678";

    // 匹配电子邮箱的正则表达式
    std::regex email_pattern(R"((\w+)@(\w+)\.(\w+))");

    // 匹配电话号码的正则表达式
    std::regex phone_pattern(R"(1[3-9]\d{9})");

    // 使用regex_search查找邮箱
    std::smatch email_match;
    if (std::regex_search(text, email_match, email_pattern)) {
        std::cout << "找到电子邮箱: " << email_match[0] << std::endl;
        std::cout << "用户名: " << email_match[1] << std::endl;
        std::cout << "域名: " << email_match[2] << "." << email_match[3] << std::endl;
    }
    else {
        std::cout << "未找到电子邮箱" << std::endl;
    }

    // 使用regex_search查找电话号码
    std::smatch phone_match;
    if (std::regex_search(text, phone_match, phone_pattern)) {
        std::cout << "找到电话号码: " << phone_match[0] << std::endl;
    }
    else {
        std::cout << "未找到电话号码" << std::endl;
    }

    // 使用regex_match检查整个字符串是否匹配模式
    std::string email = "test@example.com";
    if (std::regex_match(email, email_pattern)) {
        std::cout << "有效的电子邮箱格式" << std::endl;
    }
    else {
        std::cout << "无效的电子邮箱格式" << std::endl;
    }

    return 0;
}

//正则表达式替换
int main() {
    // 示例文本
    std::string text = "今天是2023-05-15，明天是2023-05-16，后天是2023-05-17";

    // 将日期格式从YYYY-MM-DD转换为MM/DD/YYYY
    std::regex date_pattern(R"((\d{4})-(\d{2})-(\d{2}))");
    std::string date_format = "$2/$3/$1";

    // 使用regex_replace替换所有匹配项
    std::string result = std::regex_replace(text, date_pattern, date_format);
    std::cout << "原始文本: " << text << std::endl;
    std::cout << "替换后文本: " << result << std::endl;

    // 使用标志控制替换行为
    // 只替换第一个匹配项
    result = std::regex_replace(text, date_pattern, date_format,
        std::regex_constants::format_first_only);
    std::cout << "只替换第一个: " << result << std::endl;

    // 不进行替换，而是将不匹配的部分复制到结果中
    result = std::regex_replace(text, date_pattern, date_format,
        std::regex_constants::format_no_copy);
    std::cout << "只显示替换部分: " << result << std::endl;

    return 0;
}

//正则表达式迭代器
int main() {
    // 示例文本
    std::string text = "小明的成绩是：语文85分，数学92分，英语78分，物理90分";

    // 匹配科目和分数的正则表达式
    std::regex pattern(R"((\w+)(\d+)分)");

    // 使用regex_iterator查找所有匹配项
    std::vector<std::pair<std::string, int>> scores;
    auto words_begin = std::sregex_iterator(text.begin(), text.end(), pattern);
    auto words_end = std::sregex_iterator();

    std::cout << "找到 " << std::distance(words_begin, words_end) << " 个成绩记录:" << std::endl;

    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        std::string subject = match[1];
        int score = std::stoi(match[2]);
        scores.push_back({ subject, score });

        std::cout << "科目: " << subject << ", 分数: " << score << std::endl;
    }

    // 计算平均分
    if (!scores.empty()) {
        int total = 0;
        for (const auto& score : scores) {
            total += score.second;
        }
        double average = static_cast<double>(total) / scores.size();
        std::cout << "平均分: " << average << std::endl;
    }

    return 0;
}

//综合应用
// 定义一个结构体来存储解析后的数据
struct Contact {
    std::string name;
    std::string email;
    std::string phone;
};

// 验证电子邮箱格式
bool validateEmail(const std::string& email) {
    std::regex pattern(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    return std::regex_match(email, pattern);
}

// 验证中国手机号格式
bool validateChinesePhone(const std::string& phone) {
    std::regex pattern(R"(^1[3-9]\d{9}$)");
    return std::regex_match(phone, pattern);
}

// 从文本中提取联系人信息
std::vector<Contact> extractContacts(const std::string& text) {
    std::vector<Contact> contacts;

    // 匹配格式：姓名：xxx，电子邮箱：xxx@xxx.xxx，电话：xxxxxxxxxx
    std::regex pattern(R"(姓名：([^，]+)，电子邮箱：([^，]+)，电话：([^\n]+))");

    auto begin = std::sregex_iterator(text.begin(), text.end(), pattern);
    auto end = std::sregex_iterator();

    for (std::sregex_iterator i = begin; i != end; ++i) {
        std::smatch match = *i;
        Contact contact;
        contact.name = match[1];
        contact.email = match[2];
        contact.phone = match[3];
        contacts.push_back(contact);
    }

    return contacts;
}

int main() {
    // 示例文本
    std::string text = "联系人列表：\n"
        "姓名：张三，电子邮箱：zhangsan@example.com，电话：13812345678\n"
        "姓名：李四，电子邮箱：lisi@invalid，电话：13987654321\n"
        "姓名：王五，电子邮箱：wangwu@company.org，电话：1390000abcd\n";

    // 提取联系人信息
    std::vector<Contact> contacts = extractContacts(text);

    // 验证并显示联系人信息
    std::cout << "提取到 " << contacts.size() << " 个联系人信息：" << std::endl;
    std::cout << std::left << std::setw(10) << "姓名"
        << std::setw(25) << "电子邮箱"
        << std::setw(15) << "电话"
        << std::setw(20) << "验证结果" << std::endl;
    std::cout << std::string(70, '-') << std::endl;

    for (const auto& contact : contacts) {
        bool validEmail = validateEmail(contact.email);
        bool validPhone = validateChinesePhone(contact.phone);

        std::cout << std::left << std::setw(10) << contact.name
            << std::setw(25) << contact.email
            << std::setw(15) << contact.phone;

        if (validEmail && validPhone) {
            std::cout << std::setw(20) << "全部有效" << std::endl;
        }
        else {
            std::string result;
            if (!validEmail) result += "邮箱无效 ";
            if (!validPhone) result += "电话无效";
            std::cout << std::setw(20) << result << std::endl;
        }
    }

    return 0;
}

/*
* C++正则表达式知识点总结
一、基本概念
C++11标准引入了正则表达式库，位于<regex>头文件中。正则表达式是一种用于匹配字符串模式的强大工具，可以用于搜索、替换和验证文本。

二、主要类和函数
1.
核心类：

std::regex：表示一个正则表达式
std::smatch：存储字符串匹配结果
std::cmatch：存储C风格字符串匹配结果
std::regex_iterator：用于迭代所有匹配项
std::regex_token_iterator：用于迭代子表达式匹配或未匹配部分
2.
主要函数：

std::regex_match：检查整个字符串是否匹配正则表达式
std::regex_search：在字符串中搜索匹配正则表达式的部分
std::regex_replace：替换匹配正则表达式的部分
三、正则表达式语法和元字符
1.
基本元字符：

. - 匹配任意单个字符（除了换行符）
^ - 匹配字符串开头
$ - 匹配字符串结尾
* - 匹配前面的元素零次或多次
+ - 匹配前面的元素一次或多次
? - 匹配前面的元素零次或一次
| - 表示或关系（选择）
2.
字符类：

[abc] - 匹配a、b或c中的任意一个字符
[^abc] - 匹配除了a、b和c之外的任意字符
[a-z] - 匹配a到z范围内的任意字符
\d - 匹配数字（等同于[0-9]）
\w - 匹配字母、数字或下划线（等同于[a-zA-Z0-9_]）
\s - 匹配空白字符
3.
重复限定符：

{n} - 精确匹配n次
{n,} - 匹配至少n次
{n,m} - 匹配n到m次
4.
分组：

(...) - 创建一个捕获组
(?:...) - 创建一个非捕获组

## 五、注意事项和性能考虑
1. 1.
   转义字符 ：在C++字符串中，反斜杠 \ 本身需要转义，所以要表示正则表达式中的 \d ，需要写成 \\d 。
2. 2.
   正则表达式标志 ：

   - std::regex::icase - 忽略大小写
   - std::regex::nosubs - 不存储子表达式匹配
   - std::regex::optimize - 优化匹配性能
   - std::regex::ECMAScript - 使用ECMAScript语法（默认）
3. 3.
   性能考虑 ：

   - 正则表达式编译是昂贵的操作，应尽量重用已编译的正则表达式对象
   - 避免使用过于复杂的回溯模式，如 (a+)+ 这样可能导致灾难性回溯的模式
   - 对于简单的字符串操作，使用标准字符串函数可能更高效
4. 4.
   异常处理 ：

   - 正则表达式语法错误会抛出 std::regex_error 异常
   - 应当使用try-catch块处理可能的异常
*/