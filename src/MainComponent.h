#pragma once

#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_audio_utils/juce_audio_utils.h>


class MainComponent final : public juce::AudioAppComponent
{
public:
    MainComponent();
    ~MainComponent() override;

    void prepareToPlay (int, double) override {}
    void getNextAudioBlock(const juce::AudioSourceChannelInfo&) override;
    void releaseResources() override {}

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::AudioDeviceSelectorComponent audioSetupComp;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
