#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;
typedef long double ld;

namespace Dindows {

const long long USUAL_MOD = 1000000007;

template <class T>
inline void normmod(T &x, T m = USUAL_MOD) {
    x %= m;
    if (x < 0)
        x += m;
}

inline ll mulmod(ll x, ll n, ll m) {
    x %= m;
    n %= m;
    ll r = x * n - ll(ld(x) * ld(n) / ld(m)) * m;
    while (r < 0)
        r += m;
    while (r >= m)
        r -= m;
    return r;
}
inline ll powmod(ll x, ll n, ll m) {
    ll r = 1;
    normmod(x, m);
    while (n) {
        if (n & 1)
            r *= x;
        x *= x;
        r %= m;
        x %= m;
        n /= 2;
    }
    return r;
}
inline ll powmulmod(ll x, ll n, ll m) {
    ll res = 1;
    normmod(x, m);
    while (n) {
        if (n & 1)
            res = mulmod(res, x, m);
        x = mulmod(x, x, m);
        n /= 2;
    }
    return res;
}

bool isPrime(long long n) {
    if (n <= (1 << 14)) {
        long long x = (long long)n;
        if (x <= 4 || x % 2 == 0 || x % 3 == 0)
            return x == 2 || x == 3;
        for (long long i = 5; i * i <= x; i += 6)
            if (x % i == 0 || x % (i + 2) == 0)
                return 0;
        return 1;
    }
    long long s = n - 1;
    long long t = 0;
    while (s % 2 == 0) {
        s /= 2;
        ++t;
    }
    for (long long a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
        if (!(a %= n))
            return true;
        long long f = powmulmod(a, s, n);
        if (f == 1 || f == n - 1)
            continue;
        for (long long i = 1; i < t; ++i)
            if ((f = mulmod(f, f, n)) == n - 1)
                goto nextp;
        return false;
    nextp:;
    }
    return true;
}

int start() {
    ll n;
    cin >> n;
    cout << isPrime(n) << endl;
}
}  // namespace Dindows

namespace Idiots {
/*
 * calculates (a * b) % c taking into account that a * b might overflow
 */
ll mulmod(ll a, ll b, ll mod) {
    ll x = 0, y = a % mod;
    while (b > 0) {
        if (b % 2 == 1) {
            x = (x + y) % mod;
        }
        y = (y * 2) % mod;
        b /= 2;
    }
    return x % mod;
}
/*
 * modular exponentiation
 */
ll modulo(ll base, ll exponent, ll mod) {
    ll x = 1;
    ll y = base;
    while (exponent > 0) {
        if (exponent % 2 == 1)
            x = (x * y) % mod;
        y = (y * y) % mod;
        exponent = exponent / 2;
    }
    return x % mod;
}

/*
 * Miller-Rabin primality test, iteration signifies the accuracy
 */
bool Miller(ll p, int iteration) {
    if (p < 2) {
        return false;
    }
    if (p != 2 && p % 2 == 0) {
        return false;
    }
    ll s = p - 1;
    while (s % 2 == 0) {
        s /= 2;
    }
    for (int i = 0; i < iteration; i++) {
        ll a = rand() % (p - 1) + 1, temp = s;
        ll mod = modulo(a, temp, p);
        while (temp != p - 1 && mod != 1 && mod != p - 1) {
            mod = mulmod(mod, mod, p);
            temp *= 2;
        }
        if (mod != p - 1 && temp % 2 == 0) {
            return false;
        }
    }
    return true;
}
// Main
int start() {
    int iteration = 1000000;
    ll num;
    cout << "Enter integer to test primality: ";
    cin >> num;
    if (Miller(num, iteration))
        cout << num << " is prime" << endl;
    else
        cout << num << " is not prime" << endl;
    return 0;
}
}  // namespace Idiots

int main() {
    // Test Data
    Idiots::start();
}