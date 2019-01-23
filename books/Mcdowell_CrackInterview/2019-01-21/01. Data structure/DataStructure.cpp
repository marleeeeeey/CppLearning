// DataStructure.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <algorithm>
#include <cassert>
#include <vector>
#include <map>
#include <sstream>

bool isAllSymbolsAreDifferent(std::string msg)
{
    std::sort(msg.begin(), msg.end());
    for (unsigned i = 1; i < msg.size(); i++)
    {
        if (msg[i - 1] == msg[i])
            return false;
    }
    return true;
}

bool isAllSymbolsAreDifferent2(const std::string & msg)
{
    std::vector<char> char_set(128);
    for (unsigned i = 0; i < msg.size(); i++)
    {
        if (char_set[msg[i]] == 1)
            return  false;
        else
            char_set[msg[i]] = 1;
    }
    return true;
}

void task_1_1()
{
    assert(isAllSymbolsAreDifferent("qwert") == true);
    assert(isAllSymbolsAreDifferent("") == true);
    assert(isAllSymbolsAreDifferent("qwtert") == false);
    assert(isAllSymbolsAreDifferent("    ") == false);    

    assert(isAllSymbolsAreDifferent2("qwert") == true);
    assert(isAllSymbolsAreDifferent2("") == true);
    assert(isAllSymbolsAreDifferent2("qwtert") == false);
    assert(isAllSymbolsAreDifferent2("    ") == false);
}

bool isPermutation(std::string s1, std::string s2)
{
    if (s1.size() != s2.size())
        return false;

    std::sort(s1.begin(), s1.end());
    std::sort(s2.begin(), s2.end());
    if (s1 == s2)
        return true;

    return false;
}

void task_1_2()
{
    assert(isPermutation("qwert", "qwert") == true);
    assert(isPermutation("qwert", "qwera") == false);
    assert(isPermutation("qwert", "trewq") == true);
    assert(isPermutation("qwert", "treqw") == true);
    assert(isPermutation("", "") == true);
    assert(isPermutation("123", "") == false);
    assert(isPermutation("123", " ") == false);
}

bool isPalindromPermutation(const std::string & str)
{
    std::map<char, int> charCount;
    for (auto ch : str)
    {
        charCount[ch] += 1;
    }
    bool isOddFound = false;
    for (const auto & p : charCount)
    {
        if(p.first == ' ')
            continue;

        if (p.second % 2 == 1)
        {
            if(isOddFound == false)
            {
                isOddFound = true;
            }
            else
            {
                return false;
            }
        }
    }
    return true;
}

void task_1_4()
{
    assert(isPalindromPermutation("qweqwea") == true);
    assert(isPalindromPermutation("qweasd") == false);
    assert(isPalindromPermutation("qw eq wea") == true);
    assert(isPalindromPermutation("q we asd  ") == false);
    assert(isPalindromPermutation("") == true);
}

bool isOneMOdification(const std::string & str1, const std::string & str2)
{
    const std::string & longStr = str1.size() >= str2.size() ? str1 : str2;
    const std::string & shortStr = str1.size() < str2.size() ? str1 : str2;

    bool hasInconsistent = false;
    bool isSameSize = longStr.size() == shortStr.size();
    
    int s = 0;
    int l = 0;
    for ( ; s < shortStr.size() && l < longStr.size(); )
    {
        if(shortStr[s] != longStr[l])
        {
            if (hasInconsistent == true)
                return false;

            hasInconsistent = true;
                
            if (!isSameSize)
            {
                l++;
                continue;
            }
        }
        l++;
        s++;
    }
    return true;
}

void task_1_5()
{
    assert(isOneMOdification("pale", "ple") == true);
    assert(isOneMOdification("pales", "pale") == true);
    assert(isOneMOdification("pale", "bale") == true);
    assert(isOneMOdification("pale", "bake") == false);
}

std::string getShortString(const std::string & original)
{
    if (original.size() < 3)
        return original;

    std::string result;
    result.push_back(original.at(0));
    int counter = 1;
    for (int i = 1; i < original.size(); i++)
    {
        if(counter == 0)
        {
            result.push_back(original.at(i));
            counter++;
        }
        else if(result.back() == original.at(i)) // REMEMBER_THIS: std::string::back() to access for last element
        {
            counter++;
        }
        else
        {
            // REMEMBER_THIS: add number to string.
            std::stringstream ss;
            ss << counter;
            result += ss.str() + original.at(i);
            counter = 1;
        }
    }
    
    // REMEMBER_THIS: forget to add last counter to the end of the string.
    std::stringstream ss;
    ss << counter;
    result += ss.str();
    
    if (result.size() > original.size())
        return original;

    return  result;
}

void task_1_6()
{
    assert(getShortString("aabcccccaaa") == "a2b1c5a3");
    assert(getShortString("aggggaaabcccsdfaccaaa") != "a2b1c5a3");
    assert(getShortString("") == "");
    assert(getShortString("a") == "a");
    assert(getShortString("ab") == "ab");
    assert(getShortString("abc") == "abc");
}

void printMatrix(int * matrix, int row, int col)
{
    for (int r = 0; r < row; r++)
    {
        for (int c = 0; c < col; c++)
        {
            std::cout << matrix[r*col + c] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

void transformMatrix(int * m, int s)
{
    for (int d = 0; d < (s-1)/2; d++)
    {
        int z = s - 2 * d;
        int * temp = new int[z];
        int top = d;
        int left = d;
        int right = z - d - 1;
        int bottom = z - d - 1;
        std::copy(&m[top*z+left], &m[top*z + left] + z, temp);
        for (int i = 0;  i < z; i++)
        {
            m[top * z + left + i] = m[(bottom - i)*z + left];
            m[(bottom - i)*z + left] = m[bottom*z + right - i];
            m[bottom*z + right - i] = m[(top+i)*z + right];
            m[(top + i)*z + right] = temp[z-i-1];
        }
    }
}

void related_with_task_1_7()
{
    const char * src = "qwertasdfg";
    const int len = strlen(src);
    char * dest = new char[len+1] {0};  // end symbol
    std::copy(src, src + len, dest); // use poiter as iterator
    std::cout << "len=" << len << "; src=" << src << "; dest=" << dest << std::endl;
    int matrix[4][3] = {
                    {1, 2, 3},    /* Initialization of first row */
                    {4, 5, 6},    /* Initialization of second row */
                    {7, 8, 9},    /* Initialization of third row */
                    {10, 11, 12}, /* Initialization of fourth row */
    };

    int row = 4;
    int col = 4;
    int * m2 = new int[col*row] {
        1,   2,   3,  4,
        5,   6,   7,  8,
        9,   10,   11,  12,
       13,  14,  15,  16,
    };

    printMatrix(m2, row, col);
    transformMatrix(m2, row);
    printMatrix(m2, row, col);


    int * line = new int[3]{0};
    std::copy(matrix[0], matrix[0] + 3, line);  
}

void smartZero(int * m, int row, int col)
{
    std::vector<int> zeroRows;
    std::vector<int> zeroCols;
    for (int i = 0; i < col; i++)
    {
        for(int j=0; j < row; j++)
        {
            if (m[j*col+i] == 0)
            {
                zeroRows.push_back(j);
                zeroCols.push_back(i);
            }
        }
    }
    for (auto j : zeroRows)
    {
        for (int i = 0; i < col; i++)
        {
            m[j*col + i] = 0;
        }
    }
    for (auto i : zeroCols)
    {
        for (int j = 0; j < row; j++)
        {
            m[j*col + i] = 0;
        }
    }
}

void task_1_8()
{

    int row = 4;
    int col = 4;
    int * m2 = new int[col*row]{
        1,   2,   3,  4,
        5,   0,   7,  8,
        9,   10,   11,  12,
        13,  14,  15,  16,
    };

    printMatrix(m2, row, col);
    smartZero(m2, row, col);
    printMatrix(m2, row, col);
}

bool isSubstring(std::string s1, std::string s2)
{
    return (s1.find(s2) != std::string::npos);
}

bool isCycleSubstring(std::string s1, std::string s2)
{
    std::string ss = s1 + s1;
    return isSubstring(ss, s2);
}

void task_1_9()
{
    assert(isCycleSubstring("aabcccccaaa", "asfd") == false);
    assert(isCycleSubstring("asdasd", "sdasda") == true);
    assert(isCycleSubstring("", "") == true);
    assert(isCycleSubstring("a", "a") == true);
    assert(isCycleSubstring("a", "b") == false);
}

int main()
{
    task_1_9();
    std::cout << "press any key to exit";
    std::cin.get();
}
