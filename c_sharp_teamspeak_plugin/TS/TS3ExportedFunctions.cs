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
        private static string exePath;
        static Boolean Is64Bit()
        {
            return Marshal.SizeOf(typeof(IntPtr)) == 8;
        }
        private static System.Reflection.Assembly CurrentDomain_AssemblyResolve(object sender, ResolveEventArgs args)
        {
            //MessageBox.Show("ARGH" + args.Name);
            //string currentPath = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);
            //string currentPath = @"C:\Program Files\TeamSpeak 3 Client";
            //MessageBox.Show(currentPath);
            string assemblyPath = Path.Combine(exePath, @"plugins\cef", new AssemblyName(args.Name).Name + ".dll");
            //MessageBox.Show(assemblyPath);
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
            currentDomain.AssemblyResolve += CurrentDomain_AssemblyResolve;
            exePath = UsefulFuncs.GetProcess("ts3client_win64").StartInfo.WorkingDirectory;
            var appPath = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData), @"Luch\LxBTSC");
            if (!Directory.Exists(Path.Combine(appPath, @"CefLib")))
            {
                UsefulFuncs.ExtractZip(Path.Combine(exePath, @"plugins\cef\CefLib.zip"), appPath);
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
            //var functs = (TS3Functions)TSPlugin.Instance.Functions;
            //functs.printMessageToCurrentTab(serverConnectionHandlerID.ToString());
        }

        //[DllExport]
        //public unsafe static void ts3plugin_initMenus(PluginMenuItem*** menuItems, char** menuIcon)
        //{

        //    int x = 2;
        //    int sz = x + 1;
        //    int n = 0;

        //    *menuItems = (PluginMenuItem**)Marshal.AllocHGlobal((sizeof(PluginMenuItem*) * sz));
        //    string name = "Try";
        //    string icon = "2.png";

        //    (*menuItems)[n++] = UsefulFuncs.createMenuItem(PluginMenuType.PLUGIN_MENU_TYPE_GLOBAL, 1, name, icon);
        //    (*menuItems)[n++] = UsefulFuncs.createMenuItem(PluginMenuType.PLUGIN_MENU_TYPE_GLOBAL, 2, "Unload", icon);
        //    (*menuItems)[n++] = null;
        //    Debug.Assert(n == sz);

        //    *menuIcon = (char*)Marshal.AllocHGlobal(128 * sizeof(char));

        //    IntPtr ptr = System.Runtime.InteropServices.Marshal.StringToHGlobalAnsi("t.png");
        //    void* strPtr = ptr.ToPointer();
        //    char* cptr = (char*)strPtr;
        //    UsefulFuncs.my_strcpy(*menuIcon, 128, cptr);
        //}

        //[DllExport]
        //public unsafe static void ts3plugin_onMenuItemEvent(ulong serverConnectionHandlerID, PluginMenuType type, int menuItemID, ulong selectedItemID)
        //{
        //    var funcs = TSPlugin.Instance.Functions;
        //    IntPtr v = IntPtr.Zero;
        //    switch (type)
        //    {
        //        case PluginMenuType.PLUGIN_MENU_TYPE_GLOBAL:
        //            switch (menuItemID)
        //            {
        //                case 1:
        //                    // How to get all the channel's names
        //                    // First, get a pointer to an array
        //                    if (funcs.getChannelList(serverConnectionHandlerID, ref v) != Errors.ERROR_ok)
        //                    {
        //                        funcs.logMessage("Failed", LogLevel.LogLevel_ERROR, "Plugin", serverConnectionHandlerID);
        //                        break;
        //                    }
        //                    // Convert it to a ulong*
        //                    ulong* ptr = (ulong*) v.ToPointer();
        //                    // Iterate through the array
        //                    for (ulong t = 0; ptr[t] != 0; t++)
        //                    {
        //                        // The String result
        //                        string result;
        //                        // The pointer result
        //                        IntPtr res = IntPtr.Zero;
        //                        /*
        //                            Channel Variable Arguments:
        //                            1: The server connection ID
        //                            2: The iterated channel id
        //                            3: An IntPtr at 0, which signifies CHANNEL_NAME
        //                            4: A reference to stores results
        //                        */
        //                        if (
        //                            funcs.getChannelVariableAsString(serverConnectionHandlerID, ptr[t], new IntPtr(0), ref res) !=
        //                            Errors.ERROR_ok)
        //                        {
        //                            // Error message
        //                            funcs.logMessage("Error", LogLevel.LogLevel_WARNING, "Plugin", serverConnectionHandlerID);
        //                            break;
        //                        }
        //                        // Convert the pointer to a string
        //                        if ((result = Marshal.PtrToStringAnsi(res)) == null) break;
        //                        // Print it
        //                        funcs.printMessageToCurrentTab(result);
        //                    }
                            

        //                    break;

        //                case 2:

        //                    break;

        //                default:
        //                    break;
        //            }

        //            break;
        //    }
        //}

        [DllExport]
        public static void ts3plugin_onClientDisplayNameChanged(UInt64 serverConnectionHandlerID, anyID clientID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string displayName, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string uniqueClientIdentifier)
        {
            var functions = TSPlugin.Instance.Functions;
            functions.printMessageToCurrentTab(uniqueClientIdentifier);
        }

        [DllExport]
        public static int ts3plugin_onTextMessageEvent(UInt64 serverConnectionHandlerID, anyID targetMode, anyID toID, anyID fromID, [In()] [MarshalAs(UnmanagedType.LPStr)] string fromName, [In()] [MarshalAs(UnmanagedType.LPStr)] string fromUniqueIdentifier, IntPtr message, int ffIgnored)
        {
            if (targetMode.value != 3)
                return 0;

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
                //return 0;
            }
            TSPlugin.Instance.chatGui.MessageReceived(outgoing, fromName, UsefulFuncs.StringFromNativeUtf8(message));

            /*TSPlugin.Instance.CheckMessage(
                new TextMessage
                {
                    ServerConnectionHandlerID = serverConnectionHandlerID,
                    TargetMode = targetMode.value,
                    ToID = toID.value,
                    FromID = fromID.value,
                    FromName = fromName,
                    FromUniqueID = fromUniqueIdentifier,
                    Text = UsefulFuncs.StringFromNativeUtf8(message)
                });*/

            //functions.printMessageToCurrentTab($"{serverConnectionHandlerID} {targetMode.value} {toID.value} {fromID.value} {fromName} {fromUniqueIdentifier} {message} {ffIgnored}");

            return 0;
        }
    }
}
