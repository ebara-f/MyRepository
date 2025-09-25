// ***********************************************************
//
//  エラー定義
//
//
// 2021.4.2
// ************************************************************
#pragma once

//public、class削除(2025.5.15yori)
enum ERROR_CODE {
	ERROR_CODE_NONE = 0,								// エラーなし

	// スキャナキャリブレーション時エラーコード追加(2021.8.16yori)
	ERROR_CODE_TDS_ERR_CALIB_SHOT_DATA_HALF = 10,		// 点群数エラー(点群数半分以下)
	ERROR_CODE_TDS_ERR_CALIB_SHOT_AXIS,					// 座標系エラー
	ERROR_CODE_TDS_ERR_CALIB_SHOT_NEAR,					// 計測距離が近すぎる
	ERROR_CODE_TDS_ERR_CALIB_SHOT_FAR,					// 計測距離が遠すぎる
	ERROR_CODE_TDS_ERR_CALIB_SHOT_NO_DATA,				// 点群取得失敗
	ERROR_CODE_TDS_ERR_CALIB_SHOT_1AXIS,				// 1軸角度エラー
	ERROR_CODE_TDS_ERR_CALIB_SHOT_7AXIS,				// 7軸角度エラー
	ERROR_CODE_TDS_ERR_CALIB_SHOT_DATA_LACK,			// 点群欠損エラー
	ERROR_CODE_TDS_ERR_CALIB_SHOT_MAKE_SPH,				// 球作成失敗
	ERROR_CODE_TDS_ERR_CALIB_SHOT_2AXIS,				// 2軸角度エラー

	ERROR_CODE_TDS_ERR_CALIB_SHOT_MAKE_PLN,				// 面作成失敗

	ERROR_CODE_TDS_ERR_CALIB_CALCULATE = 30,			// キャリブレーション値作成失敗
	ERROR_CODE_TDS_ERR_CALIB_NO_CHANGE,					// キャリブレーション値変更なし
	ERROR_CODE_TDS_ERR_CALIB_CHANGE_OVER,				// キャリブレーション値変化量オーバーエラー
	//ERROR_CODE_TDS_ERR_HOLDER_CHANGE_OVER,			// ホルダ定数値変化量オーバーエラー ->上位アプリにてチェックしてください(ホルダ定数変化量オーバーエラーの場合でもキャリブ値は保存する仕様です)
	ERROR_CODE_TDS_ERR_CALIB_CALC_SHOT = 34,			// キャリブレーション計算を実行するショットNoでない

	ERROR_TDS_ERR_MACHINECHECK_DATA_LACK = 40,			// 始業前点検 面計測点数エラー(許容値設定よりも少ない)

	ERROR_CODE_OPEN = 100,								//「接続に失敗しました」→「接続できません。」(2021.10.28yori)
	ERROR_CODE_CONTACTLOST,								// Vectoronとの通信が失われました
	ERROR_CODE_CLOSE,									//切断に失敗しました
	ERROR_CODE_NONVEC,									//ベクトロンが接続されていません
	ERROR_CODE_SCANNER_INIT,							//スキャナーが初期化できません
	ERROR_CODE_SCANNER_INIT2,							//スキャナの初期化に失敗しました。スキャナがアームに接続されていません。(2022.4.6yori)
	ERROR_CODE_VEC_INIT,								//ベクトロンが初期化されていません
		
	ERROR_CODE_MODE_CHANGE = 200,						//モードが切り替わらない
	ERROR_CODE_MODE_PROVE,								//有接触モードに切り替わらない
	ERROR_CODE_MODE_LAZER,								//非接触モードに切り替わらない
	ERROR_CODE_MODE_INITIALIZE,							//イニシャライズモードに切り替わらない
	ERROR_CODE_MODE_TRACE,								//トレースモードに切り替わらない
	ERROR_CODE_MODE_ARM_MOUSE,							//アームマウスモードに切り替わらない
	ERROR_CODE_MODE_MAINTE,								//メンテナンスモードに切り替わらない
	ERROR_CODE_MODE_ROUCH,								//ラッチモードに切り替わらない
	ERROR_CODE_MODE_RE_INIT,							//再イニシャライズモードに切り替わらない



	ERROR_CODE_SEQRESET = 500,							// シーケンスカウンタがリセットできない
	ERROR_CODE_GETSTS,									// 設定の読み出しに失敗しました
	ERROR_CODE_SETPROBEID,								// プローブIDの設定に失敗しました
	ERROR_CODE_SETDIAMETER,								// スタイラス直径の設定に失敗しました
	ERROR_CODE_BEEP,									// Beep音切替に失敗しました。
	ERROR_CODE_VER,										// Ver取得にに失敗しました。

	ERROR_CODE_INISTSGET,								// イニシャライズ状態の情報取得に失敗しました
	ERROR_CODE_PROPETY,									// プロパティ情報取得に失敗しました。


	ERROR_CODE_VECBUFFER_CLEAR = 1000,					// べクロトン側バッファがクリアーできない
	ERROR_CODE_SCANBUFFER_CLEAR,						// スキャナー側バッファがクリアーできない
	ERROR_CODE_QUEBFFER,								// Queバッファがいっぱいです。

	ERROR_CODE_MEMORYMAPED_WRITE = 2000,				// Polyworks転送バッファに書き込みできない (メモリマップドファイル)

	ERROR_CODE_LINENUMBERMISSION = 3000,				//ライン番号抜けエラー

};

//public ref削除(2025.4.22yori)
class Error_Defin abstract sealed
{
public:

	static char* GetErrorString(ERROR_CODE code)
	{
		char* ptStr;

		switch (code)
		{
		default:
		case ERROR_CODE::ERROR_CODE_NONE: ptStr = "エラーなし";	break;

		// スキャナキャリブレーション時エラーメッセージ追加(2021.8.16yori)
		case ERROR_CODE::ERROR_CODE_TDS_ERR_CALIB_SHOT_DATA_HALF: ptStr = "点群数エラー"; break;
		case ERROR_CODE::ERROR_CODE_TDS_ERR_CALIB_SHOT_AXIS: ptStr = "座標系エラー"; break;
		case ERROR_CODE::ERROR_CODE_TDS_ERR_CALIB_SHOT_NEAR: ptStr = "計測距離が近すぎる"; break;
		case ERROR_CODE::ERROR_CODE_TDS_ERR_CALIB_SHOT_FAR: ptStr = "計測距離が遠すぎる"; break;
		case ERROR_CODE::ERROR_CODE_TDS_ERR_CALIB_SHOT_NO_DATA: ptStr = "点群取得失敗"; break;
		case ERROR_CODE::ERROR_CODE_TDS_ERR_CALIB_SHOT_1AXIS: ptStr = "1軸角度エラー"; break;
		case ERROR_CODE::ERROR_CODE_TDS_ERR_CALIB_SHOT_7AXIS: ptStr = "7軸角度エラー"; break;
		case ERROR_CODE::ERROR_CODE_TDS_ERR_CALIB_SHOT_DATA_LACK: ptStr = "点群欠損エラー"; break;
		case ERROR_CODE::ERROR_CODE_TDS_ERR_CALIB_SHOT_MAKE_SPH: ptStr = "球作成失敗"; break;
		case ERROR_CODE::ERROR_CODE_TDS_ERR_CALIB_SHOT_2AXIS: ptStr = "2軸角度エラー"; break;

		case ERROR_CODE::ERROR_CODE_TDS_ERR_CALIB_SHOT_MAKE_PLN: ptStr = "面作成失敗"; break;

		case ERROR_CODE::ERROR_CODE_TDS_ERR_CALIB_CALCULATE: ptStr = "キャリブレーション値作成失敗"; break;
		case ERROR_CODE::ERROR_CODE_TDS_ERR_CALIB_NO_CHANGE: ptStr = "キャリブレーション値変更なし"; break;
		case ERROR_CODE::ERROR_CODE_TDS_ERR_CALIB_CHANGE_OVER: ptStr = "キャリブレーション値変化量オーバーエラー"; break;
		case ERROR_CODE::ERROR_CODE_TDS_ERR_CALIB_CALC_SHOT: ptStr = "キャリブレーション計算を実行するショットNoでない"; break;

		case ERROR_CODE::ERROR_TDS_ERR_MACHINECHECK_DATA_LACK: ptStr = "面計測点数エラー"; break;

		case ERROR_CODE::ERROR_CODE_OPEN: ptStr = "接続できません。";	break; //「接続に失敗しました」を変更(2021.10.28yori)
		case ERROR_CODE::ERROR_CODE_CONTACTLOST: ptStr = "アームとの通信が失われました。";	break; //「Vectoronとの通信が失われました」を変更(2022.3.18yori)
		case ERROR_CODE::ERROR_CODE_CLOSE: ptStr = "切断に失敗しました。";	break;
		case ERROR_CODE::ERROR_CODE_NONVEC: ptStr = "アームが接続されていません。";	break; //「ベクトロンが接続されていません」を変更(2022.3.18yori)
		case ERROR_CODE::ERROR_CODE_SCANNER_INIT: ptStr = "スキャナの初期化に失敗しました。\nコントローラの接続を確認してください。";	break; //「スキャナーが初期化できません」を変更(2022.3.18yori) //「スキャナが初期化できません。」を変更(2022.4.6yori)
		case ERROR_CODE::ERROR_CODE_SCANNER_INIT2: ptStr = "スキャナの初期化に失敗しました。\nスキャナがアームに接続されていません。";	break; //(2022.4.6yori)
		case ERROR_CODE::ERROR_CODE_VEC_INIT: ptStr = "ベクトロンが初期化されていません。";	break; //「ベクトロンが初期化されていません」を変更(2022.3.18yori)
			
		case ERROR_CODE::ERROR_CODE_MODE_CHANGE: ptStr = "モードが切り替わりません。";	break; //「モードが切り替わらない」を変更(2022.3.18yori)
		case ERROR_CODE::ERROR_CODE_MODE_PROVE: ptStr = "有接触モードに切り替わりません。";	break; //「有接触モードに切り替わらない」を変更(2022.3.18yori)
		case ERROR_CODE::ERROR_CODE_MODE_LAZER: ptStr = "非接触モードに切り替わりません";	break; //「非接触モードに切り替わらない」を変更(2022.3.18yori)
		case ERROR_CODE::ERROR_CODE_MODE_INITIALIZE: ptStr = "イニシャライズモードに切り替わりません。";	break; //「イニシャライズモードに切り替わらない」を変更(2022.3.18yori)
		case ERROR_CODE::ERROR_CODE_MODE_TRACE: ptStr = "トレースモードに切り替わりません。";	break; //「トレースモードに切り替わらない」を変更(2022.3.18yori)
		case ERROR_CODE::ERROR_CODE_MODE_ARM_MOUSE: ptStr = "アームマウスモードに切り替わりません。";	break;//「アームマウスモードに切り替わらない」を変更(2022.3.18yori)
		case ERROR_CODE::ERROR_CODE_MODE_MAINTE:ptStr = "メンテナンスモードに切り替わりません。";	break; //「メンテナンスモードに切り替わらない」を変更(2022.3.18yori)
		case ERROR_CODE::ERROR_CODE_MODE_ROUCH: ptStr = "ラッチモードに切り替わりません。";	break; //「ラッチモードに切り替わらない」を変更(2022.3.18yori)
		case ERROR_CODE::ERROR_CODE_MODE_RE_INIT: ptStr = "再イニシャライズモードに切り替わりません。";	break; //「再イニシャライズモードに切り替わらない」を変更(2022.3.18yori)

		case ERROR_CODE::ERROR_CODE_SEQRESET: ptStr = "シーケンスカウンタがリセットできません。";	break; //「シーケンスカウンタがリセットできない」を変更(2022.3.18yori)
		case ERROR_CODE::ERROR_CODE_GETSTS: ptStr = "設定の読み出しに失敗しました。";	break;
		case ERROR_CODE::ERROR_CODE_SETPROBEID: ptStr = "プローブIDの設定に失敗しました。";	break;
		case ERROR_CODE::ERROR_CODE_SETDIAMETER: ptStr = "スタイラス直径の設定に失敗しました。";	break;
		case ERROR_CODE::ERROR_CODE_BEEP: ptStr = "ビープ音切替に失敗しました。";	break; //「Beep音切替に失敗しました」を変更(2022.3.18yori)
		case ERROR_CODE::ERROR_CODE_VER: ptStr = "バージョン取得にに失敗しました。";	break; //「Ver取得にに失敗しました」を変更(2022.3.18yori)

		case ERROR_CODE::ERROR_CODE_INISTSGET: ptStr = "イニシャライズ状態の情報取得に失敗しました。";	break;
		case ERROR_CODE::ERROR_CODE_PROPETY: ptStr = "プロパティ情報取得に失敗しました。";	break;

		case ERROR_CODE::ERROR_CODE_VECBUFFER_CLEAR: ptStr = "アームのバッファがクリアできません。";	break; //「べクロトン側バッファがクリアーできない」を変更(2022.3.18yori)
		case ERROR_CODE::ERROR_CODE_SCANBUFFER_CLEAR: ptStr = "スキャナのバッファがクリアーできません。";	break; //「スキャナー側バッファがクリアーできない」を変更(2022.3.18yori)

		case ERROR_CODE::ERROR_CODE_QUEBFFER: ptStr = "Queバッファがいっぱいです。";	break;

		case ERROR_CODE::ERROR_CODE_MEMORYMAPED_WRITE: ptStr = "Polyworks転送バッファに書き込みできません。";	break; //「Polyworks転送バッファに書き込みできない (メモリマップドファイル)」を変更(2022.3.18yori)

		case ERROR_CODE::ERROR_CODE_LINENUMBERMISSION: ptStr = "ライン番号抜けエラー";	break;
		}
		return ptStr;
	}

};

