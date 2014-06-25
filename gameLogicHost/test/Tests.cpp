
#include "gtest/gtest.h"
#include "Board.h"
#include "common.h"
#include <vector>

using namespace std;


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

vector<movement>::iterator findMove(vector<movement> & moves, int row, int column) {
  vector<movement>::iterator it;
  for(it = moves.begin(); it != moves.end(); ++it) {
    if(it->target_row == row && it->target_column == column) {
      break;
    }
  }
  return it;
}

TEST(MovePawn, Test1) {
  Board b;
  vector<movement> moves = b.getMoves(1,4);
  ASSERT_EQ(moves.size(),2);
  ASSERT_NE(findMove(moves, 2, 4), moves.end());
  ASSERT_NE(findMove(moves, 3, 4), moves.end());
  b.move(*findMove(moves, 3, 4));
  moves = b.getMoves(6,4);
  ASSERT_EQ(moves.size(),2);
  ASSERT_NE(findMove(moves, 5, 4), moves.end());
  ASSERT_NE(findMove(moves, 4, 4), moves.end());
  b.move(*findMove(moves, 4, 4));
  moves = b.getMoves(3,4);
  ASSERT_EQ(moves.size(),0);
}
