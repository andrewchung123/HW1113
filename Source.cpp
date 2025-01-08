#include <iostream>
#include <chrono>  // 新增此標頭以使用計時
using namespace std;
using namespace std::chrono;

struct Node {
    int coef;
    int exp;
    Node* link;
};

class Polynomial {
private:
    Node* head;
    Node* createNode(int c, int e, Node* nxt = nullptr) {
        Node* newNode = new Node;
        newNode->coef = c;
        newNode->exp = e;
        newNode->link = nxt;
        return newNode;
    }
    void clearList() {
        Node* curr = head->link;
        while (curr != head) {
            Node* tmp = curr;
            curr = curr->link;
            delete tmp;
        }
        head->link = head;
    }
public:
    Polynomial() {
        head = new Node;
        head->coef = 0;
        head->exp = 0;
        head->link = head;
    }
    Polynomial(const Polynomial& other) {
        head = new Node;
        head->coef = 0;
        head->exp = 0;
        head->link = head;
        Node* p = other.head->link;
        while (p != other.head) {
            insertTerm(p->coef, p->exp);
            p = p->link;
        }
    }
    ~Polynomial() {
        clearList();
        delete head;
    }
    Polynomial& operator=(const Polynomial& rhs) {
        if (this == &rhs) return *this;
        clearList();
        Node* p = rhs.head->link;
        while (p != rhs.head) {
            insertTerm(p->coef, p->exp);
            p = p->link;
        }
        return *this;
    }
    void insertTerm(int c, int e) {
        if (c == 0) return;
        Node* prev = head;
        Node* curr = head->link;
        while (curr != head && curr->exp > e) {
            prev = curr;
            curr = curr->link;
        }
        if (curr != head && curr->exp == e) {
            curr->coef += c;
            if (curr->coef == 0) {
                prev->link = curr->link;
                delete curr;
            }
        }
        else {
            Node* newNode = createNode(c, e);
            prev->link = newNode;
            newNode->link = curr;
        }
    }
    Polynomial operator+(const Polynomial& rhs) const {
        Polynomial result;
        Node* p = head->link;
        while (p != head) {
            result.insertTerm(p->coef, p->exp);
            p = p->link;
        }
        p = rhs.head->link;
        while (p != rhs.head) {
            result.insertTerm(p->coef, p->exp);
            p = p->link;
        }
        return result;
    }
    Polynomial operator-(const Polynomial& rhs) const {
        Polynomial result;
        Node* p = head->link;
        while (p != head) {
            result.insertTerm(p->coef, p->exp);
            p = p->link;
        }
        p = rhs.head->link;
        while (p != rhs.head) {
            result.insertTerm(-p->coef, p->exp);
            p = p->link;
        }
        return result;
    }
    Polynomial operator*(const Polynomial& rhs) const {
        Polynomial result;
        Node* p = head->link;
        while (p != head) {
            Node* q = rhs.head->link;
            while (q != rhs.head) {
                int c = p->coef * q->coef;
                int e = p->exp + q->exp;
                result.insertTerm(c, e);
                q = q->link;
            }
            p = p->link;
        }
        return result;
    }
    double Evaluate(double x) const {
        double sum = 0.0;
        Node* p = head->link;
        while (p != head) {
            double termVal = p->coef;
            for (int i = 0; i < p->exp; i++)
                termVal *= x;
            sum += termVal;
            p = p->link;
        }
        return sum;
    }
    friend ostream& operator<<(ostream& os, const Polynomial& poly) {
        int count = 0;
        Node* p = poly.head->link;
        while (p != poly.head) {
            count++;
            p = p->link;
        }
        os << count;
        p = poly.head->link;
        while (p != poly.head) {
            os << " " << p->coef << " " << p->exp;
            p = p->link;
        }
        return os;
    }
    friend istream& operator>>(istream& is, Polynomial& poly) {
        poly.clearList();
        int n; is >> n;
        for (int i = 0; i < n; i++) {
            int c, e;
            is >> c >> e;
            poly.insertTerm(c, e);
        }
        return is;
    }
};

int main() {
    Polynomial p1, p2;

    cout << "請輸入第一個多項式 (格式: n c1 e1 c2 e2 ...): ";
    cin >> p1;
    cout << "請輸入第二個多項式 (格式: n c1 e1 c2 e2 ...): ";
    cin >> p2;

    cout << "p1 = " << p1 << endl;
    cout << "p2 = " << p2 << endl;

    // ★★★ 加入計時：p1 + p2 ★★★
    auto start = high_resolution_clock::now();
    Polynomial p3 = p1 + p2;
    auto end = high_resolution_clock::now();
    auto durationAdd = duration_cast<microseconds>(end - start).count();

    // ★★★ 加入計時：p1 - p2 ★★★
    start = high_resolution_clock::now();
    Polynomial p4 = p1 - p2;
    end = high_resolution_clock::now();
    auto durationSub = duration_cast<microseconds>(end - start).count();

    // ★★★ 加入計時：p1 * p2 ★★★
    start = high_resolution_clock::now();
    Polynomial p5 = p1 * p2;
    end = high_resolution_clock::now();
    auto durationMul = duration_cast<microseconds>(end - start).count();

    cout << "p1 + p2 = " << p3 << endl;
    cout << "p1 - p2 = " << p4 << endl;
    cout << "p1 * p2 = " << p5 << endl;

    cout << "[加法耗時] " << durationAdd << " microseconds\n";
    cout << "[減法耗時] " << durationSub << " microseconds\n";
    cout << "[乘法耗時] " << durationMul << " microseconds\n";

    double xValue;
    cout << "請輸入一個 x 的值: ";
    cin >> xValue;

    // ★★★ 加入計時：Evaluate ★★★
    start = high_resolution_clock::now();
    double val = p1.Evaluate(xValue);
    end = high_resolution_clock::now();
    auto durationEval = duration_cast<microseconds>(end - start).count();

    cout << "p1 在 x=" << xValue << " 時的值為: " << val << endl;
    cout << "[Evaluate 耗時] " << durationEval << " microseconds\n";

    return 0;
}
