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
#define all(c) (c).begin(), (c).end()

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

int n_contributors = 0;
struct contributor {
    string name;
    int idx;
    map<string, int> skills;
    //vector<pair<string, int>> skills;
};

istream& operator>>(istream &in, contributor &c) {
    in >> c.name;
    c.idx = n_contributors++;
    int k; in >> k;
    while (k--) {
        string skill; int level;
        in >> skill >> level;
        c.skills[skill] = level;
    }
    return in;
}

int n_projects = 0;
struct project {
    string name;
    int idx, takes, score, before;
    vector<pair<string, int>> skills;

    bool operator<(const project &o) const {
        return before < o.before;
    }
};

istream &operator>>(istream &in, project &p) {
    in >> p.name;
    p.idx = n_projects++;
    in >> p.takes >> p.score >> p.before;
    int k; in >> k;
    p.skills.resize(k);
    for (auto &[x,y] : p.skills) in >> x >> y;
    return in;
}

int get(const vector<string> &name, const string &s) {
    return lower_bound(all(name), s) - name.begin();
}

#define proj __mastroventor_proj

int C, P;
vector<contributor> cont;
vector<project> proj;
map<string, vi> workers;
vi busy;

void read_input() {
    cin >> C >> P;
    cont.resize(C);
    for (auto &x : cont) {
        cin >> x;
    }

    busy = vi(C);
    //busy = vector<bool>(C);

    proj.resize(P);
    for (auto &x : proj) cin >> x;

    sort(all(proj));
}

void solve() {

    vector<pair<string, vi>> ans;

    for (auto p : proj) {

        auto should_shart = p.before - p.takes + 1;

        vi workers;
        bool failed = false;
        for (auto &[skill, level] : p.skills) {
            int pick = -1, min_level = 1e9;
            forn(idx, C) if (busy[idx] <= should_shart) {
                int has_level = cont[idx].skills[skill];
                if (has_level < level) continue;

                if (pick == -1 || has_level < min_level) { // change has_level for contrib.value()
                    pick = idx;
                    min_level = has_level;
                }
            }

            if  (pick == -1) {
                failed = true;
                break;
            }
            workers.pb(pick);
        }

        if (!failed) ans.eb(p.name, workers);
    }

    cout << si(ans) << endl;
    for (auto &[p, cs] : ans) {
        cout << p << endl;
        for (auto idx : cs) cout << cont[idx].name << ' ';
        cout << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    read_input();
    solve();
    
    return 0;
}
