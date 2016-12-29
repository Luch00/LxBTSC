using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace LxBTSCForm
{
    public partial class Listener : Form
    {
        //public delegate void SendMessageHandler(object sender, MessageEventArgs e);
        //public event SendMessageHandler OnWindowMove;
        //public event SendMessageHandler OnTabSelect;

        delegate void WinEventDelegate(IntPtr hWinEventHook, uint eventType, IntPtr hwnd, int idObject, int idChild, uint dwEventThread, uint dwmsEventTime);

        [DllImport("user32.dll")]
        static extern IntPtr SetWinEventHook(uint eventMin, uint eventMax, IntPtr hmodWinEventProc, WinEventDelegate lpfnWinEventProc, uint idProcess, uint idThread, uint dwFlags);

        [DllImport("user32.dll")]
        static extern bool UnhookWinEvent(IntPtr hWinEventHook);

        [DllImport("user32.dll")]
        static extern uint GetWindowThreadProcessId(IntPtr hWnd, IntPtr ProcessId); //intptr.zero to param 2

        private WinEventDelegate procDelegate;

        const uint WINEVENT_OUTOFCONTEXT = 0;

        public Listener()
        {
            InitializeComponent();
            //this.Visible = false;
            procDelegate = new WinEventDelegate(WinEventProc);
            Process[] ts = Process.GetProcessesByName("ts3client_win64");
            
            //int threadid = GetWindowThreadProcessId(process.MainWindowHandle, IntPtr.Zero);
            winEventHook = SetWinEventHook(EVENT_OBJECT_SELECTION, EVENT_OBJECT_LOCATIONCHANGE, IntPtr.Zero, procDelegate, (uint)ts[0].Id, GetWindowThreadProcessId(ts[0].MainWindowHandle, IntPtr.Zero)/*0*/, WINEVENT_OUTOFCONTEXT);
        }

        private const uint EVENT_OBJECT_SELECTION = 0x8006;
        private const uint EVENT_OBJECT_LOCATIONCHANGE = 0x800B;
        private static IntPtr winEventHook;

        private void WinEventProc(IntPtr hWinEventHook, uint eventType, IntPtr hwnd, int idObject, int idChild, uint dwEventThread, uint dwmsEventTime)
        {
            if (idChild == 0 && idObject == 0)
            {
                //OnWindowMove(new object(), new MessageEventArgs(eventType.ToString()));
                textBox1.AppendText("move" + Environment.NewLine);
            }
            //if (eventType == EVENT_OBJECT_SELECTION)
            //{
            //    // check open channel
            //    //ChannelTabChanged();
            //    //channelTabChanged();
            //    //MessageBox.Show("select");
            //    OnTabSelect(new object(), new EventArgs());
            //}
            //if (eventType == EVENT_OBJECT_LOCATIONCHANGE && idObject == 0 && idChild == 0)
            //{
            //    //MessageBox.Show("move1");
            //    OnWindowMove(new object(), new EventArgs());
            //    //windowPositionChanged();
            //    //check rect position
            //}
        }
    }
}
