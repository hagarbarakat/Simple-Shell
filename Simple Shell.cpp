#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <string.h>
#include <fstream>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#define And "&"
using namespace std;
fstream log;
string input="";
string lastChar= "";
std:: vector <std::string>token;
string firstWord="";
//function to read input
bool readInput()
{
    printf("Shell -> ");
    getline(cin,input);
    if(!input.empty())
    {
        return true;
    }
    else
    {
        return false;
    }
}
//splitting input and checking last character if it's &
void parse()
{
    std::istringstream iss(input);
    std::vector<std::string> tokens(std::istream_iterator <std::string> {iss},std::istream_iterator <std::string>());
    for(auto& s:tokens)
    {
        lastChar=s;
    }
    firstWord= tokens.front();
    token=tokens;
   }
//executing commands
bool commands()
{    int choice=0;
    string shellCommands[4]= {"exit","cd","help","hello"};
    string username;
    for(int i=0; i<4; i++)
    {
        if(firstWord==shellCommands[i])
        {
            choice=i+1;
            break;
        }
    }
//4 choices
    switch(choice)
    {
    case 1:
    {
        exit(0);
    }
    case 2:
    {
        chdir(token.at(1).c_str());
        return true;
    }
    case 3:
    {
        cout <<"\n***WELCOME TO Simple SHELL HELP***"
             "\n-Use the shell at your own risk..."
             "\nList of Commands supported:"
             "\n>cd"
             "\n>ls"
             "\n>exit"
             "\n>all other general commands available in UNIX shell"<<endl;
        return true;
    }
    case 4:
    {
        username= getenv("USER");
        cout<< "\nHello "<<username<<".\nMind that this is not a place to play around."<<"\n Use help to know more.\n"<< endl;
        return true;
    }
    default:
    {
        return false;
    }
    }
    return false;
}
void signalHandler(int sigNum)
{


    log<< "Child terminated" <<endl;
    cout<< "Child terminated"<<endl;
//signal(SIGCLD,signalHandler);

}
bool execute()
{


    pid_t pid;
    bool found=false;
    if(lastChar==And)
    {        found=true;
    }
    pid= fork();
    if(pid<0)
    {
        perror("Error pid<0");
    }
    else if (pid>=0)

    {

signal(SIGCLD,signalHandler);
if(pid>0){
//parent
  if(!found){

waitpid(pid,NULL,0);

        }

}
else{
//child
        std::vector<char*> argc;
        for (auto const& a : token)
        {
        //check if it isn't & to function corecctly
        if(a!="&"){
            argc.push_back(const_cast<char*>(a.c_str()));
              }
        }
        argc.push_back(nullptr);
        if(execvp(token.at(0).c_str(),argc.data())<0)
        {
            perror("execvp error");
            cout<< "Error."<<endl;
            return false;
        }

    }

    }
    return true;
}




int main()
{
    cout << "\t \t \t Simple Shell\n" << endl;
    while(true)
    {
    //open log file
        log.open("log.txt",log.out|log.app);

        if(readInput())
        {
            parse();
        }
        if(!commands())
        {            if(execute())
            {
                cout<<"executed successfully"<<endl;
            }
        }
        log.close();

    }
    return 0;
}


