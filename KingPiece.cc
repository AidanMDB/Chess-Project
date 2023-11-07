
#include "KingPiece.hh"
#include "ChessBoard.hh"

using Student::ChessBoard;

namespace Student {

    KingPiece::KingPiece(ChessBoard &board, Color color, int row, int column): ChessPiece(board, color, row, column) {
        _type = King;
    }

    bool KingPiece::canMoveToLocation(int toRow, int toColumn) {
        // when king is under threat all other pieces must move to protect it
        // cannot move next to another king - is handled by check if its under threat
        // king cannot move into check
        // same color pieces cannot move which result in same color kings check

        // checks move is not further than 1 square in any direction
        if (toRow > getRow() + 1 || toColumn > getColumn() + 1 || toRow < getRow() - 1 || toColumn < getColumn() - 1) { 
            return false;
        }
        
        //_board.isKingSafe(getRow(), getColumn(), toRow, toColumn); // makes sure king is not moving into check
        return true;
    }

    const char* KingPiece::toString() {
        if ((*this).getColor() == White) {
            return "\u2654";
        }
        return "\u265A";
    }

}