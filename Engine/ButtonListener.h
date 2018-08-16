#pragma once
class ButtonListener
{
public:
	void SetType(int newType) { typeID = newType; }
	int GetType(){ return typeID;}
private:
	int typeID = 0;
};