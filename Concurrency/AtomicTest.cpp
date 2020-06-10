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
