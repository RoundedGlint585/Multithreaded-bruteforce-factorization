//
// Created by danonofficial on 04.12.17.
//

#ifndef LAB4_5_THREADSAFEPRIORITYQUEUE_H
#define LAB4_5_THREADSAFEPRIORITYQUEUE_H

#include <queue>
#include <string>
#include <mutex>
#include <condition_variable>

template<typename T, typename Q> //first is key, second is element
class ThreadSafePriorityQueue {
public:
    size_t size() const;
    Q pop();
    T popKey();
    void push(const std::pair<T,Q>& data);
    bool empty() const;
private:
    std::priority_queue<std::pair<T,Q>> queue_;
    std::mutex mutex_;
    std::condition_variable cond_;
};

template<typename  T> //first is key, second is element
class ThreadSafePriorityQueue<T,T>{
public:
    size_t size() const;
    T pop();
    T popKey() = delete;
    void push(const T& data);
    bool empty() const;
private:
    std::priority_queue<T> queue_;
    std::mutex mutex_;
    std::condition_variable cond_;
};


template<typename T, typename Q>
size_t ThreadSafePriorityQueue<T, Q>::size() const{
    std::unique_lock<std::mutex> lock(mutex_);
    return this->queue_.size();
}

template<typename T, typename Q>
Q ThreadSafePriorityQueue<T, Q>::pop()  {
    std::unique_lock<std::mutex> lock(mutex_);
    while(queue_.empty()){
        cond_.wait(lock);
    }
    Q res = queue_.top().second;
    queue_.pop();
    return res;
}

template<typename T, typename Q>
T ThreadSafePriorityQueue<T, Q>::popKey() {
    std::unique_lock<std::mutex> lock(mutex_);
    while(queue_.empty()){
        cond_.wait(lock);
    }
    T res = queue_.top().first;
    queue_.pop();
    return res;
}

template<typename T, typename Q>
void ThreadSafePriorityQueue<T, Q>::push(const std::pair<T,Q>& data) {
    std::unique_lock<std::mutex> lock(mutex_);
    queue_.push(data);
    mutex_.unlock();
    cond_.notify_one();
}

template<typename T, typename Q>
bool ThreadSafePriorityQueue<T, Q>::empty() const{
    std::unique_lock<std::mutex> lock(mutex_);
    return queue_.size() == 0;
}

template<typename T>
void ThreadSafePriorityQueue<T,T>::push(const T &data) {
    std::unique_lock<std::mutex> lock(mutex_);
    queue_.push(data);
    mutex_.unlock();
    cond_.notify_one();
}



#endif //LAB4_5_THREADSAFEPRIORITYQUEUE_H
