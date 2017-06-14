using System;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Text;

namespace LxBTSCWPF1
{
    public class Global : INotifyPropertyChanged
    {
        private int panelWidth = 90;
        public int PanelWidth
        {
            get { return panelWidth; }
            set
            {
                panelWidth = value;
                OnPropertyChanged();
            }
        }

        private static Global instance;
        public Global Instance
        {
            get { return instance ?? (instance = new Global()); }
        }

        private Global() { }

        public event PropertyChangedEventHandler PropertyChanged;

        protected void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(null, new PropertyChangedEventArgs(propertyName));
        }
    }
}
