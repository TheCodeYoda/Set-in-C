#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

struct cmp {
  bool operator()(int a, int b)
  {
    return (a % 3) < (b % 3);
  }
};

int main()
{
  set<int, cmp> s;
  s.insert(1);
  s.insert(3);
  s.insert(5);
  s.insert(7);
  s.insert(4);
  s.insert(2);
  for (auto i : s) {
    cout << i << endl;
  }
  set<int>::iterator lower, upper;
  lower = lower_bound(s.begin(), s.end(), 5);
  upper = upper_bound(s.begin(), s.end(), 5);
  cout << *lower << " " << *upper << endl;
}
