using System;
using System.ComponentModel;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Interop;

namespace VecApp
{
    /// <summary>
    /// DlgPrgBar1.xaml の相互作用ロジック
    /// </summary>
    public partial class DlgPrgBar1 : Window, IDisposable
    {
        public IntPtr	m_hWnd;     // ウィンドウハンドル

        /// Close を許可するか（false の間は Close が要求されても Hide に置換）
        /// </summary>
        public bool m_AllowClose { get; set; } = false;

        /// <summary>
        /// 非同期処理や長時間実行される処理を「キャンセル可能」にする仕組み
        /// を提供するクラス
        /// </summary>
        private CancellationTokenSource m_CTS;

        /// <summary>
        /// Close を許可するか（false の間は Close が要求されても Hide に置換）
        /// </summary>
        private bool m_IsRunning;
        
        /// <summary>
                                 /// 初期化処理
                                 /// </summary>
        public DlgPrgBar1()
        {
            InitializeComponent();
            //this.DataContext = vm = new DlgPrgBar1_ViewModel(this);

            //vm.StartProc();

			// ウィンドウズハンドルの取得
			m_hWnd = new WindowInteropHelper(this).EnsureHandle();
        }

        /// <summary>
        /// ウィンドウの初期化が終わり、すべての要素がレイアウトされて
        /// 表示準備が整ったときに発生するイベントハンドラ
        /// </summary>
        private async void Window_Loaded(object sender, RoutedEventArgs e)
        {
            if (m_IsRunning == false)
            {
                await StartAsync();
            }
        }

        /// <summary>
        /// ×ボタン（Close）やアプリ終了時の終了処理
        /// </summary>
        private void Terminate(object sender, CancelEventArgs e)
        {
            if (m_AllowClose == true)
            {
                Cancel();
                Dispose();
            }
            else
            {
                e.Cancel = true;    // 閉じさせない
                Cancel();           // バックグラウンド停止
                this.Hide();        // 画面の非表示
            }
        }

		/// <summary>
		/// ボタンClick時の処理(Btn01)
		/// </summary>
		private void Button_Click_Btn01(object sender, RoutedEventArgs e)
		{
            CSH.Grp01.Cmd14();  // 暖機監視を終了する。(2025.7.31yori)
            //Cmd_Btn01(); // 上記の処理で非表示にするため、不要(2025.7.31yori)
        }

        /// <summary>
        /// ダイアログを表示し処理を開始する
        /// </summary>
        public void ShowAndStart(Window owner = null)
        {
            if (owner != null) this.Owner = owner;

            this.Show();        // ウィンドウの表示
            this.Activate();    // ウィンドウをフォアグラウンドへ

            if (m_IsRunning == false)
            {
                _ = StartAsync();  // _ は「使わない変数」を表す特別な記号
                                   // 戻り値は無視する
            }
        }

        /// <summary>
        /// 処理開始（二重起動不可）
        /// </summary>
        public async Task StartAsync()
        {
            if (m_IsRunning == true) return;

            m_IsRunning = true;

            // UIセットアップ
            await Dispatcher.InvokeAsync(() =>
            {
                Prg.IsIndeterminate = true;  // プログレスバーの状態を
                                             // 進捗が数値で分からない（不確定）
                                             // 状態に設定

                //「暖機中です。お待ちください。」の文字列を変更する際は以下のコードで
                //StatusText.Text = "更新する文字列";
            });

            // 「キャンセル可能な処理」を制御するためのオブジェクトの生成
            if (m_CTS == null)
            {
                m_CTS = new CancellationTokenSource();
            }

            // キャンセル要求を受け取るためのオブジェクト
            var token = m_CTS.Token;

            try
            {
                // 非同期の「キャンセル可能な処理」
                // 例：100ms間隔ポーリング（キャンセル対応）
                while (token.IsCancellationRequested == false)
                {
                    // ここで状態確認・進捗反映などを行う
                    await Dispatcher.InvokeAsync(() =>
                    {
                        // 例：テキスト更新など
                        // StatusText.Text = "...";
                    });

                    // 100ms 待つ
                    await Task.Delay(100, token);
                }
            }
            catch (OperationCanceledException)  // 正常なキャンセル
            {
                // 何もしない
            }
            catch (Exception ex)  // 例外によるキャンセル
            {
                // エラー処理例
                await Dispatcher.InvokeAsync(() =>
                {
                    //StatusText.Text = "エラーが発生しました。";
                    //MessageBox.Show(this, ex.Message, "エラー", MessageBoxButton.OK, MessageBoxImage.Error);
                });
            }
            finally  // 非同期の「キャンセル可能な処理」が終了した際に必ず通る処理
            {
                await Dispatcher.InvokeAsync(() =>
                {
                    m_IsRunning = false;
                });
            }
        }

        /// <summary>
        /// 現在の処理のキャンセル
        /// </summary>
        public void Cancel()
        {
            try
            {
                if (m_CTS != null) m_CTS.Cancel();
            }
            catch
            {
                // 何もしない
            }
        }

        /// <summary>
        /// 解放処理
        /// </summary>
        public void Dispose()
        {
            if (m_CTS != null)
            {
                m_CTS.Cancel();
                m_CTS.Dispose();
                m_CTS = null;
            }
        }
















        /// <summary>
        /// ボタンClick時の処理(Btn01)
        /// </summary>
        public void Cmd_Btn01()
		{
			this.Hide();
		}
	}
}
