/**************************************************************************
 WinMain.cpp

 WindowProc()関数
 WinMain()関数
****************************************************************************/
#include "StdAfx.h"
#include "DxDevice.h"
#include "Scene.h"
#include "TatraFactory/ScriptManager.h"

/**************************************************************************
LRESULT CALLBACK WindowProc(
HWND hWnd,      //ウィンドウハンドル
UINT msg,       //メッセージ
WPARAM wParam,  //メッセージの最初のパラメータ
LPARAM lParam   //メッセージの2番目のパラメータ
)
用途: ウインドウプロシージャ
戻り値: メッセージ処理結果
***************************************************************************/
LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg) {
        case WM_DESTROY:                // ウインドウが破棄されようとしている
            ::PostQuitMessage(0);       // アプリケーションを終了する
            return 0;
        break;
        case WM_KEYDOWN:                // キーが押された
            if (wParam == VK_ESCAPE) {  // 押されたのはESCキーだ
                ::DestroyWindow(hWnd);  // ウインドウを破棄するよう要求する
            }
			wiz::XBoxController::KeyBoardState = wParam;
            return 0;
        break;
		case WM_MOUSEMOVE:	// マウスカーソルが移動したときに送られてくる
			// 移動先の座標を取得
			wiz::XBoxController::MousePoint.x = LOWORD( lParam );
			wiz::XBoxController::MousePoint.y = HIWORD( lParam );
			return 0;
			break;
        case WM_ACTIVATEAPP:
            if( wParam == TRUE ){
                XInputEnable( true );
            }
            else{
                XInputEnable( false );
            }
            return 0;
        default:
        break;
    }
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}
/**************************************************************************
 関数名:int WINAPI WinMain(
        HINSTANCE hInstance,            //インスタンスのハンドル
        HINSTANCE hPrevInstance,        //以前のインスタンス
        LPSTR lpCmdLine,                //コマンドライン
        int nShowCmd                    //起動時の状態
        );
 用途: エントリポイント。
 戻り値: 終了コード
****************************************************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE 
    hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
    //定数
    const wchar_t* pClassName = L"MLPClass";
    const wchar_t* pWndTitle = L"M.L.P.";
    //ウインドウの幅と高さ
    int iClientWidth = ___MLP_WINDOWSIZE_WIDTH;
    int iClientHeight = ___MLP_WINDOWSIZE_HEIGHT;
    // フルスクリーンにするかどうかの判定
    // コマンドラインに/fか/Fが設定されていたらフルスクリーンにする
    bool isFullScreen = false;
    for(int i = 0; i < nShowCmd; i++) {
        if(_stricmp((char*)&lpCmdLine[i], "/f") == 0) { // コマンドラインに/fを発見
 			isFullScreen = true;
           break;
        }
    }
  //WNDCLASSEX構造体の初期化
    WNDCLASSEX wcex;
    wcex.cbSize         = sizeof(WNDCLASSEX);	    //この構造体のサイズ
    wcex.style          = 0;                        //自動的にredrawをかけない
    wcex.lpfnWndProc    = WindowProc;               //ウインドウプロシージャ（コールバック関数）の指定
    wcex.cbClsExtra     = 0;                        //常に0
    wcex.cbWndExtra     = 0;                        //常に0
    wcex.hInstance      = hInstance;                //アプリケーションのインスタンスを指定
    wcex.hIcon          = LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON2));	//アイコンの指定（ここではNULL）
    wcex.hCursor        = ::LoadCursor(NULL, IDC_ARROW);					//通常の矢印カーソル
    wcex.hbrBackground  = NULL;						//背景なし
    wcex.lpszMenuName   = NULL;                     //メニューなし
    wcex.lpszClassName  = pClassName;               //クラス名の指定
    wcex.hIconSm        = LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON2));;	//小さいアイコンなし
    //ウインドウクラスの登録
    if (!::RegisterClassEx(&wcex))
    {
        //失敗した
        ::MessageBox(NULL,L"ウインドウクラス登録に失敗しました",L"エラー",MB_OK);
        return 1;   //エラー終了
    }
    HWND hWnd;
    // ウィンドウの作成
    if(isFullScreen) { // フルスクリーン
        // 画面全体の幅と高さを取得
        iClientWidth = ::GetSystemMetrics(SM_CXSCREEN);
        iClientHeight = ::GetSystemMetrics(SM_CYSCREEN);
        hWnd = ::CreateWindowEx( 
            0,                  //オプションのウィンドウスタイル
            pClassName,         // 登録されているクラス名
            pWndTitle,          // ウインドウ名
            WS_POPUP,           // ウインドウスタイル（ポップアップウインドウを作成）
            0,                  // ウインドウの横方向の位置
            0,                  // ウインドウの縦方向の位置
            iClientWidth,       // フルスクリーンウインドウの幅
            iClientHeight,      // フルスクリーンウインドウの高さ
            NULL,               // 親ウインドウのハンドル（なし）
            NULL,               // メニューや子ウインドウのハンドル
            hInstance,          // アプリケーションインスタンスのハンドル
            NULL                // ウインドウの作成データ
        );
        if (!hWnd){
            //失敗した
            ::MessageBox(0,L"ウインドウ作成に失敗しました",L"エラー",MB_OK);
            return 1;   //エラー終了
        }
    }
    else {
        //ウインドウの作成
        hWnd = ::CreateWindowEx(
            0,                              //オプションのウィンドウスタイル
            pClassName,                     //ウインドウクラス名
            pWndTitle,                      //ウインドウのタイトル
            WS_OVERLAPPEDWINDOW,            //移動バーをもつ通常のウインドウ
            CW_USEDEFAULT, CW_USEDEFAULT,   //位置はWindowsに任せる
            iClientWidth,                    //ウインドウ幅（暫定）
            iClientHeight,                   //ウインドウ高さ（暫定）
            NULL,                            //親ウインドウ（トップレベルなので、なし）
            NULL,                           //メニューなし
            hInstance,                      //このインスタンス
            NULL                            //使用しない
        );
        if (!hWnd){
            //失敗した
            ::MessageBox(0,L"ウインドウ作成に失敗しました",L"エラー",MB_OK);
            return 1;   //エラー終了
        }
        // ウィンドウサイズを再設定する
        RECT rect;
        int w_width,w_height,c_width,c_height;
        // ウインドウ全体の大きさを計算
        ::GetWindowRect(hWnd,&rect);       // ウインドウ全体のサイズ取得
        w_width = rect.right - rect.left;   // ウインドウ全体の幅の横幅を計算
        w_height = rect.bottom - rect.top;  // ウインドウ全体の幅の縦幅を計算
        // クライアント領域の大きさを計算
        ::GetClientRect(hWnd,&rect);       // クライアント部分のサイズの取得
        c_width = rect.right - rect.left;   // クライアント領域外の横幅を計算
        c_height = rect.bottom - rect.top;  // クライアント領域外の縦幅を計算
        // ウィンドウサイズの再計算
        w_width = iClientWidth + (w_width - c_width);     // 必要なウインドウの幅
        w_height = iClientHeight + (w_height - c_height); // 必要なウインドウの高さ
        // ウインドウサイズの再設定
        ::SetWindowPos(hWnd,HWND_TOP,0,0,w_width,w_height,SWP_NOMOVE);
    }
    //ウインドウの表示
    ::ShowWindow(
        hWnd,       //取得したウインドウのハンドル
        nShowCmd    //WinMainに渡されたパラメータ
    );
    // WM_PAINTが呼ばれないようにする
    ::ValidateRect(hWnd, 0);
    //例外処理開始
    try{
        // DirectXデバイスオブジェクトの初期化
        wiz::DxDevice device(hWnd, isFullScreen,iClientWidth,iClientHeight);
        //シーンの初期化
        wiz::Scene scene(device.getDevice());
		//	: 時間系の初期化
 		wiz::Tempus::Tempus();
		wiz::Script::ScriptManager::ScriptManager();
        //メッセージループ
        MSG msg;    //メッセージ構造体の宣言定義
		//::System::Diagnostics::Process^ myProcess = nullptr;
		//myProcess = ::System::Diagnostics::Process::Start("M.L.P.exe");
        while(true){
            if(::PeekMessage(&msg,NULL,0,0,PM_REMOVE)){
				if(msg.message == WM_QUIT){ // PostQuitMessage()が呼ばれた
                    break;  //ループの終了
                }
                else{
                    // メッセージの翻訳とディスパッチ
                    ::TranslateMessage(&msg);
                    ::DispatchMessage(&msg);
                }
            }
            else {  // 処理するメッセージが無いときは描画を行う
				//	: 時間系の設定
				wiz::Tempus::TimeUpdate();
                // ウィンドウが見えている時だけ描画するための処理
                WINDOWPLACEMENT wndpl;
                ::GetWindowPlacement(hWnd, &wndpl); // ウインドウの状態を取得
                //if((wndpl.showCmd != SW_HIDE) && 
                //    (wndpl.showCmd != SW_MINIMIZE) &&
                //    (wndpl.showCmd != SW_SHOWMINIMIZED) &&
                //    (wndpl.showCmd != SW_SHOWMINNOACTIVE)) {
                    // 描画処理の実行
                    device.RenderScene(&scene);
				//}
            }
        }
        //msg.wParamには終了コードが入っている
        return (int) msg.wParam;
    }
    catch(wiz::DxException& e){
        //実行失敗した
        ::MessageBox(hWnd,e.what_w(),L"エラー",MB_OK);
        return 1;   //エラー終了
    }
    catch(exception& e){
        //STLエラー
        //マルチバイトバージョンのメッセージボックスを呼ぶ
        ::MessageBoxA(hWnd,e.what(),"エラー",MB_OK);
        return 1;   //エラー終了
    }
    catch(...){
        //原因不明失敗した
        ::MessageBox(hWnd,L"原因不明のエラーです",L"エラー",MB_OK);
        return 1;   //エラー終了
    }
    //例外処理終了
    return 1;   //エラー終了
}

