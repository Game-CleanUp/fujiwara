#include "CEffect.h"

CEffect::CEffect(const CVector &pos, float w, float h, std::shared_ptr<CTexture> texture, int row, int col, int fps)
: CBillBoard(pos, w, h), mRows(row), mCols(col), mFps(fps), mFrame(0)
{
	mMaterial.mpTexture = texture;

	//描画優先度(最後に表示)
	mPriority = 0;
	CTaskManager::Get()->Remove(this); //リストから削除する
	CTaskManager::Get()->Add(this); //リストに追加する

}

void CEffect::Update() {

	//コマ数の計算
	int frame = mFrame++ / mFps;

	//アニメーション終了で無効
	if (frame >= mRows * mCols){
		mEnabled = false;
	}

	frame %= (mRows * mCols);
	//UV左
	float left = 1.0f / mCols * (frame % mCols);
	//UV右
	float righ = left + 1.0f / mCols;
	//UV上
	float top = 1.0f - 1.0f / mRows * (frame / mCols);
	//UV下
	float bot = top - 1.0f / mRows;
	//テクスチャマッピング
	mT[0].mUv[0] = CVector(righ, top, 0.0f);
	mT[0].mUv[1] = CVector(left, bot, 0.0f);
	mT[0].mUv[2] = CVector(righ, bot, 0.0f);
	mT[1].mUv[0] = CVector(left, top, 0.0f);
	mT[1].mUv[1] = CVector(left, bot, 0.0f);
	mT[1].mUv[2] = CVector(righ, top, 0.0f);
	//ビルボード更新
	CBillBoard::Update();
}
