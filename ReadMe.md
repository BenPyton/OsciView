# OsciView

[![Not Maintained](https://img.shields.io/badge/Maintenance%20Level-Not%20Maintained-yellow.svg)](https://gist.github.com/cheerfulstoic/d107229326a01ff0f333a1d3476e068d)

This is a personal project I've done some years ago after seeing [the video of SmarterEveryDay](https://www.youtube.com/watch?v=4gibcRfp4zA) on this subject.

## Overview

The purpose of this software is to visualize the output audio of the computer like on an oscilloscope.\
Hence the name OsciView.

This software is just a demo concept. It is not meant to be used in any form of production. 

The software records stereo audio signal from the output device of the computer (can be changed in the software).\
Then the signals are plotted in different views:
- The wave view shows the samples of the signals.
- The frequency/spectrum view shows the frequencies of the signals (computed with a simple DFT algorithm) plotted on a [mel scale](https://en.wikipedia.org/wiki/Mel_scale).
- The spectrogram shows the spectrum view above but on a time scale. The computed frequencies are displayed with a grey shades, with time (1 frame per pixel) on X axis and frequencies (mel scale) on Y axis.
- The oscilloscope view shows the path taken by an oscilloscope beam when we input the left audio samples on X axis and right audio samples on Y axis.

I recommend to get the great music HD files from [Chris Allen's Youtube channel](https://www.youtube.com/playlist?list=PLc4EnsriUcfQPomSF3Eh6sB143HE2r0tf).\
They are high quality content and he provides the HD files for free.

### Demo Video


## Installation

**Windows:**\
Download the [release]() and extract the zip anywhere you want.
Then run `OsciView.exe`.

**Mac/Linux:**\
Clone the repo and build the project.

## How to use

Just watch it.\
You can change some of the beam parameters and the FPS limit from the dials. 
You can select the recorded output device from the button below the dials.

You can get [a calibrating audio file]() to see what happens on the oscilloscope view.\

If you have some issues like no displacement, then it is likely your audio card removes the DC component of the wave. This DC does not change nothing in the perceived sound, but the drawings on the oscilloscope are distorted when it is removed.

In the case you can't remove this feature on your audio card, I suggest to you to use some mixing software (like [Voice Meeter Banana](https://vb-audio.com/Voicemeeter/banana.htm)) so you can have a virtual output **with** the DC component in it.

Also, you should get when possible HD audio files (pcm) instead of using compressed files (mp3) or Youtube audio output.
In general, the video players on the Internet like Youtube are compressing the audio, and thus resulting in a distorted drawing on the oscilloscope.

## Technical Information

This software uses [SFML 2.5](https://www.sfml-dev.org/index.php) and Visual Studio.\
The VS solution searches SFML libraries at `D:/SFML-2.5.1` for x86 builds and `D:/SFML-2.5.1-x64` for x64 builds.