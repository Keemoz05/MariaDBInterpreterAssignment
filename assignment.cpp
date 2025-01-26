//**************************************************************************************
//
//Program: assignment.cpp
//Course: CCP6114 Programming Fundamentals
//Lecture Class: TC1L
//Tutorial Class: TT2L
//Trimester: 2430
//Member_1: 242UC244DP | SYED HAQEEM | SYED.HAQEEM.SYED@student.mmu.edu.my | 017-4848002
//Member_2: 242UC244LR | CHAN CHUAN MENG | CHAN.CHUAN.MENG@student.mmu.edu.my | 012-5293192
//Member_3: 242UC244KE | MUHAMMAD FATHULLLAH | MUHAMMAD.FATHULLAH.MOHD@student.mmu.edu.my | 011-26020729
// **************************************************************************************
//Task distribution
//Member_1: Main, Create and Insert functions
//Member_2: Main, Update, Delete and remove quotes function
//Member_3: Main, Select, Database and Table name function
// **************************************************************************************





#include <iostream> //To use fstream library, include both the standard <iostream> AND the <fstream> header file
#include <string>
#include <fstream> 
#include <vector>
#include <sstream> //Reminder that the code has a whitespace problem. If its magically not working, probably because of this.
#include <windows.h> // for finding path
#include <cstdio> // for file renaming
using namespace std;

string filetoread = "fileinput1.mdb";

string tablename; //This will have the customer table
vector<string> columns;
vector<string> rows;
string removeQuotes(string& str); //function prototype
ofstream outFile("output.txt", ios::out);

string filename;

string sanitize(const string& str) {  //This is used to make sure every string in the input file is printable because of strange error by .mdb file,just dont disturb this.
    string cleanStr;
    for (char c : str) {
        if (isprint(c)) { // Check if character is printable
            cleanStr += c;
        }
    }
    return cleanStr;
}

void createcommand(vector<string> createcommand){ //createcommand = {CREATE,TABLE customer()...}


    if(createcommand[1].find(".txt") != string::npos ){
        filename = createcommand[1];
    }
    else{
        for (int i =2;i < createcommand.size();i++){
        //cout << createcommand[i] << " + ";
        //if ada bracket,remove it,separate it
        if (createcommand[i].find("(") != -1){
            tablename = createcommand[i].substr(0,createcommand[i].find("("));
            columns.push_back(createcommand[i].substr(createcommand[i].find("(")+1,createcommand[i].length()));
        }
        else if (createcommand[i].find(")") == -1){ //if no bracket, just push the table column inside vector<string> column
            columns.push_back(createcommand[i].substr(createcommand[i].find(",")+1,createcommand[i].length()));
        }
    }


    }

}

void selectcommand(vector<string> selectcommand){ //SELECT
    if (selectcommand[1] == ("COUNT(*)")){
        cout << rows.size() / columns.size()  << endl;
        outFile << rows.size() / columns.size()  << endl; //there is 7 columns inside customer. 
    }
    else{
    for (int i=0; i < columns.size(); i++){
        if (i == 6){
            cout << columns[i];
            outFile << columns[i]; //inputing the data in the file
        }
        else{
            cout << columns[i] << ",";
            outFile << columns[i] << ",";
        }
    }
    cout << endl;
    outFile << endl; // adds new line after listing all the columns

    for (int i=0; i < rows.size(); i++){
        if (i == 6 || i == 13 || i == 20 || i == 27){
            cout << rows[i];
            outFile << rows[i];
        }
        else{
            cout << rows[i] << ",";
            outFile << rows[i] << ",";
        }

        if (i == 6 || i == 13 || i == 20 || i == 27){ //insert new lines
           cout << endl;
           outFile << endl;
        }
    }
    }
}

void Updatecommand(vector<string> Updatecommand){

    int equal_pos1;          
    int equal_pos2;            
    int customer_id;
    int WHERE_index;
    int update_index;
    int SET_index;
    int col_index;
    int email_index;
    string id_location;
    string update_location;
    string extracted_id;
    string comparer_1;
    string comparer_2;
    string column_name;
    string new_val;                 //Note: formula for every row's customer info index number is: (n*7)-y, with y being the position in the column

    WHERE_index = -1;
    SET_index = -1;
    comparer_1 = "WHERE";
    comparer_2 = "SET";
    bool WHERE = false; //boolean variable for error checking
    bool SET = false;


    //find customer_id in WHERE and new_val in SET
    for(int i = 0; i < Updatecommand.size(); i++){

        if(Updatecommand[i] == comparer_1){
            WHERE = true;
            WHERE_index = i+1;
            id_location = Updatecommand[WHERE_index];
            equal_pos1 = id_location .find("=");                      //Finds '=' sign
            extracted_id = (id_location .substr(equal_pos1 + 1));     //finds the int number
            customer_id = stoi(extracted_id);
            break;
        }
        if(Updatecommand[i] == comparer_2 ){                          
            SET = true;
            SET_index = i+1;                        //finds keyword after the command SET e.g "customer_email=email333"
            update_location = Updatecommand[SET_index];
            equal_pos2 = update_location.find("=");
            column_name = (update_location.substr(0 , equal_pos2)); //get the string of column_name before the "=" sign
            new_val = (update_location.substr(equal_pos2 + 1)); //need to remove quotation marks
            new_val = removeQuotes(new_val);
           
        }
    }
    
    if(WHERE != true){  //error checking
        cout << "WHERE command for UPDATE command not found, please edit input file." << endl;
        exit(0);
    }

    if(SET != true){
        cout << "SET command for UPDATE command not found, please edit input file." << endl;
        exit(0);
    }
    
    //column_name comparer, if the input matches, assigns the corresponding column index number
    for(int i = 0; i < columns.size(); i++){

        if(columns[i] == column_name){

            col_index = i;
            update_index = ((customer_id*7) - 7) + col_index;

        }

    }

    //updater
    rows[update_index] = new_val;
}


void Deletecommand(vector<string> Deletecommand){

    int equal_pos; 
    string extracted_id;
    string del_location;
    string comparer;
    int WHERE_index;
    int customer_id;
    int customer_index;
    int start_element;
    int vector_bound;
    bool WHERE_id = false;

    comparer = "WHERE"; //finds the WHERE command in vector of strings in the DEL command line
    WHERE_index = -1; //base value of WHEERE, also indicates error
    for(int i =0 ; i < Deletecommand.size() ; i++){


        if(Deletecommand[i] == comparer){
            WHERE_id = true;
            WHERE_index = i+1; //assumes the index after DELETE is where customer_id is
            del_location = Deletecommand[WHERE_index];
            equal_pos = del_location.find("customer_id=");         //find customer_id=
            extracted_id = (del_location.substr(equal_pos+12));     //finds the int number

            break;
        }

    }
    
    if(WHERE_id != true){
        cout << "WHERE command for DELETE command not found, please edit input file." << endl;
        exit(0);
    }
    
    customer_id = stoi(extracted_id); //converts str to int for customer_id

    customer_index = (customer_id * 7); //last element to delete
    start_element = customer_index - 7;

    vector_bound = rows.size(); //check if vector range has been exceeded or not

    rows.erase(rows.begin() + start_element, rows.begin() + customer_index); //actual line that removes a row


}


string removeQuotes(string& str){ //for loop function used to remove quotation marks in user inputs, accept strings as arguments

    for( int i = 0; i < str.length();){

       if (str[i] == '\'' || str[i] == '"') {    //character after \ treated literally
            str.erase(i,1);                       //remove the character that has quotation marks
        }
        else{
            i++;
        }
    }
    return str;
}



void insertcommand(vector<string> insertcommand){ //insertcommand = {INSERT INTO}

    //this segment verifies the given input column to insert the values into
    bool isInputColumn = false;
    vector<string> inputcolumn;
    string columnstoinsert = insertcommand[2];
    columnstoinsert = columnstoinsert.substr(columnstoinsert.find("("),columnstoinsert.find(")"));
    columnstoinsert.erase(columnstoinsert.find("("),1);
    columnstoinsert.erase(columnstoinsert.find(")"),1);
    stringstream sss(columnstoinsert);
    string ww;
    while(getline(sss,ww,',')){
        inputcolumn.push_back(ww);
    }

    for (int i = 0;i < inputcolumn.size();i++){
        if(inputcolumn[i] == columns[i]){
            isInputColumn = true;
        }
        else{
            cout << "Error! Column input does not match size and name." << endl;
            outFile << "Error! Column input does not match size and name." << endl;
            isInputColumn = false;
            break;
        }
    }    
    
    //if all column input is correct, insert the values.
    if(isInputColumn == true){
    //values part
    string values = insertcommand.back(); //cheese method to only take the last string, (1,"name1")...
    values.erase(values.find("("),1);
    values.erase(values.find(")"),1);
    // Temporary string to store each token for getline to work
    string token;

    stringstream ss(values);
    while (getline(ss, token, ',')) {
        if (token.front() == '\'') {
            token = token.substr(1, token.size() - 2);
        }
        rows.push_back(token);
    }
    }
}

void databasecommand(vector<string> databasecommand){
    const char* relativePath = filetoread.c_str(); 
    char fullPath[MAX_PATH];
    GetFullPathName(relativePath, MAX_PATH, fullPath, NULL);
    cout << fullPath << endl;
    outFile << fullPath << endl;
}

void tablecommand(vector<string> tablecommand){
    cout << tablename << endl;
    outFile << tablename << endl;
}

void commandlist(vector<string> commandwords){  //If the first command is CREATE, do createfunction,else if first command is INSERT,do insertfunction


    for (int i =0;i < commandwords.size();i++){
        if(commandwords[i].compare("CREATE") == 0){
            createcommand(commandwords);
        }
        if(commandwords[i].compare("DATABASES") == 0){
            databasecommand(commandwords);
        }
        if(commandwords[i].compare("TABLES")== 0){
            tablecommand(commandwords);
        }
        if(commandwords[i].compare("INSERT")==0){
            insertcommand(commandwords);
        }
        if(commandwords[i].compare("SELECT") == 0){
            selectcommand(commandwords);

        }
        if(commandwords[i].compare("UPDATE") == 0){ 
            Updatecommand(commandwords);
        }
        if(commandwords[i].compare("DELETE") == 0){
            Deletecommand(commandwords);
        }
    }

}
int main(){
string command;
string MyText;
vector<string> commands;

//this section reads the given input file and saves each line separated by ';'  into the vector commands;
ifstream MyReadFile(filetoread); 
while (getline (MyReadFile, MyText,';')) {
  //cout << MyText;
  MyText = sanitize(MyText);
  commands.push_back(MyText);
}

MyReadFile.close();


for (int i =0;i < commands.size();i++){
    //THIS IS TO BREAK COMMAND DOWN LINE BY LINE
    cout << ">" << commands[i] << endl;
    outFile << ">" << commands[i] << endl;
    string sentences = commands[i];  //commands[0] = "CREATE fileoutput1.txt"
    stringstream stream(sentences); //change sentences to a stream object so getline can work
    vector<string> words;
    string s; //temporary string storage
    while (getline (stream,s,' ')) {
        if(!s.empty()){
                words.push_back(s); //THIS IS TO BREAK EACH LINE INTO WORD BY WORD and store it into vector words;
        }

    }
    commandlist(words); //execute the commandlist function with words = ['CREATE','example.TXT']

}

outFile.close();
remove(filename.c_str());
rename("output.txt",filename.c_str()); //c_str to change string filename to char const

}






