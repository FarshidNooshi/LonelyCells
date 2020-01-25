//In The Name Of GOD
#include<bits/stdc++.h>

using namespace std;

#define Z   40

int32_t main() {
    int n;  cin >> n;
    string st, ts;
    for (int i = 0; i < n - 1; i++)
        st += '*', ts += ' ';
    st += ' ';
    ts += ' ';
    for (int i  = 0; i < Z; i++) {
        for (int j = 0; j < Z; j++) {
            int w = i % (2 * n - 2), x = j % (4 * n - 4);
            if (w < n) {
                if (w == n - 1) {
                    if (!j) 
                        cout << st;
                    else {
                        if (j < 3 * n - 3) {
                            cout << ts;
                            continue;
                        }
                        int y = j - (2 * n - 2);
                        x = y % (4 * n - 4);
                        if (x >= n - 1 && x <= 2 * n - 2)
                            cout << st;
                        else 
                            cout << ts;
                    }
                } else {
                    if (!w) {
                        if (x >= n - 1 && x <= 2 * n - 2)
                            cout << st;
                        else 
                            cout << ts;
                    } else {
                        if (x == n - 1 - w || x == 2 * n - 2 + w)
                            cout << st;
                        else 
                            cout << ts;
                    }
                }
            } else {
                int y = w - (n - 1);
                w = n - 1 - y;
                if (x == n - 1 - w || x == 2 * n - 2 + w)
                    cout << st;
                else 
                    cout << ts;
            }
        }
        printf("\n");
    }
}