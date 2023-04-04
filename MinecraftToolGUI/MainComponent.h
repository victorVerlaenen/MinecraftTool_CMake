#pragma once

#include <JuceHeader.h>
#include "TableModel.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::AnimatedAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void update() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...
    juce::TableListBox m_DataTable;
    TableModel* m_pTableModel;

    // File to convert
    juce::TextButton m_FileToConvertButton;
    juce::Label m_FileToConvertLabel;
    juce::Label m_FileToConvertEditableLabel;
    juce::File m_FileToConvert;

    // Converted file
    juce::TextButton m_NewFileButton;
    juce::Label m_NewFileLabel;
    juce::Label m_NewFileEditableLabel;
    juce::File m_NewFile;

    // Convert button
    juce::TextButton m_ConvertButton;

    std::unique_ptr<juce::FileChooser> m_upFileChooser;

    void SelectFile(bool isSaveLocation = false);
    void ConvertFile();
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
