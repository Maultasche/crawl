#include <assert.h>
#include <iostream>

#include "domino.h"
#include "domino_data.h"

using namespace domino;
using namespace std;

template <class T>
void test_symmetry(DominoSet<T>& dominoes) {
  const uint8_t domino_count = dominoes.size();
  for (uint8_t i = 0; i < domino_count; ++i) {
    T d = dominoes.get(i);
    for (uint8_t j = 0; j < domino_count; ++j) {
      T other = dominoes.get(j);
      for (int dir_idx = FIRST_DIRECTION; dir_idx <= LAST_DIRECTION; ++dir_idx) {
        Direction dir = static_cast<Direction>(dir_idx);
        if (d.matches(other, dir)) {
          assert(other.matches(d, reverse(dir)));
        } else {
          assert(!other.matches(d, reverse(dir)));
        }
      }
    }
  }
}

int main(int argc, char** argv) {
  DominoSet<CornerDomino> dominoes(domino::periodic_set, 16);
  DominoSet<CornerDomino> aperiodic_dominoes(domino::aperiodic_set, 44);
  DominoSet<EdgeDomino> cohen_dominoes(domino::cohen_set, 8);
  test_symmetry(dominoes);
  test_symmetry(aperiodic_dominoes);
  vector<uint8_t> output;
  cohen_dominoes.Generate(60, 20, output);
  dominoes.Generate(10, 10, output);
  return 0;
}