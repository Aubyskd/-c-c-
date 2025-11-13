#include<iostream>
#include<string>
using namespace std;
//封装，继承，对象
//// 类的定义
//class Person {   //class默认private，struct默认public
//private://（只有内部）
//    std::string name;//属性
//    int age;
//
//public://访问权限(内外都可以访问）
//    //行为
//    // 构造函数
//    Person(const std::string& n, int a) : name(n), age(a) {}
//
//    // 成员函数
//    void introduce() {
//        std::cout << "My name is " << name << ", I am " << age << " years old." << std::endl;
//        cout << "secret is" << secret << endl;
//    }
//protected://（只有内部，子类可以访问）
//    string secret="12345";
//};
//
//// 创建和使用对象
//int main() 
//{
//    //实例化
//    Person person1("Alice", 25);  // 栈上创建对象
//    person1.introduce();
//
//    Person* person2 = new Person("Bob", 30);  // 堆上创建对象
//    person2->introduce();
//    delete person2;  // 释放堆内存
//
//	Person person3 = Person("Charlie", 28); // 另一种实例化方式)
//   // person3.secret 无法访问
//
//    return 0;
//}

////成员属性设置为私有
//struct Person
//{
//public:
//	void setname(string n)
//	{
//		name = n;
//	}
//	string getname()
//	{
//		return name;
//	}
//
//	int getage()
//	{
//		return age;
//	}
//
//	void setidol(string i)
//	{
//		idol = i;
//	}
//
//	void setdream(int d)
//	{
//		if (d < 0 || d>150)
//		{
//			cout << "error" << endl;
//			return;
//		}
//		age = d;
//	}
//private:
//	string name;//读写
//	int age=18;//读
//	string idol;//写
//};
//int main()
//{
//	Person p1;
//	p1.setname("lily");
//	cout << p1.getname() << endl;
//
//	cout << p1.getage() << endl;
//
//	p1.setidol("taylor");//无法访问到
//
//	p1.setdream(20);
//	cout << p1.getage() << endl;
//	p1.setdream(220);
//	cout << p1.getage() << endl;
//}

//练习1
//class cube
//{
//	//创建
//	//设计属性
//private:
//	int l;
//	int w;
//	int h;
//public:
//	void setl(int len)
//	{
//		l = len;
//	}
//	int getl()
//	{
//		return l;
//	}
//	void setw(int wid)
//	{
//		w = wid;
//	}
//	int getw()
//	{
//		return w;
//	}
//	void seth(int hei)
//	{
//		h = hei;
//	}
//	int geth()
//	{
//		return h;
//	}
//	//获取面积和体积
//	int cals()
//	{
//		return 2 * l * w + 2 * l * h + 2 * w * h;
//	}
//	int calv()
//	{
//		return l * h * w;
//	}
//	bool whether(cube &c)
//	{
//		if (l== c.getl() && w== c.getw() &&h== c.geth())
//		{
//			return true;
//		}
//		return false;
//	}
//	//设计行为
//	//全局函数和成员函数
//};
//bool issame(cube& c1, cube& c2)
//{
//	if (c1.getl() == c2.getl() && c1.getw() == c2.getw() && c1.geth() == c2.geth())
//	{
//		return true;
//	}
//	return false;
//}
//int main()
//{
//	cube c1;
//	c1. setl(10);
//	c1. setw(10);
//	c1. seth(10);
//
//	cout << c1.cals() << endl;
//	cout << c1.calv() << endl;
//
//	cube c2;
//	c2.setl(10);
//	c2.setw(10);
//	c2.seth(10);
//
//	cube c3;
//	c3.setl(10);
//	c3.setw(11);
//	c3.seth(10);
//
//
//	bool ret = issame(c1, c2);
//
//	if (ret)
//	{
//		cout << 1 << endl;
//	}
//	else
//	{
//		cout << 0 << endl;
//	}
//
//	bool res = c1.whether(c3);
//	if (res)
//	{
//		cout << 1 << endl;
//	}
//	else
//	{
//		cout << 0 << endl;
//	}
//}

//练习2
//#include"circle.h"
//#include"point.h"
//void whether(circle& c, point& p)
//{
//	int distance =
//		(c.getcenter().getx() - p.getx()) * (c.getcenter().getx() - p.getx()) + (c.getcenter().gety() - p.gety()) * (c.getcenter().gety() - p.gety());
//	int rdis = c.getr() * c.getr();
//	if (distance == rdis)
//	{
//		cout << "on" << endl;
//	}
//	if (distance  > rdis)
//	{
//		cout << "out" << endl;
//	}
//	if (distance < rdis)
//	{
//		cout << "in" << endl;
//	}
//}
//int main()
//{
//	circle c1;
//	c1.setr(10);
//	point p1;
//	p1.setx(10);
//	p1.sety(0);
//	c1.setc(p1);
//
//	point p2;
//	p2.setx(10);
//	p2.sety(10);
//
//	point p3;
//	p3.setx(11);
//	p3.sety(11);
//
//	point p4;
//	p4.setx(5);
//	p4.sety(0);
//
//	whether(c1, p2);
//	whether(c1, p3);
//	whether(c1, p4);
//}


////访问控制和封装
//class BankAccount {
//private:
//    double balance;  // 私有成员，只能在类内部访问
//
//protected:
//    std::string accountType;  // 保护成员，可以被派生类访问
//
//public:
//    std::string accountNumber;  // 公有成员，可以被任何函数访问
//
//    // 构造函数
//    BankAccount(const std::string& num, const std::string& type, double bal)
//        : accountNumber(num), accountType(type), balance(bal) {
//    }
//
//    // 公有方法提供对私有数据的访问
//    void deposit(double amount) {
//        if (amount > 0) {
//            balance += amount;
//        }
//    }
//
//    bool withdraw(double amount) {
//        if (amount > 0 && balance >= amount) {
//            balance -= amount;
//            return true;
//        }
//        return false;
//    }
//
//    double getBalance() const {
//        return balance;
//    }
//};

//构造函数和析构函数(系统默认创建)
//构造函数没有返回值，可以有参数，可以发生重载，名字与类名相同，创建对象时自动调用且只调用一次
class Resource {
private:
    int* data;
    size_t size;

public:

    // 默认构造函数
    Resource() : data(nullptr), size(0) {
        std::cout << "Default constructor called" << std::endl;
    }

    // 带参数的构造函数
    Resource(size_t s) : size(s) {
        data = new int[size];
        std::cout << "Parameterized constructor called" << std::endl;
    }

    // 拷贝构造函数
    Resource(const Resource& other) : size(other.size) {
        data = new int[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
        std::cout << "Copy constructor called" << std::endl;
    }

    // 拷贝赋值运算符
    Resource& operator=(const Resource& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new int[size];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        std::cout << "Copy assignment operator called" << std::endl;
        return *this;
    }

    // 移动赋值运算符 (C++11)
    Resource& operator=(Resource&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
        }
        std::cout << "Move assignment operator called" << std::endl;
        return *this;
    }

    // 析构函数(不能发生重载，只调用一次）
    ~Resource() {
        delete[] data;
        std::cout << "Destructor called" << std::endl;
    }
};
void test01()
{
    Resource r;//栈上的数据，释放对象前一定会调用这个析构函数
    Resource r1 = 10;
    Resource r2 = r1;
}


class Person
{

public:
    int age;
    Person()
    {
        cout << "hello" << endl;
    }
    Person(int n)
    {
        age = n;
        cout << "bye" << endl;
    }
    Person(const Person& p)
    {
        age = p.age;
        cout << "www" << endl;
    }
};
//使用一个已经创建完毕的对象来初始化另一个新对象
void test02()
{
    Person p1(20);
    Person p2(40);
    cout << p1.age + p2.age << endl;
}
//值传递的方式传参
void a(Person p) {

}
void test03()
{
    Person p=3;
    a(p);
    cout << p.age << endl;
}
//值方式返回局部对象
Person b()
{
    Person p1;
    return p1;
}
void test04()
{
    Person p = b();//和p1不是一个对象
}
int main()
{
    test01();
    cout << " " << endl;
    //1/括号法
    Person p1;//默认构造函数时不加括号
    Person p2(10);
    Person p3(p2);
    cout << p2.age << endl;
    cout << p3.age << endl;
    cout << " " << endl;
    //2、显示法
    Person p4;
    Person p5 = Person(11);//当前行执行结束后，创建的匿名对象被释放
    Person p6 = Person(p5);
    cout << p5.age << endl;
    cout << p6.age + 1 << endl;
    cout << " " << endl;
    //3、隐式转换法
    Person p7 = 18;
    Person p8 = p7;
    cout << p7.age << endl;
    cout << " " << endl;
    //拷贝函数调用
    test02();
    cout << " " << endl;
    test03();
    test04();
}
//
////四、继承和多态
//// 基类
//class Shape {
//protected:
//    double x, y;
//
//public:
//    Shape(double x = 0, double y = 0) : x(x), y(y) {}
//
//    // 虚函数，允许派生类重写
//    virtual double area() const {
//        return 0;
//    }
//
//    // 纯虚函数，使Shape成为抽象类
//    virtual void draw() const = 0;
//
//    // 虚析构函数，确保正确析构派生类对象
//    virtual ~Shape() {
//        std::cout << "Shape destructor" << std::endl;
//    }
//};
//
//// 派生类 - 圆形
//class Circle : public Shape {
//private:
//    double radius;
//
//public:
//    Circle(double x, double y, double r) : Shape(x, y), radius(r) {}
//
//    // 重写基类的虚函数
//    double area() const override {
//        return 3.14159 * radius * radius;
//    }
//
//    void draw() const override {
//        std::cout << "Drawing a circle at (" << x << "," << y
//            << ") with radius " << radius << std::endl;
//    }
//
//    ~Circle() {
//        std::cout << "Circle destructor" << std::endl;
//    }
//};
//
//// 派生类 - 矩形
//class Rectangle : public Shape {
//private:
//    double width, height;
//
//public:
//    Rectangle(double x, double y, double w, double h)
//        : Shape(x, y), width(w), height(h) {
//    }
//
//    double area() const override {
//        return width * height;
//    }
//
//    void draw() const override {
//        std::cout << "Drawing a rectangle at (" << x << "," << y
//            << ") with width " << width << " and height " << height << std::endl;
//    }
//
//    ~Rectangle() {
//        std::cout << "Rectangle destructor" << std::endl;
//    }
//};
//
//// 多态使用
//void printArea(const Shape& shape) {
//    std::cout << "Area: " << shape.area() << std::endl;
//    shape.draw();
//}
//
//int main() {
//    Circle circle(0, 0, 5);
//    Rectangle rectangle(10, 10, 4, 6);
//
//    printArea(circle);     // 调用Circle::area()和Circle::draw()
//    printArea(rectangle);  // 调用Rectangle::area()和Rectangle::draw()
//
//    // 使用基类指针
//    Shape* shapes[2];
//    shapes[0] = new Circle(2, 3, 7);
//    shapes[1] = new Rectangle(5, 5, 3, 8);
//
//    for (int i = 0; i < 2; ++i) {
//        printArea(*shapes[i]);
//        delete shapes[i];  // 调用适当的析构函数
//    }
//
//    return 0;
//}
//
////五、运算符重载
//class Complex {
//private:
//    double real, imag;
//
//public:
//    Complex(double r = 0, double i = 0) : real(r), imag(i) {}
//
//    // 重载+运算符（成员函数）
//    Complex operator+(const Complex& other) const {
//        return Complex(real + other.real, imag + other.imag);
//    }
//
//    // 重载-运算符（成员函数）
//    Complex operator-(const Complex& other) const {
//        return Complex(real - other.real, imag - other.imag);
//    }
//
//    // 重载*运算符（成员函数）
//    Complex operator*(const Complex& other) const {
//        return Complex(real * other.real - imag * other.imag,
//            real * other.imag + imag * other.real);
//    }
//
//    // 重载==运算符（成员函数）
//    bool operator==(const Complex& other) const {
//        return (real == other.real) && (imag == other.imag);
//    }
//
//    // 重载!=运算符（成员函数）
//    bool operator!=(const Complex& other) const {
//        return !(*this == other);
//    }
//
//    // 重载前置++运算符
//    Complex& operator++() {
//        ++real;
//        return *this;
//    }
//
//    // 重载后置++运算符
//    Complex operator++(int) {
//        Complex temp = *this;
//        ++real;
//        return temp;
//    }
//
//    // 重载<<运算符（友元函数）
//    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
//        os << c.real;
//        if (c.imag >= 0) os << "+";
//        os << c.imag << "i";
//        return os;
//    }
//
//    // 重载>>运算符（友元函数）
//    friend std::istream& operator>>(std::istream& is, Complex& c) {
//        std::cout << "Enter real part: ";
//        is >> c.real;
//        std::cout << "Enter imaginary part: ";
//        is >> c.imag;
//        return is;
//    }
//};
//
//int main() {
//    Complex a(3, 4);
//    Complex b(1, 2);
//
//    Complex c = a + b;
//    Complex d = a * b;
//
//    std::cout << "a = " << a << std::endl;
//    std::cout << "b = " << b << std::endl;
//    std::cout << "a + b = " << c << std::endl;
//    std::cout << "a * b = " << d << std::endl;
//
//    ++a;
//    std::cout << "After ++a: " << a << std::endl;
//
//    Complex e = b++;
//    std::cout << "e = b++: " << e << std::endl;
//    std::cout << "After b++: " << b << std::endl;
//
//    return 0;
//}
//
////六、静态成员和友元
//class Counter {
//private:
//    int id;
//    static int count;  // 静态数据成员声明
//
//    // 友元函数声明
//    friend void resetCounter();
//
//    // 友元类声明
//    friend class CounterManager;
//
//public:
//    Counter() : id(++count) {
//        std::cout << "Created Counter #" << id << std::endl;
//    }
//
//    ~Counter() {
//        std::cout << "Destroyed Counter #" << id << std::endl;
//    }
//
//    // 静态成员函数
//    static int getCount() {
//        return count;
//    }
//
//    int getId() const {
//        return id;
//    }
//};
//
//// 静态数据成员定义（必须在类外定义）
//int Counter::count = 0;
//
//// 友元函数定义
//void resetCounter() {
//    Counter::count = 0;
//    std::cout << "Counter reset to 0" << std::endl;
//}
//
//// 友元类定义
//class CounterManager {
//public:
//    void printCounterDetails(const Counter& c) {
//        std::cout << "Counter #" << c.id << " (total: " << Counter::count << ")" << std::endl;
//    }
//
//    void setCounterId(Counter& c, int newId) {
//        c.id = newId;
//    }
//};
//
//int main() {
//    std::cout << "Initial count: " << Counter::getCount() << std::endl;
//
//    Counter c1;
//    Counter c2;
//    Counter c3;
//
//    std::cout << "Current count: " << Counter::getCount() << std::endl;
//
//    CounterManager manager;
//    manager.printCounterDetails(c2);
//    manager.setCounterId(c3, 100);
//    manager.printCounterDetails(c3);
//
//    resetCounter();
//    std::cout << "After reset: " << Counter::getCount() << std::endl;
//
//    return 0;
//}
//
////七、模板类
//template <typename T>
//class Stack {
//private:
//    std::vector<T> elements;
//
//public:
//    void push(const T& element) {
//        elements.push_back(element);
//    }
//
//    T pop() {
//        if (elements.empty()) {
//            throw std::out_of_range("Stack is empty");
//        }
//        T top = elements.back();
//        elements.pop_back();
//        return top;
//    }
//
//    T& top() {
//        if (elements.empty()) {
//            throw std::out_of_range("Stack is empty");
//        }
//        return elements.back();
//    }
//
//    bool isEmpty() const {
//        return elements.empty();
//    }
//
//    size_t size() const {
//        return elements.size();
//    }
//
//    void clear() {
//        elements.clear();
//    }
//};
//
//// 特化模板类
//template <>
//class Stack<bool> {
//private:
//    std::vector<bool> elements;
//
//public:
//    void push(bool element) {
//        elements.push_back(element);
//        std::cout << "Specialized bool stack: pushed " << (element ? "true" : "false") << std::endl;
//    }
//
//    bool pop() {
//        if (elements.empty()) {
//            throw std::out_of_range("Bool Stack is empty");
//        }
//        bool top = elements.back();
//        elements.pop_back();
//        return top;
//    }
//
//    bool isEmpty() const {
//        return elements.empty();
//    }
//};
//
//int main() {
//    // 整数栈
//    Stack<int> intStack;
//    intStack.push(10);
//    intStack.push(20);
//    intStack.push(30);
//
//    std::cout << "Int Stack size: " << intStack.size() << std::endl;
//    std::cout << "Top element: " << intStack.top() << std::endl;
//
//    while (!intStack.isEmpty()) {
//        std::cout << "Popped: " << intStack.pop() << std::endl;
//    }
//
//    // 字符串栈
//    Stack<std::string> stringStack;
//    stringStack.push("Hello");
//    stringStack.push("World");
//
//    std::cout << "String Stack size: " << stringStack.size() << std::endl;
//
//    while (!stringStack.isEmpty()) {
//        std::cout << "Popped: " << stringStack.pop() << std::endl;
//    }
//
//    // 布尔栈（使用特化版本）
//    Stack<bool> boolStack;
//    boolStack.push(true);
//    boolStack.push(false);
//
//    while (!boolStack.isEmpty()) {
//        std::cout << "Popped: " << (boolStack.pop() ? "true" : "false") << std::endl;
//    }
//
//    return 0;
//}





/*
# C++面向对象编程语法知识总结
## 一、类和对象的基本概念
类是C++中实现面向对象编程的基本单元，它是对象的蓝图或模板。对象是类的实例。

## 二、类的属性和方法
类包含数据成员（属性）和成员函数（方法）。

## 三、类的访问控制和封装
C++提供三种访问修饰符来控制类成员的访问权限：

- public : 可以被任何函数访问
- private : 只能被类的成员函数访问
- protected : 可以被类的成员函数和派生类访问

## 四、构造函数和析构函数
构造函数在对象创建时自动调用，用于初始化对象。析构函数在对象销毁时自动调用，用于清理资源。

## 五、继承和多态
继承允许创建派生类，继承基类的成员。多态允许通过基类指针或引用调用派生类的函数。

## 六、运算符重载
C++允许为自定义类型重载大多数运算符，使其行为类似于内置类型。

## 七、静态成员和友元
静态成员属于类而不是对象。友元函数或类可以访问类的私有成员。

## 八、模板类
模板允许创建通用的类，可以处理不同类型的数据。

## 总结
C++面向对象编程的核心特性包括：

1. 1.
   封装：通过访问控制隐藏实现细节
2. 2.
   继承：允许创建派生类，重用代码
3. 3.
   多态：通过虚函数实现运行时多态
4. 4.
   抽象：通过纯虚函数创建抽象类
5. 5.
   运算符重载：使自定义类型行为类似于内置类型
6. 6.
   模板：实现泛型编程
*/