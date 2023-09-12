#pragma once

#include <vector>
#include <cstdlib> // for rand and abs function
#include <iostream>

//template <typename T>
float vector1DMultiply(std::vector<float> v1, std::vector<float> v2) {
    float y = v1[0] * v2[0] + v1[1] * v2[1];
    
    for(int i = 2; i < v1.size(); i++) y += v1[i] * v2[i];

    return y;
}

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


    /*
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
    static matrix GaussJordanElimination(matrix m) {
        return m;
    }
    static matrix GaussJordanEliminationReduced(matrix m) {
        matrix intermediate = GaussJordanElimination(m);
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
        matrix::copy(m, intermediate);
        
        // Now reduce to row echelon form
        intermediate = GaussJordanElimination(intermediate);

        // Now copy intermediate over in I and B, then check if I is an identity matrix and if so, return B
        matrix I(m.getRow(), m.getCol());
        matrix B(m.getRow(), m.getCol());
        matrix::copy(intermediate, I);
        matrix::copy(intermediate, B, m.getCol);

        if (identity(I)) return B;
        else return matrix(0, 0);
    }
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
    inline void print(){
        // Update the stroed longest character length
        if(changed) updateLongestCharacter();

        int totalLineLength = (col - 1) * (longestCharacter + 1) + longestCharacter + 2;
        for (int i = 0; i < totalLineLength; i++) std::cout << "-";
        std::cout << " (" << row << ", " << col << ")" << std::endl;

        for(int j = 0; j < row; j++) {
            std::cout << "|";
            std::string printValue = std::to_string(get(j, 0));
            int spaces = (longestCharacter - printValue.size()) / 2;
            for(int i = 0; i < spaces; i++) std::cout << " ";

            
            for (int i = 0; i < col - 1; i++) {
                std::string printValue = std::to_string(get(j, i));
                spaces = (longestCharacter - printValue.size()) /2;
                for(int k = 0; k < spaces; k++) std::cout << " ";
                std::cout << printValue;
                for(int k = 0; k < spaces; k++) std::cout << " ";
            }

            std::cout << get(j, col - 1); 
            std::cout << "|" << std::endl;
        }

        for (int i = 0; i < totalLineLength; i++) std::cout << "-";
        std::cout << std::endl;
    }
    inline void randomize(){
        for(int j = 0; j < row; j++){
            for(int i = 0; i < col; i++){
                set(j, i, rand());
            }
        }
    }
    inline void randomize(int lower, int upper, float divide){
        for(int j = 0; j < row; j++){
            for(int i = 0; i < col; i++){
                set(j, i, (rand() % (upper - lower + 1) + lower) / divide);
            }
        }
    }
    static void copy(matrix m1, matrix m2, int offsetX = 0, int offsetY = 0){
        for(int j = offsetY; j < m1.getRow(); j++){
            for(int i = offsetX; i < m1.getCol(); i++){
                m2.set(j, i, m1.get(j, i));
            }
        }
    }

    inline int getRow() { return row; }
    inline int getCol() { return col; }
    inline float get(int row, int col) { return data[row][col]; }
    inline void set(int row, int col, float value) { data[row][col] = value; }
private:
    void updateLongestCharacter(){
        int highestWidth = 0;
        for(int j = 0; j < row; j++) { 
            for(int i = 0; i < col; i++){
                std::string cha = std::to_string(get(j, i));
                int width = cha.size();
                if (width > highestWidth) highestWidth = width;
            }
        }
        if ((highestWidth + 2) != longestCharacter) {
            longestCharacter = (highestWidth + 2);
            longestCharacterHalf = longestCharacter / 2;
        }
    }
    

    std::vector<std::vector<float>> data;
    int row, col;

    bool changed;
    int longestCharacter, longestCharacterHalf;
};