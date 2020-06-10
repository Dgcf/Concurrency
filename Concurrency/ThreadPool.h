#pragma once

#include "common.h"
#include "MsgQueue.h"

class ThreadPool
{
public:
	explicit ThreadPool(unsigned int _n);
	void Start();
	void JoinOrDetach(bool type);
	
	void AddTask(Priority, std::function<void()> _f);
	void DeleteTask(std::function<void()> _f);
	void ThreadFunc();

private:
	unsigned int nums_;
	std::vector<std::thread> vecs_;
	std::list<Task<std::function<void()>>> task_;
	std::mutex m_;
	std::condition_variable cond_;
	std::atomic<bool> run_;
	
};

// ������
class TPtest
{
public:
	TPtest(unsigned int num);

	// ����
	// �̺߳���Ϊstd::function<void()>,�������ﵥ��д����
	void AddHighData();
	void AddMidData();
	void AddUsualData();
	void AddLastData();
	void AddTask();
	void Start();
	inline void Stop();
	// ����
	void Print1();
	void Print2();

private:
	std::atomic<bool> run_;
	ThreadPool pool_;
	MsgQueue<string> queue_;	// ���Ҫ���ѵ�����
};

