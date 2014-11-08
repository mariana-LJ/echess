
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
  vector<movement> moves = b.getMoves(1,4); // White to move
  ASSERT_EQ(moves.size(),2);
  ASSERT_NE(findMove(moves, 2, 4), moves.end());
  ASSERT_NE(findMove(moves, 3, 4), moves.end());
  b.move(*findMove(moves, 3, 4));
  moves = b.getMoves(6,4); // Black to move
  ASSERT_EQ(moves.size(),2);
  ASSERT_NE(findMove(moves, 5, 4), moves.end());
  ASSERT_NE(findMove(moves, 4, 4), moves.end());
  b.move(*findMove(moves, 4, 4));
  moves = b.getMoves(3,4); // White to move
  ASSERT_EQ(moves.size(),0);
}

TEST(MoveKnight, Test1){
  Board b1;
  vector<movement> moves = b1.getMoves(0,1); // White to move

  ASSERT_EQ(moves.size(),2);
  ASSERT_NE(findMove(moves, 2, 0), moves.end());
  ASSERT_NE(findMove(moves, 2, 2), moves.end());
}

TEST(MoveBishop, Test1){
  Board b;
  vector<movement> moves = b.getMoves(1,4);
  b.move(*findMove(moves, 3, 4)); // Move the pawn in front of white King

  moves = b.getMoves(6,4); // Black to move
  ASSERT_EQ(moves.size(),2);
  ASSERT_NE(findMove(moves, 5, 4), moves.end());
  b.move(*findMove(moves, 5, 4));

  moves = b.getMoves(0,5); //Get possible moves for bishop at 0,5
  ASSERT_EQ(moves.size(),5);

}


TEST(MoveRook, Test1){
  Board b;
  vector<movement> moves = b.getMoves(1,0); // White to move
  ASSERT_EQ(moves.size(),2);
  ASSERT_NE(findMove(moves, 3, 0), moves.end());
  b.move(*findMove(moves, 3,0)); // Move the pawn in front of rook at 0,0 by 2 squares

  moves = b.getMoves(6,0); // Black to move
  ASSERT_EQ(moves.size(),2);
  ASSERT_NE(findMove(moves, 4, 0), moves.end());
  b.move(*findMove(moves, 4,0));

  moves = b.getMoves(0,0); // White rook moves
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
  vector<movement> moves = b.getMoves(1,3); // White: Move front pawn first
  ASSERT_EQ(moves.size(), 2);
  ASSERT_NE(findMove(moves, 3,3), moves.end());
  b.move(*findMove(moves, 3,3));

  moves = b.getMoves(6,4); // Black to move
  ASSERT_EQ(moves.size(),2);
  ASSERT_NE(findMove(moves, 5, 4), moves.end());
  b.move(*findMove(moves, 5, 4));

  moves = b.getMoves(0,3); // Move White Queen from (0,3) to (2,3)
  ASSERT_EQ(moves.size(), 2);
  ASSERT_NE(findMove(moves, 2,3), moves.end());
  b.move(*findMove(moves, 2,3));

  moves = b.getMoves(6,2); // Black to move
  ASSERT_EQ(moves.size(),2);
  ASSERT_NE(findMove(moves, 5, 2), moves.end());
  b.move(*findMove(moves, 5, 2));

  moves = b.getMoves(2,3); // Get the moves of the current position (White Queen)
  ASSERT_EQ(moves.size(), 16);

}

TEST(MoveKing, Test1){
    Board b;
    vector<movement> moves = b.getMoves(1,4); // White: Move front pawn first
    ASSERT_EQ(moves.size(), 2);
    ASSERT_NE(findMove(moves, 3,4), moves.end());
    b.move(*findMove(moves, 3,4));

    moves = b.getMoves(6,4); // Black to move
    ASSERT_EQ(moves.size(),2);
    ASSERT_NE(findMove(moves, 5, 4), moves.end());
    b.move(*findMove(moves, 5, 4));

    moves = b.getMoves(0,4); // Move White King from (0,4) to (1,4)
    ASSERT_EQ(moves.size(), 1);
    ASSERT_NE(findMove(moves, 1,4), moves.end());
    b.move(*findMove(moves, 1,4));

    moves = b.getMoves(6,5); // Black to move
    ASSERT_EQ(moves.size(),2);
    ASSERT_NE(findMove(moves, 5, 5), moves.end());
    b.move(*findMove(moves, 5, 5));

    moves = b.getMoves(1,4); // Move White King from (1,4) to (2,4)
    ASSERT_EQ(moves.size(), 4);
    ASSERT_NE(findMove(moves, 2,4), moves.end());
    b.move(*findMove(moves, 2,4));

    moves = b.getMoves(6,1); // Black to move
    ASSERT_EQ(moves.size(),2);
    ASSERT_NE(findMove(moves, 4, 1), moves.end());
    b.move(*findMove(moves, 4, 1));

    moves = b.getMoves(2,4);
    ASSERT_EQ(moves.size(), 5);
}

TEST(MoveKing, Test2){ // Test the detection of the first move of the King
    Board b;
    vector<movement> moves = b.getMoves(1,4); // Move front pawn first
    ASSERT_EQ(moves.size(), 2);
    ASSERT_NE(findMove(moves, 3,4), moves.end());
    b.move(*findMove(moves, 3,4));

    moves = b.getMoves(6,4); // Black to move
    ASSERT_EQ(moves.size(),2);
    ASSERT_NE(findMove(moves, 5, 4), moves.end());
    b.move(*findMove(moves, 5, 4));

    moves = b.getMoves(0,4); // Move White King from (0,4) to (1,4)
    ASSERT_EQ(moves.size(), 1);
    ASSERT_NE(findMove(moves, 1,4), moves.end());
    b.move(*findMove(moves, 1,4));

    moves = b.getMoves(6,1); // Black to move
    ASSERT_EQ(moves.size(),2);
    ASSERT_NE(findMove(moves, 4, 1), moves.end());
    b.move(*findMove(moves, 4, 1));

    moves = b.getMoves(1,5); // Move white pawn from (1,5) to (3,5)
    ASSERT_EQ(moves.size(), 2);
    ASSERT_NE(findMove(moves, 3,5), moves.end());
    b.move(*findMove(moves, 3,5));

    moves = b.getMoves(6,2); // Black to move
    ASSERT_EQ(moves.size(),2);
    ASSERT_NE(findMove(moves, 5, 2), moves.end());
    b.move(*findMove(moves, 5, 2));

    moves = b.getMoves(1,4); // Move White King from (0,4) to (1,4)
    ASSERT_EQ(moves.size(), 5);
    ASSERT_NE(findMove(moves, 2,5), moves.end());
    b.move(*findMove(moves, 2,5));

}

TEST(WhiteCastle, Test1){ // Test short castle in ideal sequence
    Board b;
    vector<movement> moves = b.getMoves(1,4); // Move front pawn first
    ASSERT_EQ(moves.size(), 2);
    ASSERT_NE(findMove(moves, 2,4), moves.end());
    b.move(*findMove(moves, 2,4));

    moves = b.getMoves(6,1); // Black to move
    ASSERT_EQ(moves.size(),2);
    ASSERT_NE(findMove(moves, 4, 1), moves.end());
    b.move(*findMove(moves, 4, 1));

    moves = b.getMoves(0,5); // Move white bishop from (0,5) to (2,3)
    ASSERT_EQ(moves.size(), 4);
    ASSERT_NE(findMove(moves, 2,3), moves.end());
    b.move(*findMove(moves, 2,3));

    moves = b.getMoves(6,2); // Black to move
    ASSERT_EQ(moves.size(),2);
    ASSERT_NE(findMove(moves, 5, 2), moves.end());
    b.move(*findMove(moves, 5, 2));

    moves = b.getMoves(0,6); // Move white knight from (0,6) to (2,5)
    ASSERT_EQ(moves.size(), 3);
    ASSERT_NE(findMove(moves, 2,5), moves.end());
    b.move(*findMove(moves, 2,5));

    moves = b.getMoves(6,3); // Black to move
    ASSERT_EQ(moves.size(),2);
    ASSERT_NE(findMove(moves, 5, 3), moves.end());
    b.move(*findMove(moves, 5, 3));

    moves = b.getMoves(0,4); // Do short castle
    ASSERT_EQ(moves.size(), 3);
    ASSERT_NE(findMove(moves, 0,6), moves.end());
    b.move(*findMove(moves, 0,6));

    moves = b.getMoves(5,2); // Black to move
    ASSERT_EQ(moves.size(),1);
    ASSERT_NE(findMove(moves, 4, 2), moves.end());
    b.move(*findMove(moves, 4, 2));

    moves = b.getMoves(0,5); // Check position of rook
    ASSERT_EQ(moves.size(), 1);
}

TEST(WhiteCastle, Test2){ // Test that short castle can't be performed
    Board b;
    vector<movement> moves = b.getMoves(1,4); // Move front pawn first
    ASSERT_EQ(moves.size(), 2);
    ASSERT_NE(findMove(moves, 2,4), moves.end());
    b.move(*findMove(moves, 2,4));

    moves = b.getMoves(6,0); // Black to move
    ASSERT_EQ(moves.size(),2);
    ASSERT_NE(findMove(moves, 4, 0), moves.end());
    b.move(*findMove(moves, 4, 0));

    moves = b.getMoves(0,5); // Move white bishop from (0,5) to (2,3)
    ASSERT_EQ(moves.size(), 5);
    ASSERT_NE(findMove(moves, 2,3), moves.end());
    b.move(*findMove(moves, 2,3));

    moves = b.getMoves(6,1); // Black to move
    ASSERT_EQ(moves.size(),2);
    ASSERT_NE(findMove(moves, 5, 1), moves.end());
    b.move(*findMove(moves, 5, 1));

    moves = b.getMoves(0,6); // Move white knight from (0,6) to (2,5)
    ASSERT_EQ(moves.size(), 3);
    ASSERT_NE(findMove(moves, 2,5), moves.end());
    b.move(*findMove(moves, 2,5));

    moves = b.getMoves(6,2); // Black to move
    ASSERT_EQ(moves.size(),2);
    ASSERT_NE(findMove(moves, 5, 2), moves.end());
    b.move(*findMove(moves, 5, 2));

    moves = b.getMoves(0,4); // Move the white King
    ASSERT_EQ(moves.size(), 3);
    ASSERT_NE(findMove(moves, 1,4), moves.end());
    b.move(*findMove(moves, 1,4));

    moves = b.getMoves(6,3); // Black to move
    ASSERT_EQ(moves.size(),2);
    ASSERT_NE(findMove(moves, 4, 3), moves.end());
    b.move(*findMove(moves, 4, 3));

    moves = b.getMoves(1,4); // Return King to original position
    ASSERT_EQ(moves.size(), 2);
    ASSERT_NE(findMove(moves, 0,4), moves.end());
    b.move(*findMove(moves, 0,4));

    moves = b.getMoves(6,4); // Black to move
    ASSERT_EQ(moves.size(),2);
    ASSERT_NE(findMove(moves, 4, 4), moves.end());
    b.move(*findMove(moves, 4, 4));

    moves = b.getMoves(0,4); // Try to do short castle
    ASSERT_EQ(moves.size(), 2);
    ASSERT_EQ(findMove(moves, 0,6), moves.end());

}

TEST(WhiteCastle, Test3){ // Move rook at (0,7). Short castle should not be allowed
    Board b;
    vector<movement> moves = b.getMoves(1,4); // Move front pawn first
    ASSERT_EQ(moves.size(), 2);
    ASSERT_NE(findMove(moves, 2,4), moves.end());
    b.move(*findMove(moves, 2,4));

    moves = b.getMoves(6,0); // Black to move
    ASSERT_EQ(moves.size(),2);
    ASSERT_NE(findMove(moves, 5, 0), moves.end());
    b.move(*findMove(moves, 5, 0));

    moves = b.getMoves(0,5); // Move white bishop from (0,5) to (2,3)
    ASSERT_EQ(moves.size(), 5);
    ASSERT_NE(findMove(moves, 2,3), moves.end());
    b.move(*findMove(moves, 2,3));

    moves = b.getMoves(6,1); // Black to move
    ASSERT_EQ(moves.size(),2);
    ASSERT_NE(findMove(moves, 5, 1), moves.end());
    b.move(*findMove(moves, 5, 1));

    moves = b.getMoves(0,6); // Move white knight from (0,6) to (2,5)
    ASSERT_EQ(moves.size(), 3);
    ASSERT_NE(findMove(moves, 2,5), moves.end());
    b.move(*findMove(moves, 2,5));

    moves = b.getMoves(6,2); // Black to move
    ASSERT_EQ(moves.size(),2);
    ASSERT_NE(findMove(moves, 4, 2), moves.end());
    b.move(*findMove(moves, 4, 2));

    moves = b.getMoves(0,7); // White rook from (0,7) to (0,5)
    ASSERT_EQ(moves.size(), 2);
    ASSERT_NE(findMove(moves, 0,5), moves.end());
    b.move(*findMove(moves, 0,5));

    moves = b.getMoves(6,3); // Black to move
    ASSERT_EQ(moves.size(),2);
    ASSERT_NE(findMove(moves, 5, 3), moves.end());
    b.move(*findMove(moves, 5, 3));

    moves = b.getMoves(0,5); // White rook back to (0,7)
    ASSERT_EQ(moves.size(), 2);
    ASSERT_NE(findMove(moves, 0,7), moves.end());
    b.move(*findMove(moves, 0,7));

    moves = b.getMoves(5,1); // Black to move
    ASSERT_EQ(moves.size(),1);
    ASSERT_NE(findMove(moves, 4, 1), moves.end());
    b.move(*findMove(moves, 4, 1));

    moves = b.getMoves(0,4); // Try to castle
    ASSERT_EQ(moves.size(), 2);
    ASSERT_EQ(findMove(moves, 0,6), moves.end());
}

TEST(WhiteCastle, Test4){ // Long castle in ideal sequence
    Board b;
    vector<movement> moves = b.getMoves(1,4); // Move front pawn first
    ASSERT_EQ(moves.size(), 2);
    ASSERT_NE(findMove(moves, 2,4), moves.end());
    b.move(*findMove(moves, 2,4));

    moves = b.getMoves(6,0); // Black to move
    ASSERT_EQ(moves.size(),2);
    ASSERT_NE(findMove(moves, 5, 0), moves.end());
    b.move(*findMove(moves, 5, 0));

    moves = b.getMoves(0,3); // Move white Queen from (0,3) to (4,7)
    ASSERT_EQ(moves.size(), 4);
    ASSERT_NE(findMove(moves, 4,7), moves.end());
    b.move(*findMove(moves, 4,7));

    moves = b.getMoves(6,1); // Black to move
    ASSERT_EQ(moves.size(),2);
    ASSERT_NE(findMove(moves, 5, 1), moves.end());
    b.move(*findMove(moves, 5, 1));

    moves = b.getMoves(1,1); // Move white pawn from (1,1) to (2,1)
    ASSERT_EQ(moves.size(), 2);
    ASSERT_NE(findMove(moves, 2,1), moves.end());
    b.move(*findMove(moves, 2,1));

    moves = b.getMoves(6,2); // Black to move
    ASSERT_EQ(moves.size(),2);
    ASSERT_NE(findMove(moves, 5, 2), moves.end());
    b.move(*findMove(moves, 5, 2));

    moves = b.getMoves(0,2); // Move white bishop from (0,2) to (1,1)
    ASSERT_EQ(moves.size(), 2);
    ASSERT_NE(findMove(moves, 1,1), moves.end());
    b.move(*findMove(moves, 1,1));

    moves = b.getMoves(6,3); // Black to move
    ASSERT_EQ(moves.size(),2);
    ASSERT_NE(findMove(moves, 5, 3), moves.end());
    b.move(*findMove(moves, 5, 3));

    moves = b.getMoves(0,1); // Move white knight from (0,1) to (2,2)
    ASSERT_EQ(moves.size(), 2);
    ASSERT_NE(findMove(moves, 2,2), moves.end());
    b.move(*findMove(moves, 2,2));

    moves = b.getMoves(6,4); // Black to move
    ASSERT_EQ(moves.size(),2);
    ASSERT_NE(findMove(moves, 5, 4), moves.end());
    b.move(*findMove(moves, 5, 4));

    moves = b.getMoves(0,4); // Do long castle
    ASSERT_EQ(moves.size(), 3);
    ASSERT_NE(findMove(moves, 0,2), moves.end());
    b.move(*findMove(moves, 0,2));
}

TEST(EnPassant, Test1){
    Board b;
    vector<movement> moves = b.getMoves(1,3); // White to move
    ASSERT_EQ(moves.size(), 2);
    ASSERT_NE(findMove(moves, 3,3), moves.end());
    b.move(*findMove(moves, 3,3));

    moves = b.getMoves(6,3); // Black to move
    ASSERT_EQ(moves.size(),2);
    ASSERT_NE(findMove(moves, 4, 3), moves.end());
    b.move(*findMove(moves, 4, 3));

    moves = b.getMoves(1,7); // White to move
    ASSERT_EQ(moves.size(),2);
    ASSERT_NE(findMove(moves, 2, 7), moves.end());
    b.move(*findMove(moves, 2, 7));

    moves = b.getMoves(6,4); // Black to move
    ASSERT_EQ(moves.size(),2);
    ASSERT_NE(findMove(moves, 4, 4), moves.end());
    b.move(*findMove(moves, 4, 4));

    moves = b.getMoves(2,7); // White to move
    ASSERT_EQ(moves.size(),1);
    ASSERT_NE(findMove(moves, 3, 7), moves.end());
    b.move(*findMove(moves, 3, 7));

    moves = b.getMoves(4,4); // Black to move
    ASSERT_EQ(moves.size(),2);
    ASSERT_NE(findMove(moves, 3, 4), moves.end());
    b.move(*findMove(moves, 3, 4));

    moves = b.getMoves(1,5); // White to move
    ASSERT_EQ(moves.size(),2);
    ASSERT_NE(findMove(moves, 3, 5), moves.end());
    b.move(*findMove(moves, 3, 5));

    moves = b.getMoves(3,4); // Black to move: takes white en-passant
    ASSERT_EQ(moves.size(),2);
    ASSERT_NE(findMove(moves, 2, 5), moves.end());
    b.move(*findMove(moves, 2, 5));

}

// Testing the validation of moves
TEST(moveValid, Test1){
    Board b;
    unsigned char shadows[8][8] = {{1,1,1,1,1,1,1,1},
                                   {1,1,1,0,1,1,1,1},
                                   {0,0,0,1,0,0,0,0},
                                   {0,0,0,0,0,0,0,0},
                                   {0,0,0,0,0,0,0,0},
                                   {0,0,0,0,0,0,0,0},
                                   {1,1,1,1,1,1,1,1},
                                   {1,1,1,1,1,1,1,1}};

    ASSERT_STREQ("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", b.FEN().c_str());

    // 1. White pawn from (1,3) to (2,3)
    vector<movement> moves = b.getMoves(1,3);
    ASSERT_EQ(moves.size(), 2);
    ASSERT_EQ(b.findMovement(shadows).piece, 'P');
    ASSERT_EQ(b.findMovement(shadows).origin_row, 1);
    ASSERT_EQ(b.findMovement(shadows).origin_column, 3);
    ASSERT_EQ(b.findMovement(shadows).target_row, 2);
    ASSERT_EQ(b.findMovement(shadows).target_column, 3);
    b.move(b.findMovement(shadows));
    ASSERT_STREQ("rnbqkbnr/pppppppp/8/8/8/3P4/PPP1PPPP/RNBQKBNR b KQkq - 0 1", b.FEN().c_str());

    // 2. Black pawn from (6,3) to (4,3)
    shadows[6][3] = 0;
    shadows[4][3] = 1;
    moves = b.getMoves(6,3);
    ASSERT_EQ(moves.size(), 2);
    ASSERT_EQ(b.findMovement(shadows).piece, 'p');
    ASSERT_EQ(b.findMovement(shadows).origin_row, 6);
    ASSERT_EQ(b.findMovement(shadows).origin_column, 3);
    ASSERT_EQ(b.findMovement(shadows).target_row, 4);
    ASSERT_EQ(b.findMovement(shadows).target_column, 3);
    b.move(b.findMovement(shadows));
    ASSERT_STREQ("rnbqkbnr/ppp1pppp/8/3p4/8/3P4/PPP1PPPP/RNBQKBNR w KQkq d6 0 2", b.FEN().c_str());

    // 3. White knight from (0,6) to (2,5)
    shadows[0][6] = 0;
    shadows[2][5] = 1;
    moves = b.getMoves(0,6); //
    ASSERT_EQ(moves.size(), 2);
    ASSERT_EQ(b.findMovement(shadows).piece, 'N');
    ASSERT_EQ(b.findMovement(shadows).origin_row, 0);
    ASSERT_EQ(b.findMovement(shadows).origin_column, 6);
    ASSERT_EQ(b.findMovement(shadows).target_row, 2);
    ASSERT_EQ(b.findMovement(shadows).target_column, 5);
    b.move(b.findMovement(shadows));
    ASSERT_STREQ("rnbqkbnr/ppp1pppp/8/3p4/8/3P1N2/PPP1PPPP/RNBQKB1R b KQkq - 0 2", b.FEN().c_str());
    //rnbqkbnr/ppp1pppp/8/3p4/8/3P1N2/PPP1PPPP/RNBQKB1R b KQkq - 1 2

    // 4. Black knight from (7,1) to (5,2)
    shadows[7][1] = 0;
    shadows[5][2] = 1;
    moves = b.getMoves(7,1); //
    ASSERT_EQ(moves.size(), 3);
    ASSERT_EQ(b.findMovement(shadows).piece, 'n');
    ASSERT_EQ(b.findMovement(shadows).origin_row, 7);
    ASSERT_EQ(b.findMovement(shadows).origin_column, 1);
    ASSERT_EQ(b.findMovement(shadows).target_row, 5);
    ASSERT_EQ(b.findMovement(shadows).target_column, 2);
    b.move(b.findMovement(shadows));
    ASSERT_STREQ("r1bqkbnr/ppp1pppp/2n5/3p4/8/3P1N2/PPP1PPPP/RNBQKB1R w KQkq - 0 3", b.FEN().c_str());
    //r1bqkbnr/ppp1pppp/2n5/3p4/8/3P1N2/PPP1PPPP/RNBQKB1R w KQkq - 2 3

    // 5. White pawn from (1,4) to (3,4)
    shadows[1][4] = 0;
    shadows[3][4] = 1;
    moves = b.getMoves(1,4); //
    ASSERT_EQ(moves.size(), 2);
    ASSERT_EQ(b.findMovement(shadows).piece, 'P');
    ASSERT_EQ(b.findMovement(shadows).origin_row, 1);
    ASSERT_EQ(b.findMovement(shadows).origin_column, 4);
    ASSERT_EQ(b.findMovement(shadows).target_row, 3);
    ASSERT_EQ(b.findMovement(shadows).target_column, 4);
    b.move(b.findMovement(shadows));
    ASSERT_STREQ("r1bqkbnr/ppp1pppp/2n5/3p4/4P3/3P1N2/PPP2PPP/RNBQKB1R b KQkq e3 0 3", b.FEN().c_str());

    // 6. Black pawn from (4,3) to (3,4) takes white pawn
    shadows[4][3] = 0;
    moves = b.getMoves(4,3); //
    ASSERT_EQ(moves.size(), 2);
    ASSERT_EQ(b.findMovement(shadows).piece, 'p');
    ASSERT_EQ(b.findMovement(shadows).origin_row, 4);
    ASSERT_EQ(b.findMovement(shadows).origin_column, 3);
    ASSERT_EQ(b.findMovement(shadows).target_row, 3);
    ASSERT_EQ(b.findMovement(shadows).target_column, 4);
    b.move(b.findMovement(shadows));
    ASSERT_STREQ("r1bqkbnr/ppp1pppp/2n5/8/4p3/3P1N2/PPP2PPP/RNBQKB1R w KQkq - 0 4", b.FEN().c_str());

    // 7. White pawn from (2,3) to (3,4) takes black pawn
    shadows[2][3] = 0;
    moves = b.getMoves(2,3); //
    ASSERT_EQ(moves.size(), 2);
    ASSERT_EQ(b.findMovement(shadows).piece, 'P');
    ASSERT_EQ(b.findMovement(shadows).origin_row, 2);
    ASSERT_EQ(b.findMovement(shadows).origin_column, 3);
    ASSERT_EQ(b.findMovement(shadows).target_row, 3);
    ASSERT_EQ(b.findMovement(shadows).target_column, 4);
    b.move(b.findMovement(shadows));
    ASSERT_STREQ("r1bqkbnr/ppp1pppp/2n5/8/4P3/5N2/PPP2PPP/RNBQKB1R b KQkq - 0 4", b.FEN().c_str());

    // 8. Black bishop from (7,2) to (3,6)
    shadows[7][2] = 0;
    shadows[3][6] = 1;
    moves = b.getMoves(7,2); //
    ASSERT_EQ(moves.size(), 5);
    ASSERT_EQ(b.findMovement(shadows).piece, 'b');
    ASSERT_EQ(b.findMovement(shadows).origin_row, 7);
    ASSERT_EQ(b.findMovement(shadows).origin_column, 2);
    ASSERT_EQ(b.findMovement(shadows).target_row, 3);
    ASSERT_EQ(b.findMovement(shadows).target_column, 6);
    b.move(b.findMovement(shadows));
    ASSERT_STREQ("r2qkbnr/ppp1pppp/2n5/8/4P1b1/5N2/PPP2PPP/RNBQKB1R w KQkq - 0 5", b.FEN().c_str());
    // r2qkbnr/ppp1pppp/2n5/8/4P1b1/5N2/PPP2PPP/RNBQKB1R w KQkq - 1 5

    // 9. White bishop from (0,5) to (1,4)
    shadows[0][5] = 0;
    shadows[1][4] = 1;
    moves = b.getMoves(0,5); //
    ASSERT_EQ(moves.size(), 5);
    ASSERT_EQ(b.findMovement(shadows).piece, 'B');
    ASSERT_EQ(b.findMovement(shadows).origin_row, 0);
    ASSERT_EQ(b.findMovement(shadows).origin_column, 5);
    ASSERT_EQ(b.findMovement(shadows).target_row, 1);
    ASSERT_EQ(b.findMovement(shadows).target_column, 4);
    b.move(b.findMovement(shadows));
    ASSERT_STREQ("r2qkbnr/ppp1pppp/2n5/8/4P1b1/5N2/PPP1BPPP/RNBQK2R b KQkq - 0 5", b.FEN().c_str());
    // r2qkbnr/ppp1pppp/2n5/8/4P1b1/5N2/PPP1BPPP/RNBQK2R b KQkq - 2 5

    // 10. Black knight from (5,2) to (4,4)
    shadows[5][2] = 0;
    shadows[4][4] = 1;
    moves = b.getMoves(5,2); //
    ASSERT_EQ(moves.size(), 5);
    ASSERT_EQ(b.findMovement(shadows).piece, 'n');
    ASSERT_EQ(b.findMovement(shadows).origin_row, 5);
    ASSERT_EQ(b.findMovement(shadows).origin_column, 2);
    ASSERT_EQ(b.findMovement(shadows).target_row, 4);
    ASSERT_EQ(b.findMovement(shadows).target_column, 4);
    b.move(b.findMovement(shadows));
    ASSERT_STREQ("r2qkbnr/ppp1pppp/8/4n3/4P1b1/5N2/PPP1BPPP/RNBQK2R w KQkq - 0 6", b.FEN().c_str());
    // r2qkbnr/ppp1pppp/8/4n3/4P1b1/5N2/PPP1BPPP/RNBQK2R w KQkq - 3 6

    // 11. White short castle
    shadows[0][4] = 0;
    shadows[0][6] = 1;
    shadows[0][7] = 0;
    shadows[0][5] = 1;
    moves = b.getMoves(0,4); //
    ASSERT_EQ(moves.size(), 3);
    ASSERT_EQ(b.findMovement(shadows).piece, 'K');
    ASSERT_EQ(b.findMovement(shadows).origin_row, 0);
    ASSERT_EQ(b.findMovement(shadows).origin_column, 4);
    ASSERT_EQ(b.findMovement(shadows).target_row, 0);
    ASSERT_EQ(b.findMovement(shadows).target_column, 6);
    b.move(b.findMovement(shadows));
    ASSERT_STREQ("r2qkbnr/ppp1pppp/8/4n3/4P1b1/5N2/PPP1BPPP/RNBQ1RK1 b kq - 0 6", b.FEN().c_str());
    // r2qkbnr/ppp1pppp/8/4n3/4P1b1/5N2/PPP1BPPP/RNBQ1RK1 b kq - 4 6

    // 12. Black knight from (4,4) to (2,5) takes white knight: Check!
    shadows[4][4] = 0;
    moves = b.getMoves(4,4); //
    ASSERT_EQ(moves.size(), 6);
    ASSERT_EQ(b.findMovement(shadows).piece, 'n');
    ASSERT_EQ(b.findMovement(shadows).origin_row, 4);
    ASSERT_EQ(b.findMovement(shadows).origin_column, 4);
    ASSERT_EQ(b.findMovement(shadows).target_row, 2);
    ASSERT_EQ(b.findMovement(shadows).target_column, 5);
    b.move(b.findMovement(shadows));
    ASSERT_STREQ("r2qkbnr/ppp1pppp/8/8/4P1b1/5n2/PPP1BPPP/RNBQ1RK1 w kq - 0 7", b.FEN().c_str());

    // 13. White pawn from (1,6) to (2,5) takes black knight
    shadows[1][6] = 0;
    moves = b.getMoves(1,6); //
    ASSERT_EQ(moves.size(), 2);
    ASSERT_EQ(b.findMovement(shadows).piece, 'P');
    ASSERT_EQ(b.findMovement(shadows).origin_row, 1);
    ASSERT_EQ(b.findMovement(shadows).origin_column, 6);
    ASSERT_EQ(b.findMovement(shadows).target_row, 2);
    ASSERT_EQ(b.findMovement(shadows).target_column, 5);
    b.move(b.findMovement(shadows));
    ASSERT_STREQ("r2qkbnr/ppp1pppp/8/8/4P1b1/5P2/PPP1BP1P/RNBQ1RK1 b kq - 0 7", b.FEN().c_str());

    // 14. Black bishop from (3,6) to (2,5) takes white pawn
    shadows[3][6] = 0;
    b.move(b.findMovement(shadows));
    ASSERT_STREQ("r2qkbnr/ppp1pppp/8/8/4P3/5b2/PPP1BP1P/RNBQ1RK1 w kq - 0 8", b.FEN().c_str());

    // 15. White bishop from (1,4) to (2,5) takes black bishop
    shadows[1][4] = 0;
    b.move(b.findMovement(shadows));
    ASSERT_STREQ("r2qkbnr/ppp1pppp/8/8/4P3/5B2/PPP2P1P/RNBQ1RK1 b kq - 0 8", b.FEN().c_str());

    // 16. Black queen from (7,3) to (0,3) takes black queen
    shadows[7][3] = 0;
    b.move(b.findMovement(shadows));
    ASSERT_STREQ("r3kbnr/ppp1pppp/8/8/4P3/5B2/PPP2P1P/RNBq1RK1 w kq - 0 9", b.FEN().c_str());

    // 17. White rook from (0,5) to (0,3) takes black queen
    shadows[0][5] = 0;
    b.move(b.findMovement(shadows));
    ASSERT_STREQ("r3kbnr/ppp1pppp/8/8/4P3/5B2/PPP2P1P/RNBR2K1 b kq - 0 9", b.FEN().c_str());

    // not implemented yet that the king cannot go through an attacked square
    // while castling
    // the black king has no valid movements
    // let's try to castle
    /*shadows[7][4] = 0;
    shadows[7][2] = 1;
    shadows[7][0] = 0;
    shadows[7][3] = 1;
    movement m = b.findMovement(shadows);
    ASSERT_EQ(m.piece, '.');
    ASSERT_EQ(m.origin_row, -1);
    ASSERT_EQ(m.origin_column, -1);
    ASSERT_EQ(m.target_row, -1);
    ASSERT_EQ(m.target_column, -1);
    shadows[7][4] = 1;
    shadows[7][2] = 0;
    shadows[7][0] = 1;
    shadows[7][3] = 0;*/

    // 18. Black pawn from (6,4) to (4,4)
    shadows[6][4] = 0;
    shadows[4][4] = 1;
    b.move(b.findMovement(shadows));
    ASSERT_STREQ("r3kbnr/ppp2ppp/8/4p3/4P3/5B2/PPP2P1P/RNBR2K1 w kq e6 0 10", b.FEN().c_str());

    // 19. White bishop from (0,2) to (4,6)
    shadows[0][2] = 0;
    shadows[4][6] = 1;
    b.move(b.findMovement(shadows));
    ASSERT_STREQ("r3kbnr/ppp2ppp/8/4p1B1/4P3/5B2/PPP2P1P/RN1R2K1 b kq - 0 10", b.FEN().c_str());
    // r3kbnr/ppp2ppp/8/4p1B1/4P3/5B2/PPP2P1P/RN1R2K1 b kq - 1 10

    // 20. Black bishop from (7,5) to (5,3)
    shadows[7][5] = 0;
    shadows[5][3] = 1;
    b.move(b.findMovement(shadows));
    ASSERT_STREQ("r3k1nr/ppp2ppp/3b4/4p1B1/4P3/5B2/PPP2P1P/RN1R2K1 w kq - 0 11", b.FEN().c_str());
    // r3k1nr/ppp2ppp/3b4/4p1B1/4P3/5B2/PPP2P1P/RN1R2K1 w kq - 2 11

    // 21. White knight from (0,1) to (2,0)
    shadows[0][1] = 0;
    shadows[2][0] = 1;
    b.move(b.findMovement(shadows));
    ASSERT_STREQ("r3k1nr/ppp2ppp/3b4/4p1B1/4P3/N4B2/PPP2P1P/R2R2K1 b kq - 0 11", b.FEN().c_str());
    // r3k1nr/ppp2ppp/3b4/4p1B1/4P3/N4B2/PPP2P1P/R2R2K1 b kq - 3 11

    // not implemented yet that the king cannot go through an attacked square
    // while castling
    // the black king cannot still long castle
    // let's try to castle
    /*shadows[7][4] = 0;
    shadows[7][2] = 1;
    shadows[7][0] = 0;
    shadows[7][3] = 1;
    m = b.findMovement(shadows);
    ASSERT_EQ(m.piece, '.');
    ASSERT_EQ(m.origin_row, -1);
    ASSERT_EQ(m.origin_column, -1);
    ASSERT_EQ(m.target_row, -1);
    ASSERT_EQ(m.target_column, -1);
    shadows[7][4] = 1;
    shadows[7][2] = 0;
    shadows[7][0] = 1;
    shadows[7][3] = 0;*/

    // 22. Black knight from (7,6) to (6,4)
    shadows[7][6] = 0;
    shadows[6][4] = 1;
    b.move(b.findMovement(shadows));
    ASSERT_STREQ("r3k2r/ppp1nppp/3b4/4p1B1/4P3/N4B2/PPP2P1P/R2R2K1 w kq - 0 12", b.FEN().c_str());
    // r3k2r/ppp1nppp/3b4/4p1B1/4P3/N4B2/PPP2P1P/R2R2K1 w kq - 4 12

    // 23. White rook from (0,3) to (1,3)
    shadows[0][3] = 0;
    shadows[1][3] = 1;
    b.move(b.findMovement(shadows));
    ASSERT_STREQ("r3k2r/ppp1nppp/3b4/4p1B1/4P3/N4B2/PPPR1P1P/R5K1 b kq - 0 12", b.FEN().c_str());
    // r3k2r/ppp1nppp/3b4/4p1B1/4P3/N4B2/PPPR1P1P/R5K1 b kq - 5 12

    // finally the black king can long castle
    // 24. Black king from (7,4) to (7,2) and
    //     Black rook from (7,0) to (7,3)
    shadows[7][4] = 0;
    shadows[7][2] = 1;
    shadows[7][0] = 0;
    shadows[7][3] = 1;
    b.move(b.findMovement(shadows));
    ASSERT_STREQ("2kr3r/ppp1nppp/3b4/4p1B1/4P3/N4B2/PPPR1P1P/R5K1 w - - 0 13", b.FEN().c_str());
    // 2kr3r/ppp1nppp/3b4/4p1B1/4P3/N4B2/PPPR1P1P/R5K1 w - - 6 13
    //shadows[][] = ;

}
