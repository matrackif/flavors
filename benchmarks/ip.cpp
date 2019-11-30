#include <ip.h>
#include <sstream>

using namespace Flavors;

namespace FlavorsBenchmarks
{
    void parseLine(const std::string& line, std::vector<std::string>& tmpMasks, std::vector<unsigned>& lenghts)
	{
		std::vector<std::string> tokens;
		std::string token;
		std::stringstream streamLine{ line };

		while (getline(streamLine, token, ';'))
			tokens.push_back(token);

		tmpMasks.push_back(tokens[2]);
		try 
        { 
            lenghts.push_back(stoul(tokens[3])); 
        }
		catch (...) 
        { 
            //TODO: Exception 
        }
	}

    unsigned parseTmpMask(std::string& tmpMask)
    {
        unsigned mask = 0;
        std::vector<std::string> tokens;
		std::string token;
		std::stringstream streamLine{ tmpMask };

		while (getline(streamLine, token, '.'))
			tokens.push_back(token);

		mask |= stoul(tokens[0]);
		mask |= stoul(tokens[1]) << 8;
		mask |= stoul(tokens[2]) << 16;
		mask |= stoul(tokens[3]) << 24;

        return mask;
    }

    Flavors::Masks IpBenchmark::loadIpSetAsMasks(std::string& path, unsigned count)
    {
        std::vector<std::string> lines;
		std::ifstream file;
		file.open(path);
		bool isReading = true;
		unsigned numLinesRead = 0;
		std::string line;

        std::vector<std::string> tmpMasks;
        std::vector<unsigned> lenghts;

		if (file.good())
		{
			while ((file >> line) && isReading)
			{
				isReading = count > 0 ? (++numLinesRead < count) : true;
				parseLine(line, tmpMasks, lenghts);
			}
               
		}

        std::vector<unsigned> reorderedMasks(tmpMasks.size());
        std::transform(tmpMasks.begin(), tmpMasks.end(), reorderedMasks.begin(), parseTmpMask);

        Flavors::Masks masks(Flavors::Configuration::Default32, tmpMasks.size());

        cuda::memory::copy(masks.Lengths.Get(), lenghts.data(), masks.Count * sizeof(unsigned));
        cuda::memory::copy(masks.Store.Get(), reorderedMasks.data(), masks.Count * sizeof(unsigned));

        return masks;
    }

	Flavors::Keys IpBenchmark::loadIpSetAsKeys(std::string& path, unsigned count)
	{
		std::vector<std::string> lines;
		std::ifstream file;
		file.open(path);
		bool isReading = true;
		unsigned numLinesRead = 0;
		std::string line;

		std::vector<std::string> tmpMasks;
		std::vector<unsigned> lenghts;

		if (file.good())
		{
			while ((file >> line) && isReading)
			{
				isReading = count > 0 ? (++numLinesRead < count) : true;
				parseLine(line, tmpMasks, lenghts);
			}

		}
		std::vector<unsigned> reorderedMasks(tmpMasks.size());
		std::transform(tmpMasks.begin(), tmpMasks.end(), reorderedMasks.begin(), parseTmpMask);
		Flavors::Keys keys(Flavors::Configuration::Default32, tmpMasks.size());
		cuda::memory::copy(keys.Store.Get(), reorderedMasks.data(), keys.Count * sizeof(unsigned));
		return keys;
	}

    void IpBenchmark::runForDictionary(std::string& path)
	{
		//std::cout << "Processing ip set: " << path << std::endl;
		//measured.Add("Dictionary", path);

		//timer.Start();
		//std::vector<unsigned> data = { 0u, 3221225472u, 3221225472u, 3758096384u, 3221225472u, 4160749568u, 3556769792u };
		std::vector<unsigned> data{ 0, 96, 96, 112, 96, 124, 106 };
		std::vector<unsigned> lengths = { 1, 2, 3, 4, 5, 5, 7};
		Configuration c({ 7 });
		Flavors::Masks keys(c, data.size());
		keys.FillFromVector(data, lengths);
		std::cout << keys << std::endl;
		//keys.FillFromVector(data, lengths);
		//measured.Add("Load", timer.Stop());
		measured.Add("Count", keys.Count);
		
		timer.Start();
		keys.Sort();
		measured.Add("Sort", timer.Stop());

		CudaArray<unsigned> result{ keys.Count };

		//constexpr unsigned randomCount = 100000;
		//constexpr int seed = 123;
		//Keys randomIpSet = loadIpSetAsKeys(path, randomCount);
		//randomIpSet.FillRandom2(seed);
		//measured.Add("Seed", seed);
		for(auto& config : configs)
		{
			std::cout << "Testing config: " << config << std::endl;
			
			// call some_function which may throw something
			measured.Add("Config", config);

			timer.Start();
			auto reshapedIpSet = keys.ReshapeMasks(config);
			measured.Add("Reshape", timer.Stop());
			std::cout << "Keys: \n" << reshapedIpSet << std::endl;
			timer.Start();
			Tree tree{ reshapedIpSet };
			auto items = tree.containers.Items.ToHost();
			auto children = tree.Children.ToHost();
			auto containerStarts = tree.containers.Starts.ToHost();
			auto containerLengths = tree.containers.Lengths.ToHost();
			measured.Add("Build", timer.Stop());
			
			//measured.Add("RandomCount", randomCount);

			// TODO call ReshapeKeys or call loadIpSetAsKeys() with config argument to be safe
			// ReshapeKeys() should not modify the actual keys, just how they are stored in the array
			//randomIpSet = randomIpSet.ReshapeKeys(config);
			//timer.Start();
			//tree.Match(randomIpSet, result.Get());
			//measured.Add("RandomMatch", timer.Stop());

			//timer.Start();
			//randomIpSet.Sort();
			//measured.Add("RandomSort", timer.Stop());

			result.Clear();
			//timer.Start();
			//tree.Match(randomIpSet, result.Get());
			//measured.Add("RandomSortedMatch", timer.Stop());
			measured.AddHitCount(result);
					
			measured.Add("TreeMemory", tree.MemoryFootprint());
			measured.Add("TreeLevels", tree);
			measured.Add("Depth", tree.Depth());

			// Get memory footprint of specific arrays
			measured.Add("TreeMemoryUniqueOnly", tree.GetSpecificMemoryFootPrint(Tree::ArrayType::SUM_UNIQUE_SIZES_ONLY));
			measured.Add("ChildrenMemory", tree.GetSpecificMemoryFootPrint(Tree::ArrayType::CHILDREN));
			measured.Add("ChildrenCountsMemory", tree.GetSpecificMemoryFootPrint(Tree::ArrayType::CHILDREN_COUNTS));
			measured.Add("ScanMemory", tree.GetSpecificMemoryFootPrint(Tree::ArrayType::SCAN));
			measured.Add("PreScanMemory", tree.GetSpecificMemoryFootPrint(Tree::ArrayType::PRE_SCAN));
			measured.Add("PermuationMemory", tree.GetSpecificMemoryFootPrint(Tree::ArrayType::PERMUTATION));
			measured.Add("LengthsMemory", tree.GetSpecificMemoryFootPrint(Tree::ArrayType::LENGTHS));
			measured.Add("MasksPartsMemory", tree.GetSpecificMemoryFootPrint(Tree::ArrayType::MASKS_PARTS));
			measured.Add("ContainerSumMemory", tree.GetSpecificMemoryFootPrint(Tree::ArrayType::CONTAINER_SUM));
			measured.Add("ContainerItemsMemory", tree.GetSpecificMemoryFootPrint(Tree::ArrayType::CONTAINER_ITEMS));
			measured.Add("ContainerStartsMemory", tree.GetSpecificMemoryFootPrint(Tree::ArrayType::CONTAINER_STARTS));
			measured.Add("ContainerLengthsMemory", tree.GetSpecificMemoryFootPrint(Tree::ArrayType::CONTAINER_LENGTHS));
			measured.Add("AverageNodeSizesLevels", tree.getAverageNodeSizePerLevel());

			auto avgNodeSize = tree.getAverageNodeSize();
			auto treeHeight = tree.Depth();
			measured.Add("AverageNodeSize", avgNodeSize);
			measured.Add("TreeHeight", treeHeight);
			measured.Add("NodeSizeToHeightRatio", avgNodeSize / treeHeight);
			std::ostringstream oss;
			oss << "{";
			for (auto itemsPerLvl : tree.containers.ItemsPerLevel)
			{
				oss << itemsPerLvl << ", ";
			}
			oss << "}";
			measured.Add("ItemsPerLevel", oss.str());
			//measured.Add("MaxItemsPerLevel", *std::max_element(tree.containers.ItemsPerLevel.cbegin(), tree.containers.ItemsPerLevel.cend()));
			// TODO find fails at random times for configs with large strides, probably too much memory allocated
			timer.Start();
			tree.Find(reshapedIpSet, result.Get());
			measured.Add("Find", timer.Stop());

			timer.Start();
			tree.Match(reshapedIpSet, result.Get());
			measured.Add("Match", timer.Stop());
			measured.AppendToFile(resultFile);
        }
		
	}

}