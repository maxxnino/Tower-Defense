#pragma once
#include <unordered_map>
#include <memory>
#include <string>
#include "resource.h"

// we will make this a singleton (there can be only one!)
template<class T>
class Codex
{
public:
	// retrieve a ptr to resource based on string (load if not exist)
	static const std::shared_ptr<T> Retrieve( const std::wstring& key )
	{
		return Get()._Retrieve( key );
	}
	// remove all entries from codex
	static void Purge()
	{
		Get()._Purge();
	}
private:
	// retrieve a ptr to resource based on string (load if not exist)
	const std::shared_ptr<T> _Retrieve( const std::wstring& key )
	{
		const auto it = entries.find(key);
		if (it == entries.end())
		{
			const auto resource = std::make_shared<T>(key);
			entries.emplace(key, resource);
			return resource;
		}
		else
		{
			return it->second;
		}
	}
	// remove all entries from codex
	void _Purge()
	{
		entries.clear();
	}
	// gets the singleton instance (creates if doesn't already exist)
	static Codex& Get()
	{
		static Codex codex;
		return codex;
	}
private:
	std::unordered_map<std::wstring,std::shared_ptr<T>> entries;
};