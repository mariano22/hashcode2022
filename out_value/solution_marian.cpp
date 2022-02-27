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
    #define D(v) cerr << #v"=" << v << endl //;)
    #define dpr(v) cerr << #v"=" << v << endl //;)
    #define dpra(a,n) { forn(i,(n)) cerr << (a)[i] << (i==(n)-1?'\n':' '); }
    #define dprv(vec) dpra(vec,si(vec))

#else
    #define D(v) (void)0
    #define dpr(v) (void)0
    #define dpra(a,n) (void)0
    #define dprv(vec) (void)0
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int C, P,S;
vector<string> c_name, p_name, s_name;
vector<map<int,int>> c_skill_original, c_skill;
vector<ll> p_takes, p_score, p_before;
vector<vector<pair<int,int>>> p_reqs;
vector<map<int,int>> p_reqs_map;
vector<double> p_value, s_value, c_value, p_cost;
vector<vector<int>> s_required;

vector<int> p_ord;
vector<vector<int>> r_ord;
vector<int> c_busy;
//~ vector<vector<int>> c_skill_have;

map<string,int> skill_id_map;
int skill_id(const string& s) {
    auto it = skill_id_map.find(s);
    if (it!=skill_id_map.end()) return it->snd;
    return skill_id_map[s]=si(skill_id_map);
}

void read_input() {
    cin >> C >> P;
    c_name.resize(C); c_skill_original.resize(C);  c_value.resize(C); 
    forn(i,C) {
        cin >> c_name[i];
        int x; cin >> x;
        forn(_,x) {
            string skill_str; int skill_level;
            cin >> skill_str >> skill_level;
            c_skill_original[i][skill_id(skill_str)]=skill_level;
        }
    }
    
    p_name.resize(P); p_takes.resize(P); p_score.resize(P); p_before.resize(P); p_reqs.resize(P); p_value.resize(P); p_reqs_map.resize(P); p_cost.resize(P);
    forn(j,P) {
        int n_roles;
        cin >> p_name[j] >> p_takes[j] >> p_score[j] >> p_before[j] >> n_roles;
        p_reqs[j].resize(n_roles);
        forn(r,n_roles) {
            string req_skill; int req_level;
            cin >> req_skill >> req_level;
            int s_id = skill_id(req_skill);
            p_reqs[j][r]=pii(s_id,req_level);
            p_reqs_map[j][s_id]=req_level;
        }
    }
    
    S = si(skill_id_map);
    s_value.resize(S); s_required.resize(S); s_name.resize(S);
    
    for(auto const &[skill_str, skill_id] : skill_id_map) {
        s_name[skill_id]=skill_str;
    }
    
    forn(p_idx,P) {
        forn(r_idx, si(p_reqs[p_idx])) {
            s_required[p_reqs[p_idx][r_idx].fst].pb(p_idx);
        }
    }
    
    forn(s_idx,S) s_value[s_idx] = si(s_required[s_idx]);
    
    double last_diff = 0;
    int c = 0;
    forn(it,100000) {
        double diff = 0;
        forn(p_idx,P) {
            double sum = 0;
            forn(i, si(p_reqs[p_idx])) {
                int s_id = p_reqs[p_idx][i].fst;
                sum += s_value[s_id];
            }
            double new_value = p_score[p_idx] / (p_takes[p_idx]*sum);
            diff += abs(new_value-p_value[p_idx]);
            p_value[p_idx] = new_value*0.9 + p_value[p_idx]*0.1;
        }
        
        forn(s_idx,S) {
             double sum = 0;
             forn(i, si(s_required[s_idx])) {
                 sum += p_value[s_required[s_idx][i]];
             }
             diff += abs(sum-s_value[s_idx]);
             s_value[s_idx] = sum*0.9 + s_value[s_idx]*0.1;
        }
        //~ D(it);
        //~ D(diff);
        //~ D(abs(diff-last_diff));
        //~ D(c);
        if (diff<1e-9) break;
        //~ if (abs(diff-last_diff)<1e-6) {
            //~ if (c++ == 10) break;
        //~ } else c = 0;
        last_diff=diff;
    }
    
    forn(c_idx, C) {
        c_value[c_idx]=0;
        forn(p_idx,P) {
            forn(r, si(p_reqs[p_idx])) {
                int s_id = p_reqs[p_idx][r].fst;
                int s_lvl = p_reqs[p_idx][r].snd;
                if (c_skill_original[c_idx][s_id]>=s_lvl) {
                    c_value[c_idx]+=p_value[p_idx];
                } else if (s_lvl==1 || c_skill_original[c_idx][s_id]==s_lvl-1) {
                    c_value[c_idx]+=p_value[p_idx]*0.5;
                }
            }
        }
    }
    forn(p_idx, P) {
        p_cost[p_idx]=0;
        forn(r, si(p_reqs[p_idx])) {
            int s_id = p_reqs[p_idx][r].fst;
            p_cost[p_idx] += s_value[s_id];
        }
    }
    
}

void clear_problem() {
    c_name.clear(); c_skill_original.clear(); c_value.clear();
    p_name.clear(); p_takes.clear(); p_score.clear(); p_before.clear(); p_reqs.clear(); p_value.clear(); p_reqs_map.clear(); p_cost.clear();
    s_value.clear(); s_required.clear();
}

struct SingleAnswer {
    vector<int> c_selecteds;
    bool fail;
    ll t_start, t_end, real_value;
    double ratio;
    SingleAnswer() {
        fail = true;
        ratio = 0;
        t_start = 1e9;
        t_end = 0;
    }
};

SingleAnswer assign(int p_idx,int p_start_time) {
    int R =si(p_reqs[p_idx]); 
    SingleAnswer result;
    result.t_start = p_start_time;
    result.t_end = p_start_time + p_takes[p_idx];
    result.real_value = p_score[p_idx] - max(0LL,result.t_end-p_before[p_idx]);
    result.fail = false;
    result.c_selecteds.resize(R);
    
    set<int> c_selecteds_set;
    set<int> s_selected_set;
    forn(r,R) {
        int r_idx = r_ord[p_idx][r];
        int s_idx = p_reqs[p_idx][r_idx].fst;
        int req_lvl = p_reqs[p_idx][r_idx].snd; 
        
        int c_selected = -1;
        double c_selected_value = 1e18;
        forn(c_idx, C) if (!c_selecteds_set.count(c_idx) && c_busy[c_idx] <= p_start_time) {
            auto it = c_skill[c_idx].find(s_idx);
            int c_lvl = it == c_skill[c_idx].end() ? 0 : it->snd;
            
            if ( ( c_lvl >= req_lvl || (s_selected_set.count(s_idx) && c_lvl==req_lvl-1)) && 
                 c_selected_value > c_value[c_idx]) {
            //~ if (c_lvl >= req_lvl && c_selected_value > c_value[c_idx] ) {
               c_selected = c_idx; 
               c_selected_value = c_value[c_idx];
            }
        }
        if (c_selected==-1) {
            result.fail = true;
        } else {
            c_selecteds_set.insert(c_selected);
            result.c_selecteds[r_idx]=c_selected;
            for(const auto& [other_skill_id, other_skill_lvl] : c_skill[c_selected]) {
                auto it = p_reqs_map[p_idx].find(other_skill_id);
                if (it!=p_reqs_map[p_idx].end() && it->snd <= other_skill_lvl) {
                    s_selected_set.insert(other_skill_id);
                }
            }
        }
    }
    
    if (!result.fail) {
        assert(si(c_selecteds_set)==R);
        double p_real_cost = 0; 
        forn(r, R) {
            int c_idx = result.c_selecteds[r];
            p_real_cost += (result.t_end - c_busy[c_idx]) * c_value[c_idx];
        }
        result.ratio = result.real_value/p_real_cost;
    }
    return result;
}

vector<pair<int,vi>> anss;
#define EPS 1e-8

ll solve() {
    anss.clear();
    p_ord.resize(P);
    forn(i,P) p_ord[i]=i;
    sort(p_ord.begin(), p_ord.end(), [] (const int& i, const int& j) {
        return mp(p_value[i],i)>mp(p_value[j],j);
        //~ return mp(p_before[i],i)<mp(p_before[j],j);
        //~ return mp(p_before[i]-p_takes[i],i)<mp(p_before[j]-p_takes[j],j);
        //~ return mp(p_score[i],i)>mp(p_score[j],j);
    });
    
    r_ord.resize(P);
    forn(p_idx,P) {
        r_ord[p_idx].resize(si(p_reqs[p_idx]));
        forn(r,si(p_reqs[p_idx])) {
            r_ord[p_idx][r]=r;
        }
        sort(r_ord[p_idx].begin(), r_ord[p_idx].end(), [p_idx] (const int& i, const int& j) {
            return mp(s_value[p_reqs[p_idx][i].fst],i)<mp(s_value[p_reqs[p_idx][j].fst],j);
        });
    }
    
    c_skill = c_skill_original;
    c_busy.resize(C); 
    //~ c_skill_have.resize(S);
    forn(c_idx,C) {
        c_busy[c_idx]=0;
        //~ for(const auto& [s_idx, _] : c_skill[c_idx]) {
            //~ c_skill_have[s_idx].pb(c_idx);
        //~ }
    }
    
    ll anss_value = 0;
    forn(i,P) {
        int p_idx = p_ord[i];
        int R =si(p_reqs[p_idx]); 
        
        int a = 0;
        //~ int b = 2e5;
        int b = p_score[p_idx]+p_before[p_idx]-p_takes[p_idx];
        while(b-a > 20) {
            int l = (2*a+b) / 3;
            int r = (a+2*b) / 3;
            SingleAnswer l_ans = assign(p_idx, l);
            SingleAnswer r_ans = assign(p_idx, r);
            if ( r_ans.fail ) {
                a = r+1;
            } else if ( l_ans.fail ) {
                a = l+1;
            } else if ( l_ans.ratio < EPS ) {
                b = l-1;
            } else if ( l_ans.ratio < EPS ) {
                b = r-1;
            } else if ( l_ans.ratio < r_ans.ratio) {
                a = l+1;
            } else {
                b = r-1;
            }
        }
        SingleAnswer ans;
        forsn(p_start_time, a,b+1) {
            SingleAnswer curr = assign(p_idx, p_start_time);
            if ( (ans.fail && !curr.fail) ||
                 (!ans.fail && !curr.fail && ans.ratio < curr.ratio+EPS) ) {
               ans = curr;
            }
        }
    
        D(i);
        if ( !ans.fail ) {
            // Updates anss, c_busy, c_skill
            assert(si(ans.c_selecteds)==R);
            anss.pb(mp(p_idx,ans.c_selecteds));
            forn(r_idx,R) {
                int c_idx = ans.c_selecteds[r_idx];
                c_busy[c_idx] = ans.t_end;
                
                int s_idx = p_reqs[p_idx][r_idx].fst;
                int req_lvl = p_reqs[p_idx][r_idx].snd; 
                auto it = c_skill[c_idx].find(s_idx);
                int c_lvl = it == c_skill[c_idx].end() ? 0 : it->snd;
                if (req_lvl >= c_lvl) {
                    c_skill[c_idx][s_idx]++;
                }
            }
            D(ans.real_value);
            anss_value += ans.real_value;
        } else {
            D("FAIL");
        }
    }
    
    D(anss_value);
    
    
    p_ord.clear(); r_ord.clear();
    c_busy.clear();
    //~ c_skill_have.clear();
    return 0;
}

void print_solution() {
    cout << si(anss) << endl;
    for(const auto& [p_idx, c_idxs] : anss) {
        cout << p_name[p_idx] << endl;
        forn(j, si(c_idxs)) {
            cout << c_name[c_idxs[j]] << (j==si(c_idxs)-1 ? '\n' : ' ');
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        //~ freopen("./in/a_an_example.in", "r", stdin);
        freopen("./in/b_better_start_small.in", "r", stdin);
        //~ freopen("./in/c_collaboration.in", "r", stdin);
        //~ freopen("./in/d_dense_schedule.in", "r", stdin);
        //~ freopen("./in/e_exceptional_skills.in", "r", stdin);
        //~ freopen("./in/f_find_great_mentors.in", "r", stdin);
    #endif

    read_input();
    
    //~ forn(i,P) {
        //~ cout << p_name[i] << ' ' << p_value[i] << " // ";
    //~ }
    //~ cout << endl;
    //~ forn(i,S) {
        //~ cout << s_name[i] << ' ' << s_value[i] << " // ";
    //~ }
    //~ cout << endl;
    //~ forn(i,C) {
        //~ cout << c_name[i] << ' ' << c_value[i] << " // ";
    //~ }
    
    solve();
    
    print_solution();
    
    clear_problem();
    
    return 0;
}
