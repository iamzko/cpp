#include <iostream>
#include <exception>
#include <unistd.h>

#include <thread>
#include <queue>
#include <mutex>
#include <atomic>
#include <condition_variable>

#define MAX_SIZE 10

std::atomic<bool> g_is_running(true);
std::queue<int> g_data_que;
std::mutex g_data_que_mtx;
std::condition_variable g_data_que_empty_cv;
std::condition_variable g_data_que_full_cv;

void consumer() {
    auto thrd_id = std::this_thread::get_id();
    std::cout << "consumer thread id: " << thrd_id << std::endl;

    int data;
    while (g_is_running) {
        while (g_data_que.empty()) {
            if (!g_is_running) {
                return;
            }
            std::unique_lock<std::mutex> data_que_ul(g_data_que_mtx);
            g_data_que_empty_cv.wait(data_que_ul);
        }
        {
            std::lock_guard<std::mutex> data_que_lg(g_data_que_mtx);
            data = g_data_que.front();
            g_data_que.pop();
        }
        g_data_que_full_cv.notify_one();
        std::cout << "data: " << data << std::endl;
    }
}

void producer() {
    auto thrd_id = std::this_thread::get_id();
    std::cout << "producer thread id: " << thrd_id << std::endl;
    int cnt = 1;
    while (g_is_running) {
        while (g_data_que.size() > MAX_SIZE) {
            if (!g_is_running) {
                return;
            }
            std::unique_lock<std::mutex> data_que_ul(g_data_que_mtx);
            g_data_que_full_cv.wait(data_que_ul);
        }
        {
            std::lock_guard<std::mutex> data_que_lg(g_data_que_mtx);
            g_data_que.push(cnt);
        }
        g_data_que_empty_cv.notify_one();
        ++cnt;
    }
}

int main() {
    auto thrd_id = std::this_thread::get_id();
    std::cout << "main thread id: " << thrd_id << std::endl;
    try {
        std::thread produce_thrd(producer);
        std::thread consume_thrd(consumer);
        std::this_thread::sleep_for(std::chrono::microseconds(20000));
       
        g_is_running = false;
         sleep(10);
        g_data_que_empty_cv.notify_one();
        g_data_que_full_cv.notify_one();
        produce_thrd.join();
        consume_thrd.join();
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
