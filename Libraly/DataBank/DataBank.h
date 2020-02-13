#ifndef DATABANK_H_
#define DATABANK_H_
#include "../Object/Definition.h"

class DataBank
{
public:
	static DataBank* Instance();

	//Ÿ‚ÌƒQ[ƒ€‚Å‰Šú‰»‚µ‚È‚¢‚Æ‚¢‚¯‚È‚¢’l
	void ResetData();

	void SetPlayerHp(int hp) { m_player_hp = hp; }
	void SetNote(int note1_, int note2_, int note3_) {
		note1 = note1_;
		note2 = note2_;
		note3 = note3_;
	}
	void SetBulletType(int bullet_type_) { m_bullet_type = bullet_type_; }
	void SetfgPos(float fg_) { m_fg = fg_; }
	void Setfloor1Pos(float floor1_) { m_floor1 = floor1_; }
	void SetPlayerMapPos(float mPos) { m_map_pos = mPos; }
	void SetSleepGauge(float sleep_hp) { m_sleep_gauge = sleep_hp; }
	void SetFatigueGauge(float fatigue_hp) { m_fatigue_gauge = fatigue_hp; }
	void SetIsGameClear(bool is_game_clear_) { m_is_game_clear = is_game_clear_; }
	void SetPlayerType(int Which_type_of_player) { m_PlayerType = Which_type_of_player; };
	void SetMapType(int Which_type_of_map) { m_MapType = Which_type_of_map; };
	void SetIsGameOver(bool is_game_over_) { m_is_game_over = is_game_over_; }
	void SetPlayerDirection(int direction_) { m_Pdirection = direction_; }
	void SetPlayerEffect(P_effect effect_);
	void SetWaveState(WaveState wave_state_) { m_wave_state = wave_state_; }
	void SetState(int state_) { m_state = state_; }
	void SetWave(WaveType wave_,bool torf_) { m_wave_change[(int)wave_] = torf_; }
	void SetIsDebuff(bool is_debuff) { m_is_debuff = is_debuff; }
	void SetIsHitBanana(bool is_hit_banana) { m_is_hit_banana = is_hit_banana; }
	void SetIsHitShit(bool is_hit_shit) { m_is_hit_shit = is_hit_shit; }
	void SetDoEnemyDeadlyAi(bool do_e_deadly_ai_) { m_do_enemy_deadly_ai = do_e_deadly_ai_; }
	void SetBulletDeathPos(Position pos) { m_bullet_death_pos.x = pos.x; m_bullet_death_pos.y = pos.y; }
	void SetBulletDeathPosClear() { m_bullet_death_pos.x = 0.f; m_bullet_death_pos.y = 0.f; }
	void SetGameStartFlame(int flame) { m_game_start_flame = flame; }
	void SetGameEndFlame(int flame) { m_game_end_flame = flame; }
	

	int GetPlayerHp() { return m_player_hp; }
	int GetNote1() { return note1; }
	int GetNote2() { return note2; }
	int GetNote3() { return note3; }
	int GetBulletType() { return m_bullet_type; }
	int GetPlayerType() { return m_PlayerType; }
	int GetMapType() { return m_MapType; }
	int GetPlayerHp()const { return m_player_hp; }
	int GetPlayerdirection() { return m_Pdirection; }
	int GetPlayerEffect(P_effect p_effect_);
	int GetState() { return m_state; }
	float GetfgPos(){ return m_fg; }
	float Getfloor1Pos() { return m_floor1; }
	float GetPlayerMapPos() { return m_map_pos; }
	float GetSleepGauge() { return m_sleep_gauge; }
	float GetFatigueGauge() { return m_fatigue_gauge; }
	bool GetIsSleepMax() { return m_sleep_gauge >= Sleep_Gauge_Max; }
	bool GetIsFatigueGauge() { return m_fatigue_gauge >= Fatigue_Gauge_Max; }
	bool GetIsGameClear() { return m_is_game_clear; }
	bool GetIsGameOver() { return m_is_game_over; }
	bool GetWavetype(WaveType wave_) { return m_wave_change[(int)wave_]; }
	bool GetIsDebuff() { return m_is_debuff; }
	bool GetIsHitBanana() { return m_is_hit_banana; }
	bool GetIsHitShit() { return m_is_hit_shit; }
	bool GetDoEnemyDeadlyAi() { return m_do_enemy_deadly_ai; }
	int GetGameStartFlame() { return m_game_start_flame; }
	int GetGameEndFlame() { return m_game_end_flame; }
	Position GetBulletDeathPos() { return m_bullet_death_pos; }
	 
	WaveState GetWaveState() { return m_wave_state; }

	
	

protected:
	DataBank();
	~DataBank();

private:
	int m_player_hp;
	int note1;
	int note2;
	int note3;

	int m_bullet_type;	// PlayerBulletType•Û‘¶•Ï”

	int m_PlayerType;

	int m_MapType;

	int m_state;


	float m_map_pos;
	float m_fg;
	float m_floor1;
	
	
	float m_sleep_gauge, m_fatigue_gauge;

	bool m_is_debuff;
	bool m_is_hit_banana;
	bool m_is_hit_shit;
	bool m_is_game_clear;
	bool m_is_game_over;
	bool m_wave_change[(int)WaveType::WaveMax];
	bool m_PlayerEffect[(int)P_effect::MaxEffect];

	int m_Pdirection;
	Position m_centerpos;
	WaveState m_wave_state;

	bool m_do_enemy_deadly_ai;//“G‚Ì•KE‹Z‚ª“®‚¢‚Ä‚¢‚é‚©‚Ç‚¤‚©

	Position m_bullet_death_pos; // ƒvƒŒƒCƒ„[‚Ì‹Ê‚ª€‚ñ‚¾‚Æ‚«‚ÌÀ•W

	int m_game_start_flame, m_game_end_flame;

private:
	static DataBank* p_instance;

};

#endif

