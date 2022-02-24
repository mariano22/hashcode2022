//touch {a..m}.in; tee {a..m}.cpp < template.cpp
#include <bits/stdc++.h>
using namespace std;

#define forsn(i,s,n) for(int i = (int)(s); i<((int)n); i++)
#define forn(i,n) for(int i=0;i<(int)(n);i++)
#define dforn(i,n) for(int i=n-1; i>=0; i--)
#define dforsn(i,s,n) for(int i = (int)(n)-1; i>=((int)s); i--)

#define si(c) ((int)c.size())
#define zero(v) memset(v, 0, sizeof(v))
#define forall(it,v) for(auto it=v.begin();it!=v.end();++it)
#define pb push_back
#define fst first
#define snd second
typedef long long ll;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef pair<int,int> pii;

#define mp make_pair
#define pb push_back
#define eb emplace_back

#ifdef DEBUG
    #define D(v) cout << #v"=" << v << endl //;)
    #define dpr(v) cout << #v"=" << v << endl //;)
    #define dpra(a,n) { forn(i,(n)) cout << (a)[i] << (i==(n)-1?'\n':' '); }
    #define dprv(vec) dpra(vec,si(vec))

#else
    #define D(v) (void)0
    #define dpr(v) (void)0
    #define dpra(a,n) (void)0
    #define dprv(vec) (void)0
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

template<class T>
vector<T> make_unique(vector<T> a) {
    sort(all(a));
    a.erase(unique(all(a)), a.end());
    return a;
}


void read_input() {

}


void solve(double alloted_time) {

}

int main() {
    #ifdef DEBUG
        freopen("./in/a_an_example.in", "r", stdin);
        //~ freopen("./in/b_better_start_small.in", "r", stdin);
        //~ freopen("./in/c_collaboration.in", "r", stdin);
        //~ freopen("./in/d_dense_schedule.in", "r", stdin);
        //~ freopen("./in/e_exceptional_skills.in", "r", stdin);
        //~ freopen("./in/f_find_great_mentors.in", "r", stdin);
    #endif
    ios_base::sync_with_stdio(0); cin.tie(0);

    read_input();
    
    solve(120);
    
    return 0;
}
