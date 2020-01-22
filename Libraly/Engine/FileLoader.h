#pragma once
#include<vector>
#include<unordered_map>
#include<string>
#include<fstream>
#include<sstream>
#include<random>

/*
データ保存クラス
内容はまだ未定
*/

//文字から数値への変換
int AtoI(std::string str);

namespace RandomTool {
	int GetRandom();
}

namespace FileLoadTool {
	//vector二重配列
	template<typename T>
	using w_vector	=	std::vector<std::vector<T>>;

	//std::vector<ポインタ型>解放
	template <typename T>
	void ReleaseMemory(std::vector<T*>& delete_vector) {
		for (int i = 0;i < delete_vector.size();i++) {
			if (delete_vector[i])delete delete_vector[i];
		}
		std::vector<T*>().swap(delete_vector);
	}

	//w_vector解放
	template<typename T>
	void DeleteWVector(w_vector<T*>& vec) {
		
		for (int i = 0;i < static_cast<int>(vec.size());i++) {
			ReleaseMemory(vec[i]);
		}
		w_vector<T*>().swap(vec);
	}


	char ItoC(int num);
}

namespace FileLoad {

	//CSVファイルの情報をstring型で入手
	std::vector<std::vector<std::string*>> GetFileData(std::string file_name);

	//CSVファイルの情報をint型で入手
	FileLoadTool::w_vector<int*> GetFileDataInt(std::string file_name);

	//CSVファイルに情報を書き込み
	bool FileWriting(std::string write_file_name, FileLoadTool::w_vector<int*> write_data, bool x_y_num = true);

	std::vector<std::string*> SplitComma(std::string& input);

}


