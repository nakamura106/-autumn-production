#ifndef DATABANK_H_
#define DATABANK_H_

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
	void SetfgPos(float fg_) { m_fg = fg_; }
	void Setfloor1Pos(float floor1_) { m_floor1 = floor1_; }
	void SetPlayerMapPos(int mPos) { m_map_pos = mPos; }
	void SetSleepGauge(float sleep_hp) { m_sleep_gauge = sleep_hp; }
	void SetFatigueGauge(float fatigue_hp) { m_fatigue_gauge = fatigue_hp; }

	int GetPlayerHp() { return m_player_hp; }
	int GetNote1() { return note1; }
	int GetNote2() { return note2; }
	int GetNote3() { return note3; }
	float GetfgPos(){ return m_fg; }
	float Getfloor1Pos() { return m_floor1; }
	float GetPlayerMapPos() { return m_map_pos; }
	float GetSleepGauge() { return m_sleep_gauge; }
	float GetFatigueGauge() { return m_fatigue_gauge; }

	int GetPlayerHp()const { return m_player_hp; }

protected:
	DataBank();
	~DataBank();

private:
	int m_player_hp;
	int note1;
	int note2;
	int note3;
	float m_map_pos;
	float m_fg;
	float m_floor1;
	
	float m_sleep_gauge, m_fatigue_gauge;

private:
	static DataBank* p_instance;

};

#endif

