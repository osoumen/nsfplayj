/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.3.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
#include "nsfplay/xgm/version.h"
//[/Headers]

#include "MainComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#if JUCE_MAC
#define NO_THREAD
#endif
static const int RENDER_BUFFER_MULTIPLIER = 3;
static const int VIEW_UPDATE_RATE_HZ = 60;
//[/MiscUserDefs]

//==============================================================================
MainComponent::MainComponent ()
    : Thread("render")
{
    //[Constructor_pre] You can add your own custom stuff here..
    mOutBuf = nullptr;
    mOutBufSize = 0;
	mOutBufReadPtr = 0;
	mOutBufWritePtr = 0;
	mOutBufIsFull = false;
    //[/Constructor_pre]

    addAndMakeVisible (songinfo = new GroupComponent ("song info",
                                                      TRANS("NSF Header Infomation")));

    addAndMakeVisible (engine_verison = new Label ("engine version",
                                                   TRANS("version")));
    engine_verison->setFont (Font (14.00f, Font::plain).withTypefaceStyle ("Regular").withExtraKerningFactor (0.111f));
    engine_verison->setJustificationType (Justification::centredRight);
    engine_verison->setEditable (false, false, false);
    engine_verison->setColour (TextEditor::textColourId, Colours::black);
    engine_verison->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (audio_settings = new TextButton ("Audio settings"));
    audio_settings->setButtonText (TRANS("Audio settings..."));
    audio_settings->addListener (this);

    addAndMakeVisible (title_label = new Label ("title label",
                                                TRANS("Title")));
    title_label->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    title_label->setJustificationType (Justification::centredRight);
    title_label->setEditable (false, false, false);
    title_label->setColour (TextEditor::textColourId, Colours::black);
    title_label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    title_label->setBounds (16, 72, 80, 24);

    addAndMakeVisible (artist_label = new Label ("artist label",
                                                 TRANS("Artist")));
    artist_label->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    artist_label->setJustificationType (Justification::centredRight);
    artist_label->setEditable (false, false, false);
    artist_label->setColour (TextEditor::textColourId, Colours::black);
    artist_label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    artist_label->setBounds (16, 104, 80, 24);

    addAndMakeVisible (copyright_label = new Label ("copyright label",
                                                    TRANS("Copyright")));
    copyright_label->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    copyright_label->setJustificationType (Justification::centredRight);
    copyright_label->setEditable (false, false, false);
    copyright_label->setColour (TextEditor::textColourId, Colours::black);
    copyright_label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    copyright_label->setBounds (16, 136, 80, 24);

    addAndMakeVisible (soundchip_label = new Label ("soundchip label",
                                                    TRANS("Soundchip")));
    soundchip_label->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    soundchip_label->setJustificationType (Justification::centredRight);
    soundchip_label->setEditable (false, false, false);
    soundchip_label->setColour (TextEditor::textColourId, Colours::black);
    soundchip_label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    soundchip_label->setBounds (16, 168, 80, 24);

    addAndMakeVisible (song_no = new Label ("song_no",
                                            String()));
    song_no->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    song_no->setJustificationType (Justification::centred);
    song_no->setEditable (false, false, false);
    song_no->setColour (Label::outlineColourId, Colour (0x00ffffff));
    song_no->setColour (TextEditor::textColourId, Colours::black);
    song_no->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (watch = new ToggleButton ("watch button"));
    watch->setButtonText (TRANS("watch"));
    watch->addListener (this);
    watch->setToggleState (true, dontSendNotification);

    addAndMakeVisible (time_slider = new Slider ("time slider"));
    time_slider->setRange (0, 10, 0);
    time_slider->setSliderStyle (Slider::LinearHorizontal);
    time_slider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    time_slider->addListener (this);

    addAndMakeVisible (time_text = new Label ("time text",
                                              TRANS("--:--")));
    time_text->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    time_text->setJustificationType (Justification::centred);
    time_text->setEditable (false, false, false);
    time_text->setColour (TextEditor::textColourId, Colours::black);
    time_text->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (song_no_btn = new Slider ("song no button"));
    song_no_btn->setRange (0, 10, 1);
    song_no_btn->setSliderStyle (Slider::IncDecButtons);
    song_no_btn->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    song_no_btn->addListener (this);

    addAndMakeVisible (play_button = new ImageButton ("play button"));
    play_button->setButtonText (TRANS("play"));
    play_button->addListener (this);

    play_button->setImages (false, true, true,
                            ImageCache::getFromMemory (play_icon_png, play_icon_pngSize), 1.000f, Colour (0x00000000),
                            Image(), 1.000f, Colour (0x00000000),
                            Image(), 1.000f, Colour (0x00000000));
    play_button->setBounds (16, 218, 20, 20);

    addAndMakeVisible (stop_button = new ImageButton ("stop button"));
    stop_button->setButtonText (TRANS("stop"));
    stop_button->addListener (this);

    stop_button->setImages (false, true, true,
                            ImageCache::getFromMemory (stop_icon_png, stop_icon_pngSize), 1.000f, Colour (0x00000000),
                            Image(), 1.000f, Colour (0x00000000),
                            Image(), 1.000f, Colour (0x00000000));
    stop_button->setBounds (40, 218, 20, 20);

    addAndMakeVisible (file_select_button = new TextButton ("file select button"));
    file_select_button->setButtonText (TRANS("..."));
    file_select_button->addListener (this);

    addAndMakeVisible (title = new TextEditor ("title"));
    title->setMultiLine (false);
    title->setReturnKeyStartsNewLine (false);
    title->setReadOnly (true);
    title->setScrollbarsShown (true);
    title->setCaretVisible (false);
    title->setPopupMenuEnabled (true);
    title->setText (String());

    addAndMakeVisible (artist = new TextEditor ("artist"));
    artist->setMultiLine (false);
    artist->setReturnKeyStartsNewLine (false);
    artist->setReadOnly (true);
    artist->setScrollbarsShown (true);
    artist->setCaretVisible (false);
    artist->setPopupMenuEnabled (true);
    artist->setText (String());

    addAndMakeVisible (copyright = new TextEditor ("copyright"));
    copyright->setMultiLine (false);
    copyright->setReturnKeyStartsNewLine (false);
    copyright->setReadOnly (true);
    copyright->setScrollbarsShown (true);
    copyright->setCaretVisible (false);
    copyright->setPopupMenuEnabled (true);
    copyright->setText (String());

    addAndMakeVisible (soundchip = new TextEditor ("soundchip"));
    soundchip->setMultiLine (false);
    soundchip->setReturnKeyStartsNewLine (false);
    soundchip->setReadOnly (true);
    soundchip->setScrollbarsShown (true);
    soundchip->setCaretVisible (false);
    soundchip->setPopupMenuEnabled (true);
    soundchip->setText (String());

    addAndMakeVisible (file = new TextEditor ("file"));
    file->setMultiLine (false);
    file->setReturnKeyStartsNewLine (false);
    file->setReadOnly (true);
    file->setScrollbarsShown (true);
    file->setCaretVisible (false);
    file->setPopupMenuEnabled (true);
    file->setText (String());


    //[UserPreSize]
	engine_verison->setText(NSFPLAY_TITLE, dontSendNotification);
	time_slider->setChangeNotificationOnlyOnRelease(true);
    //[/UserPreSize]

    setSize (400, 280);


    //[Constructor] You can add your own custom stuff here..
    setAudioChannels (0, 2);

	// TODO: 設定を読み込む、無ければデフォルトを設定する
	mConfig.SetValue("LPF", 40);
	mConfig.SetValue("HPF", 255);
	mConfig.SetValue("MASTER_VOLUME", 256);
	mConfig.SetValue("FDS_OPTION1", 0);
	mConfig.SetValue("FDS_OPTION2", 1);
	mConfig.SetValue("STOP_SEC", 5);
//	mConfig.SetValue("AUTO_DETECT", 0);
//	mConfig.SetValue("AUTO_STOP", 0);

#if (!JUCE_WINDOWS && !JUCE_MAC)
	mConfig.SetValue("APU1_QUALITY", 1);
	mConfig.SetValue("APU2_QUALITY", 1);
	mConfig.SetValue("5B_QUALITY", 1);
	mConfig.SetValue("MMC5_QUALITY", 1);
	mConfig.SetValue("N163_QUALITY", 1);
	mConfig.SetValue("VRC6_QUALITY", 1);
	mConfig.SetValue("VRC7_QUALITY", 1);
	mConfig.SetValue("FDS_QUALITY", 1);
#endif

	mPlayer.SetConfig(&mConfig);

	mNsfWatcher.addListener(this);
	setWantsKeyboardFocus(true);

	for (int i=0; i<8; ++i) {
		mChipMute[i] = false;
	}
	mChMask = 0;

	startTimerHz(VIEW_UPDATE_RATE_HZ);
    //[/Constructor]
}

MainComponent::~MainComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	if (isTimerRunning()) {
		stopTimer();
	}
    //[/Destructor_pre]

    songinfo = nullptr;
    engine_verison = nullptr;
    audio_settings = nullptr;
    title_label = nullptr;
    artist_label = nullptr;
    copyright_label = nullptr;
    soundchip_label = nullptr;
    song_no = nullptr;
    watch = nullptr;
    time_slider = nullptr;
    time_text = nullptr;
    song_no_btn = nullptr;
    play_button = nullptr;
    stop_button = nullptr;
    file_select_button = nullptr;
    title = nullptr;
    artist = nullptr;
    copyright = nullptr;
    soundchip = nullptr;
    file = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
	mNsfWatcher.removeListener(this);
#ifndef NO_THREAD
	if (isThreadRunning()) {
		signalThreadShouldExit();
	}
	mBufferFullWait.signal();
	waitForThreadToExit(-1);
#endif
	shutdownAudio();
    //[/Destructor]
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MainComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    songinfo->setBounds (8, 48, getWidth() - 22, 160);
    engine_verison->setBounds (getWidth() - 4 - 176, getHeight() - -1 - 24, 176, 24);
    audio_settings->setBounds (8, getHeight() - 7 - 24, 120, 24);
    song_no->setBounds (getWidth() - 53 - 48, 216, 48, 24);
    watch->setBounds (getWidth() - 7 - 71, 16, 71, 24);
    time_slider->setBounds (64, 216, getWidth() - 197, 24);
    time_text->setBounds (getWidth() - 101 - 40, 216, 40, 24);
    song_no_btn->setBounds (getWidth() - 14 - 39, 216, 39, 24);
    file_select_button->setBounds (getWidth() - 78 - 32, 16, 32, 24);
    title->setBounds (104, 72, getWidth() - 133, 24);
    artist->setBounds (104, 104, getWidth() - 133, 24);
    copyright->setBounds (104, 136, getWidth() - 133, 24);
    soundchip->setBounds (104, 168, getWidth() - 133, 24);
    file->setBounds (16, 16, getWidth() - 125, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MainComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == audio_settings)
    {
        //[UserButtonCode_audio_settings] -- add your button handler code here..
		showDeviceSetting();
        //[/UserButtonCode_audio_settings]
    }
    else if (buttonThatWasClicked == watch)
    {
        //[UserButtonCode_watch] -- add your button handler code here..
        //[/UserButtonCode_watch]
    }
    else if (buttonThatWasClicked == play_button)
    {
        //[UserButtonCode_play_button] -- add your button handler code here..
		GenericScopedLock<CriticalSection> lock(mPlayerMutex);
		{
			mNsf.time_in_ms = -1;
			mNsf.loop_in_ms = -1;
			mNsf.fade_in_ms = -1;
			mNsf.loop_num = -1;
			mPlayer.Reset();
		}
		mElapsedTime = .0;
		mElapsedTimePrev = -1.;
		startRender();
        //[/UserButtonCode_play_button]
    }
    else if (buttonThatWasClicked == stop_button)
    {
        //[UserButtonCode_stop_button] -- add your button handler code here..
		mPlayer.FadeOut(0);
        //[/UserButtonCode_stop_button]
    }
    else if (buttonThatWasClicked == file_select_button)
    {
        //[UserButtonCode_file_select_button] -- add your button handler code here..
		FileChooser chooser("Choose NSF File..", File(), "*.nsf");
		chooser.browseForFileToOpen();
		filesDropped(chooser.getResult().getFullPathName(), 0, 0);
        //[/UserButtonCode_file_select_button]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void MainComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == time_slider)
    {
        //[UserSliderCode_time_slider] -- add your slider handling code here..
		if (!mPlayer.IsStopped()) {
			if (time_slider->getValue() > mElapsedTime) {
				GenericScopedLock<CriticalSection> lock(mPlayerMutex);
				mPlayer.Skip((time_slider->getValue() - mElapsedTime) * mSampleRate);
			}
			else {
				GenericScopedLock<CriticalSection> lock(mPlayerMutex);
				mPlayer.Reset();
				mPlayer.Skip(time_slider->getValue() * mSampleRate);
			}
			mElapsedTime = time_slider->getValue();
			mElapsedTimePrev = mElapsedTime - 1.0;
		}
        //[/UserSliderCode_time_slider]
    }
    else if (sliderThatWasMoved == song_no_btn)
    {
        //[UserSliderCode_song_no_btn] -- add your slider handling code here..
		if (mNsf.GetSongNum() > 1) {
			GenericScopedLock<CriticalSection> lock(mPlayerMutex);
			mPlayer.SetSong(song_no_btn->getValue());
			{
				mNsf.time_in_ms = -1;
				mNsf.loop_in_ms = -1;
				mNsf.fade_in_ms = -1;
				mNsf.loop_num = -1;
				mPlayer.Reset();
			}
			mElapsedTime = .0;
			mElapsedTimePrev = -1.;
			startRender();
			updateSongNo();
			repaint();
		}
        //[/UserSliderCode_song_no_btn]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void MainComponent::filesDropped (const StringArray& filenames, int mouseX, int mouseY)
{
    //[UserCode_filesDropped] -- Add your code here...
    String path(filenames[0]);
	if (path.startsWithChar('"')) {
		path = path.substring(1, path.length()-1);
	}
	File oldFile = mLoadedFile;
	if (newloadNsfFile (path)) {
		mNsfWatcher.removeFolder(oldFile.getParentDirectory());
		if (watch->getToggleState()) {
			mNsfWatcher.addFolder(mLoadedFile.getParentDirectory());
		}
		file->setText(path, dontSendNotification);
		fillBuffer();
		startRender();
		repaint();
	}
    //[/UserCode_filesDropped]
}

bool MainComponent::keyPressed (const KeyPress& key)
{
    //[UserCode_keyPressed] -- Add your code here...
    if (!mLoadedFile.exists()) {
		return false;
	}

	if (key == juce::KeyPress::upKey) {
		play_button->triggerClick();
		return true;
	}
	if (key == juce::KeyPress::downKey) {
		stop_button->triggerClick();
		return true;
	}
	if (key == juce::KeyPress::leftKey) {
		song_no_btn->setValue(mPlayer.GetSong()-1, sendNotification);
		return true;
	}
	if (key == juce::KeyPress::rightKey) {
		song_no_btn->setValue(mPlayer.GetSong()+1, sendNotification);
		return true;
	}

	if (key.getKeyCode() >= '1' && key.getKeyCode() <= '8') {
		int chip = key.getKeyCode() - '1';
		mChipMute[chip] = !mChipMute[chip];
		String param(xgm::NSFPlayerConfig::dname[chip]);
		param += "_MUTE";
		mConfig.SetValue(param.toStdString(), mChipMute[chip]?1:0);
		mPlayer.SetConfig(&mConfig);
		mPlayer.Notify(chip);
		return true;
	}

	if (key.getKeyCode() == 'Q') {
		setMaskCh(0, !getChMask(0));
		return true;
	}
	if (key.getKeyCode() == 'W') {
		setMaskCh(1, !getChMask(1));
		return true;
	}
	if (key.getKeyCode() == 'E') {
		setMaskCh(2, !getChMask(2));
		return true;
	}
	if (key.getKeyCode() == 'R') {
		setMaskCh(3, !getChMask(3));
		return true;
	}
	if (key.getKeyCode() == 'T') {
		setMaskCh(4, !getChMask(4));
		return true;
	}

	return false;
    //[/UserCode_keyPressed]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()

	mSampleRate = sampleRate;

	{
		GenericScopedLock<CriticalSection> lock(mPlayerMutex);
		mSampleBlockSize = samplesPerBlockExpected;
#ifndef NO_THREAD
		mOutBufSize = samplesPerBlockExpected * RENDER_BUFFER_MULTIPLIER;
#else
		mOutBufSize = samplesPerBlockExpected;
#endif
		if (mOutBuf)
			delete [] mOutBuf;
		mOutBuf = new short[mOutBufSize];
	}

	if (newloadNsfFile (mLoadedFile)) {
		fillBuffer();
		startRender();
	}
}

void MainComponent::fillBuffer()
{
	if ((mPlayer.GetLength() > 0) && !mPlayer.IsStopped() && (mOutBufSize > 0)) {
		GenericScopedLock<CriticalSection> lock(mPlayerMutex);
		mPlayer.Render(mOutBuf, mOutBufSize);
#ifndef NO_THREAD
		mOutBufReadPtr = 0;
		mOutBufWritePtr = 0;
#endif
		mOutBufIsFull = true;
	}
}

void MainComponent::startRender()
{
#ifndef NO_THREAD
	if (!isThreadRunning()) {
		startThread(realtimeAudioPriority);
	}
#endif
}

void MainComponent::run()
{
	while (!threadShouldExit()) {
		bool isStopped = false;
		{
			GenericScopedLock<CriticalSection> lock(mPlayerMutex);
			if ((mPlayer.GetLength() > 0) && !mPlayer.IsStopped() && (mOutBufSize > 0)) {
				if (!mOutBufIsFull) {
					int to_write = (mOutBufReadPtr > mOutBufWritePtr) ?
									(mOutBufReadPtr - mOutBufWritePtr):
									(mOutBufReadPtr - mOutBufWritePtr + mOutBufSize);
					if (to_write > mSampleBlockSize) to_write = mSampleBlockSize;
					mPlayer.Render(&mOutBuf[mOutBufWritePtr], to_write);
					mOutBufWritePtr = (mOutBufWritePtr + to_write) % mOutBufSize;
					if (mOutBufWritePtr == mOutBufReadPtr) {
						mOutBufIsFull = true;
					}
				}
				if (mPlayer.IsStopped()) {
					isStopped = true;
				}
			}
		}
		if (isStopped) {
			mElapsedTime = .0;
			mElapsedTimePrev = -1.;
			if (mPlayer.IsDetected()) {
				const MessageManagerLock mmLock;
				song_no_btn->setValue(mPlayer.GetSong()+1, sendNotification);
			}
			break;
		}
		if (mOutBufIsFull) {
			mBufferFullWait.wait();
		}
	}
}

void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
	bufferToFill.clearActiveBufferRegion();

#ifndef NO_THREAD
	bool isBufferReady = ((mOutBufWritePtr != mOutBufReadPtr)?true:false)
						|| mOutBufIsFull;
	short *readPtr = &mOutBuf[mOutBufReadPtr];
#else
	if (!mOutBufIsFull) {
		fillBuffer();
		if (mPlayer.IsStopped() && mOutBufIsFull) {
			mElapsedTime = .0;
			mElapsedTimePrev = -1.;
			if (mPlayer.IsDetected()) {
				const MessageManagerLock mmLock;
				song_no_btn->setValue(mPlayer.GetSong()+1, sendNotification);
			}
		}
	}
	bool isBufferReady = mOutBufIsFull;
	short *readPtr = mOutBuf;
#endif
	if (isBufferReady) {
		auto buffer = bufferToFill.buffer;
		for (int ch=0; ch<bufferToFill.buffer->getNumChannels(); ++ch) {
			float* channelData = buffer->getWritePointer(ch);
			for (int i=0; i<buffer->getNumSamples(); ++i) {
				channelData[i] = readPtr[i] / 32768.0f;
			}
		}
#ifndef NO_THREAD
		//assert(buffer->getNumSamples() == mSampleBlockSize);
		mOutBufReadPtr = (mOutBufReadPtr + mSampleBlockSize) % mOutBufSize;
		if (mOutBufIsFull) {
			mOutBufIsFull = false;
			mBufferFullWait.signal();
		}
#else
		mOutBufIsFull = false;
#endif
		mElapsedTime += mSampleBlockSize / mSampleRate;
	}
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
	if (mOutBuf) {
		GenericScopedLock<CriticalSection> lock(mPlayerMutex);
		delete [] mOutBuf;
		mOutBuf = nullptr;
		mOutBufSize = 0;
	}
}

void MainComponent::setMaskCh(int ch, bool mask)
{
	if (mask) {
		mChMask |= 1 << ch;
	}
	else {
		mChMask &= ~(1 << ch);
	}
	mConfig.SetValue("MASK", mChMask);
	mPlayer.SetConfig(&mConfig);
	for (int i=0; i<xgm::NES_DEVICE_MAX; ++i) {
		mPlayer.Notify(i);
	}
}

bool MainComponent::getChMask(int ch)
{
	return (mChMask & (1 << ch))?true:false;
}

void MainComponent::folderChanged (const File)
{
	if (watch->getToggleState()) {
		if (mLoadedFile.exists()) {
			if (mNsfLastModificationTime != mLoadedFile.getLastModificationTime()) {
				if (newloadNsfFile(mLoadedFile)) {
					fillBuffer();
					startRender();
				}
			}
		}
	}
}

bool MainComponent::newloadNsfFile (const File& file)
{
	if (file.exists() && mNsf.LoadFile(file.getFullPathName().toRawUTF8())) {
		mPlayer.FadeOut(0);
		{
			GenericScopedLock<CriticalSection> lock(mPlayerMutex);
			mPlayer.Load(&mNsf);
			mPlayer.SetPlayFreq(mSampleRate);
			if (mLoadedFile != file) {
				mLoadedFile = file;
			}
			mNsfLastModificationTime = mLoadedFile.getLastModificationTime();
			mPlayer.Reset();
			mPlayer.SetSong(0);

			updateSongInfoView();
			mElapsedTime = .0;
			mElapsedTimePrev = -1.;
		}
		return true;
	}
	return false;
}

bool MainComponent::isInterestedInFileDrag (const StringArray&)
{
	return true;
}

void MainComponent::timerCallback()
{
	if ((mElapsedTime - mElapsedTimePrev) >= 1.0) {
		int elapsedSecs = static_cast<int>(mElapsedTime);
		String timerValue = String::formatted("%d:%02d", elapsedSecs / 60, elapsedSecs % 60);
		if (time_text->getText() != timerValue) {
			time_text->setText(timerValue, dontSendNotification);
			time_text->repaint();

			if (!time_slider->isMouseButtonDown()) {
				time_slider->setValue(mElapsedTime, dontSendNotification);
				time_slider->repaint();
			}
		}
		mElapsedTimePrev = mElapsedTime;
	}
}

void MainComponent::updateSongInfoView()
{
	if (mLoadedFile.exists()) {
		title->setText(String(CharPointer_UTF8(mNsf.title)), dontSendNotification);
		artist->setText(String(CharPointer_UTF8(mNsf.artist)), dontSendNotification);
		copyright->setText(String(CharPointer_UTF8(mNsf.copyright)), dontSendNotification);
		String soundchipStr;
		if (mNsf.soundchip & 1)
			soundchipStr += "VRC6 ";
		if (mNsf.soundchip & 2)
			soundchipStr += "VRC7 ";
		if (mNsf.soundchip & 4)
			soundchipStr += "FDS ";
		if (mNsf.soundchip & 8)
			soundchipStr += "MMC5 ";
		if (mNsf.soundchip & 16)
			soundchipStr += "N163 ";
		if (mNsf.soundchip & 32)
			soundchipStr += "5B ";
		if (mNsf.pal_ntsc & 1) {
			soundchipStr += "PAL ";
		}
		else {
			soundchipStr += "NTSC ";
		}
		if (mNsf.pal_ntsc & 2) {
			soundchipStr += "Dual PAL & NTSC Mode";
		}
		soundchip->setText(soundchipStr, dontSendNotification);

		time_slider->setRange(0, mPlayer.GetLength() / 1000);
		if (mNsf.GetSongNum() > 1) {
			song_no_btn->setRange(0, mNsf.GetSongNum()-1, 1);
		}

		updateSongNo();
	}
}

void MainComponent::updateSongNo()
{
	if (mLoadedFile.exists()) {
		String songnoStr;
		songnoStr += String(mPlayer.GetSong()+1);
		songnoStr += "/";
		songnoStr += String(mNsf.GetSongNum());
		song_no->setText(songnoStr, dontSendNotification);
	}
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainComponent" componentName=""
                 parentClasses="public AudioAppComponent, public FileDragAndDropTarget, public gin::FileSystemWatcher::Listener, public Thread, public Timer"
                 constructorParams="" variableInitialisers="Thread(&quot;render&quot;)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="400" initialHeight="280">
  <METHODS>
    <METHOD name="filesDropped (const StringArray&amp; filenames, int mouseX, int mouseY)"/>
    <METHOD name="keyPressed (const KeyPress&amp; key)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ff323e44"/>
  <GROUPCOMPONENT name="song info" id="1c9a446e991706fc" memberName="songinfo"
                  virtualName="" explicitFocusOrder="0" pos="8 48 22M 160" title="NSF Header Infomation"/>
  <LABEL name="engine version" id="5cc22a9a49c7c05a" memberName="engine_verison"
         virtualName="" explicitFocusOrder="0" pos="4Rr -1Rr 176 24" edTextCol="ff000000"
         edBkgCol="0" labelText="version" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="14.00000000000000000000"
         kerning="0.11100000000000000144" bold="0" italic="0" justification="34"/>
  <TEXTBUTTON name="Audio settings" id="1c1a6e226df9be27" memberName="audio_settings"
              virtualName="" explicitFocusOrder="0" pos="8 7Rr 120 24" buttonText="Audio settings..."
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="title label" id="44105956cc3354f0" memberName="title_label"
         virtualName="" explicitFocusOrder="0" pos="16 72 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Title" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.00000000000000000000"
         kerning="0.00000000000000000000" bold="0" italic="0" justification="34"/>
  <LABEL name="artist label" id="90aec584bcfa74bd" memberName="artist_label"
         virtualName="" explicitFocusOrder="0" pos="16 104 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Artist" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.00000000000000000000"
         kerning="0.00000000000000000000" bold="0" italic="0" justification="34"/>
  <LABEL name="copyright label" id="d12e9a42483791ed" memberName="copyright_label"
         virtualName="" explicitFocusOrder="0" pos="16 136 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Copyright" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.00000000000000000000"
         kerning="0.00000000000000000000" bold="0" italic="0" justification="34"/>
  <LABEL name="soundchip label" id="93632d61cdc41217" memberName="soundchip_label"
         virtualName="" explicitFocusOrder="0" pos="16 168 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Soundchip" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.00000000000000000000"
         kerning="0.00000000000000000000" bold="0" italic="0" justification="34"/>
  <LABEL name="song_no" id="9b9464454fe1674" memberName="song_no" virtualName=""
         explicitFocusOrder="0" pos="53Rr 216 48 24" outlineCol="ffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="36"/>
  <TOGGLEBUTTON name="watch button" id="1d26f09c50bab78f" memberName="watch"
                virtualName="" explicitFocusOrder="0" pos="7Rr 16 71 24" buttonText="watch"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="1"/>
  <SLIDER name="time slider" id="9703246e15662f1d" memberName="time_slider"
          virtualName="" explicitFocusOrder="0" pos="64 216 197M 24" min="0.00000000000000000000"
          max="10.00000000000000000000" int="0.00000000000000000000" style="LinearHorizontal"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.00000000000000000000" needsCallback="1"/>
  <LABEL name="time text" id="7fcf63d02d632d6" memberName="time_text"
         virtualName="" explicitFocusOrder="0" pos="101Rr 216 40 24" edTextCol="ff000000"
         edBkgCol="0" labelText="--:--" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.00000000000000000000"
         kerning="0.00000000000000000000" bold="0" italic="0" justification="36"/>
  <SLIDER name="song no button" id="666ac98a4f8639ab" memberName="song_no_btn"
          virtualName="" explicitFocusOrder="0" pos="14Rr 216 39 24" min="0.00000000000000000000"
          max="10.00000000000000000000" int="1.00000000000000000000" style="IncDecButtons"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.00000000000000000000" needsCallback="1"/>
  <IMAGEBUTTON name="play button" id="25c0f6239c7fd518" memberName="play_button"
               virtualName="" explicitFocusOrder="0" pos="16 218 20 20" buttonText="play"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="play_icon_png" opacityNormal="1.00000000000000000000"
               colourNormal="0" resourceOver="" opacityOver="1.00000000000000000000"
               colourOver="0" resourceDown="" opacityDown="1.00000000000000000000"
               colourDown="0"/>
  <IMAGEBUTTON name="stop button" id="8342368829eecb9b" memberName="stop_button"
               virtualName="" explicitFocusOrder="0" pos="40 218 20 20" buttonText="stop"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="stop_icon_png" opacityNormal="1.00000000000000000000"
               colourNormal="0" resourceOver="" opacityOver="1.00000000000000000000"
               colourOver="0" resourceDown="" opacityDown="1.00000000000000000000"
               colourDown="0"/>
  <TEXTBUTTON name="file select button" id="a64a44d4bb69d6ce" memberName="file_select_button"
              virtualName="" explicitFocusOrder="0" pos="78Rr 16 32 24" buttonText="..."
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTEDITOR name="title" id="3c531f4860e13949" memberName="title" virtualName=""
              explicitFocusOrder="0" pos="104 72 133M 24" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="1" scrollbars="1" caret="0" popupmenu="1"/>
  <TEXTEDITOR name="artist" id="b3cd98d7e686820e" memberName="artist" virtualName=""
              explicitFocusOrder="0" pos="104 104 133M 24" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="1" scrollbars="1" caret="0" popupmenu="1"/>
  <TEXTEDITOR name="copyright" id="70fbb403242f2b91" memberName="copyright"
              virtualName="" explicitFocusOrder="0" pos="104 136 133M 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="1" scrollbars="1"
              caret="0" popupmenu="1"/>
  <TEXTEDITOR name="soundchip" id="9c811861217d0264" memberName="soundchip"
              virtualName="" explicitFocusOrder="0" pos="104 168 133M 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="1" scrollbars="1"
              caret="0" popupmenu="1"/>
  <TEXTEDITOR name="file" id="ba9225b28ab29a15" memberName="file" virtualName=""
              explicitFocusOrder="0" pos="16 16 125M 24" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="1" scrollbars="1" caret="0" popupmenu="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//==============================================================================
// Binary resources - be careful not to edit any of these sections!

// JUCER_RESOURCE: play_icon_png, 156, "../play_icon.png"
static const unsigned char resource_MainComponent_play_icon_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,16,0,0,0,16,8,6,0,0,0,31,243,255,97,0,0,0,9,112,72,89,115,0,0,11,19,0,0,11,19,
1,0,154,156,24,0,0,0,78,73,68,65,84,56,141,205,210,49,14,0,32,8,3,64,107,252,255,151,117,113,64,8,161,117,162,171,246,136,193,49,218,100,223,168,61,88,224,57,0,16,175,11,0,11,149,64,5,209,64,6,77,166,
100,227,7,201,128,143,12,248,39,172,223,34,13,84,107,76,1,246,35,5,128,45,246,201,1,153,144,28,35,33,22,72,6,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* MainComponent::play_icon_png = (const char*) resource_MainComponent_play_icon_png;
const int MainComponent::play_icon_pngSize = 156;

// JUCER_RESOURCE: stop_icon_png, 120, "../stop_icon.png"
static const unsigned char resource_MainComponent_stop_icon_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,16,0,0,0,16,8,6,0,0,0,31,243,255,97,0,0,0,9,112,72,89,115,0,0,11,19,0,0,11,19,
1,0,154,156,24,0,0,0,42,73,68,65,84,56,141,99,96,24,104,192,8,99,252,255,255,255,63,73,26,25,25,25,25,24,24,24,152,40,117,193,168,1,163,6,12,14,3,6,30,0,0,66,96,4,24,249,92,175,255,0,0,0,0,73,69,78,68,
174,66,96,130,0,0};

const char* MainComponent::stop_icon_png = (const char*) resource_MainComponent_stop_icon_png;
const int MainComponent::stop_icon_pngSize = 120;


//[EndFile] You can add extra defines here...
//[/EndFile]
