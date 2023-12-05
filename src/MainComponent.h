#pragma once

#include <vector>
#include "BTrack.h"
#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_audio_utils/juce_audio_utils.h>


class MainComponent final : public juce::AudioAppComponent,
                            public juce::ChangeListener,
                            private juce::Timer
{
public:
    MainComponent();
    ~MainComponent() override;

    void prepareToPlay (int, double) override { initBTrack(); }
    void getNextAudioBlock(const juce::AudioSourceChannelInfo&) override;
    void releaseResources() override {}

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;
    void timerCallback() override;

    void initBTrack();

    juce::AudioDeviceSelectorComponent audioSetupComp;
    juce::Label labelBTrackInfo;

    BTrack bTrack;
    std::vector<double> bTrackFrame;
    bool beatDue=false;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
