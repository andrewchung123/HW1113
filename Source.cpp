#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// �G���j�M�禡
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
    return -1; // �S�����
}

int main() {
    string type;
    int a, b;
    // Ū���C������
    while (cin >> type >> a >> b) {
        // Ū���w�ƧǪ����
        vector<string> data;
        if (type == "i") {
            // ��ƫ��A���
            vector<int> int_data(a);
            for (int i = 0; i < a; ++i) {
                cin >> int_data[i];
            }
            for (int i = 0; i < b; ++i) {
                int target;
                cin >> target;
                // ����G���j�M
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
                // ����G���j�M
                int result = binary_search(str_data, target);
                cout << result << endl;
            }
        }
    }
    return 0;
}