#include "MainComponent.h"
#include "FileConverter.h"

//==============================================================================
MainComponent::MainComponent()
{
	// Make sure you set the size of the component after
	// you add any child components.
	setSize(450, 300);
	setFramesPerSecond(60); // This sets the frequency of the update calls.

	// TABLE OUTPUT
	addAndMakeVisible(m_DataTable);
	m_pTableModel = new TableModel();
	m_DataTable.setModel(m_pTableModel);
	m_DataTable.getHeader().addColumn("Converted", 1, 60, 50, 200);
	m_DataTable.getHeader().addColumn("Name", 2, 150, 20, 60);
	m_DataTable.getHeader().addColumn("Extension", 3, 70, 20, 60);
	m_DataTable.getHeader().addColumn("Path", 4, getWidth() - 60 - 150 - 70, 20, 60);
	
	// FILE TO CONVERT
	// BUTTON
	addAndMakeVisible(m_FileToConvertButton);
	m_FileToConvertButton.setButtonText("Browse");
	m_FileToConvertButton.onClick = [this]()
	{
		SelectFile();
	};

	// EDITABLE LABEL
	addAndMakeVisible(m_FileToConvertEditableLabel);
	m_FileToConvertEditableLabel.setEditable(true);
	m_FileToConvertEditableLabel.setText("C:\\", juce::dontSendNotification);
	m_FileToConvertEditableLabel.setColour(juce::Label::textColourId, juce::Colours::white);
	m_FileToConvertEditableLabel.setColour(juce::Label::backgroundColourId, juce::Colours::darkgrey);
	m_FileToConvertEditableLabel.onTextChange = [this]()
	{
		m_FileToConvert = juce::File(m_FileToConvertEditableLabel.getText());

		if (m_FileToConvert.existsAsFile() == false)
		{
			m_FileToConvertEditableLabel.setColour(juce::Label::backgroundColourId, juce::Colours::indianred);
		}
		else
		{
			m_FileToConvertEditableLabel.setColour(juce::Label::backgroundColourId, juce::Colours::darkgrey);
		}
		Logger::getCurrentLogger()->writeToLog(m_FileToConvert.getFullPathName() + "\n");
	};

	// LABEL
	addAndMakeVisible(m_FileToConvertLabel);
	m_FileToConvertLabel.setText("File to convert:", juce::dontSendNotification);
	m_FileToConvertLabel.attachToComponent(&m_FileToConvertEditableLabel, true);
	m_FileToConvertLabel.setColour(juce::Label::textColourId, juce::Colours::white);

	// NEW FILE
	// BUTTON
	addAndMakeVisible(m_NewFileButton);
	m_NewFileButton.setButtonText("Browse");
	m_NewFileButton.onClick = [this]()
	{
		SelectFile(true);
	};

	// EDITABLE LABEL
	addAndMakeVisible(m_NewFileEditableLabel);
	m_NewFileEditableLabel.setEditable(true);
	m_NewFileEditableLabel.setText("C:\\", juce::dontSendNotification);
	m_NewFileEditableLabel.setColour(juce::Label::textColourId, juce::Colours::white);
	m_NewFileEditableLabel.setColour(juce::Label::backgroundColourId, juce::Colours::darkgrey);
	m_NewFileEditableLabel.onTextChange = [this]()
	{
		m_NewFile = juce::File(m_NewFileEditableLabel.getText());
		if (m_NewFile.exists() == false)
		{
			m_NewFileEditableLabel.setColour(juce::Label::backgroundColourId, juce::Colours::indianred);
		}
		else
		{
			m_NewFileEditableLabel.setColour(juce::Label::backgroundColourId, juce::Colours::darkgrey);
		}
		Logger::getCurrentLogger()->writeToLog(m_NewFile.getFullPathName() + "\n");
	};

	// LABEL
	addAndMakeVisible(m_NewFileLabel);
	m_NewFileLabel.setText("Location to save:", juce::dontSendNotification);
	m_NewFileLabel.attachToComponent(&m_NewFileEditableLabel, true);
	m_NewFileLabel.setColour(juce::Label::textColourId, juce::Colours::white);

	// CONVERT
	addAndMakeVisible(m_ConvertButton);
	m_ConvertButton.setButtonText("Convert");
	m_ConvertButton.onClick = [this]()
	{
		ConvertFile();
	};

	// Cancel
	addAndMakeVisible(m_CancelButton);
	m_CancelButton.setButtonText("Cancel");
}

MainComponent::~MainComponent()
{
	delete m_pTableModel;
}

//==============================================================================
void MainComponent::update()
{
	// This function is called at the frequency specified by the setFramesPerSecond() call
	// in the constructor. You can use it to update counters, animate values, etc.
}

//==============================================================================
void MainComponent::paint(juce::Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

	// You can add your drawing code here!
}

void MainComponent::resized()
{
	// This is called when the MainContentComponent is resized.
	// If you add any child components, this is where you should
	// update their positions.
	m_FileToConvertButton.setBounds(340, 15, 100, 20);
	m_FileToConvertEditableLabel.setBounds(130, 15, 200, 20);

	m_NewFileButton.setBounds(340, 40, 100, 20);
	m_NewFileEditableLabel.setBounds(130, 40, 200, 20);

	m_ConvertButton.setBounds(20, 70, 100, 20);
	m_CancelButton.setBounds(140, 70, 100, 20);

	m_DataTable.setBounds(0, 110, getWidth(), getHeight());
}

void MainComponent::SelectFile(bool isSaveLocation)
{
	// You can add multiple options here with the bitwise AND
	auto chooserFlags = isSaveLocation ? FileBrowserComponent::openMode | FileBrowserComponent::canSelectDirectories : FileBrowserComponent::openMode;
	const auto browserTitle = isSaveLocation ? "Select the location to save the new file..." : "Select the file you want to convert...";
	const auto filePattern = isSaveLocation ? juce::String() : "*.json";
	m_upFileChooser = std::make_unique<juce::FileChooser>(browserTitle,
		File::getSpecialLocation(File::userHomeDirectory),
		filePattern);

	m_upFileChooser->launchAsync(chooserFlags, [this, isSaveLocation](const FileChooser& chooser)
		{
			File mooseFile(chooser.getResult());
			if (mooseFile == juce::File() || mooseFile.exists() == false)
				return;

			Logger::getCurrentLogger()->writeToLog(isSaveLocation ? "isSave" : "isNotSave");

			auto& labelToSet = isSaveLocation ? m_NewFileEditableLabel : m_FileToConvertEditableLabel;
			if (isSaveLocation)
			{
				m_NewFile = chooser.getResult();
			}
			else
			{
				m_FileToConvert = chooser.getResult();
			}

			labelToSet.setText(mooseFile.getFullPathName(), juce::dontSendNotification);
		});
}

void MainComponent::ConvertFile()
{
	using namespace convert;

	// Create the vector of blocks to fill
	std::vector<Block*> blocks{};

	// Read the json file and fill the vector of blocks
	auto fileToParse{ m_FileToConvert.getFullPathName() };
	bool result = FileConverter::ParseJsonToBlocks(fileToParse.toWideCharPointer(), blocks);

	// Write the obj file with the vector of blocks
	auto newFile{ m_NewFile.getFullPathName() + "/" + m_FileToConvert.getFileNameWithoutExtension() + ".obj" };
	FileConverter::WriteBlocksToObj(newFile.toWideCharPointer(), blocks);

	// Update the output table
	m_pTableModel->SetFile(0, true, m_FileToConvert.getFileNameWithoutExtension(), m_NewFile.getFileExtension(), m_NewFile.getFullPathName());
	m_pTableModel->SetFile(1, false, m_FileToConvert.getFileNameWithoutExtension(), m_FileToConvert.getFileExtension(), m_FileToConvert.getFullPathName());

	// release memory
	for (auto pBlock : blocks)
	{
		delete pBlock;
	}
}
