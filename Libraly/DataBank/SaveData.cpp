#include"DataBank.h"
#include "SaveData.h"
#include"../Engine/FileLoader.h"

SaveData::SaveData()
{
	//csv�t�@�C���ǂݍ��݂����s�����ꍇ�A0������
	if (GetCsvFileData() != true) {

		m_is_data_exist = false;

		m_clear_item_num = 0;

		for (int i = 0;i < static_cast<int>(ClearTimeType::ClearTimeType_Max);++i) {
			m_clear_time[i] = 0;
		}
	}
}

SaveData::~SaveData()
{
}

int SaveData::GetClearTime(ClearTimeType clear_time_type_)
{
	if (clear_time_type_ < ClearTimeType::ClearTimeType_Max) {

		return m_clear_time[static_cast<int>(clear_time_type_)];

	}
	return 0;
}

bool SaveData::SetClearItemNum(int clear_item_num_)
{
	if (m_clear_item_num < clear_item_num_) {

		m_clear_item_num = clear_item_num_;

		return true;
	}

	return false;
}

bool SaveData::SetNewClearTime(ClearTimeType clear_time_type_, int clear_time_num_)
{

	int clear_time_type = static_cast<int>(clear_time_type_);

	if (clear_time_type_ < ClearTimeType::ClearTimeType_Max) {

		//�n�C�X�R�A�X�V
		if (m_clear_time[clear_time_type] < clear_time_num_) {

			m_clear_time[clear_time_type] = clear_time_num_;

			return true;
		}
	}

	return false;
}

bool SaveData::GetCsvFileData()
{
	//������
	FileLoadTool::w_vector<int*> file = FileLoad::GetFileDataInt(g_save_file_name);

	int clear_time_max = static_cast<int>(ClearTimeType::ClearTimeType_Max);

	//csv�t�@�C����2�i����K�v������
	if (file.size() >= 2) {
		if (static_cast<int>(file[1].size()) >= clear_time_max + 3) {//+3��csv�̎g�p���Ă��Ȃ������ƃf�[�^�����݂��邩����Ə̍��l�����̕�

			//�f�[�^���݂��邩
			m_is_data_exist = static_cast<bool>(*file[1][1]);

			//�̍��l����
			m_clear_item_num = *file[1][2];

			//�X�R�A�^�C��
			for (int i = 0;i < clear_time_max;++i) {

				m_clear_time[i] = *file[1][i + 3];

			}

			FileLoadTool::DeleteWVector(file);

			//�擾����
			return true;
		}
	}

	FileLoadTool::DeleteWVector(file);

	//�擾���s
	return false;
}

bool SaveData::SetCsvFileData()
{
	FileLoadTool::w_vector<int*> data = FileLoad::GetFileDataInt(g_save_file_name);

	int clear_time_max = static_cast<int>(ClearTimeType::ClearTimeType_Max);

	if (data.size() >= 2) {

		if (static_cast<int>(data[1].size()) >= clear_time_max + 3) {//+3��csv�̎g�p���Ă��Ȃ������ƃf�[�^�����݂��邩����Ə̍��l�����̕�
			
			//�f�[�^���݂��邩
			*data[1][1] = static_cast<int>(m_is_data_exist);

			//�̍��l����
			*data[1][2] = m_clear_item_num;

			//�X�R�A�^�C��
			for (int i = 0;i < clear_time_max;++i) {

				*data[1][i + 3] = m_clear_time[i];

			}

			//csv�ɓo�^
			FileLoad::FileWriting(g_save_file_name, data, true);

			FileLoadTool::DeleteWVector(data);

			return true;
		}
	}

	FileLoadTool::DeleteWVector(data);

	return false;
}
