#include<string>
#include<vector>
#include<unordered_set>

/**
Word Break problem - Given a string s and a dictionary, check whether the string can be broken down to valid words. Initially I was asked to return true or false based on whether string can be broken down or not. Later I was asked to modify my code to return the number of possible ways to break the string. Like for eg : "takebathandcome" can be broken down in 2 ways

    "take bath and come"
    "take bat hand come"
    So the modified function should return 2
*/

using namespace std;

int wordBreak(string s, unordered_set<string>& wordDict) {
  int m = s.size();
  vector<int> dp(m + 1, 0); //table of # of breaking down ways instead of true/false
  dp[0] = 1;
  for (int i = 1; i <= m; i++){
    for (int j = i - 1; j >= 0; j--){
      if (dp[j] && wordDict.find(s.substr(j, i - j)) != wordDict.end()){
        dp[i] += dp[j];    
      }
    }
  }
  return dp[m];
}

int main() {

return 0;
}
