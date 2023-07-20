#pragma once

template<typename T = int>
struct LeagueObfuscation
{
	bool isInit;
	unsigned char xorCount64;
	unsigned char xorCount8;
	T xorKey;
	unsigned char valueIndex;
	T valueTable[4];
};

template<typename T = int>
inline T Decrypt(const LeagueObfuscation<T>& data)
{
	if (!data.isInit)
		throw std::exception("");

	if (data.xorCount8 != 0)
		if (data.xorCount8 > sizeof(T) || data.xorCount8 < 0)
			throw std::exception("");

	if (data.xorCount64 != 0)
		if (data.xorCount64 > sizeof(T) || data.xorCount64 < 0)
			throw std::exception("");

	if (data.valueIndex > 4)
		throw std::exception("");

	int xorCount64 = data.xorCount64 >= 1 ? 1 : 0;

	auto tXoredValue = data.valueTable[data.valueIndex];
	auto tXorKeyValue = data.xorKey;
	{
		auto tXorValuePtr = reinterpret_cast<DWORD64*>(&tXorKeyValue);
		for (auto i = 0; i < xorCount64; i++)
			*(reinterpret_cast<DWORD64*>(&tXoredValue) + i) ^= ~tXorValuePtr[i];
	}
	{
		auto tXorValuePtr = reinterpret_cast<unsigned char*>(&tXorKeyValue);
		for (auto i = sizeof(T) - data.xorCount8; i < sizeof(T); ++i)
			*(reinterpret_cast<unsigned char*>(&tXoredValue) + i) ^= ~tXorValuePtr[i];
	}
	return tXoredValue;
}