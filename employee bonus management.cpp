
//**********************************************************************
//*                                                                    *
//* This program receives a company's information, including it's      *
//* name, the bonus year, the number of employees, and the bonus       *
//* amount. A database of the company's employees bonus records is     *
//* then received and printed. The datbase is sorted and printed into  *
//* ascending order by year hired.                                     *
//*                                                                    *
//**********************************************************************

#include <iostream>
#include <new>
#include <cstdlib>
#include <cstring>
using namespace std;

//**********************************************************************
//*                         Symbolic Constants                         *
//**********************************************************************
#define COMPANY_ALLOC_ERR  1       // Unable to allocate memory for the
                                   // company information
#define COURSE_NAME        "Object-Oriented Programming and Design"
                                   // PCC assigned course name
#define COURSE_NUMBER      "CS246" // PCC assigned course number
#define EMPLOYEE_ALLOC_ERR 3       // Unable to allocate memory for the
                                   // database of employee bonus records
#define MAX_NAME_LENGTH    80      // Maximum valid name length
#define NAME_ALLOC_ERR     2       // Unable to allocate memory for the
                                   // company name
#define PROGRAM_NUMBER     6       // Teacher assigned program number

//**********************************************************************
//*                       Program Structures                           *
//**********************************************************************
// A company's information
struct company_info
{
   char  *p_company_name;      // Point to the company's name
   int   bonus_year,           // The year the bonus is given
         number_employees;     // The number of employees at the company
   float company_bonus_amount; // The bonus amount to be given
};
//**********************************************************************
//*                         Program Classes                            *
//**********************************************************************
// An employee's bonus records
class bonus_records
{
   int   employee_id,   // The employee's id number
         service_years, // The number of service years 
         years_hired;   // The year the employee was hired
   float bonus_amount;  // The employee's bonus amount to be received
public:
   // Destructor, delete an employee record
        ~bonus_records   () {cout << "\n\nDestructor executing ...";}

   // Set the data members
   void set_employee_id  (int e)  {employee_id = e;}
   void set_service_years(int s)  {service_years = s; }
   void set_years_hired  (int y)  {years_hired = y; }
   void set_bonus_amount (float b){bonus_amount = b;}

   // Get the data members
   int   get_employee_id  ()      {return employee_id;}
   int   get_service_years()      {return service_years;}
   int   get_years_hired  ()      {return years_hired; }
   float get_bonus_amount ()      {return bonus_amount;}
};

//**********************************************************************
//*                        Function Prototypes                         *
//**********************************************************************
void           print_heading();
   // Print the program heading
company_info*  get_company_information();
   // Get the company information
bonus_records* get_employees(company_info new_company_info);
   // Get the employee bonus record database
void           print_database(bonus_records *p_employee_start,
                              int number_employees, const char *p_sort_order);
   // Print the database of company employee bonus records
void           sort_employees(bonus_records *p_employee_start,
                              int number_employees);
   // Sort the database by years hired in ascending order
void           fatal_error(int error_number, const char *fname, 
                           const char *p_memory_name);
   // Print the fatal error message and exit

//**********************************************************************
//*                           Main Function                            *
//**********************************************************************
int main()
{
   company_info   *p_company_info;  // Point to the company information
   bonus_records  *p_bonus_records; // Point to the employee bonus records
  
   // Print the program heading
   cout << "\n\n\n\n\n\n";
   print_heading();
   
   // Get and print company information
   p_company_info = get_company_information();
   cout << "\n\nCompany name:        "  << p_company_info->p_company_name;
   cout <<   "\nYear of the bonuses: "  << p_company_info->bonus_year;
   cout <<   "\nNumber of employees: "  << p_company_info->number_employees;
   cout <<   "\nBonus per year:      $" << p_company_info->company_bonus_amount;

   // Get and print the employee database
   p_bonus_records = get_employees(*p_company_info);
   print_database(p_bonus_records, p_company_info->number_employees,
                  "IN UNSORTED ORDER");

   // Sort and print the employee database
   sort_employees(p_bonus_records, p_company_info->number_employees);
   print_database(p_bonus_records, p_company_info->number_employees,
                  "SORTED BY YEAR HIRED");

   // Free the dynamically allocated memory
   delete [] p_company_info->p_company_name;
   delete p_company_info;
   delete [] p_bonus_records;
 
   // Say goodbye and terminate the program
   cout << "\n\n\nThanks for processing employee bonuses today ;)";
   cout << "\n\n\n\n\n\n";
   return 0;
}

//**********************************************************************
//*                   Print the program's heading                      *
//**********************************************************************
void print_heading()
{
   cout << "\n"          << COURSE_NUMBER
        << " "           << COURSE_NAME
        << " - Program " << PROGRAM_NUMBER;
   cout << "\n========================================================";
   cout << "\nThis program asks for information about your company and";
   cout << "\nabout each employee. It then calculates the bonus amount";
   cout << "\nowed each employee based on the number of service years.";
   return;
}

//**********************************************************************
//*                    Get the company information                     *
//**********************************************************************
struct company_info* get_company_information()
{
   char         new_name[MAX_NAME_LENGTH+1]; // The company's name
   company_info *p_company = NULL;           // Point to the company information
   
   // Allocate memory for company information, abort if unavailable
   try
   {
     p_company = new company_info;
   }
   catch (bad_alloc xa)
   {
      fatal_error(COMPANY_ALLOC_ERR, "get_company_info()", "company information");
   }
   
   // Receieve the company name and allocate memory for the name
   cout << "\n\n\nEnter the name of your company here (no spaces): ";
   cin  >> new_name; 
   try
   {
      p_company->p_company_name = new char[strlen(new_name)+1];
   }
   catch (bad_alloc xa)
   {
      fatal_error(NAME_ALLOC_ERR, "get_company_info()", "company name");
   }
   strcpy_s(p_company->p_company_name, strlen(new_name) + 1, new_name);

   // Receive the number of employees in the company
   do
   {
      cout << "\nEnter your number of employees (1 or more): ";
      cin  >> p_company->number_employees; 
   
      if (p_company->number_employees < 1)
         cout << "     The number of employees must be 1 or more.";
   }
   while (p_company->number_employees < 1 );
   
   // Receive the year the bonus is given
   cout << "Enter the year in which the bonuses are given (YYYY): ";
   cin  >> p_company->bonus_year; 
   
   // Receive the bonus amount to be given
   cout << "Give the yearly bonus amount per employee (in dollars): ";
   cin  >> p_company->company_bonus_amount; 
   
   return p_company; 
}

//**********************************************************************
//*                       Get the employees                            *
//**********************************************************************
bonus_records* get_employees(company_info new_company_info)
{
   int           employee_id_counter = 1,  // Count the number of employee ids
                 service_years;            // The employees' service years
   bonus_records *p_employee_start = NULL, // Point to the start of the
                                           // employee database
                 *p_employees;             // Point to every employee
   
   // Allocate database of employee bonus records
   try
   {
      p_employee_start = new bonus_records[new_company_info.number_employees];
   }
   catch (bad_alloc xa)
   {
      fatal_error(EMPLOYEE_ALLOC_ERR, "get_employees()", "employee");
   }

   // Get the employee's years of service
   p_employees = p_employee_start;
   do
   {
      cout << "\n\n";
      do
      {
         cout << "Enter the number of service years of employee #" 
                                                       << employee_id_counter 
              << ".";
         cout <<     "\nEnter 0 (zero) if this employee does not exist: ";
         cin  >> service_years;
         
         if (service_years < 0)
         {
            cout <<   "   The service years must be 0 or greater.";
            cout << "\n   Please reenter the number of service years.";
         }
      }
      while (service_years < 0);
      
      // Build the employee records
      if(service_years > 0)
      { 
         p_employees->set_service_years(service_years);
         p_employees->set_employee_id  (employee_id_counter);
         p_employees->set_years_hired
                    (new_company_info.bonus_year - service_years);
         p_employees->set_bonus_amount
                    (service_years * new_company_info.company_bonus_amount);
         p_employees++;
      }
      employee_id_counter+=1;
   }
   while ((p_employees - p_employee_start) < new_company_info.number_employees);

   return p_employee_start;
}

//**********************************************************************
//*                   Print the employee database                      *
//**********************************************************************
void print_database(bonus_records *p_employee_start, int number_employees,
                    const char *p_sort_order)
{
   bonus_records *p_employees;   // Point to every employee
   
   cout <<"\n\nHere is the employee database, " << p_sort_order << ":";
   cout <<  "\n====================================================";
   cout <<  "\nEmployee Id   Service Years   Year Hired   Bonus Amt";
   cout <<  "\n-----------   -------------   ----------   ---------";

   for (p_employees = p_employee_start;
       (p_employees - p_employee_start) < number_employees; p_employees++)
   {
      cout <<"\n     "        << p_employees->get_employee_id  ()
           <<"              " << p_employees->get_service_years()
           <<"            "   << p_employees->get_years_hired  ()
           <<"        $"      << p_employees->get_bonus_amount ();
   }   
   return; 
}


//**********************************************************************
//*                     Sort the employee database                     *
//**********************************************************************
void sort_employees(bonus_records *p_employee_start, int number_employees)
{
   bonus_records *p_employees,     // Point to every employee
                 temp_employee;    // Temporary employee for the swap
   int           employee_counter; // Count the number of employees

   for (employee_counter = 1; employee_counter <= (number_employees - 1);
        employee_counter++)
      for (p_employees = p_employee_start; 
          (p_employees - p_employee_start) < (number_employees - 1);
          p_employees++)
      {
         if (p_employees->get_years_hired() > (p_employees+1)->get_years_hired())
         {
            temp_employee      = *p_employees;
            *p_employees       = *(p_employees + 1);
            *(p_employees + 1) = temp_employee;
         }
      }
   return; 
}

//**********************************************************************
//*               Print the fatal error message and exit               *
//**********************************************************************
void fatal_error(int error_number, const char *p_fname, 
                 const char *p_memory_name)
{
   cout << "\n\nError #"                            << error_number 
        << " occurred in "                          << p_fname ;
   cout <<   "\nUnable to allocate memory for the " << p_memory_name << ".";
   cout <<   "\nThe program is aborting.";
   exit (error_number);
}