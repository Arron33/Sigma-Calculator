#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>
#include "Class Functions.h"


void Limb::Input_Data(void)												//implementing member function that reads in data from the user
{
	char ch = 'y';														//'ch' is used in 3rd inner nested do/while loop (option to add more data)
	bool test = true;													//'test' is used to exit main do while loop

	do
	{
		double temp_dip, temp_dip_d;									//setting two temp doubles to use in pushback
		bool check = true;												//'check' is used to exit inner nested do while loops

		cout << "Enter data for loc" << endl;

		do
		{
			cout << "Dip in degrees 0-90: ";							//user enters dip measurement
			cin >> temp_dip;											//stored in temp variable
			if (temp_dip >= 0 && temp_dip <= 90)						//checks if the dip entered by user is valid
			{
				dip.push_back(temp_dip);								//added to dip vector
				check = false;
			}
			else
			{
				cout << "Enter Valid Dip " << endl;
				check = true;											//if invalid dip, stay in the loop
			}
		} while (check == true);

		do
		{
			cout << "Dip Direction in degrees 0-359: ";					//same as previous do while loop but to set dip direction
			cin >> temp_dip_d;
			if (temp_dip_d >= 0 && temp_dip_d <= 359)
			{
				dip_d.push_back(temp_dip_d);							//added to dip_d vector
				check = false;
			}
			else
			{
				cout << "Enter Valid Dip Direction " << endl;
				check = true;
			}
		} while (check == true);

		do
		{
			cout << "Do you want to add another Loc? (y/n)" << endl;	//final nested do while loop, used to allow user to input as much data as needed
			ch = _getch();
			ch = tolower(ch);											//allows user to input (Y/N) as well as (y/n)

			if (ch == 'y')
			{
				test = true;											//if (y) we leave final inner loop but stay in the main outer loop to add more data
				check = false;										
			}
			else if (ch == 'n')
			{
				test = false;											//if (n) we leave both inner and outer do while loops and exit function
				check = false;			
			}
			else
			{
				check = true;											//restarts the loop with an error message
				cout << "User didnt enter (y/n) " << endl;
			}
		} while (check == true);

	} while (test);
}

void Limb::Display_Data(void)											//implementing member function to display data	
{
	cout << endl << "Number of locs: " << dip.size() << endl;		

	for (int i = 0; i < dip.size(); i++)								//loop through vectors and display each row until end of dip vector
	{
		cout << "Loc " << i + 1 << ": ";								//as locs can only be given in assending order, (i + 1) is the same as loc_num
		cout << dip[i] << "/";
		cout << dip_d[i] << endl;
	}
	cout << "\n";
}

void Limb::Write_Data(void)												//implementing member function to write data to a .txt file
{
	fstream f_out;														//declaring stream name
	string file_name;													//declaring a string to use as a file name

	cin.ignore(INT_MAX, '\n');											//removes enter from buffer for getline to work
	cout << "Save as file name, eg. 'LimbX.txt': ";	
	getline(cin, file_name);											

	f_out.open(file_name, fstream::out | fstream::app);					//creates file with a name the user has chosen

	if (f_out.fail())													//check to see if file opening worked
	{
		cout << "Can't open file to write to " << endl;
		exit(0);
	}

	for (int i = 0; i < dip.size(); i++)								//loop through vectors writing to file until the end of dip vector
	{
		f_out << i + 1 << "\t";											//tab and line spacing to allow easy read in of .txt file
		f_out << dip[i] << "\t";
		f_out << dip_d[i] << endl;
	}

	f_out.close();
}

void Limb::Read_Data(void)												//implementing member function to read data from a .txt file
{
	fstream f_in;														//declaring stream name
	string file_name;													//declaring a string to allow user to read in a file of their choosing

	cout << "Open file name, eg. (LimbX.txt): ";
	getline(cin, file_name);

	f_in.open(file_name, fstream::in);									//opens file with name user has chosen

	if (f_in.fail())													//check to see if opening file worked
	{
		cout << "Error opening file" << endl;
		return;
	}

	loc_num.clear();													//clearing previous vector data, as about to add read in data
	dip.clear();
	dip_d.clear();

	while (!f_in.eof())													//while loop to add read in data to vectors
	{
		double temp_loc_num, temp_dip, temp_dip_d;						//using temp variables for pushback

		for (int i = 0; f_in >> temp_loc_num; i++)
		{
			loc_num.push_back(temp_loc_num);							//pushback adds data from file to vectors
			f_in >> temp_dip;
			dip.push_back(temp_dip);
			f_in >> temp_dip_d;
			dip_d.push_back(temp_dip_d);
		}
	}
	f_in.close();
}

void Limb::Calc_Average(void)											//implementing member function to calculate the average dip/dip direction of an object
{
	double dip_sum = 0.0, dip_d_sum = 0.0;								//setting initial values to 0.0

	for (int i = 0; i < dip.size(); i++)								//for loop to calculate the sum of all dip measurments (couldnt get accumulate from <numeric> to work)
	{
		dip_sum = dip_sum + dip[i];
	}
	for (int i = 0; i < dip.size(); i++)								//same as previous for loop but for dip direction measurements
	{
		dip_d_sum = dip_d_sum + dip_d[i];
	}

	dip_av = (dip_sum / dip.size());									//calculating the average dip/dip direction of data provided
	dip_d_av = (dip_d_sum / dip.size());

	cout << "Average dip/dip direction for limb is: " << dip_av << "/" << dip_d_av << endl;
}

void Limb::Convert_To_Pole(void)										//implementing member function to convert the average dip/dip direction into a pole to the plane
{
	pole_plunge = 90 - dip_av;											//plunge of pole is 90 - dip of plane

	if (dip_d_av > 180) pole_trend = dip_d_av - 180;					//trend of pole is dip direction +/- 180 (dont want a trend of over 360)
	else if (dip_d_av < 180) pole_trend = dip_d_av + 180;

	cout << "Trend and plunge of the pole to this limb is :" << pole_trend << "/" << pole_plunge << endl << endl;
}

void Limb::Flip_Pole(void)												//implementing member function to flip the pole of a limb object
{																		//needed for final sigma 1 calculation in 'Sigma_Calc' function
	pole_plunge = pole_plunge * -1;										//flipped pole will have -ve dip

	if (pole_trend > 180) pole_trend = pole_trend - 180;				//flipped pole will have oposite dip direction
	else if (pole_trend < 180) pole_trend = pole_trend + 180;
}																		//this class member function must be ran on one of the limb objects before the sigma 1 calculation
