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

struct state {

    state() {
    }

    // move to a neighbour solution
    void step() {
    }

    // rollback last step
    void rollback() {

    }

    // value to maximize (if you want to minimize just change sign at the end)
    //
    double value() {
        return 0;
    }

};

// s: state
// seconds: time to run
// high: initial temperature (we might need to adjust it depending on the input)
// low: final temperature
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


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    return 0;
}

