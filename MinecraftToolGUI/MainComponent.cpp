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

	addAndMakeVisible(m_SelectFileButton);
	m_SelectFileButton.setButtonText("Select file");
	m_SelectFileButton.onClick = [this]()
	{
		SelectFile();
	};

	addAndMakeVisible(m_SelectedFileLabel);
	m_SelectedFileLabel.setFont(juce::Font(16.0f, juce::Font::bold));
	m_SelectedFileLabel.setText("File to convert:", juce::dontSendNotification);
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
	//m_DataTable.setBounds(0, 0, getWidth(), getHeight());
	m_SelectedFileLabel.setJustificationType(juce::Justification::centred);
	m_SelectedFileLabel.setBounds(10, 20, 0, 0);
	m_InputFile.setBounds(m_SelectedFileLabel.getX() + m_SelectedFileLabel.getWidth(), 10, 300, 30);
	m_SelectFileButton.setBounds(10, 40, 300, 20);
}

void MainComponent::SelectFile()
{
	// the filechooser has to keep existing to make sure it works
	m_upFileChooser = std::make_unique<juce::FileChooser>("Please select the file you want to convert...",
		File::getSpecialLocation(File::userHomeDirectory),
		"*.json");

	// You can add multiple options here with the bitwise AND
	auto chooserFlags = FileBrowserComponent::openMode;


	m_upFileChooser->launchAsync(chooserFlags, [this](const FileChooser& chooser)
		{
			File mooseFile(chooser.getResult());
			m_InputFileName = mooseFile.getFullPathName();
			m_InputFile.setText(m_InputFileName);
		});
}
