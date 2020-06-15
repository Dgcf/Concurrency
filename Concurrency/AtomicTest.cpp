#include "AtomicTest.h"

spinlock::spinlock()
{

}
void spinlock::lock()
{
	while (flag_.test_and_set(std::memory_order_acquire));
}

void spinlock::unlock()
{
	flag_.clear(std::memory_order_release);
}

AtomicTest::AtomicTest()
{

}

std::atomic<bool> x(true);
std::atomic<bool> y(true);
std::atomic<int> z(0);

void write_x_then_y()
{
	x.store(true, std::memory_order_relaxed);
	y.store(true, std::memory_order_relaxed);
}

void read_y_then_x()
{
	while (!y.load(std::memory_order_relaxed));
	if (x.load(std::memory_order_relaxed))
	{
		++z;
	}
}

void test()
{
	x = false;
	y = false;
	z = 0;
	std::thread a(write_x_then_y);
	std::thread b(read_y_then_x);
	a.join();
	b.join();
	assert(z.load() != 0);
}

std::atomic<int> x1(0), y11(0), z1(0);
std::atomic<bool> go(false);
unsigned const loop_count = 10;

read_values values1[loop_count];
read_values values2[loop_count];
read_values values3[loop_count];
read_values values4[loop_count];
read_values values5[loop_count];

void increment(std::atomic<int>* var_to_inc, read_values* values)
{
	while (!go)
	{
		std::this_thread::yield();
	}
	for (size_t i = 0; i < loop_count; i++)
	{
		values->x = x1.load(std::memory_order_relaxed);
		values->y = y11.load(std::memory_order_relaxed);
		values->z = z1.load(std::memory_order_relaxed);
		var_to_inc->store(i + 1, std::memory_order_relaxed);
		std::this_thread::yield();
	}
}

void read_vals(read_values* values)
{
	while (!go)
	{
		std::this_thread::yield();
	}
	for (size_t i = 0; i < loop_count; i++)
	{
		values[i].x = x1.load(std::memory_order_relaxed);
		values[i].y = y11.load(std::memory_order_relaxed);
		values[i].z = z1.load(std::memory_order_relaxed);
		std::this_thread::yield();
	}
}

void print(read_values* v)
{
	for (unsigned i = 0; i < loop_count; ++i)
	{
		if (i) std::cout << ",";
		std::cout << "(" << v[i].x << "," << v[i].y << "," << v[i].z << ")";
 	}
	std::cout << std::endl;
}

void test1()
{
	std::thread t1(increment, &x1, values1);
	std::thread t2(increment, &y11, values2);
	std::thread t3(increment, &z1, values3);
	std::thread t4(read_vals, values4);
	std::thread t5(read_vals, values5);
	go = true;
	t5.join();
	t4.join();
	t3.join();
	t2.join();
	t1.join();

	print(values1);
	print(values2);
	print(values3);
	print(values4);
	print(values5);
}
