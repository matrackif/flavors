#pragma once

#include <benchmark.h>
#include <words.h>

namespace FlavorsBenchmarks
{
    class IpBenchmark : public WordsBenchmark
    {
    public:

        IpBenchmark(nlohmann::json& j):
			WordsBenchmark(j)
		{
		}

    protected:
        void runForDictionary(std::string& path) override;

    private:
        Flavors::Masks loadIpSetAsMasks(std::string& path, unsigned count = 0);
		Flavors::Keys loadIpSetAsKeys(std::string& path, unsigned count = 0);
    };
}