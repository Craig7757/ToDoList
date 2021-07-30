#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iterator>

//Craig's ToDoList
using namespace std;

//this function returns the current date mm/dd/yyyy
string setCurrentDate(){

    //gets current time
    time_t current = time(0);

    tm *now = localtime(&current);

    //this is for converting the date int values to a string value
    stringstream convert;

    string date = "";

    string month;
    convert << (now->tm_mon + 1);
    convert >> month;
    date += month + '/';
    convert.clear();

    string day;
    convert << (now->tm_mday);
    convert >> day;
    date += day + '/';
    convert.clear();

    string year;
    convert << (now->tm_year + 1900);
    convert >> year;
    date += year;
    convert.clear();

    return(date);
}//end CurrentDate


//The "To-Do" task
class Task{

private:

    //3 categories work, school, extra stuff to do
    string category = "";

    //Name of the task
    string TaskName = "";

    //Will be used to assign which list this task is moved too
    bool DONE = false;

    //The "why/how" of the task
    string description = "";

    //Creation date/time
    string created = "";

    //for the deadline
    string due = "";

    //finished time
    string finished = "";

public:

    //Task Class
    //can easily be refactored to support the creation of objects

    Task(){

        setDone("");
        setDateCreated("");
        setCategory("");
        setTaskName("");
        setDescription("");
        setDateDue("");

    }

    //this Task is used when reading-in items off the list for editing
    Task(string cat, string name, string desc, string due, string date, string done){

        setDone(done);
        setDateCreated(date);
        setCategory(cat);
        setTaskName(name);
        setDescription(desc);
        setDateDue(due);


    };

////////////////////////
//Getters & Setters:
////////////////////////

//This sets the default DONE boolean to false because
//the task wouldn't be on the list if it was finished
    void setDone(string done){

        if(done != ""){

            DONE = true;

        }else{

             DONE = false;
        }
    }

    bool getDone(){
        return DONE;
    }

    void setDateCreated(string date){

        if(date != ""){

            created = date;

        }else{

            created = setCurrentDate();
        }
    }

    string getDateCreated(){
        return created;
    }

    void setDateDue(string date){

        if(date != ""){

            due = date;

        }else{

            //I can revisit this function to handle more dynamic date input and
            //convert it to the formatted input using try-catch statements
            cout << "\nEnter the date this is due (mm/dd/yyyy):\n";
            cin >> due;

        }
    }

    string getDateDue(){
        return due;
    }

    void setCategory(string cat){

        if(cat != ""){

            category = cat;

        }else{


            int choice = 0;
            string group = " ";

            cout << "\nWhich category does this fall under? (1)[Work],(2)[School],(3)[Extra]?\n";
            cin >> choice;

            //choice filter
            if(choice == 1){
                group = "Work";
            }
            else if(choice == 2){
                group = "School";
            }
            else if(choice == 3){
                group = "Extra";
            }

            cout << "\n\"" << group << "\" is the preferred category? \n(1) Yes or (2) No\n";
            //recycling the choice variable to verify the category
            cin >> choice;

            //this creates a recursive function and recalls the setCategory function if
            //the user chooses a different category
            if(choice != 1){
                setCategory("");
            }

            category = group;

        }
    }//end setCategory

    string getCategory(){
        return category;
    }

    void setTaskName(string Name){

        if(Name != ""){

            TaskName = Name;

        }else{


            string name = "";

            for(int i = 0; i != 1;){

            cout << endl << "Please enter the Task's name: \n";
            fflush(stdin);
            getline(cin, name);

            cout << endl << "Is " << name << " is the preferred name?\n(1) Yes or (2) No\n";
            cin >> i;

            }

        TaskName = name;

        }
    }

    string getTaskName(){

        return TaskName;
    }

    void setDescription(string desc){

        if(desc != ""){

            description = desc;

        }else{

            string describe = "";

            cout << "\nPlease enter the Task's description: \n";

            fflush(stdin);
            getline(cin, describe);

            description = describe;

        }
    }

    string getDescription(){

        return description;
    }

};//End Of Task class

//this formats the strings for file input
//if the temp file needs next-line statements they could be added here
//isolates the last part of a task then add a '\n' to place the
//next task on the next line; pointers can be used to shift the char array
string FormatIn(string in){

    string  out;
    char str[in.size() + 1];

    strcpy(str, in.c_str());

    int i = 0;
    while(str[i]){
            if(str[i] == ' '){
                str[i] = '`';
               }
            i++;
        }
        out = str;
        out += "\n";

        return out;

}//end FormatIn

//formats the vector data for user-friendly reading
void FormatOut(string in){

    string  out;
    char str[in.size() + 1];

    strcpy(str, in.c_str());

    int i = 0;
    while(str[i]){
            if(str[i] == '`'){
                str[i] = ' ';
               }
            i++;
        }

    //this prints the formatted content to console
    i = 0;
    while(str[i]){

            cout << str[i];
            i++;
        }

    cout << '|';

}//end FormatOut

//this formats the string for a vector
string FormatForVector(string in){

    string  out;
    char str[in.size() + 1];

    strcpy(str, in.c_str());

    int i = 0;
    while(str[i]){
            if(str[i] == '|'){
                str[i] = ' ';
               }
            i++;
        }
        out = str;
        out += "\n";

        return out;

}//end FormatForVector

string FormatFromVector(string in){

    string  out;
    char str[in.size() + 1];

    strcpy(str, in.c_str());

    //this cycles through the string and replaces the endl statements with '|'
    int i = 0;
    while(str[i]){
            if(str[i] == '\n'){
                str[i] = '|';
            }

            i++;
        }
        out = str;
        return out;

}//end FormatFromVector

//this function cycles through and prints out the list to console
void ReadList(vector<vector<string>> ToOutput, int choice){

    if(choice == 1){

        //this should print the lines within the vector
        for(int i = 0; i != ToOutput.size(); i++){
                cout << endl << '|';
                for(int j = 0; j != ToOutput[i].size(); j++){

                        //call to output the individual line
                        FormatOut(ToOutput[i][j]);
                }
                cout << endl;
        }
    }
    else if(choice == 2){

            //this should print the lines within the vector
            for(int i = 0; i != ToOutput.size(); i++){
                cout << endl << " (" << i << ") " << '|';
                for(int j = 0; j != ToOutput[i].size(); j++){

                        //call to output the individual line
                        FormatOut(ToOutput[i][j]);
                }
                cout << endl;

            }//end nested loops
        }//end if else 2
}//end ReadList

//this function cycles through and prints out a selected task to console
int ReadTask(vector<string> ToOutput, int mode){

//modes(in descending order)
//mode1 prints out the numbered sections of a task
//mode2 returns 1 if a task is found to be "Done"
//mode3 returns true if a task is found to not  be "Not`Done"

    //mode1
    if(mode == 3){

            //this should print the items within the vector
                for(int j = 0; j != ToOutput.size(); j++){
                        cout << endl << " (" << j << ") " << '|';
                        //call to output the individual line
                        FormatOut(ToOutput[j]);
                }
                cout << endl;
    //mode2
    }else if(mode == 1){

        //this should print the items within the vector
        for(int j = 0; j != ToOutput.size(); j++){
                string check = FormatFromVector(ToOutput[j]);
                if(check == "Done"){

                    return 1;
                }//end else-if statement
        }//end Done for-loop

    //mode3
    }else if(mode == 2){

        //this should print the items within the vector
        for(int j = 0; j != ToOutput.size(); j++){
                string check = FormatFromVector(ToOutput[j]);
                if(check == "Not`Done"){

                    return 1;
                }
        }//end Not`Done for-loop
    }//end else-if statements

    return 0;

}//end ReadList

//this function will chop up the line that has been read-in
//so that we can create a vector of strings
vector<string> LineSegments(string row){

    //vector of strings to be returned
    vector <string> segments;

    //string to be added to the vector of strings
    string segment = "";

    //format the string to be vector friendly
    row = FormatForVector(row);

    istringstream iss(row);

    //this reads the row into the vector of strings
    while(iss >> segment){
        segments.push_back(segment);

    }

    //return the vector of strings
    return segments;

}// end LineSegments

//this opens a file, reads the file into the vector, then closes the file
vector<vector<string>> FileReadIn(string file){

            fstream ToRead;
            ToRead.open(file);
            ToRead.is_open();

            //this will read out the current Task-list onto a vector
            string line = "";
            vector<vector<string>>ToDoList{};

            //if the archive is open
            if(ToRead.is_open()){
                    //creation of a vector of strings
                    vector<string> row;
                while(getline(ToRead, line) || line == ""){

                    //for an empty ToDo list
                    if(line == ""){
                        line = "\n";
                    }
                    else if(line != "" || line != "\n"){

                            //this reads-in the line and formats it
                            stringstream ss(FormatIn(line));

                            //assigns the line to a string value
                            string segments = ss.str();

                            //this adds the vector of strings to the vector of vectors
                            ToDoList.push_back(LineSegments(segments));

                    }//end else-if
                }//end while
            }//end if

    ToRead.close();

    return ToDoList;

}//end FileReadInFunction

//this opens the file, formats the vector, writes the vector to
//the file and closes the file
void FileWriteIn(vector<vector<string>> ToDoList, string ThisFile){

    //place data into the file
    fstream WriteIn;
    //this creates a flag that wipes the file before writing to it
    WriteIn.open(ThisFile, ios::out | ios::trunc);
    WriteIn.is_open();

    //format the list
    for(int i = 0; i != ToDoList.size(); i++){
            for(int j = 0; j != ToDoList[i].size(); j++){

                        ToDoList[i][j] = FormatIn(ToDoList[i][j]);

                    }
            }

    //this should format the lines to be written into the file
    for(int i = 0; i != ToDoList.size(); i++){

            WriteIn << "|";
            for(int j = 0; j != ToDoList[i].size(); j++){

                WriteIn << FormatFromVector(ToDoList[i][j]);

            }

            WriteIn << endl;
    }//end for-loop

    WriteIn.close();

}//end WriteIn function

//this clears the file before writing into it
void SaveFile(vector<vector<string>>ToDoList, string ArchiveFile){

    //place data into the file
    fstream SaveFile;
    //this creates a flag that wipes the file before writing to it
    SaveFile.open(ArchiveFile, ios::out | ios::trunc);
    SaveFile.is_open();

    //format the list
    for(int i = 0; i != ToDoList.size(); i++){
            for(int j = 0; j != ToDoList[i].size(); j++){

                        ToDoList[i][j] = FormatIn(ToDoList[i][j]);

                    }
            }

    //this should format the lines to be written into the file
    for(int i = 0; i != ToDoList.size(); i++){

            SaveFile << "|";
            for(int j = 0; j != ToDoList[i].size(); j++){

                //read the task into the file
                SaveFile << FormatFromVector(ToDoList[i][j]);

            }

            //this begins the text task on the next line
            SaveFile << endl;
        }

    //close file
    SaveFile.close();

}//end SaveFile

//this closes the program
void CloseProgram(){

    //add automatic console window closing (timed so that the message below is viewable)
    cout << "\nHave a great day!!!." << endl;

    std::this_thread::sleep_for(std::chrono:: seconds(3));

    exit(0);
}//end CloseProgram

//This function adds to the ToDo list
void AddTask(vector<vector<string>>archive,string ArchiveFile,string TempFile){

    //clone the overall vector of vectors
    vector<vector<string>> ArchiveList = archive;

    //Encapsulated adding a new task within the do-while loop for verification
    int i = 0;
    while(i == 0){

        string line;
        string piece = "";

        //individual vector containing a single task
        vector<string> item;

        //create Task-object to be added to the ToDO list
        Task ToAdd;

        //gathering the different elements of the Task

        piece = ToAdd.getCategory();
        item.push_back(piece);

        piece = ToAdd.getTaskName();
        item.push_back(piece);

        piece = ToAdd.getDescription();
        item.push_back(piece);

        piece = ToAdd.getDateCreated();
        item.push_back(piece);

        piece = ToAdd.getDateDue();
        item.push_back(piece);

        if(ToAdd.getDone() == false){

            piece = "Not Done";
            item.push_back(piece);
        }

        //read-out task for the user to verify
        cout << endl << "Task:" << endl;
        for(int i = 0; i != item.size(); i++){

            cout <<"|" << item[i];

        }
        cout << "|" << endl;

        cout << line;
        cout << "\nIs this task ready to be added?\n1 for yes, any other number for no.\n";
        cin >> i;

        if(i == 1){

             ArchiveList.push_back(item);

        }

    }//end while loop

    FileWriteIn(ArchiveList,TempFile);
    SaveFile(FileReadIn(TempFile),ArchiveFile);

}//end AddTask

void UpdateTask(vector<vector<string>>archive,string ArchiveFile,string TempFile,int stop, int scan){

    //clone the overall vector of vectors
    vector<vector<string>> ArchiveList = archive;

        //Encapsulated adding a new task within the do-while loop for verification
        int i = 0;
        int check = 2;

        while(i != -1){

        int choice = 0;
        int TaskNumber;

        //individual vector containing a single task
        vector<string> task;

        if(scan == -1){

        //read the numbered tasks out for the user
        ReadList(FileReadIn(ArchiveFile),check);

        cout << endl << "Enter the number of the task you wish to choose:" << endl;
        cin >> TaskNumber;

        //read the selected task onto a string
        task = ArchiveList[TaskNumber];

        //read-out task for the user to verify
        cout << endl << "Task:" << endl;
        for(int i = 0; i != task.size(); i++){

           FormatOut(task[i]);
        }

        cout << "\n\nIs this the chosen task?\n(1) for yes, any other number for no.\n(0) to cancel\n";
        cin >> i;

        i = -i;

        }else{
            i = -1;
        }

        if(i == -1){

            if(stop == 2){

                    //erase the chosen task from the vector of string vectors
                    auto it = find(ArchiveList.begin(), ArchiveList.end(), task);

                    if(it != ArchiveList.end()){
                    ArchiveList.erase(it);
                    SaveFile(ArchiveList,TempFile);

                    cout << "\n\nItem deleted!!\n\n";
                    }


            }
            else if(stop == 3){

                //create a temp. task to pull the new info from
               Task ToUpdate = Task(task[0], task[1], task[2], task[3], task[4], task[5]);

                //read-out task segments for the user to pick
                cout << endl << "Options:" << endl;
                ReadTask(task, stop);

                cout << endl << "Enter the number of the section you wish to edit:" << endl;
                cin >> choice;

                if (choice == 0){

                    ToUpdate.setCategory("");

                    task.at(choice) = ToUpdate.getCategory();

                }else if(choice == 1){

                    ToUpdate.setTaskName("");

                    task.at(choice) = ToUpdate.getTaskName();

                }else if(choice == 2){

                    ToUpdate.setDescription("");

                    task.at(choice) = ToUpdate.getDescription();

                }else if(choice == 3){

                    ToUpdate.setDateCreated("");

                    //this may pose an issue if the creation date needs to be edited
                    //however, this program assumes the task creation will be correct when this function is called
                    task.at(choice) = ToUpdate.getDateCreated();

                }else if(choice == 4){

                    ToUpdate.setDateDue("");
                    task.at(choice) = ToUpdate.getDateDue();

                }else if(choice == 5){

                    cout << endl << "Has this task been completed?\n1 for yes, 2 for no\n";
                    int done = 2;
                    cin >> done;

                    if(done == 1){

                            ToUpdate.setDone(" ");

                    }else{

                        ToUpdate.setDone("");
                    }

                    if(ToUpdate.getDone() == true){

                        task[choice] = "Done";


                    }else{

                         task[choice] = "Not Done";
                    }
                }

                //add the updated task to the vector of vectors
                ArchiveList[TaskNumber] = task;
                //save the update
                SaveFile(ArchiveList,TempFile);

            }else if(stop == 4){

                    //erase the chosen task from the vector of string vectors
                    auto it = find(ArchiveList.begin(), ArchiveList.end(), task);

                    if(it != ArchiveList.end()){
                    ArchiveList.erase(it);
                    SaveFile(ArchiveList,TempFile);

                    cout << "\n\nItem deleted!!\n\n";
                    }
            }//end if-statements

        }else if(i == 0){

            break;
        }

        }//end while-loop
}//end UpdateTask

void ScanForDone(string Archive, string ATemp, string Done, string DTemp){

    vector<vector<string>> ToScan = FileReadIn(Archive);
    vector<vector<string>> Scanned = FileReadIn(Done);

    int scan = 0;

    //loop through the tasks
    for(int j = 0; j < ToScan.size(); j++){
            //scan is recycle here; set to 1 when needed
            scan = ReadTask(ToScan[j], 1);

            if(scan == 1){

                vector<string> task = ToScan[j];

                //this pushes the new done-task onto the vector of vector strings
                Scanned.push_back(task);
                auto it = find(ToScan.begin(), ToScan.end(), task);

                    if(it != ToScan.end()){
                    //this erases the task off of the archive vector of string vectors
                    ToScan.erase(it);
                    }

                // write the new vector of string vectors to the temp list
                //then save that list to the Done archive
                FileWriteIn(Scanned,DTemp);
                SaveFile(FileReadIn(DTemp),Done);

                // write the new vector of string vectors to the temp list
                //then save that list to the Archive
                FileWriteIn(ToScan,ATemp);
                SaveFile(FileReadIn(ATemp),Archive);

                }//end scan Archive
    }

    ToScan.clear();
    Scanned.clear();
    ToScan = FileReadIn(Done);
    Scanned = FileReadIn(Archive);

    //loop through the tasks
    for(int j = 0; j < ToScan.size(); j++){

            //scan is recycle here; set to 1 when needed
            scan = ReadTask(ToScan[j], 2);

            if(scan == 1){

                   vector<string> task = ToScan[j];

                //this pushes the new done-task onto the vector of vector strings
                Scanned.push_back(task);
                auto it = find(ToScan.begin(), ToScan.end(), task);

                    if(it != ToScan.end()){
                    //this erases the task off of the archive vector of string vectors
                    ToScan.erase(it);
                    }

                // write the new vector of string vectors to the temp list
                //then save that list to the Done archive
                FileWriteIn(Scanned,ATemp);
                SaveFile(FileReadIn(ATemp),Archive);

                // write the new vector of string vectors to the temp list
                //then save that list to the Archive
                FileWriteIn(ToScan,DTemp);
                SaveFile(FileReadIn(DTemp),Done);

            }//end scan if-statement
    }//end for-loops
}//end ScanForDoneFunction

void START(){

    cout << endl << "Welcome to the ToDoList!!!\n";

    string ArchiveFile = "ToDoList.txt";
    string ATempFile = "ToDoRead.txt";

    string DoneFile = "DoneList.txt";
    string DTempFile = "DoneRead.txt";

    //this iterates user options until the user chooses to end program usage
    for(int stop = 1; stop != 0;){


            //this prints the file's contents to the console
            ReadList(FileReadIn(ArchiveFile), stop);

            cout << "\n\nPlease enter a 1 to add a task to the list." << endl;
            cout << "Please enter a 2 to delete a task from the list." << endl;
            cout << "Please enter a 3 to edit a task on the list." << endl;
            cout << "Please enter a 4 to view the finished tasks." << endl;
            cout << "Enter 0 exit." << endl;
            cin >> stop;

            if(stop == 1){

                //this passes the vector of string vectors to the AddList function for processing
                AddTask(FileReadIn(ArchiveFile), ArchiveFile, ATempFile);

            }
            else if(stop == 2){

                    //call the function to display and remove the task(s)
                    UpdateTask(FileReadIn(ArchiveFile), ArchiveFile, ATempFile, stop, -1);

                    //automatically read the new list from the temp file and
                    //save it the archive
                    SaveFile(FileReadIn(ATempFile), ArchiveFile);
                    stop = 1;
            }
            else if(stop == 3){

                    //call the function to display and remove the task(s)
                    UpdateTask(FileReadIn(ArchiveFile), ArchiveFile, ATempFile, stop, -1);

                    //automatically read the new list from the temp file and
                    //save it the archive
                    SaveFile(FileReadIn(ATempFile), ArchiveFile);
                    stop = 1;

            }else if(stop == 4){


                    cout << endl << "Done List:\n";
                    //this prints the file's contents to the console
                    ReadList(FileReadIn(DoneFile), 1);

                    cout << endl << "Please enter a 1 to return to the ToDo List." << endl;
                    cout << "Please enter a 2 to delete a task from the list." << endl;
                    cout << "Please enter a 3 to edit a task on the list." << endl;
                    cout << "Enter 0 exit." << endl;
                    cin >> stop;

                    if(stop == 2){

                    //call the function to display and remove the task(s)
                    UpdateTask(FileReadIn(DoneFile), DoneFile, DTempFile, stop, -1);

                    //automatically read the new list from the temp file and
                    //save it the archive
                    SaveFile(FileReadIn(DTempFile), DoneFile);
                    stop = 1;

                    }
                    else if(stop == 3){

                            //call the function to display and remove the task(s)
                            UpdateTask(FileReadIn(DoneFile), DoneFile, DTempFile, stop, -1);

                            //automatically read the new list from the temp file and
                            //save it the archive
                            SaveFile(FileReadIn(DTempFile), DoneFile);
                            stop = 1;

                    }

                    //stop = 1;
            }//after viewing the DoneList the program exits automatically (un-comment the above code to display and loop through the main menu again)

            ScanForDone(ArchiveFile, ATempFile, DoneFile, DTempFile);

    }

///////////////////////////////////////////////////
// look into adding a timeout if list is left open
///////////////////////////////////////////////////

    CloseProgram();

}//end Start



int main()
{

    START();

    return 0;
}
