#include <iostream>
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
  s.insert(9);
  s.insert(15);
  s.insert(16);
  for (auto i : s) {
    cout << i << endl;
  }
}
