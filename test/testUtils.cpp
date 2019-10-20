#include <catch/catch.hpp>
#include <helpers.h>

struct NonStreamableStruct {};
struct StreamableStruct
{
	friend std::ostream& operator<<(std::ostream & ostr, const StreamableStruct& ss);
};

std::ostream& operator<<(std::ostream & ostr, const StreamableStruct& ss)
{
	 return ostr << "StreamableStruct" << std::endl;
}

TEST_CASE("Test proper functionality of is_streamable<std::ostringstream, T>()", "[is_streamable]")
{
	SECTION("Types that should be streamable")
	{
		REQUIRE(is_streamable<std::ostringstream, int>::value);
		REQUIRE(is_streamable<std::ostringstream, std::string>::value);
		REQUIRE(is_streamable<std::ostringstream, StreamableStruct>::value);
	}

	SECTION("Types that should NOT be streamable")
	{
		REQUIRE(!is_streamable<std::ostringstream, NonStreamableStruct>::value);
		REQUIRE(!is_streamable<std::ostringstream, std::vector<int>>::value);
	}
}
