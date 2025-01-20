#include <iostream> //To use the fstream library, include both the standard <iostream> AND the <fstream> header file
#include <string>
#include <fstream> //A combination of ofstream and ifstream: creates, reads, and writes to files
#include <bits/stdc++.h>
#include <vector>
#include <sstream> //Reminder that the code has a whitespace problem. If its magically not working, probably because of this.
#include <windows.h>
#include <streambuf>

using namespace std;
//sigma sigma on the wall whos the skibidiest of them all
string tablename; //This will have the customer table
vector<string> columns;
vector<string> rows;
string removeQuotes(string& str); //function prototype
ofstream outFile;

string sanitize(const string& str) {  //This is used to make sure every string in the input file is printable because of strange error by .mdb file,just dont disturb this.
    string cleanStr;
    for (char c : str) {
        if (isprint(c)) { // Check if character is printable
            cleanStr += c;
        }
    }
    return cleanStr;
}
void createcommand(vector<string> createcommand){ //From CREATE TABLE customer(customer_id INT,customer_name TEXT..), This function is to Get its table name(customer) and store the customer_id,customer_name.. in vector columns from line 10.


    if(createcommand[1].find(".txt") != string::npos ){
        
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

    string filename = "customerData.txt"; //creating the text file

    ofstream outFile(filename, ios::out); //opening the file
    if (!outFile.is_open()){
        cerr << "Error: Could not create file " << filename << endl;
        return ;
    }

    outFile << tablename << endl << endl;


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
    outFile << endl;

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

    cout << "SAVING" << endl; 

    outFile.flush();

    outFile.close(); //close the file
    return ;
}

void Updatecommand(vector<string> Updatecommand){

    size_t equal_pos1;             //uses size_t data
    size_t equal_pos2;             //excessive variables :/
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
    string new_val;                 //Note: formula for every row's email index number is: (n*7)-1

    WHERE_index = -1;
    SET_index = -1;
    comparer_1 = "WHERE";
    comparer_2 = "SET";




    //find customer_id in WHERE and new_val in SET
    for(int i = 0; i < Updatecommand.size(); i++){

        if(Updatecommand[i] == comparer_1){

            WHERE_index = i+1;
            id_location = Updatecommand[WHERE_index];
            equal_pos1 = id_location .find("=");                      //Finds = sign
            extracted_id = (id_location .substr(equal_pos1 + 1));     //finds the int number
            customer_id = stoi(extracted_id);
            break;
        }
        if(Updatecommand[i] == comparer_2 ){                           //ensure WHERE is found first before running SET
            SET_index = i+1;                        //finds keyword after the command SET e.g "customer_email=email333"
            update_location = Updatecommand[SET_index];
            equal_pos2 = update_location.find("=");
            column_name = (update_location.substr(0 , equal_pos2)); //get the string of column_name before the "=" sign
            new_val = (update_location.substr(equal_pos2 + 1)); //need to remove quotation marks
            new_val = removeQuotes(new_val);
           
        }
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

    size_t equal_pos; //uses size_t data
    string extracted_id;
    string del_location;
    string comparer;
    int WHERE_index;
    int customer_id;
    int customer_index;
    int start_element;
    int vector_bound;


    comparer = "WHERE"; //finds the WHERE command in vector of strings in the DEL command line
    WHERE_index = -1; //base value of WHEERE, also indicates error
    for(int i =0 ; i < Deletecommand.size() ; i++){


        if(Deletecommand[i] == comparer){
            WHERE_index = i+1; //assumes the index after DELETE is where customer_id is
            del_location = Deletecommand[WHERE_index];
            equal_pos = del_location.find("customer_id=");         //find customer_id=
            extracted_id = (del_location.substr(equal_pos+12));     //finds the int number

            break;
        }

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



void insertcommand(vector<string> insertcommand){ //INSERT INTO customer(customer_id,customer_name) VALUES (1, 'namel')

    string values = insertcommand.back();
    values.erase(values.find("("),1);
    values.erase(values.find(")"),1);
    // Temporary string to store each token
    std::string token;

    // Use a stringstream for parsing
    std::stringstream ss(values);
    while (std::getline(ss, token, ',')) {
        // Remove single quotes if present
        if (token.front() == '\'') {
            token = token.substr(1, token.size() - 2);
        }
        rows.push_back(token);
    }

}

void databasecommand(vector<string> databasecommand){
    const char* relativePath = "fileinput2.mdb"; // Replace with your file name
    char fullPath[MAX_PATH];
    GetFullPathName(relativePath, MAX_PATH, fullPath, NULL);
    cout << fullPath << endl;
}

void tablecommand(vector<string> tablecommand){
    string tableName = "customer";
    cout << tableName << endl;
}

void commandlist(vector<string> commandwords){  //If the first command is CREATE, do createfunction,else if first command is INSERT,do insertfunction


    string firstword = commandwords[0]; //probably not used

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
        if(commandwords[i].compare("UPDATE") == 0){ //introduce error catching in future iterations
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
ifstream MyReadFile("fileinput2.mdb");


while (getline (MyReadFile, MyText,';')) {
  // Output the text from the file
  //cout << MyText;
  MyText = sanitize(MyText);
  commands.push_back(MyText);
}
for (int i =0;i < commands.size();i++){
    //THIS IS TO BREAK COMMAND DOWN LINE BY LINE
    cout << ">" << commands[i] << endl;
    string sentences = commands[i]; //im not sure if you need to stringify it so it wont break
    stringstream stream(sentences); //change sentences to a stream object so getline can work
    vector<string> words;
    string s; //temporary string storage
    while (getline (stream,s,' ')) {
        if(!s.empty()){
                words.push_back(s); //THIS IS TO BREAK EACH LINE INTO WORD BY WORD,words is an array now
        }

    }
    commandlist(words); //execute the commandlist function with words = ['CREATE','example.TXT']

}




}






