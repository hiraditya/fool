#include <queue>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

/* Inserting latest 5000 records in
   container along with timestamp and retrieve them as needed and discard which are older then 5000. 
*/

typedef std::chrono::time_point<std::chrono::system_clock> Time;

class Record {
  int i;
public:
  friend std::istream& operator>>(std::istream &is, Record &r);
  friend std::ostream& operator<<(std::ostream &os, const Record &r);
};

std::istream& operator>>(std::istream &is, Record &r) {
  is >> r.i;
  return is;
}

std::ostream& operator<<(std::ostream &os, const Record &r) {
  os << " " << r.i;
  return os;
}

typedef std::pair<Record, Time> Data;

struct MaintainRecords {
  const int Max;
  std::queue<Data> q;

  MaintainRecords(int m) : Max(m) {}

  std::queue<Data>& get_queue() {
    return q;
  }

  void insert(Data d) {
    if (q.size() == Max)
      q.pop();
    q.push(d);
  }

  void insert(Record r, Time t) {
    insert(std::make_pair(r, t));
  }
};

int main() {
  MaintainRecords m(5000);
  std::ifstream data("elements.txt");
  Record r;
  while(data >> r) {
    Time t = std::chrono::system_clock::now();
    m.insert(r, t);
    std::this_thread::sleep_for(std::chrono::microseconds(10));
  }
  auto &q = m.get_queue();
  while (!q.empty()) {
    auto &rec = q.front();
    //std::time_t now_c = std::chrono::system_clock::to_time_t(rec.second);
    std::cout << rec.first; // << ", time: " << now_c << "\n";
    q.pop();
  }
  return 0;
}
