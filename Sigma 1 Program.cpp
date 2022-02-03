#include <iostream>
#include <conio.h>
#include "Class Functions.h"

																							//declaring global variables 
Limb Limb1, Limb2;																			//creating two objects from the "Limb" class
char ch1, ch2;																				//'ch1' is used for the option to input or read data, 'ch2' is used in the save data if statement
bool check, save_check;																		//'check' is used in the following do while loops to prevent people from inputing an invalid answer
																							//'save_check' is used to make sure users input a valid character while deciding to save
																							//ch1, ch2, check and save_check are used in setting the data for both limbs

void Get_Data_Limb1(void)																	//creating 2 get_data functions to be used in main this is the first (to be used on Limb1 object)
{
	cout << "Please set Limb 1 Data: " << endl;												//do while loop for object 'Limb1'
	do
	{
		cout << "Would you like to (a) input new data, or (b) read in from a file: " << endl;
		ch1 = _getch();
		ch1 = tolower(ch1);																	//corrects to lower case if user entered capitol letter

		if (ch1 == 'a')																		//if (a), input data
		{
			Limb1.Input_Data();
			
			do
			{
				cout << "Would you like to save this data? (y/n): " << endl;				//nested do while loop for saving the data
				ch2 = _getch();
				ch2 = tolower(ch2);

				if (ch2 == 'y')																//if (y), save data (using 'Write_Data' member function)
				{																			//and display the data (using 'Display_Data' member function)
					Limb1.Write_Data();
					Limb1.Display_Data();
					save_check = false;														//if set to false we exit the inner loop
				}
				else if (ch2 == 'n')
				{
					Limb1.Display_Data();													//if user doesnt want to save, display data anyway
					save_check = false;
				}
				else
				{
					save_check = true;														//if user doesnt enter a valid character, stay in the loop (save_check = true)
					cout << "User didnt enter (y/n) " << endl;				
				}
			} while (save_check == true);

			check = false;																	//exit outer loop and continue to limb 2

		}
		else if (ch1 == 'b')
		{
			Limb1.Read_Data();
			Limb1.Display_Data();
			check = false;																	//exit outer loop and continue to limb 2
		}
		else
		{
			cout << "Didnt enter 'a' or 'b'" << endl;
			check = true;																	//stay in outer loop as entered invalid char
		}
	} while (check == true);
}

void Get_Data_Limb2(void)
{
	cout << "Please set Limb 2 Data: " << endl;												//same do while loops and if statements as previous function however using 'Limb2' object
	do
	{
		cout << "Would you like to (a) input new data, or (b) read in from a file: " << endl;
		ch1 = _getch();
		ch1 = towlower(ch1);

		if (ch1 == 'a')
		{
			Limb2.Input_Data();

			do
			{
				cout << "Would you like to save this data? (y/n): " << endl;
				ch2 = _getch();
				ch2 = tolower(ch2);
				
				if (ch2 == 'y')																	
				{																				
					Limb2.Write_Data();
					Limb2.Display_Data();
					save_check = false;
				}
				else if (ch2 == 'n')
				{
					Limb2.Display_Data();							
					save_check = false;
				}
				else
				{
					save_check = true;															
					cout << "User didnt enter (y/n) " << endl;
				}
			} while (save_check == true);
			
			check = false;

		}
		else if (ch1 == 'b')
		{
			Limb2.Read_Data();
			Limb2.Display_Data();
			check = false;
		}
		else
		{
			cout << "Didnt enter 'a' or 'b'" << endl;
			check = true;
		}
	} while (check == true);
}

void Sigma_Calc(void)
{
	double* sigma1_trend, * sigma1_plunge;													//two pointers to be used in final sigma 1 calculation (local variables)

	sigma1_trend = new double;																//allocating memory to store double
	sigma1_plunge = new double;

	*sigma1_trend = ((Limb1.pole_trend + Limb2.pole_trend) / 2);							//calculation for sigma 1 trend and plunge
	*sigma1_plunge = ((Limb1.pole_plunge + Limb2.pole_plunge) / 2);

	if (*sigma1_plunge < 0)																	//if the dip of the sigma 1 is -ve, flip the trend and plunge
	{
		*sigma1_plunge = *sigma1_plunge * -1;

		if (*sigma1_trend > 180) *sigma1_trend = *sigma1_trend - 180;						//flipped sigma 1 will have oposite dip direction
		else if (*sigma1_trend < 180) *sigma1_trend = *sigma1_trend + 180;
	}

	cout << "Principal stress (Sigma 1) Trend/Plunge of this fold is: " << *sigma1_trend << "/" << *sigma1_plunge << endl << endl;

	delete sigma1_trend;																	//deallocating memory
	delete sigma1_plunge;
}



void main(void)
{
	Get_Data_Limb1();																		//using the 2 get data functions above
	Get_Data_Limb2();

	cout << "Limb 1 Calculations: " << endl;												//using Limb member functions to calculate average dip/dip direction
	Limb1.Calc_Average();																	//and then convert to a pole to the plane (trend/plunge)
	Limb1.Convert_To_Pole();	

	cout << "Limb 2 Calculations: " << endl;
	Limb2.Calc_Average();
	Limb2.Convert_To_Pole();
	Limb2.Flip_Pole();																		//need to flip one of the objects pole to planes for sigma 1 calculation to work

	Sigma_Calc();																			//finally calculating sigma 1
}
