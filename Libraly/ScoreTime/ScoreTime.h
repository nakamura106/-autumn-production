#ifndef SCORETIME_H_
#define SCORETIME_H_

class ScoreTime
{
public:
	ScoreTime();
	~ScoreTime();

	void TransformFlametoTime();

	void DrawScore();

private:
	int m_score_time;

};

#endif
