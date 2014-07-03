
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
  Board b1;
  vector<movement> moves = b1.getMoves(0,1);

  ASSERT_EQ(moves.size(),2);
  ASSERT_NE(findMove(moves, 2, 0), moves.end());
  ASSERT_NE(findMove(moves, 2, 2), moves.end());
}

TEST(MoveBishop, Test1){
  Board b;
  vector<movement> moves = b.getMoves(1,4);
  b.move(*findMove(moves, 3, 4)); // Move the pawn in front of white Queen

  moves = b.getMoves(0,5); //Get possible moves for bishop at 0,5
  ASSERT_EQ(moves.size(),5);

}


TEST(MoveRook, Test1){
  Board b;
  vector<movement> moves = b.getMoves(1,0);

  b.move(*findMove(moves, 3,0)); // Move the pawn in front of rook at 0,0 by 2 squares

  moves = b.getMoves(0,0);
  ASSERT_EQ(moves.size(),2);

}

TEST(BigTest, Test1){
  Board b;
  vector<movement> moves = b.getMoves(1,3);

  ASSERT_EQ(moves.size(),2);
  ASSERT_NE(findMove(moves, 3, 3), moves.end());
  b.move(*findMove(moves, 3, 3)); // Queen's pawn to (3,3): d4

  moves = b.getMoves(6,3);
  ASSERT_EQ(moves.size(),2);
  ASSERT_NE(findMove(moves, 4, 3), moves.end());
  b.move(*findMove(moves, 4, 3)); // Black Queen's pawn to (4,3): d5

  moves = b.getMoves(0,1); // White Knight from (0,1) to (2,2)
  ASSERT_EQ(moves.size(),3);
  ASSERT_NE(findMove(moves, 2, 2), moves.end());
  b.move(*findMove(moves, 2, 2));

  moves = b.getMoves(7,6); // Black Knight from (7,6) to (5,5)
  ASSERT_EQ(moves.size(),2);
  ASSERT_NE(findMove(moves, 5, 5), moves.end());
  b.move(*findMove(moves, 5, 5));

  moves = b.getMoves(0,2); // White bishop from (0,2) to (4,6)
  ASSERT_EQ(moves.size(),5);
  ASSERT_NE(findMove(moves, 4, 6), moves.end());
  b.move(*findMove(moves, 4, 6));

  moves = b.getMoves(7,2); // Black bishop from (7,2) to (2,7)
  ASSERT_EQ(moves.size(),5);
  ASSERT_NE(findMove(moves, 2, 7), moves.end());
  b.move(*findMove(moves, 2, 7));

  moves = b.getMoves(0,6); // White knight at (0,6) takes black bishop at (2,7)
  ASSERT_EQ(moves.size(), 2);
  ASSERT_NE(findMove(moves, 2, 7), moves.end());
  b.move(*findMove(moves, 2, 7));

  moves = b.getMoves(6, 4); // Black pawn from (6,4) to (4,4)
  ASSERT_EQ(moves.size(), 2);
  ASSERT_NE(findMove(moves, 4,4), moves.end());
  b.move(*findMove(moves, 4,4));

  moves = b.getMoves(1,4); // White pawn from (1,4) to (3,4)
  ASSERT_EQ(moves.size(), 2);
  ASSERT_NE(findMove(moves, 3,4), moves.end());
  b.move(*findMove(moves, 3,4));

  moves = b.getMoves(7,5); // Black bishop from (7,5) to (4,2)
  ASSERT_EQ(moves.size(), 5);
  ASSERT_NE(findMove(moves, 4,2), moves.end());
  b.move(*findMove(moves, 4,2));

  moves = b.getMoves(1,6); // White pawn from (1,6) to (3,6)
  ASSERT_EQ(moves.size(), 2);
  ASSERT_NE(findMove(moves,3,6), moves.end());
  b.move(*findMove(moves, 3,6));

  moves = b.getMoves(5,5); // Black knight from (5,5) to (3,6) takes white pawn
  ASSERT_EQ(moves.size(), 5);
  ASSERT_NE(findMove(moves, 3,6), moves.end());
  b.move(*findMove(moves, 3,6));

  moves = b.getMoves(0, 7); // White rook from (0,7) to (0,6)
  ASSERT_EQ(moves.size(), 1);
  ASSERT_NE(findMove(moves, 0,6), moves.end());
  b.move(*findMove(moves, 0,6));

  moves = b.getMoves(6,0); // Black pawn from (6,0) to (4,0)
  ASSERT_EQ(moves.size(), 2);
  ASSERT_NE(findMove(moves, 4,0), moves.end());
  b.move(*findMove(moves, 4,0));

  moves = b.getMoves(0,6); // White rook from (0,6) to (3,6) takes black knight
  ASSERT_EQ(moves.size(), 4);
  ASSERT_NE(findMove(moves, 3,6), moves.end());
  b.move(*findMove(moves, 3,6));

  moves = b.getMoves(7,0); // Black rook from (7,0) to (5,0)
  ASSERT_EQ(moves.size(), 2);
  ASSERT_NE(findMove(moves, 5,0), moves.end());
  b.move(*findMove(moves, 5,0));

  moves = b.getMoves(0,5); // White bishop from (0,5) to (3,2)
  ASSERT_EQ(moves.size(), 6);
  ASSERT_NE(findMove(moves, 3,2), moves.end());
  b.move(*findMove(moves, 3,2));

  moves = b.getMoves(5,0); // Black rook from (5,0) to (5,5)
  ASSERT_EQ(moves.size(), 9);
  ASSERT_NE(findMove(moves, 5,5), moves.end());
  b.move(*findMove(moves, 5,5));
}

TEST(MoveQueen, Test1){
  Board b;
  vector<movement> moves = b.getMoves(1,3); // Move front pawn first
  ASSERT_EQ(moves.size(), 2);
  ASSERT_NE(findMove(moves, 3,3), moves.end());
  b.move(*findMove(moves, 3,3));

  moves = b.getMoves(0,3); // Move White Queen from (0,3) to (2,3)
  ASSERT_EQ(moves.size(), 2);
  ASSERT_NE(findMove(moves, 2,3), moves.end());
  b.move(*findMove(moves, 2,3));
  moves = b.getMoves(2,3);
  ASSERT_EQ(moves.size(), 16);

}

TEST(MoveKing, Test1){
    Board b;
    vector<movement> moves = b.getMoves(1,4); // Move front pawn first
    ASSERT_EQ(moves.size(), 2);
    ASSERT_NE(findMove(moves, 3,4), moves.end());
    b.move(*findMove(moves, 3,4));

    moves = b.getMoves(0,4); // Move White King from (0,4) to (1,4)
    ASSERT_EQ(moves.size(), 1);
    ASSERT_NE(findMove(moves, 1,4), moves.end());
    b.move(*findMove(moves, 1,4));
    moves = b.getMoves(1,4); // Move White King from (1,4) to (2,4)
    ASSERT_EQ(moves.size(), 4);
    ASSERT_NE(findMove(moves, 2,4), moves.end());
    b.move(*findMove(moves, 2,4));
    ASSERT_EQ(moves.size(), 5);


}
