#include <iostream>
#include <vector>
#include "JsonToObj.h"

int wmain(int argc, wchar_t* argv[], wchar_t* envp[])
{
	// Check if all necesarry command line arguments are provided
	if (argc >= 3)
	{
		std::wcout << "Executable itself: " << argv[0] << std::endl;
		std::wcout << "File to read: " << argv[1] << std::endl;
		std::wcout << "File to write: " << argv[2] << std::endl;

		using namespace fileConvertor;

		// Create the vector of blocks to fill
		std::vector<Block*> blocks{};

		// Read the json file and fill the vector of blocks
		bool result = JsonToObj::ParseJsonToBlocks(argv[1], blocks);
		if (result == false)
		{
			return -2;
		}

		// Write the obj file with the vector of blocks
		JsonToObj::WriteBlocksToObj(argv[2], blocks);

		// release memory
		for (auto pBlock : blocks)
		{
			delete pBlock;
		}
	}
	else
	{
		return -1; // file not found
	}
	return 0;
}