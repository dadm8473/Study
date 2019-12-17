#include "DXUT.h"
#include "Header.h"
#include <fstream>
#include <algorithm>

ScoreManager* gScoreManager;

void ScoreManager::Save()
{
	Sort();

	FILE* fp = fopen("./ScoreData.dat", "wb");

	ScoreInfo wirteData[3];

	for (int i = 0; i < 3; ++i)
		wirteData[i] = scoreData[i];

	fwrite(wirteData, sizeof(ScoreInfo), 3, fp);

	fclose(fp);
}

void ScoreManager::Load()
{
	FILE* fp = fopen("./ScoreData.dat", "rb");

	scoreData.clear();

	if (!fp)
		for (int i = 0; i < 3; ++i)
			scoreData.push_back(ScoreInfo());
	else
	{
		ScoreInfo readData[3];

		fread(readData, sizeof(ScoreInfo), 3, fp);

		for (int i = 0; i < 3; ++i)
			scoreData.push_back(readData[i]);

		fclose(fp);
	}
}

bool SortScore(const ScoreInfo& a, const ScoreInfo& b)
{
	return a.score > b.score;
}

void ScoreManager::Sort()
{
	if (scoreData.size() > 0)
		std::sort(scoreData.begin(), scoreData.end(), SortScore);
}
