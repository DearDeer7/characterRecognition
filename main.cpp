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
// not used yet!
vector<string> crop(vector<string>& vs) {
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
            if(i >= 300 || j >= 300) cur += '0';
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
    return vs;
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
//        out << cur << endl;
    }
//    out << endl;
    return sub;
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

// get a set of ratios of all subMatrices
vector<double> getRatios(vector<string>& vs) {
    vector<double> ans;
    vector<string> sub = getSub(vs, 0, 0); // left top part
    ans.push_back(getRatio(sub));

    sub = getSub(vs, 0, 150); // right top part
    ans.push_back(getRatio(sub));

    sub = getSub(vs, 150, 0); // left down part
    ans.push_back(getRatio(sub));

    sub = getSub(vs, 150, 150); // right down part
    ans.push_back(getRatio(sub));

    return ans;
}

// calc match ratios and print results
void calc(const vector<vector<double>>& ratios,const vector<double>& myRatios) {
    vector<double> res(5);
    double mi = 1.0, idx = -1; // minimal value of ratio, index of minimal value
    for(int i = 0; i < 5; ++i) {
        double t = 0.0;
        for(int j = 0; j < 4; ++j) {
            t += fabs(ratios[i][j] - myRatios[j]); // absolute difference of two corresponding part
            cout << fabs(ratios[i][j] - myRatios[j]) << " ";
        }
        cout << endl;
        res[i] = t / 4;
        if(mi > res[i]) {
            mi = res[i];
            idx = i;
        }
//        cout << res[i] << " ";
    }
//    cout << endl;
    double percent = 1.0 - res[idx];
    cout << "Best Match = " << idx + 1 << " with ratio " << percent * 100.0 << "%\n\n";
}


int main() {

//    ofstream out(ADDR + "out.txt"); // output file, not used yet!
    vector<vector<double>> ratios; // sets of ratios of standard characters
    for(int i = 1; i <= 5; ++i) { // read and process five photos
        ifstream in(ADDR + to_string(i) + ".txt");
        if(!in) {
            cout << "failed to open file!\nquitting...\n\n";
            exit(0);
        }
        vector<string> M = getMatrix(in);
        ratios.push_back(getRatios(M));
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
        else if(option == 1) { // choose a standard character
            cout << "----Mode1----" << endl;
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
            vector<string> M = getMatrix(in);
            vector<double> myRatios = getRatios(M);
            in.close();

            calc(ratios, myRatios);
        }
        else if(option == 2) { // choose a handwritten character of ours
            cout << "----Mode2----" << endl;
            string txt;
            cout << "Please input full txt file name:" << endl;
            cin >> txt;
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
            vector<string> M = getMatrix(in);
            vector<double> myRatios = getRatios(M);
            in.close();

            calc(ratios, myRatios);
        }
        else if(option == 3) { // choose a handwritten character of teacher's
            cout << "----Mode3----" << endl;
            string txt;
            cout << "Please input txt full file name:" << endl;
            cin >> txt;
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
            vector<string> M = getMatrix(in);
            vector<double> myRatios = getRatios(M);
            in.close();

            calc(ratios, myRatios);
        }
        else { // illegal input messages
            cout << "illegal input!" << endl;
            exit(0);
        }

        out.close();
    }


    return 0;
}