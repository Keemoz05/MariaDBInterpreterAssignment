#include <iostream> //To use the fstream library, include both the standard <iostream> AND the <fstream> header file
#include <string>
#include <fstream> //A combination of ofstream and ifstream: creates, reads, and writes to files
#include <bits/stdc++.h>
#include <vector>
#include <sstream>
using namespace std;

string tablename; //customer table
vector<string> columns;
vector<string> rows;

string sanitize(const string& str) {  //this is used for string comparison,just dont disturb la
    string cleanStr;
    for (char c : str) {
        if (isprint(c)) { // Check if character is printable
            cleanStr += c;
        }
    }
    return cleanStr;    // remove strange character caused by getline or something for compare string to work when program is run in cmd
}
void createcommand(vector<string> createcommand){ //CREATE TABLE customer(customer_id INT,customer_name TEXT,customer_city TEXT,customer_state TEXT,customer_country TEXT, customer_phone TEXT,customer_email TEXT)


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
        cout << columnvalue << endl;
    }

    }

}

void insertcommand(vector<string> insertcommand){

    for (int i = 0;i < insertcommand.size();i++){
        cout << insertcommand[i] << " + ";
    }

}

void commandlist(vector<string> commandwords){  //commandwords["CREATE",'fileoutput.txt')


    string firstword = commandwords[0]; //probably not used

    for (int i =0;i < commandwords.size();i++){
        if(commandwords[i].compare("CREATE") == 0){
        createcommand(commandwords);
    }
        if(commandwords[i].compare("DATABASES") == 0){
            //cout << commandwords[i] << endl;
            cout << "DO DATABASE FUNCTION" << endl;
        }
        if(commandwords[i].compare("TABLES")== 0){
            //cout << commandwords[i] << endl;
            cout << "DO TABLE FUNCTION" << endl;
        }
        if(commandwords[i].compare("INSERT")==0){
            insertcommand(commandwords);
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








