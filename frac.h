#include <iostream>
#include <vector>
#include <cmath>

std::vector <int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59};

/*
2.5 = 5 / 2
1.5 = 3 / 2

1.333 = 4 / 3
250 / 100

*/   
class frac {
public:
    frac(int v, int b) 
        : value(v),
          base(b){
    }
    frac(int v) 
        : value(v),
          base(1){}
    frac(float v) {
            float n = v * 10;
            int p = 1;
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
        bool done;
        for(int i = primes.size() - 1; i > -1; i--) {
            if (getValue() % primes[i] == 0 && getBase() % primes[i] == 0){
                setValue(getValue() / primes[i]);
                setBase(primes[i]);
                done = true;
                break;
            }
        }
        if (!done){
            int i = getValue() - 1;

            int highestPrime = primes[primes.size() - 1];
            while ((getValue() % i != 0 || getBase() % i != 0) && i > highestPrime) i--;
            
            setValue(getValue() / i);
            setBase(getBase() / i);
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
private:
    int value, base;
};