#include "ThreadTest.h"

ThreadTest::ThreadTest()
{
}

void ThreadTest::Start()
{
	std::thread t(&ThreadTest::ThreadFunc, this);
	t_ = std::move(t);
	//t_.join();
	cout << "ThreadTest::Start" << endl;
}

void ThreadTest::Join()
{
	t_.join();
}

void ThreadTest::ThreadFunc()
{
	cout << "ThreadFunc" << endl;
	ThrowException();
}

void ThreadTest::ThrowException() const
{
	throw "ThreadFunc has exception";
}
