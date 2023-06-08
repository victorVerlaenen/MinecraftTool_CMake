#pragma once
#include <JuceHeader.h>
#include "FileOutput.h"
class TableModel :public juce::TableListBoxModel
{
public:
	TableModel();

	int getNumRows() override;
	void paintRowBackground(Graphics&, int rowNumber, int width, int height, bool rowIsSelected) override;
	void paintCell(Graphics&,
		int 	rowNumber,
		int 	columnId,
		int 	width,
		int 	height,
		bool 	rowIsSelected
	)override;

	void SetFile(int index, bool converted, juce::String name, juce::String extension, juce::String path);
private:
	std::vector<FileOutput> m_FileOutputs;
};
