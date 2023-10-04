#include <iostream>
#include <vector>
#include <cmath>

// some small functions and constants
std::vector <int> primes = {1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59};
int min(int x, int y) { if (x <= y) return x; else return y; }

/*
2.5 = 5 / 2
1.5 = 3 / 2

1.333 = 4 / 3
250 / 100

*/   
class frac {
public:
    frac () { }
    frac(int v, int b) 
        : value(v),
          base(b){
    }
    frac(int v) 
        : value(v) {}
    frac(float v) {
            float n = v;
            int p = 0;
            while (n - std::floor(n) > 0){
                n *= 10;
                p++;
            }
            base = std::pow(10, p);
            value = n;
        }

    static frac add(frac f1, frac f2) {
        if (f1.getBase() == f2.getBase()) return frac(f1.getValue() + f2.getValue(), f1.getBase());
        return frac(f1.getValue() * f2.getBase() + f2.getValue() * f1.getBase(), f1.getBase() * f2.getBase());
    }
    static frac sub(frac f1, frac f2) {
        if (f1.getBase() == f2.getBase()) return frac(f1.getValue() - f2.getValue(), f1.getBase());
        return frac(f1.getValue() * f2.getBase() - f2.getValue() * f1.getBase(), f1.getBase() * f2.getBase());
    }
    static frac multiply(frac f1, frac f2) {
        return frac(f1.getValue() * f2.getValue(), f1.getBase() * f2.getBase());
    }

    void reduce() {
        if (getBase() != 1) {
            bool done;
            for(int i = 0; i < primes.size(); i++) {
                if (getBase() % primes[i] == 0 && (getValue() % (getBase() / primes[i])) == 0){
                    setValue(getValue() / (getBase() / primes[i]));
                    setBase(primes[i]);
                    done = true;
                    break;
                }
            }
            if (!done){
                int i = min(getValue(), getBase()) - 1;
                while ((getBase() % i != 0 || getValue() % (getBase() / i) != 0) && i > 2) i--;
                
                if (i > 2){
                    setValue(getValue() / (getBase() / i));
                    setBase(getBase() / i);
                }
            }
        }
    }
    static frac reduce(frac f) {
        if (f.getBase() == 1) return f;
        else {
            int newValue, newBase;
            bool done;
            for(int i = 0; i < primes.size(); i++) {
                if (f.getBase() % primes[i] == 0 && (f.getValue() % (f.getBase() / primes[i])) == 0){
                    newValue = f.getValue() / (f.getBase() / primes[i]);
                    newBase = primes[i];
                    done = true;
                    break;
                }
            }
            if (!done){
                int i = f.getValue() - 1;

                while ((f.getBase() % i != 0 || f.getValue() % (f.getBase() / i) != 0) && i > 2) i--;
                
                if (i > 2){
                    newValue = f.getValue() / (f.getBase() / i);
                    newBase = f.getBase() / i;
                }
            }
            return frac(newValue, newBase);
        }
    }
    int inline getBase() { return base; }
    int inline getValue() { return value; }
    void inline setValue(int v) { value = v; }
    void inline setBase(int b) { base = b; }
    void inline print() { 
        if (getValue() % getBase() == 0) std::cout << getValue() / getBase(); 
        else std::cout << getValue() << " / " << getBase(); 
    }

    // Needed functions for matrix to work 
    static std::vector<std::vector<frac>> floatTofrac(std::vector<std::vector<float>> m) {
        std::vector<std::vector<frac>> returnVector = std::vector<std::vector<frac>>(m.size());

        for (int j = 0; j < m.size(); j++) {
            for(int i = 0; i < m[0].size(); i++) {
                returnVector[j].push_back(frac(m[j][i]));
            }
        }

        return returnVector;
    }
    static std::string toString (frac f) {
        return (std::to_string(f.getValue()) + "/" + std::to_string(f.getBase()));
    }
    static frac abs (frac f) {
        if (f.getValue() > 0) return frac(f.getValue(), f.getBase());
        else frac(-f.getValue(), f.getBase());
    }

    // Operator overloading
    operator std::string() { return (std::to_string(getValue()) + "/" + std::to_string(getBase())); }
    
    bool operator == (frac f) { return getValue() == f.getValue() && getBase() == f.getBase(); }
    bool operator != (frac f) { return getValue() != f.getValue() || getBase() != f.getBase(); }
    bool operator == (int value) { return ((getValue() / getBase()) == value); }
    bool operator != (int value) { return ((getValue() / getBase()) != value); }
    
    frac operator * (frac f) { return frac(getValue() * f.getValue(), getBase() * f.getBase()); }
    frac operator / (frac f) { return reduce(frac(getValue() * f.getBase(), getBase() * f.getValue())); }
    frac operator + (frac f) {
        if (getBase() == f.getBase()) return frac(getValue() + f.getValue(), getBase());
        else return frac(getValue() * f.getBase() + f.getValue() * getBase(), getBase() * f.getBase());}
    frac operator - (frac f) {
        if (getBase() == f.getBase()) return frac(getValue() - f.getValue(), getBase());
        else return frac(getValue() * f.getBase() - f.getValue() * getBase(), getBase() * f.getBase());}
    frac operator - () {
        return frac(-getValue(), getBase());
    }
    void operator *= (frac f) { setValue(getValue() * f.getValue()); setBase(getBase() * f.getBase()); }
    void operator /= (frac f) { setValue(getValue() / f.getValue()); setBase(getBase() / f.getBase()); }
    void operator += (frac f) {
        if (getBase() == f.getBase()) setValue(getValue() + f.getValue());
        else { 
            setValue(getValue() * f.getBase() + f.getValue() * getBase()); 
            setBase(getBase() * f.getBase());
        } }
    void operator -= (frac f) {
        if (getBase() == f.getBase()) setValue(getValue() - f.getValue());
        else { 
            setValue(getValue() * f.getBase() - f.getValue() * getBase()); 
            setBase(getBase() * f.getBase());
        } }
private:
    int value;
    int base = 1;
};