#include <assert.h>
#include <iostream>
#include "Chess.h"
#include "ChessBoard.hh"
#include "ChessPiece.hh"

void test_scanValidity(Student::ChessBoard &sBoard) {
    for (int i = 0; i < sBoard.getNumRows(); i++) {       // loops through entire board to search for pieces
        for (int j = 0; j < sBoard.getNumCols(); j++) {
            Student::ChessPiece *piece = sBoard.getPiece(i,j);
            if (piece != nullptr) {
                std::cout << "Index: " << i << "," << j << "  ->  "; // prints out location and Type of piece
                switch (piece->getColor()) {
                    case 0: std::cout << "Black ";
                            break;
                    case 1: std::cout << "White ";
                            break;
                }
                switch (piece->getType()) {
                    case 0: std::cout << "Pawn ";
                            break;
                    case 1: std::cout << "Rook "; 
                            break;
                    case 2: std::cout << "Bishop ";
                            break;
                    case 3: std::cout << "King ";
                }

                std::cout << (sBoard.isPieceUnderThreat(i,j) ? "  Under Threat" : "  X") << std::endl; // prints under threat or not
            }
        }
    }
}

void isValidScan(Student::ChessBoard &sBoard) {
    for (int row = 0; row < sBoard.getNumRows(); row++) {
        for (int col = 0; col < sBoard.getNumCols(); col++) {   // loop through board and find a piece

            Student::ChessPiece* piece = sBoard.getPiece(row, col);
            if (piece != nullptr) {                                 // if the piece exists check every location and see if it can move there
                std::cout << "Index: " << row << "," << col << "  ->  "; // prints out location and Type of piece
                switch (piece->getColor()) {
                    case 0: std::cout << "Black ";
                            break;
                    case 1: std::cout << "White ";
                            break;
                }
                switch (piece->getType()) {
                    case 0: std::cout << "Pawn ";
                            break;
                    case 1: std::cout << "Rook "; 
                            break;
                    case 2: std::cout << "Bishop ";
                            break;
                    case 3: std::cout << "King ";
                }
                std::cout << std::endl;

                for (int row2 = 0; row2 < sBoard.getNumCols(); row2++) {
                    for (int col2 = 0; col2 < sBoard.getNumRows(); col2++) {
                        if (sBoard.isValidMove(row, col, row2, col2)) {
                            std::cout << row2 << ", " << col2 << "   " <<std::endl;  // print out where it can move
                        }
                    }
                }
                //std::cout << std::endl;
            }
        }
    }
}

void test_part1_4x4_1()
{
    // Config file content:
    // 0
    // 4 4
    // w r 3 2
    // b b 1 3
    // b r 1 1
    // w r 2 3
    // ~
    // isValidScan

    // Corresponding code
    Student::ChessBoard sBoard(4, 4);
    sBoard.createChessPiece(White, Rook, 3, 2);
    sBoard.createChessPiece(Black, Bishop, 1, 3);
    sBoard.createChessPiece(Black, Rook, 1, 1);
    sBoard.createChessPiece(White, Rook, 2, 3);

    // verify size and pieces
    assert(sBoard.getNumRows() == 4);
    assert(sBoard.getNumCols() == 4);

    // verify first rook was inputted
    assert(sBoard.getPiece(3,2)->getType() == Rook);
    assert(sBoard.getPiece(3,2)->getColor() == White);

    // verify bishop
    assert(sBoard.getPiece(1,3)->getType() == Bishop);
    assert(sBoard.getPiece(1,3)->getColor() == Black);

    //verify second rook
    assert(sBoard.getPiece(1,1)->getType() == Rook);
    assert(sBoard.getPiece(1,1)->getColor() == Black);

    //verify third rook
    assert(sBoard.getPiece(2,3)->getType() == Rook);
    assert(sBoard.getPiece(2,3)->getColor() == White);

    // verify character outputs and display
    std::ostringstream board_result = sBoard.displayBoard();
    std::cout << board_result.str() << std::endl;

    // Calls isValidMove() from every position to every
    // other position on the chess board for all pieces.
    assert(!sBoard.isValidMove(0,0,1,1));

    for (int i = 0; i < sBoard.getNumRows(); i++) {       // verifies which Bishop 3,0 movements are valid
        for (int j = 0; j < sBoard.getNumCols(); j++) {
            Student::ChessPiece *piece = sBoard.getPiece(i,j);
            if (piece != nullptr) {
                std::cout << "Index: " << i << "," << j << "  ->  ";
                switch (piece->getColor()) {
                    case 0: std::cout << "Black ";
                            break;
                    case 1: std::cout << "White ";
                            break;
                }
                switch (piece->getType()) {
                    case 0: std::cout << "Pawn ";
                            break;
                    case 1: std::cout << "Rook "; 
                            break;
                    case 2: std::cout << "Bishop ";
                            break;
                    case 3: std::cout << "King ";
                }
                std::cout << "" << std::endl;
                for (int row = 0; row < sBoard.getNumRows(); row++) {
                    for (int col = 0; col < sBoard.getNumCols(); col++) {
                        if (sBoard.isValidMove(i,j,row,col)) {
                            std::cout << "    "<< row << "," << col << std::endl;
                        }
                    }
                }
            }
            else {
                //std::cout << "Index: " << i << "," << j << " N/A" << std::endl;
            }
        }
    }
    /*
    for (int i = 0; i < 4; i++) {       // verifies which rook 3,2 movements are valid
        for (int j = 0; j < 4; j++) {
            if (sBoard.isValidMove(3,2,i,j)) {
                std::cout << i << "," << j << " Rook 3,2" << std::endl;
            }
        }
    }
    
    for (int i = 0; i < 4; i++) {       // verifies which rook 1,1 movements are valid
        for (int j = 0; j < 4; j++) {
            if (sBoard.isValidMove(1,1,i,j)) {
                std::cout << i << "," << j << " Rook 1,1" << std::endl;
            }
        }
    }
    
    for (int i = 0; i < 4; i++) {       // verifies which rook 2,3 movements are valid
        for (int j = 0; j < 4; j++) {
            if (sBoard.isValidMove(2,3,i,j)) {
                std::cout << "Row,Col " << i << "," << j << " Rook 2,3" << std::endl;
            }
        }
    }
    */
    return;
}

void test_part1_4x4_2() {
    /*  
    0
    4 4
    b r 0 2
    w b 3 0
    b r 2 2
    w b 3 3
    ~
    isValidScan */
    Student::ChessBoard sBoard(4, 4);
    sBoard.createChessPiece(Black, Rook, 0, 2);
    sBoard.createChessPiece(White, Bishop, 3, 0);
    sBoard.createChessPiece(Black, Rook, 2, 2);
    sBoard.createChessPiece(White, Bishop, 3, 3);

    std::cout << sBoard.displayBoard().str() << std::endl;

    for (int i = 0; i < sBoard.getNumRows(); i++) {       // verifies which Bishop 3,0 movements are valid
        for (int j = 0; j < sBoard.getNumCols(); j++) {
            Student::ChessPiece *piece = sBoard.getPiece(i,j);
            if (piece != nullptr) {
                std::cout << "Index: " << i << "," << j << "  ->  ";
                switch (piece->getColor()) {
                    case 0: std::cout << "Black ";
                            break;
                    case 1: std::cout << "White ";
                            break;
                }
                switch (piece->getType()) {
                    case 0: std::cout << "Pawn ";
                            break;
                    case 1: std::cout << "Rook "; 
                            break;
                    case 2: std::cout << "Bishop ";
                            break;
                    case 3: std::cout << "King ";
                }
                std::cout << "" << std::endl;
                for (int row = 0; row < sBoard.getNumRows(); row++) {
                    for (int col = 0; col < sBoard.getNumCols(); col++) {
                        if (sBoard.isValidMove(i,j,row,col)) {
                            std::cout << "    "<< row << "," << col << std::endl;
                        }
                    }
                }
            }
            else {
                //std::cout << "Index: " << i << "," << j << " N/A" << std::endl;
            }
        }
    }
    return;
}

void test_part1_4x4_3() {
    /* 
    0
    4 4
    w b 2 2
    w r 1 0
    w p 1 1
    b p 0 1
    ~
    isValidScan */
    Student::ChessBoard sBoard(4, 4);
    sBoard.createChessPiece(White, Bishop, 2, 2);
    sBoard.createChessPiece(White, Rook, 1, 0);
    sBoard.createChessPiece(White, Pawn, 1, 1);
    sBoard.createChessPiece(Black, Pawn, 0, 1);

    std::cout << sBoard.displayBoard().str() << std::endl;

    for (int i = 0; i < sBoard.getNumRows(); i++) {       // verifies which Bishop 3,0 movements are valid
        for (int j = 0; j < sBoard.getNumCols(); j++) {
            Student::ChessPiece *piece = sBoard.getPiece(i,j);
            if (piece != nullptr) {
                std::cout << "Index: " << i << "," << j << "  ->  ";
                switch (piece->getColor()) {
                    case 0: std::cout << "Black ";
                            break;
                    case 1: std::cout << "White ";
                            break;
                }
                switch (piece->getType()) {
                    case 0: std::cout << "Pawn ";
                            break;
                    case 1: std::cout << "Rook "; 
                            break;
                    case 2: std::cout << "Bishop ";
                            break;
                    case 3: std::cout << "King ";
                }
                std::cout << "" << std::endl;
                for (int row = 0; row < sBoard.getNumRows(); row++) {
                    for (int col = 0; col < sBoard.getNumCols(); col++) {
                        if (sBoard.isValidMove(i,j,row,col)) {
                            std::cout << "    "<< row << "," << col << std::endl;
                        }
                    }
                }
            }
            else {
                std::cout << "Index: " << i << "," << j << " N/A" << std::endl;
            }
        }
    }
    return;
}

void test_part1_6x6_2() {
    /*        
    0
    6 6
    b r 2 2
    w b 1 1
    w b 0 0
    w r 1 4
    w p 3 3
    b p 2 1
    ~
    isValidScan */

    Student::ChessBoard sBoard(6, 6);
    sBoard.createChessPiece(Black, Rook, 2, 2);
    sBoard.createChessPiece(White, Bishop, 1, 1);
    sBoard.createChessPiece(White, Bishop, 0, 0);
    sBoard.createChessPiece(White, Rook, 1, 4);
    sBoard.createChessPiece(White, Pawn, 3, 3);
    sBoard.createChessPiece(Black, Pawn, 2, 1);

    std::cout << sBoard.displayBoard().str() << std::endl;

    for (int i = 0; i < sBoard.getNumRows(); i++) {       // verifies which Bishop 3,0 movements are valid
        for (int j = 0; j < sBoard.getNumCols(); j++) {
            Student::ChessPiece *piece = sBoard.getPiece(i,j);
            if (piece != nullptr) {
                std::cout << "Index: " << i << "," << j << "  ->  ";
                switch (piece->getColor()) {
                    case 0: std::cout << "Black ";
                            break;
                    case 1: std::cout << "White ";
                            break;
                }
                switch (piece->getType()) {
                    case 0: std::cout << "Pawn ";
                            break;
                    case 1: std::cout << "Rook "; 
                            break;
                    case 2: std::cout << "Bishop ";
                            break;
                    case 3: std::cout << "King ";
                }
                std::cout << "" << std::endl;
                for (int row = 0; row < sBoard.getNumRows(); row++) {
                    for (int col = 0; col < sBoard.getNumCols(); col++) {
                        if (sBoard.isValidMove(i,j,row,col)) {
                            std::cout << "    "<< row << "," << col << std::endl;
                        }
                    }
                }
            }
            else {
                std::cout << "Index: " << i << "," << j << " N/A" << std::endl;
            }
        }
    }
    return;
}

void test_part1_8x8_10() {
    /*
    0
    8 8
    b r 2 1
    b p 3 1
    b r 0 2 
    b p 5 7
    w p 7 6
    w b 3 5
    w r 2 2
    b p 4 7
    b r 0 2
    b p 4 4
    w b 6 2
    w p 2 7
    b p 5 6
    b r 3 3
    b b 5 3
    b r 2 6
    ~
    isValidScan
    */
   
    Student::ChessBoard sBoard(8, 8);
    sBoard.createChessPiece(Black, Rook, 2, 2);
    sBoard.createChessPiece(Black, Pawn, 3, 1);
    sBoard.createChessPiece(Black, Rook, 0, 2);
    sBoard.createChessPiece(Black, Pawn, 5, 7);
    sBoard.createChessPiece(White, Pawn, 7, 6);
    sBoard.createChessPiece(White, Bishop, 3, 5);
    sBoard.createChessPiece(White, Rook, 2, 2);
    sBoard.createChessPiece(Black, Pawn, 4, 7);
    sBoard.createChessPiece(Black, Rook, 0, 2);
    sBoard.createChessPiece(Black, Pawn, 4, 4);
    sBoard.createChessPiece(White, Bishop, 6, 2);
    sBoard.createChessPiece(White, Pawn, 2, 7);
    sBoard.createChessPiece(Black, Pawn, 5, 6);
    sBoard.createChessPiece(Black, Rook, 3, 3);
    sBoard.createChessPiece(Black, Bishop, 5, 3);
    sBoard.createChessPiece(Black, Rook, 2, 6);

    std::cout << sBoard.displayBoard().str() << std::endl;

    for (int i = 0; i < sBoard.getNumRows(); i++) {       // verifies which Bishop 3,0 movements are valid
        for (int j = 0; j < sBoard.getNumCols(); j++) {
            Student::ChessPiece *piece = sBoard.getPiece(i,j);
            if (piece != nullptr) {
                std::cout << "Index: " << i << "," << j << "  ->  ";
                switch (piece->getColor()) {
                    case 0: std::cout << "Black ";
                            break;
                    case 1: std::cout << "White ";
                            break;
                }
                switch (piece->getType()) {
                    case 0: std::cout << "Pawn ";
                            break;
                    case 1: std::cout << "Rook "; 
                            break;
                    case 2: std::cout << "Bishop ";
                            break;
                    case 3: std::cout << "King ";
                }
                std::cout << "" << std::endl;
                for (int row = 0; row < sBoard.getNumRows(); row++) {
                    for (int col = 0; col < sBoard.getNumCols(); col++) {
                        if (sBoard.isValidMove(i,j,row,col)) {
                            std::cout << "    "<< row << "," << col << std::endl;
                        }
                    }
                }
            }
            else {
                //std::cout << "Index: " << i << "," << j << " N/A" << std::endl;
            }
        }
    }
    return;
}

void test_part1_8x8_1() {
    /*
    0
    8 8
    w r 7 6
    b b 1 7
    b r 1 5
    w r 2 3
    b r 4 2
    w b 3 0
    b r 6 2
    w b 3 7
    ~
    isValidScan
    */

    Student::ChessBoard sBoard(8, 8);
    sBoard.createChessPiece(White, Rook, 7, 6);
    sBoard.createChessPiece(Black, Bishop, 1, 7);
    sBoard.createChessPiece(Black, Rook, 1, 5);
    sBoard.createChessPiece(White, Rook, 2, 3);
    sBoard.createChessPiece(Black, Rook, 4, 2);
    sBoard.createChessPiece(White, Bishop, 3, 0);
    sBoard.createChessPiece(Black, Rook, 6, 2);
    sBoard.createChessPiece(White, Bishop, 3, 7);

    std::cout << sBoard.displayBoard().str() << std::endl;

    for (int i = 0; i < sBoard.getNumRows(); i++) {       // verifies which Bishop 3,0 movements are valid
        for (int j = 0; j < sBoard.getNumCols(); j++) {
            Student::ChessPiece *piece = sBoard.getPiece(i,j);
            if (piece != nullptr) {
                std::cout << "Index: " << i << "," << j << "  ->  ";
                switch (piece->getColor()) {
                    case 0: std::cout << "Black ";
                            break;
                    case 1: std::cout << "White ";
                            break;
                }
                switch (piece->getType()) {
                    case 0: std::cout << "Pawn ";
                            break;
                    case 1: std::cout << "Rook "; 
                            break;
                    case 2: std::cout << "Bishop ";
                            break;
                    case 3: std::cout << "King ";
                }
                std::cout << "" << std::endl;
                for (int row = 0; row < sBoard.getNumRows(); row++) {
                    for (int col = 0; col < sBoard.getNumCols(); col++) {
                        if (sBoard.isValidMove(i,j,row,col)) {
                            std::cout << "    "<< row << "," << col << std::endl;
                        }
                    }
                }
            }
            else {
                //std::cout << "Index: " << i << "," << j << " N/A" << std::endl;
            }
        }
    }
    return;
}

void test_part1_4x4_5() {
    /*
    0
    4 4
    b b 0 1
    b b 1 1
    b b 2 1
    w p 2 0
    ~
    isValidScan
    */
    
    Student::ChessBoard sBoard(4, 4);
    sBoard.createChessPiece(Black, Bishop, 0, 1);
    sBoard.createChessPiece(Black, Bishop, 1, 1);
    sBoard.createChessPiece(Black, Bishop, 2, 1);
    sBoard.createChessPiece(White, Pawn, 2, 0);

    std::cout << sBoard.displayBoard().str() << std::endl;

    for (int i = 0; i < sBoard.getNumRows(); i++) {       // verifies which Bishop 3,0 movements are valid
        for (int j = 0; j < sBoard.getNumCols(); j++) {
            Student::ChessPiece *piece = sBoard.getPiece(i,j);
            if (piece != nullptr) {
                std::cout << "Index: " << i << "," << j << "  ->  ";
                switch (piece->getColor()) {
                    case 0: std::cout << "Black ";
                            break;
                    case 1: std::cout << "White ";
                            break;
                }
                switch (piece->getType()) {
                    case 0: std::cout << "Pawn ";
                            break;
                    case 1: std::cout << "Rook "; 
                            break;
                    case 2: std::cout << "Bishop ";
                            break;
                    case 3: std::cout << "King ";
                }
                std::cout << "" << std::endl;
                for (int row = 0; row < sBoard.getNumRows(); row++) {
                    for (int col = 0; col < sBoard.getNumCols(); col++) {
                        if (sBoard.isValidMove(i,j,row,col)) {
                            std::cout << "    "<< row << "," << col << std::endl;
                        }
                    }
                }
            }
            else {
                //std::cout << "Index: " << i << "," << j << " N/A" << std::endl;
            }
        }
    }
    return;
}

void test_part2_4x4_1() {
    /*
    0
    4 4
    w r 3 2
    b b 1 3
    b r 1 1
    w r 2 3
    ~
    isValidScan
    underThreatScan
    movePiece 3 2 3 1
    movePiece 1 1 1 2
    movePiece 2 3 2 1
    movePiece 1 2 0 2
    movePiece 0 0 2 3
    isValidScan
    underThreatScan
    movePiece 2 1 0 1
    movePiece 1 3 2 2
    movePiece 3 1 3 0
    movePiece 2 2 3 1
    movePiece 0 2 1 0
    isValidScan
    underThreatScan
    movePiece 3 0 3 1
    movePiece 0 2 2 2
    movePiece 3 1 3 0
    movePiece 2 2 1 2
    movePiece 1 1 2 3
    isValidScan
    underThreatScan
    movePiece 3 0 0 0
    */

    Student::ChessBoard sBoard(4, 4);
    sBoard.createChessPiece(White, Rook, 3, 2);
    sBoard.createChessPiece(Black, Bishop, 1, 3);
    sBoard.createChessPiece(Black, Rook, 1, 1);
    sBoard.createChessPiece(White, Rook, 2, 3);

    std::cout << sBoard.displayBoard().str() << std::endl;

    for (int i = 0; i < sBoard.getNumRows(); i++) {       // loops through entire board to search for pieces
        for (int j = 0; j < sBoard.getNumCols(); j++) {
            Student::ChessPiece *piece = sBoard.getPiece(i,j);
            if (piece != nullptr) {
                
                std::cout << "Index: " << i << "," << j << "  ->  "; // prints out location and Type of piece
                switch (piece->getColor()) {
                    case 0: std::cout << "Black ";
                            break;
                    case 1: std::cout << "White ";
                            break;
                }
                switch (piece->getType()) {
                    case 0: std::cout << "Pawn ";
                            break;
                    case 1: std::cout << "Rook "; 
                            break;
                    case 2: std::cout << "Bishop ";
                            break;
                    case 3: std::cout << "King ";
                }
                std::cout << "" << std::endl;

                std::cout << (sBoard.isPieceUnderThreat(i,j) ? "Under Threat" : "X") << std::endl; // prints under threat or not

                /*                 
                for (int row = 0; row < sBoard.getNumRows(); row++) {   // lists all possible moves of a piece
                    for (int col = 0; col < sBoard.getNumCols(); col++) {
                        if (sBoard.isValidMove(i,j,row,col)) {
                            std::cout << "    "<< row << "," << col << std::endl;
                        }
                    }
                }
                 */
            }
        }
    }
    // perform movements
    sBoard.movePiece(3, 2, 3, 1); //moved
    std::cout << sBoard.displayBoard().str() << std::endl;

    sBoard.movePiece(1, 1, 1, 2); //moved
    std::cout << sBoard.displayBoard().str() << std::endl;

    sBoard.movePiece(2, 3, 2, 1); //moved
    std::cout << sBoard.displayBoard().str() << std::endl;

    sBoard.movePiece(1, 2, 0, 2); //didnt move
    std::cout << sBoard.displayBoard().str() << std::endl;

    sBoard.movePiece(0, 0, 2, 3); //didnt move
    std::cout << sBoard.displayBoard().str() << std::endl;

    // check what those movements changed

    for (int i = 0; i < sBoard.getNumRows(); i++) {       // loops through entire board to search for pieces
        for (int j = 0; j < sBoard.getNumCols(); j++) {
            Student::ChessPiece *piece = sBoard.getPiece(i,j);
            if (piece != nullptr) {
                
                std::cout << "Index: " << i << "," << j << "  ->  "; // prints out location and Type of piece
                switch (piece->getColor()) {
                    case 0: std::cout << "Black ";
                            break;
                    case 1: std::cout << "White ";
                            break;
                }
                switch (piece->getType()) {
                    case 0: std::cout << "Pawn ";
                            break;
                    case 1: std::cout << "Rook "; 
                            break;
                    case 2: std::cout << "Bishop ";
                            break;
                    case 3: std::cout << "King ";
                }
                std::cout << "" << std::endl;

                std::cout << (sBoard.isPieceUnderThreat(i,j) ? "Under Threat" : "X") << std::endl; // prints under threat or not

                /*
                for (int row = 0; row < sBoard.getNumRows(); row++) {   // lists all possible moves of a piece
                    for (int col = 0; col < sBoard.getNumCols(); col++) {
                        if (sBoard.isValidMove(i,j,row,col)) {
                            std::cout << "    "<< row << "," << col << std::endl;
                        }
                    }
                }
                */
            }
        }
    }

    // second set of moves
    sBoard.movePiece(2, 1, 0, 1);
    std::cout << "2-1 moved 0-1" << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;

    sBoard.movePiece(1, 3, 2, 2);
    std::cout << "1-3 moved 2-2" << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;

    sBoard.movePiece(3, 1, 3, 0);
    std::cout << "3-1 moved 3-0" << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;

    sBoard.movePiece(2, 2, 3, 1);
    std::cout << "2-2 moved 3-1" << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;

    sBoard.movePiece(0, 2, 1, 0);
    std::cout << "0-2 moved 1-0" << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;

    for (int i = 0; i < sBoard.getNumRows(); i++) {       // loops through entire board to search for pieces
        for (int j = 0; j < sBoard.getNumCols(); j++) {
            Student::ChessPiece *piece = sBoard.getPiece(i,j);
            if (piece != nullptr) {
                
                std::cout << "Index: " << i << "," << j << "  ->  "; // prints out location and Type of piece
                switch (piece->getColor()) {
                    case 0: std::cout << "Black ";
                            break;
                    case 1: std::cout << "White ";
                            break;
                }
                switch (piece->getType()) {
                    case 0: std::cout << "Pawn ";
                            break;
                    case 1: std::cout << "Rook "; 
                            break;
                    case 2: std::cout << "Bishop ";
                            break;
                    case 3: std::cout << "King ";
                }
                std::cout << "" << std::endl;

                std::cout << (sBoard.isPieceUnderThreat(i,j) ? "Under Threat" : "X") << std::endl; // prints under threat or not

                /*
                for (int row = 0; row < sBoard.getNumRows(); row++) {   // lists all possible moves of a piece
                    for (int col = 0; col < sBoard.getNumCols(); col++) {
                        if (sBoard.isValidMove(i,j,row,col)) {
                            std::cout << "    "<< row << "," << col << std::endl;
                        }
                    }
                }
                */
            }
        }
    }
    return;
}

void test_part3_4x4_1() {

    Student::ChessBoard sBoard(4, 4);
    sBoard.createChessPiece(White, Rook, 3, 2);
    sBoard.createChessPiece(Black, Bishop, 1, 3);
    sBoard.createChessPiece(Black, Rook, 1, 1);
    sBoard.createChessPiece(White, Rook, 2, 3);
    sBoard.createChessPiece(Black, King, 0, 0);
    sBoard.createChessPiece(White, King, 3, 0);

    std::cout << sBoard.movePiece(3, 0, 2, 0) << std::endl;
    std::cout << "eirjgn\n";
    std::cout << sBoard.isValidMove(0, 0, 1, 0) << std::endl;
    return;

/*
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(3, 0, 2, 0) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(1, 3, 0, 2) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(2, 3, 1, 3) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(1, 1, 0, 1) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(1, 2, 0, 3) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(2, 0, 3, 0) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(0, 1, 2, 1) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(3, 2, 0, 2) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(2, 1, 0, 1) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(0, 1, 3, 2) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(1, 3, 1, 0) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(0, 0, 1, 0) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(0, 2, 3, 2) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(1, 0, 1, 1) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(2, 0, 3, 3) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

        std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(3, 2, 3, 1) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(1, 1, 0, 2) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(3, 1, 3, 2) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(0, 2, 0, 3) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

        std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(1, 3, 2, 3) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(3, 2, 2, 2) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(0, 3, 1, 3) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(3, 0, 2, 0) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(0, 1, 0, 2) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(2, 3, 1, 0) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(2, 0, 3, 1) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

        std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(1, 3, 0, 3) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(2, 2, 0, 2) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(0, 3, 1, 3) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(3, 1, 1, 2) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

        std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(0, 2, 0, 1) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(1, 3, 1, 2) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(0, 1, 2, 1) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(1, 2, 0, 2) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(2, 0, 0, 0) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(3, 1, 2, 0) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(0, 2, 1, 2) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(2, 0, 3, 0) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(1, 2, 0, 2) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(0, 1, 1, 1) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(2, 1, 2, 3) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

        std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(0, 2, 0, 1) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(2, 3, 2, 0) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(0, 1, 1, 2) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(1, 2, 0, 0) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(2, 0, 2, 2) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(1, 2, 1, 3) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(2, 2, 2, 0) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(1, 2, 0, 2) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

        std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(2, 2, 2, 2) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(2, 0, 2, 1) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(0, 2, 0, 3) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(3, 0, 2, 0) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(0, 3, 0, 2) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(3, 0, 2, 2) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(2, 1, 1, 1) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(0, 2, 0, 3) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(1, 1, 0, 1) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(0, 3, 1, 3) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(1, 0, 3, 3) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(0, 1, 2, 1) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(1, 3, 1, 2) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(2, 1, 1, 1) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard);

    std::cout << std::endl;
    std::cout << "Move" << (sBoard.movePiece(1, 2, 0, 2) ? "Succeeded" : "Failed") << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
    test_scanValidity(sBoard); */
}

void test_part3_4x4_2() {
    Student::ChessBoard sBoard(4, 4);
    sBoard.createChessPiece(Black, Rook, 3, 3);
    sBoard.createChessPiece(Black, Bishop, 0, 0);
    sBoard.createChessPiece(Black, Bishop, 3, 0);
    sBoard.createChessPiece(White, Rook, 2, 3);
    sBoard.createChessPiece(Black, King, 3, 1);
    sBoard.createChessPiece(White, King, 1, 0);

    std::cout << sBoard.displayBoard().str() << std::endl;
    sBoard.movePiece(2, 3, 2, 0);

    sBoard.movePiece(3, 3, 0, 3);

    sBoard.movePiece(2, 0, 2, 2);

    sBoard.movePiece(0, 0, 1, 1);

    sBoard.movePiece(2, 1, 2, 1);


    sBoard.movePiece(2, 2, 3, 2);

    sBoard.movePiece(3, 1, 3, 2);

    sBoard.movePiece(1, 0, 1, 1);

    sBoard.movePiece(3, 2, 2, 3);

    sBoard.movePiece(3, 3, 2, 1);


    sBoard.movePiece(1, 1, 1, 0);

    sBoard.movePiece(0, 3, 0, 2);

    sBoard.movePiece(1, 0, 2, 0);

    sBoard.movePiece(3, 0, 0, 3);

    sBoard.movePiece(2, 1, 3, 0);


    sBoard.movePiece(2, 0, 3, 1);

    sBoard.movePiece(0, 3, 1, 2);

    sBoard.movePiece(3, 1, 2, 0);

    sBoard.movePiece(2, 3, 3, 3);

    sBoard.movePiece(3, 0, 1, 2);


    sBoard.movePiece(2, 0, 1, 0);

    sBoard.movePiece(1, 2, 2, 1);

    sBoard.movePiece(1, 0, 2, 1);

    sBoard.movePiece(0, 2, 3, 2);

    sBoard.movePiece(1, 2, 0, 2);


    sBoard.movePiece(2, 1, 2, 0);

    sBoard.movePiece(3, 2, 1, 2);
    std::cout << sBoard.displayBoard().str() << std::endl;
    sBoard.movePiece(2, 0, 3, 1);
    std::cout << sBoard.displayBoard().str() << std::endl;
    sBoard.movePiece(1, 2, 2, 2);
    std::cout << sBoard.displayBoard().str() << std::endl;
    sBoard.movePiece(0, 0, 3, 2);

    std::cout << sBoard.displayBoard().str() << std::endl;
    sBoard.movePiece(3, 1, 3, 0); // start here
    std::cout << sBoard.displayBoard().str() << std::endl;
    sBoard.movePiece(3, 3, 3, 2);

    std::cout << sBoard.displayBoard().str() << std::endl;

    sBoard.movePiece(1, 2, 1, 0);

    std::cout << sBoard.displayBoard().str() << std::endl;




    sBoard.movePiece(2, 3, 3, 1);


    std::cout << sBoard.displayBoard().str() << std::endl;



    sBoard.movePiece(0, 1, 3, 3);


    std::cout << sBoard.displayBoard().str() << std::endl;



    sBoard.movePiece(0, 2, 0, 3);



    std::cout << sBoard.displayBoard().str() << std::endl;


    sBoard.movePiece(0, 1, 3, 2);



    std::cout << sBoard.displayBoard().str() << std::endl;

    std::cout << sBoard.isValidMove(2, 2, 2, 0) << std::endl;
    std::cout << sBoard.movePiece(2, 2, 2, 0) << std::endl;
    std::cout << sBoard.displayBoard().str() << std::endl;
}

void test_part3_4x4_2_case() {
    Student::ChessBoard sBoard(4, 4);
    sBoard.createChessPiece(Black, Rook, 3, 3);
    sBoard.createChessPiece(Black, Bishop, 0, 0);
    sBoard.createChessPiece(Black, Bishop, 3, 0);
    sBoard.createChessPiece(White, Rook, 2, 3);
    sBoard.createChessPiece(Black, King, 3, 1);
    sBoard.createChessPiece(White, King, 1, 0);

    std::cout << sBoard.displayBoard().str() << std::endl;
}

void test_part3_4x4_6() {
    Student::ChessBoard sBoard(4, 4);
    sBoard.createChessPiece(White, Pawn, 1, 1);
    sBoard.createChessPiece(Black, Bishop, 1, 1);
    sBoard.createChessPiece(Black, Rook, 3, 0);
    sBoard.createChessPiece(White, Bishop, 2, 0);
    sBoard.createChessPiece(Black, King, 0, 0);
    sBoard.createChessPiece(White, King, 0, 3);

    std::cout << sBoard.displayBoard().str() << std::endl;

    sBoard.movePiece(0, 3, 1, 3);
    std::cout << sBoard.displayBoard().str() << std::endl;

    sBoard.movePiece(1, 1, 2, 0);
    std::cout << sBoard.displayBoard().str() << std::endl;

    sBoard.movePiece(1, 3, 0, 3);
    std::cout << sBoard.displayBoard().str() << std::endl;

    sBoard.movePiece(2, 0, 0, 2);
    std::cout << sBoard.displayBoard().str() << std::endl;

    sBoard.movePiece(0, 1, 0, 0);
    std::cout << sBoard.displayBoard().str() << std::endl;


    sBoard.movePiece(0, 3, 1, 2);
    std::cout << sBoard.displayBoard().str() << std::endl;

    sBoard.movePiece(0, 2, 2, 0);
    std::cout << sBoard.displayBoard().str() << std::endl;

    sBoard.movePiece(1, 2, 2, 2);
    std::cout << sBoard.displayBoard().str() << std::endl;

    sBoard.movePiece(0, 0, 1, 0);
    std::cout << sBoard.displayBoard().str() << std::endl;

    sBoard.movePiece(0, 1, 3, 2);
    std::cout << sBoard.displayBoard().str() << std::endl;


    sBoard.movePiece(2, 2, 1, 2);
    std::cout << sBoard.displayBoard().str() << std::endl;

    sBoard.movePiece(3, 0, 3, 1);
    std::cout << sBoard.displayBoard().str() << std::endl;

    sBoard.movePiece(1, 2, 1, 3);
    std::cout << sBoard.displayBoard().str() << std::endl;

    sBoard.movePiece(2, 0, 1, 1);
    //error here
    std::cout << sBoard.displayBoard().str() << std::endl;
    sBoard.movePiece(1, 0, 2, 1);
    std::cout << sBoard.displayBoard().str() << std::endl;

    sBoard.movePiece(1, 3, 1, 2);

    sBoard.movePiece(3, 1, 3, 2);

    sBoard.movePiece(1, 2, 0, 3);

    sBoard.movePiece(1, 0, 2, 0);

    sBoard.movePiece(2, 0, 0, 1);


    sBoard.movePiece(0, 3, 1, 3);

    sBoard.movePiece(3, 2, 3, 1);

    sBoard.movePiece(1, 3, 0, 3);

    sBoard.movePiece(3, 1, 3, 0);

    sBoard.movePiece(0, 0, 2, 2);


    sBoard.movePiece(0, 3, 1, 3);

    sBoard.movePiece(3, 0, 3, 2);

    sBoard.movePiece(1, 3, 2, 3);

    sBoard.movePiece(3, 2, 3, 0);

    sBoard.movePiece(2, 0, 3, 2);


    sBoard.movePiece(2, 3, 1, 2);

    sBoard.movePiece(3, 0, 3, 3);

    sBoard.movePiece(1, 2, 0, 1);

    sBoard.movePiece(1, 1, 0, 0);

    sBoard.movePiece(1, 3, 0, 1);


    sBoard.movePiece(0, 1, 1, 2);

    sBoard.movePiece(3, 3, 0, 3);

    sBoard.movePiece(1, 2, 0, 3);

    sBoard.movePiece(2, 0, 1, 1);

    sBoard.movePiece(2, 0, 2, 1);


    sBoard.movePiece(0, 3, 1, 3);

    sBoard.movePiece(1, 1, 2, 0);

    sBoard.movePiece(1, 3, 0, 3);

    sBoard.movePiece(2, 0, 1, 0);

    sBoard.movePiece(0, 1, 1, 1);


    sBoard.movePiece(0, 3, 1, 3);

    sBoard.movePiece(1, 0, 2, 0);

    sBoard.movePiece(1, 3, 0, 2);

    sBoard.movePiece(2, 0, 1, 0);

    sBoard.movePiece(2, 0, 2, 2);


    sBoard.movePiece(0, 2, 1, 3);

    sBoard.movePiece(0, 0, 3, 3);

    sBoard.movePiece(1, 3, 1, 2);

    sBoard.movePiece(3, 3, 2, 2);

    sBoard.movePiece(0, 3, 2, 3);


    sBoard.movePiece(1, 2, 2, 3);

    sBoard.movePiece(1, 0, 2, 1);



    sBoard.movePiece(2, 1, 0, 3);
}

void test_part3_4x4_8() {
    Student::ChessBoard sBoard(8, 8);
    sBoard.createChessPiece(White, Rook, 4, 5);
    sBoard.createChessPiece(Black, Rook, 5, 6);
    sBoard.createChessPiece(White, Pawn, 1, 5);
    sBoard.createChessPiece(Black, Bishop, 7, 6);
    sBoard.createChessPiece(White, Pawn, 5, 5);
    sBoard.createChessPiece(White, Rook, 3, 6);
    sBoard.createChessPiece(Black, Bishop, 7, 1);
    sBoard.createChessPiece(Black, Bishop, 0, 2);
    sBoard.createChessPiece(Black, Rook, 7, 6);
    sBoard.createChessPiece(White, Pawn, 4, 2);
    sBoard.createChessPiece(White, Rook, 0, 0);
    sBoard.createChessPiece(Black, Bishop, 7, 5);
    sBoard.createChessPiece(White, Rook, 2, 1);
    sBoard.createChessPiece(White, Rook, 0, 7);
    sBoard.createChessPiece(White, Bishop, 0, 4);
    sBoard.createChessPiece(White, Bishop, 6, 7);
    sBoard.createChessPiece(Black, King, 1, 2);
    sBoard.createChessPiece(White, King, 0, 1);
    std::cout << sBoard.displayBoard().str() << std::endl;

    sBoard.movePiece(0, 1, 1, 2);
    std::cout << sBoard.displayBoard().str() << std::endl;
    sBoard.movePiece(0, 2, 2, 0);
    sBoard.movePiece(0, 7, 0, 6);
    sBoard.movePiece(5, 4, 0, 6);
    sBoard.movePiece(5, 6, 5, 5);
    sBoard.movePiece(0, 0, 1, 0);
    sBoard.movePiece(7, 5, 4, 2);
    sBoard.movePiece(3, 7, 4, 7);


    sBoard.movePiece(0, 6, 2, 6);
    sBoard.movePiece(7, 1, 6, 2);
    sBoard.movePiece(0, 4, 2, 2);
    sBoard.movePiece(3, 1, 1, 0);
    sBoard.movePiece(5, 5, 4, 5);
    sBoard.movePiece(2, 2, 3, 1);
    sBoard.movePiece(4, 2, 1, 5);
    sBoard.movePiece(5, 5, 1, 2);


    sBoard.movePiece(1, 2, 2, 3);
    sBoard.movePiece(2, 0, 0, 2);
    sBoard.movePiece(3, 1, 6, 4);
    sBoard.movePiece(0, 5, 7, 7);
    sBoard.movePiece(7, 6, 7, 3);
    sBoard.movePiece(3, 6, 3, 3);
    sBoard.movePiece(4, 5, 4, 1);
    sBoard.movePiece(7, 5, 6, 6);


    sBoard.movePiece(2, 6, 2, 7);
    sBoard.movePiece(4, 1, 5, 1);
    sBoard.movePiece(1, 0, 0, 0);
    sBoard.movePiece(3, 3, 3, 5);
    sBoard.movePiece(0, 2, 1, 1);
    sBoard.movePiece(2, 1, 2, 0);
    sBoard.movePiece(1, 5, 3, 3);
    sBoard.movePiece(1, 0, 2, 6);


    sBoard.movePiece(2, 0, 2, 1);
    sBoard.movePiece(7, 3, 7, 2);
    sBoard.movePiece(2, 7, 5, 7);
    sBoard.movePiece(1, 3, 0, 4);
    sBoard.movePiece(7, 2, 7, 1);
    sBoard.movePiece(6, 4, 3, 1);
    sBoard.movePiece(6, 2, 7, 3);
    sBoard.movePiece(6, 3, 1, 4);


    sBoard.movePiece(0, 0, 6, 0);
    sBoard.movePiece(3, 3, 4, 4);
    sBoard.movePiece(6, 0, 2, 0);
    sBoard.movePiece(7, 0, 3, 5);
    sBoard.movePiece(4, 4, 6, 2);
    sBoard.movePiece(2, 3, 3, 4);
    sBoard.movePiece(1, 1, 7, 7);
    sBoard.movePiece(1, 2, 0, 0);


    sBoard.movePiece(3, 1, 4, 0);
    sBoard.movePiece(5, 1, 5, 4);
    sBoard.movePiece(3, 4, 4, 3);
    sBoard.movePiece(6, 2, 6, 0);
    sBoard.movePiece(5, 4, 5, 2);
    sBoard.movePiece(5, 7, 5, 2);
    sBoard.movePiece(7, 1, 5, 1);
    sBoard.movePiece(1, 1, 4, 5);


    sBoard.movePiece(2, 1, 5, 1);
    sBoard.movePiece(7, 7, 1, 1);
    sBoard.movePiece(4, 0, 1, 3);
    sBoard.movePiece(4, 7, 5, 3);
    sBoard.movePiece(6, 2, 5, 1);
    sBoard.movePiece(2, 0, 2, 1);
    sBoard.movePiece(1, 1, 4, 4);
    sBoard.movePiece(4, 2, 6, 6);



}

int main()
{
    //test_part1_4x4_1();
    //test_part1_4x4_2();
    //test_part1_4x4_3();
    //test_part1_6x6_2();
    //test_part1_8x8_10();
    //test_part1_8x8_1();
    //test_part1_4x4_5();
    //test_part2_4x4_1();
    //test_part3_4x4_1();
    //test_part3_4x4_2();
    //test_part3_4x4_6();
    test_part3_4x4_8();
    return EXIT_SUCCESS;
}
