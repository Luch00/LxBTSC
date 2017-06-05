﻿using CefSharp;
using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.IO;
using System.Runtime.CompilerServices;
using Microsoft.WindowsAPICodePack.Taskbar;

namespace LxBTSCForm
{
    public partial class Form1 : Form
    {
        private string appdataPath = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData));
        private CefLibraryHandle libraryLoader;

        public static Dictionary<string, string> Emotes = new Dictionary<string, string>();

        public Form1()
        {
            libraryLoader = new CefLibraryHandle(Path.Combine(appdataPath, @"Luch\LxBTSC\CefLib\libcef.dll"));
            InitCef();
            TaskbarManager.Instance.SetApplicationIdForSpecificWindow(this.Handle, "lxbtscform_separate_window");
            InitializeComponent();
        }
        private Dictionary<ulong, Dictionary<int, BrowserTabPage>> serverTabs = new Dictionary<ulong, Dictionary<int, BrowserTabPage>>();

        private class BrowserTabPage : TabPage
        {
            public BrowserTab Browser { get; private set; }
            //public TabPage Tab { get; private set; }
            public TabPage ServerTab { get; set; }
            public bool HasMessages { get; set; }
            public BrowserTabPage(string header)
            {
                Browser = new BrowserTab("");
                HasMessages = false;
                this.Text = header;
                this.Controls.Add(Browser);
            }
        }

        public void ServerConnected(ulong serverConnectionHandlerID, string name)
        {
            if (!serverTabs.ContainsKey(serverConnectionHandlerID))
            {
                var chatTabs = new Dictionary<int, BrowserTabPage>
                {
                    {-2, new BrowserTabPage("Server") },
                    {-1, new BrowserTabPage("Channel") }
                };
                serverTabs.Add(serverConnectionHandlerID, chatTabs);
                TabPage serverPage = new TabPage(name);
                chatTabs[-2].ServerTab = serverPage;
                //TabPage serverChatPage = new TabPage("Server");
                //serverChatPage.Controls.Add(chatTabs[-2]);
                //TabPage channelChatPage = new TabPage("Channel");
                //channelChatPage.Controls.Add(chatTabs[-1]);

                TabControl chatTabControl = new TabControl();
                chatTabControl.Alignment = TabAlignment.Bottom;
                chatTabControl.Dock = DockStyle.Fill;

                chatTabControl.TabPages.Add(chatTabs[-2]);
                chatTabControl.TabPages.Add(chatTabs[-1]);

                serverPage.Controls.Add(chatTabControl);
                tabControl1.TabPages.Add(serverPage);
            }
        }

        [MethodImpl(MethodImplOptions.NoInlining)]
        private static void InitCef()
        {
            var appdataPath = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData));
            if (!Cef.IsInitialized)
            {
                Cef.EnableHighDPISupport();
                CefSettings set = new CefSettings
                {
                    PersistSessionCookies = true,
                    CachePath = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData), @"Luch\LxBTSC\Cache"),
                    BrowserSubprocessPath = Path.Combine(appdataPath, @"Luch\LxBTSC\CefLib", "CefSharp.BrowserSubprocess.exe"),
                    LocalesDirPath = Path.Combine(appdataPath, @"Luch\LxBTSC\CefLib\locales"),
                    ResourcesDirPath = Path.Combine(appdataPath, @"Luch\LxBTSC\CefLib")
                };
                set.CefCommandLineArgs.Add("--disable-gpu", "--disable-gpu");
                //set.CefCommandLineArgs.Add("--log-file", @"C:\Users\TURSAS\Desktop\debug.log");
                //set.CefCommandLineArgs.Add("--log-severity", "verbose");
                Cef.Initialize(set);
            }
        }

        private void Cbo_MessageEvent(object sender, MessageEventArgs e)
        {
            var m = e.Message;
            if (m.Length>0)
            {
                MessageReceived(0, 3, true, "Test", m);
            }
        }

        public void MessageReceived(ulong server, ushort target, bool outgoing, string name, string s)
        {
            if (serverTabs.ContainsKey(server))
            {
                switch (target)
                {
                    case 1:
                        break;
                    case 2:
                        serverTabs[server][-1].Browser.MessageReceived(outgoing, name, s);
                        break;
                    case 3:
                        serverTabs[server][-2].Browser.MessageReceived(outgoing, name, s);
                        break;
                }
            }
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            this.Dispose();
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            Cef.Shutdown();
            libraryLoader.Dispose();
        }
    }

    public class CallBackObject
    {
        public delegate void MessageEventHandler(object sender, MessageEventArgs e);
        public event MessageEventHandler MessageEvent;

        public void ReceiveMessage(string message)
        {
            if (MessageEvent == null)
                return;
            MessageEventArgs args = new MessageEventArgs(message);
            MessageEvent(this, args);
        }
    }

    public class MessageEventArgs
    {
        public string Message { get; private set; }

        public MessageEventArgs(string s)
        {
            Message = s;
        }
    }
}
