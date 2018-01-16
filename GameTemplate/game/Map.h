#pragma once

class MapChip;

class Map
{
public:
	Map();
	~Map();
	void Init();
	void Update();
	void Draw();
private:
	std::vector<MapChip*> mapChipList;   //マップチップのリスト
};

