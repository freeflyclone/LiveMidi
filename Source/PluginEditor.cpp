/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
LiveMidiAudioProcessorEditor::LiveMidiAudioProcessorEditor (LiveMidiAudioProcessor& p)
    : AudioProcessorEditor (&p), 
    mAudioProcessor (p)
{
    setResizable(true, true);

    addAndMakeVisible(mGroovesLabel);
    addAndMakeVisible(mGroovesButton);
    mGroovesButton.addListener(this);

    addAndMakeVisible(mBrowser);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    // 
    // SOHN: do setSize() last!
    setSize (800, 400);
}

LiveMidiAudioProcessorEditor::~LiveMidiAudioProcessorEditor()
{
}

//==============================================================================
void LiveMidiAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void LiveMidiAudioProcessorEditor::resized()
{
    Rectangle area = getLocalBounds();
    auto width = area.getWidth();
    auto height = area.getHeight();

	// TODO: contain all these in a Grid or FlexBox

    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor.
    auto text = mGroovesLabel.getText();

    const Font labelFont = mGroovesLabel.getFont();
    const auto textWidth = GlyphArrangement::getStringWidth(labelFont, mGroovesLabel.getText());
    const auto textHeight = labelFont.getHeight();

    mGroovesLabel.setBounds(10, 20, textWidth, textHeight);
    mGroovesButton.setBounds(20 + textWidth, 10, width - textWidth - 30, 32);

    mBrowser.setBounds(10, 60, width - 20, height / 2);
}


void LiveMidiAudioProcessorEditor::buttonClicked(Button* button) {
    if (button == &mGroovesButton) {
        FileChooser chooser("Select folder to browse...", button->getButtonText(), "*.mid", false);

        if (chooser.browseForDirectory()) {
            File f = chooser.getResult();

            button->setButtonText(f.getFullPathName());
            mBrowser.Initialize(f);
        }
    }
}
