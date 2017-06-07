using System;
using LxBTSCForm;
using LxBTSCWPF1;
using System.Threading.Tasks;
using System.Threading;
using System.Runtime.InteropServices;
using System.Windows;

namespace TS
{
    public class TSPlugin
    {
        #region singleton
        private readonly static Lazy<TSPlugin> _instance = new Lazy<TSPlugin>(() => new TSPlugin());

        private TSPlugin()
        {

        }

        public static TSPlugin Instance
        {
            get
            {
                return _instance.Value;
            }
        }

        #endregion
        public TS3Functions Functions { get; set; }

        public System.Threading.Timer timer;

        public string PluginName = "LxBTSC";
        public string PluginVersion = "0.1";
        public int ApiVersion = 21;
        public string Author = "Luch";
        public string Description = "Better TeamSpeak Chat";
        public string PluginID { get; set; }
        //public Form1 chatGui;
        public Window2 chatGui;

        public int Init()
        {
            //chatGui = new Form1();
            chatGui = new Window2();
            chatGui.MessageSent += ChatGui_MessageSent;
            chatGui.Show();
            return 0;
        }

        private void ChatGui_MessageSent(object sender, MessageSentEventArgs e)
        {
            //MessageBox.Show(e.Message);
            //IntPtr msg = Marshal.StringToHGlobalAnsi(e.Message);
            IntPtr msg = UsefulFuncs.NativeUtf8FromString(e.Message);
            switch (e.ChatID)
            {
                case 1:
                    if (Functions.requestSendPrivateTextMsg(e.ServerID, msg, e.ToID, null) != Errors.ERROR_ok)
                        Functions.logMessage("Failed Chat", LogLevel.LogLevel_WARNING, "lxbtsc", e.ServerID);
                    break;
                case 2:
                    ushort id = 0;
                    if (Functions.getClientID(e.ServerID, ref id) != Errors.ERROR_ok)
                        Functions.logMessage("Failed Chat", LogLevel.LogLevel_WARNING, "lxbtsc", e.ServerID);

                    ulong channelid = 0;
                    if (Functions.getChannelOfClient(e.ServerID, id, ref channelid) != Errors.ERROR_ok)
                        Functions.logMessage("Failed Chat", LogLevel.LogLevel_WARNING, "lxbtsc", e.ServerID);
                    
                    if (Functions.requestSendChannelTextMsg(e.ServerID, msg, channelid, null) != Errors.ERROR_ok)
                        Functions.logMessage("Failed Chat", LogLevel.LogLevel_WARNING, "lxbtsc", e.ServerID);
                    break;
                default:
                    if (Functions.requestSendServerTextMsg(e.ServerID, msg, null) != Errors.ERROR_ok)
                        Functions.logMessage("Failed Chat", LogLevel.LogLevel_WARNING, "lxbtsc", e.ServerID);
                    break;
            }
            Functions.freeMemory(msg);
        }

        public void ServerConnected(UInt64 serverConnectionHandlerID, string name)
        {
            chatGui.ServerConnected(serverConnectionHandlerID, name);
            //chatGui2.ServerConnected(serverConnectionHandlerID, name);
        }

        private void CheckHandle(object state)
        {
            //chatGui.Show();
        }

        public void Shutdown()
        {
            //chatGui2.Close();
            chatGui.Close();
            //chatGui.Dispose();
        }
    }
}
