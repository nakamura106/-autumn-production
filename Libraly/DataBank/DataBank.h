#ifndef DATABANK_H_
#define DATABANK_H_

class DataBank
{
public:
	static DataBank* Instance();

	void SetPlayerHp(int hp) { m_player_hp = hp; }
	void SetSleepGauge(float sleep_hp) { m_sleep_gauge = sleep_hp; }
	void SetFatigueGauge(float fatigue_hp) { m_fatigue_gauge = fatigue_hp; }

	int GetPlayerHp() { return m_player_hp; }
	float GetSleepGauge() { return m_sleep_gauge; }
	float GetFatigueGauge() { return m_fatigue_gauge; }

	int GetPlayerHp()const { return m_player_hp; }

protected:
	DataBank();
	~DataBank();

private:
	int m_player_hp;
	float m_sleep_gauge, m_fatigue_gauge;

private:
	static DataBank* p_instance;

};

#endif

