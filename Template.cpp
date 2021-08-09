#include <bits/stdc++.h>

using namespace std;

//=== exponentiation  ===
//{
    long long   pow(long long a, long long b)
    {
        if (b == 0) return 1;
        long long re = Pow(a,  b/2);
        if (b % 2 == 0) return re * re;
        else return re * re * a;
    }

    long long pow(long long a, long long b, long long mod)
    {
        if (b == 0) return 1;
        long long re = Pow(a,  b/2);
        if (b % 2 == 0) return re * re % mod;
        else return (re * re % mod) * a % mod;
    }
//}

//=== euclidean extended ===
//{
    void Diophante(long long a, long long b, long long &d, long long&x)
    {
      long long m, n, r, q, xm, xn, xr;
      m = a; xm = 1;
      n = b; xn = 0;
      while (n != 0)
      {
        q = m / n;
        r = m - q * n;
        xr = xm - q * xn;
        m = n; xm = xn;
        n = r; xn = xr;
      }
      d = m;
      x = xm;
      cout << d << " " << x << '\n';
    }
//}

//=== matrix
//{
    struct matrix {
        long long c[2][2];
        void init() {
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 2; j++) c[i][j] = 0;
            }
        }
    };
    long long Mul(long long x, long long y,long long m) /// Tinh (x * y) mod M voi (x,y, M <= 10 ^ 18)
    {
        x %= m; y %= m;
        long long q = (long double) x * y / m;
        long long r = (x * y - q * m) % m;
        if (r < 0) r += m;
        return r;
    }
//}

int main()
{

}
