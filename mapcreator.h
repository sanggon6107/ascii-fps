#pragma once
#include <vector>
#include <string>
using namespace std;

class MapCreator
{
public :
	void Export(wstring& out);

private:
	MapCreator(int w, int h);
	void InitMap();
	void CreateMaze();
	
	
	vector<wstring> map_;
	int w_;
	int h_;
};