#pragma once
#include <vector>

namespace fileConvertor
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

	class JsonToObj final
	{
	public:
		static bool ParseJsonToBlocks(const wchar_t* fileToParse, std::vector<Block*>& blockList);
		static void WriteBlocksToObj(const wchar_t* fileToWrite, const std::vector<Block*>& blockList);

	private:
		JsonToObj() = default;
		~JsonToObj() = default;

		static void WriteBlocks(FILE* pFile, const std::vector<Block*>& blocks);
	};
}
