#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// 二分搜尋函式
template <typename T>
int binary_search(const vector<T>& arr, const T& target) {
    int low = 0, high = arr.size() - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (arr[mid] == target) {
            return mid;
        }
        else if (arr[mid] < target) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return -1; // 沒有找到
}

int main() {
    string type;
    int a, b;
    // 讀取每筆測資
    while (cin >> type >> a >> b) {
        // 讀取已排序的資料
        vector<string> data;
        if (type == "i") {
            // 整數型態資料
            vector<int> int_data(a);
            for (int i = 0; i < a; ++i) {
                cin >> int_data[i];
            }
            for (int i = 0; i < b; ++i) {
                int target;
                cin >> target;
                // 執行二分搜尋
                int result = binary_search(int_data, target);
                cout << result << endl;
            }
        }
        else if (type == "s") {
            vector<string> str_data(a);
            for (int i = 0; i < a; ++i) {
                cin >> str_data[i];
            }
            for (int i = 0; i < b; ++i) {
                string target;
                cin >> target;
                // 執行二分搜尋
                int result = binary_search(str_data, target);
                cout << result << endl;
            }
        }
    }
    return 0;
}