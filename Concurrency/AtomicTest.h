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

// ÄÚ´æÄ£ÐÍ

extern std::atomic<bool> x, y;
extern std::atomic<int> z;

void write_x_then_y();
void read_y_then_x();
void test();

struct read_values {
	int x, y, z;
};
void increment(std::atomic<int>* var_to_inc, read_values*);
void read_vals(read_values* values);
void print(read_values* v);
void test1();
