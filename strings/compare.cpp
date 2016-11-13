// String comparator
// We want what strcmp does but with a twist, if there is a 
// number we want to compare the numeric values
// E.g. s1 = foo123 and s2 = foo24, then s1 > s2
#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

// tokenize digits vs non-digits
// Returns last index of token (exclusive)
int getToken(const string &s, const int start)
{
    if (s.size() <= start)
    {
        return -1;
    }

    int i = start;
    bool first = isdigit(s[i]) ? true : false;

    while (++i < s.size())
    {
        bool curr = isdigit(s[i]) ? true : false;
        if (curr != first)
        {
            return i;
        }
    }

    return i;
}

// return 0 if both are equal
// 1 if 1st string > 2nd string
// -1 if 1st < 2nd
int crazycompare(const string &s1, const string &s2) {

    if (s1.empty() && s2.empty()) {
        return 0;
    }
    else if (s1.empty()) {
        return -1;
    }
    else if (s2.empty()) {
        return 1;
    }

    int sind1 = 0;
    int end1  = 0;
    int sind2 = 0;
    int end2  = 0;

    string sm1;
    string sm2;

    while (1)
    {
        end1 = getToken(s1, sind1);
        end2 = getToken(s2, sind2);

        sm1 = s1.substr(sind1, 
            (end1 == s1.size()) ? string::npos :
            end1 - sind1);

        sm2 = s2.substr(sind2, 
            (end2 == s2.size()) ? string::npos :
            end2 - sind2);

        if (isdigit(s1[sind1]) && isdigit(s2[sind2]))
        {
            const int n1 = atoi(sm1.c_str());
            const int n2 = atoi(sm2.c_str());

            if (n1 < n2)
            {
                return -1;
            }
            else if (n1 > n2)
            {
                return 1;
            }
            // keep going
        }
        else if (!isdigit(s1[sind1]) && !isdigit(s2[sind2]))
        {
            int c = strcmp(sm1.c_str(), sm2.c_str());
            if (c < 0)
            {
                return -1;
            }
            else if (c > 0)
            {
                return 1;
            }
            // keep going
        }
        else 
        {
            if (isdigit(s1[sind1]))
            {
                return -1;
            }
            else
            {
                return 1;
            }
        }

        sind1 = end1;
        sind2 = end2;

        if (end1 == s1.size() && end2 == s2.size())
        {
            return 0;
        }
        else if (end1 == s1.size())
        {
            return -1;
        }
        else if (end2 == s2.size())
        {
            return 1;
        }
    }

    return 0;
}

int main(int argc, char **argv) {

    string s1 = argv[1];
    string s2 = argv[2];

    cout << crazycompare(s1, s2) << endl;
    return 0;
}
