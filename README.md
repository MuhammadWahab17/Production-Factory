# Production-Factory
If you are using windows change the libarary for sleep function
#include<Windows.h> for window
In Visual Studio system time is displayed by following code
void time() {
    time_t now = time(NULL);
    //char *str = asctime(localtime(&now));
    tm now_tm = {};
    char str[26] = {};
    localtime_s(&now_tm, &now);
    asctime_s(str, 26, &now_tm);
    cout << str<<endl;
}
use of ctime() function in VS is not allow so you can replace that line by this calling this function ...
