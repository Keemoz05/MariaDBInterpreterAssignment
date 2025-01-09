#include <iostream> //To use the fstream library, include both the standard <iostream> AND the <fstream> header file
#include <string>
#include <fstream> //A combination of ofstream and ifstream: creates, reads, and writes to files
#include <bits/stdc++.h>
#include <vector>
#include <sstream> //Reminder that the code has a whitespace problem. If its magically not working, probably because of this.
#include <windows.h>

using namespace std;
//sigma sigma on the wall whos the skibidiest of them all
string tablename; //This will have the customer table
vector<string> columns;
vector<string> rows;

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
        cout << "Create TXT FILE!" << endl;
    }
    else{
        cout << "Table Created!" << endl;
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
    for (int i=0; i < columns.size(); i++){
        if (i == 6){
            cout << columns[i];
        }
        else{
            cout << columns[i] << ",";
        }

    }
    cout << endl;

    for (int i=0; i < rows.size(); i++){
        if (i == 6 || i == 13 || i == 20 || i == 27){
            cout << rows[i];
        }
        else{
            cout << rows[i] << ",";
        }

        if (i == 6 || i == 13 || i == 20 || i == 27) //insert new lines
           cout << endl;
    }
}

void Updatecommand(vector<string> Updatecommand){
    int customer_id;
    int email_index;
    string new_email;
                            //note customer_id and new email value is place holder right now
                            //formula for every row's email index number is: (n*7)-1
    customer_id = 3;
    email_index = (customer_id * 7) - 1;

    //email updater
    new_email= "email333";
    rows[email_index] = new_email;
    for (string test : Updatecommand){
        cout << test << endl;
    }




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
    for(int i =0 ; i < Deletecommand.size() ; i++){


        if(Deletecommand[i] == comparer){
            WHERE_index = i;
            cout << WHERE_index << endl;
            break;


        }

    }

    //for(string commands : Deletecommand){ //goes through each strings in the line that has DELETE (ignore for now)
    WHERE_index = WHERE_index + 1;              //assumes the index after DELETE is where customer_id is
    del_location = Deletecommand[WHERE_index];
    cout << del_location << endl;
    equal_pos = del_location.find("customer_id=");         //find customer_id=
    extracted_id = (del_location.substr(equal_pos+12));     //finds the int number


    //}
    customer_id = stoi(extracted_id); //converts str to int for customer_id


    customer_index = (customer_id * 7); //last element to delete
    start_element = customer_index - 7;

    cout << "Start element is "<< customer_index << endl;

    vector_bound = rows.size(); //check if vector range has been exceeded or not

    cout << "True vector bound is " << vector_bound << endl;

    //if (customer_index == vector_bound){
        //customer_index = customer_index - 1; //if vector bound exceed by only 1 (e.g the last row), make sures the vector range is not exceeded
        //cout << "customer index is " << customer_index<<endl;
    //}

    //else {
        //cout << "The vector bound has been exceeded, program will terminate from this point." << endl;
        //exit(0);
    //}

                                                                                    //issues
                                                                                    //1. commas need to be removed
                                                                                    //2. yet to find reason why fourth line cannot be removed
                                                                                    //3. check for invalid customer_

    rows.erase(rows.begin() + start_element, rows.begin() + customer_index);




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


            cout << "Do update function"<< endl;
            Updatecommand(commandwords);
        }



        if(commandwords[i].compare("DELETE") == 0){


            cout << "Do delete function"<< endl;
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






