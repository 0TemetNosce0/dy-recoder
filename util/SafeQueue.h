#pragma once
#include "AudioBasic/AudioGlobal.h"
#include "AudioSampleBuffer.h"
#include <condition_variable>
#include <mutex>
#include <queue>
//#include <QDebug>

// template<typename T>
// class threadsafe_queue
//{
// private:
//    mutable std::mutex mut;
//    std::queue< std::shared_ptr<T> >
//    data_queue;//队里存储的是shared_ptr这样可以保证push和pop操作时不会引起构造或析构异常，队列更加高效
//    std::condition_variable data_read;//采用条件变量同步入队和出队操作
//    std::condition_variable data_write;//采用条件变量同步入队和出队操作
//    size_t MAX_COUNT = 5;

// public:
//    threadsafe_queue(){}

//    void wait_and_pop(T& value)//直至容器中有元素可以删除
//    {
//        std::unique_lock<std::mutex> lk(mut);
//        data_read.wait(lk,[this]{return !data_queue.empty();});
//        value = std::move(*data_queue.front());//move 给value;
//        data_queue.pop();//移出第一个元素
//        data_write.notify_one();
//    }

//    bool try_pop(T& value)//若队中无元素可以删除则直接返回false
//    {
//        std::lock_guard<std::mutex> lk(mut);
//        if(data_queue.empty())
//            return false;
//        value = std::move(*data_queue.front());
//        data_queue.pop();

//        return true;
//    }

//    std::shared_ptr<T> wait_and_pop()
//    {
//        std::unique_lock<std::mutex> lk(mut);

//        data_read.wait(lk,[this]{return !data_queue.empty();});
//        std::shared_ptr<T> res = data_queue.front();
//        data_queue.pop();
//        data_write.notify_one();
//        return res;
//    }

//    std::shared_ptr<T> try_pop()
//    {
//        std::lock_guard<std::mutex> lk(mut);
//        if(data_queue.empty())
//            return std::shared_ptr<T>();
//        std::shared_ptr<T> res = data_queue.front();
//        data_queue.pop();
//        return res;
//    }

//    void wait_and_push(T new_value)
//    {
//        std::shared_ptr<T>
//        data(std::make_shared<T>(std::move(new_value)));//数据的构造在临界区外从而缩小临界区，并且不会在临界区抛出异常
//        std::unique_lock<std::mutex> lk(mut);
//        data_write.wait(lk,[this]{return (data_queue.size() < MAX_COUNT);});
//        data_queue.push(data);
//        data_read.notify_one();
//    }

//    bool empty() const
//    {
//        std::lock_guard<std::mutex> lk(mut);
//        return data_queue.empty();
//    }
//};
template <typename T> class SafeQueue
{
protected:
    mutable std::mutex mut;
    std::queue<T *> data_queue;
    std::condition_variable data_read;  //采用条件变量同步入队和出队操作
    std::condition_variable data_write; //采用条件变量同步入队和出队操作
    size_t MAX_COUNT = 50;

public:
    SafeQueue() {}

    T *wait_and_pop() //直至容器中有元素可以删除
    {
        std::unique_lock<std::mutex> lk(mut);
        data_read.wait(lk, [this] {
            return !data_queue.empty();
        });

        T *value = data_queue.front(); //空的时候会报错
        data_queue.pop();              //移出第一个元素
        data_write.notify_one();
        return value;
    }

    T *try_pop() //
    {
        std::lock_guard<std::mutex> lk(mut);
        if (data_queue.empty())
            return nullptr;
        T *value = data_queue.front();
        data_queue.pop();
        data_write.notify_one();
        return value;
    }

    //    std::shared_ptr<T> wait_and_pop()
    //    {
    //        std::unique_lock<std::mutex> lk(mut);

    //        data_read.wait(lk,[this]{return !data_queue.empty();});
    //        std::shared_ptr<T> res = data_queue.front();
    //        data_queue.pop();
    //        data_write.notify_one();
    //        return res;
    //    }

    //    std::shared_ptr<T> try_pop()
    //    {
    //        std::lock_guard<std::mutex> lk(mut);
    //        if(data_queue.empty())
    //            return std::shared_ptr<T>();
    //        std::shared_ptr<T> res = data_queue.front();
    //        data_queue.pop();
    //        return res;
    //    }

    void wait_and_push(T *new_value)
    {
        std::unique_lock<std::mutex> lk(mut);
        data_write.wait(lk, [this] {
            return (data_queue.size() < MAX_COUNT);
        });

        data_queue.emplace(new_value);
        data_read.notify_one();
    }
    bool empty() const
    {
        std::lock_guard<std::mutex> lk(mut);
        return data_queue.empty();
    }
    void clear()
    {
        std::lock_guard<std::mutex> lk(mut);
        while (!data_queue.empty()) {
            data_queue.pop();
        }
    }
};
class /*AUDIO_CORE_EXPORT*/ AudioSampleBufferQueue : public SafeQueue<AudioSampleBuffer>
{
public:
    AudioSampleBufferQueue() : SafeQueue(/*20*/) {}
    ~AudioSampleBufferQueue() {}
    //    void clear()
    //    {
    //        std::lock_guard<std::mutex> lk(mut);
    //        while (!data_queue.empty()) {
    //            AudioSampleBuffer *buffervalue = data_queue.front();
    //            delete  buffervalue;
    //            data_queue.pop();
    //        }
    //    }
};
