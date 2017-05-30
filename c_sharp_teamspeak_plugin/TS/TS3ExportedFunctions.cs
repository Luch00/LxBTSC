using RGiesecke.DllExport;
using System;
using System.Reflection;
using System.Runtime.InteropServices;
using System.IO;

namespace TS
{

    public class TS3ExportedFunctions
    {
        static AppDomain currentDomain = AppDomain.CurrentDomain;
        //private static string exePath;
        private static string pluginPath;
        static Boolean Is64Bit()
        {
            return Marshal.SizeOf(typeof(IntPtr)) == 8;
        }
        private static Assembly CurrentDomain_AssemblyResolve(object sender, ResolveEventArgs args)
        {
            //string currentPath = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);
            //string currentPath = @"C:\Program Files\TeamSpeak 3 Client";
            string assemblyPath = Path.Combine(pluginPath, @"cef", new AssemblyName(args.Name).Name + ".dll");
            if (!File.Exists(assemblyPath))
            {
                return null;
            }
            Assembly assembly = Assembly.LoadFrom(assemblyPath);
            return assembly;
        }

        [DllExport]
        public static String ts3plugin_name()
        {
            return TSPlugin.Instance.PluginName;
        }
        [DllExport]
        public static String ts3plugin_version()
        {
            return TSPlugin.Instance.PluginVersion;
        }
        [DllExport]
        public static int ts3plugin_apiVersion()
        {
            return TSPlugin.Instance.ApiVersion;
        }
        [DllExport]
        public static String ts3plugin_author()
        {
            return TSPlugin.Instance.Author;
        }
        [DllExport]
        public static String ts3plugin_description()
        {
            return TSPlugin.Instance.Description;
        }
        [DllExport]
        public static void ts3plugin_setFunctionPointers(TS3Functions funcs)
        {
            TSPlugin.Instance.Functions = funcs;
        }
        [DllExport]
        public static int ts3plugin_init()
        {
            //MessageBox.Show("INIT");
            pluginPath = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData), @"TS3Client\plugins");
            currentDomain.AssemblyResolve += CurrentDomain_AssemblyResolve;
            var appPath = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData), @"Luch\LxBTSC");
            if (!Directory.Exists(Path.Combine(appPath, @"CefLib")))
            {
                UsefulFuncs.ExtractZip(Path.Combine(pluginPath, @"cef\CefLib.zip"), appPath);
            }

            return TSPlugin.Instance.Init();
        }
        [DllExport]
        public static void ts3plugin_shutdown()
        {
            TSPlugin.Instance.Shutdown();
        }
        [DllExport]
        public static void ts3plugin_registerPluginID(String id)
        {
            var functs = TSPlugin.Instance.Functions;
            TSPlugin.Instance.PluginID = id;
        }
        [DllExport]
        public static void ts3plugin_freeMemory(System.IntPtr data)
        {
            Marshal.FreeHGlobal(data);
        }
        [DllExport]
        public static void ts3plugin_currentServerConnectionChanged(ulong serverConnectionHandlerID)
        {
        }

        [DllExport]
        public static void ts3plugin_onConnectStatusChangeEvent(UInt64 serverConnectionHandlerID, ConnectStatus status, int errorNumber)
        {
            if (status == ConnectStatus.STATUS_CONNECTED)
            {
                IntPtr name = IntPtr.Zero;
                TSPlugin.Instance.Functions.getServerVariableAsString(serverConnectionHandlerID, new IntPtr((int)VirtualServerProperties.VIRTUALSERVER_NAME), ref name);
                //string ret = Marshal.PtrToStringAnsi(name);
                string ret = UsefulFuncs.StringFromNativeUtf8(name);
                TSPlugin.Instance.chatGui.ServerConnected(serverConnectionHandlerID, ret);
                //TSPlugin.Instance.Functions.printMessageToCurrentTab("connected " + serverConnectionHandlerID + " " + ret);
            }
        }

        //[DllExport]
        //public static void ts3plugin_onClientDisplayNameChanged(UInt64 serverConnectionHandlerID, anyID clientID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string displayName, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string uniqueClientIdentifier)
        //{
        //    var functions = TSPlugin.Instance.Functions;
        //    functions.printMessageToCurrentTab(uniqueClientIdentifier);
        //}

        [DllExport]
        public static int ts3plugin_onTextMessageEvent(UInt64 serverConnectionHandlerID, anyID targetMode, anyID toID, anyID fromID, [In()] [MarshalAs(UnmanagedType.LPStr)] string fromName, [In()] [MarshalAs(UnmanagedType.LPStr)] string fromUniqueIdentifier, IntPtr message, int ffIgnored)
        {
            bool outgoing = false;
            var functions = TSPlugin.Instance.Functions;
            ushort myID = 0;
            if (functions.getClientID(serverConnectionHandlerID, ref myID) != Errors.ERROR_ok)
            {
                functions.logMessage("Unable to get own client ID", LogLevel.LogLevel_ERROR, "Bot", serverConnectionHandlerID);
                return 0;
            }
            if (fromID.value == myID)
            {
                outgoing = true;
            }
            TSPlugin.Instance.chatGui.MessageReceived(serverConnectionHandlerID, targetMode.value, outgoing, fromName, UsefulFuncs.StringFromNativeUtf8(message));

            return 0;
        }
    }
}
