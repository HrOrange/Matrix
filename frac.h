#include <iostream>
#include <vector>
#include <cmath>

// needs to add 1
std::vector <int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59};

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
        if (getBase() > 1){
            bool done;
            for(int i = primes.size() - 1; i > -1; i--) {
                if (getValue() % primes[i] == 0 && getBase() % primes[i] == 0){
                    setValue(getValue() / (getBase() / primes[i]));
                    setBase(primes[i]);
                    done = true;
                    break;
                }
            }
            if (!done){
                int i = getValue() - 1;

                int highestPrime = primes[primes.size() - 1];
                while ((getValue() % i != 0 || getBase() % i != 0) && i > highestPrime) i--;
                
                setValue(getValue() / (getBase() / i));
                setBase(getBase() / i);
                std::cout << "something found" << std::endl;
            }
        }
    }
    static frac reduce(frac f) {
        if (f.getBase() == 1) return f;
        else {
            int newValue, newBase;
            bool done;
            for(int i = primes.size() - 1; i > -1; i--) {
                newValue = f.getValue() / (f.getBase() / primes[i]);
                if (f.getValue() % primes[i] == 0 && newValue % primes[i] == 0){
                    newBase = primes[i];
                    done = true;
                    break;
                }
            }
            if (!done){
                int i = f.getValue() - 1;

                int highestPrime = primes[primes.size() - 1];
                while ((newValue % i != 0 || f.getBase() % i != 0) && i > highestPrime) {
                    i--;
                }
                
                newValue = f.getValue() / (f.getBase() / i);
                newBase = f.getBase() / i;
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