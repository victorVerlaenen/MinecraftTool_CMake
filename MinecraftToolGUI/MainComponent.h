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

    juce::TextButton m_SelectFileButton;
    juce::String m_InputFileName{"NoFileSelected"};
    juce::TextEditor m_InputFile;
    juce::Label m_SelectedFileLabel;

    std::unique_ptr<juce::FileChooser> m_upFileChooser;

    void SelectFile();
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
