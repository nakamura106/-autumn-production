#ifndef DATABANK_H_
#define DATABANK_H_
#include "../Object/Definition.h"

class DataBank
{
public:
	static DataBank* Instance();

	void SetPlayerHp(int hp) { m_player_hp = hp; }
	void SetNote(int note1_, int note2_, int note3_) {
		note1 = note1_;
		note2 = note2_;
		note3 = note3_;
	}
	void SetBulletType(int bullet_type_) { m_bullet_type = bullet_type_; }
	void SetfgPos(float fg_) { m_fg = fg_; }
	void Setfloor1Pos(float floor1_) { m_floor1 = floor1_; }
	void SetPlayerMapPos(int mPos) { m_map_pos = mPos; }
	void SetSleepGauge(float sleep_hp) { m_sleep_gauge = sleep_hp; }
	void SetFatigueGauge(float fatigue_hp) { m_fatigue_gauge = fatigue_hp; }
	void SetIsGameClear(bool is_game_clear_) { m_is_game_clear = is_game_clear_; }
	void SetPlayerType(int Which_type_of_player) { m_PlayerType = Which_type_of_player; };
	void SetMapType(int Which_type_of_map) { m_MapType = Which_type_of_map; };
	void SetIsGameOver(bool is_game_over_) { m_is_game_over = is_game_over_; }
	void SetPlayerCenter(Position position_) { m_centerpos = position_; }

	int GetPlayerHp() { return m_player_hp; }
	int GetNote1() { return note1; }
	int GetNote2() { return note2; }
	int GetNote3() { return note3; }
	int GetBulletType() { return m_bullet_type; }
	int GetPlayerType() { return m_PlayerType; }
	int GetMapType() { return m_MapType; }
	int GetPlayerHp()const { return m_player_hp; }
	float GetfgPos(){ return m_fg; }
	float Getfloor1Pos() { return m_floor1; }
	float GetPlayerMapPos() { return m_map_pos; }
	float GetSleepGauge() { return m_sleep_gauge; }
	float GetFatigueGauge() { return m_fatigue_gauge; }
	bool GetIsGameClear() { return m_is_game_clear; }
	bool GetIsGameOver() { return m_is_game_over; }
	Position GetPlayerCenter() { return m_centerpos; }
	

protected:
	DataBank();
	~DataBank();

private:
	int m_player_hp;
	int note1;
	int note2;
	int note3;

	int m_bullet_type;	// PlayerBulletTypeï€ë∂ïœêî

	int m_PlayerType;

	int m_MapType;


	float m_map_pos;
	float m_fg;
	float m_floor1;
	
	float m_sleep_gauge, m_fatigue_gauge;

	bool m_is_game_clear;
	bool m_is_game_over;

	Position m_centerpos;

private:
	static DataBank* p_instance;

};

#endif

