#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6+5;

int test, K;
int isPrime[maxn];
vector <int> prime, ans;

void Eratosthenes(){
    int x = 1e6;
    isPrime[0] = 1;
    isPrime[1] = 1;
    for (int i=2; i<=1000; i++)
        if (isPrime[i] == 0){
            int j = i * i;
            while (j <= x){
                isPrime[j] = 1;
                j += i;
            }
        }
}

long long Pow(int a, int x, int mod){
    if (x == 0) return 1;
    if (x == 1) return 2;
    long long re = Pow(a, x / 2, mod);
    if (x % 2 == 0) return re * re % mod;
    else return (re * re % mod ) * a % mod;
}


int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);\
    Eratosthenes();
    for (int i=1; i<=(int)1e6; i++)
        if (isPrime[i] == 0)
            prime.push_back(i);
    /*cout << prime.size();
    for(auto x: prime){
        cout << Pow(2, x, x) << ' ';
    }*/
    cin >> test;
    for (int test_case = 1; test_case <= test; test_case++){
        cin >> K;
        K += 2;
        ans.clear();
        while(K%2==0) K/= 2;
        int idx = 1;
        while (K != 1 and idx < prime.size()){
            if (isPrime[K] == 0){
                ans.push_back(K);
                break;
            }
            if (K % prime[idx] == 0){
            ans.push_back(prime[idx]);
            while(K % prime[idx] == 0)
                K /= prime[idx];
            }
                else idx++;
        }
        if (ans.size() == 0) cout << -1;
        else{
            for (int i=0; i<ans.size()-1; i++)
                cout << ans[i] << ' ';
            cout << ans[ans.size() - 1];
        }
        cout << '\n';
    }
}
