#include <bits/stdc++.h>

using namespace std;

//=== exponentiation  ===
//{
    long long __pow(long long a, long long b)
    {
        if (b == 0) return 1;
        long long re = __pow(a,  b/2);
        if (b % 2 == 0) return re * re;
        else return re * re * a;
    }

    long long __pow(long long a, long long b, long long mod)
    {
        if (b == 0) return 1;
        long long re = __pow(a,  b/2);
        if (b % 2 == 0) return re * re % mod;
        else return (re * re % mod) * a % mod;
    }
//}

//=== euclidean extended ===
//{
    void diophante(long long a, long long b, long long &d, long long&x)
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

//=== matrix ===
//{
    struct matrix {
        long long c[2][2];
        void init() {
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 2; j++) c[i][j] = 0;
            }
        }
    };
    long long mul(long long x, long long y,long long m) /// Tinh (x * y) mod M voi (x,y, M <= 10 ^ 18)
    {
        x %= m; y %= m;
        long long q = (long double) x * y / m;
        long long r = (x * y - q * m) % m;
        if (r < 0) r += m;
        return r;
    }
//}



//=== prime ===
//{
    vector <int> eratosthenes(int limit)
    {
        vector <int> isPrime(limit + 1, 0);

        isPrime[0] = 1;
        isPrime[1] = 1;
        for (int i=2; i<=sqrt(limit); i++)
            if (isPrime[i] == 0)
            {
                int j = i * i;
                while (j <= limit)
                {
                    isPrime[j] = 1;
                    j += i;
                }
            }
        return isPrime;
    }

    vector <int> primeArray(int limit)
    {
        vector <int> primeArray;
        vector <int> isPrime = eratosthenes(limit);
        for (int i=1; i<=limit; i++)
            if (isPrime[i] == 0)
                primeArray.push_back(i);
        return primeArray;
    }
//}

//=== string ===
//{
    /// Z Algorithm
    vector <int> Z(string s){
        int n = s.length();
        vector <int> Z(n);
        int L, R, k;
        L = R = 0;
        for (int i = 1; i < n; ++i)
        {
            if (i > R)
            {
                L = R = i;
                while (R<n && s[R-L] == s[R])
                    R++;
                Z[i] = R-L;
                R--;
            }
            else
            {
                k = i-L;
                if (Z[k] < R-i+1)
                    Z[i] = Z[k];
                else
                {
                    L = i;
                    while (R<n && s[R-L] == s[R])
                        R++;
                    Z[i] = R-L;
                    R--;
                }
            }
        }
        return Z;
    }

    /// Hash
    vector <long long> Hash(string s, long long base, long long MOD){
        int n = s.length();
        vector <long long> Hash(n + 1);
        for (int i=1; i<=n; i++)
            Hash[i] = (Hash[i-1] * base % MOD + s[i-1] + MOD * MOD) % MOD;
        return Hash;
    }

    /// KMP
    /// bug kmp :v

//}

/*
//=== geometry ===
//{
    ///minimum enclosing circle O(N)
    ///https://www.geeksforgeeks.org/minimum-enclosing-circle-set-2-welzls-algorithm/
    struct Point {
        double x, y;
        Point(){};
        Point(double _x, double _y) : x(_x), y(_y) {};
        Point(const Point &A) : x(A.x), y(A.y) {};
        int operator < (const Point &A) {
            return make_pair(x, y) < make_pair(A.x, A.y);
        }
        int operator == (const Point &A) {
            return make_pair(x, y) == make_pair(A.x, A.y);
        }
    };

    struct Circle {
        Point center;
        double r;
        Circle(){};
        Circle(double _x, double _y, double _r) : center(Point(_x, _y)), r(_r) {};
        Circle(Point _center, double _r) : center(_center), r(_r) {};
        Circle(const Circle &A) : center(A.center), r(A.r) {};
        int operator < (const Circle &A) {
            return r < A.r;
        }
    };

    double dist(Point A, Point B) {
        double x = A.x - B.x;
        double y = A.y - B.y;
        return sqrtl(x * x + y * y);
    }

    bool inSide(Point A, Circle C) {
        return dist(A, C.center) <= C.r;
    }

    Point get_circle_center(double bx, double by,
                            double cx, double cy)
    {
        double B = bx * bx + by * by;
        double C = cx * cx + cy * cy;
        double D = bx * cy - by * cx;
        return { (cy * B - by * C) / (2 * D),
                 (bx * C - cx * B) / (2 * D) };
    }

    Circle circle_three(Point A, Point B, Point C) {
        Point O = get_circle_center(B.x - A.x, B.y - A.y, C.x - A.x, C.y - A.y);
        O.x += A.x;
        O.y += A.y;
        return Circle(O, dist(O, A));
    }

    Circle circle_two(Point A, Point B) {
        Point O = Point((A.x + B.x) / 2.0, (A.y + B.y) / 2.0);
        return Circle(O, dist(A, B) / 2.0);
    }

    bool check_valid_circle(Circle C, vector<Point> p) {
        for (Point A : p) {
            if (!inSide(A, C)) return false;
        }
        return true;
    }

    // Function to return the minimum enclosing circle for N <= 3
    Circle MEC_small(vector<Point> p) {
        assert((int)p.size() <= 3);
        if (p.empty()) return Circle(Point(0, 0), 0);
        if ((int)p.size() == 1) return Circle(p[0], 0);
        if ((int)p.size() == 2) return circle_two(p[0], p[1]);

        for (int i = 0; i < 3; i++) {
            for (int j = i + 1; j < 3; j++) {
                Circle C = circle_two(p[i], p[j]);
                if (check_valid_circle(C, p)) return C;
            }
        }
        Circle res = circle_three(p[0], p[1], p[2]);
        return res;
    }

    Circle welzl_helper(vector<Point>& P, vector<Point> R, int n)
    {
        if (n == 0 || R.size() == 3) {
            return MEC_small(R);
        }

        int idx = rng() % n;
        Point p = P[idx];

        swap(P[idx], P[n - 1]);

        Circle C = welzl_helper(P, R, n - 1);

        if (inSide(p, C)) {
            return C;
        }

        R.push_back(p);

        return welzl_helper(P, R, n - 1);
    }

    ///minimum enclosing circle O(N)
    Circle MEC(vector<Point> p) {
        int n = (int)p.size();
        random_shuffle(p.begin(), p.end());
        return welzl_helper(p, {}, n);
    }

    ///minimum enclosing circle O(N)
    Circle get(vector<double> &x, vector<double> &y) {
        int n = (int)x.size();
        vector<Point> p(n);
        for (int i = 0; i < n; i++) p[i] = Point(x[i], y[i]);
        return MEC(p);
    }

//}
*/
int main()
{

}
