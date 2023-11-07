#include "BishopPiece.hh"
#include "ChessBoard.hh"
using Student::ChessBoard;

namespace Student{
                                                                                // Calls the ChessPiece constructor
    BishopPiece::BishopPiece(ChessBoard &board, Color color, int row, int column): ChessPiece(board, color, row, column) {
        _type = Bishop;
    }

    bool BishopPiece::canMoveToLocation(int toRow, int toColumn) {
        int current_row = getRow();
        int current_col = getColumn();

        if (abs(toRow - current_row) != abs(toColumn - current_col)) { // if the change is not the same then its not diagonal to the bishop
            return false;                                           
        }

        int direction_row = (toRow < current_row) ? -1 : 1;     // determines whether bishop moves left or right
        int direction_col = (toColumn < current_col) ? -1 : 1;  // determines whether the bishop moves up or down

        int check_row = current_row + direction_row; // set checker indexes to start location
        int check_col = current_col + direction_col;

        while (check_row != toRow && check_col != toColumn) {

            if (_board.getPiece(check_row, check_col)) { // checks if there is a piece in the way
                return false;
            }            
            check_row += (direction_row); // decrements/increments by 1 as necessary
            check_col += (direction_col);
        }
        return true;
        /*        old code that didn't work
        int current_row = getRow();
        int current_col = getColumn();
                
        if (abs(toRow - current_row) != abs(toColumn - current_col)) { // if the change is not the same then its not diagonal to the bishop
            return false;                                          
        }

        int direction_row = (toRow < current_row) ? -1 : 1;     // determines whether bishop moves left or right
        int direction_col = (toColumn < current_col) ? -1 : 1;  // determines whether the bishop moves up or down

        int check_row = current_row + (1 * direction_row);
        int check_col = current_col + (1 * direction_col);

        for (int i = 2; check_row != toRow && check_col != toColumn && check_row < (_board.getNumRows() - 1) && check_col < (_board.getNumCols() - 1) && check_row > 0 && check_col > 0; i++) { // increment i so long as check row and col are within the bounds of the board
           
            if (_board.getPiece(check_row,check_col) != nullptr && check_row != toRow && check_col != toColumn) { // checks if there is a piece in the way and its not the place we are moving to 
                return false;
            }
            check_row += (i * direction_row);
            check_col += (i * direction_col);
        }

        return true;

        // Old check if space is valid
        if (toRow + toColumn == getRow() + getColumn() || toRow - toColumn == getRow() - getColumn()) {
            return true;
        }
        return false;
        */
    }

    const char* BishopPiece::toString() {
        if ((*this).getColor() == White) {
            return "\u2657"; // return white bishop
        }
        return "\u265D"; // return black bishop
    }

}