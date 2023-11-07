
#include "RookPiece.hh"
#include "ChessBoard.hh"
using Student::ChessBoard;

namespace Student {

    RookPiece::RookPiece(ChessBoard &board, Color color, int row, int column): ChessPiece(board, color, row, column) {
        _type = Rook;
    }

    bool RookPiece::canMoveToLocation(int toRow, int toColumn) {
        // if move-to values are not on horizontal or vertical return false
        int current_row = getRow();
        int current_col = getColumn();
 
        if (toRow != current_row && toColumn != current_col) { // makes sure it stays on the same row or column
            return false;
        } 

/*         if (toRow == current_row && toColumn == current_col) {
            return false;
        }  */

        if (toRow == current_row) {
            int direction = (toColumn < current_col) ? -1 : 1; // determines which direction rook is moving (up/down)

            for (int i = current_col + direction; i != toColumn; i += direction) { // iterates along the path of rook
                if (_board.getPiece(current_row,i) != nullptr) {          // makes sure theres no piece on the spaces
                    return false;
                }
            }
        }
        else if (toColumn == current_col) {
            int direction = (toRow < current_row) ? -1 : 1; // determines which direction rook is moving (left/right)

            for (int i = current_row + direction; i != toRow; i += direction) { // iterates along the path of rook
                if (_board.getPiece(i,current_col) != nullptr) {          // makes sure theres no piece on the spaces
                    return false;
                }
            }
        }

        return true;
        //chatgpt this: if I have a rook class function that takes in 2 variables relating to where it will move on a 2d matrix how would i check if there was another piece in the way

    }

    const char* RookPiece::toString() {
        if ((*this).getColor() == White) {
            return "\u2656"; // return white bishop
        }
        return "\u265C"; // return black bishop
    }

}