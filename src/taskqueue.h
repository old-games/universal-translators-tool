#ifndef __TASK_QUEUE_H__
#define __TASK_QUEUE_H__



#define TASK_LOCK std::lock_guard<std::mutex> lock(mTaskMutex);



template<class T>
class TaskManaged
{
	typedef std::queue<T> TaskQueue;


public:
	
	virtual bool CheckTasks() = 0;	// returns true if there was some tasks

protected:

	TaskManaged() = default;
	virtual ~TaskManaged() = default;

	inline virtual bool IsTaskQueueEmpty()
	{
		TASK_LOCK
		return mTasks.empty();
	}

	inline void AddTask(const T& task)
	{
		TASK_LOCK
		mTasks.push(task);
	}

	inline T PopTask()
	{
		TASK_LOCK
		T task(mTasks.front());
		mTasks.pop();
		return task;
	}

	inline void ClearTasks()
	{
		TASK_LOCK
		std::queue<T> empty;
		std::swap( mTasks, empty );
	}

	TaskQueue	mTasks;
	std::mutex	mTaskMutex;
};



#endif // __TASK_QUEUE_H__
