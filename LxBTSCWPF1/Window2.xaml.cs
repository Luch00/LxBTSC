using CefSharp;
using Microsoft.WindowsAPICodePack.Taskbar;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.IO;
using System.Runtime.CompilerServices;
using System.Windows;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Media.Imaging;

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
            //ServerConnected(4, "test", new List<User> { new User {ClientID = 1, Name = "TEST" } });
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

        public void ServerConnected(ulong serverConnectionHandlerID, string name, List<User> users)
        {
            //MessageBox.Show(name);
            //if (!serverTabs.ContainsKey(serverConnectionHandlerID))
            //{
            //    try
            //    {
            //        var serverTab = new ServerTab(serverConnectionHandlerID, name, users);
            //    }
            //    catch (Exception e)
            //    {
            //        MessageBox.Show(e.Message);
            //    }
            //    //serverTab.GetAvatarFUCK += ServerTab_GetAvatarFUCK;
            //    //serverTabs.Add(serverConnectionHandlerID, serverTab);
            //    //ServerTabs2.Add(serverTab);

            //    //serverTabControl.SelectedIndex = (serverTabControl.Items.Count - 1);
            //}
            Dispatcher.Invoke(() =>
            {
                try
                {
                    if (!serverTabs.ContainsKey(serverConnectionHandlerID))
                    {
                        var serverTab = new ServerTab(serverConnectionHandlerID, name, users);
                        serverTab.GetAvatarFUCK += ServerTab_GetAvatarFUCK; ;
                        serverTabs.Add(serverConnectionHandlerID, serverTab);
                        ServerTabs2.Add(serverTab);

                        serverTabControl.SelectedIndex = (serverTabControl.Items.Count - 1);
                    }
                    else
                    {
                        foreach (var item in users)
                        {
                            serverTabs[serverConnectionHandlerID].UserConnected(item);
                        }
                    }
                }
                catch (Exception e)
                {
                    MessageBox.Show(e.Message);
                }
            });
        }

        private void ServerTab_GetAvatarFUCK(object sender, GetAvatarEventArgs e)
        {
            OnGetAvatar(e);
        }

        public void UserConnected(ulong serverConnectionHandlerID, User user)
        {
            serverTabs[serverConnectionHandlerID].UserConnected(user);
        }

        public void UserDisconnected(ulong serverConnectionHandlerID, ushort clientID)
        {
            serverTabs[serverConnectionHandlerID].UserDisconnected(clientID);
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

        public void SetAvatarPath(ulong server, ushort target, string path)
        {
            if (serverTabs.ContainsKey(server))
            {
                serverTabs[server].SetUserAvatar(target, path);
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
            }
        }

        public event EventHandler<MessageSentEventArgs> MessageSent;
        public event EventHandler<GetAvatarEventArgs> GetAvatar;
        public event PropertyChangedEventHandler PropertyChanged;

        protected virtual void OnMessageSent(MessageSentEventArgs e)
        {
            MessageSent?.Invoke(this, e);
        }

        protected virtual void OnGetAvatar(GetAvatarEventArgs e)
        {
            GetAvatar?.Invoke(this, e);
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

    public class GetAvatarEventArgs : EventArgs
    {
        public ulong ServerID { get; set; }
        public ushort ClientID { get; set; }
    }

    public class User : INotifyPropertyChanged
    {
        public ushort ClientID { get; set; }
        public string Name { get; set; }

        private BitmapImage thumbnail;
        public BitmapImage Image
        {
            get { return thumbnail; }
            set
            {
                thumbnail = value;
                OnPropertyChanged();
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        protected void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        public void SetImage(string path)
        {
            try
            {
                BitmapImage img = new BitmapImage();
                RenderOptions.SetBitmapScalingMode(img, BitmapScalingMode.HighQuality);
                img.BeginInit();
                img.CacheOption = BitmapCacheOption.None;
                img.DecodePixelHeight = 48;
                img.UriSource = new Uri(path);
                img.EndInit();
                Image = img;
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
            }
        }
    }
}
