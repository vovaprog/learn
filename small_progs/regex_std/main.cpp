#include <iostream>
#include <regex>

using namespace std;

int main()
{
    try{
        const char *text = "key1:value1\r\nkey2:value2\r\nkey3:value3\r\n";

        regex rex("([A-Za-z0-9]+:[A-Za-z0-9]+");

        if(regex_match(text, rex))
        {
            cout <<"match\n";
        }
        else
        {
            cout <<"NOT matched\n";
        }
    }catch(regex_error err){
        cout << err.what() << endl;

    }

    return 0;
}


