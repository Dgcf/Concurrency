#pragma once

#include "common.h"

template<typename T>
class threadsafe_queue
{
private:
	mutable std::mutex mux;
	std::queue<std::shared_ptr<T>> data_queue;
	std::condition_variable data_cond;

public:
	void wait_and_pop(T& value)
	{

	}

	bool try_pop()
	{
		
	}

	std::shared_ptr<T> wait_and_pop()
	{

	}

	std::shared_ptr<T> try_pop()
	{

	}

	void push(T new_value)
	{
		std::lock_guard<std::mutex> lc(mux);
		data_queue.push(std::make_shared<T>(new_value));
		data_cond.notify_one();
	}

	bool empty() const
	{
		std::lock_guard<std::mutex> lc(mux);
		return data_queue.empty();
	}
};