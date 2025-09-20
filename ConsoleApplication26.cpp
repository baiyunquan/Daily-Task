#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <array>
#include <cctype>

using namespace std;

class Solution {
public:
    int strStr(string haystack, string needle) {
        vector<int> nextVal{};
        nextVal.resize(needle.size() + 1);

        nextVal[0] = -1;
        int j = 0, k = -1;

        while (j < needle.size()) {
            if (k == -1) {
                j++, k++;
                nextVal[j] = k;
            }
            else {
                if (needle[j] == needle[k]) {
                    j++, k++;
                    if (needle[k] == needle[j]) {
                        nextVal[j] = nextVal[k];
                    }
                    else {
                        nextVal[j] = k;
                    }

                }
                else {
                    k = nextVal[k];
                }
            }
        }

        int ptr1 = 0, ptr2 = 0;
        while (ptr1 < haystack.size() && ptr2 < needle.size()) {
            if (haystack[ptr1] == needle[ptr2]) {
                ptr1++, ptr2++;
            }
            else {
                ptr2 = nextVal[ptr2];
                if (ptr2 < 0) {
                    ptr2 = 0;
                    ptr1++;
                }
            }
        }

        return ptr1 - needle.size();
    }
};

int main() {
    string haystack{"aaaaaaaaaaaaaaaaabaaaa"}, needle{"aaaaab"};

    vector<int> nextVal{};
    nextVal.resize(needle.size() + 1);

    nextVal[0] = -1;
    int j = 0, k = -1;

    while (j < needle.size()) {
        if (k == -1) {
            j++, k++;
            nextVal[j] = k;
        }
        else {
            if (needle[j] == needle[k]) {
                j++, k++;
                if (needle[k] == needle[j]) {
                    nextVal[j] = nextVal[k];
                }
                else {
                    nextVal[j] = k;
                }
                
            }
            else {
                k = nextVal[k];
            }
        }
    }

    int ptr1 = 0, ptr2 = 0;
    while (ptr1 < haystack.size() && ptr2 < needle.size()) {
        if (haystack[ptr1] == needle[ptr2]) {
            ptr1++, ptr2++;
        }
        else {
            ptr2 = nextVal[ptr2];
            if (ptr2 < 0) {
                ptr2 = 0;
                ptr1++;
            }
        }
    }
    
    cout << haystack.substr(ptr1 - needle.size() , needle.size()) << endl;
    return 0;
}