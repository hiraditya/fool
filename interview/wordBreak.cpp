#include<string>
#include<vector>
#include<unordered_set>
#include<iostream>

/**
Word Break problem - Given a string s and a dictionary, check whether the string
can be broken down to valid words. Initially I was asked to return true or false
based on whether string can be broken down or not. Later I was asked to modify
my code to return the number of possible ways to break the string. Like for eg :
"takebathandcome" can be broken down in 2 ways

    "take bath and come"
    "take bat hand come"
    So the modified function should return 2
*/

using namespace std;

int word_break(string s, unordered_set<string>& word_dict) {
  int m = s.size();
  // Table of # of breaking down ways instead of true/false
  vector<int> dp(m + 1, 0);
  dp[0] = 1;
  for (int i = 1; i <= m; i++){
    for (int j = i - 1; j >= 0; j--){
      if (dp[j] &&
          word_dict.find(s.substr(j, i - j)) != word_dict.end()){
        dp[i] += dp[j];
        std::cout << s.substr(j, i-j) << " ";
      }
    }
  }
  return dp[m];
}

// Returns true of false if a string can be broken down. Beats everyone on leetcode.
bool wordBreak(string s, const vector<string>& wordDict) {
  if (std::find(wordDict.begin(), wordDict.end(), s) != wordDict.end())
    return true;

  int longestWord = 0;
  for(int i = 0; i < wordDict.size(); ++i){
    longestWord = max(longestWord, (int)wordDict[i].size());
  }

  int m = s.size();
  // Table of # of breaking down ways instead of true/false
  vector<bool> dp(m + 1, 0);
  dp[0] = true;
  for (int i = 1; i <= m; i++){
    for (int j = i - 1; j >= max(0, i-longestWord); j--){
      if (dp[j]) {
        if (std::find(wordDict.begin(), wordDict.end(), s.substr(j, i - j)) != wordDict.end()) {
          dp[i] = true;
          break;
        }
      }
    }
  }
  return dp[m];
}

bool word_break_b(string s, unordered_set<string>& word_dict) {
  int m = s.size();
  vector<bool> dp(m+1, false);
  dp[0] = true;
  for (int i = 1; i <= m; ++i) {
    for (int j = i-1; j >= 0; --j) {
      if (dp[j] && (word_dict.find(s.substr(j, i-j)) != word_dict.end())) {
        dp[i] = true;
        break;
      }
    }
  }
  return dp[m];
}

int main() {
  unordered_set<string> u{"take", "bat", "hand", "come", "bath", "and", "at", "takeb"};
  string s = "takebathandcome";
  cout << "\nTotal: " << word_break_b(s, u) << "\n";
  cout << "\nTotal: " << word_break(s, u) << "\n";
return 0;
}
