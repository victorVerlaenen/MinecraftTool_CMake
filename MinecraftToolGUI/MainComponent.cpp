#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
	// Make sure you set the size of the component after
	// you add any child components.
	setSize(500, 300);
	setFramesPerSecond(60); // This sets the frequency of the update calls.

	//addAndMakeVisible(m_DataTable);
   // m_pTableModel = new TableModel();
	//m_DataTable.setModel(m_pTableModel);
	//m_DataTable.getHeader().addColumn("Name", 1, 100, 50, 200);
	//m_DataTable.getHeader().addColumn("x", 2, 50, 20, 60);
	//m_DataTable.getHeader().addColumn("y", 3, 50, 20, 60);
	//m_DataTable.getHeader().addColumn("z", 4, 50, 20, 60);

	// SELECT FILE BUTTON
	addAndMakeVisible(m_SelectFileButton);
	m_SelectFileButton.setButtonText("Browse");
	m_SelectFileButton.onClick = [this]()
	{
		SelectFile();
	};

	// SELECTED FILE LABEL
	addAndMakeVisible(m_SelectedFileEditableLabel);
	m_SelectedFileEditableLabel.setEditable(true);
	m_SelectedFileEditableLabel.setText("C:/", juce::dontSendNotification);
	m_SelectedFileEditableLabel.setColour(juce::Label::textColourId, juce::Colours::white);
	m_SelectedFileEditableLabel.setColour(juce::Label::backgroundColourId, juce::Colours::darkgrey);

	// SELECT FILE LABEL
	addAndMakeVisible(m_SelectedFileLabel);
	m_SelectedFileLabel.setText("File to convert:", juce::dontSendNotification);
	m_SelectedFileLabel.attachToComponent(&m_SelectedFileEditableLabel, true);
	m_SelectedFileLabel.setColour(juce::Label::textColourId, juce::Colours::white);
}

MainComponent::~MainComponent()
{
	//delete m_pTableModel;
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
	m_SelectFileButton.setBounds(320, 15, 100, 20);
	m_SelectedFileEditableLabel.setBounds(110, 15, 200, 20);
}

void MainComponent::SelectFile()
{
	m_upFileChooser = std::make_unique<juce::FileChooser>("Please select the file you want to convert...",
		File::getSpecialLocation(File::userHomeDirectory),
		"*.json");

	// You can add multiple options here with the bitwise AND
	auto chooserFlags = FileBrowserComponent::openMode;

	m_upFileChooser->launchAsync(chooserFlags, [this](const FileChooser& chooser)
		{
			File mooseFile(chooser.getResult());
			m_SelectedFileEditableLabel.setText(mooseFile.getFullPathName(), juce::dontSendNotification);
		});
}
