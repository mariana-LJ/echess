
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
    vector<movement> candidate_moves;
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
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    ASSERT_EQ(candidate_moves[0].piece, 'P');
    ASSERT_EQ(candidate_moves[0].origin_row, 1);
    ASSERT_EQ(candidate_moves[0].origin_column, 3);
    ASSERT_EQ(candidate_moves[0].target_row, 2);
    ASSERT_EQ(candidate_moves[0].target_column, 3);
    b.move(candidate_moves[0]);
    ASSERT_STREQ("rnbqkbnr/pppppppp/8/8/8/3P4/PPP1PPPP/RNBQKBNR b KQkq - 0 1", b.FEN().c_str());

    // 2. Black pawn from (6,3) to (4,3)
    shadows[6][3] = 0;
    shadows[4][3] = 1;
    moves = b.getMoves(6,3);
    ASSERT_EQ(moves.size(), 2);
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    ASSERT_EQ(candidate_moves[0].piece, 'p');
    ASSERT_EQ(candidate_moves[0].origin_row, 6);
    ASSERT_EQ(candidate_moves[0].origin_column, 3);
    ASSERT_EQ(candidate_moves[0].target_row, 4);
    ASSERT_EQ(candidate_moves[0].target_column, 3);
    b.move(candidate_moves[0]);
    ASSERT_STREQ("rnbqkbnr/ppp1pppp/8/3p4/8/3P4/PPP1PPPP/RNBQKBNR w KQkq d6 0 2", b.FEN().c_str());

    // 3. White knight from (0,6) to (2,5)
    shadows[0][6] = 0;
    shadows[2][5] = 1;
    moves = b.getMoves(0,6); //
    ASSERT_EQ(moves.size(), 2);
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    ASSERT_EQ(candidate_moves[0].piece, 'N');
    ASSERT_EQ(candidate_moves[0].origin_row, 0);
    ASSERT_EQ(candidate_moves[0].origin_column, 6);
    ASSERT_EQ(candidate_moves[0].target_row, 2);
    ASSERT_EQ(candidate_moves[0].target_column, 5);
    b.move(candidate_moves[0]);
    ASSERT_STREQ("rnbqkbnr/ppp1pppp/8/3p4/8/3P1N2/PPP1PPPP/RNBQKB1R b KQkq - 0 2", b.FEN().c_str());
    //rnbqkbnr/ppp1pppp/8/3p4/8/3P1N2/PPP1PPPP/RNBQKB1R b KQkq - 1 2

    // 4. Black knight from (7,1) to (5,2)
    shadows[7][1] = 0;
    shadows[5][2] = 1;
    moves = b.getMoves(7,1); //
    ASSERT_EQ(moves.size(), 3);
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    ASSERT_EQ(candidate_moves[0].piece, 'n');
    ASSERT_EQ(candidate_moves[0].origin_row, 7);
    ASSERT_EQ(candidate_moves[0].origin_column, 1);
    ASSERT_EQ(candidate_moves[0].target_row, 5);
    ASSERT_EQ(candidate_moves[0].target_column, 2);
    b.move(candidate_moves[0]);
    ASSERT_STREQ("r1bqkbnr/ppp1pppp/2n5/3p4/8/3P1N2/PPP1PPPP/RNBQKB1R w KQkq - 0 3", b.FEN().c_str());
    //r1bqkbnr/ppp1pppp/2n5/3p4/8/3P1N2/PPP1PPPP/RNBQKB1R w KQkq - 2 3

    // 5. White pawn from (1,4) to (3,4)
    shadows[1][4] = 0;
    shadows[3][4] = 1;
    moves = b.getMoves(1,4); //
    ASSERT_EQ(moves.size(), 2);
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    ASSERT_EQ(candidate_moves[0].piece, 'P');
    ASSERT_EQ(candidate_moves[0].origin_row, 1);
    ASSERT_EQ(candidate_moves[0].origin_column, 4);
    ASSERT_EQ(candidate_moves[0].target_row, 3);
    ASSERT_EQ(candidate_moves[0].target_column, 4);
    b.move(candidate_moves[0]);
    ASSERT_STREQ("r1bqkbnr/ppp1pppp/2n5/3p4/4P3/3P1N2/PPP2PPP/RNBQKB1R b KQkq e3 0 3", b.FEN().c_str());

    // 6. Black pawn from (4,3) to (3,4) takes white pawn
    shadows[4][3] = 0;
    moves = b.getMoves(4,3); //
    ASSERT_EQ(moves.size(), 2);
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    ASSERT_EQ(candidate_moves[0].piece, 'p');
    ASSERT_EQ(candidate_moves[0].origin_row, 4);
    ASSERT_EQ(candidate_moves[0].origin_column, 3);
    ASSERT_EQ(candidate_moves[0].target_row, 3);
    ASSERT_EQ(candidate_moves[0].target_column, 4);
    b.move(candidate_moves[0]);
    ASSERT_STREQ("r1bqkbnr/ppp1pppp/2n5/8/4p3/3P1N2/PPP2PPP/RNBQKB1R w KQkq - 0 4", b.FEN().c_str());

    // 7. White pawn from (2,3) to (3,4) takes black pawn
    shadows[2][3] = 0;
    moves = b.getMoves(2,3); //
    ASSERT_EQ(moves.size(), 2);
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    ASSERT_EQ(candidate_moves[0].piece, 'P');
    ASSERT_EQ(candidate_moves[0].origin_row, 2);
    ASSERT_EQ(candidate_moves[0].origin_column, 3);
    ASSERT_EQ(candidate_moves[0].target_row, 3);
    ASSERT_EQ(candidate_moves[0].target_column, 4);
    b.move(candidate_moves[0]);
    ASSERT_STREQ("r1bqkbnr/ppp1pppp/2n5/8/4P3/5N2/PPP2PPP/RNBQKB1R b KQkq - 0 4", b.FEN().c_str());

    // 8. Black bishop from (7,2) to (3,6)
    shadows[7][2] = 0;
    shadows[3][6] = 1;
    moves = b.getMoves(7,2); //
    ASSERT_EQ(moves.size(), 5);
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    ASSERT_EQ(candidate_moves[0].piece, 'b');
    ASSERT_EQ(candidate_moves[0].origin_row, 7);
    ASSERT_EQ(candidate_moves[0].origin_column, 2);
    ASSERT_EQ(candidate_moves[0].target_row, 3);
    ASSERT_EQ(candidate_moves[0].target_column, 6);
    b.move(candidate_moves[0]);
    ASSERT_STREQ("r2qkbnr/ppp1pppp/2n5/8/4P1b1/5N2/PPP2PPP/RNBQKB1R w KQkq - 0 5", b.FEN().c_str());
    // r2qkbnr/ppp1pppp/2n5/8/4P1b1/5N2/PPP2PPP/RNBQKB1R w KQkq - 1 5

    // 9. White bishop from (0,5) to (1,4)
    shadows[0][5] = 0;
    shadows[1][4] = 1;
    moves = b.getMoves(0,5); //
    ASSERT_EQ(moves.size(), 5);
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    ASSERT_EQ(candidate_moves[0].piece, 'B');
    ASSERT_EQ(candidate_moves[0].origin_row, 0);
    ASSERT_EQ(candidate_moves[0].origin_column, 5);
    ASSERT_EQ(candidate_moves[0].target_row, 1);
    ASSERT_EQ(candidate_moves[0].target_column, 4);
    b.move(candidate_moves[0]);
    ASSERT_STREQ("r2qkbnr/ppp1pppp/2n5/8/4P1b1/5N2/PPP1BPPP/RNBQK2R b KQkq - 0 5", b.FEN().c_str());
    // r2qkbnr/ppp1pppp/2n5/8/4P1b1/5N2/PPP1BPPP/RNBQK2R b KQkq - 2 5

    // 10. Black knight from (5,2) to (4,4)
    shadows[5][2] = 0;
    shadows[4][4] = 1;
    moves = b.getMoves(5,2); //
    ASSERT_EQ(moves.size(), 5);
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    ASSERT_EQ(candidate_moves[0].piece, 'n');
    ASSERT_EQ(candidate_moves[0].origin_row, 5);
    ASSERT_EQ(candidate_moves[0].origin_column, 2);
    ASSERT_EQ(candidate_moves[0].target_row, 4);
    ASSERT_EQ(candidate_moves[0].target_column, 4);
    b.move(candidate_moves[0]);
    ASSERT_STREQ("r2qkbnr/ppp1pppp/8/4n3/4P1b1/5N2/PPP1BPPP/RNBQK2R w KQkq - 0 6", b.FEN().c_str());
    // r2qkbnr/ppp1pppp/8/4n3/4P1b1/5N2/PPP1BPPP/RNBQK2R w KQkq - 3 6

    // 11. White short castle
    shadows[0][4] = 0;
    shadows[0][6] = 1;
    shadows[0][7] = 0;
    shadows[0][5] = 1;
    moves = b.getMoves(0,4); //
    ASSERT_EQ(moves.size(), 3);
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    ASSERT_EQ(candidate_moves[0].piece, 'K');
    ASSERT_EQ(candidate_moves[0].origin_row, 0);
    ASSERT_EQ(candidate_moves[0].origin_column, 4);
    ASSERT_EQ(candidate_moves[0].target_row, 0);
    ASSERT_EQ(candidate_moves[0].target_column, 6);
    b.move(candidate_moves[0]);
    ASSERT_STREQ("r2qkbnr/ppp1pppp/8/4n3/4P1b1/5N2/PPP1BPPP/RNBQ1RK1 b kq - 0 6", b.FEN().c_str());
    // r2qkbnr/ppp1pppp/8/4n3/4P1b1/5N2/PPP1BPPP/RNBQ1RK1 b kq - 4 6

    // 12. Black knight from (4,4) to (2,5) takes white knight: Check!
    shadows[4][4] = 0;
    moves = b.getMoves(4,4); //
    ASSERT_EQ(moves.size(), 6);
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    ASSERT_EQ(candidate_moves[0].piece, 'n');
    ASSERT_EQ(candidate_moves[0].origin_row, 4);
    ASSERT_EQ(candidate_moves[0].origin_column, 4);
    ASSERT_EQ(candidate_moves[0].target_row, 2);
    ASSERT_EQ(candidate_moves[0].target_column, 5);
    b.move(candidate_moves[0]);
    ASSERT_STREQ("r2qkbnr/ppp1pppp/8/8/4P1b1/5n2/PPP1BPPP/RNBQ1RK1 w kq - 0 7", b.FEN().c_str());

    // 13. White pawn from (1,6) to (2,5) takes black knight
    shadows[1][6] = 0;
    moves = b.getMoves(1,6); //
    ASSERT_EQ(moves.size(), 2);
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    ASSERT_EQ(candidate_moves[0].piece, 'P');
    ASSERT_EQ(candidate_moves[0].origin_row, 1);
    ASSERT_EQ(candidate_moves[0].origin_column, 6);
    ASSERT_EQ(candidate_moves[0].target_row, 2);
    ASSERT_EQ(candidate_moves[0].target_column, 5);
    b.move(candidate_moves[0]);
    ASSERT_STREQ("r2qkbnr/ppp1pppp/8/8/4P1b1/5P2/PPP1BP1P/RNBQ1RK1 b kq - 0 7", b.FEN().c_str());

    // 14. Black bishop from (3,6) to (2,5) takes white pawn
    shadows[3][6] = 0;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    b.move(candidate_moves[0]);
    ASSERT_STREQ("r2qkbnr/ppp1pppp/8/8/4P3/5b2/PPP1BP1P/RNBQ1RK1 w kq - 0 8", b.FEN().c_str());

    // 15. White bishop from (1,4) to (2,5) takes black bishop
    shadows[1][4] = 0;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    b.move(candidate_moves[0]);
    ASSERT_STREQ("r2qkbnr/ppp1pppp/8/8/4P3/5B2/PPP2P1P/RNBQ1RK1 b kq - 0 8", b.FEN().c_str());

    // 16. Black queen from (7,3) to (0,3) takes black queen
    shadows[7][3] = 0;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    b.move(candidate_moves[0]);
    ASSERT_STREQ("r3kbnr/ppp1pppp/8/8/4P3/5B2/PPP2P1P/RNBq1RK1 w kq - 0 9", b.FEN().c_str());

    // 17. White rook from (0,5) to (0,3) takes black queen
    shadows[0][5] = 0;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    b.move(candidate_moves[0]);
    ASSERT_STREQ("r3kbnr/ppp1pppp/8/8/4P3/5B2/PPP2P1P/RNBR2K1 b kq - 0 9", b.FEN().c_str());

    // not implemented yet that the king cannot go through an attacked square
    // while castling
    // the black king has no valid movements
    // let's try to castle
    /*shadows[7][4] = 0;
    shadows[7][2] = 1;
    shadows[7][0] = 0;
    shadows[7][3] = 1;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
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
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    b.move(candidate_moves[0]);
    ASSERT_STREQ("r3kbnr/ppp2ppp/8/4p3/4P3/5B2/PPP2P1P/RNBR2K1 w kq e6 0 10", b.FEN().c_str());

    // 19. White bishop from (0,2) to (4,6)
    shadows[0][2] = 0;
    shadows[4][6] = 1;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    b.move(candidate_moves[0]);
    ASSERT_STREQ("r3kbnr/ppp2ppp/8/4p1B1/4P3/5B2/PPP2P1P/RN1R2K1 b kq - 0 10", b.FEN().c_str());
    // r3kbnr/ppp2ppp/8/4p1B1/4P3/5B2/PPP2P1P/RN1R2K1 b kq - 1 10

    // 20. Black bishop from (7,5) to (5,3)
    shadows[7][5] = 0;
    shadows[5][3] = 1;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    b.move(candidate_moves[0]);
    ASSERT_STREQ("r3k1nr/ppp2ppp/3b4/4p1B1/4P3/5B2/PPP2P1P/RN1R2K1 w kq - 0 11", b.FEN().c_str());
    // r3k1nr/ppp2ppp/3b4/4p1B1/4P3/5B2/PPP2P1P/RN1R2K1 w kq - 2 11

    // 21. White knight from (0,1) to (2,0)
    shadows[0][1] = 0;
    shadows[2][0] = 1;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    b.move(candidate_moves[0]);
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
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
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
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    b.move(candidate_moves[0]);
    ASSERT_STREQ("r3k2r/ppp1nppp/3b4/4p1B1/4P3/N4B2/PPP2P1P/R2R2K1 w kq - 0 12", b.FEN().c_str());
    // r3k2r/ppp1nppp/3b4/4p1B1/4P3/N4B2/PPP2P1P/R2R2K1 w kq - 4 12

    // 23. White rook from (0,3) to (1,3)
    shadows[0][3] = 0;
    shadows[1][3] = 1;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    b.move(candidate_moves[0]);
    ASSERT_STREQ("r3k2r/ppp1nppp/3b4/4p1B1/4P3/N4B2/PPPR1P1P/R5K1 b kq - 0 12", b.FEN().c_str());
    // r3k2r/ppp1nppp/3b4/4p1B1/4P3/N4B2/PPPR1P1P/R5K1 b kq - 5 12

    // finally the black king can long castle
    // 24. Black king from (7,4) to (7,2) and
    //     Black rook from (7,0) to (7,3)
    shadows[7][4] = 0;
    shadows[7][2] = 1;
    shadows[7][0] = 0;
    shadows[7][3] = 1;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    b.move(candidate_moves[0]);
    ASSERT_STREQ("2kr3r/ppp1nppp/3b4/4p1B1/4P3/N4B2/PPPR1P1P/R5K1 w - - 0 13", b.FEN().c_str());
    // 2kr3r/ppp1nppp/3b4/4p1B1/4P3/N4B2/PPPR1P1P/R5K1 w - - 6 13
    //shadows[][] = ;

}

// Testing the validation of moves
TEST(candidateMoves, Test1){
    Board b;
    vector<movement> candidate_moves;
    unsigned char shadows[8][8] = {{1,1,1,1,1,1,1,1},
                                   {1,1,1,1,1,1,1,1},
                                   {0,0,0,0,0,0,0,0},
                                   {0,0,0,0,0,0,0,0},
                                   {0,0,0,0,0,0,0,0},
                                   {0,0,0,0,0,0,0,0},
                                   {1,1,1,1,1,1,1,1},
                                   {1,1,1,1,1,1,1,1}};

    ASSERT_STREQ("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", b.FEN().c_str());

    // 1. e4       (1,4) to (3,4)
    shadows[1][4] = 0;
    shadows[3][4] = 1;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    b.move(*findMove(candidate_moves, 3, 4));
    ASSERT_STREQ("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1", b.FEN().c_str());

    // 1. ... d5   (6,3) to (4,3)
    shadows[6][3] = 0;
    shadows[4][3] = 1;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    b.move(*findMove(candidate_moves, 4, 3));
    ASSERT_STREQ("rnbqkbnr/ppp1pppp/8/3p4/4P3/8/PPPP1PPP/RNBQKBNR w KQkq d6 0 2", b.FEN().c_str());

    // 2. c4       (1,2) to (3,2)
    shadows[1][2] = 0;
    shadows[3][2] = 1;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    b.move(*findMove(candidate_moves, 3, 2));
    ASSERT_STREQ("rnbqkbnr/ppp1pppp/8/3p4/2P1P3/8/PP1P1PPP/RNBQKBNR b KQkq c3 0 2", b.FEN().c_str());

    // 2. ... dxe4 (4,3) to (3,4)
    // two candidate moves
    shadows[4][3] = 0;
    shadows[3][4] = 1;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(2, candidate_moves.size());
    b.move(*findMove(candidate_moves, 3, 4));
    ASSERT_STREQ("rnbqkbnr/ppp1pppp/8/8/2P1p3/8/PP1P1PPP/RNBQKBNR w KQkq - 0 3", b.FEN().c_str());

    // 3. Nc3       (0,1) to (2,2)
    shadows[0][1] = 0;
    shadows[2][2] = 1;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    b.move(*findMove(candidate_moves, 2, 2));
    ASSERT_STREQ("rnbqkbnr/ppp1pppp/8/8/2P1p3/2N5/PP1P1PPP/R1BQKBNR b KQkq - 0 3", b.FEN().c_str());
    // rnbqkbnr/ppp1pppp/8/8/2P1p3/2N5/PP1P1PPP/R1BQKBNR b KQkq - 1 3

    // 3. ... Nf3  (7,6) to (5,5)
    shadows[7][6] = 0;
    shadows[5][5] = 1;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    b.move(*findMove(candidate_moves, 5, 5));
    ASSERT_STREQ("rnbqkb1r/ppp1pppp/5n2/8/2P1p3/2N5/PP1P1PPP/R1BQKBNR w KQkq - 0 4", b.FEN().c_str());
    // rnbqkb1r/ppp1pppp/5n2/8/2P1p3/2N5/PP1P1PPP/R1BQKBNR w KQkq - 2 4

    // 4. Qg4      (0,3) to (3,6)
    shadows[0][3] = 0;
    shadows[3][6] = 1;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    b.move(*findMove(candidate_moves, 3, 6));
    ASSERT_STREQ("rnbqkb1r/ppp1pppp/5n2/8/2P1p1Q1/2N5/PP1P1PPP/R1B1KBNR b KQkq - 0 4", b.FEN().c_str());
    // rnbqkb1r/ppp1pppp/5n2/8/2P1p1Q1/2N5/PP1P1PPP/R1B1KBNR b KQkq - 3 4

    // 4. ... h5   (6,7) to (4,7)
    shadows[6][7] = 0;
    shadows[4][7] = 1;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    b.move(*findMove(candidate_moves, 4, 7));
    ASSERT_STREQ("rnbqkb1r/ppp1ppp1/5n2/7p/2P1p1Q1/2N5/PP1P1PPP/R1B1KBNR w KQkq h6 0 5", b.FEN().c_str());

    // 5. Qxh5     (3,6) to (4,7)
    // four candidate moves
    shadows[3][6] = 0;
    shadows[4][7] = 1;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(4, candidate_moves.size());
    b.move(*findMove(candidate_moves, 4, 7));
    ASSERT_STREQ("rnbqkb1r/ppp1ppp1/5n2/7Q/2P1p3/2N5/PP1P1PPP/R1B1KBNR b KQkq - 0 5", b.FEN().c_str());

    // 5. ... Rxh5 (7,7) to (4,7)
    shadows[7][7] = 0;
    shadows[4][7] = 1;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    b.move(*findMove(candidate_moves, 4, 7));
    ASSERT_STREQ("rnbqkb2/ppp1ppp1/5n2/7r/2P1p3/2N5/PP1P1PPP/R1B1KBNR w KQq - 0 6", b.FEN().c_str());

    // 6. c5       (3,2) to (4,2)
    shadows[3][2] = 0;
    shadows[4][2] = 1;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    b.move(*findMove(candidate_moves, 4, 2));
    ASSERT_STREQ("rnbqkb2/ppp1ppp1/5n2/2P4r/4p3/2N5/PP1P1PPP/R1B1KBNR b KQq - 0 6", b.FEN().c_str());

    // 6. ... Rxc5 (4,7) to (4,2)
    // two possible moves
    shadows[4][7] = 0;
    shadows[4][2] = 1;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(2, candidate_moves.size());
    b.move(*findMove(candidate_moves, 4, 2));
    ASSERT_STREQ("rnbqkb2/ppp1ppp1/5n2/2r5/4p3/2N5/PP1P1PPP/R1B1KBNR w KQq - 0 7", b.FEN().c_str());

    // 7. g4       (1,6) to (3,6)
    shadows[1][6] = 0;
    shadows[3][6] = 1;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    b.move(*findMove(candidate_moves, 3, 6));
    ASSERT_STREQ("rnbqkb2/ppp1ppp1/5n2/2r5/4p1P1/2N5/PP1P1P1P/R1B1KBNR b KQq g3 0 7", b.FEN().c_str());

    // 7. ... Qd6  (7,3) to (5,3)
    shadows[7][3] = 0;
    shadows[5][3] = 1;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    b.move(*findMove(candidate_moves, 5, 3));
    ASSERT_STREQ("rnb1kb2/ppp1ppp1/3q1n2/2r5/4p1P1/2N5/PP1P1P1P/R1B1KBNR w KQq - 0 8", b.FEN().c_str());
    // rnb1kb2/ppp1ppp1/3q1n2/2r5/4p1P1/2N5/PP1P1P1P/R1B1KBNR w KQq - 1 8

    // 8. Nxe4    (2,2) to (3,4)
    shadows[2][2] = 0;
    shadows[3][4] = 1;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    b.move(*findMove(candidate_moves, 3, 4));
    ASSERT_STREQ("rnb1kb2/ppp1ppp1/3q1n2/2r5/4N1P1/8/PP1P1P1P/R1B1KBNR b KQq - 0 8", b.FEN().c_str());

    // 8. ... g5  (6,6) to (4,6)
    shadows[6][6] = 0;
    shadows[4][6] = 1;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    b.move(*findMove(candidate_moves, 4, 6));
    ASSERT_STREQ("rnb1kb2/ppp1pp2/3q1n2/2r3p1/4N1P1/8/PP1P1P1P/R1B1KBNR w KQq g6 0 9", b.FEN().c_str());

    // 9. Nxd6+   (3,4) to (5,3)
    // four candidate moves
    shadows[3][4] = 0;
    shadows[5][3] = 1;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(4, candidate_moves.size());
    b.move(*findMove(candidate_moves, 5, 3));
    ASSERT_STREQ("rnb1kb2/ppp1pp2/3N1n2/2r3p1/6P1/8/PP1P1P1P/R1B1KBNR b KQq - 0 9", b.FEN().c_str());

    // 9. ... Kd8 (7,4) to (7,3)
    shadows[7][4] = 0;
    shadows[7][3] = 1;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    b.move(*findMove(candidate_moves, 7, 3));
    ASSERT_STREQ("rnbk1b2/ppp1pp2/3N1n2/2r3p1/6P1/8/PP1P1P1P/R1B1KBNR w KQ - 0 10", b.FEN().c_str());
    // rnbk1b2/ppp1pp2/3N1n2/2r3p1/6P1/8/PP1P1P1P/R1B1KBNR w KQ - 1 10

    // 10. Nxb7+   (5,3) to (6,1)
    // three possible moves
    shadows[5][3] = 0;
    shadows[6][1] = 1;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(3, candidate_moves.size());
    b.move(*findMove(candidate_moves, 6, 1));
    ASSERT_STREQ("rnbk1b2/pNp1pp2/5n2/2r3p1/6P1/8/PP1P1P1P/R1B1KBNR b KQ - 0 10", b.FEN().c_str());

    // 10. ... Bxb7 (7,2) to (6,1)
    // just one option for the bishop, because in check
    shadows[7][2] = 0;
    shadows[6][1] = 1;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    b.move(*findMove(candidate_moves, 6, 1));
    ASSERT_STREQ("rn1k1b2/pbp1pp2/5n2/2r3p1/6P1/8/PP1P1P1P/R1B1KBNR w KQ - 0 11", b.FEN().c_str());

    // 11. Ba6      (0,5) to (5,0)
    shadows[0][5] = 0;
    shadows[5][0] = 1;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    b.move(*findMove(candidate_moves, 5, 0));
    ASSERT_STREQ("rn1k1b2/pbp1pp2/B4n2/2r3p1/6P1/8/PP1P1P1P/R1B1K1NR b KQ - 0 11", b.FEN().c_str());
    // rn1k1b2/pbp1pp2/B4n2/2r3p1/6P1/8/PP1P1P1P/R1B1K1NR b KQ - 1 11

    // 11. ... Bxh1 (6,1) to (0,7)
    // two possible moves
    shadows[6][1] = 0;
    shadows[0][7] = 1;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(2, candidate_moves.size());
    b.move(*findMove(candidate_moves, 0, 7));
    ASSERT_STREQ("rn1k1b2/p1p1pp2/B4n2/2r3p1/6P1/8/PP1P1P1P/R1B1K1Nb w Q - 0 12", b.FEN().c_str());

    // 12. Nf3      (0,6) to (2,5)
    shadows[0][6] = 0;
    shadows[2][5] = 1;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    b.move(*findMove(candidate_moves, 2, 5));
    ASSERT_STREQ("rn1k1b2/p1p1pp2/B4n2/2r3p1/6P1/5N2/PP1P1P1P/R1B1K2b b Q - 0 12", b.FEN().c_str());
    // rn1k1b2/p1p1pp2/B4n2/2r3p1/6P1/5N2/PP1P1P1P/R1B1K2b b Q - 1 12

    // 12. ... Nxg4 (5,5) to (3,6)
    shadows[5][5] = 0;
    shadows[3][6] = 1;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    b.move(*findMove(candidate_moves, 3, 6));
    ASSERT_STREQ("rn1k1b2/p1p1pp2/B7/2r3p1/6n1/5N2/PP1P1P1P/R1B1K2b w Q - 0 13", b.FEN().c_str());

    // 13. Ne5      (2,5) to (4,4)
    shadows[2][5] = 0;
    shadows[4][4] = 1;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    b.move(*findMove(candidate_moves, 4, 4));
    ASSERT_STREQ("rn1k1b2/p1p1pp2/B7/2r1N1p1/6n1/8/PP1P1P1P/R1B1K2b b Q - 0 13", b.FEN().c_str());
    // rn1k1b2/p1p1pp2/B7/2r1N1p1/6n1/8/PP1P1P1P/R1B1K2b b Q - 1 13

    // 13. ... Nxf2 (3,6) to (1,5)
    // three possible moves
    shadows[3][6] = 0;
    shadows[1][5] = 1;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(3, candidate_moves.size());
    b.move(*findMove(candidate_moves, 1, 5));
    ASSERT_STREQ("rn1k1b2/p1p1pp2/B7/2r1N1p1/8/8/PP1P1n1P/R1B1K2b w Q - 0 14", b.FEN().c_str());

    // 14. Nd7      (4,4) to (6,3)
    shadows[4][4] = 0;
    shadows[6][3] = 1;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    b.move(*findMove(candidate_moves, 6, 3));
    ASSERT_STREQ("rn1k1b2/p1pNpp2/B7/2r3p1/8/8/PP1P1n1P/R1B1K2b b Q - 0 14", b.FEN().c_str());
    // rn1k1b2/p1pNpp2/B7/2r3p1/8/8/PP1P1n1P/R1B1K2b b Q - 1 14

    // 14. ... Rc2  (4,2) to (1,2)
    shadows[4][2] = 0;
    shadows[1][2] = 1;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    b.move(*findMove(candidate_moves, 1, 2));
    ASSERT_STREQ("rn1k1b2/p1pNpp2/B7/6p1/8/8/PPrP1n1P/R1B1K2b w Q - 0 15", b.FEN().c_str());
    // rn1k1b2/p1pNpp2/B7/6p1/8/8/PPrP1n1P/R1B1K2b w Q - 2 15

    // 15. Bc8      (5,0) to (7,2)
    shadows[5][0] = 0;
    shadows[7][2] = 1;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    b.move(*findMove(candidate_moves, 7, 2));
    ASSERT_STREQ("rnBk1b2/p1pNpp2/8/6p1/8/8/PPrP1n1P/R1B1K2b b Q - 0 15", b.FEN().c_str());
    // rnBk1b2/p1pNpp2/8/6p1/8/8/PPrP1n1P/R1B1K2b b Q - 3 15

    // 15. ... Rxd2 (1,2) to (1,3)
    // three possible moves
    shadows[1][2] = 0;
    shadows[1][3] = 1;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(3, candidate_moves.size());
    b.move(*findMove(candidate_moves, 1, 3));
    ASSERT_STREQ("rnBk1b2/p1pNpp2/8/6p1/8/8/PP1r1n1P/R1B1K2b w Q - 0 16", b.FEN().c_str());

    // 16. b3       (1,1) to (2,1)
    shadows[1][1] = 0;
    shadows[2][1] = 1;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    b.move(*findMove(candidate_moves, 2, 1));
    ASSERT_STREQ("rnBk1b2/p1pNpp2/8/6p1/8/1P6/P2r1n1P/R1B1K2b b Q - 0 16", b.FEN().c_str());

    // 16. ... Bf3  (0,7) to (2,5)
    shadows[0][7] = 0;
    shadows[2][5] = 1;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    b.move(*findMove(candidate_moves, 2, 5));
    ASSERT_STREQ("rnBk1b2/p1pNpp2/8/6p1/8/1P3b2/P2r1n1P/R1B1K3 w Q - 0 17", b.FEN().c_str());
    // rnBk1b2/p1pNpp2/8/6p1/8/1P3b2/P2r1n1P/R1B1K3 w Q - 1 17

    // 17. Ba3      (0,2) to (2,0)
    shadows[0][2] = 0;
    shadows[2][0] = 1;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    b.move(*findMove(candidate_moves, 2, 0));
    ASSERT_STREQ("rnBk1b2/p1pNpp2/8/6p1/8/BP3b2/P2r1n1P/R3K3 b Q - 0 17", b.FEN().c_str());
    // rnBk1b2/p1pNpp2/8/6p1/8/BP3b2/P2r1n1P/R3K3 b Q - 2 17

    // 17. ... Be2  (2,5) to (1,4)
    shadows[2][5] = 0;
    shadows[1][4] = 1;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    b.move(*findMove(candidate_moves, 1, 4));
    ASSERT_STREQ("rnBk1b2/p1pNpp2/8/6p1/8/BP6/P2rbn1P/R3K3 w Q - 0 18", b.FEN().c_str());
    // rnBk1b2/p1pNpp2/8/6p1/8/BP6/P2rbn1P/R3K3 w Q - 3 18

    // 18. Bxe7+    (2,0) to (6,4)
    shadows[2][0] = 0;
    shadows[6][4] = 1;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(1, candidate_moves.size());
    b.move(*findMove(candidate_moves, 6, 4));
    ASSERT_STREQ("rnBk1b2/p1pNBp2/8/6p1/8/1P6/P2rbn1P/R3K3 b Q - 0 18", b.FEN().c_str());

    // 18. ... Kxc8 (7,3) to (7,2)
    // two possible moves
    shadows[7][3] = 0;
    shadows[7][2] = 1;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(2, candidate_moves.size());
    b.move(*findMove(candidate_moves, 7, 2));
    ASSERT_STREQ("rnk2b2/p1pNBp2/8/6p1/8/1P6/P2rbn1P/R3K3 w Q - 0 19", b.FEN().c_str());

    // 19. Kxd2     (0,4) to (1,3)
    // two possible moves
    shadows[0][4] = 0;
    shadows[1][3] = 1;
    candidate_moves = b.findMovement(shadows);
    ASSERT_EQ(2, candidate_moves.size());
    b.move(*findMove(candidate_moves, 1, 3));
    ASSERT_STREQ("rnk2b2/p1pNBp2/8/6p1/8/1P6/P2Kbn1P/R7 b - - 0 19", b.FEN().c_str());

    // 19. ...

}
