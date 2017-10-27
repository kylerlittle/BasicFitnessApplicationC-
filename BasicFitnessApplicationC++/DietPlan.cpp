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

#include "DietPlan.h"

DietPlan::DietPlan(string newName, int newGoalCals, string newDate)
{
	mGoalCalories = newGoalCals;
	mName = newName;
	mDate = newDate;
}

// Precondition: assignment operator is overloaded
DietPlan::DietPlan(const DietPlan &copy)
{
	(*this) = copy;
}

void DietPlan::setGoalCals(int &newGoalCals)
{
	mGoalCalories = newGoalCals;
}

void DietPlan::setName(string &newName)
{
	mName = newName;
}

void DietPlan::setDate(string &newDate)
{
	mDate = newDate;
}

int DietPlan::getGoalCals() const
{
	return (*this).mGoalCalories;
}

string DietPlan::getName() const
{
	return (*this).mName;
}

string DietPlan::getDate() const
{
	return (*this).mDate;
}

DietPlan::~DietPlan()
{

}

DietPlan & DietPlan::operator = (const DietPlan &rhs)
{
	int goal = rhs.getGoalCals();  // initial value of reference must be an L-value
	
	(*this).setGoalCals(goal);
	(*this).setDate(rhs.getDate());
	(*this).setName(rhs.getName());

	return (*this);
}

void DietPlan::editGoal()
{
	int newGoal;
	cout << "Current Goal Calories: " << mGoalCalories << endl;
	cout << "Please enter new number of goal calories: ";
	cin >> newGoal;
	(*this).setGoalCals(newGoal);
}

fstream & operator << (fstream &lhs, DietPlan &rhs)
{
	lhs << rhs.getName() << endl;
	lhs << rhs.getGoalCals() << endl;
	lhs << rhs.getDate() << endl;

	return lhs;
}

ostream & operator << (ostream &lhs, DietPlan &rhs)
{
	lhs << "Goal Calories: " << rhs.getGoalCals() << endl;
	lhs << "Plan Name: " << rhs.getName() << endl;
	lhs << "Date: " << rhs.getDate() << endl;

	return lhs;
}

fstream & operator >> (fstream &lhs, DietPlan &rhs)
{
	string sPlan, sDate;
	char plan[MAX_LINE], date[MAX_DATE], newLine = '\n';
	int goal;

	lhs.getline(plan, MAX_LINE);    // getline only accepts a char *
	lhs >> goal;
	lhs.get(newLine);  // extract the new line character	
	lhs.getline(date, MAX_DATE);
	
	sPlan = plan;   // convert character arrays to string
	sDate = date;

	rhs.setName(sPlan);		// store strings into object
	rhs.setGoalCals(goal);
	rhs.setDate(sDate);

	return lhs;
}