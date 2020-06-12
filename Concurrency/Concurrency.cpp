// Concurrency.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "common.h"
#include "ThreadPool.h"
#include "ThreadTest.h"

int main()
{
    /*TPtest t(10);
    t.Start();*/
    /*std::string str = "Meet the new boss...";
    std::hash<std::string> hash_fn;
    size_t str_hash = hash_fn(str);
    std::cout << str_hash << endl;*/
    ThreadTest t;
    t.Start();
    
    std::this_thread::sleep_for(std::chrono::seconds(5));
    t.Join();
    std::cout << "Hello World!\n";
}

