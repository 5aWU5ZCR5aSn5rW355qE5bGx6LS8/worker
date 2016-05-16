#pragma once
#include <vector>
#include <memory>

namespace memDB
{
	template<typename BackStorage, size_t MAX_RECORDS>
	class RecordPool
	{
		using RecordIterator = typename BackStorage::iterator;

		std::vector<RecordIterator> mRecords;

		BackStorage* mStorage;
	public:
		explicit RecordPool(BackStorage& storage)
			:mStorage(std::addressof(storage))
		{
			mRecords.reserve(MAX_RECORDS);
		}

		~RecordPool() = default;

		void add(RecordIterator iter)
		{
			mRecords.emplace_back(iter);
		}

		void swap(RecordPool& other)
		{
			mRecords.swap(other.mRecords);
			mStorage->swap(*other.mStorage);
		}

		void reset()
		{
			for (auto iter : mRecords)
			{
				mStorage->erase(iter);
			}
			mRecords.clear();
		}
	};

}