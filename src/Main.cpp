#include "MainComponent.h"

class GuiAppApplication final : public juce::JUCEApplication
{
public:
    GuiAppApplication() {}

    const juce::String getApplicationName() override       { return JUCE_APPLICATION_NAME_STRING; }
    const juce::String getApplicationVersion() override    { return JUCE_APPLICATION_VERSION_STRING; }
    bool moreThanOneInstanceAllowed() override             { return false; }

    void initialise (const juce::String& commandLine) override
    {
        juce::ignoreUnused (commandLine);
        mainWindow.reset (new MainWindow (getApplicationName()));
    }

    void shutdown() override                                { mainWindow = nullptr; }
    void systemRequestedQuit() override                     { quit(); }

    //==============================================================================
    class MainWindow final : public juce::DocumentWindow
    {
    public:
        explicit MainWindow (juce::String name)
            : DocumentWindow (
                name,
                juce::Desktop::getInstance().getDefaultLookAndFeel().findColour (
                    ResizableWindow::backgroundColourId
                ),
                DocumentWindow::allButtons
            )
        {

            setContentOwned (new MainComponent(), true);

           #if JUCE_LINUX
            setFullScreen (true);
            setUsingNativeTitleBar (false);
            setTitleBarHeight (0);
           #else
            setResizable (true, true);
            centreWithSize (getWidth(), getHeight());
            setUsingNativeTitleBar (true);
           #endif

            setVisible (true);
        }

        void closeButtonPressed() override
        {
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

private:
    std::unique_ptr<MainWindow> mainWindow;
};

START_JUCE_APPLICATION (GuiAppApplication)
