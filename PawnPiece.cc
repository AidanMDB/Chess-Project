
#include "PawnPiece.hh"
#include "ChessBoard.hh"
using Student::ChessBoard;

namespace Student {
    
    PawnPiece::PawnPiece(ChessBoard &board, Color color, int row, int column): ChessPiece(board, color, row, column) {
        _type = Pawn;
    }

    bool PawnPiece::canMoveToLocation(int toRow, int toColumn) {
        // check if piece is in the way IDK how to do that b/c _board doesn't work
        int current_row = getRow();
        int current_col = getColumn();
        
        if (getColor() == Black) { // BLACK Pawns
            if ((toRow == current_row + 1) && (toColumn == current_col)) { // checks if black moves forward one place without changing column
                if (_board.getPiece(toRow, toColumn) != nullptr) {  // makes sure theres not a piece in the way
                    return false;
                }
                return true;
            }
            else if (current_row == 1 && toRow == (current_row + 2) && toColumn == current_col) { // checks if pawn is on starting space for 2 spaces
                if (_board.getPiece(toRow, toColumn) != nullptr) {  // makes sure theres not a piece in the way
                    return false;
                }
                else if (_board.getPiece(toRow - 1, toColumn) != nullptr) {  // makes sure theres not a piece in the way
                    return false;
                }
                return true;
            }
            else if (toRow == (current_row + 1) && (toColumn == (current_col - 1) || toColumn == (current_col + 1))) { //checks if pawn is moving diagonally
                if (_board.getPiece(toRow, toColumn) == nullptr) {                  // if it is make sure there is a piece there to take
                    return false;
                }
                return true;
            }
        }

        if (getColor() == White) { // WHITE Pawns
            if ((toRow == current_row - 1) && (toColumn == current_col)) { // checks if white moves forward one place without changing column
                if (_board.getPiece(toRow, toColumn) != nullptr) {  // makes sure theres not a piece in the way
                    return false;
                }
                return true;
            }
            else if (current_row == (_board.getNumRows() - 2) && toRow == (current_row - 2) && toColumn == current_col) { // checks if pawn is on starting space for 2 spaces
                if (_board.getPiece(toRow, toColumn) != nullptr) {  // makes sure theres not a piece in the way
                    return false;
                }
                else if (_board.getPiece(toRow + 1, toColumn) != nullptr) {  // makes sure theres not a piece in the way
                    return false;
                }
                return true;
            }
            else if (toRow == (current_row - 1) && (toColumn == (current_col - 1) || toColumn == (current_col + 1))) { //checks if pawn is moving diagonally
                if (_board.getPiece(toRow, toColumn) == nullptr) {                  // if it is make sure there is a piece there to take
                    return false;
                }
                return true;
            }
        }
        return false;
    }

    const char* PawnPiece::toString() {
        if ((*this).getColor() == White) {
            return "\u2659"; // return white bishop
        }
        return "\u265F"; // return black bishop
    }

}