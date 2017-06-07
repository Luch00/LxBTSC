using CefSharp;
using Microsoft.WindowsAPICodePack.Taskbar;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.IO;
using System.Runtime.CompilerServices;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Media;

namespace LxBTSCWPF1
{
    /// <summary>
    /// Interaction logic for Window2.xaml
    /// </summary>
    public partial class Window2 : Window, INotifyPropertyChanged
    {
        private string appdataPath = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData));
        private CefLibraryHandle libraryLoader;
        public Window2()
        {
            libraryLoader = new CefLibraryHandle(Path.Combine(appdataPath, @"Luch\LxBTSC\CefLib\libcef.dll"));
            InitCef();
            InitializeComponent();
            TaskbarManager.Instance.SetApplicationIdForSpecificWindow(new WindowInteropHelper(this).EnsureHandle(), "lxbtsc_separate__window");
            //ServerConnected(1, "Test");
            //ServerConnected(4, "test");
        }

        private Dictionary<ulong, ServerTab> serverTabs = new Dictionary<ulong, ServerTab>();
        private ObservableCollection<ServerTab> serverTabs2 = new ObservableCollection<ServerTab>();
        public ObservableCollection<ServerTab> ServerTabs2
        {
            get { return serverTabs2; }
            set
            {
                serverTabs2 = value;
            }
        }

        public static readonly SolidColorBrush BRUSH_BLACK = new SolidColorBrush(Colors.Black);
        public static readonly SolidColorBrush BRUSH_TEAL = new SolidColorBrush(Colors.Teal);

        private string chatboxText;
        public string ChatboxText
        {
            get { return chatboxText; }
            set
            {
                chatboxText = value;
            }
        }

        //public class ChatTab : TabItem
        //{
        //    public BrowserTab Browser { get; set; }
        //    public int Target { get; set; }
        //    public int From { get; set; }
        //    //public bool HasNewMessages { get; set; }

        //    public ChatTab(string header, int target)
        //    {
        //        Browser = new BrowserTab();
        //        Target = target;
        //        this.Header = header;
        //        this.Content = Browser;
        //    }

        //    public void MessageReceived(bool outgoing, string name, string s, bool isSelected)
        //    {
        //        if (!isSelected)
        //        {
        //            //HasNewMessages = true;
        //            this.Foreground = BRUSH_TEAL;
        //        }
        //        Browser.MessageReceived(outgoing, name, s);
        //    }

        //    public void WasSelected()
        //    {
        //        this.Foreground = BRUSH_BLACK;
        //    }
        //}

        //public class ServerTab : TabItem
        //{
        //    public ulong ServerConnectionHandlerID { get; private set; }
        //    public Dictionary<int, ChatTab> chatTabs;
        //    //public ChatTabControl chatTabControl;
        //    public TabControl chatTabControl;
        //    public SolidColorBrush ForegroundBrush
        //    {
        //        get { return foregroundBrush; }
        //        set
        //        {
        //            if (foregroundBrush != value)
        //            {
        //                foregroundBrush = value;
        //            }
        //        }
        //    }
        //    private SolidColorBrush foregroundBrush;
        //    public ServerTab(ulong serverConnectionHandlerID, string header)
        //    {
        //        ServerConnectionHandlerID = serverConnectionHandlerID;
        //        this.Header = header;

        //        chatTabs = new Dictionary<int, ChatTab>
        //        {
        //            { -2, new ChatTab("Server", 3) },
        //            { -1, new ChatTab("Channel", 2) }
        //        };
        //        chatTabControl = new TabControl();
        //        chatTabControl.TabStripPlacement = Dock.Bottom;
        //        chatTabControl.Items.Add(chatTabs[-2]);
        //        chatTabControl.Items.Add(chatTabs[-1]);
        //        this.Content = chatTabControl;
        //        chatTabControl.SelectedIndex = 0;
        //    }

        //    public void MessageReceived(ushort target, bool outgoing, string name, string s, bool isSelected)
        //    {
        //        if (!isSelected)
        //        {
        //            this.Foreground = BRUSH_TEAL;
        //        }
        //        bool chatIsSelected;
        //        switch (target)
        //        {
        //            case 1:
        //                // private message
        //                break;
        //            case 2:
        //                chatIsSelected = chatTabs[-2] == chatTabControl.SelectedItem;
        //                chatTabs[-1].MessageReceived(outgoing, name, s, chatIsSelected);
        //                break;
        //            case 3:
        //                chatIsSelected = chatTabs[-2] == chatTabControl.SelectedItem;
        //                chatTabs[-2].MessageReceived(outgoing, name, s, chatIsSelected);
        //                break;
        //            default:
        //                break;
        //        }
        //    }

        //    public void AddChatTab(int id, string name)
        //    {
        //        chatTabs.Add(id, new ChatTab(name, id));
        //        chatTabControl.Items.Add(chatTabs[id]);
        //    }

        //    public void WasSelected()
        //    {
        //        //ForegroundBrush = BRUSH_BLACK;
        //        this.Foreground = BRUSH_BLACK;
        //    }
        //}

        public void ServerConnected(ulong serverConnectionHandlerID, string name)
        {
            Dispatcher.Invoke(() =>
            {
                try
                {
                    if (!serverTabs.ContainsKey(serverConnectionHandlerID))
                    {
                        var serverTab = new ServerTab(serverConnectionHandlerID, name);
                        serverTabs.Add(serverConnectionHandlerID, serverTab);
                        ServerTabs2.Add(serverTab);

                        //serverTabControl.Items.Add(serverTab);
                        serverTabControl.SelectedIndex = (serverTabControl.Items.Count - 1);
                    }
                }
                catch (Exception e)
                {
                    MessageBox.Show(e.Message);
                }
            });
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
                set.CefCommandLineArgs.Add("disable-smooth-scrolling", "1");
                //set.CefCommandLineArgs.Add("--log-file", @"C:\Users\TURSAS\Desktop\debug.log");
                //set.CefCommandLineArgs.Add("--log-severity", "verbose");
                Cef.Initialize(set);
            }
        }

        public void MessageReceived(ulong server, ushort target, bool outgoing, string name, string s)
        {
            if (serverTabs.ContainsKey(server))
            {
                bool isSelected = serverTabs[server] == CurrentServerTab;
                serverTabs[server].MessageReceived(target, outgoing, name, s, isSelected);
            }
        }

        private void Window_Closed(object sender, EventArgs e)
        {
            //this.Dispose();
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            Cef.Shutdown();
            libraryLoader.Dispose();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            //ServerConnected(2, "Testi2");
            if (CurrentServerTab != null)
            {
                CurrentServerTab.Foreground = Brushes.Black;
            }
            else
            {
                MessageBox.Show("null");
            }
        }

        //public ChatTab CurrentChatTab { get; set; }
        private ServerTab currentServerTab;
        public ServerTab CurrentServerTab
        {
            get { return currentServerTab; }
            set
            {
                if (currentServerTab != value)
                {
                    currentServerTab = value;
                    value.WasSelected();
                }
            }
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {

        }

        private void TextBox_PreviewKeyDown(object sender, System.Windows.Input.KeyEventArgs e)
        {
            if (e.Key == System.Windows.Input.Key.Enter && ChatboxText.Length > 0)
            {
                if ((Keyboard.Modifiers & ModifierKeys.Shift) != ModifierKeys.Shift)
                {
                    var serverID = CurrentServerTab.ServerConnectionHandlerID;
                    var chatID = CurrentServerTab.SelectedTab.Target;
                    var to = CurrentServerTab.SelectedTab.From;
                    var eventargs = new MessageSentEventArgs();
                    eventargs.ServerID = serverID;
                    eventargs.ChatID = (ushort)chatID;
                    eventargs.ToID = (ushort)to;
                    eventargs.Message = ChatboxText;
                    OnMessageSent(eventargs);
                    ChatboxText = string.Empty;
                    OnPropertyChanged("ChatboxText");
                    e.Handled = true;
                }
                //else
                //{
                //    ChatboxText += Environment.NewLine;
                //    OnPropertyChanged("ChatboxText");
                //}
            }
        }

        public event EventHandler<MessageSentEventArgs> MessageSent;
        public event PropertyChangedEventHandler PropertyChanged;

        protected virtual void OnMessageSent(MessageSentEventArgs e)
        {
            MessageSent?.Invoke(this, e);
        }

        protected void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }

    public class MessageSentEventArgs : EventArgs
    {
        public ulong ServerID { get; set; }
        public ushort ChatID { get; set; }
        public ushort ToID { get; set; }
        public string Message { get; set; }
    }
}
