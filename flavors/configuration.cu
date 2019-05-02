#include <configuration.h>

#include <algorithm>
#include <thrust/execution_policy.h>
#include <sstream>

namespace Flavors
{
	Configuration Configuration::Default32{ std::vector <unsigned>{32} };
	Configuration Configuration::Binary32{ std::vector <unsigned>{1, 1, 1, 1, 1, 1, 1, 1,
																  1, 1, 1, 1, 1, 1, 1, 1,
																  1, 1, 1, 1, 1, 1, 1, 1,
																  1, 1, 1, 1, 1, 1, 1, 1} };

	Configuration Configuration::Default(unsigned length)
	{
		std::vector<unsigned> levels;
		auto currentLength = length;

		while(currentLength > 32)
		{
			levels.push_back(32);
			currentLength -= 32;
		}

		if(currentLength > 0)
			levels.push_back(currentLength);

		return Configuration{levels};
	}

	Configuration Configuration::Binary(unsigned length)
	{
		std::vector<unsigned> levels(length, 1u);
		return Configuration{levels};
	}

	Configuration::Configuration():
		Length(0)
	{
	}

	Configuration::Configuration(const std::vector<unsigned>& levels):
		Length(0),
		h_levels(levels)
	{
		for (auto level : h_levels)
			Length += level;
	}

	void Configuration::Create(const std::vector<unsigned>& levels)
	{
		h_levels = levels;
		Length = 0;
		for (auto level : h_levels)
			Length += level;
	}

	unsigned* Configuration::Get()
	{
		if(levels.Count() == 0)
		{
			levels = CudaArray<unsigned>{static_cast<int>(h_levels.size())};
			cuda::memory::copy(levels.Get(), h_levels.data(), Depth() * sizeof(unsigned));
		}

		return levels.Get();
	}

	unsigned Configuration::operator[](int level) const
	{
		return h_levels[level];
	}

	int Configuration::Mask(int level) const
	{
		//TODO: Can this be done better? Why overflow acts differently for literal 32 and config.h_levels[level]
		return h_levels[level] != 32 ? (1u << h_levels[level]) - 1u : ~0;
	}

	void Configuration::PopLastLevel()
	{
		//TODO: Should this reallocate CudaArray, if Get has been already called?
		h_levels.pop_back();
	}

	std::string Configuration::ToString()
	{
		std::stringstream ss;

		ss << "{";
		std::copy(h_levels.begin(), h_levels.end() - 1, std::ostream_iterator<unsigned>(ss, ", "));
		ss << *(h_levels.end() - 1) << "}";

		return ss.str();
	}

	std::ostream& operator<<(std::ostream& os, Configuration& obj)
	{
		os << obj.ToString();

		return os;
	}

	bool operator==(const Configuration& lhs, const Configuration& rhs)
	{
		if (lhs.Depth() != rhs.Depth())
			return false;

		auto cmpResult = std::mismatch(lhs.h_levels.begin(), lhs.h_levels.end(), rhs.h_levels.begin());
		return cmpResult.first == lhs.h_levels.end();
	}

	bool operator!=(const Configuration& lhs, const Configuration& rhs)
	{
		return !(lhs == rhs);
	}
}
