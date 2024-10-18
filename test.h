#include "vec.h"
#include <iostream>
#include <string>
using namespace std;

struct student{           //自定义类
    int id;
    char name[20];
    char major[20];
};

ostream& operator<<(ostream &os,student &stu){
    os<<stu.id<<' '<<stu.name<<' '<<stu.major;
    return os;
} 
istream& operator>>(istream &is,student &stu){
    is>>stu.id>>stu.name>>stu.major;
    return is;
} 
void test_int();
void test_string();
void test_struct();
void test_2D(){
    Vector<Vector<int>> asa(3);
    asa.push(9);
    asa[0].push(123);
    cout<<asa;

    Vector<Vector<int>> sas(3);
    cin>>sas;
    cout<<sas<<'\n';
    cout<<sas[1];
}

void test_string(){
    Vector<string> ooo(3);//测试string下的push功能和构造函数
    cout<<"input your string. Finish this input with pressing space and enter keys in order \n";
    cin>>ooo;               //输入运算符重载
    ooo.push("aaa");
    ooo.push("bbb");
    ooo.push("ccc");
    cout<<ooo<<'\n';            //输出运算符重载
    
    Vector<string>AAA(6,"oooo");//测试string下的另一构造函数
    cout<<AAA<<'\n';

    Vector<string>BBB(AAA);//测试复制构造函数
    cout<<BBB<<'\n';
    
    cout<<"operator+\n";
    cout<< ooo+AAA;       //加法测试,预期结果是字符串变长

    ooo.swap(AAA);
    cout<<ooo<<'\n';
    cout<<AAA<<'\n';

    try{
        cout<<ooo[1]<<endl;
        cout<<ooo[10];     //下标越界异常处理
    }
    catch(char const *&as){
        cout<<as<<'\n';        
    }
}

void test_struct(){
    student stu_1={123,"jack","Computer"};
    student sut_2={321,"rose","Literature"};
    Vector<student> stu(3);
    stu.push(stu_1);
    stu.push(sut_2);
    cout<<"please input\n";
    cin>>stu;
    cout<<stu<<endl;
    
    Vector<student> copy(stu);
    cout<<copy<<'\n';

    cout<<stu[1];//下标测试

}




void test_int() {
    // 测试默认构造函数
    Vector<int> vecDefault;
    cout << "Default Vector: ";
    for (int i = 0; i < 10; ++i) {
        vecDefault.push(i+1);
    }
    cout << vecDefault << endl;
    // 测试带初始容量的构造函数
    Vector<int> vecCapacity(5);
    for (int i = 0; i < 5; ++i) {
        vecCapacity.push(i * 10);
    }
    cout << "Vector with capacity 5: " << vecCapacity << endl;
    
    cin.get();
    // 测试带初始容量和值的构造函数
    Vector<int> vecWithValues(3, -1);
    cout << "Vector with 3 elements initialized to -1: " << vecWithValues << endl;

    cin.get();
    // 测试拷贝构造函数
    Vector<int> vecCopy(vecWithValues);
    cout << "Copied Vector: " << vecCopy << endl;

    cin.get();
    // 测试赋值运算符
    vecWithValues = vecCapacity;
    cout << "vecWithValues (after assignment from vecCapacity): " << vecWithValues << endl;

    cin.get();
    // 测试插入功能
    vecDefault.insert(5, 99);
    cout << "vecDefault after inserting 99 at position 5: " << vecDefault << endl;

    cin.get();
    // 测试插入多个元素的功能
    vecDefault.insert(1, 200, 2);
    cout << "vecDefault after inserting 2 elements of 200 starting from position 1: " << vecDefault << endl;

    cin.get();
    // 测试删除功能
    vecDefault.Delete(4, 6);
    cout << "vecDefault after deleting element from position 4: " << vecDefault << endl;

    cin.get();
    //测试交换功能
    cout << "Before swap:\n";
    cout << "vecDefault: ";
    for (int i = 0; i < vecDefault.Size(); ++i) {
               cout << vecDefault[i] << " ";
    }
    cout << "\nvecCapacity: ";
    for (int i = 0; i < vecCapacity .Size(); ++i) {
        cout << vecCapacity[i] << " ";
    }

    cout<<endl;
    cout << "vec1 capacity before swap: " << vecDefault.Capacity() << endl;
    cout << "vec2 capacity before swap: " << vecCapacity .Capacity() << endl;
    cout << "vec1 size before swap: " << vecDefault.Size() << endl;
    cout << "vec2 size before swap: " << vecCapacity.Size() << endl;

    vecDefault .swap(vecCapacity);
    cout << "\nAfter swap:\n";
    cout << "vecDefault: ";
    for (int i = 0; i < vecDefault.Size(); ++i) {
        cout << vecDefault[i] << " ";
    }
    cout << "\nvecCapacity: ";
    for (int i = 0; i < vecCapacity.Size(); ++i) {
        cout << vecCapacity[i] << " ";
    }

    cout<<'\n';
    cout << "vec1 capacity after swap: " << vecDefault.Capacity() << endl;
    cout << "vec2 capacity after swap: " << vecCapacity .Capacity() << endl;
    cout << "vec1 size after swap: " << vecDefault.Size() << endl;
    cout << "vec2 size after swap: " << vecCapacity.Size() << endl;

    cin.get();
    // 测试下标越界异常
    try {
        cout << "Element at index 15: " << vecDefault.at(15) << endl;
    }
    catch (const char *e) {
        cout << "Exception caught: " << e << endl;
    }

    cin.get();
    // 测试容量调整
    cout << "vecDefault capacity before free2: " << vecDefault.Capacity() << endl;
    vecDefault.free2();
    cout << "vecDefault capacity after free2: " << vecDefault.Capacity() << endl;

    cin.get();
    // 测试pop功能
    cout << "Element popped: " << vecDefault.at(vecDefault.Size()-1) << endl;
    vecDefault.pop();
    cout << "vecDefault after popping: " << vecDefault << endl;

    cin.get();
    // 测试友元输入运算符
    cout << "Enter elements for vecInput (end with newline):" << endl;
    Vector<int> vecInput;
    cin >> vecInput;
    cout << "Input Vector: " << vecInput<<'\n';

    //测试加法
    try{
        cout<<"vecDefault size "<<vecDefault.Size()<<'\n';
        cout<<"vecCopy size "<<vecCopy.Size()<<'\n';
        cout<<"vecDefault+vecCopy";
        cout<<vecDefault + vecCopy;
    }
    catch(int a){
            cout<<"\ncant add two vector with different size"<<std::endl;
    }

    //测试
    try{
        cout<<"vecDefault capacity"<<vecDefault.Capacity()<<'\n';
        vecDefault.reserve(12);
        cout<<"after reserve      "<<vecDefault.Capacity()<<endl;
    }
    catch(char *p){
        cout<<p;
    }
}
