#include<string>
#include<vector>
#include<unordered_set>
#include<iostream>

/**
Word Break problem - Given a string s and a dictionary, check whether the string can be broken down to valid words. Initially I was asked to return true or false based on whether string can be broken down or not. Later I was asked to modify my code to return the number of possible ways to break the string. Like for eg : "takebathandcome" can be broken down in 2 ways

    "take bath and come"
    "take bat hand come"
    So the modified function should return 2
*/

using namespace std;

int wordBreak(string s, unordered_set<string>& wordDict) {
  int m = s.size();
 //table of # of breaking down ways instead of true/false
  vector<int> dp(m + 1, 0);
  dp[0] = 1;
  for (int i = 1; i <= m; i++){
    for (int j = i - 1; j >= 0; j--){
      if (dp[j] &&
          wordDict.find(s.substr(j, i - j)) != wordDict.end()){
        dp[i] += dp[j];
      }
    }
  }
  return dp[m];
}

int main() {
  unordered_set<string> u{"take", "bat", "hand", "come", "bath", "and"};
  string s = "takebathandcome";
  cout << "\nTotal: " << wordBreak(s, u) << "\n";
return 0;
}
