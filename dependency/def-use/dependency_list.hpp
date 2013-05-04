#include<vector>
#include<list>
#include<map>

#include<bitset>
#include<cassert>

#include<algorithm>

template<typename T, typename Block>
class Dependency {
  typedef std::vector<T> ProducerList;
  typedef std::vector<T> ConsumerList;
  typedef std::vector<T> PathList;
  typedef std::list<Block> BlockList;
  typedef std::map<Block, BlockList> Paths_t;
  //typedef std::bitset DUPV;

  ProducerList Producers;
  ConsumerList Consumers;
  Paths_t Paths;
  //DUPV Dupv;

  public:
  void AddProducer(const T& t) { Producers.push_back(t); }
  void AddConsumer(const T& t) { Consumers.push_back(t); }
  /**
   * A -> B, B -> C 
   * => A --> ABC
   */
  void AddPath(const Block& From, const Block& To) {
    // When no entry enter From as well.
    if(Paths.find(From) == Paths.end()) {
      Paths[From].push_back(From);
    }
    Paths[From].push_back(To);
  }
  /**
   *  For a path ABCDE; From = A, To = C
   *  => AB 
   *  i.e., CDE is removed
   */
  void RemovePath(const Block& From, const Block& To) {
    typename Paths_t::iterator entry = Paths.find(From);
    assert(entry != Paths.end());
    typename BlockList::iterator b_entry = 
      std::find(entry->second.begin(), entry.second.end(), To);
    assert(b_entry != entry->second.end());
    entry.remove(b_entry, entry->second.end());
  }
  typename Paths_t::const_iterator PathExists(const Block& From, const Block& To) {
    typename Paths_t::const_iterator entry = Paths.find(From);
    if(entry != Paths.end()) {
      typename BlockList::iterator b_entry = 
        std::find(entry->second.begin(), entry->second.end(), To);
      if(b_entry != entry->second.end())
        return entry;
    }
    return Paths.end();  
  }
};
