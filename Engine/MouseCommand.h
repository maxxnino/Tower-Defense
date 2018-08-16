#pragma once
class MouseCommand
{
public:
	void SetType(int newType) { typeID = newType; }
	int GetType()
	{
		int temp = typeID;
		typeID = 0;
		return temp;
	}
private:
	int typeID = 0;
};