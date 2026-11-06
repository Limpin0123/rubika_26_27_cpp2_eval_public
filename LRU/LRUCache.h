#pragma once

#include <string>
#include <unordered_map>

class LRUCache
{
public:

	// The maximum capacity of the cache
	LRUCache(int capacity);

	// Get the value store in the cache
	// If the key exists, return its associated value.
	// If the key does not exist, return an empty string.
	// Whenever a key is accessed, it becomes the most recently used element.
	std::string get(int key);

	// Insert a ne value in the cache
	// If the key already exists, update its value. Otherwise, insert the new key-value pair.
	// If the cache is full, remove the least recently used element.
	// Inserting or updating an element makes it the most recently used element.
	void put(int key, std::string value);
private:
	int maxCapacity;
	std::vector<int> sortedKeyByUpdateTime;
	std::unordered_map<int, int> fastAccess;
	std::unordered_map<int, std::string> cache;

	void updateElementLastUsage(int key);
	void removeOldestElement();
};