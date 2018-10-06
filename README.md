# Better Chat plugin for TeamSpeak 3
[![Build status](https://ci.appveyor.com/api/projects/status/5x17tael0j88eeuh?svg=true)](https://ci.appveyor.com/project/Luch00/lxbtsc)

Releases: [Here](https://github.com/Luch00/LxBTSC/releases)

Automatic build for current master: [64bit only](https://ci.appveyor.com/api/projects/Luch00/lxbtsc/artifacts/BetterChat.ts3_plugin?branch=master&job=Environment%3A+GENERATOR%3DVisual+Studio+2015+Win64%2C+QTDIR%3DC%3A%5CQt%5C5.6%5Cmsvc2015_64%2C+PLATFORM%3Dx64)

### What does it do?
Plugin inserts a new chat widget into TeamSpeak UI on top of the regular one. The new widget is based on Chromium 45 and thus enables html/css/javascript to be used to style, script and embed content into the chat.
![Chat](https://i.imgur.com/FCuXJcS.gif)


### Features
Style with css, for example show user avatars in chat

Animated emotes & no size restrictions

![Emotes](https://i.imgur.com/8SvvDdR.gif)

Embed linked images, youtube, tweets etc...

![Youtube](https://i.imgur.com/RDW9ovv.png)

![Twitter](https://i.imgur.com/rAaTNXc.png)


### Restrictions
* This plugin does not perfectly replicate every function that is available in the regular chat
  * Some context menu options are missing
  * File downloads will use a separate UI
  * Some status messages will not be printed
  * etc..
* Chromium does not contain proprietary codecs meaning any content that uses those codecs (e.g. H264 or mp3) will NOT play even if embedding them might be possible.
* Chromium 45 is from 2015 and may not work perfectly with current day embeds.


## Building

### Windows:
Visual Studio 2015/2017

Visual Studio 2015 (v140) toolset

Windows 8.1/10 SDK

[Qt Visual Studio Tools](https://marketplace.visualstudio.com/items?itemName=TheQtCompany.QtVisualStudioTools-19123)

[Qt 5.6.2](https://download.qt.io/official_releases/qt/5.6/5.6.2/)

### Linux:
Install Qt sdk and in the project directory run:

```
qmake -config release
make
```


## Debugging
To debug the javascript side of things, add the environment variable

`QTWEBENGINE_REMOTE_DEBUGGING=PORT`

and point your browser to `http://127.0.0.1:PORT/`
