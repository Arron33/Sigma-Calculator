#pragma once
#include <vector>

using namespace std;


class Limb														//declaring a class called "Limb"
{
public:															//only need using public variables and functions
	double dip_av, dip_d_av, pole_plunge, pole_trend;			//variables to store average dip/dip direction as well as trend/plunge of the pole to plane
	vector<double>dip, dip_d, loc_num;							//vectors to store loc number, dip/dip direction

	Limb()														//constructor to set all member variables to zero and clear all member vectors
	{
		dip_av = 0;
		dip_d_av = 0;
		pole_plunge = 0;
		pole_trend = 0;
		loc_num.clear();
		dip.clear();
		dip_d.clear();
	}

	void Input_Data(void);										//declaring various class member functions used in my program
	void Display_Data(void);									//see 'Class Functions.ccp'
	void Write_Data(void);
	void Read_Data(void);
	void Calc_Average(void);
	void Convert_To_Pole(void);
	void Flip_Pole(void);
};