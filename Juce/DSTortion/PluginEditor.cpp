/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DstortionAudioProcessorEditor::DstortionAudioProcessorEditor (DstortionAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
	addAndMakeVisible(driveKnob = new Slider("Drive"));
	driveKnob->setSliderStyle(Slider::Rotary);
	driveKnob->setTextBoxStyle(Slider::NoTextBox, false, 100, 100);
	driveKnob->setColour(Slider::rotarySliderOutlineColourId, Colours::white);
	driveKnob->setColour(Slider::thumbColourId, Colours::white);
	driveKnob->setColour(Slider::rotarySliderFillColourId, Colours::black);

	addAndMakeVisible(rangeKnob = new Slider("Range"));
	rangeKnob->setSliderStyle(Slider::Rotary);
	rangeKnob->setTextBoxStyle(Slider::NoTextBox, false, 100, 100);
	rangeKnob->setColour(Slider::rotarySliderOutlineColourId, Colours::white);
	rangeKnob->setColour(Slider::thumbColourId, Colours::white);
	rangeKnob->setColour(Slider::rotarySliderFillColourId, Colours::black);

	addAndMakeVisible(blendKnob = new Slider("Blend"));
	blendKnob->setSliderStyle(Slider::Rotary);
	blendKnob->setTextBoxStyle(Slider::NoTextBox, false, 100, 100);
	blendKnob->setColour(Slider::rotarySliderOutlineColourId, Colours::white);
	blendKnob->setColour(Slider::thumbColourId, Colours::white);
	blendKnob->setColour(Slider::rotarySliderFillColourId, Colours::black);

	addAndMakeVisible(typeKnob = new Slider("Type"));
	typeKnob->setSliderStyle(Slider::LinearVertical);
	typeKnob->setTextBoxStyle(Slider::NoTextBox, false, 100, 100);
	typeKnob->setColour(Slider::rotarySliderOutlineColourId, Colours::white);
	typeKnob->setColour(Slider::thumbColourId, Colours::white);
	typeKnob->setColour(Slider::rotarySliderFillColourId, Colours::black);

	addAndMakeVisible(volumeKnob = new Slider("Volume"));
	volumeKnob->setSliderStyle(Slider::Rotary);
	volumeKnob->setTextBoxStyle(Slider::NoTextBox, false, 100, 100);
	volumeKnob->setColour(Slider::rotarySliderOutlineColourId, Colours::white);
	volumeKnob->setColour(Slider::thumbColourId, Colours::white);
	volumeKnob->setColour(Slider::rotarySliderFillColourId, Colours::black);

	


	driveAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "drive", *driveKnob);
	rangeAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "range", *rangeKnob);
	blendAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "blend", *blendKnob);
	typeAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "type", *typeKnob);
	volumeAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "volume", *volumeKnob);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 200);
}

DstortionAudioProcessorEditor::~DstortionAudioProcessorEditor()
{
}

//==============================================================================
void DstortionAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::darkred);

    g.setColour (Colours::black);
    g.setFont (15.0f);

	g.drawText("Drive", ((getWidth() / 6) * 1) - (100 / 2), (getHeight() / 2) - (100 / 2) + 5, 100, 100, Justification::centred, false);
	g.drawText("Range", ((getWidth() / 6) * 2) - (100 / 2), (getHeight() / 2) - (100 / 2) + 5, 100, 100, Justification::centred, false);
	g.drawText("Mix", ((getWidth() / 6) * 3) - (100 / 2), (getHeight() / 2) - (100 / 2) + 5, 100, 100, Justification::centred, false);
	
	g.drawText("Volume", ((getWidth() / 6) * 5) - (100 / 2), (getHeight() / 2) - (100 / 2) + 5, 100, 100, Justification::centred, false);
}

void DstortionAudioProcessorEditor::resized()
{
	driveKnob->setBounds(((getWidth() / 6) * 1) - (100 / 2), (getHeight() / 2) - (100 / 2), 100, 100);
	rangeKnob->setBounds(((getWidth() / 6) * 2) - (100 / 2), (getHeight() / 2) - (100 / 2), 100, 100);
	blendKnob->setBounds(((getWidth() / 6) * 3) - (100 / 2), (getHeight() / 2) - (100 / 2), 100, 100);
	typeKnob->setBounds(((getWidth() / 6) * 4) - (100 / 2), (getHeight() / 2) - (100 / 2), 100, 100);
	volumeKnob->setBounds(((getWidth() / 6) * 5) - (100 / 2), (getHeight() / 2) - (100 / 2), 100, 100);
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
