/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.3.2

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"

#include "nsfplay/xgm/player/nsf/nsf.h"
#include "nsfplay/xgm/player/nsf/nsfplay.h"
#include "nsfplay/xgm/player/nsf/nsfconfig.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MainComponent  : public AudioAppComponent,
                       public FileDragAndDropTarget,
                       public gin::FileSystemWatcher::Listener,
                       public Thread,
                       public Timer,
                       public Button::Listener,
                       public Slider::Listener
{
public:
    //==============================================================================
    MainComponent ();
    ~MainComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

   	bool isInterestedInFileDrag (const StringArray&) override;
	void folderChanged (const File) override;
	bool newloadNsfFile (const File& file);
	void setMaskCh(int ch, bool mask);
	bool getChMask(int ch);
	void showDeviceSetting()
	{
		AudioDeviceSelectorComponent selector(deviceManager,
											  0, 256,
											  0, 256,
											  true, true,
											  true, false);

		selector.setSize(400, 600);

		DialogWindow::LaunchOptions dialog;
		dialog.content.setNonOwned(&selector);
		dialog.dialogTitle = "Audio/MIDI Device Settings";
		dialog.componentToCentreAround = this;
		dialog.dialogBackgroundColour = getLookAndFeel().findColour(ResizableWindow::backgroundColourId);
		dialog.escapeKeyTriggersCloseButton = true;
		dialog.useNativeTitleBar = false;
		dialog.resizable = false;
		dialog.useBottomRightCornerResizer = false;

		dialog.runModal();
	}
	void run() override;
	void fillBuffer();
	void startRender();
	void timerCallback() override;
	void updateSongInfoView();
	void updateSongNo();
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;
    void filesDropped (const StringArray& filenames, int mouseX, int mouseY) override;
    bool keyPressed (const KeyPress& key) override;

    // Binary resources:
    static const char* play_icon_png;
    static const int play_icon_pngSize;
    static const char* stop_icon_png;
    static const int stop_icon_pngSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	xgm::NSF mNsf;
	xgm::NSFPlayerConfig mConfig;
	xgm::NSFPlayer mPlayer;
	short *mOutBuf;
	uint32_t mOutBufSize;
	uint32_t mOutBufReadPtr;
	uint32_t mOutBufWritePtr;
	uint32_t mSampleBlockSize;
	bool	 mOutBufIsFull;
	WaitableEvent	mBufferFullWait;
	CriticalSection mPlayerMutex;
	double mSampleRate;
	gin::FileSystemWatcher mNsfWatcher;
	File	mLoadedFile;
	Time	mNsfLastModificationTime;
	bool	mChipMute[8];
	uint32_t	mChMask;
	double	mElapsedTime;
	double	mElapsedTimePrev;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<GroupComponent> songinfo;
    std::unique_ptr<Label> engine_verison;
    std::unique_ptr<TextButton> audio_settings;
    std::unique_ptr<Label> title_label;
    std::unique_ptr<Label> artist_label;
    std::unique_ptr<Label> copyright_label;
    std::unique_ptr<Label> soundchip_label;
    std::unique_ptr<Label> song_no;
    std::unique_ptr<ToggleButton> watch;
    std::unique_ptr<Slider> time_slider;
    std::unique_ptr<Label> time_text;
    std::unique_ptr<Slider> song_no_btn;
    std::unique_ptr<ImageButton> play_button;
    std::unique_ptr<ImageButton> stop_button;
    std::unique_ptr<TextButton> file_select_button;
    std::unique_ptr<TextEditor> title;
    std::unique_ptr<TextEditor> artist;
    std::unique_ptr<TextEditor> copyright;
    std::unique_ptr<TextEditor> soundchip;
    std::unique_ptr<TextEditor> file;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
