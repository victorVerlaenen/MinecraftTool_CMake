#pragma once
#include <vector>

namespace convert
{
	struct Block
	{
		Block(const char* layer, bool opaque, float x, float y, float z)
			:layer{ layer }
			, opaque{ opaque }
			, x{ x }
			, y{ y }
			, z{ z }
		{
		}

		const char* layer;
		const bool opaque;
		const float x, y, z;
	};

	class FileConverter final
	{
	public:
		static bool ParseJsonToBlocks(const wchar_t* fileToParse, std::vector<Block*>& blockList);
		static void WriteBlocksToObj(const wchar_t* fileToWrite, const std::vector<Block*>& blockList);

	private:
		FileConverter() = default;
		~FileConverter() = default;

		static void WriteBlocks(FILE* pFile, const std::vector<Block*>& blocks);
	};
}
