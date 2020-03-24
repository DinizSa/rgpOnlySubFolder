#pragma once
#include<string>
using namespace std;


class cItem {
public:
	cItem(string name, string asset, string desc, int usageRemaining = 1);
	inline string getName() { return sName; };
	inline string getAsset() { return sAsset; };
	inline string getDescription() { return sDesc; };

private:
	string sName;
	string sAsset;
	string sDesc;
	int iUsesRemainning;
};