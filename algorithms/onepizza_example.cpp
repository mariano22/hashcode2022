#include <bits/stdc++.h>
using namespace std;

#define forn(i,n) for(int i=0;i<(int)(n);i++)
#define si(c) ((int)(c).size())
#define forsn(i,s,n) for(int i = (int)(s); i<((int)n); i++)
#define dforsn(i,s,n) for(int i = (int)(n)-1; i>=((int)s); i--)
#define all(c) (c).begin(), (c).end()
#define D(a) cerr << #a << "=" << (a) << endl;
#define pb push_back
#define eb emplace_back
#define mp make_pair

typedef long long int ll;
typedef vector<int> vi;
typedef pair<int,int> pii;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

template<class T>
vector<T> make_unique(vector<T> a) {
    sort(all(a));
    a.erase(unique(all(a)), a.end());
    return a;
}

int C;
vector<vector<string>> like, dislike;
map<string, pair<vi,vi>> ingredients;
vector<string> names;
map<string,int> id;

struct state {

    int n_ingredients, happy;
    vector<bool> ans;
    vi violations;

    state(vector<bool> ans) {
        n_ingredients = si(ingredients);
        this->ans = ans;
        this->violations = vi(C);
        happy = C;


        int idx = 0;
        for (auto &[ingredient, preferences] : ingredients) {
            if (ans[idx]) {
                for (auto client : preferences.second) 
                    violations[client]++;
            }
            else {
                for (auto client : preferences.first) 
                    violations[client]++;
            }
            idx++;
        }

        happy = 0;
        forn(i, C) happy += violations[i] == 0;
    }

    void flip(int idx) {
        auto [u,v] = ingredients[names[idx]];
        if (!ans[idx]) swap(u,v);
        for (auto x : u) { 
            if (violations[x] == 0) happy--;
            violations[x]++;
        }
        for (auto x : v) {
            violations[x]--;
            if (violations[x] == 0) happy++;
        }
        ans[idx] = !ans[idx];
    }

    vi flipped;
    void step() {
        flipped.clear();

        int idx = rng()%si(ans);
        flip(idx);
        flipped.pb(idx);
    }

    void rollback() {
        while (!flipped.empty()) {
            int idx = flipped.back();
            flipped.pop_back();
            flip(idx);
        }
    }

    double value() {
        return happy;
    }

};

void simulated_annealing(state &s, double seconds, double high=10, double low=0) {
    using namespace std::chrono;

    steady_clock::time_point start = steady_clock::now();

    double energy = s.value();
    uniform_real_distribution<double> dist(0.0, 1.0);

    while (true) {
        steady_clock::time_point now = steady_clock::now();
        double elapsed = duration_cast<duration<double>>(now - start).count();
        if (elapsed >= seconds) break;

        s.step();
        double new_energy = s.value();
        double T = (elapsed * low + (seconds-elapsed) * high) / seconds; 
        double prob = exp((new_energy - energy) / T);

        if (dist(rng) < prob) {
            energy = new_energy;
        }
        else {
            s.rollback();
        }
    }
    D(energy);
}

void read_input() {
    cin >> C;
    like.resize(C);
    dislike.resize(C);
    forn(i, C) {
        int k; 
        cin >> k;
        while (k--) {
            string s; cin >> s;
            like[i].pb(s);
            ingredients[s].first.pb(i);
        }
        cin >> k;
        while (k--) {
            string s; cin >> s;
            dislike[i].pb(s);
            ingredients[s].second.pb(i);
        }
    }
    int idx = 0;
    for (auto &[ingr, _] : ingredients) {
        names.pb(ingr);
        id[ingr] = idx;
        idx++;
    }
}

void test() {
    vector<bool> ans(si(ingredients));
    state s(ans);
    int last = 0;
    forn(mask, 1<<si(ingredients)) {
        int change = mask ^ last;
        forn(i, si(ingredients)) if ((change>>i)&1) {
            s.flip(i);
            cerr << mask << ": \n";
            for (auto x : s.violations) cerr << x << ' ';
            cerr << endl;
            cerr << s.value() << endl;
        }
        last = mask;
    }
}

void solve(double alloted_time) {
    vector<bool> ans(si(ingredients));
    forn(i, si(ans)) ans[i] = rng() % 2;
    state s(ans);
    simulated_annealing(s, alloted_time);

    vector<string> put;
    forn(i, si(s.ans)) if (s.ans[i]) put.pb(names[i]);
    cout << si(put);
    for (auto x : put) cout << ' ' << x;
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    read_input();
    solve(120);

    return 0;
}

