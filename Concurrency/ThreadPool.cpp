#include "ThreadPool.h"

ThreadPool::ThreadPool(unsigned int _n):
nums_(_n),
run_(true)
{

}

void ThreadPool::Start()
{
	for (size_t i = 0; i < nums_; i++)
	{
		std::thread t(std::bind(&ThreadPool::ThreadFunc, this));
		vecs_.push_back(std::move(t));
	}
}

void ThreadPool::JoinOrDetach(bool type)
{
	std::vector<std::thread>::iterator iter;

	for (iter = vecs_.begin(); iter != vecs_.end(); ++iter)
	{
		if (type && iter->joinable())
		{
			iter->join();
		}
		else
		{
			iter->detach();
		}
	}
}

void ThreadPool::AddTask(Priority _p, std::function<void()> _f)
{
	Task<std::function<void()>> task(_p, _f);
	{
		std::lock_guard<std::mutex> lock(m_);
		task_.push_back(task);
		task_.sort();
	}
	// ���������������߳�������notify����
	// ��������߳���ִ���������wait��notify����
	cond_.notify_all();
}

void ThreadPool::DeleteTask(std::function<void()> _f)
{

}

void ThreadPool::ThreadFunc()
{
	printf("-----new thread id: %ld -----\n", std::this_thread::get_id());
	// ����task
	while (run_.load())
	{
		std::unique_lock<std::mutex> ul(m_);
		cond_.wait(ul, [this] { return !task_.empty(); });
		std::function<void()> func = task_.front().tp_;
		task_.pop_front();
		func();
	}
}

TPtest::TPtest(unsigned int num):pool_(num), run_(true)
{
}

void TPtest::AddHighData()
{
	vector<string> h = {
		"����", "��", "��һλ", "��", "�񼶱�", "����", "�ǳ�", "ǿ��",
		"����", "Ҳ����", "ѧϰ", "Ŭ����", "����", "ʲô", "����", "��", "�ȴ�", "Ϊ��"
	};
	
	for (vector<string>::const_iterator iter = h.cbegin(); iter != h.cend(); ++iter)
	{
		Task<string> task(High, *iter);
		queue_.AddQueue(Task<string>(High, *iter));
	}
}

void TPtest::AddMidData()
{
	vector<string> m = {
		"hello", "Zsh", "is", "big", "God", "She", "Very", "Stronge",
		"But", "Also", "Study", "Hard", "So", "what", "are", "you", "Waiting", "for"
	};
	for (vector<string>::const_iterator iter = m.cbegin(); iter != m.cend(); ++iter)
	{
		Task<string> task(Mid, *iter);
		queue_.AddQueue(Task<string>(High, *iter));
	}
}

void TPtest::AddUsualData()
{
	vector<string> u = {
		"123", "23", "789", "321", "569", "284", "092", "1594",
		"370", "527", "840", "316", "478", "326", "326", "780", "22", "393"
	};
	for (vector<string>::const_iterator iter = u.cbegin(); iter != u.cend(); ++iter)
	{
		Task<string> task(Mid, *iter);
		queue_.AddQueue(Task<string>(High, *iter));
	}
}

void TPtest::AddLastData()
{
	vector<string> l = {
		"123", "23", "789", "321", "569", "284", "092", "1594",
		"370", "527", "840", "316", "478", "326", "326", "780", "22", "393"
	};
	for (vector<string>::const_iterator iter = l.cbegin(); iter != l.cend(); ++iter)
	{
		Task<string> task(Mid, *iter);
		queue_.AddQueue(Task<string>(High, *iter));
	}
}

void TPtest::AddTask()
{
	while (run_.load())
	{
		pool_.AddTask(Usual, std::bind(&TPtest::AddLastData, this));
		pool_.AddTask(Usual, std::bind(&TPtest::AddUsualData, this));
		pool_.AddTask(Usual, std::bind(&TPtest::AddMidData, this));
		pool_.AddTask(Usual, std::bind(&TPtest::AddHighData, this));
		pool_.AddTask(Usual, std::bind(&TPtest::Print2, this));
		pool_.AddTask(Usual, std::bind(&TPtest::Print1, this));
	}
}

void TPtest::Start()
{
	// start��AddTask����λ�ò���
	pool_.Start();
	std::async(std::launch::async, &TPtest::AddTask, this);
	
	pool_.JoinOrDetach(true);
}

void TPtest::Stop()
{
	run_.store(false);
}

void TPtest::Print1()
{
	string s = queue_.Take();
	printf("Print1: %s\n", s.c_str());
}

void TPtest::Print2()
{
	string s = queue_.Take();
	printf("Print2: %s\n", s.c_str());
}
