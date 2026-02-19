#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

// Fungsi bantuan untuk menghitung (10^p) % m
long long power(long long base, long long exp, long long m) {
    long long res = 1;
    base %= m;
    while (exp > 0) {
        if (exp % 2 == 1) res = (__int128)res * base % m;
        base = (__int128)base * base % m;
        exp /= 2;
    }
    return res;
}

// Fungsi utama dengan logika Divide and Conquer
long long helper(long long n, int m) {
    if (n == 1) return 1 % m;
    
    if (n % 2 == 0) {
        long long half = helper(n / 2, m);
        long long p = power(10, n / 2, m);
        // (11...1 {n/2 kali} * (10^{n/2} + 1)) % m
        return ((__int128)half * (p + 1)) % m;
    } else {
        long long prev = helper(n - 1, m);
        // (11...1 {n-1 kali} * 10 + 1) % m
        return ((__int128)prev * 10 + 1) % m;
    }
}

int solve(long n, int m) {
    if (n == 0) return 0;
    return (int)helper(n, m);
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        long n = stol(first_multiple_input[0]);

        int m = stoi(first_multiple_input[1]);

        int result = solve(n, m);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
