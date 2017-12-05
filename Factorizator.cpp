//
// Created by danonofficial on 04.12.17.
//

#include <iostream>
#include "Factorizator.h"

std::string Factorizator::getFactorization() const {
    return factorization;
}

void Factorizator::generateFactorization() {
    int count = 0;
    int i;
    factorization += std::to_string(num) + "=";
    uint64_t num = this->num;
    for(i =2 ; i *i<=  num; i++){

        while(num %i == 0) {
            count++;
            num /=i;
        }
        if(count != 0){
            factorization += std::to_string(i) + "^" + std::to_string(count) + "*";
        }
    }
    if(num != 1){
        factorization +=std::to_string(num)+ "^" + "1";
    }else {
        factorization.erase(factorization.end() - 1, factorization.end());
    }
}

void Factorizator::setNum(uint64_t num) {
    this->num =  num;
    generateFactorization();
}

Factorizator::Factorizator(const uint64_t &num):num(num) {
    generateFactorization();
}

Factorizator::~Factorizator() {
    factorization.clear();
}
