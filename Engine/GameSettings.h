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
		AddData(filename);
	}
	GameSettings()
	{
		AddData(L"Data\\setting.ini");
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
	std::string GetMapData(const std::string& dataName)
	{
		auto it = mapData.find(dataName);
		if (it != mapData.end())
		{
			return it->second;
		}
		else
		{
			return "";
		}
	}
	static GameSettings& Get()
	{
		static GameSettings gameSetting;
		return gameSetting;
	}
	void AddMapData(const std::wstring& filename)
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
			else if (line[0] == '*')
			{
				std::string data;
				std::string c;
				while (file >> c)
				{
					data += c;
				}
				mapData.emplace(std::move(line), std::move(data));
			}
		}
	}
private:
	void AddData(const std::wstring& filename)
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
private:
	std::unordered_map<std::string, float> settingData;
	std::unordered_map<std::string, std::string> mapData;
};