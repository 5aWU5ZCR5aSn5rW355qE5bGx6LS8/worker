#pragma once

namespace memDB
{
	template<typename RecordPool>
	class SwapChain
	{
		RecordPool frontBuffer;
		RecordPool backBuffer;
	public:
		template<typename... Args>
		SwapChain(Args&&... args)
			:frontBuffer(std::forward<Args>(args)...), backBuffer(std::forward<Args>(args)...)
		{

		}

		~SwapChain() = default;

		RecordPool& front() { return frontBuffer; }
		RecordPool& back() { return backBuffer; }

		void swap()
		{
			backBuffer.swap(frontBuffer);
			backBuffer.reset();
		}
	};
}