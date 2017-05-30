using System;
using LxBTSCForm;

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
        public Form1 chatGui;

        public int Init()
        {
            chatGui = new Form1();
            
            chatGui.Show();
            
            return 0;
        }

        public void ServerConnected(UInt64 serverConnectionHandlerID, string name)
        {
            chatGui.ServerConnected(serverConnectionHandlerID, name);
        }

        private void CheckHandle(object state)
        {
            chatGui.Show();
        }

        public void Shutdown()
        {
            chatGui.Close();
            chatGui.Dispose();
        }
    }
}
