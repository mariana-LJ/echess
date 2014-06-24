
#include "gtest/gtest.h"
#include "Board.h"
#include "common.h"
#include <vector>

using namespace std;


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

bool findMove(vector<square> & moves, square & move) {
  for(vector<square>::iterator it = moves.begin(); it != moves.end(); ++it) {
    if(it->row == move.row && it->column == move.column) {
      return true;
    }
  }
  return false;
}

TEST(MovePawn, Test1) {
  Board b;
  square s(1,4);
  vector<square> moves = b.getMoves(s);
  ASSERT_EQ(moves.size(),2);
  s.row = 2; s.column = 4;
  ASSERT_TRUE(findMove(moves,s));
  s.row = 3; s.column = 4;
  ASSERT_TRUE(findMove(moves,s));
}
