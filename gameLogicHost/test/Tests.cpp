
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

TEST(MoveKnight, Test1){
  Board b;
  vector<movement> moves = b.getMoves(0,1);

  ASSERT_EQ(moves.size(),2);
  ASSERT_NE(findMove(moves, 2, 0), moves.end());
  ASSERT_NE(findMove(moves, 2, 2), moves.end());
}

TEST(MoveBishop, Test1){
  Board b;
  vector<movement> moves = b.getMoves(1,4);
  b.move(moves.at(0)); // Move the pawn in front of white King

  moves = b.getMoves(0,5); //Get possible moves for bishop at 0,5
  ASSERT_EQ(moves.size(),5);

}

TEST(MoveRook, Test1){
  Board b;
  vector<movement> moves = b.getMoves(1,0);

  b.move(moves.at(1)); // Move the pawn in front of rook at 0,0 by 2 squares

  moves = b.getMoves(0,0);
  ASSERT_EQ(moves.size(),2);

}

TEST(BigTest, Test1){
  Board b;
  int indexMove;
  vector<movement> moves = b.getMoves(1,3);

  ASSERT_NE(findMove(moves, 3, 3), moves.end());
  b.move(moves.at(1)); // Queen's pawn to (3,3)

  moves = b.getMoves(6,3);
  ASSERT_NE(findMove(moves, 4, 3), moves.end());
  indexMove = distance(moves.begin(), findMove(moves, 4, 3));
  b.move(moves.at(indexMove)); // Black Queen's pawn to (4,3)

  moves = b.getMoves(0,1); // White Knight from (0,1) to (2,2)
  ASSERT_EQ(moves.size(),3);
  indexMove = distance(moves.begin(), findMove(moves, 2, 2));
  b.move(moves.at(indexMove));

  moves = b.getMoves(7,6); // Black Knight from (7,6) to (5,5)
  indexMove = distance(moves.begin(), findMove(moves, 5, 5));
  b.move(moves.at(indexMove));

  moves = b.getMoves(7,6); // White bishop from (0,2) to (4,6)
  ASSERT_EQ(moves.size(),5);
  indexMove = distance(moves.begin(), findMove(moves, 4, 6));
  b.move(moves.at(indexMove));
}
