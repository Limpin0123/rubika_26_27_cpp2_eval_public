#include "LRUCache.h"
#include <algorithm>

#include "MemoryTrack.h"

LRUCache::LRUCache(int capacity)
{
	maxCapacity = capacity;
}

std::string LRUCache::get(int key)
{
	auto it = cache.find(key);

	if (it == cache.end()) return "";
	else
	{
		updateElementLastUsage(it->first);

		return it->second;
	}
}

void LRUCache::put(int key, std::string value)
{
	auto it = cache.find(key);
	if (it == cache.end())//value not in the cache
	{
		cache.emplace(key, value);
	}
	else
	{
		cache.at(key) = value;
	}
	updateElementLastUsage(key);
}

void LRUCache::updateElementLastUsage(int key)
{
	auto keyIt = fastAccess.find(key);
	if (keyIt == fastAccess.end())//element not in the list => inserting
	{
		if (cache.size() > maxCapacity)
		{
			removeOldestElement();
		}
		sortedKeyByUpdateTime.push_back(key);
		fastAccess.emplace(key, sortedKeyByUpdateTime.size() - 1);
	}
	else//element in the list => updating
	{
		//moving the element at the end of the list
		sortedKeyByUpdateTime.erase(sortedKeyByUpdateTime.begin() + keyIt->second);
		sortedKeyByUpdateTime.push_back(key);
		fastAccess.at(key) = sortedKeyByUpdateTime.size() - 1;
	}
}

void LRUCache::removeOldestElement()
{
	int removedKey = sortedKeyByUpdateTime.front();

	sortedKeyByUpdateTime.erase(sortedKeyByUpdateTime.begin());

	fastAccess.erase(removedKey);
	
	auto it = cache.find(removedKey);
	cache.erase(it);
}
