#include <iostream> //To use the fstream library, include both the standard <iostream> AND the <fstream> header file
#include <string>
#include <fstream> //A combination of ofstream and ifstream: creates, reads, and writes to files
#include <bits/stdc++.h>
#include <vector>
#include <sstream> //Reminder that the code has a whitespace problem. If its magically not working, probably because of this.
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
    cout << tablename << endl;
    for (string columnvalue : columns){
        cout << columnvalue << endl;  //remove this when done, used for logging
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

    for (int i=0; i < 28; i++){
        if (i == 6 || i == 13 || i == 20 || i == 27){
            cout << rows[i];
        }
        else{
            cout << rows[i] << ",";
        }

        if (i == 6 || i == 13 || i == 20 || i == 27)
           cout << endl;
    }
}

void Updatecommand(vector<string> Updatecommand){
    int customer_id;
    int email_index;
    string new_email;
                     //note customer_id and new email value is place holder right now
    customer_id = 3; //formula for every row's email index number is: (n*7)-1
    email_index = (customer_id * 7) - 1;

    //email updater
    new_email= "email333";
    rows[email_index] = new_email;




}

//void Deletecommand()




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

    //cout << values << endl;
    for (int i=0;i < rows.size();i++){
        cout << rows[i] << " " << i << endl;  //remove this when done, used for logging
    }
    //for (int i = 0;i < insertcommand.size();i++){
    //    cout << insertcommand[i] << " + ";
    //}

}

void commandlist(vector<string> commandwords){  //If the first command is CREATE, do createfunction,else if first command is INSERT,do insertfunction


    string firstword = commandwords[0]; //probably not used

    for (int i =0;i < commandwords.size();i++){
        if(commandwords[i].compare("CREATE") == 0){
            createcommand(commandwords);
        }
        if(commandwords[i].compare("DATABASES") == 0){
            //cout << commandwords[i] << endl;
            cout << "DO DATABASE FUNCTION" << endl;
            cout << tablename << endl;
        }
        if(commandwords[i].compare("TABLES")== 0){
            //cout << commandwords[i] << endl;
            cout << "DO TABLE FUNCTION" << endl;
        }
        if(commandwords[i].compare("INSERT")==0){
            insertcommand(commandwords);

        }
        if(commandwords[i].compare("SELECT") == 0){
            selectcommand(commandwords);

        }
        if(commandwords[i].compare("UPDATE") == 0){
            cout << "Do update function"<< endl;
            Updatecommand(commandwords);
        }
        if(commandwords[i].compare("DELETE") == 0){
            cout << "Do delete function"<< endl;
        }
    }

}
int main(){

string command;
string MyText;
vector<string> commands;
ifstream MyReadFile("fileinput1.mdb");



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









