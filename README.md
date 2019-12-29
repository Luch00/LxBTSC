# Better Chat plugin for TeamSpeak 3
[![Build status](https://ci.appveyor.com/api/projects/status/5x17tael0j88eeuh?svg=true)](https://ci.appveyor.com/project/Luch00/lxbtsc)

Releases: [Here](https://github.com/Luch00/LxBTSC/releases)

Automatic build for current master: [Windows 64bit only](https://ci.appveyor.com/api/projects/Luch00/lxbtsc/artifacts/BetterChat.ts3_plugin)

### What does it do?
* Plugin inserts a new chat widget into TeamSpeak UI on top of the regular one
  * The new widget is based on QWebEngine (Chromium 69)
  * Enables html/css/javascript to be used to style, script and embed content into the chat
  * Option to have avatars in chat
  * Enables custom emotes easily shareable via Teamspeak server file system, packages or external urls

### What does it NOT do
* This plugin does not perfectly replicate every function that is available in the regular chat
  * Many context menu options for chat are missing
  * No search text function in chat
  * File downloads will use a separate UI
  * Some status, error & event messages will not be printed
  * etc..
* Chromium does not contain proprietary codecs meaning any content that uses those codecs (e.g. H.264) will NOT play even if embedding them might be possible. [Workaround is to manually replace QWebEngine shipped with TS3 with one that has been compiled with proprietary codecs enabled](#building-qwebengine).


### Features
Style with css, for example show user avatars in chat

Animated emotes & no size restrictions

![Emotes](https://i.imgur.com/8SvvDdR.gif)

Embed linked images, youtube, tweets etc...

![Youtube](https://i.imgur.com/RDW9ovv.png)

![Twitter](https://i.imgur.com/rAaTNXc.png)


## Building

### Windows
Visual Studio 2017

Visual Studio 2017 (v141) toolset

Windows 8.1/10 SDK

[Qt Visual Studio Tools](https://marketplace.visualstudio.com/items?itemName=TheQtCompany.QtVisualStudioTools-19123)

[Qt 5.12.3](https://download.qt.io/official_releases/qt/5.12/5.12.3/)

### Building QWebEngine
With proprietary codecs enabled on Windows
https://doc.qt.io/qt-5.12/qtwebengine-platform-notes.html

Install everything mentioned in above section

Install [Python 2.7](https://www.python.org/downloads/windows/), [Bison & Flex](https://sourceforge.net/projects/winflexbison/), [GPerf](http://gnuwin32.sourceforge.net/packages/gperf.htm) 

Make sure everything is in system PATH

Open Visual Studio 2017 x64 Developer Command Prompt and navigate to webengine directory in Qt sources

Run 
```
qmake -- -webengine-proprietary-codecs
nmake
```

Thats it, hours later compilation should be done :smile:. Paste the resulting QWebEngine files to teamspeak directory.

### Linux
Install Qt sdk and in the project directory run:

```
qmake -config release
make
```


## Debugging
To debug the javascript side of things, add the environment variable

`QTWEBENGINE_REMOTE_DEBUGGING=PORT`

and point your browser to `http://127.0.0.1:PORT/`
