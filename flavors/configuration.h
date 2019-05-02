#pragma once

#include <ostream>
#include <vector>

#include <utils.h>

namespace Flavors
{
	//TODO: Constructor from init list
	class Configuration
	{
	public:
		static Configuration Default32;
		static Configuration Binary32;

		static Configuration Default(unsigned length);
		static Configuration Binary(unsigned length);

		int Length;

		unsigned* Get();

		Configuration();
		explicit Configuration(const std::vector<unsigned>& levels);
		void Create(const std::vector<unsigned>& levels);

		unsigned operator[](int level) const;

		int Depth() const { return h_levels.size(); };
		int Mask(int level) const;

		void PopLastLevel();

		std::string ToString();
		friend std::ostream& operator<<(std::ostream& os, Configuration& obj);

		friend bool operator==(const Configuration& lhs, const Configuration& rhs);
		friend bool operator!=(const Configuration& lhs, const Configuration& rhs);

		Configuration(const Configuration& other) = default;
		Configuration(Configuration&& other) noexcept = default;
		Configuration& operator=(const Configuration& other) = default;
		Configuration& operator=(Configuration&& other) noexcept = default;
	private:
		std::vector<unsigned> h_levels;
		CudaArray<unsigned> levels;
	};
}
