using System;
using System.Windows.Forms;
using CefSharp.WinForms;
using CefSharp;
using System.Text.RegularExpressions;
using CodeKicker.BBCode;
using System.IO;
using Newtonsoft.Json;
using System.Collections.Generic;

namespace LxBTSCForm
{
    public partial class BrowserTab : UserControl
    {
        public IWinFormsWebBrowser Browser { get; private set; }
        private readonly CallBackObject cbo;

        public BrowserTab(string url)
        {
            InitializeComponent();

            var browser = new ChromiumWebBrowser(url)
            {
                Dock = DockStyle.Fill
            };
            this.Dock = DockStyle.Fill;
            browserPanel.Controls.Add(browser);

            Browser = browser;

            browser.MenuHandler = new Handlers.MenuHandler();
            browser.LifeSpanHandler = new Handlers.LifespanHandler();
            browser.FrameLoadEnd += Browser_FrameLoadEnd;

            cbo = new CallBackObject();
            cbo.MessageEvent += Cbo_MessageEvent;

            browser.RegisterJsObject("callbackObj", cbo);
            LoadHtml();
        }

        private void Browser_FrameLoadEnd(object sender, FrameLoadEndEventArgs e)
        {
            if (e.Frame.IsMain)
            {
                foreach (var line in history)
                {
                    Browser.ExecuteScriptAsync($"AddServerLine('<div>{line}</div>');");
                }
            }
        }

        private string appdataPath = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData));

        public static Dictionary<string, string> Emotes = new Dictionary<string, string>();

        private List<string> history = new List<string>();

        private void LoadHtml()
        {
            if (File.Exists(Path.Combine(appdataPath, @"Luch\LxBTSC\template\chat.html")))
            {
                var slashes = appdataPath.Replace("\\", "/");
                var file = $"file:///{slashes}/Luch/LxBTSC/template/chat.html";
                var json = File.ReadAllText($"{appdataPath}\\Luch\\LxBTSC\\template\\emotes.json");
                Emotes = JsonConvert.DeserializeObject<Dictionary<string, string>>(json);
                Browser.RequestHandler = new Handlers.RequestHandler(file);
                Browser.Load(file);
            }
        }

        private void Cbo_MessageEvent(object sender, MessageEventArgs e)
        {
            var m = e.Message;
            if (m.Length > 0)
            {
                MessageReceived(true, "Test", m);
            }
        }

        public void MessageReceived(bool outgoing, string name, string s)
        {
            var message = ToHTML(s.Replace("\r", ""));
            if (message.Length > 0)
            {
                string chatline = string.Format("<img class=\"{0}\"><{1:HH:mm:ss}> <span class=\"name\">\"{2}\"</span>: {3}", outgoing ? "outgoing" : "incoming", DateTime.Now, name, Emoticonize(message));
                
                try
                {
                    Browser.ExecuteScriptAsync($"AddServerLine('<div>{chatline}</div>');");
                }
                catch (Exception)
                {
                    history.Add(chatline);
                }
            }
        }

        private Regex ytRegex = new Regex(@"http(?:s?):\/\/(?:www\.)?youtu(?:be\.com\/watch\?v=|\.be\/)([\w\-\\_]*)(&(amp;)?‌​[\w\?‌​=]*)?");

        private string ToHTML(string s)
        {
            s = parser.ToHtml(s);
            Match m = ytRegex.Match(s);
            if (m.Success)
            {
                s = $"{s}<br><iframe width=\"560\" height=\"315\" src=\"https://www.youtube.com/embed/{m.Groups[1].Value}\" frameborder=\"0\" allowfullscreen></iframe>";
            }
            return s;
        }

        private string Emoticonize(string s)
        {
            string emoticonized = s;
            foreach (var emote in Emotes)
            {
                emoticonized = emoticonized.Replace(emote.Key, $"<img class=\"{emote.Value}\" alt=\"{emote.Key}\"/>");
            }
            return emoticonized;
        }

        BBCodeParser parser = new BBCodeParser(new[]
        {
            new BBTag("b", "<b>", "</b>"),
            new BBTag("i", "<i>", "</i>"),
            new BBTag("u", "<u>", "</u>"),
            new BBTag("url", "<a href=\"${href}\">", "</a>", new BBAttribute("href", "", PrefixHref), new BBAttribute("href", "href", PrefixHref)),
        });

        static string PrefixHref(IAttributeRenderingContext attributeRenderingContext)
        {
            if (!string.IsNullOrWhiteSpace(attributeRenderingContext.AttributeValue))
            {
                if (attributeRenderingContext.AttributeValue.Contains("://"))
                {
                    return attributeRenderingContext.AttributeValue;
                }
                return $"http://{attributeRenderingContext.AttributeValue}";
            }
            var content = attributeRenderingContext.GetAttributeValueByID(BBTag.ContentPlaceholderName);
            if (content.Contains("://"))
            {
                return content;
            }
            return $"http://{content}";
        }
    }
}
