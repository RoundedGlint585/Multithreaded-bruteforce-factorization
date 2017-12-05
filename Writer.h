//
// Created by danonofficial on 04.12.17.
//

#ifndef LAB4_5_WRITER_H
#define LAB4_5_WRITER_H

#include "ThreadSafeQueue.h"
#include <condition_variable>
#include <thread>
#include <fstream>
#include <atomic>
class Writer {
public:
    static Writer & Instance();
    Writer(Writer const&) = delete;             // Copy construct
    Writer(Writer&&) = delete;                  // Move construct
    Writer& operator=(Writer const&) = delete;  // Copy assign
    Writer& operator=(Writer &&) = delete;
    void push(const std::string&);
    void open(const std::string&);
protected:
    Writer();
    ~Writer();
    ThreadSafeQueue<std::string> order_;
    std::thread writing;
    std::ofstream file;
    std::atomic_bool isEnd;
    std::atomic_int queue;
};

#endif //LAB4_5_WRITER_H
