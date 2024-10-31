#include<stdio.h>
#include<string.h>
#include<ctype.h>
#define MAX 5

//declare struct
typedef struct{
	
	char name[50];
	double homeworkAvg;
	double quizAvg;
	double examAvg;
	
}gradebook_s;

//define six functions
void printOptions();
int addStudent(gradebook_s studentGrades[], int currentStudents);
int removeStudent(gradebook_s studentGrades[], int currentStudents);
void updateGrades(gradebook_s studentGrades[], int currentStudents);
void printGrades(gradebook_s studentGrades[], int currentStudents);
void missingGrades(gradebook_s studentGrades[], int currentStudents);
void displayIDs(gradebook_s studentGrades[], int currentStudents);

int main()
{
	//declare array and variables
	gradebook_s studentGrades[MAX];
	int currentStudents = 0;
	char option;
	
	//print opening statement
	printf("Welcome to your gradebook management system!\n");
	
	//while function is not exit keep asking for new functions
	while(option != 'e' || option != 'E')
	{
		//call list of options
		printOptions();
		
		//ask for selection
		printf("Selection: ");
		scanf(" %c", &option);
		
		if(option == 'a' || option == 'A') //add student
		{
			currentStudents = addStudent(studentGrades, currentStudents);
		}
		else if(option == 'r' || option == 'R') //remove student
		{
			currentStudents = removeStudent(studentGrades, currentStudents);
		}
		else if(option == 'p' || option == 'P') //print grades
		{
			printGrades(studentGrades, currentStudents);
		}
		else if(option == 'u' || option == 'U') //update grades
		{
			updateGrades(studentGrades, currentStudents);
		}
		else if(option == 'm' || option == 'M') //missing grades
		{
			missingGrades(studentGrades, currentStudents);
		}
		else if(option == 'd' || option == 'D') //deiplay students and IDs
		{
			displayIDs(studentGrades, currentStudents);
		}
		else if(option == 'e' || option == 'E') //exit function
		{
			break;
		}
		else //try again invalid input
		{
			printf("Invalid input please try again.\n");
		}
	}

	//create file for writting to
	FILE *file = fopen("gradebook.txt", "w");
	
	//if file exists write information to file
	if(file != NULL)
	{
		//until num of students print all information per student
		for (int i = 0; i < currentStudents; i++) 
		{
            fprintf(file, "Name: %s\n", studentGrades[i].name);
            fprintf(file, "Homework Average: %.2lf\n", studentGrades[i].homeworkAvg);
            fprintf(file, "Quiz Average: %.2lf\n", studentGrades[i].quizAvg);
            fprintf(file, "Exam Average: %.2lf\n", studentGrades[i].examAvg);
            fprintf(file, "Weighted Average: %.2lf\n", 
                ((0.5 * studentGrades[i].homeworkAvg) + (0.2 * studentGrades[i].quizAvg) + (0.3 * studentGrades[i].examAvg)));
            fprintf(file, "\n");
        }
	}
	
	//close file
	fclose(file);
	
	return 0;
}

//function 1
void printOptions()
{
	printf("************************************\n");
	printf("What would you like to do in the gradebook?\n");
	printf("A: Add a Student to the Gradebook\n");
	printf("R: Remove a Student from the Gradebook\n");
	printf("P: Print Grades from the Gradebook\n");
	printf("U: Update a Student's Grade\n");
	printf("M: Determine who is missing Grades\n");
	printf("D: Display all names and associated IDs.\n");
	printf("E: Exit\n");
	printf("************************************\n");
}

//add student function
int addStudent(gradebook_s studentGrades[], int currentStudents)
{
	//last name
	char sur[50];
	
	if(currentStudents != MAX)
	{
		//enter first and last name separated by space
		printf("Enter the Student's Full Name: ");
		scanf("%s%s", studentGrades[currentStudents].name , sur);
        
        //combine into one string
        strcat(strcat(studentGrades[currentStudents].name, " "), sur);
        
        //add a student
        currentStudents++;
	}
	else
	{
		//if gradebook full
		printf("Your gradebook is full!\n");
	}
	
	return currentStudents;
}

//remove student
int removeStudent(gradebook_s studentGrades[], int currentStudents)
{
	//if gradebook has at least one student
	if (currentStudents > 0) {
		
		//get name of student
        char nameRemove[50];
        char nameRemoveSUR[50];
        printf("Enter the name of the student to remove: ");
        scanf("%s%s", nameRemove, nameRemoveSUR);
        
        //convert to one string called nameRemove
        //with space bewteen first and last name
        strcat(nameRemove, " ");
        strcat(nameRemove, nameRemoveSUR);

		//declare an index for when found 
        int found = -1;
        
        //go through all students
        for (int i = 0; i < currentStudents; i++) {
            if (strcmp(nameRemove, studentGrades[i].name) == 0) 
			{
				//set index to location student was found at
                found = i;
                break;
            }
        }
        
		//if found then remove the student
        if (found != -1)
		{
            // Remove student by shifting the elements in array
            for (int i = found; i < currentStudents; i++)
			{
                studentGrades[i] = studentGrades[i + 1];
            }
            studentGrades--;
    		//remove one student from count
            currentStudents--;
            printf("Removing %s from the gradebook.\n", nameRemove);
        } 
		else
		{
			//if student not found
            printf("%s not found.\n", nameRemove);
        }
    } 
	else 
	{
		//no students in gradebook
        printf("Gradebook is empty.\n");
    }
    
    return currentStudents;
    
}
void updateGrades(gradebook_s studentGrades[], int currentStudents)
{
	//if at least one student
	if (currentStudents > 0) {
        int studentID;
        
        //list all students and IDs by calling function
        printf("Here are the list of students and their IDs.\n");
        displayIDs(studentGrades, currentStudents);
        
        //collect ID of student you want to update
        printf("Enter the ID of the student: ");
        scanf("%d", &studentID);

		//look for student in array if found 
		//set index to that location
        int found = -1;
        for(int i = 0; i < currentStudents; i++)
		{
            if (studentID == i) 
			{
                found = i;
                break;
            }
        }
		
		//if found then update grades for the selected student
        if (found != -1) 
		{
            printf("You are about to update the grades entered for %s.\n", studentGrades[found].name);
            printf("Please enter the respective score for each assessment group.\n");
            printf("Enter the overall homework average: ");
            scanf("%lf", &studentGrades[found].homeworkAvg);
            printf("Enter the overall quiz average: ");
            scanf("%lf", &studentGrades[found].quizAvg);
            printf("Enter the overall exam average: ");
            scanf("%lf", &studentGrades[found].examAvg);
            printf("Success! %s's grades entered are now updated in your gradebook!\n", studentGrades[found].name);
        } 
		else //not found
		{
        	printf("Student not found.\n");
        }
    } 
	else //no students in gradebook
	{
        printf("Gradebook is empty. Cannot update grades.\n");
    }
}

//print grades
void printGrades(gradebook_s studentGrades[], int currentStudents)
{
	//print grades for each student and calculate weighted avergae
	if (currentStudents > 0) {
	        printf("Student Grades:\n");
	        for (int i = 0; i < currentStudents; i++) {
	            printf("Name: %s\n", studentGrades[i].name);
	            printf("Homework Average: %.2lf\n", studentGrades[i].homeworkAvg);
	            printf("Quiz Average: %.2lf\n", studentGrades[i].quizAvg);
	            printf("Exam Average: %.2lf\n", studentGrades[i].examAvg);
	            printf("Weighted Average: %.2lf\n", (0.5 * studentGrades[i].homeworkAvg) + (0.2 * studentGrades[i].quizAvg) + (0.3 * studentGrades[i].examAvg));
	            printf("\n");
	        }
	    } 
		else //gradebook empty
		{
	        printf("Gradebook is empty.\n");
	    }
}

//missing grades
void missingGrades(gradebook_s studentGrades[], int currentStudents)
{
	if (currentStudents > 0)
	{
        printf("Students with Missing Grades:\n");
        int found = 0; // Track missing grades found

		//go through each student to find when values are 0
        for(int j = 0; j < currentStudents; j++) 
		{
            if (studentGrades[j].homeworkAvg == 0.0 || studentGrades[j].quizAvg == 0.0 || studentGrades[j].examAvg == 0.0) {
                found = 1;
                printf("%s is missing grades.\n", studentGrades[j].name);
            }
        }

		//None found
        if (!found) {
            printf("No students are missing grades.\n");
        }
    } 
	else //gradebook empty
	{
        printf("Gradebook is empty.\n");
    }
}

//display names and IDs
void displayIDs(gradebook_s studentGrades[], int currentStudents)
{
	//display names and IDs for each student
	if (currentStudents > 0)
	{
        printf("List of students and their IDs:\n");
        for (int i = 0; i < currentStudents; i++) 
		{
            printf("Name: %s ID: %d\n", studentGrades[i].name, i);
        }
	} 
		else //gradebook empty
		{
	       	printf("Gradebook is empty.\n");
    	}
}




