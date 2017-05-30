using CefSharp;
using System.Windows.Forms;

namespace LxBTSCForm.Handlers
{
    internal class MenuHandler : IContextMenuHandler
    {
        private const int CopyLinkAddress = 26506;
        public void OnBeforeContextMenu(IWebBrowser browserControl, IBrowser browser, IFrame frame, IContextMenuParams parameters, IMenuModel model)
        {
            if (parameters.UnfilteredLinkUrl != "")
            {
                model.AddItem((CefMenuCommand)CopyLinkAddress, "Copy Link Address");
            }
        }

        public bool OnContextMenuCommand(IWebBrowser browserControl, IBrowser browser, IFrame frame, IContextMenuParams parameters, CefMenuCommand commandId, CefEventFlags eventFlags)
        {
            if ((int)commandId == CopyLinkAddress)
            {
                Clipboard.SetText(parameters.UnfilteredLinkUrl);
            }
            return false;
        }

        public void OnContextMenuDismissed(IWebBrowser browserControl, IBrowser browser, IFrame frame)
        {
        }

        public bool RunContextMenu(IWebBrowser browserControl, IBrowser browser, IFrame frame, IContextMenuParams parameters, IMenuModel model, IRunContextMenuCallback callback)
        {
            return false;
        }
    }
}
