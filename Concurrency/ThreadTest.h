#pragma once
#include "common.h"

class ThreadTest
{
public:
	ThreadTest();
	void Start();
	void Join();
	void ThreadFunc();
	void ThrowException() const;

private:
	std::thread t_;
};

//void StartThread();

