#include <iostream>
#include <vector>
#include "string"
#include<algorithm>
using namespace std;
class caculation{              //定义一个类caculation，三个数分别为运算时第一个第二个数和答案
public:
    void  add();
    void  sub();
    void  mul();
    void  div();
    void  sam();
    void  putin (void);
    void  putout ();
    int comnum();
private:
    vector <int> num1;
    vector <int> num2;
    vector <int> anwser;
};
bool mainprogram();
int main()
{    
    while (mainprogram(  )){}     //避免主程序的递归调用，选择在main函数里面循环来达到多次计算的效果
    return 0;
}


bool   mainprogram()  //定义主程序
{
    int n;
    cout<<"please choose your operation caculation"<<"\n"<<"add (1)  sub (2)  mul(3)  div (4)  sam(5)  end(0)"<<endl;
    cin>>n;
    caculation Cal;
    switch(n){
                 case 1:Cal.add();
                 case 2:Cal.sub();
                 case 3:Cal.mul();
                 case 4:Cal.div();
                 case 5:Cal.sam();
                 case 0:return false ;
                 default:{
                          cout<<"ERROR";
                 }
               }
    return true;
}


void caculation:: putin()  //定义输入程序，用来得到用于计算的两个数
{
    string s1,s2;
    cout<<"please enter your first number:"<<"\n"<<endl;
    cin>>s1;
    if(s1[0]=='-')num1.push_back(1);           //用字符串得到输入的值，并用vector的第一位作为符号位
    else num1.push_back(0);
    int i;
    for(i=s1.length()-1;i>0;i--)
    {
        num1.push_back(s1[i]-'0');
    }
    if(s1[0]!='-')num1.push_back(s1[0]);
    cout<<"please enter your second  number:"<<"\n"<<endl;
    cin>>s1;
    if(s2[0]=='-')num2.push_back(1);
    else num2.push_back(0);
    for(i=s1.length()-1;i>0;i++)
    {
         num2.push_back(s2[i]-'0');
    }
    if(s2[0]!='-')num2.push_back(s2[0]);
    return ;
}
void caculation:: putout()
{
    cout<<"anwser is :"<<"\n"<<endl;
    int i;
    vector<int>::iterator p1=anwser.begin();
    if(*p1==1)
    {
        cout<<"-"<<endl;
    }
    i=anwser.size()-1;
    for(;i>0;i--)
    {
        cout<<anwser[i]<<endl;
    }
    cout<<"\n"<<endl;
}


void caculation::add()  //定义加法运算, 此处遍历时使用迭代器遍历，也可以用数组遍历
{
    putin();
    auto s1=num1.begin();   //定义迭代器，使它的位置指向第一个符号位
    auto s2=num2.begin();
    int i=0,n=0;
    if(*s1==*s2)
    {
        anwser.push_back(*s1);
        for(;s1!=num1.end()||s2!=num2.end(); )
        {
            s1++;
            s2++;
            n=*s1+*s2+i;
            i=n/10;
            n=n%10;
            anwser.push_back(n);
        }
        if(num1.size()==num2.size())
        {
            if(i)anwser.push_back(i);
        }
        else{
            if(num1.size()>num2.size())
            {
                for( ;s1!=num1.end(); )
                {
                    s1++;
                    n=*s1+n;
                    i=n/10;
                    n=n%10;
                    anwser.push_back(n);
                }
            }else {
                for( ;s2!=num2.end();)
                {
                    s2++;
                    n=*s2+n;
                    i=n/10;
                    n=n%10;
                    anwser.push_back(n);
                }
            }
        }
    } 
    else{
        if(*s1==0)
        {
            *s1=1;
            num1.swap(num2);
            sub();
        }
        else 
        {
            *s2=1;
            sub();
        }
    }
    putout();
}


int caculation::comnum()   //比较两个大数的绝对值，用于减法，除法和取膜运算。
{
    putin();
    if(num1.size()>num2.size())return 1;
    if(num1.size()<num2.size())return 0;
    int i=num1.size()-1;
    for(; i>0;i--)
    {
        if(num1[i]<num2[i])return 0;
        if(num1[i]>num2[i])return 1;
    }
    return 2;
}


void caculation::sub()
{
     putin();
     if(num1[0]!=num2[0])
     {
        if(num1[0]==0)
        {
            num2[0]=0;
            add();
        }else 
        {
             num2[0]=1;
            add();
        }
    }
    int i=comnum();
    if(i==2)
    {
        anwser.push_back(0);
        anwser.push_back(0);
        return ;
    }
    int n=0,t=0,s=0;
    if(i)
    {
        anwser.push_back(num1[n]);
        for(n++ ;n<num2.size() ;n++ )     //先判断两个数的大小，并用大数减去小数
        {
            t=num1[n]-num2[n]+s;
            if(t<0)
            {
                s=-1;
                t+=10;
            }
            else s=0;
            anwser.push_back(t);
        }
        for( ;n<num1.size() ;n++)
        {
            t=num1[n]+s;
            if(t<0)
            {
                s=-1;
                t+=10;
            }
            else s=0;
            anwser.push_back(t);
    }
    }
    else 
    {
       num1.swap(num2);    //若前数比后数小，交换两个数的值即可
       sub();
       anwser[0]=!anwser[0];
    }
    putout();
}
void caculation::mul()
{
    anwser.assign((num1.size()-1)+(num2.size()-1)+1,0);   //规定最大位数，计算完之后根据0数量的再减
    int s=num1[0]^num2[0];
    anwser.push_back(s);
    int n1=1,n2=1,p=0,t=0;
    for(;n1<num1.size();n1++)
    {
        for(;n2<num2.size();n2++)
        {
            p=num1[n1]*num2[n2]+s;
            s=p/10;
            s=s%10;
            anwser[n1+n2-1]=s;
        }
    }
    if((*anwser.end())==0)anwser.pop_back();          //因为最大位数不是两个数字的位数之和就是和减一，所以只用判断那个可能的最高位即可
}
void caculation::sam()
{
    int n=comnum();                       //先判断两个数字的大小，如果第一个数小于第二个数直接返回0 如果相等返回1。
    
}
