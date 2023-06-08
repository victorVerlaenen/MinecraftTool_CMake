#include "TableModel.h"

TableModel::TableModel()
{
	m_FileOutputs.push_back({ false,"","","C:\\"});
	m_FileOutputs.push_back({ false,"","","C:\\"});
}

int TableModel::getNumRows()
{
	return static_cast<int>(m_FileOutputs.size());
}

void TableModel::paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
	if (rowIsSelected)
	{
		g.setColour(Colour{210,210,210});
		g.fillRoundedRectangle(0, 0, static_cast<float>(width), static_cast<float>(height), 3);
		g.drawRoundedRectangle(0, 0, static_cast<float>(width), static_cast<float>(height), 3, 2);
	}else
	{
		g.setColour(Colour{ 255,128,64 });
		g.drawRoundedRectangle(0, 0, static_cast<float>(width), static_cast<float>(height), 3, 2);
	}
}

void TableModel::paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
	if (rowNumber < m_FileOutputs.size())
	{
		if (rowIsSelected)
		{
			g.setColour(Colour{ 64,64,64 });
		}
		else
		{
			g.setColour(Colour{ 243,243,243 });
		}
		FileOutput& file = m_FileOutputs[rowNumber];
		switch (columnId)
		{

		case 1: g.drawText(String{ file.isOriginal ? "true" : "false"}, 10, 0, width, height, Justification::centredLeft);
			break;
		case 2: g.drawText(String{ file.name }, 0, 0, width, height, Justification::centredLeft);
			break;
		case 3: g.drawText(String{ file.extension }, 0, 0, width, height, Justification::centredLeft);
			break;
		case 4: g.drawText(String{ file.path }, 0, 0, width, height, Justification::centredLeft);
			break;
		}
	}
}

void TableModel::SetFile(int index, bool converted, juce::String name, juce::String extension, juce::String path)
{
	m_FileOutputs[index].isOriginal = converted;
	m_FileOutputs[index].name = name;
	m_FileOutputs[index].extension = extension;
	m_FileOutputs[index].path = path;
}
