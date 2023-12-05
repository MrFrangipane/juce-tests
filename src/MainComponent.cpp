#include "MainComponent.h"


MainComponent::MainComponent()
: audioSetupComp (deviceManager,
                  0,
                  256,
                  0,
                  256,
                  false,
                  false,
                  false,
                  false)
{
    addAndMakeVisible (audioSetupComp);
    setSize (600, 400);

    setAudioChannels (2, 2);

    deviceManager.addChangeListener (this);
}


MainComponent::~MainComponent()
{
    shutdownAudio();
}


void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    auto* device = deviceManager.getCurrentAudioDevice();
    auto activeInputChannels = device->getActiveInputChannels();
    auto activeOutputChannels = device->getActiveOutputChannels();
    auto maxInputChannels = activeInputChannels.getHighestBit() + 1;
    auto maxOutputChannels = activeOutputChannels.getHighestBit() + 1;

    for (auto channel = 0; channel < maxOutputChannels; ++channel)
    {
        if ((!activeOutputChannels[channel]) || maxInputChannels == 0)
        {
            bufferToFill.buffer->clear (channel, bufferToFill.startSample, bufferToFill.numSamples);
        }
        else
        {
            auto actualInputChannel = channel % maxInputChannels;

            if (!activeInputChannels[channel])
            {
                bufferToFill.buffer->clear (channel, bufferToFill.startSample, bufferToFill.numSamples);
            }
            else
            {
                auto* inBuffer = bufferToFill.buffer->getReadPointer(actualInputChannel, bufferToFill.startSample);
                auto* outBuffer = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);

                for (auto sample = 0; sample < bufferToFill.numSamples; ++sample)
                {
                    outBuffer[sample] = inBuffer[sample];
                }
            }
        }
    }
}


void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}


void MainComponent::resized()
{
    auto rect = getLocalBounds();
    audioSetupComp.setBounds(rect);
}


void MainComponent::changeListenerCallback(juce::ChangeBroadcaster*)
{
    juce::AudioDeviceManager::AudioDeviceSetup currentAudioSetup;
    deviceManager.getAudioDeviceSetup(currentAudioSetup);
    bTrack.updateHopAndFrameSize(currentAudioSetup.bufferSize / 2, currentAudioSetup.bufferSize);
}
