// INI読み込みクラスを作成(2026.8.5yori)
using System.Runtime.InteropServices;
using System.Text;

namespace VecApp
{
    public class IniFile
    {
        private readonly string _path;

        public IniFile(string path)
        {
            _path = path;
        }

        [DllImport("kernel32.dll", CharSet = CharSet.Unicode)]
        private static extern int GetPrivateProfileString(
            string lpAppName,
            string lpKeyName,
            string lpDefault,
            StringBuilder lpReturnedString,
            int nSize,
            string lpFileName);

        public string Read(string section, string key, string defaultValue = "")
        {
            StringBuilder sb = new StringBuilder(256);

            GetPrivateProfileString(
                section,
                key,
                defaultValue,
                sb,
                sb.Capacity,
                _path);

            return sb.ToString();
        }
    }
}