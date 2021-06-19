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

// crop matrix
// make sure the character is at left top
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
    vector<string> ans;
    for(int i = 0; i < vs.size() + u; ++i) {
        if(i < u) continue;
        string cur;
        for(int j = 0; j < vs[0].size() + l; ++j) {
            if(j < l) continue;
            if(i >= sz || j >= sz) cur += '0';
            else cur += vs[i][j];
        }
        ans.push_back(cur);
    }
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

// get a specified subMatrix by given r and c (starting index)
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

// get subMatrices of M
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
    return one * 1.0 / (one + zero);
}

// get difference ratio of two characters
double getRatios(vector<vector<string>>& subM_S, vector<vector<string>>& subM_T) {
    double diff = 0;
    for(int i = 0; i < 4; ++i ) {
        diff += fabs(getRatio(subM_S[i]) - getRatio(subM_T[i]));
    }
    return diff / 4.0;
}

// search with point (row, col) in M in four directions to detect '1'
int search(vector<string>& M, int row, int col) {
    if(M[row][col] == '1') return 1;

    vector<int> dirs{0,1,0,-1,0};
    for(int i = 0; i < 4; ++i) {
        int y = row + dirs[i];
        int x = col + dirs[i + 1];
        if(y < 0 || y >= M.size() || x < 0 || x >= M[0].size()) continue;
        if(M[y][x] == '1') return 1;
    }
    return 0;
}

// get match rate of two matrix
double getMatch(vector<string>& sub_s, vector<string>& sub_t) {
    int r = sub_s.size(), c = sub_s[0].size();
    int match = 0;
    int raw_one = 0;
    for(int i = 0; i < r; ++i) {
        for(int j = 0; j < c; ++j) {
            if(sub_t[i][j] == '1') {
                raw_one++;
                match += search(sub_s, i, j);
            }
        }
    }
    if(raw_one == 0) return 0;
    return match * 1.0 / raw_one; // divide overlapped one with one in sub_s
}

// get match rates of two characters
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

    vector<double> matches_S; // 重合度数组
    vector<double> ratios_S; // 像素差数组
    for(auto& M_S : MM_S) {
        vector<vector<string>> subM_S = getSubs(M_S); // a character's subMatrices
        matches_S.push_back(getMatches(subM_S, subM_T));
        ratios_S.push_back(getRatios(subM_S, subM_T));
    }

    double ma = 0, idx = -1; // max value of ratio, index of max value
    vector<double> overalls(5); // 综合得分（相似度）
    for(int i = 0; i < 5; ++i) {
        overalls[i] = matches_S[i] * 0.8 + (1.0 - ratios_S[i]) * 0.2;
        if(overalls[i] > ma) {
            ma = overalls[i];
            idx = i;
        }
    }

    // 格式化输出
    for(int i = 0; i < matches_S.size(); ++i) {
        if(i == 0) {
            cout << "------------------------------------------------\n|重合度\t|";
        }
        printf(" %.2f\t|", matches_S[i]);
    }
    for(int i = 0; i < ratios_S.size(); ++i) {
        if(i == 0) {
            cout << "\n|像素差\t|";
        }
        printf(" %.2f\t|", ratios_S[i]);
    }
    for(int i = 0; i < overalls.size(); ++i) {
        if(i == 0) {
            cout << "\n|相似度\t|";
        }
        printf(" %.2f\t|", overalls[i]);
    }
    cout << "\n------------------------------------------------\n";


    unordered_map<int, string> mp; // key-val binds
    mp[0] = "开";
    mp[1] = "心";
    mp[2] = "人";
    mp[3] = "鱼";
    mp[4] = "少";
    cout << "Best Match is " << idx + 1 << "（" << mp[idx] << "）" << " with rate ";
    printf("%.2f%\n\n",ma * 100);
}


int main() {

    vector<vector<string>> MM_S; // sets of source Matrix of standard characters
    for(int i = 1; i <= 5; ++i) { // read and process five sample photos
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
        else if(option >= 1 && option <= 3) {
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
            if(!in) { // file open check
                cout << "failed to open file!\nquitting...\n\n";
                exit(0);
            }
            vector<string> M_T = getMatrix(in);
            in.close();

            calc(MM_S, M_T); // character recognition and print results
        }
        else { // legal option input check
            cout << "illegal option!" << endl;
        }

    }

    return 0;
}