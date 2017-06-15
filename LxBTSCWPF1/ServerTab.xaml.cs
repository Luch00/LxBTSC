using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace LxBTSCWPF1
{
    /// <summary>
    /// Interaction logic for ServerTab.xaml
    /// </summary>
    public partial class ServerTab : TabItem
    {
        private SolidColorBrush foregroundBrush;
        private BrowserTab selectedTab;

        public ulong ServerConnectionHandlerID { get; private set; }

        public SolidColorBrush ForegroundBrush
        {
            get { return foregroundBrush; }
            set
            {
                if (foregroundBrush != value)
                {
                    foregroundBrush = value;
                }
            }
        }

        public BrowserTab SelectedTab
        {
            get { return selectedTab; }
            set
            {
                if (selectedTab != value)
                {
                    selectedTab = value;
                    value.WasSelected();
                }
            }
        }

        //public Dictionary<int, BrowserTab> chatTabs;
        private Dictionary<int, BrowserTab> chatTabs = new Dictionary<int, BrowserTab>();
        public Dictionary<int, BrowserTab> ChatTabs
        {
            get { return chatTabs; }
            set
            {
                chatTabs = value;
            }
        }

        private ObservableCollection<BrowserTab> chatTabs2 = new ObservableCollection<BrowserTab>();
        public ObservableCollection<BrowserTab> ChatTabs2
        {
            get { return chatTabs2; }
            set
            {
                chatTabs2 = value;
            }
        }

        private ObservableCollection<User> users = new ObservableCollection<User>();
        public ObservableCollection<User> Users
        {
            get { return users; }
            set
            {
                users = value;
            }
        }

        public Global Global
        {
            get { return Global.Instance; }
        }

        public ServerTab(ulong serverConnectionHandlerID, string header, List<User> users)
        {
            //var result = string.Join(",", (object[])users.ToArray());
            //MessageBox.Show(result);
            
            InitializeComponent();
            
            ServerConnectionHandlerID = serverConnectionHandlerID;
            Header = header;
            foreach (var item in users)
            {
                Users.Add(item);
                //item.SetImage(@"F:\pics\zmSFw4D.png");
                
            }
            var server = new BrowserTab("Server", 3);
            var channel = new BrowserTab("Channel", 2);
            ChatTabs.Add(-2, server);
            ChatTabs.Add(-1, channel);
            ChatTabs2.Add(server);
            ChatTabs2.Add(channel);
            
            chatTabControl.SelectedIndex = 0;
        }

        public void UserConnected(User user)
        {
            try
            {
                Users.Add(user);
                MessageBox.Show("connected: " + user.Name);
                var args = new GetAvatarEventArgs();
                args.ServerID = ServerConnectionHandlerID;
                args.ClientID = user.ClientID;
                OnGetAvatar(args);
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
            }
        }

        public void UserDisconnected(ushort clientID)
        {
            var user = Users.Where(x => x.ClientID == clientID).FirstOrDefault();
            if (user != null)
            {
                Users.Remove(user);
            }
        }

        public event EventHandler<GetAvatarEventArgs> GetAvatarFUCK;
        public virtual void OnGetAvatar(GetAvatarEventArgs e)
        {
            GetAvatarFUCK?.Invoke(this, e);
        }

        public void SetUserAvatar(ushort clientID, string path)
        {
            var user = Users.Where(x => x.ClientID == clientID).FirstOrDefault();
            if (user != null)
            {
                MessageBox.Show(path);
                user.SetImage(path);
            }
        }
        
        public void MessageReceived(ushort target, bool outgoing, string name, string s, bool isSelected)
        {
            if (!isSelected)
            {
                //this.Foreground = BRUSH_TEAL;
                this.Foreground = Brushes.Teal;
            }
            bool chatIsSelected = false;
            switch (target)
            {
                case 1:
                    // private message
                    break;
                case 2:
                    chatIsSelected = chatTabs[-1] == SelectedTab;//chatTabControl.SelectedItem;
                    chatTabs[-1].MessageReceived(outgoing, name, s, chatIsSelected);
                    break;
                case 3:
                    chatIsSelected = chatTabs[-2] == SelectedTab;//chatTabControl.SelectedItem;
                    chatTabs[-2].MessageReceived(outgoing, name, s, chatIsSelected);
                    break;
                default:
                    break;
            }
        }

        public void AddChatTab(int id, string name)
        {
            var tab = new BrowserTab(name, 3);
            ChatTabs.Add(-2, tab);
            ChatTabs2.Add(tab);
        }

        public void WasSelected()
        {
            //ForegroundBrush = BRUSH_BLACK;
            //this.Foreground = BRUSH_BLACK;
            this.Foreground = Brushes.Black;
        }

        private void TabItem_Loaded(object sender, RoutedEventArgs e)
        {
            foreach (var item in Users)
            {
                var args = new GetAvatarEventArgs();
                args.ServerID = ServerConnectionHandlerID;
                args.ClientID = item.ClientID;
                OnGetAvatar(args);
            }
        }
    }
}
