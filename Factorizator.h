//
// Created by danonofficial on 04.12.17.
//

#ifndef LAB4_5_FACTORIZATOR_H
#define LAB4_5_FACTORIZATOR_H

#include <string>
class Factorizator {
public:
    Factorizator() = default;
    Factorizator(const uint64_t &num);
    ~Factorizator();
    std::string getFactorization() const;
    void generateFactorization();
    void setNum(uint64_t);

private:
    uint64_t num;
    std::string factorization;
};


#endif //LAB4_5_FACTORIZATOR_H
