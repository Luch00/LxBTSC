using System.Collections.Generic;
using System.Collections.ObjectModel;
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

        public ServerTab(ulong serverConnectionHandlerID, string header)
        {
            InitializeComponent();

            ServerConnectionHandlerID = serverConnectionHandlerID;
            Header = header;

            var server = new BrowserTab("Server", 3);
            var channel = new BrowserTab("Channel", 2);
            ChatTabs.Add(-2, server);
            ChatTabs.Add(-1, channel);
            ChatTabs2.Add(server);
            ChatTabs2.Add(channel);
            
            chatTabControl.SelectedIndex = 0;
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
    }
}
