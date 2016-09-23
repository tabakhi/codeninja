// 7.5 Compute all mnemonics for a phone number
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sys/time.h>
#include <unordered_map>

using namespace std;

void makeMap(vector< vector<char> > &map)
{
    vector<char> str;
    vector<char> str2;

    str.push_back('a');
    str.push_back('b');
    str.push_back('c');

    str2.push_back('p');
    str2.push_back('q');
    str2.push_back('r');
    str2.push_back('s');

    map.push_back(str);
    for (size_t i = 0; i < 7; i++)
    {
        if (i == 4)
        {
            map.push_back(str2);
        }
        else if (i == 6)
        {
            str2[0] += 7;
            str2[1] += 7;
            str2[2] += 7;
            str2[3] += 7;
            map.push_back(str2);
        }
        else
        {
            str[0] += 3;
            str[1] += 3;
            str[2] += 3;
            map.push_back(str);
        }
    }

    for (size_t i = 0; i < map.size(); i++)
    {
        for (size_t j = 0; j < map[i].size(); j++)
        {
            cout << map[i][j] << ",";
        }
        cout << endl;
    }
}

void 
printNemonics(const string &number,
        string &str,
        size_t level, 
        vector< vector<char> > &map)
{
    if (level == number.size())
    {
        cout << str << endl;
        return;
    }

    int digit = number[level] - '0';
    assert(digit >= 2);
    assert(digit <= 9);

    for (size_t j = 0; j < map[digit-2].size(); j++)
    {
        str += map[digit-2][j];
        printNemonics(number, str, level+1, map);
        str.erase(str.size()-1);
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cerr << "Please provide phone number" << endl;
        return 1;
    }

    string number = argv[1];
    vector< vector<char> > map;
    makeMap(map);

    string str;
    printNemonics(number, str, 0, map);
    return 0;
}
