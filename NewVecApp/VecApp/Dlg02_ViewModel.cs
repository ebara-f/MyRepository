using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;
using System.Windows.Threading;

namespace VecApp
{
	/// <summary>
	/// Dlg02のViewModel
	/// </summary>
	public partial class Dlg02_ViewModel : ViewModel
	{
		private Dlg02 view;
		private CancellationTokenSource cancelTokensource;

		public Dlg02_ViewModel(Dlg02 _view)
		{
			view = _view;
			CancelCommand = new ProcCancelCommand(this);
		}

		/// <summary>
		/// Windowを閉じる
		/// </summary>
		private void CloseWindow()
		{
			view.Close();
		}


		// プロパティ
		private bool _executing = false;
		public bool Executing
		{
			get { return _executing; }
			set
			{
				if (_executing != value)
				{
					_executing = value;
					OnPropertyChanged("Executing");
				}
			}
		}

		public ICommand CancelCommand { get; set; }


		/// <summary>
		/// コンストラクタ
		/// </summary>
		public Dlg02_ViewModel()
		{
		}


		/// <summary>
		/// 処理開始
		/// </summary>
		public void StartProc()
		{
			this.Executing = true;

			// CancellationTokenの生成
			this.cancelTokensource = new CancellationTokenSource();
			var cancelToken = this.cancelTokensource.Token;

			// 本処理を実行
			this.MainProc(cancelToken);
		}


		// コマンドクラス
		private class ProcCancelCommand : ICommand
		{
			private Dlg02_ViewModel vm;

			public ProcCancelCommand(Dlg02_ViewModel _vm)
			{
				vm = _vm;
			}

			public bool CanExecute(object parameter)
			{
				return true;
			}

			public event EventHandler CanExecuteChanged
			{
				// CS0067を回避するためのダミー処理
				add { }
				remove { }
			}

			public void Execute(object parameter)
			{
				vm.cancelTokensource?.Cancel();  // キャンセルを発行
			}
		}


		/*----- 本処理 -----*/
		private async void MainProc(CancellationToken cancelToken)
		{
			// 非同期で処理を実行
			await Task.Run(() =>
			{
				while ( true )
				{
					// キャンセル判定
					if (cancelToken.IsCancellationRequested == true)
					{
						this.Executing = false;
						break;
					}

					Thread.Sleep(100);
				}
			});

			// 終了処理
			this.Executing = false;

			CloseWindow();
		}
	}
}
