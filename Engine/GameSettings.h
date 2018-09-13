#pragma once
#include <fstream>
#include <unordered_map>
#include <string>
#include <assert.h>
class GameSettings
{
public:
	GameSettings(const std::wstring& filename)
	{
		std::fstream file(filename);
		assert(file);
		for (std::string line; std::getline(file, line); )
		{
			if (line[0] == '[')
			{
				float data;
				file >> data;
				settingData.emplace(std::move(line), data);
			}
		}
	}
	GameSettings()
	{
		std::fstream file(L"Data\\setting.ini");
		assert(file);
		for (std::string line; std::getline(file, line); )
		{
			if (line[0] == '[')
			{
				float data;
				file >> data;
				settingData.emplace(std::move(line), data);
			}
		}
	}
	float GetData(const std::string& dataName)
	{
		auto it = settingData.find(dataName);
		if (it != settingData.end())
		{
			return it->second;
		}
		else
		{
			return 10;
		}
	}
	static GameSettings& Get()
	{
		static GameSettings gameSetting;
		return gameSetting;
	}
private:
	std::unordered_map<std::string, float> settingData;
};