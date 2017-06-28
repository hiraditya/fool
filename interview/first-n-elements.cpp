#include<queue>
#include <iostream>
#include <chrono>

/* Very simply question of inserting latest 5000 records in
   container along with timestamp and retrieve them as needed and discard which are older then 5000. 
*/

struct Record {
};

typedef std::pair<Record, Time> Data;

struct MaintainRecords {
  const int Max;
  std::queue<Data> q;

  MaintainRecords(int m) : Max(m) {}

  void insert(Data d) {
    if (q.size() == Max)
      q.pop_front();
    q.push_back(d);
  }

  void insert(Record r, Time t) {
    insert(std::make_pair(r, t));
  }
};

int main() {
  MaintainRecords m(5000);
  Record r;
  while(data >> r) {
    std::chrono::time_point<std::chrono::system_clock> t = std::chrono::system_clock::now();
    insert(r, t);
  } 
}

