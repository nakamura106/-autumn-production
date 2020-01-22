#ifndef SOUNDMANAGER_H_
#define SOUNDMANAGER_H_

#include "AudioPlayer.h"
#include <string>

class SoundManager
{
public:
	static SoundManager* Instance();

	// 各シーンごとの音素材登録
	void RegisterTitleSound();		// タイトル
	void RegisterSelectSound();		// セレクト
	void RegisterGameMainSound();	// ゲームメイン
	void RegisterEndSound();		// ゲームエンド

	// 鳴らす関数
	void SoundBGM();
	void SoundSelectBGM();
	void SoundSelectSE();
	void SoundSelect2SE();
	void SoundSelect3SE();
	void SoundClickSE();

	void ResetSelectFlag();

	// 解放関数
	void ReleaseTitleSound();
	void ReleaseSelectSound();

protected:
	SoundManager();
	~SoundManager();

private:
	static SoundManager* p_instance;

	bool m_select1_flag;	// selectSEをループさせないためのフラグ
	bool m_select2_flag;
	bool m_select3_flag;

	
	std::string m_bgm;
	std::string m_select1_se;
	std::string m_select2_se;
	std::string m_select3_se;
	std::string m_click_se;

	std::string m_bgm_file;
	std::string m_se1_file;
	std::string m_se2_file;
	std::string m_se3_file;
	std::string m_click_se_file;

	int i = 0;

	AudioPlayer* m_pAudio = AudioPlayer::GetInstance(GetWindowHandle());
};

#endif

