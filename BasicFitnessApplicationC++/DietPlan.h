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
#include <string>
#include <fstream>

using std::string;
using std::fstream;
using std::ostream;
using std::cout;
using std::cin;
using std::endl;

#define MAX_LINE 40
#define MAX_DATE 20

class DietPlan
{
public:
	// Constructors-- default & copy
	DietPlan(string newName = "", int newGoalCals = 0, string newDate = "00/00/0000");
	DietPlan(const DietPlan &copy);

	// Setters
	void setGoalCals(int &newGoalCals);
	void setName(string &newName);
	void setDate(string &newDate);

	// Getters
	int getGoalCals() const;
	string getName() const;
	string getDate() const;

	// Destructor
	~DietPlan();

	// Member Functions
	DietPlan & operator = (const DietPlan &rhs);

	// Description: Displays user's current number of goal calories, then prompts user 
	//				to enter a new number of goal calories. Stores into object.
	void editGoal();

private:
	int mGoalCalories;		// maximum intake of calories for a day
	string mName;			// plan name
	string mDate;			// date for which plan is intended
};

// Nonmember Functions

// 1. Overload the Stream Insertion Operator <<
// Description: for writing plan to the file
//				lhs should be used as ofstream class
fstream & operator << (fstream &lhs, DietPlan &rhs);

// 2. Second Overload of the Stream Insertion Operator <<
// Description: for displaying to the screen
//				lhs should be of ostream class
ostream & operator << (ostream &lhs, DietPlan &rhs);

// 3. Overload the Stream Extraction Operator >>
// Description: for reading in from a file
fstream & operator >> (fstream &lhs, DietPlan &rhs);