using System;
using System.Windows;
using System.Windows.Interop;

namespace VecApp
{
    /// <summary>
    /// Base class for SubWindow
    /// </summary>
    public abstract class SubWindowBase : Window
    {
        private IntPtr _hWnd;

        public SubWindowBase()
        {
            _hWnd = new WindowInteropHelper(this).EnsureHandle();
        }

        public IntPtr hWnd
        {
            get => _hWnd;
        }

        public abstract Panel CurrentPanel { get; set; }
    }
}
