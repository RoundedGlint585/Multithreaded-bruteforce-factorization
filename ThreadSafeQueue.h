//
// Created by danonofficial on 04.12.17.
//

#ifndef LAB4_5_THREADSAFEQUEUE_H
#define LAB4_5_THREADSAFEQUEUE_H


#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <iostream>

template<typename  T> //first is key, second is element
class ThreadSafeQueue{
public:
    size_t size();
    T pop();
    T popKey() = delete;
    void push(const T& data);
    bool empty() const;
private:
    std::mutex mutex_;
    std::queue<T> queue_;
    std::condition_variable cond_;

};

template<typename T>
size_t ThreadSafeQueue<T>::size() {
    std::unique_lock<std::mutex> lock(mutex_);
    return queue_.size();
}

template<typename T>
T ThreadSafeQueue<T>::pop() {
    std::unique_lock<std::mutex> lock(mutex_);
    while(queue_.empty()){
        cond_.wait(lock);
    }
    T res = queue_.front();
    queue_.pop();
    return res;
}

template<typename T>
void ThreadSafeQueue<T>::push(const T &data) {
    std::unique_lock<std::mutex> lock(mutex_);

    queue_.push(data);
    //mutex_.unlock();
    cond_.notify_one();
}

template<typename T>
bool ThreadSafeQueue<T>::empty() const {
    return queue_.size() == 0;
}

#endif //LAB4_5_THREADSAFEQUEUE_H
