
/*
X~~~~~~~~~~~~~~~~~~~~~_______($)
*****  *   * * *  *  *
011 2  3   4   4  3  3   4 (crossed)
01 2 2 (failed)
01111 2 (failed)

Initial location: 0
Initial speed: 0

each step:
    1. choose a new speed from {speed, speed + 1, speed - 1} (but not negative)
    2. move speed spaces: loc += speed
    3. if I land on water, I fail
    4. if I land past end of river, I win
    5. otherwise, keep going

Given a string representation of the rocks in the river e.g. "*****  *   * * *  *  *", determine whether the river is crossable.

can_cross_river("*****  *   * * *  *  *")
--> True
*/

// * is an object is the space where frog can land on
// space is like water where frog will sink
// explore a combination which results in successful crossing of river

/*
length of river
islands are the landing points (at the landing point the speed should be within +/-1 of the distance of the next island)
*/


/*
X~~~...
"* *"
 012
  
Speed: 0
Index: 0

Speed: 1
Index: 0

Speed: 2
Index: 2

*/

bool can_cross_river(string islands, string river, int speed = 0) {
  bool success = true;
  int r_pos = 0;
  if (river.size() == 0)
    return true;
  if (islands[0] != '*')
    return false;
  if (speed == 0 && islands[1] != '*')
    return false;
  if (speed < 0)
    return false;
  // at any point choose within +/-1 of speed
  if (speed && islands[speed] == '*') {
    string r = river.substr(speed);
    string i = islands.substr(speed);
    if (can_cross_river(i, s, speed)) {
      return true;
    }
  }
  if (islands[speed + 1] == '*') {
    string r = river.substr(speed + 1);
    string i = islands.substr(speed + 1);
    if (can_cross_river(i, s, speed + 1))
      return true;
  }
  if (speed && islands[speed -1] == '*') {
    string r = river.substr(speed - 1);
    string i = islands.substr(speed - 1);
    if (can_cross_river(i, s, speed - 1))
      return true;
  }
  else
    return false;
} 
}
