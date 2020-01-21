#pragma once
#include"../Object/Definition.h"
#include<string>

const std::string g_save_file_name = "Res/Csv/SaveData/SaveData1.csv";

class SaveData {
public:
	SaveData();
	~SaveData();

	/*�C���X�^���X�Q�b�^�[*/
	static SaveData& GetInstance() {
		static SaveData save_data;
		return save_data;
	}

	/*�Q�b�^�[�Q*/
	bool GetIsDataExist() { return m_is_data_exist; }
	int GetClearItemNum() { return m_clear_item_num; }
	int GetClearTime(ClearTimeType clear_time_type_);

	/*�̍��l�����X�V�֐�*/
	bool SetClearItemNum(int clear_item_num_);

	/*�n�C�X�R�A�X�V�ݒ�֐�*/
	bool SetNewClearTime(ClearTimeType clear_time_type_, int clear_time_num_);

	/*csv�t�@�C������f�[�^�����*/
	bool GetCsvFileData();

	/*csv�t�@�C���Ƀf�[�^����������*/
	bool SetCsvFileData();

private:
	bool m_is_data_exist;	//�f�[�^�����݂��邩
	int m_clear_item_num;	//�̍��l����
	int m_clear_time[static_cast<int>(ClearTimeType::ClearTimeType_Max)];//�N���A�^�C��

};

