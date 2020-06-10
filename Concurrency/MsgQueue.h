#pragma once
#include "common.h"

template<typename Tp>
class MsgQueue
{
public:
	void AddQueue(const Task<Tp>& q)
	{
		{
			std::lock_guard<std::mutex> lc(m_);
			data_.push_back(q);
			data_.sort();
		}
		cond_.notify_one();
	}

	Tp Take()
	{
		std::unique_lock<std::mutex> ul(m_);
		cond_.wait(ul, [this] { return !data_.empty(); });
		Tp tmp = data_.front().tp_;
		data_.pop_front();
		return tmp;
	}

private:
	std::mutex m_;
	std::condition_variable cond_;
	std::list<Task<Tp>> data_;
};
