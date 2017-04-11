#include <iostream>
#include <regex>

using namespace std;

void testHttpRequest();
void testHttpRequestStdRegex();
void testHttpRequestBoostRegex();
void testHttpRequestPcre();
void testHttpRequestPerformance();
void testStdRegexPerformance();
void testBoostRegexPerformance();
void testPcreRegexPerformance();

void regex_test1()
{
    try {
        const char *text1 = "key1:value1";

        // by default perl regular expressions
        regex rex("([A-Za-z0-9]+):([A-Za-z0-9]+)");

        // regex_match matches whole input string (like ^...$)
        if(regex_match(text1, rex))
        {
            cout <<"regex_match ok\n";
        }
        else
        {
            cout <<"regex_match NO\n";
        }

        const char *text2 = "key1:value1\r\nkey2:value2\r\nkey3:value3\r\n";

        // regex_search can find substring
        if(regex_search(text2, rex))
        {
            cout <<"regex_search ok\n";
        }
        else
        {
            cout <<"regex_search NO\n";
        }

        cmatch match;

        const char *text3 = text2;

        while (regex_search(text3, match, rex))
        {
            for (auto x:match)
            {
                std::cout << "[" << x << "] ";
            }
            cout << endl;

            // can access group by index
            cout << match[1] << endl;

            text3 = match.suffix().first;
        }

    } catch (regex_error err) {
        cout << "regex_error: " << err.what() << endl;
    }
}


int main()
{
    //regex_test1();
    //testHttpRequest();
    //testHttpRequestStdRegex();
    //testHttpRequestBoostRegex();
    //testHttpRequestPcre();
    testHttpRequestPerformance();
    //testStdRegexPerformance();
    testBoostRegexPerformance();
    testPcreRegexPerformance();

    return 0;
}


