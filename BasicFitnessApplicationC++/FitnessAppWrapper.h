/*******************************************************************************
* Programmer: Kyler Little													  *
* Class: CptS 122; Lab Section 6                                              *
* Programming Assignment: Basic Fitness Application (PA #5)                   *
* Date: 03/04/2017                                                            *
*                                                                             *
* Description: This program is a basic fitness application, that allows the   *
*			   user to manually edit "diet" and "exercise" plans. The		  *
*			   program will also read in each plan from a file & save the	  *
*			   current plan upon exiting. Lastly, the user can display his/	  *
*			   her weekly diet/exercise plans.								  *
*                                                                             *
* Relevant Formulas: Refer to each function definition.                       *
*                                                                             *
* Format of record in stream:		 Workout Day		(planName string)	  *
*                                    2000				(Goal Cals/Steps int) *
*									 01/01/2017			(date string)		  *
*                                                                             *
* Format of output data:			 Same as input. However, a new line is    *
*									 appended to the end of the file, causing *
*									 issues if the new line is not erased     *
*									 manually.								  *
******************************************************************************/

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "DietPlan.h"
#include "ExercisePlan.h"

#define DAYS_PER_WEEK 7

using std::string;
using std::vector;
using std::endl;
using std::cout;
using std::cin;
using std::fstream;

typedef enum userChoice
{
	LOAD_W_DIET = 1, LOAD_W_EXER, STORE_W_DIET, STORE_W_EXER, DISPLAY_W_DIET, DISPLAY_W_EXER,
	EDIT_D_DIET, EDIT_D_EXER, EXIT
} UserChoice;

class FitnessAppWrapper
{
public:
	// Member Functions:
	// Description: this function runs this program's operations when a given
	//				object calls it.
	void runApp();

	// Precondition: file is already open
	// Description: This function reads one record from the given stream and stores
	//				it into a DietPlan object
	void loadDailyPlan(fstream &fileStream, DietPlan &plan);

	// Precondition: file is already open
	// Description: This function reads one record from the given stream and stores
	//				it into an ExercisePlan object
	void loadDailyPlan(fstream &fileStream, ExercisePlan &plan);

	// Description: This function reads in all seven daily plans from the given stream. It 
	//				uses loadDailyPlan() as a helper function. If there are less than seven
	//				then the loop will exit. Each DietPlan is stored as an entry in 
	//				the vector 'weeklyPlan.'
	// Precondition: file is already open
	void loadWeeklyPlan(fstream &fileStream, vector<DietPlan> &weeklyPlan);

	// Description: This function reads in all seven daily plans from the given stream. It 
	//				uses loadDailyPlan() as a helper function. If there are less than seven
	//				then the loop will exit. Each ExercisePlan is stored as an entry in 
	//				the vector 'weeklyPlan.'
	// Precondition: file is already open
	void loadWeeklyPlan(fstream &fileStream, vector<ExercisePlan> &weeklyPlan);

	// Description: prints the contents of "weeklyPlan" to screen; if vector is empty,
	//				then nothing will be printed.
	void displayWeeklyPlan(vector<DietPlan> &weeklyPlan) const;

	// Description: prints the contents of "weeklyPlan" to screen; if vector is empty,
	//				then nothing will be printed.
	void displayWeeklyPlan(vector<ExercisePlan> &weeklyPlan) const;

	// Description: this writes the contents of the DietPlan object to the output
	//				stream. This uses my overloaded stream insertion operator.
	// Precondition: file must be open
	void storeDailyPlan(fstream &output, DietPlan &plan);

	// Description: this writes the contents of the ExercisePlan object to the output
	//				stream. This uses my overloaded stream insertion operator.
	// Precondition: file must be open
	void storeDailyPlan(fstream &output, ExercisePlan &plan);

	// Description: using storeDailyPlan() as a helper function, this function iterates
	//				through the weeklyPlan vector & inserts that vector's entry (a 
	//				DietPlan object) into the output stream. Note: this function
	//				uses an iterator object (adding an extra level of indirection).
	// NOTE: this function does add a newline to the end of the file, which ultimately
	//		 causes the "Load" function to create a new object solely containing
	//		 the new line... there is really no way around this that I know of. However, 
	//		 it doesn't affect things in a neagtive way...
	// Precondition: file must be open
	void storeWeeklyPlan(fstream &output, vector<DietPlan> &weeklyPlan);

	// Description: using storeDailyPlan() as a helper function, this function iterates
	//				through the weeklyPlan vector & inserts that vector's entry (an 
	//				ExercisePlan object) into the output stream. Note: this function
	//				uses an iterator object (adding an extra level of indirection).
	// NOTE: this function does add a newline to the end of the file, which ultimately
	//		 causes the "Load" function to create a new object solely containing
	//		 the new line... there is really no way around this that I know of. However, 
	//		 it doesn't affect things in a neagtive way...
	// Precondition: file must be open
	void storeWeeklyPlan(fstream &output, vector<ExercisePlan> &weeklyPlan);

	// Description: this function calls displayWeeklyPlan() to display the current
	//				plan to the user. It will prompt the user to enter a plan to edit
	//				(numerical value between 1 and size of vector) until it is within
	//				the valid range. It indirectly returns this value via an output 
	//				parameter.
	void getEditChoice(int *pChoice, vector<DietPlan> &weeklyPlan);

	// Description: this function calls displayWeeklyPlan() to display the current
	//				plan to the user. It will prompt the user to enter a plan to edit
	//				(numerical value between 1 and size of vector) until it is within
	//				the valid range. It indirectly returns this value via an output 
	//				parameter.
	void getEditChoice(int *pChoice, vector<ExercisePlan> &weeklyPlan);

	// Description: This function clears the screen and invokes the DietPlan object's
	//				edit function. Since the object has direct access to the private 
	//				data members via this function, no pointers are needed. The function
	//				then displays a summary of the edits made.
	// Precondition: vector weeklyPlan is populated
	void editDailyPlan(int choice, vector<DietPlan> &weeklyPlan);

	// Description: This function clears the screen and invokes the ExercisePlan object's
	//				edit function. Since the object has direct access to the private 
	//				data members via this function, no pointers are needed. The function
	//				then displays a summary of the edits made.
	// Precondition: vector weeklyPlan is populated
	void editDailyPlan(int choice, vector<ExercisePlan> &weeklyPlan);

	// Description: displays menu of 9 choices to user
	void displayMenu();

	// Description: gets the user's choice (an integral value between 1 & 9)
	//				If user's choice is invalid (i.e. outside of range), the
	//				program will continue to prompt the user.
	void getUserChoice(UserChoice *pChoice);
	
private:
	vector<DietPlan> weeklyDietPlan;
	vector <ExercisePlan> weeklyExercisePlan;
};