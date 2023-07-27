#include <DxLib.h>
#include <string>
#include<math.h>
#include"circle_collition.h"

namespace {
	bool keystop=false;




	/* 斜めのお試し*/

	//XY座標
	int x=0,y=0;
	//速さ
	int sonic = 0;
	//動く距離
	int sx = 0, sy = 0;
	//ただのお遊び
	int count = 0;

	/*~斜めのお試し*/




	/*自機狙いの動き*/

	//自機のXY座標
	int px=0, py = 0;
	//敵のXY座標
	int ex=0, ey = 0;
	//XY移動距離
	int ux=0, uy = 0;
	//求められた角度　整数か、小数点で変わる動き
	double kakudo = 0;
	//以下自機を動かす系
	int idoux=0, idouy=0;

	/*~自機狙いの動き*/

}

//最初に1回呼ばれる処理
void Init(){

	/* 斜めのお試し*/

	//速さを指定
	sonic = 5;
	//X移動距離を求める計算
	sx = sonic*cos(45);
	//Y移動距離を求める計算
	sy = sonic*sin(45);

	/*~斜めのお試し*/



	/*自機狙いの動き*/

	//時キャラXY座標
	px = 300;
	py = 200;
	//敵XY座標
	ex = 00;
	ey = 100;
	//敵と自分の角度を求める式
	kakudo=atan2(py - ey,px - ex);
	//移動距離を求める式
	ux = sonic * cos(kakudo);
	uy = sonic * sin(kakudo);

	/*~自機狙いの動き*/
}
//毎フレーム呼ばれる処理
void Update() {
	


	/* 斜めのお試し*/

	//お遊び
	if (59 == count++ % 60) {
		sx = -sx;
		sy = -sy;
	}
	//XY座標へ、移動距離の代入
	x += sx;
	y += sy;

	/*~斜めのお試し*/





	/*自機狙いの動き*/
	int dis = 150;//半径
	int rad = 50; //判定位置の調整
	//円の当たり判定
	if (
		circlecollition(px + rad, py + rad, dis, ex + rad, ey + rad, dis) == false
		) {
		//敵と自分の角度を求める式
		kakudo = atan2(py - ey, px - ex);
		printfDx("%f\n", kakudo);
		//移動距離を求める式
		ux = sonic * cos(kakudo);
		uy = sonic * sin(kakudo);
	}




	
		//Xの移動処理
		if (ex != px) {
			ex += ux;
		}
		else {
			printfDx("X止まり\n");
		}
		//Yの移動処理
		if (ey != py) {
			ey += uy;
		}
		else {
			printfDx("Y止まり\n");
		}

	//以下、自機を動かす処理系
	if (CheckHitKey(KEY_INPUT_W)) {
		idouy -= 1;
	}
	if (CheckHitKey(KEY_INPUT_S)) {
		idouy += 1;
	} if (CheckHitKey(KEY_INPUT_A)) {
		idoux -= 1;
	} if (CheckHitKey(KEY_INPUT_D)) {
		idoux += 1;
	}

	if (CheckHitKey(KEY_INPUT_W) == 0 &&
		CheckHitKey(KEY_INPUT_S) == 0) {
		if (idouy <= -1) {
			idouy += 1;
		}
		else if (idouy >= 1) {
			idouy -= 1;
		}
		else {
			idouy = 0;
		}

	}
	if (CheckHitKey(KEY_INPUT_A) == 0 &&
		CheckHitKey(KEY_INPUT_D) == 0) {
		if (idoux <= -1) {
			idoux += 1;
		}
		else if (idoux >= 1) {
			idoux -= 1;
		}
		else {
			idoux = 0;
		}

	}

	if (idouy >= 10) {
		idouy = 10;
	}
	else if (idouy <= -10) {
		idouy = -10;
	}
	if (idoux >= 10) {
		idoux = 10;
	}
	else if (idoux <= -10) {
		idoux = -10;
	}

	py += idouy;
	px += idoux;

	/*~自機狙いの動き*/


}
void Draw() {
	/* 斜めのお試し*/

	//色の指定（ついでに四角の大きさも）
	int color = 100;
	//表示
	DrawBox(x, y, (x + color), (y + color), GetColor(color - 50, color - 50, color - 50), true);

	/*~斜めのお試し*/





	/*自機狙いの動き*/

	//表示
	DrawBox(ex, ey, ex + color, ey + color, GetColor(color * 2, color * 2, color * 2), true);
	DrawBox(px - 1, py - 1, px + color, py + color, GetColor(color, color, color), true);


	//当たり判定表示
	int dis = 150;//半径
	int rad = 50; //判定位置の調整
	DrawCircle(ex + rad, ey + rad, dis, GetColor(255, 0, 0), false);
	DrawCircle(px + rad, py + rad, dis, GetColor(255, 0, 0), false);

	/*~自機狙いの動き*/

	printfDx("%d\n", idoux);
	printfDx("%d\n", idouy);

}
void Delete(){
	
}
// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(false);
	ChangeWindowMode(TRUE);	//ウィンドウモードにする
	SetGraphMode(800, 600, 32);	//ウィンドウサイズを設定する
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	SetDrawScreen(DX_SCREEN_BACK);	//裏画面を描画対象へ

	Init();//初期化
	//メイン処理
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		clsDx();
		Update();//更新処理
		Draw();//描画処理

		ScreenFlip();		//裏画面と表画面の入替
		ClearDrawScreen();	//裏画面の描画を全て消去
	}
	Delete();
	DxLib_End();			// ＤＸライブラリ使用の終了処理
	return 0;				// ソフトの終了 
}