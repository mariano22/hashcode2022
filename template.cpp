//touch {a..m}.in; tee {a..m}.cpp < template.cpp
#include <bits/stdc++.h>
using namespace std;
#define forr(i,a,b) for(int i=(a); i<(b); i++)
#define forn(i,n) forr(i,0,n)
#define sz(c) ((int)c.size())
#define zero(v) memset(v, 0, sizeof(v))
#define forall(it,v) for(auto it=v.begin();it!=v.end();++it)
#define pb push_back
#define fst first
#define snd second
typedef long long ll;
typedef pair<int,int> ii;
#define dforn(i,n) for(int i=n-1; i>=0; i--)
#define mkp make_pair

#ifdef DEBUG
    #define dprint(v) cout << #v"=" << v << endl //;)
    #define dpr(v) cout << #v"=" << v << endl //;)
    #define dpra(a,n) { forn(i,(n)) cout << (a)[i] << (i==(n)-1?'\n':' '); }
    #define dprv(vec) dpra(vec,sz(vec))

#else
    #define dprint(v) (void)0
    #define dpr(v) (void)0
    #define dpra(a,n) (void)0
    #define dprv(vec) (void)0
#endif

const int MAXC=100100;
const int MAXM=100100;
int C,Ln[MAXC][2],L[MAXC][2][5],M,sol,di[MAXM][2],dc[MAXC];
vector<int> Linv[MAXM][2];
vector<int> available;
map<string,int> mp;
string invmp[MAXM];
int included[MAXM];
int sat[MAXC];
int fid(const string& str) {
    auto it = mp.find(str);
    if (it!=mp.end()) return it->second;
    return mp[str]=sz(mp);
}

void printsolution() {
    vector<int> sol;
    forn(i,M) if (included[i]==1) {
        sol.pb(i);
    }
    cout << sz(sol);
    forn(i,sz(sol)) cout << ' ' << invmp[sol[i]];
    cout << endl;
}
void dprintsolution() {
    #ifdef DEBUG
        printsolution();
    #endif
}

int main() {
    #ifdef DEBUG
        freopen("./in/a_an_example.in", "r", stdin);
        //~ freopen("./in/b_basic.in", "r", stdin);
        //~ freopen("./in/c_coarse.in", "r", stdin);
        //~ freopen("./in/d_difficult.in", "r", stdin);
        //~ freopen("./in/e_elaborate.in", "r", stdin);
    #endif
    ios::sync_with_stdio(0);
    cin >> C;
    zero(included); zero(di);
    forn(i,C) {
        forn(nf,2) { int f = 1-nf;
            cin >> Ln[i][f];
            forn(j,Ln[i][f]) {
                string str; cin >> str;
                int id = fid(str);
                L[i][f][j] = id;
                Linv[id][f].pb(i);
                di[id][f]++;
            }
        }
    }
    M = sz(mp);
    assert(M < MAXM);
    forall(it,mp) {
        invmp[it->snd]=it->first;
    }
    
    memset(included,-1,sizeof(included));
    forn(i,C) available.pb(i);
    
    set<int> csol;
    for(int its=0;sz(available);its++) {
        
        forn(idx,sz(available)) {
            int i = available[idx];
            forn(f,2) {
                forn(j,Ln[i][f]) {
                    di[L[i][f][j]][0]=di[L[i][f][j]][1]=0;
                }
            }
        }
        forn(idx,sz(available)) {
            int i = available[idx];
            forn(f,2) {
                forn(j,Ln[i][f]) {
                    di[L[i][f][j]][f]++;
                }
            }
        }
        
        forn(idx,sz(available)) {
            int i = available[idx];
            dc[i]=0;
            forn(f,2) {
                forn(j,Ln[i][f]) {
                    dc[i] += di[L[i][f][j]][!f];
                }
            }
        }
        int pmin = available[0];
        forn(idx,sz(available)) {
            if (dc[available[idx]] < dc[pmin]) {
                pmin = available[idx];
            }
        }
        //~ dprint(pmin);
        
        
        forn(f,2) {
            forn(j,Ln[pmin][f]) {
                included[L[pmin][f][j]] = (f ? 1 : 0);
            }
        }
        csol.insert(pmin);
        
        vector<int> newavailable;
        dprint(sz(available));
        forn(idx,sz(available)) {
            bool inc = true;
            int i = available[idx];
            if (i==pmin) continue;
            forn(f,2) {
                forn(j,Ln[i][f]) {
                    if ( (included[L[i][f][j]]==1 && !f) || (included[L[i][f][j]]==0 && f) ) {
                        inc = false;
                        goto fin;
                    }
                }
            }
            fin:
            if (inc) newavailable.pb(i);
        }
        available = newavailable;
        //if (its==0) break;
    }
    
    zero(sat);
    forn(j,M) if (included[j]!=-1) {
        bool f = included[j];
        forn(idx,sz(Linv[j][f])) {
            int i = Linv[j][f][idx];
            sat[i]++;
        }
    }
    forn(j,M) if (included[j]==-1) {
        forn(f,2) {
            forn(idx,sz(Linv[j][f])) {
                int i = Linv[j][f][idx];
                sat[i]++;
            }
        }
    }
    const int ITERATIONS = 100000000;
    dforn(iteration,ITERATIONS) {
        
        //dprintsolution();
        //dprint(iteration);
        bool swap = false;
        forn(j,M) if (included[j]!=-1) {
            bool f = included[j];
            int ss = 0;
            forn(idx,sz(Linv[j][f])) {
                int i = Linv[j][f][idx];
                ss += csol.count(i);
            }
            int cc = 0;
            forn(idx,sz(Linv[j][!f])) {
                int i = Linv[j][!f][idx];
                if (sat[i] == Ln[i][0]+Ln[i][1]-1) {
                    cc++;
                }
            }
            int dd = iteration/(ITERATIONS/5);
            if (ss < cc || ss < cc+dd) {
                
                forn(idx,sz(Linv[j][f])) {
                    int i = Linv[j][f][idx];
                    csol.erase(i);
                    sat[i]--;
                }
                forn(idx,sz(Linv[j][!f])) {
                    int i = Linv[j][!f][idx];
                    sat[i]++;
                    if (sat[i] == Ln[i][0]+Ln[i][1]) {
                        csol.insert(i);
                        forn(cf,2) {
                            forn(cj,Ln[i][cf]) {
                                int ing = L[i][cf][cj];
                                if (included[ing]==-1) {
                                    included[ing]=cf;
                                    forn(cing,sz(Linv[ing][!cf])) {
                                        sat[cing]--;
                                    }
                                }
                            }
                        }
                    }
                }
                
                included[j]=!f;
                swap=true;
                break;
            }
        }
        if (!swap) break;
    }
    
    
    printsolution();
    
    return 0;
}
