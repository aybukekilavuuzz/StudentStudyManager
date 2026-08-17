#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#define MAX_COURSES 20
#define NAME_SIZE 50
#define DATA_FILE "courses.dat"

struct Course
{
    char name[NAME_SIZE];
    float midterm;
    float final;
    int credit;
};

void addCourse(struct Course courses[], int *courseCount);
void showCourses(struct Course courses[], int courseCount);
void calculateAverage(struct Course courses[], int courseCount);
void searchCourse(struct Course courses[], int courseCount);
void calculateGPA(struct Course courses[], int courseCount);
void updateCourse(struct Course courses[], int courseCount);
void deleteCourse(struct Course courses[], int *courseCount);
void saveData(struct Course courses[], int courseCount);
int loadData(struct Course courses[]);
int findCourse(struct Course courses[], int courseCount, const char name[]);
void clearInput(void);
void printCourse(struct Course *course);

int main()
{
    struct Course courses[MAX_COURSES];
    int courseCount = loadData(courses);
    int choice;

    do
    {
        printf("\n=================================\n");
        printf("      STUDENT STUDY MANAGER\n");
        printf("=================================\n\n");

        printf("1. Add Course\n");
        printf("2. Show Courses\n");
        printf("3. Calculate Average\n");
        printf("4. Search Course\n");
        printf("5. Calculate GPA\n");
        printf("6. Update Course\n");
        printf("7. Delete Course\n");
        printf("8. Save Data\n");
        printf("9. Exit\n");

        printf("\nChoose an option: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            clearInput();
            continue;
        }

        clearInput();

        switch (choice)
        {
            case 1:
                addCourse(courses, &courseCount);
                break;

            case 2:
                showCourses(courses, courseCount);
                break;

            case 3:
                calculateAverage(courses, courseCount);
                break;

            case 4:
                searchCourse(courses, courseCount);
                break;

            case 5:
                calculateGPA(courses, courseCount);
                break;

            case 6:
                updateCourse(courses, courseCount);
                break;

            case 7:
                deleteCourse(courses, &courseCount);
                break;

            case 8:
                saveData(courses, courseCount);
                break;

            case 9:
                saveData(courses, courseCount);
                printf("Goodbye!\n");
                break;

            default:
                printf("Invalid choice. Please choose between 1 and 9.\n");
        }

    } while (choice != 9);

    return 0;
}

void clearInput(void)
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

void addCourse(struct Course courses[], int *courseCount)
{
    if (*courseCount >= MAX_COURSES)
    {
        printf("Course limit reached. Maximum is %d courses.\n", MAX_COURSES);
        return;
    }

    char name[NAME_SIZE];

    printf("\nEnter course name: ");

    if (fgets(name, NAME_SIZE, stdin) == NULL)
    {
        printf("Invalid input.\n");
        return;
    }

    name[strcspn(name, "\n")] = '\0';

    if (strlen(name) == 0)
    {
        printf("Course name cannot be empty.\n");
        return;
    }

    if (findCourse(courses, *courseCount, name) != -1)
    {
        printf("This course already exists.\n");
        return;
    }

    strcpy(courses[*courseCount].name, name);

    while (1)
    {
        printf("Enter credit (1-10): ");

        if (scanf("%d", &courses[*courseCount].credit) == 1 &&
            courses[*courseCount].credit >= 1 &&
            courses[*courseCount].credit <= 10)
        {
            clearInput();
            break;
        }

        printf("Invalid credit. Please enter a value between 1 and 10.\n");
        clearInput();
    }

    while (1)
    {
        printf("Enter midterm grade (0-100): ");

        if (scanf("%f", &courses[*courseCount].midterm) == 1 &&
            isfinite(courses[*courseCount].midterm) &&
            courses[*courseCount].midterm >= 0 &&
            courses[*courseCount].midterm <= 100)
        {
            clearInput();
            break;
        }

        printf("Invalid grade. Please enter a value between 0 and 100.\n");
        clearInput();
    }

    while (1)
    {
        printf("Enter final grade (0-100): ");

        if (scanf("%f", &courses[*courseCount].final) == 1 &&
            isfinite(courses[*courseCount].final) &&
            courses[*courseCount].final >= 0 &&
            courses[*courseCount].final <= 100)
        {
            clearInput();
            break;
        }

        printf("Invalid grade. Please enter a value between 0 and 100.\n");
        clearInput();
    }

    (*courseCount)++;

    printf("\nCourse added successfully!\n");
}

void showCourses(struct Course courses[], int courseCount)
{
    if (courseCount == 0)
    {
        printf("\nNo courses found.\n");
        return;
    }

    printf("\n========== COURSE LIST ==========\n");

    for (int i = 0; i < courseCount; i++)
    {
        printf("\n[%d]\n", i + 1);
        printCourse(&courses[i]);
    }
}

void printCourse(struct Course *course)
{
    float average;

    average = course->midterm * 0.4f +
              course->final * 0.6f;

    printf("Course: %s\n", course->name);
    printf("Credit: %d\n", course->credit);
    printf("Midterm: %.2f\n", course->midterm);
    printf("Final: %.2f\n", course->final);
    printf("Average: %.2f\n", average);

    if (average >= 90)
        printf("Letter Grade: AA\n");
    else if (average >= 85)
        printf("Letter Grade: BA\n");
    else if (average >= 80)
        printf("Letter Grade: BB\n");
    else if (average >= 70)
        printf("Letter Grade: CB\n");
    else if (average >= 60)
        printf("Letter Grade: CC\n");
    else if (average >= 50)
        printf("Letter Grade: DC\n");
    else if (average >= 40)
        printf("Letter Grade: DD\n");
    else
        printf("Letter Grade: FF\n");

    if (average >= 50)
        printf("Status: PASSED\n");
    else
        printf("Status: FAILED\n");
}

int findCourse(struct Course courses[], int courseCount, const char name[])
{
    for (int i = 0; i < courseCount; i++)
    {
        if (strcmp(courses[i].name, name) == 0)
            return i;
    }

    return -1;
}

void calculateAverage(struct Course courses[], int courseCount)
{
    if (courseCount == 0)
    {
        printf("\nNo courses available.\n");
        return;
    }

    char searchName[NAME_SIZE];

    printf("\nEnter course name: ");

    if (fgets(searchName, NAME_SIZE, stdin) == NULL)
        return;

    searchName[strcspn(searchName, "\n")] = '\0';

    int index = findCourse(courses, courseCount, searchName);

    if (index == -1)
    {
        printf("Course not found.\n");
        return;
    }

    float average = courses[index].midterm * 0.4f +
                    courses[index].final * 0.6f;

    printf("\nCourse: %s\n", courses[index].name);
    printf("Average: %.2f\n", average);

    if (average >= 50)
        printf("Status: PASSED\n");
    else
        printf("Status: FAILED\n");
}

void searchCourse(struct Course courses[], int courseCount)
{
    if (courseCount == 0)
    {
        printf("\nNo courses available.\n");
        return;
    }

    char searchName[NAME_SIZE];

    printf("\nSearch course: ");

    if (fgets(searchName, NAME_SIZE, stdin) == NULL)
        return;

    searchName[strcspn(searchName, "\n")] = '\0';

    if (strlen(searchName) == 0)
    {
        printf("Search term cannot be empty.\n");
        return;
    }

    int found = 0;

    for (int i = 0; i < courseCount; i++)
    {
        if (strstr(courses[i].name, searchName) != NULL)
        {
            printCourse(&courses[i]);
            found = 1;
        }
    }

    if (!found)
        printf("Course not found.\n");
}

void calculateGPA(struct Course courses[], int courseCount)
{
    if (courseCount == 0)
    {
        printf("\nNo courses available.\n");
        return;
    }

    float totalPoints = 0.0f;
    int totalCredits = 0;

    for (int i = 0; i < courseCount; i++)
    {
        float average = courses[i].midterm * 0.4f +
                        courses[i].final * 0.6f;

        float gradePoint;

        if (average >= 90)
            gradePoint = 4.0f;
        else if (average >= 85)
            gradePoint = 3.5f;
        else if (average >= 80)
            gradePoint = 3.0f;
        else if (average >= 70)
            gradePoint = 2.5f;
        else if (average >= 60)
            gradePoint = 2.0f;
        else if (average >= 50)
            gradePoint = 1.5f;
        else if (average >= 40)
            gradePoint = 1.0f;
        else
            gradePoint = 0.0f;

        totalPoints += gradePoint * courses[i].credit;
        totalCredits += courses[i].credit;
    }

    if (totalCredits == 0)
    {
        printf("GPA cannot be calculated.\n");
        return;
    }

    printf("\nGPA: %.2f / 4.00\n",
           totalPoints / totalCredits);
}

void updateCourse(struct Course courses[], int courseCount)
{
    if (courseCount == 0)
    {
        printf("\nNo courses available.\n");
        return;
    }

    char searchName[NAME_SIZE];

    printf("\nEnter course name to update: ");

    if (fgets(searchName, NAME_SIZE, stdin) == NULL)
        return;

    searchName[strcspn(searchName, "\n")] = '\0';

    int index = findCourse(courses, courseCount, searchName);

    if (index == -1)
    {
        printf("Course not found.\n");
        return;
    }

    printf("\nCurrent information:\n");
    printCourse(&courses[index]);

    printf("\nEnter new information:\n");

    while (1)
    {
        printf("New credit (1-10): ");

        if (scanf("%d", &courses[index].credit) == 1 &&
            courses[index].credit >= 1 &&
            courses[index].credit <= 10)
        {
            clearInput();
            break;
        }

        printf("Invalid credit.\n");
        clearInput();
    }

    while (1)
    {
        printf("New midterm grade (0-100): ");

        if (scanf("%f", &courses[index].midterm) == 1 &&
            isfinite(courses[index].midterm) &&
            courses[index].midterm >= 0 &&
            courses[index].midterm <= 100)
        {
            clearInput();
            break;
        }

        printf("Invalid grade.\n");
        clearInput();
    }

    while (1)
    {
        printf("New final grade (0-100): ");

        if (scanf("%f", &courses[index].final) == 1 &&
            isfinite(courses[index].final) &&
            courses[index].final >= 0 &&
            courses[index].final <= 100)
        {
            clearInput();
            break;
        }

        printf("Invalid grade.\n");
        clearInput();
    }

    printf("Course updated successfully!\n");
}

void deleteCourse(struct Course courses[], int *courseCount)
{
    if (*courseCount == 0)
    {
        printf("\nNo courses available.\n");
        return;
    }

    char searchName[NAME_SIZE];

    printf("\nEnter course name to delete: ");

    if (fgets(searchName, NAME_SIZE, stdin) == NULL)
        return;

    searchName[strcspn(searchName, "\n")] = '\0';

    int index = findCourse(courses, *courseCount, searchName);

    if (index == -1)
    {
        printf("Course not found.\n");
        return;
    }

    printf("\nCourse: %s\n", courses[index].name);

    char answer;

    printf("Are you sure you want to delete it? (y/n): ");

    if (scanf(" %c", &answer) != 1)
    {
        clearInput();
        return;
    }

    clearInput();

    if (tolower((unsigned char)answer) != 'y')
    {
        printf("Deletion cancelled.\n");
        return;
    }

    for (int i = index; i < *courseCount - 1; i++)
        courses[i] = courses[i + 1];

    (*courseCount)--;

    printf("Course deleted successfully!\n");
}

void saveData(struct Course courses[], int courseCount)
{
    FILE *file = fopen(DATA_FILE, "wb");

    if (file == NULL)
    {
        printf("Error opening file for saving.\n");
        return;
    }

    if (fwrite(&courseCount, sizeof(int), 1, file) != 1)
    {
        printf("Error saving course count.\n");
        fclose(file);
        return;
    }

    if (courseCount > 0)
    {
        if (fwrite(courses,
                   sizeof(struct Course),
                   courseCount,
                   file) != (size_t)courseCount)
        {
            printf("Error saving course data.\n");
            fclose(file);
            return;
        }
    }

    if (fclose(file) != 0)
    {
        printf("Error closing data file.\n");
        return;
    }

    printf("Data saved successfully.\n");
}

int loadData(struct Course courses[])
{
    FILE *file = fopen(DATA_FILE, "rb");
    int courseCount;

    if (file == NULL)
        return 0;

    if (fread(&courseCount, sizeof(int), 1, file) != 1)
    {
        fclose(file);
        printf("Data file is corrupted.\n");
        return 0;
    }

    if (courseCount < 0 || courseCount > MAX_COURSES)
    {
        fclose(file);
        printf("Invalid data file.\n");
        return 0;
    }

    if (courseCount > 0)
    {
        if (fread(courses,
                  sizeof(struct Course),
                  courseCount,
                  file) != (size_t)courseCount)
        {
            fclose(file);
            printf("Data file is incomplete.\n");
            return 0;
        }
    }

    fclose(file);

    for (int i = 0; i < courseCount; i++)
    {
        courses[i].name[NAME_SIZE - 1] = '\0';

        if (courses[i].credit < 1 || courses[i].credit > 10 ||
            !isfinite(courses[i].midterm) ||
            !isfinite(courses[i].final) ||
            courses[i].midterm < 0 || courses[i].midterm > 100 ||
            courses[i].final < 0 || courses[i].final > 100)
        {
            printf("Invalid course data found. Data was not loaded.\n");
            return 0;
        }
    }

    return courseCount;
}