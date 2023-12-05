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
    addAndMakeVisible(labelBTrackInfo);

    setSize (600, 400);

    setAudioChannels (1, 1);

    deviceManager.addChangeListener (this);

    startTimer (50);
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
                    bTrackFrame.at(sample) = (double)inBuffer[sample];
                }
            }
        }
    }

    bTrack.processAudioFrame(bTrackFrame.data());
    if (bTrack.beatDueInCurrentFrame()) { beatDue = true; }
}


void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}


void MainComponent::resized()
{
    auto rect = getLocalBounds();
    audioSetupComp.setBounds(rect);
    labelBTrackInfo.setBounds(rect.removeFromTop(30));
}


void MainComponent::changeListenerCallback(juce::ChangeBroadcaster*)
{
    initBTrack();
}


void MainComponent::initBTrack()
{
    juce::AudioDeviceManager::AudioDeviceSetup currentAudioSetup;
    deviceManager.getAudioDeviceSetup(currentAudioSetup);

    bTrack.updateHopAndFrameSize(currentAudioSetup.bufferSize / 2, currentAudioSetup.bufferSize);
    bTrackFrame.resize(currentAudioSetup.bufferSize);
    bTrack.setTempo(120);
}


void MainComponent::timerCallback()
{
    auto tempo = bTrack.getCurrentTempoEstimate();

    if (beatDue)
    {
        labelBTrackInfo.setText("X - " + juce::String(tempo, 2), juce::dontSendNotification);
        beatDue = false;
    } else
    {
        labelBTrackInfo.setText("O - " + juce::String(tempo, 2), juce::dontSendNotification);
    }
}
