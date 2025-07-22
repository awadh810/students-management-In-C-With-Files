#include <iostream>
#include <ostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <windows.h>
#include <iomanip>

using namespace std;
ofstream ofs;
ifstream ifs;
int counter = 0;


struct studentInfo
{
    string itsName;
    string gender;
    string itsAddress;
    string itsSpecializing;
    int itsLevel;
    int itsStudNumber;
    string subjectName[6];
    int subjectMark[6];

} Std;


struct systemInfo
{
    string Specializing_Name;
    int total_Level_Specializing;
    int Specializing_ID;
    int total_Students_In_Specializing;
    int total_Males_Students_In_Specializing;
    int total_Females_Students_In_Specializing;
    int last_StudNumber;

    string userName;
    string userAddress;
    int userPassword;
    int userID;

} syste[4] , emplooy;

bool add_New_Student();
bool delete_Student();
bool modify_Data_Student();
bool search_About_Student();
void show_All_Data_Students();
bool sort_Data_In_File();
void system_Setting();

void add_User();
void delete_User();
void show_All_Data_Users();
void show_All_Data_Specializing();

void Program_Interface();
void about_The_Program();
bool login();

string get_Specializing_Name();
void read_Specialize_Data(string SpecializeName);
void write_New_Specialize_Data(string SpecializeName);
void read_students_Data_From_File(studentInfo students[] , int allSize);
void showOneRecord(studentInfo student[] , int index);
int binarySearch(studentInfo Students[] , int allSize , int idSearch);
void openFile();


int main()
{
   int ch ;    bool exite = false;
   system("color f4");

   Program_Interface();

   if (login())
   {
       system("cls");
       do
       {
           cout<<"\n\t\t\t\t\t     Student Management System.\n"
               <<"\n\t\t\t\t\t   ===============================\n\n";

           cout<< "\n\n\t\t|| NO. ||             PROCESS                       \n"
               << "\t\t||=====||===========================================\n"
               << "\t\t||  1  ||Add New Student.\n\t\t||  2  ||Delete Student.\n\t\t||  "
               << "3  ||Querying About Student.\n\t\t||  4  ||Modify Student Data."
               << "\n\t\t||  5  ||Sort Students Data In File.  \t\t\n\t\t||  6  ||Show Students Data."
               << "\n\t\t||  7  ||Setting System.  \t\t\n\t\t||  8  ||About The Program.\n\t\t||  "
               << "9  ||Exit From The Program."
               << "\n\t\t||=================================================\n"
               << "\t\t||\t\t     PROCESS  NO. :  ";             cin>>ch;
           cout<<"\n\t\t\t    ";   system("PAUSE");              system("cls");

           switch (ch){
                 case 1:
                     add_New_Student()?        cout<<"\n\n\t\t\t\t\t\t\t  Saved Student Data is successfully.\n":    cout<<"\t\t\t\t\t\t\t  Student Data is not saved successfully.\n";
                     break;
                 case 2:
                     delete_Student()?         cout<<"\n\n\t\t\t\t\t\t\t  delete Student Data is successfully.\n":    cout<<"\t\t\t\t\t\t\t  There is no student by this ID Number.\n";
                     break;
                 case 3:
                     search_About_Student()?   cout<<"\n\n":                                                          cout<<"\t\t\t\t\t\t\t  Student search is not found.\n";
                     break;
                 case 4:
                     modify_Data_Student()?    cout<<"\n\n\t\t\t\t\t\t\t   Student Data is modify successfully.\n":    cout<<"\t\t\t\t\t\t\t  There is no student by this ID Number.\n";
                     break;
                 case 5:
                     sort_Data_In_File()?      cout<<"\n\n\t\t\t\t\t\t\t   Sorting Student Data is successfully.\n":    cout<<"\t\t\t\t\t\t\t  Sorting Operation is Field.\n";
                     break;
                 case 6:
                     show_All_Data_Students();
                     break;
                 case 7:
                     system_Setting();
                     break;
                case 8:
                    about_The_Program();
                    break;
                case 9:
                    system("cls");
                    cout<<"\n\n\n\t\t\t\t\t     Finish The Program.\n";
                    exit(0);
                    break;

               default:
                   break;
           }

           cout<<"\n\n\t\t\t\t\t\t    ";     system("PAUSE");     system("cls");

       }while(true);
   }

    return 0;
}


// --------------------------------------------------------->> *** <<----------------------------------------------------------
// -------------------------------------------------------- >> *** <<----------------------------------------------------------

bool add_New_Student()
{
    bool isAdded = false;      char Read[50];

                    cout<<"\t\t\t\t\t\t   Add New Student: \n\t\t\t\t\t    ===========================\n\n";
    Std.itsSpecializing = get_Specializing_Name();
    read_Specialize_Data(Std.itsSpecializing);
    Std.itsStudNumber = syste[counter].last_StudNumber + 1;

    cout<<"\t\t\t\t\t\t\t  Add New Student:\n\t\t\t\t\t\t    ===========================\n\n";

    cout<<"\n\t\t\t\t\t\t\t Enter the Name:  " ;             /*gets(Read);   Std.itsName = Read; */     cin>>Std.itsName;
    cout<<"\n\t\t\t\t\t\t\t Enter the Address:  " ;          /*gets(Read);   Std.itsAddress = Read; */  cin>>Std.itsAddress;
    cout<<"\n\t\t\t\t\t\t\t Enter the Level:  " ;            cin>>Std.itsLevel;
    cout<<"\n\t\t\t\t\t\t\t Determine the Gender:  " ;       int ch;
    for (;;)
    {
        cout<<"\n\t\t\t\t\t\t\t\t 1: Male.";
        cout<<"\n\t\t\t\t\t\t\t\t 2: Female.";
        cout<<"\n\n\t\t\t\t\t\t\t\tEnter Your Choice Number Here:  ";    cin>>ch;

        if (ch == 1)
        {
             Std.gender = "Male";   syste[counter].total_Males_Students_In_Specializing += 1;       break;
        }
        else if (ch == 2)
        {
             Std.gender = "Female"; syste[counter].total_Females_Students_In_Specializing += 1;     break;
        }
        else
            cout<<"\n\t\t\t\t\t\t\t Invalid Input ,, Try again." ;
    }

    ofs<<Std.itsStudNumber<<" "<<Std.itsName<<" "<<Std.gender<<" "<<Std.itsAddress<<" "<<Std.itsSpecializing<<" "<<Std.itsLevel;

    cout<<"\n\t\t\t\t\t\t\tEnter The Subjects Name and Marks :  \n";
    for (int i=0; i<6; i++)
    {
        cout<<"\n\t\t\t\t\t\t\t\tSubject Name:  " ;      /*gets(Read);    Std.subjectName[i] = Read;*/    cin>>Std.subjectName[i];
        cout<<"\n\t\t\t\t\t\t\t\t\tSubject Mark:  " ;    cin>>Std.subjectMark[i];
        ofs<<" "<<Std.subjectName[i]<<" "<<Std.subjectMark[i];
    }
    ofs<<endl;
    ofs.close();
    isAdded = true;
    syste[counter].last_StudNumber = Std.itsStudNumber;
    syste[counter].total_Students_In_Specializing += 1;
    write_New_Specialize_Data(Std.itsSpecializing);

    return isAdded;
} // end add new student method;


bool delete_Student()
{
                        cout<<"\t\t\t\t\t\t  Delete Student:\n\t\t\t\t\t    =========================\n\n";

    string  specializeName = get_Specializing_Name();
    ofs.close();
    read_Specialize_Data(specializeName);
    studentInfo students[syste[counter].total_Students_In_Specializing];
    int allSize = syste[counter].total_Students_In_Specializing;

    if (specializeName == "IT")
    {
        ifs.open("IT-Department.txt" , ios::in);   read_students_Data_From_File(students , allSize);   ofs.open("IT-Department.txt" , ios::trunc);
    }

    else if (specializeName == "IS")
    {
        ifs.open("IS-Department.txt" , ios::in);   read_students_Data_From_File(students , allSize);   ofs.open("IS-Department.txt" , ios::trunc);
    }

    else
    {
        ifs.open("CS-Department.txt" , ios::in);   read_students_Data_From_File(students , allSize);    ofs.open("CS-Department.txt" , ios::trunc);
    }

    bool isDeleted = false;
    int id , index = 0;
    cout<<"\n\n\n\n\n\n\n\t\t\t||=========================================== ";
    cout<<"\n\t\t\t||Enter the Student ID that you want to deleted: ";
    cout<<"\n\t\t\t||                 ID:    ";                     cin>>id;
    cout<<"\n\n\t\t\t   ";            system("PAUSE");              system("cls");

    for (int i = 0; i<allSize; i++)
    {
        if (students[i].itsStudNumber != id)
        {
            ofs<<students[i].itsStudNumber<<" "<<students[i].itsName<<" "<<students[i].gender<<" "<<students[i].itsAddress<<" "<<students[i].itsSpecializing<<" "<<students[i].itsLevel;
            for ( int j = 0; j<6; j++)
                    ofs<<" "<<students[i].subjectName[j]<<" "<<students[i].subjectMark[j];
        }
        else
        {
            isDeleted = true;  index = i;
        }
        ofs<<endl;
    }
    ofs.close();

    syste[counter].total_Students_In_Specializing -= 1;
    if (students[index].gender == "Male")
        syste[counter].total_Males_Students_In_Specializing -= 1;
    else
       syste[counter].total_Females_Students_In_Specializing -= 1;
    write_New_Specialize_Data(specializeName);

    return isDeleted;
} // end delete student method ;


bool modify_Data_Student()
{
    char Read[50];
                    cout<<"\t\t\t\t\t\t  Modify Student Data:\n\t\t\t\t\t    ===========================\n\n";

    string  specializeName = get_Specializing_Name();
    ofs.close();
    read_Specialize_Data(specializeName);
    studentInfo students[syste[counter].total_Students_In_Specializing];
    int allSize = syste[counter].total_Students_In_Specializing;

    if (specializeName == "IT")
    {
        ifs.open("IT-Department.txt" , ios::in);   read_students_Data_From_File(students , allSize);   ofs.open("IT-Department.txt" , ios::trunc);
    }

    else if (specializeName == "IS")
    {
        ifs.open("IS-Department.txt" , ios::in);   read_students_Data_From_File(students , allSize);   ofs.open("IS-Department.txt" , ios::trunc);
    }

    else
    {
        ifs.open("CS-Department.txt" , ios::in);   read_students_Data_From_File(students , allSize);    ofs.open("CS-Department.txt" , ios::trunc);
    }

    bool isModify = false;
    int id ;
    cout<<"\n\n\n\n\n\n\n\t\t\t||=========================================== ";
    cout<<"\n\t\t\t||Enter the Student ID that you want to modify its data:  ";
    cout<<"\n\t\t\t||                 ID:";                         cin>>id;
    cout<<"\n\n\t\t\t   ";            system("PAUSE");              system("cls");

    for (int i = 0; i<allSize; i++)
    {
        if (students[i].itsStudNumber == id)
        {
            ofs<<students[i].itsStudNumber<<" "<<students[i].itsName<<" "<<students[i].gender<<" "<<students[i].itsAddress<<" "<<students[i].itsSpecializing<<" "<<students[i].itsLevel;
            for(int j = 0; j<6; j++)
            {
                cout<<"\n\t\t\t     ||====================================";
                cout<<"\n\t\t\t     ||Enter Subject Name and Mark :  "<<j+1;
                cout<<"\n\t\t\t     ||Subject Name: ";    /*gets(Read);     students[i].subjectName[j]  = Read;*/   cin>>students[i].subjectName[j];
                cout<<"\t\t\t     ||Mark:";             cin>>students[i].subjectMark[j];

                ofs<<" "<<students[i].subjectName[j]<<" "<<students[i].subjectMark[j];
            }
            ofs<<endl;
            isModify = true;
        }
        else
        {
            ofs<<students[i].itsStudNumber<<" "<<students[i].itsName<<" "<<students[i].gender<<" "<<students[i].itsAddress<<" "<<students[i].itsSpecializing<<" "<<students[i].itsLevel;
            for ( int j = 0; j<6; j++)
                    ofs<<" "<<students[i].subjectName[j]<<" "<<students[i].subjectMark[j];
            ofs<<endl;
        }
    }
    ofs.close();

    return isModify;
}  // end modify student data method ;


bool search_About_Student()
{
    bool isFound = false;
    int ch;
     cout<<"\t\t\t\t\t\t\t  Search About Student:\n\t\t\t\t\t\t    ===========================\n\n";

    string  specializeName = get_Specializing_Name();
    ofs.close();
    read_Specialize_Data(specializeName);
    studentInfo students[syste[counter].total_Students_In_Specializing];
    int allSize = syste[counter].total_Students_In_Specializing;

    if (specializeName == "IT")
    {
        ifs.open("IT-Department.txt" , ios::in);   read_students_Data_From_File(students , allSize);
    }

    else if (specializeName == "IS")
    {
        ifs.open("IS-Department.txt" , ios::in);   read_students_Data_From_File(students , allSize);
    }

    else
    {
        ifs.open("CS-Department.txt" , ios::in);   read_students_Data_From_File(students , allSize);
    }
                    cout<<"\n\t\t\t\t\t\t\t  Search About Student:\n\t\t\t\t\t\t       ===========================\n\n";

                    cout<<"\n\n\n\t\t\t|| NO.  || Determine the type of search: ";
                    cout<<"\n\t\t\t||==================================================== ";
                    cout<<"\n\t\t\t||  1 : || ID.";
                    cout<<"\n\t\t\t||  2 : || Name.";
                    cout<<"\n\t\t\t||  Otherwise to comeback to main screen.";
                    cout<<"\n\t\t\t||=================================================== ";
                    cout<<"\n\t\t\t||       Type NO. :  ";        cin>>ch;
                    cout<<"\n\n\t\t\t   ";                        system("PAUSE");         system("cls");


    if (ch == 1 )  //binary search  by student id ;
    {
        int idSearch ;
        cout<<"\n\n\n\n\n\n\n\t\t\t||=========================================== ";
        cout<<"\n\t\t\t||Enter the Student ID that you want to search about:  ";
        cout<<"\n\t\t\t||                 ID:  ";                       cin>>idSearch;
        cout<<"\n\n\t\t\t   ";            system("PAUSE");              system("cls");

        int c = binarySearch(students , allSize , idSearch);  //binary search ;
        if (c != -1 )
        {
             cout<<"\n\t\t\t The Student you Search about is found and these its data: ";
             showOneRecord(students , c);
             isFound = true;
        }
    }

    else if (ch == 2)   // sequential search  by Student Name ;
    {
        char nameSearch[50] ;
        cout<<"\n\n\n\n\n\n\n\t\t\t||=========================================== ";
        cout<<"\n\t\t\t||Enter the Student Name that you want to search it:  ";
        cout<<"\n\t\t\t||                 Name:  ";                     /* gets(nameSearch);*/ cin>>nameSearch;
        cout<<"\n\n\t\t\t   ";            system("PAUSE");              system("cls");

        for (int i = 0; i<allSize; i++ )
        {
            if (students[i].itsName == nameSearch)  // sequential search ;
            {
                cout<<"\n\t\t\t The Student you Search about is found and these its data: ";
                showOneRecord(students , i);
                isFound = true;   break;
            }
        }
    }

    else
        system("PAUSE");

    return isFound;
}  // end search about student method ;



void show_All_Data_Students()   // show data one Specialize
{
                cout<<"\t\t\t\t\t\t\t  Show All Students Data:\n\t\t\t\t\t\t    ===========================\n\n";

    string  specializeName = get_Specializing_Name();
    ofs.close();
    read_Specialize_Data(specializeName);
    studentInfo students[syste[counter].total_Students_In_Specializing];
    int allSize = syste[counter].total_Students_In_Specializing;

    if (specializeName == "IT")
    {
        ifs.open("IT-Department.txt" , ios::in);   read_students_Data_From_File(students , allSize);
    }

    else if (specializeName == "IS")
    {
        ifs.open("IS-Department.txt" , ios::in);   read_students_Data_From_File(students , allSize);
    }

    else
    {
        ifs.open("CS-Department.txt" , ios::in);   read_students_Data_From_File(students , allSize);
    }

    if (allSize != 0)
        for (int i = 0; i<allSize; i++ )
        {
            showOneRecord(students , i);
        }
    else
        cout<<"\n\t\t\t The File is Empty.";

}  // end show All the data method ;


bool sort_Data_In_File()
{
    bool isSorting = false;
               cout<<"\t\t\t\t\t\t\t  Sort Data Students:\n\t\t\t\t\t\t    ===========================\n\n";
               int ch ;
               cout<<"\n\n\n\t\t\t|| NO.  || Determine the type of sorting: ";
               cout<<"\n\t\t\t||============================================== ";
               cout<<"\n\t\t\t||  1 : || ID.";
               cout<<"\n\t\t\t||  2 : || Name.";
               cout<<"\n\t\t\t||  3 : || Level.";
               cout<<"\n\t\t\t||  Otherwise to comeback to main screen.";
               cout<<"\n\t\t\t||================================================ ";
               cout<<"\n\t\t\t||        Sorting NO. :  ";        cin>>ch;
               cout<<"\n\n\t\t\t   ";                            system("PAUSE");         system("cls");

    string  specializeName = get_Specializing_Name();
    ofs.close();
    read_Specialize_Data(specializeName);
    studentInfo students[ syste[counter].total_Students_In_Specializing ];
    int allSize = syste[counter].total_Students_In_Specializing;

    if (specializeName == "IT")
    {
        ifs.open("IT-Department.txt" , ios::in);   read_students_Data_From_File(students , allSize);   ofs.open("IT-Department.txt" , ios::trunc);
    }

    else if (specializeName == "IS")
    {
        ifs.open("IS-Department.txt" , ios::in);   read_students_Data_From_File(students , allSize);   ofs.open("IS-Department.txt" , ios::trunc);
    }

    else
    {
        ifs.open("CS-Department.txt" , ios::in);   read_students_Data_From_File(students , allSize);    ofs.open("CS-Department.txt" , ios::trunc);
    }


   if (ch == 1)
   {
       studentInfo temp;
       for (int i=0; i<allSize; i++)
       {
           for(int j=0; j<allSize-1; j++)
           {
               if (students[j].itsStudNumber > students[j+1].itsStudNumber)
               {
                   temp = students[j];
                   students[j] = students[j+1];
                   students[j+1] = temp;
               }
           }

            ofs<<students[i].itsStudNumber<<" "<<students[i].itsName<<" "<<students[i].gender<<" "<<students[i].itsAddress<<" "<<students[i].itsSpecializing<<" "<<students[i].itsLevel;
            for ( int j = 0; j<6; j++)
                    ofs<<" "<<students[i].subjectName[j]<<" "<<students[i].subjectMark[j];
            ofs<<endl;
       }
       ofs.close();   isSorting = true;
   }


   else if (ch == 2)
   {
       studentInfo temp;
       for (int i=0; i<allSize; i++)
       {
           for(int j=0; j<allSize-1; j++)
           {
               if (students[j].itsName > students[j+1].itsName)
               {
                   temp = students[j];
                   students[j] = students[j+1];
                   students[j+1] = temp;
               }
           }
            ofs<<students[i].itsStudNumber<<" "<<students[i].itsName<<" "<<students[i].gender<<" "<<students[i].itsAddress<<" "<<students[i].itsSpecializing<<" "<<students[i].itsLevel;
            for ( int j = 0; j<6; j++)
                    ofs<<" "<<students[i].subjectName[j]<<" "<<students[i].subjectMark[j];
            ofs<<endl;
       }
       ofs.close();    isSorting = true;
   }

   else if (ch == 3)
   {
       studentInfo temp;
       for (int i=0; i<allSize; i++)
       {
           for(int j=0; j<allSize-1; j++)
           {
               if (students[j].itsLevel > students[j+1].itsLevel)
               {
                   temp = students[j];
                   students[j] = students[j+1];
                   students[j+1] = temp;
               }
           }
            ofs<<students[i].itsStudNumber<<" "<<students[i].itsName<<" "<<students[i].gender<<" "<<students[i].itsAddress<<" "<<students[i].itsSpecializing<<" "<<students[i].itsLevel;
            for ( int j = 0; j<6; j++)
                    ofs<<" "<<students[i].subjectName[j]<<" "<<students[i].subjectMark[j];
            ofs<<endl;
       }
       ofs.close();      isSorting = true;
   }

   else
   {
       ofs.close();   system("PAUSE");
   }

   return isSorting;

}  // end sort method


string get_Specializing_Name()
{
    int numberSpecializing;
    string nameSpecializing;
    for ( ;; )
    {
        cout<<"\n\n\t\t      Choose Number Of Specializing : "; /*that you want to add the new Student to it :";*/
        cout<<"\n\n\n\t\t    || NO.  ||    Specializing      ";
        cout<<"\n\t\t    ||==================================";
        cout<<"\n\t\t    ||  1   ||         IT           ";
        cout<<"\n\t\t    ||  2   ||         IS           ";
        cout<<"\n\t\t    ||  3   ||         CS           ";
        cout<<"\n\t\t    ||==================================";
        cout<<"\n\t\t    ||          Specializing  NO. :  ";       cin>>numberSpecializing;
        cout<<"\n\n\t\t\t     ";     system("PAUSE");   system("cls");

        if (numberSpecializing == 1)
        {
            nameSpecializing = "IT";     ofs.open("IT-Department.txt" , ios::app);     break;
        }

        else if (numberSpecializing == 2)
        {
            nameSpecializing = "IS";     ofs.open("IS-Department.txt", ios::app);      break;
        }

        else if (numberSpecializing == 3)
        {
            nameSpecializing = "CS";      ofs.open("CS-Department.txt", ios::app);     break;
        }

        else
            cout<<"\n\t\t\t Invalid Input ,,  Try again\n";

        } // end for loop

        return nameSpecializing;
} // end get_Specializing_Name_From_The_System method ;


void read_Specialize_Data(string SpecializeName)   // change to void
{
    ifs.open("Specialize-Data.txt", ios::in);
    counter = 0;
    int index = 0;

    while(!ifs.eof())
    {
        ifs>>syste[index].Specializing_Name>>syste[index].total_Level_Specializing>>syste[index].Specializing_ID>>syste[index].total_Students_In_Specializing>>syste[index].total_Males_Students_In_Specializing>>syste[index].total_Females_Students_In_Specializing>>syste[index].last_StudNumber;
        if ( SpecializeName == syste[index].Specializing_Name )
        {
            counter = index;
        }
        index++;
    }
    ifs.close();

} // end read_Specialize_Data method ;


void write_New_Specialize_Data(string SpecializeName)
{
    ofs.open("Specialize-Data.txt" , ios::trunc);
    for (int i = 0; i<3; i++)
    {
        if (SpecializeName == syste[i].Specializing_Name)
            ofs<<syste[counter].Specializing_Name<< " " <<syste[counter].total_Level_Specializing<< " " <<syste[counter].Specializing_ID<< " " <<syste[counter].total_Students_In_Specializing<< " " <<syste[counter].total_Males_Students_In_Specializing<< " " <<syste[counter].total_Females_Students_In_Specializing<< " " <<syste[counter].last_StudNumber<<endl;
        else
            ofs<<syste[i].Specializing_Name<< " " <<syste[i].total_Level_Specializing<< " " <<syste[i].Specializing_ID<< " " <<syste[i].total_Students_In_Specializing<< " " <<syste[i].total_Males_Students_In_Specializing<< " " <<syste[i].total_Females_Students_In_Specializing<< " " <<syste[i].last_StudNumber<<endl;
    }
    ofs.close();

} // end write_New_Specialize_Data method ;


void read_students_Data_From_File(studentInfo students[] ,int allSize)
{
    int x = 0 ;
    while(!ifs.eof())
    {
        ifs>>students[x].itsStudNumber>>students[x].itsName>>students[x].gender>>students[x].itsAddress>>students[x].itsSpecializing>>students[x].itsLevel;
        for (int i =0; i<6; i++)
        {
            ifs>>students[x].subjectName[i]>>students[x].subjectMark[i];
        }
        x++;
    }
    ifs.close();
}

void showOneRecord(studentInfo student[] , int index)
{
    float result = 0;
    cout<<"\n\n\n \t||   |Number: "<<student[index].itsStudNumber<<" "<<"\t\t  |Name: "<<student[index].itsName<< "\t\t |Specialize: "<<student[index].itsSpecializing  << "\n \t||   |Level: "<<student[index].itsLevel  <<  "\t\t          |Gender: "<<student[index].gender<<"\t         |Address: "<<student[index].itsAddress<<endl;
    cout<<"\t||=======================================================================";
    for(int i=0; i<6; i++)
    {
        cout<<"\n\t||       Subject Name: "  << i+1 << " : "   << student[index].subjectName[i];
        cout<<"\t\t         Subject Mark "   << i+1 << " : "   << student[index].subjectMark[i];
        Sleep(100);
        result += student[index].subjectMark[i];
    }

    result = result / 9;

    if(result<=0.9)
        {result=0;};
    cout<<"\n\t||========================================================================";

    if(result>=90){
        cout<<"\n\t||Estimate: A"<<"\t      |Rate: %"<<result<<"\t         |Total Grades: "<<result*9<<endl;}

    else if(result>=80){
        cout<<"\n\t||Estimate: B"<<"\t      |Rate: %"<<result<<"\t         |Total Grades: "<<result*9<<endl;}

    else if(result>=70){
        cout<<"\n\t||Estimate: C"<<"\t      |Rate: %"<<result<<"\t         |Total Grades: "<<result*9<<endl;}

    else if(result>=60){
        cout<<"\n\t||Estimate: D"<<"\t      |Rate: %"<<result<<"\t         |Total Grades: "<<result*9<<endl;}

    else{
        cout<<"\n\t||Estimate: F"<<"\t      |Rate: %"<<result<<"\t         |Total Grades: "<<result*9<<endl;}

}  // end show one record method ;


int binarySearch(studentInfo Students[] , int allSize , int idSearch)
{
     studentInfo temp;
       for (int i=0; i<allSize; i++)
       {
           for(int j=0; j<allSize-1; j++)
           {
               if (Students[j].itsStudNumber > Students[j+1].itsStudNumber)
               {
                   temp = Students[j];
                   Students[j] = Students[j+1];
                   Students[j+1] = temp;
               }
           }
       }
    int low = 0;
    int high = allSize - 1;
    int mid;
    while (low <= high)
    {
        mid = (low + high)/2;
        if (Students[mid].itsStudNumber < idSearch)
            low = mid + 1;

        else if (Students[mid].itsStudNumber > idSearch)
            high = mid - 1;

        else
            return mid;
    }
    return -1;

}  // end binary Search


void system_Setting()
{
    cout<<"\n\t\t\t\t\t\t       Welcome to Student System Management.\n\t\t\t\t\t\t    ___________________________________________\n\n";
    bool exit =true;
    do
    {
        show_All_Data_Specializing();         cout<<"\n\n\t\t\t\t\t\t       ";     system("PAUSE");

        int choice , ch;

        cout<<"\n\n\n\t\t\t\t\t\t    || NO.  ||    Operations      ";
        cout<<"\n\t\t\t\t\t\t    ||==================================";
        cout<<"\n\t\t\t\t\t\t    ||  1   || Department of Management System Users.";
        cout<<"\n\t\t\t\t\t\t    ||  2   || To comeback to main screen.";
        cout<<"\n\t\t\t\t\t\t    ||==================================";
        cout<<"\n\n\t\t\t\t\t\t    || Operation NO. :  ";       cin>>choice;
        cout<<"\n\n\t\t\t\t\t\t\t     ";     system("PAUSE");   system("cls");

        switch (choice)
        {
           case 1:
               cout<<"\n\n\t\t\t\t\t\t     You can do the following operations : \n\t\t\t\t\t\t    _________________________________________\n"
                   <<"\n\t\t\t\t\t\t 1:  Add New User."
                   <<"\n\t\t\t\t\t\t 2:  Delete  User."
                   <<"\n\t\t\t\t\t\t 3:  Show All Users Data."
                   <<"\n\t\t\t\t\t\t   Otherwise to comeback to main screen."
                   <<"\n\t\t\t\t\t\t   Enter Your Choice Number Here:  ";
               cin>>ch;

              if ( ch == 1 )
                  add_User();

              else if ( ch == 2 )
                 delete_User();

              else if ( ch == 3 )
                 show_All_Data_Users();
              cout<<"\n\n\t\t\t\t\t\t       ";      system("PAUSE");

              break;

           case 2:
              exit = false;
              break;

           default:
              show_All_Data_Specializing();
              break;
        } // end switch ;

        system("cls");
        }while(exit != false);


}  // end system setting method ;



void add_User()
{
    char Read[50];
    ofs.open("system-Users.txt" , ios::app);        system("cls");
    cout<<"\n\n\t\t\t\t\t\t\t  Add New User:\n\t\t\t\t\t\t    ===========================\n\n";

    cout<<"\n\t\t\t\t\t\t\t Enter User Name :  " ;               /*gets(Read);   emplooy.userName = Read;*/  cin>>emplooy.userName;
    cout<<"\n\t\t\t\t\t\t\t Enter User Address :  " ;            /*gets(Read);   emplooy.userAddress;*/      cin>>emplooy.userAddress;
    cout<<"\n\t\t\t\t\t\t\t Enter User Password :  " ;           cin>>emplooy.userPassword;

    ofs<< emplooy.userName << " " << emplooy.userAddress << " " << emplooy.userPassword <<endl;
    ofs.close();
    cout<< "\n\t\t\t\t\t\t Data User saved successfully.\n";

}  // end add user method ;

void delete_User()
{
    system("cls");        cout<<"\n\n\t\t\t\t\t\t\t     \tDelete User: \n\t\t\t\t\t\t\t    =======================\n\n";
    bool isDeleted = false;   char name[50];    int size = 0;
    systemInfo users[100];

    ifs.open("system-Users.txt" , ios::in);
    while (!ifs.eof())
    {
        ifs >> users[size].userName >> users[size].userAddress >> users[size].userPassword;
        size++;
    }
    ifs.close();  size--;

    ofs.open("system-Users.txt" , ios::trunc);
    cout<<"\t\t\t\t\t\t   Enter The User Name that you want to delete it:  ";    gets(name);   //cin>> name;

    for ( int i =0; i<size; i++)
    {
        if (name != users[i].userName)
        {
            ofs << users[i].userName << " " << users[i].userAddress << " " << users[i].userPassword <<endl;
        }

        else
           isDeleted = true ;
    }
    ofs.close();
    if (isDeleted == true)
        cout<<"\n\t\t\t\t\t\t   The user is deleted from the system.\n";
    else
        cout<<"\n\t\t\t\t\t\t   There is not user by this name.\n";
}  // end delete user method ;


void show_All_Data_Users()
{
    system("cls");      cout<<"\n\n\t\t\t\t\t\t\t      Show Data Users:\n\t\t\t\t\t\t\t    =========================\n\n";
    string name;     int size = 0;
    systemInfo users[100];

    ifs.open("system-Users.txt" , ios::in);
    while (!ifs.eof())
    {
        ifs >> users[size].userName >> users[size].userAddress >> users[size].userPassword;
        size++;
    }
    ifs.close();  size--;

    cout << "\n\n\t\t\t\t      User Name    ||   User Address   ||   User Password ";
    cout << "\n\t\t\t\t      ____________________________________________________\n";
    for ( int i = 0; i<size; i++)
    {
        cout<< "\t\t\t\t         " << users[i].userName << "     ||     "  << users[i].userAddress << "       ||        " << users[i].userPassword<<endl;
        cout << "\n\t\t\t\t     _____________________________________________________\n";
    }

}  // end show all data users  method ;


void show_All_Data_Specializing()
{
    string nameFiles[3] = {"IT-Department.txt" , "IS-Department.txt" , "CS-Department.txt" };
    for (int i = 0; i<3; i++)
        read_Specialize_Data(nameFiles[i]);

    cout << "\n\n\t\t   Specializing Name ||   total Levels   ||   total Students  ||   total Males Students  ||   total Females Students ";
    cout << "\n\t\t   __________________________________________________________________________________________________________________\n";
    for(int i = 0; i<3; i++)
    {
        cout << "\t\t\t    " << syste[i].Specializing_Name << "\t     || \t  " << syste[i].total_Level_Specializing  <<  "      ||\t    " << syste[i].total_Students_In_Specializing  << "\t      ||\t   "  << syste[i].total_Males_Students_In_Specializing  << "\t         ||\t    " << syste[i].total_Females_Students_In_Specializing<<endl;
        cout << "\t\t   __________________________________________________________________________________________________________________\n";
    }

}  // end show all Data Specializing method


void Program_Interface(){
    cout<<"\n\n\n\n\n";
    cout<<"\n\t\t       |---------------------------------------|";
    cout<<"\n\t\t       |     WELCOME  TO  STUDENTS  SYSTEM      |";
    cout<<"\n\t\t       |_______________________________________|";
    cout<<"\n\t\t       |                                       |";
    cout<<"\n\t\t       |          SEIYUN    UNIVERSITY         |";
    cout<<"\n\t\t       |                                       |";
    cout<<"\n\t\t       |     COLLEGE  OF  APPLED  SCIENCES     |";
    cout<<"\n\t\t       |_______________________________________|";
    cout<<"\n\t\t       |                                       | ";
    cout<<"\n\t\t       |---------------------------------------|";
    cout<<"\n\n\n\n\t\t\t     "; system("PAUSE"); system("cls");

}   // end the Program_Interface method ;

void about_The_Program()
{
    cout<<"\n\n\n\n\n\t\t\t";
    cout<<"\n\t\t\t    This Program Made by: ";
    cout<<"\n\t\t\t==============================";
    char a[5][25]{{'A','w','a','d','h','  ','M','o','h','a','m','m','e','d','  ','B','i','n','  ','W','a','h','l','a','n'},{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'}};

    for(int i=0;i<5;i++)
    {
        cout<<"\n\t\t\t  ||";
        cout<<"\n\t\t\t";
        cout<<i+1<<"  ||";
        for(int j=0;j<25;j++)
        {
            cout<<a[i][j];
            Sleep(50);
        }
    }
    cout<<"\n\t\t\t";     system("PAUSE");      system("cls");
}  // end about the program method ;


bool login()
{
    char name[50];    int password;   bool isFound = false;

    login:
        ifs.open("system-Users.txt" , ios::in);
        cout<<"\n\n\n\n\n\n\n\t\t\t||=========================================== ";
        cout<<"\n\t\t\t||Enter User Name: ";        /*gets(name);*/   cin>>name;
        cout<<"\n\n\n\t\t\t||=========================================== ";
        cout<<"\n\t\t\t||Enter User Password: ";    cin>>password;

    while (!ifs.eof())
    {
        ifs>>emplooy.userName >> emplooy.userAddress >> emplooy.userPassword;
        if(name == emplooy.userName && password == emplooy.userPassword  )
        {
             isFound = true;      break;
        }

    }
    ifs.close();

    if (isFound == false)
    {
        cout<<"\n\t\t\t Invalid Input ,, Try again.\n\n";   cout<<"\n\t\t\t ";   system("PAUSE");  system("cls");  goto login;
    }

    return isFound;
}  // end login method ;




void openFile()   // this method not used in the program ;
{
    string  specializeName = get_Specializing_Name();
    ofs.close();
    read_Specialize_Data(specializeName);
    studentInfo students[ syste[counter].total_Students_In_Specializing ];
    int allSize = syste[counter].total_Students_In_Specializing;

    if (specializeName == "IT")
    {
        ifs.open("IT-Department.txt" , ios::in);   read_students_Data_From_File(students , allSize);   ofs.open("IT-Department.txt" , ios::trunc);
    }

    else if (specializeName == "IS")
    {
        ifs.open("IS-Department.txt" , ios::in);   read_students_Data_From_File(students , allSize);   ofs.open("IS-Department.txt" , ios::trunc);
    }

    else
    {
        ifs.open("CS-Department.txt" , ios::in);   read_students_Data_From_File(students , allSize);    ofs.open("CS-Department.txt" , ios::trunc);
    }

}  // end open File Method ;
