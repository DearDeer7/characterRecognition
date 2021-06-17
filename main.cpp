/*
 * created by deardeer
 * c++11 standard
 * */
#include <bits/stdc++.h>
using namespace std;

// created a directory named files,
// then copy your files path into ADDR string below
// remember to add "\\" in the end
const string ADDR = "C:\\Users\\14795\\Desktop\\CR\\files\\";
ofstream out(ADDR + "out.txt"); // output file, not used yet!

// crop matrix
// make sure the character is right at left top
// and matrix size stay 300*300
vector<string> crop(vector<string>& vs) {
    const int sz = vs.size();
    int l = INT_MAX;
    int r = INT_MIN;
    int u = INT_MAX;
    int d = INT_MIN;
    for(int i = 0; i < vs.size(); ++i) {
        for(int j = 0; j < vs[0].size(); ++j) {
            char& c = vs[i][j];
            if(c == '1') {
                l = min(l, j);
                r = max(r, j);
                u = min(u, i);
                d = max(d, i);
            }
        }
    }
//    cout << l << " " << r << " " << u << " " << d << endl;
//    int len = max(r - l + 1, d - u + 1);
//    r = l + len;
//    d = u + len;
//    cout << l << " " << r << " " << u << " " << d << endl;
    vector<string> ans;
    for(int i = 0; i < vs.size() + u; ++i) {
        if(i < u) continue;
        string cur;
        for(int j = 0; j < vs[0].size() + l; ++j) {
            if(j < l) continue;
            if(i >= sz || j >= sz) cur += '0';
            else cur += vs[i][j];
        }
        out << cur << endl;
        ans.push_back(cur);
    }
    out << endl;
    out << ans.size() << " "  << ans[0].size() << endl;
    return ans;
}

// get character matrix by ifstream
// i.e. read bit matrix from file
vector<string> getMatrix(ifstream& in) {
    vector<string> vs;
    string s;
    while(getline(in, s)) {
        vs.push_back(s);
    }
    return crop(vs);
}

// get subMatrix by given r and c (starting index)
vector<string> getSub(vector<string>& vs, int r, int c) {
    vector<string> sub;
    for(int i = 0; i <= 149; ++i) {
        string cur;
        for(int j = 0; j <= 149; ++j) {
            cur.push_back(vs[i + r][j + c]);
        }
        sub.push_back(cur);
    }
    return sub;
}

vector<vector<string>> getSubs(vector<string>& M) {
    vector<vector<string>> vvs;
    vvs.push_back(getSub(M, 0, 0));
    vvs.push_back(getSub(M, 0, 150));
    vvs.push_back(getSub(M, 150, 0));
    vvs.push_back(getSub(M, 150, 150));
    return vvs;
}

// get character pixel ratio
double getRatio(vector<string>& vs) {
    int one = 0, zero = 0;
    for(auto& s : vs) {
        for(char c : s) {
            if(c == '1') one++;
            else zero++;
        }
    }
    if(one == 0){
        cout << "No pixel found!" << endl;
        exit(0);
    }
    return one * 1.0 / (one + zero);
}

double getRatios(vector<vector<string>>& subM_S, vector<vector<string>>& subM_T) {
    double diff = 0;
    for(int i = 0; i < 4; ++i ) {
        diff += fabs(getRatio(subM_S[i]) - getRatio(subM_T[i]));
    }
    return diff / 4.0;
}

double getMatch(vector<string>& sub_s, vector<string>& sub_t) {
    int r = sub_s.size(), c = sub_s[0].size();
    int match = 0;
    int raw_one = 0;
    for(int i = 0; i < r; ++i) {
        for(int j = 0; j < c; ++j) {
            if(sub_s[i][j] == '1') {
                raw_one++;
                if(sub_s[i][j] == sub_t[i][j]) match++;
            }
        }
    }
    return match * 1.0 / raw_one; // divide overlapped one with one in sub_s
}

double getMatches(vector<vector<string>>& subM_S, vector<vector<string>>& subM_T) {
    double res = 0;
    for(int i = 0; i < 4; ++i) {
        res += getMatch(subM_S[i], subM_T[i]);
    }
    return res / 4.0;
}

// calc match ratios and print results
void calc(vector<vector<string>>& MM_S, vector<string>& M_T) {
    vector<vector<string>> subM_T = getSubs(M_T);

    vector<double> matches_S;
    vector<double> ratios_S;
    for(auto& M_S : MM_S) {
        vector<vector<string>> subM_S = getSubs(M_S); // a character's subMatrices
        matches_S.push_back(getMatches(subM_S, subM_T));
        ratios_S.push_back(getRatios(subM_S, subM_T));
    }

    double ma = 0, idx = -1; // max value of ratio, index of minimal value
    for(int i = 0; i < matches_S.size(); ++i) {
        cout << matches_S[i] << " " << ratios_S[i] << endl;
        double t = matches_S[i] * 0.8 + ratios_S[i] * 0.2;
        if(t == 0) t = matches_S[i] + ratios_S[i];
        if(t > ma) {
            ma = t;
            idx = i;
        }
    }

    cout << "Best Match = " << idx + 1 << " with ratio " << ma * 100.0 << "%\n\n";

//    vector<double> res(5);
//    double mi = 1.0, idx = -1; // minimal value of ratio, index of minimal value
//    for(int i = 0; i < 5; ++i) {
//        double t = 0.0;
//        for(int j = 0; j < 4; ++j) {
//            t += fabs(ratios[i][j] - myRatios[j]); // absolute difference of two corresponding part
//            cout << fabs(ratios[i][j] - myRatios[j]) << " ";
//        }
//        cout << endl;
//        res[i] = t / 4;
//        if(mi > res[i]) {
//            mi = res[i];
//            idx = i;
//        }
////        cout << res[i] << " ";
//    }
////    cout << endl;
//    double percent = 1.0 - res[idx];
//    cout << "Best Match = " << idx + 1 << " with ratio " << percent * 100.0 << "%\n\n";
}


int main() {

//    ofstream out(ADDR + "out.txt"); // output file, not used yet!
    vector<vector<string>> MM_S; // sets of source Matrix of standard characters
    for(int i = 1; i <= 5; ++i) { // read and process five photos
        ifstream in(ADDR + to_string(i) + ".txt");
        if(!in) {
            cout << "failed to open file!\nquitting...\n\n";
            exit(0);
        }
        vector<string> M = getMatrix(in);
        MM_S.push_back(M);
        in.close();
    }

    int option = -1; // user's option
    while(option != 0) {
        cout << "Notes: input 0 to quit..." << endl;
        cout << "Please input option:" << endl;
        cin >> option;
        if(option == 0) {
            cout << "quitting..." << endl;
            exit(0);
        }
        else if(option >= 1 || option <= 3) {
            cout << "----Mode" << option << "----" << endl;
            string txt;
            cout << "Please input full txt file name:" << endl;
            cin >> txt; // full txt file name, such as 1.txt, h_1.txt, xxx.txt
            while(txt.size() < 5 || txt.rfind(".txt") == string::npos) { // input check
                cout << "illegal input!" << endl;
                cout << "Please input full txt file name:" << endl;
                cin >> txt; // full txt file name, such as 1.txt, h_1.txt, xxx.txt
            }
            ifstream in(ADDR + txt);
            if(!in) {
                cout << "failed to open file!\nquitting...\n\n";
                exit(0);
            }
            vector<string> M_T = getMatrix(in);
            in.close();

            calc(MM_S, M_T);
        }

        out.close();
    }


    return 0;
}