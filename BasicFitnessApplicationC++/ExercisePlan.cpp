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

#include "ExercisePlan.h"

ExercisePlan::ExercisePlan(string newName, int newGoalsteps, string newDate)
{
	mGoalSteps = newGoalsteps;
	mName = newName;   // assumes string assignment operator is overloaded (I think it is)
	mDate = newDate;
}

ExercisePlan::ExercisePlan(const ExercisePlan &copy)
{
	(*this) = copy;  // I overloaded the assignment operator, so this works
}

void ExercisePlan::setGoalSteps(int &newGoalSteps)
{
	mGoalSteps = newGoalSteps;
}

void ExercisePlan::setName(string &newName)
{
	mName = newName;
}
 
void ExercisePlan::setDate(string &newDate)
{
	mDate = newDate;
}

int ExercisePlan::getGoalSteps() const
{
	return mGoalSteps;
}
string ExercisePlan::getName() const
{
	return mName;
}
string ExercisePlan::getDate() const
{
	return mDate;
}

ExercisePlan::~ExercisePlan()
{
	// empty destructor
}

ExercisePlan & ExercisePlan::operator = (const ExercisePlan &rhs)
{
	int goal = rhs.getGoalSteps();   // initial value of reference must be an L-value

	(*this).setGoalSteps(goal);
	(*this).setName(rhs.getName());
	(*this).setDate(rhs.getDate());

	return (*this);  // return the object which I am performing assignment on
}

void ExercisePlan::editGoal()
{
	int newGoal;
	cout << "Current Goal Steps: " << mGoalSteps << endl;
	cout << "Please enter new number of goal steps: ";
	cin >> newGoal;
	(*this).setGoalSteps(newGoal);
}

fstream & operator << (fstream &lhs, ExercisePlan &rhs)
{
	lhs << rhs.getName() << endl;
	lhs << rhs.getGoalSteps() << endl;
	lhs << rhs.getDate() << endl;

	return lhs;
}

ostream & operator << (ostream &lhs, ExercisePlan &rhs)
{
	lhs << "Goal Steps: " << rhs.getGoalSteps() << endl;
	lhs << "Plan Name: " << rhs.getName() << endl;
	lhs << "Date: " << rhs.getDate() << endl;

	return lhs;
}

fstream & operator >> (fstream &lhs, ExercisePlan &rhs)
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
	rhs.setGoalSteps(goal);
	rhs.setDate(sDate);

	return lhs;

	return lhs;
}