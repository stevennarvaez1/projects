#include <iostream>
#include <stdbool.h>
#include <vector>
#include <string>

using namespace std;

struct task
{
   string task_name;
   bool   is_task_complete;
};

int number_of_tasks();
vector<task> get_tasks(int task_quantity);
void insert_task(vector<task>* user_tasks);
void show_tasks(vector<task> list_of_tasks);
void delete_task(vector<task>* user_tasks, int task_quantity);
void complete_task(vector<task>* user_tasks, int task_quantity);


int main()
{
   int num_task = 0;
   int menu_response;

   vector<task> my_tasks;
   
   cout << "\n      To Do List";
   
   
   cout << "\n\n         MENU"          << "\n 1. Create To-Do List" << "\n 2. Insert Task "
        << "\n 3. Delete Task"   << "\n 4. Mark Task as Complete"  << "\n 5. Show To-Do List" << "\n 6. Quit";
 
   
   do
   {
      cout << "\n\n   Select a choice: ";
      cin >> menu_response;

      switch (menu_response) {
      case 1: 
         num_task = number_of_tasks();
         my_tasks = get_tasks(num_task);
         break;
      case 2:
         insert_task(&my_tasks);
         show_tasks(my_tasks);
         num_task+=1;
         break;
      case 3: 
         delete_task(&my_tasks, num_task);
         if(!my_tasks.empty())
            show_tasks(my_tasks);
         break;
      case 4:
         complete_task(&my_tasks, num_task);
         show_tasks(my_tasks);
         break;
      case 5:
         show_tasks(my_tasks);
         break;

      }
      if (menu_response <= 0 || menu_response > 6)
         cout << "Please enter a valid menu choice.";
   }
   while(menu_response != 6);
   

  

   return 0;
}


int number_of_tasks()
{
   int task_quantity;
   
   cout << "\nPlease Enter The Number of Tasks: ";
   do{

   cin >> task_quantity;
   
   if (task_quantity <= 0)
      cout << "\nPlease enter a valid number of tasks.(1 or more): ";
   }
   while (task_quantity <= 0);

   return task_quantity;
}

vector<task> get_tasks(int task_quantity)
{
   int    task_counter;
   string name_task;
   vector<task> task_list;

   cin.ignore();

   cout << "\n Please enter your tasks: \n";
   for(task_counter = 0; task_counter < task_quantity; task_counter++)
   {
      getline(cin, name_task);
      task_list.push_back({name_task, false}); 
   }
   
   return task_list;
}

void insert_task(vector<task>* user_tasks)
{
   string user_task_name;

   cin.ignore();
   cout << "\n\n Enter the task to insert:\n";
   getline(cin, user_task_name);
   user_tasks->push_back({user_task_name, false});
   return;
}

void delete_task(vector<task>* user_tasks, int task_quantity)
{
   int task_number; 
 
   if (!user_tasks->empty())
   { 
   cout << "\nEnter the number of task you wish to delete: ";
   cin >> task_number;
   while (task_number > task_quantity)
   {
      cout << "\n Please enter a valid task number: ";
      cin >> task_number;
   }
   task_number-=1;
   user_tasks->erase(user_tasks->begin()+task_number);
   }
   else
      cout << "\nThe To-Do List is empty!";
  return;
}
void show_tasks(vector<task> tasks)
{
   vector<task>::iterator task_iterator;
   int count_tasks = 1;

   cout << "\n Your Current To-Do List" 
        << "\n --------------------- ";
   for(task_iterator = tasks.begin(); task_iterator != tasks.end(); task_iterator++)
   {
      cout << "\n " << count_tasks << ". " << task_iterator->task_name;
      if (task_iterator->is_task_complete == true)
         cout << " (completed)";
      else
         cout << " (incomplete)";
      
      count_tasks++;
   }

   return;
}

void complete_task(vector<task>* user_tasks, int task_quantity)
{
   int task_number;

   cout << "\nEnter the number of task to mark as complete: ";
   cin >> task_number;
   while (task_number > task_quantity)
   {
      cout << "\n Please enter a valid task number.";
      cin >> task_number;
   }
   task_number -= 1;
   user_tasks->at(task_number).is_task_complete = true;

   return;
}
