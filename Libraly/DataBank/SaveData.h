#pragma once
#include"../Object/Definition.h"
#include<string>

const std::string g_save_file_name = "Res/Csv/SaveData/SaveData1.csv";

class SaveData {
public:
	SaveData();
	~SaveData();

	/*インスタンスゲッター*/
	static SaveData& GetInstance() {
		static SaveData save_data;
		return save_data;
	}

	/*ゲッター群*/
	bool GetIsDataExist() { return m_is_data_exist; }
	int GetClearItemNum() { return m_clear_item_num; }
	int GetClearTime(ClearTimeType clear_time_type_);

	/*称号獲得数更新関数*/
	bool SetClearItemNum(int clear_item_num_);

	/*ハイスコア更新設定関数*/
	bool SetNewClearTime(ClearTimeType clear_time_type_, int clear_time_num_);

	/*csvファイルからデータを入手*/
	bool GetCsvFileData();

	/*csvファイルにデータを書き込み*/
	bool SetCsvFileData();

private:
	bool m_is_data_exist;	//データが存在するか
	int m_clear_item_num;	//称号獲得数
	int m_clear_time[static_cast<int>(ClearTimeType::ClearTimeType_Max)];//クリアタイム

};

