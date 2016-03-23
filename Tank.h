#pragma once
class Tank
{
public:
	Tank();
	Tank(double setX, double setY, double setZ);
	~Tank();

	void draw() const;

private:
	double x,y,z;

	double angle;
	//temp
	double a;
};
