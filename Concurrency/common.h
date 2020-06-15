#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <deque>
#include <map>
#include <atomic>
#include <thread>
#include <future>
#include <mutex>
#include <condition_variable>
#include <algorithm>
#include <chrono>
#include <memory>

using namespace std;

enum Priority
{
	Unknown,
	High,
	Mid,
	Usual,
	Last
};

template<typename T>
struct Task
{
	Task(const Priority _p, T _f):
		prio_(_p), tp_(_f) {}

	Task(const Task& t)
	{
		prio_ = t.prio_;
		tp_ = t.tp_;
	}

	Task& operator=(const Task& t)
	{
		return *this;
	}

	//  ±º‰∏¥‘”∂»
	bool operator<(const Task& _t)
	{
		return prio_ > _t.prio_;
	}

	Priority prio_;
	T tp_;
};
