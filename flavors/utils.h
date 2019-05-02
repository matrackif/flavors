#pragma once
#include <vector>
#include <iostream>
#include <cuda-api-wrappers/api_wrappers.hpp>

namespace Flavors
{
	inline cuda::launch_configuration_t make_launch_config(int iterationCount)
	{
		cuda::launch_configuration_t config{ 0, 0, 0 };

		config.block_dimensions.x = 1024;
		config.grid_dimensions.x = (iterationCount + config.block_dimensions.x - 1) / config.block_dimensions.x;

		return config;
	}

	template<typename  T>
	class CudaArray
	{
	public:
		CudaArray(): count(0) {}

		explicit CudaArray(int count) :
			count(count)
		{
			auto currentDevice = cuda::device::current::get();
			store = cuda::memory::device::make_unique<T[]>(currentDevice, count);
			Clear();
		}

		void Clear()
		{
			cuda::memory::device::zero(store.get(), count * sizeof(T));
		}

		T* Get() { return store.get(); }

		std::vector<T> ToHost() const
		{
			std::vector<T> host(count);
			cuda::memory::copy(host.data(), store.get(), count * sizeof(unsigned));
			return host;
		}

		friend  std::ostream& operator<<(std::ostream& os, const CudaArray& obj)
		{
			auto h_array = obj.ToHost();

    		for(auto item : h_array)
        		os << item << ", ";
			os << std::endl;

			return os;
		}


		CudaArray(const CudaArray& other)
			: count(other.count)
		{
			if(count > 0)
			{
				auto currentDevice = cuda::device::current::get();
				store = cuda::memory::device::make_unique<T[]>(currentDevice, count);
				cuda::memory::copy(store.get(), other.store.get(), count * sizeof(T));
			}
		}

		CudaArray(CudaArray&& other) noexcept = default;

		CudaArray& operator=(const CudaArray& other)
		{
			if (this == &other)
				return *this;
			count = other.count;

			if(count > 0)
			{
				auto currentDevice = cuda::device::current::get();
				store = cuda::memory::device::make_unique<T[]>(currentDevice, count);
				cuda::memory::copy(store.get(), other.store.get(), count * sizeof(T));
			}
			return *this;
		}

		CudaArray& operator=(CudaArray&& other) noexcept = default;

		size_t MemoryFootprint()
		{
			return count * sizeof(T);
		}

		int Count()
		{
			return count;
		}

	private:
		int count;
		cuda::memory::device::unique_ptr<T[]> store;
	};

	class Cuda2DArray
	{
	public:
		Cuda2DArray();
		Cuda2DArray(int depth, int count);

		int Depth;
		unsigned* Get() { return store.Get(); }
		unsigned** GetLevels() { return levels.Get(); }
		unsigned* operator[](int level) const { return h_levels[level]; }

		std::vector<std::vector<unsigned>> ToHost() const;

		Cuda2DArray(const Cuda2DArray& other) = delete;
		Cuda2DArray& operator=(const Cuda2DArray& other) = delete;
		Cuda2DArray(Cuda2DArray&& other) = default;
		Cuda2DArray& operator=(Cuda2DArray&& other) = default;

		size_t MemoryFootprint();
	private:
		int count;
		CudaArray<unsigned> store;
		CudaArray<unsigned*> levels;
		std::vector<unsigned*> h_levels;
	};

	class CudaJaggedArray
	{
	public:
		CudaJaggedArray() {}
		
		CudaJaggedArray(std::vector<unsigned> sizes, unsigned offset = 0);

		int Depth() const;

		unsigned* operator[](int level);
		unsigned** GetLevels() { return levels.Get(); };

		std::vector<std::vector<unsigned>> ToHost();

		CudaJaggedArray(const CudaJaggedArray& other) = delete;
		CudaJaggedArray& operator=(const CudaJaggedArray& other) = delete;
		CudaJaggedArray(CudaJaggedArray&& other) = default;
		CudaJaggedArray& operator=(CudaJaggedArray&& other) = default;

		size_t MemoryFootprint();
	private:
		CudaArray<unsigned*> levels;
		std::vector<unsigned> sizes;
		std::vector<CudaArray<unsigned>> h_levels;
	};
}
