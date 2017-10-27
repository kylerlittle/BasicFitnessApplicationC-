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

#include "FitnessAppWrapper.h"

void FitnessAppWrapper::runApp()
{
	UserChoice choice = LOAD_W_DIET;   // initializing to a random value that's not EXIT
	int editChoice = 0;
	fstream diet, exercise;

	// Make sure to open and close files accordingly

	while (choice != EXIT)
	{
		displayMenu();
		getUserChoice(&choice);
		switch (choice)
		{
		case LOAD_W_DIET:
			diet.open("dietPlans.txt");
			if (diet.is_open())
			{
				loadWeeklyPlan(diet, weeklyDietPlan);
			}
			diet.close();
			break;
		case LOAD_W_EXER:
			exercise.open("exercisePlans.txt");
			if (exercise.is_open())
			{
				loadWeeklyPlan(exercise, weeklyExercisePlan);
			}
			exercise.close();
			break;
		case STORE_W_DIET:
			diet.open("dietPlans.txt");
			if (diet.is_open())
			{
				storeWeeklyPlan(diet, weeklyDietPlan);
			}
			diet.close();
			break;
		case STORE_W_EXER:
			exercise.open("exercisePlans.txt");
			if (exercise.is_open())
			{
				storeWeeklyPlan(exercise, weeklyExercisePlan);
			}
			exercise.close();
			break;
		case DISPLAY_W_DIET:
			displayWeeklyPlan(weeklyDietPlan);
			break;
		case DISPLAY_W_EXER:
			displayWeeklyPlan(weeklyExercisePlan);
			break;
		case EDIT_D_DIET:
			getEditChoice(&editChoice, weeklyDietPlan);
			editDailyPlan(editChoice, weeklyDietPlan);
			break;
		case EDIT_D_EXER:
			getEditChoice(&editChoice, weeklyExercisePlan);
			editDailyPlan(editChoice, weeklyExercisePlan);
			break;
		case EXIT:    // if files have yet to be loaded, load, then store; else, just store
			if (weeklyDietPlan.empty())  // LIKELY haven't loaded files yet...
			{		// it is possible that the files were empty
				diet.open("dietPlans.txt");
				if (diet.is_open())
				{
					loadWeeklyPlan(diet, weeklyDietPlan);
				}
				diet.close();
			}
			if (weeklyExercisePlan.empty())  // LIKELY haven't loaded files yet...
			{		// it is possible that the files were empty
				exercise.open("exercisePlans.txt");
				if (exercise.is_open())
				{
					loadWeeklyPlan(exercise, weeklyExercisePlan);
				}
				exercise.close();
			}
			// otherwise, simply store the current files
			diet.open("dietPlans.txt");
			exercise.open("exercisePlans.txt");
			storeWeeklyPlan(diet, weeklyDietPlan);
			storeWeeklyPlan(exercise, weeklyExercisePlan);
			diet.close();
			exercise.close();
			break;
		}
		system("pause");
		system("cls");
	}
}

void FitnessAppWrapper::loadDailyPlan(fstream &fileStream, DietPlan &plan)
{
	fileStream >> plan;
}

void FitnessAppWrapper::loadDailyPlan(fstream &fileStream, ExercisePlan &plan)
{
	fileStream >> plan;
}

void FitnessAppWrapper::loadWeeklyPlan(fstream &fileStream, vector<DietPlan> &weeklyPlan)
{
	DietPlan filler;

	while (!fileStream.eof() && weeklyPlan.size() <= DAYS_PER_WEEK)
	{
		weeklyPlan.push_back(filler);   // allocate space for a day plan at end of vector
		loadDailyPlan(fileStream, weeklyPlan.back());   // load the values into that object
	}
}

void FitnessAppWrapper::loadWeeklyPlan(fstream &fileStream, vector<ExercisePlan> &weeklyPlan)
{
	ExercisePlan filler;

	while (!fileStream.eof() && weeklyPlan.size() <= DAYS_PER_WEEK)
	{
		weeklyPlan.push_back(filler);   // allocate space for a day plan at end of vector
		loadDailyPlan(fileStream, weeklyPlan.back());   // load the values into that object
	}
}

void FitnessAppWrapper::displayWeeklyPlan(vector<DietPlan> &weeklyPlan) const
{
	int day = 1;
	// an iterator is a general object which has the ability to iterate thru elements
	// of a data structure... for a list, this would be a pointer
	// for a vector, elements are stored contiguously, so the iterator i (below) is
	// essentially an index, except with an extra level of indirection
	// using the "begin" and "end" attributes avoids 'off-by-one' errors
	for (vector<DietPlan>::iterator i = weeklyPlan.begin(); i != weeklyPlan.end(); ++i)
	{
		cout << "Diet Plan Day #" << day << endl << *i << endl;
		++day;
	}
}

void FitnessAppWrapper::displayWeeklyPlan(vector<ExercisePlan> &weeklyPlan) const
{
	int day = 1;
	for (vector<ExercisePlan>::iterator i = weeklyPlan.begin(); i != weeklyPlan.end(); ++i)
	{
		cout << "Exercise Plan Day #" << day << endl << *i << endl;
		++day;
	}
}

void FitnessAppWrapper::storeDailyPlan(fstream &output, DietPlan &plan)
{
	output << plan;
}

void FitnessAppWrapper::storeDailyPlan(fstream &output, ExercisePlan &plan)
{
	output << plan;
}

void FitnessAppWrapper::storeWeeklyPlan(fstream &output, vector<DietPlan> &weeklyPlan)
{
	for (vector<DietPlan>::iterator i = weeklyPlan.begin(); i != weeklyPlan.end(); ++i)
	{
		storeDailyPlan(output, *i);
	}
}

void FitnessAppWrapper::storeWeeklyPlan(fstream &output, vector<ExercisePlan> &weeklyPlan)
{
	for (vector<ExercisePlan>::iterator i = weeklyPlan.begin(); i != weeklyPlan.end(); ++i)
	{
		storeDailyPlan(output, *i);
	}
}

void FitnessAppWrapper::getEditChoice(int *pChoice, vector<DietPlan> &weeklyPlan)
{
	system("cls");    // clear screen
	displayWeeklyPlan(weeklyPlan);   // display to the user his/her plans to edit

	int choice = 0;

	cout << "Which day would you like to edit? <1-" << weeklyPlan.size() << ">  ";
	do
	{
		cin >> choice;   // get the user's choice while it is outside of a valid range
	} while (choice < 1 || choice > weeklyPlan.size());

	*pChoice = choice;    // indirectly return his/her choice
}

void FitnessAppWrapper::getEditChoice(int *pChoice, vector<ExercisePlan> &weeklyPlan)
{
	system("cls");    // clear screen
	displayWeeklyPlan(weeklyPlan);   // display to the user his/her plans to edit

	int choice = 0;

	cout << "Which day would you like to edit? <1-" << weeklyPlan.size() << ">  ";
	do
	{
		cin >> choice;   // get the user's choice while it is outside of a valid range
	} while (choice < 1 || choice > weeklyPlan.size());

	*pChoice = choice;    // indirectly return his/her choice
}

void FitnessAppWrapper::editDailyPlan(int choice, vector<DietPlan> &weeklyPlan)
{
	system("cls");	// clear screen for user-friendly interface
	weeklyPlan[choice - 1].editGoal();  // invoke member editGoal Function... -1 since index starts at 0
	system("pause");  // give the user a brief pause
	cout << "Summary of Edits Made:" << endl;
	cout << weeklyPlan[choice - 1];   // now display the edits
}

void FitnessAppWrapper::editDailyPlan(int choice, vector<ExercisePlan> &weeklyPlan)
{
	system("cls");	// clear screen for user-friendly interface
	weeklyPlan[choice - 1].editGoal();  // invoke member editGoal Function... -1 since index starts at 0
	system("pause");  // give the user a brief pause
	cout << "Summary of Edits Made:" << endl;
	cout << weeklyPlan[choice - 1];   // now display the edits
}

void FitnessAppWrapper::displayMenu()
{
	cout << "\t1. Load weekly diet plan from file." << endl;
	cout << "\t2. Load weekly exercise plan from file." << endl;
	cout << "\t3. Store weekly diet plan to file." << endl;
	cout << "\t4. Store weekly exercise plan to file." << endl;
	cout << "\t5. Display weekly diet plan to screen." << endl;
	cout << "\t6. Display weekly exercise plan to screen." << endl;
	cout << "\t7. Edit daily diet plan." << endl;
	cout << "\t8. Edit daily exercise plan." << endl;
	cout << "\t9. Exit." << endl;
}

void FitnessAppWrapper::getUserChoice(UserChoice *pChoice)
{
	int choice = 0;
	cout << "Select a choice <1-9>: ";
	do
	{
		cin >> choice;
	} while (choice < LOAD_W_DIET || choice > EXIT);
	*pChoice = (UserChoice)choice;
}