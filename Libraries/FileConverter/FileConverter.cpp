#include "FileConverter.h"
#include "rapidjson.h"
#include "document.h"
#include "istreamwrapper.h"
#include <fstream>
#include <Windows.h>

bool convert::FileConverter::ParseJsonToBlocks(const wchar_t* fileToParse, std::vector<Block*>& blockList)
{
	using rapidjson::Document;
	Document jsonDoc;

	if (std::ifstream is{ fileToParse })
	{
		// Parse the json file
		rapidjson::IStreamWrapper isw{ is };
		jsonDoc.ParseStream(isw);

		using rapidjson::Value;

		// Loop over all the array elements of the json file
		for (Value::ConstValueIterator itr = jsonDoc.Begin(); itr != jsonDoc.End(); itr++)
		{
			auto& layer = *itr;
			auto& layerValue = layer["layer"];
			auto& opaqueValue = layer["opaque"];
			auto& positions = layer["positions"];

			// Loop over all the block positions of each layer
			for (Value::ConstValueIterator posItr = positions.Begin(); posItr != positions.End(); posItr++)
			{
				auto& blockPosition = *posItr;
				auto& xValue = blockPosition[0];
				auto& yValue = blockPosition[1];
				auto& zValue = blockPosition[2];

				// Add this block to the blocks vector
				blockList.push_back(new Block{ layerValue.GetString(), opaqueValue.GetBool(), xValue.GetFloat(), yValue.GetFloat(), zValue.GetFloat() });
			}
		}
		return true;
	}
	return false;
}

void convert::FileConverter::WriteBlocksToObj(const wchar_t* fileToWrite, const std::vector<Block*>& blockList)
{
	// Create new file to write to
	FILE* pOFile = nullptr;
	_wfopen_s(&pOFile, fileToWrite, L"w+,ccs=UTF-8");
	if (pOFile != nullptr)
	{
		fwprintf_s(pOFile, L"# json parsed to obj\n");

		SetConsoleOutputCP(CP_UTF8);

		// Enable buffering to prevent VS from chopping up UTF-8 byte sequences
		setvbuf(stdout, nullptr, _IOFBF, 1000);

		WriteBlocks(pOFile, blockList);

		fclose(pOFile);
	}
}

void convert::FileConverter::WriteBlocks(FILE* pFile, const std::vector<Block*>& blocks)
{
	// Write all the vertices for every block in the list
	for (auto pBlock : blocks)
	{
		fwprintf_s(pFile, L"v %.4f %.4f %.4f\n", 0.0f + pBlock->x, 0.0f + pBlock->y, 0.0f + pBlock->z);
		fwprintf_s(pFile, L"v %.4f %.4f %.4f\n", 0.0f + pBlock->x, 0.0f + pBlock->y, 1.0f + pBlock->z);
		fwprintf_s(pFile, L"v %.4f %.4f %.4f\n", 0.0f + pBlock->x, 1.0f + pBlock->y, 0.0f + pBlock->z);
		fwprintf_s(pFile, L"v %.4f %.4f %.4f\n", 0.0f + pBlock->x, 1.0f + pBlock->y, 1.0f + pBlock->z);
		fwprintf_s(pFile, L"v %.4f %.4f %.4f\n", 1.0f + pBlock->x, 0.0f + pBlock->y, 0.0f + pBlock->z);
		fwprintf_s(pFile, L"v %.4f %.4f %.4f\n", 1.0f + pBlock->x, 0.0f + pBlock->y, 1.0f + pBlock->z);
		fwprintf_s(pFile, L"v %.4f %.4f %.4f\n", 1.0f + pBlock->x, 1.0f + pBlock->y, 0.0f + pBlock->z);
		fwprintf_s(pFile, L"v %.4f %.4f %.4f\n", 1.0f + pBlock->x, 1.0f + pBlock->y, 1.0f + pBlock->z);
	}

	fwprintf_s(pFile, L"\n");

	// Write the normals (Only 6 because all the blocks have the same normals)
	fwprintf_s(pFile, L"vn %.4f %.4f %.4f\n", 0.0f, 0.0f, 1.0f);
	fwprintf_s(pFile, L"vn %.4f %.4f %.4f\n", 0.0f, 0.0f, -1.0f);
	fwprintf_s(pFile, L"vn %.4f %.4f %.4f\n", 0.0f, 1.0f, 0.0f);
	fwprintf_s(pFile, L"vn %.4f %.4f %.4f\n", 0.0f, -1.0f, 0.0f);
	fwprintf_s(pFile, L"vn %.4f %.4f %.4f\n", 1.0f, 0.0f, 0.0f);
	fwprintf_s(pFile, L"vn %.4f %.4f %.4f\n", -1.0f, 0.0f, 0.0f);

	fwprintf_s(pFile, L"\n");

	// Write the faces
	const int facesPerBlock{ 8 };
	for (int i{ 0 }; i <= blocks.size(); i++)
	{
		int increment{ i * facesPerBlock };
		fwprintf_s(pFile, L"f %d//%d %d//%d %d//%d\n", 1 + increment, 2, 7 + increment, 2, 5 + increment, 2);
		fwprintf_s(pFile, L"f %d//%d %d//%d %d//%d\n", 1 + increment, 2, 3 + increment, 2, 7 + increment, 2);
		fwprintf_s(pFile, L"f %d//%d %d//%d %d//%d\n", 1 + increment, 6, 4 + increment, 6, 3 + increment, 6);
		fwprintf_s(pFile, L"f %d//%d %d//%d %d//%d\n", 1 + increment, 6, 2 + increment, 6, 4 + increment, 6);
		fwprintf_s(pFile, L"f %d//%d %d//%d %d//%d\n", 3 + increment, 3, 8 + increment, 3, 7 + increment, 3);
		fwprintf_s(pFile, L"f %d//%d %d//%d %d//%d\n", 3 + increment, 3, 4 + increment, 3, 8 + increment, 3);
		fwprintf_s(pFile, L"f %d//%d %d//%d %d//%d\n", 5 + increment, 5, 7 + increment, 5, 8 + increment, 5);
		fwprintf_s(pFile, L"f %d//%d %d//%d %d//%d\n", 5 + increment, 5, 8 + increment, 5, 6 + increment, 5);
		fwprintf_s(pFile, L"f %d//%d %d//%d %d//%d\n", 1 + increment, 4, 5 + increment, 4, 6 + increment, 4);
		fwprintf_s(pFile, L"f %d//%d %d//%d %d//%d\n", 1 + increment, 4, 6 + increment, 4, 2 + increment, 4);
		fwprintf_s(pFile, L"f %d//%d %d//%d %d//%d\n", 2 + increment, 1, 6 + increment, 1, 8 + increment, 1);
		fwprintf_s(pFile, L"f %d//%d %d//%d %d//%d\n", 2 + increment, 1, 8 + increment, 1, 4 + increment, 1);
	}
}