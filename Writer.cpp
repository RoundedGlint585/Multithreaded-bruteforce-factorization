//
// Created by danonofficial on 04.12.17.
//

#include <iostream>
#include "Writer.h"

Writer &Writer::Instance() {
        static Writer myInstance;
        return myInstance;
}

Writer::Writer() {
    isEnd = false;
    file = std::ofstream();
    file.open("output.txt");

    writing = std::thread([&](){

        file.flush();
        while(!isEnd){
            std::string res = order_.pop();
            file << res;
        }
        while(!order_.empty()){
            std::string res =  order_.pop();
            file <<res;
        }
    });
}
Writer::~Writer() {
    isEnd = true;
    this->push("");
    writing.join();
    file.close();
}

void Writer::push(const std::string& data) {
    this->order_.push(data);
}

void Writer::open(const std::string &fileName) {
    file.close();
    file.open(fileName);
}
