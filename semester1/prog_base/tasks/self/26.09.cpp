#include <iostream>
using namespace std;
int main()
{
    int h,m, code, tarif;
cout << "enter hours: ";
cin >> h;
cout << "enter minutes: ";
cin >> m;
cout << "enter code: ";
cin >> code;
m+=h*60;
float answer;
    switch(code)
{
case 44:
{
answer=0.44*m;
break;
}
case 666:
{
 answer=0;
break;
}
case 1:
{
answer=m*30;
break;
}
default:
{
answer=m;
}
}
cout << "answer: " << answer;
}
