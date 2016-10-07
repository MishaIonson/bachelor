#include <iostream>
#include <string>
using namespace std;

int main()
{
    int day;
    string answer;
    cin >> day;
    int p;
    p = day % 7;
    switch(p)
    {
        case 1:
        {
            answer = "wednesday";
            break;
        }
        case 2:
        {
            answer = "thursday";
            break;
        }
        case 3:
        {
            answer = "friday";
            break;
        }
        case 4:
        {
             answer = "saturday";
        }
        case 5:
        {
            answer = "sunday";
            break;
        }
        case 6:
        {
            answer = "monday";
            break;
        }
        case 0:
        {
            answer = "tuesday";
            break;
        }
    }
    cout << answer;
}
