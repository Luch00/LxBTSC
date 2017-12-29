# LxBTSC
Better TeamSpeak Chat (kinda)

[![Build status](https://ci.appveyor.com/api/projects/status/5x17tael0j88eeuh?svg=true)](https://ci.appveyor.com/project/Luch00/lxbtsc)

Plugin packages for current master: [x64](https://ci.appveyor.com/api/projects/Luch00/lxbtsc/artifacts/BetterChat.ts3_plugin?branch=master&job=Environment%3A+GENERATOR%3DVisual+Studio+2015+Win64%2C+QTDIR%3DC%3A%5CQt%5C5.6%5Cmsvc2015_64%2C+PLATFORM%3Dx64) / [x86](https://ci.appveyor.com/api/projects/Luch00/lxbtsc/artifacts/BetterChat.ts3_plugin?branch=master&job=Environment%3A+GENERATOR%3DVisual+Studio+2015%2C+QTDIR%3DC%3A%5CQt%5C5.6%5Cmsvc2015%2C+PLATFORM%3DWin32)

Replace Teamspeak text chat tabs with stylable HTML

![Chat](https://i.imgur.com/FCuXJcS.gif)

Bigger & animated emotes, embed youtube, style with CSS, add javascript etc..


## Building
Visual Studio 2015/2017

Visual Studio 2015 (v140) toolset

Windows 8.1/10 SDK

[Qt Visual Studio Tools](https://marketplace.visualstudio.com/items?itemName=TheQtCompany.QtVisualStudioTools-19123)

Qt 5.6.2


## Debugging
To debug the javascript side of things, add the environment variable

`QTWEBENGINE_REMOTE_DEBUGGING=PORT`

and point your browser to `http://127.0.0.1:PORT/`
