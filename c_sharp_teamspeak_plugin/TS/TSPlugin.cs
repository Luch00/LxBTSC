using System;
using LxBTSCForm;
using System.Windows.Forms;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Threading;

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
        AppDomain currentDomain = AppDomain.CurrentDomain;
        
        [DllImport("user32.dll")]
        public extern static int SetParent(int child, int parent);

        public System.Threading.Timer timer;

        public string PluginName = "LxBTSC";
        public string PluginVersion = "0.1";
        public int ApiVersion = 20;
        public string Author = "Luch";
        public string Description = "Better TeamSpeak Chat";
        public string PluginID { get; set; }
        public LxBTSCForm.Form1 chatGui;

        int ownhandle = 0;

        public int Init()
        {
            chatGui = new Form1();
            
            ownhandle = chatGui.Handle.ToInt32();
            
            timer = new System.Threading.Timer(CheckHandle, null, 1000, Timeout.Infinite);
            
            return 0;
        }

        [DllImport("user32.dll", SetLastError = true)]
        static extern int GetWindowLong(IntPtr hWnd, int nIndex);

        const int GWL_EXSTYLE = -20;
        const int WS_EX_TOPMOST = 0x0008;

        public static bool IsWindowTopMost(IntPtr hWnd)
        {
            int exStyle = GetWindowLong(hWnd, GWL_EXSTYLE);
            return (exStyle & WS_EX_TOPMOST) == WS_EX_TOPMOST;
        }

        private void CheckHandle(object state)
        {
            var tshandle = GetHandle();
            if (tshandle.ToInt32() == ownhandle)
            {
                timer.Change(1000, Timeout.Infinite);
                return;
            }
            timer.Dispose();
            
            NativeWindow owner = new NativeWindow();
            owner.AssignHandle(tshandle);
            //MessageBox.Show(tshandle.ToString());
            var b = IsWindowTopMost(tshandle);
            //MessageBox.Show(b.ToString());
            chatGui.TopMost = IsWindowTopMost(tshandle);
            chatGui.Show(owner);
            try
            {
                chatGui.StartAutomation();
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
            }
        }

        private IntPtr GetHandle()
        {
            Process[] p = Process.GetProcessesByName("ts3client_win64");
            if (p[0] != null)
            {
                return p[0].MainWindowHandle;
            }
            return IntPtr.Zero;
        }

        public void Shutdown()
        {
            //winHook.Unhook();
            chatGui.Close();
            chatGui.Dispose();
        }
    }
}
