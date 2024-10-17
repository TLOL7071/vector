#include<iostream>
#include <stdexcept>
#ifndef vec_h
#define vec_h
using namespace std;

template<typename type>
class Vector;

template<typename ty>
ostream& operator<<(ostream& os, Vector<ty>& vec);

template<typename ty>
ostream& operator<<(ostream& os, Vector<ty>&& vec);

template<typename ty>
istream& operator>>(istream& os, Vector<ty>& vec);

template <typename type>
class Vector
{
private:
    type* p;                                    //头
    int size;                                 //储存大小
    int capacity;                               //容量
public:
    
    void reserve(int n);
    Vector();                                  //构造函数1  将capacity设为15,p指向type类型的数组头
    Vector(int n);                              //构造函数2  将capacity设为n*2，
    Vector(int n, type m);                      //构造函数3  将capacity设为n*2,将前n个内容赋为type m
    Vector(Vector<type>& a);                    //复制构造函数 利用copy函数复制数据，但具体支持的数据类型不清楚，基本的int double等应该是可以的，但不知道struct 和class 效果怎么样//al:对class也有用(english version:Also applicable to class type)
    
    explicit Vector(type* p1, type* p2);         //将type类型数组的p1和p2之间的数据复制，两者顺序可以颠倒，还有这是要显式调用的
    ~Vector();
    bool empty();                               //判断是否为空，空返回true
    int Capacity();                             //返回capacity
    int Size();
    void pop();//弹出最后一个数据成员，希望对这个函数重写一遍，结合capacity，size，          //al:试着完成了(english version:have tried to solve the problem.)
    void push(const type &a);                          //将type a加入vector的末尾， 当容量capacity不足以存储时，扩容，希望对扩容功能加以检测   //al:加了一个检测，但不知道你想在哪里检测。
    type at(int i);//返回vector中第i位的数据，对i越界的异常处理没有写完，希望补全

    Vector& operator=(const Vector<type>& vec); //赋值运算符号，希望检测
    type& operator[](int i); //throw(char *);//下表运算符，但没有越界处理//al:加入了越界处理
    Vector operator+(const Vector<type>& vec) throw(int);
    //加法用算符重载，但是设计有问题。希望再写一个
    Vector operator++(int);//希望加入对数据类型的判断，以避免数据不满足++运算操作
    Vector& operator++(); 

    void free2();                               //将容量变为size大小，及舍弃未利用的空间
    void insert(int position, type n);
    void insert(int position, type n, int m);
    void Delete(int n);
    void Delete(int n, int m);
    void swap(Vector<type>& vec);
    friend ostream& operator << <>(ostream& os, Vector<type>& vec);
    friend ostream& operator << <>(ostream& os, Vector<type>&& vec);
    friend istream& operator >> <>(istream& is, Vector<type>& vec);//以回车为结束标记，空格为区分符号
};
template <typename type>
istream& operator>>(istream& is, Vector<type>& vec);

template <typename type>
ostream& operator<<(ostream& os, Vector<type>& vec);


template <typename type>
Vector<type> ::Vector()             //构造函数1
{
    size = 0;
    capacity = 15;
    p = new type[capacity]();
}
template <typename type>
Vector<type>::Vector(int n)           //���캯��2
{
    size = 0;
    p = new type[n * 2];
    capacity = n * 2;
}
template <typename type>                //���캯��3
void Vector<type>::reserve(int n)
{
    if (n < 0)
        throw "n is too small!\n";
    this->capacity +=n;
    type *temp = new type[capacity];
    for (int i = 0; i < this->size; i++)
    {
        temp[i] =this->p[i];
    }
    delete[]this->p;
    this->p = temp;
}
template <typename type>                //���캯��4
Vector<type> ::Vector(int n, type m)
{
    p = new type[n * 2];
    //memset(p,)
    fill(p, p + n, m);
    capacity = n * 2;
    size = n;
}
template<typename type>                 //�������캯��6
Vector<type>::Vector(Vector<type>& a)
{
    p = new type[a.size * 2]();
    //copy(a.p, a.p + a.size, p);                        //copy是浅拷贝，这里用type类型对应的深拷贝比较好
    for (int i = 0; i < a.size; i++)
    {
        p[i] = a.p[i];                                   //对应type类型重载=来实现深拷贝
    }
    size = a.size;
    capacity = a.size * 2;
}
template<typename type>                 //���캯��7
Vector<type>::Vector(type* p1, type* p2)
{

    if ((p2 - p1) >= 0)
    {
        p = new type[(p2 - p1) * 2]();
        size = p2 - p1;
        capacity = (p2 - p1) * 2;
        for (int i = 0; i < p2 - p1; i++)
            p[i] = p1[i];
    }
    else
    {
        p = new type[(p1 - p2) * 2]();
        capacity = (p1 - p2) * 2;
        size = p1 - p2;
        for (int i = 0; i < p1 - p2; i++)
        {
            p[i] = p2[i];
        }
    }
}
template<typename type>                 //��������
Vector<type>::~Vector()
{
    delete[] this->p;
}
template<typename type>                 //�ж�vector�Ƿ�Ϊ��
bool Vector<type>::empty()
{
    if (size == 0)
        return true;
    else
        return false;
}
template<typename type>                 //����capacity
int Vector<type>::
Capacity()
{
    return capacity;
}
template<typename type>                 //���ص�ǰ�洢����
int Vector<type>::Size()
{
    return this->size;
}
template<typename type>                 //ɾ�����һ��Ԫ������ǰvectorΪ�գ���ӡerror
void Vector<type>::pop()
{
    if (this->size >= 1)
    {
        if constexpr (!std::is_trivially_destructible<type>::value) {
            p[size - 1].~T();  //若type为类弹出后执行它的析构函数(english version:If the type is a class, its destructor is executed after popping.)
        }
        this->size--;
        if (size <= capacity / 4) {
            capacity /= 2;
            type* tempt = new type[this->capacity];
            for (int i = 0; i < this->size; i++)
            {
                tempt[i] = this->p[i];
            }
            delete[]p;
            p = tempt; 
        }   
    }
    else{
        cout << "error";
    }
}
template<typename type>                 //��˳�����Ԫ�أ�
void Vector<type>::push(const type &a)
{
    if (this->size == this->capacity)
    {
        capacity *= 2;
        type* tempt = new(std::nothrow) type[this->capacity];
        if (!tempt)
        {
            throw std::runtime_error("Memory allocation failed");
        }
        for (int i = 0; i < this->size; i++)
        {
            tempt[i] = this->p[i];
        }
        delete[]p;
        p = tempt;
    }
    *(p + this->size) = a;
    this->size++;
}
template<typename type>                 //����vector���±�λ��Ԫ�أ����������ޣ����� 0X16
type Vector<type>::at(int i)
{
    if (i >= size)
    {
        throw "yuejie!!!";                //*******加入当i越界时，触发异常
    }
    return p[i];
}
template<typename type>                 //��=��������أ�ʵ��vec1=vec2��ֵ
Vector<type>& Vector<type>::  operator=(const Vector<type>& vec)
{
    if(this == &vec)
         return *this;
    type* temp = new type[vec.capacity];
    for (int i = 0; i < vec.size; ++i) {
        temp[i] = vec.p[i];
    }
    delete[] this->p;
    p = temp;
    this->size = vec.size;
    this->capacity = vec.capacity;
    return *this;
}
template<typename type>             //��[]���أ�ʵ��vec[i]���±�Ϊi
type& Vector<type>:: operator[](int i)//throw(char *)
{
    if(i>=size||i<0) throw ("yue jie !!!");       //al:新增越界访问异常处理(english version:Add out-of-bounds access exception handling.)
    return this->p[i];
}
template<typename type>             //��+���أ�ʵ��vec1+vec2����vec3�����и�Ԫ��Ϊ��Ӻ���
Vector<type> Vector<type>:: operator+(const Vector<type>& vec) throw(int)
    {
        Vector<type> temp(*this);
        if(this->size!=vec.size)
            throw(1);
        for(int i=0;i<vec.size;i++)
        {
            temp[i]+=vec.p[i];
        }
        return temp;
}
template<typename type>                     //�Ժ�׺�����++���أ�ʵ�ַ���++ǰ�Ķ���֮���ٶԲ�������ȫ��Ԫ�ؼ�1
Vector<type> Vector<type>:: operator++(int)//��Ӽ�
    {
        Vector<type> tp(*this);
        static_assert(std::is_arithmetic<type>::value,"Vector element must be of arithmetic type" );
        for(int i=0;i<this->size;i++)
        {
            this->p[i]++;
        }
        return tp;
    }
template<typename type>                     //��ǰ׺�����++���أ�ʵ���ȶԲ�������ȫ��Ԫ�ؼ�1���󷵻�++��Ķ���
Vector<type>& Vector<type>:: operator++()//ǰ�Ӽ�
{
    for (int i = 0; i < this->size; i++)
    {
        this->p[i]++;
    }
    return *this;
}
template<typename type>                     //ͨ������vector.size��С�����飬��ԭ����Ǩ�ƣ���delete��ԭ������Ŀռ�
void Vector<type>::free2()                 //��ɶ�size��ռ�����
{
    type *temp = new type[this->size];
    for (int i = 0; i < this->size; i++)
    {
        temp[i] =this->p[i];
    }
    delete[]this->p;
    this->p = temp;
    this->capacity=this->size;
}
template<typename type>                 //��ָ��λ��position����nԪ��
void Vector<type>::insert(int position, type n)
{
    if (this->size == this->capacity)
    {
        capacity *= 2;
        type* tempt = new type[this->capacity];
        for (int i = 0; i < this->size; i++)
        {
            tempt[i] = this->p[i];
        }
        delete[]p;
        p = tempt;
    }
    for (int i = this->size; i > position; i--)
    {
        this->p[i] = this->p[i - 1];
    }
    this->p[position] = n;
    this->size++;
}
template<typename type>                     //��positionλ�ò���m��nԪ��
void Vector<type>::insert(int position, type n, int m)
{
    if ((this->size + m) >= this->capacity)
    {
        do
        {
            capacity *= 2;
        } while ((this->size + m) >= this->capacity);
        type* tempt = new type[this->capacity];
        for (int i = 0; i < this->size; i++)
        {
            tempt[i] = this->p[i];
        }
        delete[]p;
        p = tempt;
    }
    for (int i = this->size + m - 1; i >= position + m; i--)
    {
        this->p[i] = this->p[i - m];
    }
    for (int i = position; i < position + m; i++)
        this->p[i] = n;
    this->size += m;

}
template<typename type>             //ɾȥn�±�����Ԫ��
void Vector<type>::Delete(int n)
{
    this->size--;
    for (int i = n; i < this->size; i++)
    {
        this->p[i] = this->p[i + 1];
    }
    this->p[size] = 0;
}
template<typename type>                 //ɾȥnС�괦�����n��Ԫ��
void Vector<type>::Delete(int n, int m)
{//[n,m]����
    for (int i = 0; i < this->size - m - 1; i++)
        this->p[n + i] = this->p[m + i + 1];

    for (int i = this->size - 1; i >= this->size - 1 - m + n; i--)
    {
        this->p[i] = 0;
    }
    this->size -= m - n + 1;

}
template<typename type>            //ʵ������vector�����ݻ���
void Vector<type>::swap(Vector<type>& vec)
{
    type* t = this->p;
    this->p = vec.p;
    vec.p = t;
    int tt;
    tt = this->size;
    this->size = vec.size;
    vec.size = tt;
    tt = this->capacity;
    this->capacity = vec.capacity;
    vec.capacity = tt;
}
template <typename ty>            //��<<���أ�ʹcout�����vector�������
ostream& operator<<(ostream& os, Vector<ty>& vec)
{
    for (int i = 0; i < vec.size; i++)
    {
        cout << vec.p[i];
        cout << ' ';
    }
    return os;
}
template <typename ty>           //��>>���أ���ʹ��cin���vector����������
istream& operator >>(istream& is, Vector<ty>& vec)
{
    int i;
    cin.clear();
    ty temp;
    for (i = 0;i<vec.capacity; i++)
    {   
        cin>>temp;
        vec.push(temp);
        if(cin.peek()=='\n')
            break;
        
    }
    return is;
}

istream& operator >>(istream& is, Vector<string>& vec)
{
    int i;
    cin.clear();
    string temp;
    for (i = 0;i<vec.Capacity(); i++)
    {   
        getline(cin,temp,' ');
        vec.push(temp);
        if(cin.peek()=='\n')
            break;
    }
    return is;
}

template <typename ty>            //��<<���أ�ʹcout�����vector�������
ostream& operator<<(ostream& os, Vector<ty>&& vec)
{
    for (int i = 0; i < vec.size; i++)
    {
        cout << vec.p[i];
        cout << ' ';
    }
    return os;
}
#endif