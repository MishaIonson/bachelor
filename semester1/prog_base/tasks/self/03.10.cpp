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
    switch(day)
    {
        case 1:
        case 8:
        case 15:
        case 22:
        case 29:
        {
            answer = "wednesday";
            break;
        }
        case 2:
        case 9:
        case 16:
        case 23:
        case 31:
        {
            answer = "thursday";
            break;
        }
        case 3:
        case 10:
        case 17:
        case 24:
        {
            answer = "friday";
            break;
        }
        case 4:
        case 11:
        case 18:
        case 25:
        {
            answer = "saturday";
            break;
        }
        case 5:
        case 12:
        case 19:
        case 26:
        {
            answer = "sunday";
            break;
        }
            case 6:
            case 13:
            case 20:
            case 27:
            {
                answer = "monday";
                break;
            }
            case 7:
            case 14:
            case 21:
            case 28:
            {
                answer="tuesday";
                break;
            }
    }
    cout << answer;
}
