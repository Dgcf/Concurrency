// Concurrency.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "common.h"
#include "ThreadPool.h"

int main()
{
    TPtest t(10);
    t.Start();
    
    std::cout << "Hello World!\n";
}

