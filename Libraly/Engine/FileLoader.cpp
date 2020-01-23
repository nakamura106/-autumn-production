#include"FileLoader.h"

/*
セーブ関係関数
ゲームのセーブのようなものを作りたい
*/

int AtoI(std::string str) {
	return atoi(str.c_str());
}

int RandomTool::GetRandom() {
	std::random_device rd;

	std::mt19937 mt(rd());

	int rand = mt();

	//一応、負の場合は正に変換
	if (rand < 0)rand = -rand;

	return rand;
}

//int型の数字をchar型に変換
char FileLoadTool::ItoC(int num) {

	std::string moji = std::to_string(num);

	return moji[0];
}


std::vector<std::vector<std::string*>> FileLoad::GetFileData(std::string file_name) {

	std::vector<std::vector<std::string*>> file_data;

	//ファイル読み込みデータ取得
	
	std::ifstream ifs(file_name);

	//オープン失敗
	if (ifs.fail())return file_data;

	std::string str;

	//改行するタイミングでfalse
	while (std::getline(ifs, str)) {
		file_data.push_back(std::vector<std::string*>());

		std::vector<std::string*> split_str = SplitComma(str);

		//分割した行を登録
		for (auto i : split_str) {
			file_data[file_data.size() - 1].push_back(new std::string(*i));
		}

		//std::vector解放
		FileLoadTool::ReleaseMemory(split_str);

	}
	
	return std::move(file_data);
}


FileLoadTool::w_vector<int*> FileLoad::GetFileDataInt(std::string file_name) {

	//ファイルデータを読み込む(文字列)
	FileLoadTool::w_vector<std::string*> f_data;
	
	f_data = GetFileData(file_name);

	//int型に変換するための二重配列
	FileLoadTool::w_vector<int*>f_int_data;

	//文字列→int型(整数)への変換処理
	for (int i = 0;i < f_data.size();++i) {

		f_int_data.push_back(std::vector<int*>());

		for (int j = 0;j < f_data[i].size();++j) {

			f_int_data[i].push_back(new int(AtoI(*f_data[i][j])));

		}
	}

	//w_vector解放
	FileLoadTool::DeleteWVector(f_data);

	return std::move(f_int_data);
}

//引数x_y_numはx軸・y軸のそれぞれに番号を追加するかどうかの判定
bool FileLoad::FileWriting(std::string write_file_name, FileLoadTool::w_vector<int*> write_data, bool x_y_num) {

	//ファイルに書き込んでセーブする機能
	std::ofstream ofs(write_file_name);

	if (!ofs)return false;//失敗

	//サイズが空の場合は失敗
	if (write_data.empty())return false;

	int file_start_tmp = 0;

	if (x_y_num) {
		//行番号のセット
		for (int i = 0;i < write_data[0].size();i++) {
			ofs << std::to_string(i) << ',';
		}
		ofs << std::endl;

		file_start_tmp = 1;

	}

	//i=1の意味は1列目が不要データであるから
	for (int i = file_start_tmp;i < write_data.size();i++) {

		if (x_y_num) {
			//1行目は番号に
			ofs << std::to_string(i) << ',';
		}

		//i=1の意味は1行目が不要データであるから
		for (int j = file_start_tmp;j < write_data[i].size();j++) {
			ofs << std::to_string(*write_data[i][j]) << ',';
		}
		ofs << std::endl;
	}

	return true;
}


std::vector<std::string*> FileLoad::SplitComma(std::string& input) {

	std::istringstream stream(input);
	std::string str;
	std::vector<std::string*> split_str;

	while (std::getline(stream, str, ',')) {
		split_str.push_back(new std::string(str));
	}

	return split_str;

}


