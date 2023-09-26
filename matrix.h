#pragma once

#include <vector>
#include <cstdlib> // for rand and abs function
#include <iostream>

/* Examples
{
    { 1, 2, 3 },
    { 4, 5, 6 }
}
{
    { 1 },
    { 2 },
    { 3 }    
}
*/

class matrix {
public:

    // Constructors and destructors
    matrix (std::vector<std::vector<float>> m)
    : data(m),
      row(m.size()),
      col(m[0].size()) {
    }
    matrix (int rows, int columns) 
    : row(rows),
      col(columns) {
        data = std::vector<std::vector<float>>(rows);
        for (int i = 0; i < rows; i++) data[i] = std::vector<float>(columns);
    }
    matrix (int rows) 
    : row(rows),
      col(1) {
        for(int i = 0; i < rows; i++) data.push_back( { 0 } );
    }

    // Math operations
    static matrix multiply (matrix m1, matrix m2){
        if(m1.getCol() != m2.getRow()) {
            std::cout << "Sizes dont match for multiply." << std::endl;
            return matrix(0, 0);
        }
        matrix newMatrix(m1.getRow(), m2.getCol());
        
        for (int j = 0; j < newMatrix.getRow(); j++) {
            for (int i = 0; i < newMatrix.getCol(); i++) {
                float total = 0;
                for(int k = 0; k < m1.getCol(); k++) total += (m1.get(j, k) * m2.get(k, i));
                newMatrix.set(j, i, total);
            }
        }

        return newMatrix;
    }
    static matrix multiply (matrix m, float v){
        matrix newMatrix(m.getRow(), m.getCol());
        
        for (int j = 0; j < newMatrix.getRow(); j++) {
            for (int i = 0; i < newMatrix.getCol(); i++) {
                newMatrix.set(j, i, m.get(j, i) * v);
            }
        }

        return newMatrix;
    }
    static matrix add (matrix m1, matrix m2){
        if(m1.getRow() != m2.getRow() || m1.getCol() != m2.getCol())
        {
            std::cout << "Sizes dont match." << std::endl;
            return matrix(0, 0);
        }

        matrix res(m1.getRow(), m1.getCol());
        for(int j = 0; j < m1.getRow(); j++){
            for(int i = 0; i < m1.getCol(); i++){
                res.set(j, i, m1.get(j, i) + m2.get(j, i));
            }
        }
        return res;
    }  
    static matrix sub (matrix m1, matrix m2){
        if(m1.getRow() != m2.getRow() || m1.getCol() != m2.getCol())
        {
            std::cout << "Sizes dont match." << std::endl;
            return matrix(0, 0);
        }

        matrix res(m1.getRow(), m1.getCol());
        for(int j = 0; j < m1.getRow(); j++){
            for(int i = 0; i < m1.getCol(); i++){
                res.set(j, i, m1.get(j, i) - m2.get(j, i));
            }
        }
        return res;
    }    
    static matrix abs(matrix m){
        matrix res(m.getRow(), m.getCol());
        for(int j = 0; j < m.getRow(); j++){
            for(int i = 0; i < m.getCol(); i++){
                res.set(j, i, std::abs(m.get(j, i)));
            }
        }
        return res;
    }
    static matrix transpose(matrix m){
        matrix res(m.getCol(), m.getRow());
        
        for(int j = 0; j < res.getRow(); j++) {
            for (int i = 0; i < res.getCol(); i++) {
                res.set(j, i, m.get(i, j));
            }
        }

        return res;
    }
    static bool identity(matrix m){
        if(m.getRow() != m.getCol()) return false;

        bool res = true;
        for (int j = 0; j < m.getRow(); j++) {
            for(int i = 0; i < m.getCol(); i++){
                float value = m.get(j, i);
                if ((i != j && value != 0.0f) || (i == j && value != 1.0f)) {
                    res = false;
                    break;
                }
            }
            if (!res) break;
        }
        return res;
    }
    static inline matrix createIdentity(int size){
        matrix returnMatrix(size, size);
        for(int i = 0; i < size; i++) returnMatrix.set(i, i, 1.0f);
        return returnMatrix;
    }
    static inline float trace(matrix m) { 
        if (m.getRow() != m.getCol()) {
            std::cout << "Sizes dont match!!! The columns and rows should be the same, I think." << std::endl;
            return 0;
        }

        float total;
        for (int i = 0; i < m.getRow(); i++) total += m.get(i, i);
        return total;
    }
    static matrix GaussJordanElimination(matrix m, bool verbose = false) {
        matrix intermediate = copy(m);

        //Step 1
        int leadingOneCol = -1;
        int leadingOneRow = -1;
        bool done = false;
        while (done == false){
            // Step 1 (Find first column with non-zero value)
            float a;
            bool leadingOneFound = false;
            for (int i = leadingOneCol + 1; i < intermediate.getCol(); i++){
                for(int j = leadingOneRow + 1; j < intermediate.getRow(); j++){
                    
                    // Check if the row below the last leading one has a value  
                    if (intermediate.get(j, i) != 0.0f) {

                        // Step 2 (Switch this row with the first row)
                        if (j - leadingOneRow > 1) {
                        
                            intermediate.switchRows(leadingOneRow + 1, j);
                            std::cout << "SWITCH: " << (leadingOneRow + 1) << " " << j << std::endl;
                        } 
                        leadingOneFound = true;
                        leadingOneCol = i;
                        leadingOneRow++;
                        a = intermediate.get(leadingOneRow, leadingOneCol);
                        break;
                    }

                }
                if (leadingOneFound) break;
            }
            if (!leadingOneFound) {
                done = true;
                break;
            }

            // Step 3 (Divide the row by a)
            for(int i = leadingOneCol; i < intermediate.getCol(); i++) intermediate.set(leadingOneRow, i, intermediate.get(leadingOneRow, i) / a);
            //intermediate.print();

            // Step 4 (Add suitable multiplies of the first row to the ones belowto obtain zeros under the leading one)
            for (int j = leadingOneRow + 1; j < intermediate.getRow(); j++) {
                if(intermediate.get(j, leadingOneCol) != 0.0f){
                    float mult = -intermediate.get(j, leadingOneCol);
                    for (int i = 0; i < intermediate.getCol(); i++) intermediate.set(j, i, intermediate.get(j, i) + intermediate.get(leadingOneRow, i) * mult);
                }
            }
            if (verbose) {
                std::cout << "Leading one found at position: (" << leadingOneRow << ", " << leadingOneCol << ") with the value: " << a << std::endl;
                intermediate.print();
            }
        }

        return intermediate;
    }
    static matrix GaussJordanEliminationReduced(matrix m, bool verbose = false) {
        matrix intermediate = GaussJordanElimination(m, verbose);

        // First find the leading one from below.
        for(int j = intermediate.getRow() - 1; j > 0; j--) {
            for (int i = 0; i < intermediate.getCol(); i++) {

                // Leading one found
                if (intermediate.get(j, i) == 1.0f){

                    // check values above
                    for(int k = (j - 1); k > -1; k--) {

                        // If something other than 0.0 found.
                        if (intermediate.get(k, i) != 0.0f){
                            float mult = -intermediate.get(k, i);
                            //std::cout << "mult: " << mult << " x: " << i << " y: " << k << std::endl;
                            for (int x = 0; x < intermediate.getCol(); x++) intermediate.set(k, x, intermediate.get(k, x) + intermediate.get(j, x) * mult);
                        }
                    }
                    break; // Found the leading one, find the next one.
                }
            }
        }

        return intermediate;
    }
    static matrix inverse(matrix m){
        if (m.getRow() != m.getCol())
        {
            std::cout << "Not a square matrix!" << std::endl;
            return matrix(0, 0);
        }

        // Copy A over and create the identity matrix. (Left side A and right side I)
        matrix intermediate = matrix(m.getRow(), m.getCol() * 2);
        for(int i = 0; i < m.getRow(); i++) intermediate.set(i, m.getCol() + i, 1.0f);
        matrix::copy(m, &intermediate); // side effect does not seem to work here for some reason
        
        // Now reduce to row echelon form
        intermediate = GaussJordanEliminationReduced(intermediate);
        intermediate.print();

        // Now copy intermediate over in I and B, then check if I is an identity matrix and if so, return B
        matrix I(m.getRow(), m.getCol());
        matrix B(m.getRow(), m.getCol());
        matrix::copy(intermediate, &I);
        matrix::copy(intermediate, &B, m.getCol(), 0);
        
        if (identity(I)) return B;
        else return matrix(0, 0);
    }
    static float determinant2x2(matrix m) { return (m.get(0, 0) * m.get(1, 1)) - (m.get(0, 1) * m.get(1, 0)); }
    static matrix inverse2x2(matrix m) {
        float determinant = (m.get(0, 0) * m.get(1, 1)) - (m.get(0, 1) * m.get(1, 0));
        if (m.getCol() != 2 || m.getRow() != 2)
        {
            std::cout << "Matrix is not a 2x2." << std::endl;
            return matrix(0, 0);
        }
        else if (determinant == 0){
            std::cout << "Determinant is zero." << std::endl;
            return matrix(0, 0);
        }

        float inverseDeterminant = 1.0f / determinant;
        matrix res(2, 2);
        for(int j = 0; j < 2; j++) {
            for (int i = 0; i < 2; i++) {
                if (i != j) res.set(j, i, inverseDeterminant * -m.get(j, i));
                else res.set(j, i, inverseDeterminant * m.get(1 - j, 1 - i));
            }
        }
        return res;
    }
    static float determinant(matrix m){
        // For the case with a zero row.
        for (int j = 0; j < m.getRow(); j++) {
            bool notZeroFound = false;
            for(int i = 0; i < m.getCol(); i++) {
                if (m.get(j, i) != 0.0f) {
                    notZeroFound = true;
                    break;
                }
            }
            if (!notZeroFound) return 0.0f;
        }

        float total = 1.0f;
        matrix intermediate = copy(m);

        //Now we do Gauss Jordan Elimination
        //Step 1
        int leadingOneCol = -1;
        int leadingOneRow = -1;
        bool done = false;
        while (done == false){
            // Step 1 (Find first column with non-zero value)
            float a;
            bool leadingOneFound = false;
            for (int i = leadingOneCol + 1; i < intermediate.getCol(); i++){
                for(int j = leadingOneRow + 1; j < intermediate.getRow(); j++){
                    
                    // Check if the row below the last leading one has a value  
                    if (intermediate.get(j, i) != 0.0f) {

                        // Step 2 (Switch this row with the first row)
                        if (j - leadingOneRow > 1) {
                        
                            intermediate.switchRows(leadingOneRow + 1, j);
                            std::cout << "SWITCH: " << (leadingOneRow + 1) << " " << j << std::endl;
                        } 
                        leadingOneFound = true;
                        leadingOneCol = i;
                        leadingOneRow++;
                        a = intermediate.get(leadingOneRow, leadingOneCol);
                        break;
                    }

                }
                if (leadingOneFound) break;
            }
            if (!leadingOneFound) {
                done = true;
                break;
            } else {
                total *= a;
                std::cout << "- " << a << std::endl;
            }

            // Step 3 (Divide the row by a)
            for(int i = leadingOneCol; i < intermediate.getCol(); i++) intermediate.set(leadingOneRow, i, intermediate.get(leadingOneRow, i) / a);

            // Step 4 (Add suitable multiplies of the first row to the ones below to obtain zeros under the leading one)
            for (int j = leadingOneRow + 1; j < intermediate.getRow(); j++) {
                if(intermediate.get(j, leadingOneCol) != 0.0f){
                    float mult = -intermediate.get(j, leadingOneCol);
                    for (int i = 0; i < intermediate.getCol(); i++) {
                        intermediate.set(j, i, intermediate.get(j, i) + intermediate.get(leadingOneRow, i) * mult);
                    }
                }
            }
            intermediate.print();
        }

        return total;
    }

    // Normal operations for the class as a whole (not necessarily math functions)
    std::vector<int> getSize() { return { row, col }; }
    inline void printSize() { std::cout << "Rows: " << row << " Cols: " << col << std::endl; }
    inline void reset(float value = 0){
        for(int j = 0; j < row; j++) {
            for (int i = 0; i < col; i++) {
                set(j, i, value);
            }
        }
    }
    // Modes can be 1, 2, 3
    inline void print(int mode = 1){
        if (mode < 1 || mode > 3) {
            std::cout << "Mode is not between 1 and 3" << std::endl;
            return;
        }
        int longestCharacter = 0;
        for (int j = 0; j < row; j++) {
            for (int i = 0; i < col; i++) {
                std::string cha = std::to_string(get(j, i));
                int width = cha.size();
                if (width > longestCharacter) longestCharacter = width;
            }
        }

        
        // First line
        int totalLineLength;
        if (mode == 1 || mode == 3) totalLineLength = col * (longestCharacter + 3) + 1;
        else totalLineLength = col * (longestCharacter + 2) + 2;

        for (int i = 0; i < totalLineLength; i++) std::cout << "-";
        std::cout << " (" << row << ", " << col << ")" << std::endl;
        
        // All the lines in the middle
        for(int j = 0; j < row; j++) {
            std::cout << "|";
            
            // First to second last value in each row.
            for (int i = 0; i < col - 1; i++) {
                std::string printValue = std::to_string(get(j, i));

                int dif = longestCharacter - printValue.size();
                int extra = dif % 2;
                int spaces = dif / 2;

                for(int k = 0; k < (spaces + extra); k++) std::cout << " ";
                std::cout << " " << printValue << " ";
                for(int k = 0; k < spaces; k++) std::cout << " ";

                if (mode == 1 || mode == 3) std::cout << "|";
            }

            // last value in each row.
            std::string printValue = std::to_string(get(j, getCol() - 1));
            int dif = longestCharacter - printValue.size();
            int extra = dif % 2;
            int spaces = dif / 2;

            for(int k = 0; k < (spaces + extra); k++) std::cout << " ";
            std::cout << " " << printValue << " ";
            for(int k = 0; k < spaces; k++) std::cout << " ";
            std::cout << "|" << std::endl;

            if (mode == 2 || mode == 3){
                for (int i = 0; i < totalLineLength; i++) std::cout << "-";
                std::cout << std::endl;
            }
        }

        // The last line
        if (mode == 1){
            for (int i = 0; i < totalLineLength; i++) std::cout << "-";
            std::cout << std::endl;
        }
        
    }
    inline void randomize(){
        for(int j = 0; j < row; j++){
            for(int i = 0; i < col; i++){
                set(j, i, rand());
            }
        }
    }
    inline void randomize(int lower, int upper, float divide, int precision = 2){
        for(int j = 0; j < row; j++){
            for(int i = 0; i < col; i++){
                set(j, i, (rand() % (upper - lower + 1) + lower) / divide);
            }
        }
    }
    static void copy(matrix m1, matrix* m2, int offsetX = 0, int offsetY = 0){
        for(int j = 0; j < m1.getRow(); j++){
            for(int i = 0; i < m1.getCol(); i++){
                m2->set(j, i, m1.get(j + offsetY, i + offsetX));
            }
        }
    }
    static matrix copy(matrix m) {
        matrix m2 (m.getRow(), m.getCol());
        for(int j = 0; j < m.getRow(); j++){
            for(int i = 0; i < m.getCol(); i++){
                m2.set(j, i, m.get(j, i));
            }
        }
        return m2;
    }
    static matrix switchRows(matrix m, int row1, int row2){
        if (row1 > row2) {
            int variableTemp = row1;
            row1 = row2;
            row2 = variableTemp;
        } else if (row1 == row2) return m;

        matrix m2(m.getRow(), m.getCol());
        std::vector<float> temp(m.getCol());
        for(int i = 0; i < m.getCol(); i++) temp[i] = m.get(row1, i);
        
        for (int j = 0; j < m.getRow(); j++){
            if(j == row1){
                for(int i = 0; i < m.getCol(); i++) m2.set(j, i, m.get(row2, i));
            } else if (j == row2){
                for(int i = 0; i < m.getCol(); i++) m2.set(j, i, temp[i]);
            } else {
                for(int i = 0; i < m.getCol(); i++) m2.set(j, i, m.get(j, i));
            }
        }

        return m2;
    }
    void switchRows(int row1, int row2){
        if (row1 > row2) {
            int variableTemp = row1;
            row1 = row2;
            row2 = variableTemp;
        } else if (row1 == row2) return;

        std::vector<float> temp(getCol());
        for(int i = 0; i < getCol(); i++) temp[i] = get(row1, i);

        for(int i = 0; i < getCol(); i++) set(row1, i, get(row2, i));
        for(int i = 0; i < getCol(); i++) set(row2, i, temp[i]);
    }   

    inline int getRow() { return row; }
    inline int getCol() { return col; }
    inline float get(int row, int col) { return data[row][col]; }
    inline void set(int row, int col, float value) { data[row][col] = value; }
private:

    std::vector<std::vector<float>> data;
    int row, col;
};