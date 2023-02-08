#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include "Core.h" // custom classes and functions (like Input, Button, etc.)
#include "UI.h"
#include "StereoRecorder.h"
#include "WaveView.h"
#include "OsciView.h"
#include "FreqView.h"
#include "SpectrumView.h"

using namespace std;

int main()
{
	Window::Create(sf::VideoMode(1040, 620), "OsciView", sf::Style::Titlebar | sf::Style::Close);

	// Load font
	sf::Font font;
	if (!font.loadFromFile("data/font/consola.ttf"))
	{
		cout << "Error when loading font" << endl;
	}

	sf::Color lightGrey(200, 200, 200);
	sf::Color darkGrey(80, 80, 80);

	UIStyle style;
	style.setFont(font, 16);
	style.mapStyle(UI_NORMAL, lightGrey, sf::Color::Black, lightGrey, 1.0f);
	style.mapStyle(UI_HOVERED, lightGrey, sf::Color(50, 50, 50), lightGrey, 3.0f);
	style.mapStyle(UI_CLICKED, sf::Color::Black, lightGrey, lightGrey, 1.0f);
	style.mapStyle(UI_DISABLED, darkGrey, sf::Color::Black, darkGrey, 1.0f);
	style.mapStyle(UI_FOCUSED, lightGrey, sf::Color::Blue, lightGrey, 1.0f);


	sf::Text fpsText("FPS: ??", font, 16);
	fpsText.setPosition(10, 10);
	fpsText.setFillColor(lightGrey);

	string strList[] = { "hello", "hola", "bonjour", "konnichiwa", "hi", "salut" };
	int strIndex = 0;

	// Color indices for the beam hue
	int colorIndex = 1;
	sf::Color colorList[] = {
		sf::Color(255, 0, 0),
		sf::Color(255, 255, 0),
		sf::Color(0, 255, 0),
		sf::Color(0, 255, 255),
		sf::Color(0, 0, 255),
		sf::Color(255, 0, 255)
	};

	const string devicePrefix =
#ifdef _WIN32
	"OpenAL Soft on "
#else
	"";
#endif
	;

	StereoRecorder recorder;
	recorder.setChannelCount(2);
	recorder.start(48000);

	string defaultDevice = sf::SoundBufferRecorder::getDefaultDevice().substr(devicePrefix.length());
	if (!recorder.setDevice(devicePrefix + defaultDevice))
	{
		cout << "Failed to open audio device: \"" << defaultDevice << "\"" << endl;
	}

	cout << "Device used: " << defaultDevice << endl;

	Label leftLabel(0, 30, 210, 30, style);
	leftLabel.setText("Left");
	leftLabel.setAlignement(TextAlign::ALIGN_CENTER);

	Label rightLabel(0, 30, 210, 30, style);
	rightLabel.setText("Right");
	rightLabel.setAlignement(TextAlign::ALIGN_CENTER);

	HorizontalLayout labelLayout(0, 10, 430, 20);
	labelLayout.setSpacing(10);
	labelLayout.add(leftLabel);
	labelLayout.add(rightLabel);

	WaveView waveLeft(0, 0, 200, 0, style);
	waveLeft.setSampleRate(recorder.getSampleRate());
	waveLeft.setSamples(recorder.getLeftBuffer());

	WaveView waveRight(0, 0, 200, 0, style);
	waveRight.setSampleRate(recorder.getSampleRate());
	waveRight.setSamples(recorder.getRightBuffer());

	HorizontalLayout waveLayout(0, 30, 430, 120);
	waveLayout.setPaddings(10, 10, 10, 10);
	waveLayout.setSpacing(10);
	waveLayout.add(waveLeft);
	waveLayout.add(waveRight);

	FreqView freqLeft(0, 0, 200, 0, style);
	freqLeft.setSamples(recorder.getLeftFFT());

	FreqView freqRight(0, 0, 200, 0, style);
	freqRight.setSamples(recorder.getRightFFT());

	HorizontalLayout freqLayout(0, 150, 430, 110);
	freqLayout.setPaddings(10, 10, 0, 10);
	freqLayout.setSpacing(10);
	freqLayout.add(freqLeft);
	freqLayout.add(freqRight);

	SpectrumView spectrumLeft(0, 0, 200, 0, style);
	spectrumLeft.setSamples(recorder.getLeftFFT());

	SpectrumView spectrumRight(0, 0, 200, 0, style);
	spectrumRight.setSamples(recorder.getRightFFT());

	HorizontalLayout spectrumLayout(0, 260, 430, 200);
	spectrumLayout.setPaddings(10, 10, 0, 10);
	spectrumLayout.setSpacing(10);
	spectrumLayout.add(spectrumLeft);
	spectrumLayout.add(spectrumRight);

	OsciView osciView(430, 10, 600, 600, style);
	osciView.setSamples(recorder.getLeftBuffer(), recorder.getRightBuffer());
	osciView.setColor(colorList[colorIndex]);

	DialButton intensityDial(0, 0, 80, 80, style);
	intensityDial.setLabel("Intensity");
	intensityDial.setMinimum(0);
	intensityDial.setMaximum(200);
	intensityDial.setValue(140);

	DialButton lineWidthDial(0, 0, 80, 80, style);
	lineWidthDial.setLabel("Beam size");
	lineWidthDial.setMinimum(0);
	lineWidthDial.setMaximum(20);
	lineWidthDial.setValue(8);
	lineWidthDial.setLabelPosition(DialButton::LabelPosition::TOP);

	DialButton hueDial(0, 0, 80, 80, style);
	hueDial.setLabel("Beam hue");
	hueDial.setMinimum(0);
	hueDial.setMaximum(360);
	hueDial.setValue(15);
	hueDial.setMinAngle(-180);
	hueDial.setMaxAngle(180);
	hueDial.setLoopable(true);

	DialButton fpsLimitDial(0, 0, 80, 80, style);
	fpsLimitDial.setLabel("FPS limit");
	fpsLimitDial.setMinimum(30);
	fpsLimitDial.setMaximum(240);
	fpsLimitDial.setValue(120);
	fpsLimitDial.setLabelPosition(DialButton::LabelPosition::TOP);

	HorizontalLayout dialLayout(0, 465, 430, 80);
	dialLayout.setPaddings(20, 10, 0, 0);
	dialLayout.setSpacing(20);
	dialLayout.add(intensityDial);
	dialLayout.add(lineWidthDial);
	dialLayout.add(hueDial);
	dialLayout.add(fpsLimitDial);

	Button selectAudioDeviceButton(10, 580, 410, 30, style);
	selectAudioDeviceButton.setText(defaultDevice);
	selectAudioDeviceButton.setMaxTextLength(40);

	// Main window layout
	Layout rootLayout(0, 0, static_cast<int>(Window::GetWidth()), static_cast<int>(Window::GetHeight()));
	rootLayout.add(labelLayout);
	rootLayout.add(waveLayout);
	rootLayout.add(osciView);
	rootLayout.add(freqLayout);
	rootLayout.add(spectrumLayout);
	rootLayout.add(dialLayout);
	rootLayout.add(selectAudioDeviceButton);

	VerticalLayout deviceButtonsLayout(0, 0, 400, 400);
	deviceButtonsLayout.setAnchor(sf::Vector2f(0.5f, 0.5f));
	deviceButtonsLayout.setPivot(sf::Vector2f(0.5f, 0.5f));
	deviceButtonsLayout.setSpacing(10);

	std::vector<std::string> devices = sf::SoundBufferRecorder::getAvailableDevices();
	std::vector<Button*> deviceButtons(devices.size());
	for(int i = 0; i < devices.size(); ++i)
	{
		string deviceName = devices[i].substr(devicePrefix.length());
		cout << "\"" << deviceName << "\"" << endl;
		deviceButtons[i] = new Button(0, 0, 300, 30, style);
		deviceButtons[i]->setText(deviceName);
		deviceButtons[i]->setMaxTextLength(40);
		deviceButtonsLayout.add(*deviceButtons[i]);
	}

	Button backButton(10, 10, 60, 30, style);
	backButton.setText("Cancel");

	Label deviceSelectionLabel(0, 30, 0, 30, style);
	deviceSelectionLabel.setAnchor(sf::Vector2f(0.5f, 0.0f));
	deviceSelectionLabel.setPivot(sf::Vector2f(0.5f, 0.0f));
	deviceSelectionLabel.setText("Audio Device Selection");
	deviceSelectionLabel.setAlignement(TextAlign::ALIGN_CENTER);

	Layout deviceSelectionLayout(0, 0, static_cast<int>(Window::GetWidth()), static_cast<int>(Window::GetHeight()));
	deviceSelectionLayout.add(deviceSelectionLabel);
	deviceSelectionLayout.add(backButton);
	deviceSelectionLayout.add(deviceButtonsLayout);

	// Initialize the window
	Window::SetLayout(rootLayout);
	Window::SetFramerate(fpsLimitDial.getValue());

	// ///////////////////////////// APPLICATION LOOP
	while (Window::IsOpen())
	{
		Window::Update();

		// ///////////////////////// GAME LOGIC
		if (Input::GetKeyDown(sf::Keyboard::Escape))
		{
			Window::Close();
		}

		Window::GetWindow()->setTitle("OsciView | FPS: " + floatToStr(Time::GetFps(), 0));

		if (Window::GetLayout() == &rootLayout)
		{
			if (intensityDial.valueChanged())
			{
				osciView.setIntensity(intensityDial.getValue() * 0.01f);
			}

			if (lineWidthDial.valueChanged())
			{
				osciView.setLineWidth(static_cast<float>(lineWidthDial.getValue()));
			}

			if (hueDial.valueChanged())
			{
				sf::Color lineColor = fromHSV(hueDial.getValue() / 360.0f, 1.0f, 1.0f);
				osciView.setColor(lineColor);
			}

			if (fpsLimitDial.valueChanged())
			{
				Window::SetFramerate(fpsLimitDial.getValue());
			}

			if (selectAudioDeviceButton.click())
			{
				Window::SetLayout(deviceSelectionLayout);
			}
		}
		else if (Window::GetLayout() == &deviceSelectionLayout)
		{
			int indexClicked = -1;
			for (int i = 0; i < deviceButtons.size() && indexClicked < 0; ++i)
			{
				if (deviceButtons[i]->click())
					indexClicked = i;
			}

			if (indexClicked >= 0)
			{
				string deviceName = deviceButtons[indexClicked]->getText();
				if (!recorder.setDevice(devicePrefix + deviceName))
				{
					cout << "Failed to open audio device: \"" << defaultDevice << "\"" << endl;
					selectAudioDeviceButton.setText("No selected device...");
				}
				else
				{
					selectAudioDeviceButton.setText(deviceName);
				}

				Window::SetLayout(rootLayout);
			}

			if (backButton.click())
			{
				Window::SetLayout(rootLayout);
			}
		}

		recorder.updateSamples();

		// ///////////////////////// START DRAW
		Window::Clear();
		Window::Draw();
		// ///////////////////////// END DRAW
		Window::Display();
	}

	recorder.stop();

	for (int i = 0; i < deviceButtons.size(); ++i)
	{
		delete deviceButtons[i];
	}

	return 0;
}
