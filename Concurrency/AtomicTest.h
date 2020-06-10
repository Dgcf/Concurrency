#pragma once
#include "common.h"

class spinlock
{
public:
	spinlock();
	void lock();
	void unlock();

private:
	std::atomic_flag flag_ = ATOMIC_FLAG_INIT;
};

class AtomicTest
{
public:
	AtomicTest();
	
private:
	spinlock lock_;
};

