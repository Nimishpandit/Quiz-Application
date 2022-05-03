#include<fstream>
#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<cstdlib>
#include<ctime>
#include"quiz.h"
#include"conio2.h"
using namespace std;
void Admin::createAdmin(string userid,string password,string username)
{
    fstream fobj("admin.bin",ios::in|ios::binary);
    if(fobj.fail())
    {
        fobj.open("admin.bin",ios::out|ios::binary);
        Admin adminobj;
        adminobj.setUserDetails(userid,password,username);
        fobj.write((char*)&adminobj,sizeof(Admin));
    }
    fobj.close();
}
void User::setUserDetails(string userid,string password,string username)
{
     strcpy(this->userid,userid.c_str());
     strcpy(this->pwd,password.c_str());
     strcpy(this->username,username.c_str());
}
int User::input()
{
    clrscr();
    int i;
    textcolor(LIGHTGREEN);
    for(i=1;i<=96;i++)
        cout<<"*";
    cout<<endl;
    for(i=1;i<=96;i++)
        cout<<"*";
    textcolor (RED);
    gotoxy(42,2);
    cout<<"QUIZ APPLICATION";
    gotoxy(74,4);
    textcolor(WHITE);
    cout<<"Press 0 to Exit/Go back";
    gotoxy(1,10);
    textcolor(YELLOW);
    for(i=1;i<=96;i++)
        cout<<"*";
    gotoxy(1,21);
    for(i=1;i<=96;i++)
        cout<<"*";
    gotoxy(36,14);
        cout<<"Enter User ID :";
    textcolor(WHITE);
    cin.getline(userid,20);
    if(strcmp(userid,"0")==0)
        return 0;
    textcolor(YELLOW);
    gotoxy(36,15);
        cout<<"Enter Password:";
    char ch;
    i=0;
    while(true)
    {
        ch=getch();
        if(ch==13)
            break;
        if(ch==8)
        {
            if(i==0)
                continue;
            cout<<"\b \b";
            i--;
            continue;
        }
        cout<<ch;
        delay(200);
        cout<<"\b*";
        pwd[i]=ch;
        i++;
    }
    pwd[i]='\0';
    if(strcmp(pwd,"0")==0)
        return 0;
    return 1;
}
int User::checkUserExists(string usertype)
{
    if(strcmp(userid,"")==0||strcmp(pwd,"")==0)
    {
        gotoxy(34,24);
        textcolor(RED);
        cout<<"BOTH THE FEILD ARE MANDATORY";
        getch();
        return 0;
    }
    ifstream fin;
    User *uptr;
    if(usertype=="admin")
    {
        fin.open("admin.bin",ios::in|ios::binary);
        uptr=new Admin;
    }
    else if(usertype=="student")
    {
        fin.open("student.bin",ios::in|ios::binary);
        uptr=new Student;
    }
    else
    {
        gotoxy(30,24);
        textcolor(RED);
        cout<<"WRONG USERTYPE PASSED!";
        getch();
        return 0;
    }
    bool useridfound=0,pwdfound=0;
    while(1)
    {
        fin.read((char*)uptr,sizeof(*uptr));
        if(fin.eof())
             break;
        if(strcmp(userid,uptr->userid)==0)
        {
            if(strcmp(pwd,uptr->pwd)==0)
               {
                   useridfound=pwdfound=1;
                   break;
               }
               useridfound=1;
        }
    }
    bool result=0;
    if(useridfound==0)
    {
        gotoxy(38,24);
        textcolor(RED);
        cout<<"No Such User Exists!";
        getch();
    }
    else if(pwdfound==0)
    {
        gotoxy(40,24);
        textcolor(RED);
        cout<<"INVALID PASSWORD!";
        getch();
    }
    else
    {
        result=1;
        strcpy(username,uptr->username);
    }
    fin.close();
    return result;
}
string User::getName()
{
    string USERNAME(username);
    return USERNAME;
}
string User::getUserID()
{
    string USERID(userid);
    //USERID=userid;
    return USERID;
}
void Admin::addQuestion()
{
  Question quesObj;
  quesObj.add();
}

void Question::add()
{
   int i;
   fstream fobj("question.bin",ios::app|ios::in|ios::binary);
   if(!fobj)
   {
       gotoxy(36,15);
       textcolor(RED);
       cout<<"Sorry! File cannot be opened!";
       getch();
       return ;
   }
   fobj.seekg(0,ios::end);
   if(fobj.tellg()==0)
       quesid=1;
   else
   {
       fobj.seekg(-1*sizeof(*this),ios::end);
       fobj.read((char *)this,sizeof(*this));
       quesid++;
   }
   char uchoice;
   do
   {
       clrscr();
       textcolor(LIGHTGREEN);
       for(i=1;i<=96;i++)
          cout<<"*";
       cout<<endl;
       for(i=1;i<=96;i++)
         cout<<"*";
       textcolor (RED);
       gotoxy(42,2);
       cout<<"QUIZ APP";
       gotoxy(70,4);
       textcolor(WHITE);
       cout<<"Use * To Terminate Question";
       gotoxy(73,5);
       cout<<"Press 0* to Exit/Go back";
       gotoxy(35,6);
       cout<<"**** ADD QUESTION DETAILS ****";
       gotoxy(1,8);
       textcolor(YELLOW);
       string str;
       cout<<"Enter Question:";
       cin.ignore();
       textcolor(WHITE);
       getline(cin,str,'*');
       if(strcmp(str.c_str(),"0")==0)
       {
           gotoxy(38,14);
           textcolor(RED);
           cout<<"Closing Add Question...";
           getch();
           fobj.close();
           return;
       }
        strncpy(ques,str.c_str(),499);
        textcolor(LIGHTGREEN);
        cout<<endl<<"Carries marks:";
        textcolor(YELLOW);
        cin>>tot_marks;
        cout<<endl<<"OPTIONS"<<endl<<endl;
        textcolor(YELLOW);
        cout<<"(a)" ;
        cin.ignore();
        textcolor(WHITE);
        getline(cin,str);
        strncpy(op1,str.c_str(),99);
        textcolor(YELLOW);
        cout<<"(b)" ;
        textcolor(WHITE);
        getline(cin,str);
        strncpy(op2,str.c_str(),99);
        textcolor(YELLOW);
        cout<<"(c)" ;
        textcolor(WHITE);
        getline(cin,str);
        strncpy(op3,str.c_str(),99);
        textcolor(YELLOW);
        cout<<"(d)" ;
        textcolor(WHITE);
        getline(cin,str);
        strncpy(op4,str.c_str(),99);
        bool valid;
        do
        {
            gotoxy(1,20);
            textcolor(YELLOW);
            cout<<"Enter Correct Ans(a/b/c/d) :";
            textcolor(WHITE);
            cin>>ans;
            if(ans>='a'&&ans<='d')
                valid=true;
            else
            {
            gotoxy(36,23);
            textcolor(RED);
            cout<<"Invalid choice, Please try again";
            getch();
            gotoxy(36,23);
            cout<<"\t\t\t\t\t\t\t\t\t\t";
            gotoxy(29,20);
            cout<<"\t\t\t\t\t\t\t\t\t\t";
            valid=false;
            }
        }while(valid==false);
        fobj.write((char*)this,sizeof(*this));
        quesid++;
        gotoxy(34,23);
        textcolor(LIGHTGREEN);
        cout<<"QUESTION ADDED SUCESSFULLY!";
        getch();
        gotoxy(1,25);
        textcolor(LIGHTMAGENTA);
        cout<<"Do you want to add more questions (Y/N):";
        textcolor(WHITE);
        cin>>uchoice;
   }while(uchoice=='y'||uchoice=='Y');
   fobj.close();
}
void Admin::addStudent()
{
   Student studObj;
   studObj.add();
}

void Student::add()
{
    char uchoice;
    int id,i;
    string str;
   fstream fobj("student.bin",ios::app|ios::in|ios::binary);
   if(!fobj)
   {
       gotoxy(36,14);
       textcolor(RED);
       cout<<"Sorry! File cannot be opened!";
       getch();
       return ;
   }
    fobj.seekg(0,ios::end);
    if(fobj.tellg()==0)
       id=1;
   else
   {
       fobj.seekg(-1*sizeof(*this),ios::end);
       fobj.read((char *)this,sizeof(*this));
       char *pos=strchr(userid,'-');
       if(pos!=NULL)
       {
           id=atoi(pos+1);
           id++;
       }
   }
   do
   {
       clrscr();
       textcolor(LIGHTGREEN);
       for(i=1;i<=96;i++)
          cout<<"~";
       cout<<endl;
       for(i=1;i<=96;i++)
         cout<<"~";
       textcolor (RED);
       gotoxy(42,2);
       cout<<"QUIZ APP";
       gotoxy(74,4);
       textcolor(WHITE);
       cout<<"Press 0 to Exit/Go back";
       gotoxy(35,5);
       cout<<"**** ADD STUDENT DETAILS ****";
       gotoxy(1,8);
       textcolor(YELLOW);
       cout<<"Enter Student Name:";
       cin.ignore();
       textcolor(WHITE);
       getline(cin,str);
       strncpy(username,str.c_str(),49);
       if(strcmp(username,"0")==0)
       {
           gotoxy(38,14);
           textcolor(RED);
           cout<<"Closing Add Student...";
           getch();
           fobj.close();
           return;
       }
       textcolor(YELLOW);
       cout<<"Enter Student Password:";
       textcolor(WHITE);
       getline(cin,str);
       strncpy(pwd,str.c_str(),19);
       if(strcmp(pwd,"0")==0)
       {
           gotoxy(38,16);
           textcolor(RED);
           cout<<"Closing Add Student...";
           getch();
           fobj.close();
           return;
       }
       sprintf(userid,"STU-%d",id);
       fobj.write((char*)this,sizeof(*this));
       gotoxy(34,18);
       textcolor(LIGHTGREEN);
       cout<<"STUDENT ADDED SUCESSFULLY!";
       cout<<endl<<endl<<"STUDENT ID IS :"<<userid;
       getch();
        gotoxy(1,24);
        textcolor(LIGHTMAGENTA);
        cout<<"Do you want to add more questions (Y/N):";
        textcolor(WHITE);
        cin>>uchoice;
        id++;
   }while(uchoice=='y'||uchoice=='Y');
   fobj.close();
}
void Admin::viewQuestion()
{
    Question queObj;
    queObj.viewQuestion();
    clrscr();
}
void Question::viewQuestion()
{
    int i;
    ifstream fin("question.bin",ios::in|ios::binary);
    if(!fin)
    {
        gotoxy(36,15);
       textcolor(RED);
       cout<<"No questions have been added yet";
       getch();
       return ;
    }
    fin.seekg(0,ios::end);
    if(fin.tellg()==0)
    {
        gotoxy(36,15);
       textcolor(RED);
       cout<<"No questions present in the file";
       getch();
       fin.close();
       return;
    }
    clrscr();
    fin.seekg(0);
    while(1)
    {
       textcolor(LIGHTGREEN);
       for(i=1;i<=96;i++)
          cout<<"*";
       cout<<endl;
       for(i=1;i<=96;i++)
         cout<<"*";
       textcolor (RED);
       gotoxy(42,2);
       cout<<"QUIZ APP";
       textcolor(WHITE);
       gotoxy(35,5);
       cout<<"**** SHOW QUESTION DETAILS ****"<<endl<<endl;
       textcolor(LIGHTGREEN);
       for(i=1;i<=96;i++)
         cout<<"*";
       fin.read((char*)this,sizeof(*this));
       if(fin.eof())
       {
           cout<<endl;
           textcolor(LIGHTRED);
           gotoxy(35,10);
           cout<<"NO MORE QUESTIONS PRESENT!";
           getch();
           break;
       }
       else
       {
        show();
        getch();
        clrscr();
       }
    }
    fin.close();
}
void Question::show()
{
    cout<<endl;
    textcolor(YELLOW);
    cout<<"Q."<<quesid<<" ";
    cout<<ques<<endl;
    cout<<"carries Marks: "<<tot_marks<<endl;
    cout<<"a. "<<op1<<endl;
    cout<<"b. "<<op2<<endl;
    cout<<"c. "<<op3<<endl;
    cout<<"d. "<<op4<<endl;
    textcolor(LIGHTGREEN);
    cout<<endl<<"Correct Option:"<<ans;
}
void Admin::viewStudent()
{
    Student studObj;
    studObj.showStudentDetails();
    clrscr();
}
void Student::showStudentDetails()
{
    int i,x=10;;
    textcolor(LIGHTGREEN);
    for(i=1;i<=96;i++)
          cout<<"*";
    cout<<endl;
    for(i=1;i<=96;i++)
         cout<<"*";
    textcolor (RED);
    gotoxy(42,2);
    cout<<"QUIZ APP";
    textcolor(WHITE);
    gotoxy(35,5);
    cout<<"**** SHOW STUDENT DETAILS ****"<<endl<<endl;
    textcolor(LIGHTGREEN);
    for(i=1;i<=96;i++)
           cout<<"*";
    gotoxy(1,8);
    textcolor(YELLOW);
    cout<<"    Student ID\t\t\t\t  Student Name\t\t\t\t  Password"<<endl;
    textcolor(LIGHTGREEN);
    for(i=1;i<=96;i++)
           cout<<"*";
    ifstream fin("student.bin",ios::in|ios::binary);
    if(!fin)
    {
        gotoxy(38,15);
       textcolor(RED);
       cout<<"No students have been added yet";
       getch();
       return ;
    }
    fin.seekg(0,ios::end);
    if(fin.tellg()==0)
    {
        gotoxy(38,15);
       textcolor(RED);
       cout<<"No students present in the file";
       getch();
       fin.close();
       return;
    }
    fin.seekg(0);
    while(1)
    {
       fin.read((char*)this,sizeof(*this));
       if(fin.eof())
       {
           textcolor(WHITE);
           gotoxy(70,6);
           cout<<"Press any Key to Go back !";
           getch();
           break;
       }
       else
       {
        textcolor(WHITE);
        gotoxy(7,x);
        cout<<userid;
        gotoxy(43,x);
        cout<<username;
        gotoxy(86,x);
        cout<<pwd;
        x++;
       }
    }
    fin.close();
}
void Admin::removeQuestion()
{
    Question queObj;
    queObj.Remove();
    clrscr();
}
void Question::Remove()
{
       int i;
       clrscr();
       textcolor(LIGHTGREEN);
       for(i=1;i<=96;i++)
          cout<<"*";
       cout<<endl;
       for(i=1;i<=96;i++)
         cout<<"*";
       textcolor (RED);
       gotoxy(42,2);
       cout<<"QUIZ APP";
       gotoxy(74,4);
       textcolor(WHITE);
       cout<<"Press 0 to Exit/Go back";
       gotoxy(35,5);
       cout<<"**** REMOVE QUESTION DETAILS ****";
       ifstream fin("question.bin",ios::in|ios::binary);
        if(!fin)
      {
       gotoxy(36,14);
       textcolor(RED);
       cout<<"Sorry! File cannot be opened!";
       getch();
       return ;
      }
      fin.seekg(0,ios::end);
       if(fin.tellg()==0)
      {
        gotoxy(32,15);
       textcolor(RED);
       cout<<"No Questions Available For Deletion!";
       getch();
       fin.close();
       return;
      }
       ofstream fout("temp.bin",ios::out|ios::binary);
        if(!fout)
      {
       gotoxy(36 ,15);
       textcolor(RED);
       cout<<"Sorry! Removal not possible!";
       fout.close();
       getch();
       return ;
      }
      fin.seekg(0);
      bool found=false,valid=true;
      int id;
      do
      {
       gotoxy(1,8);
       textcolor(YELLOW);
       cout<<"Enter Question ID:";
       textcolor(WHITE);
       cin>>id;
       if(id==0)
       {
           fin.close();
           fout.close();
           remove("temp.bin");
           return;
       }
       if(id<0)
       {
         valid=false;
         gotoxy(38,18);
         textcolor(RED);
         cout<<"Invalid Question ID";
         getch();
         gotoxy(38,18);
         cout<<"\t\t\t\t\t\t\t";
         gotoxy(19,8);
         cout<<"\t\t\t\t\t\t\t";
         gotoxy(19,8);
       }
       else
       {
           while(true)
           {
               fin.read((char*)this,sizeof(*this));
               if(fin.eof())
                  break;
               if(id==quesid)
               {
                    found=true;
                    continue;
               }
               else
                    fout.write((char*)this,sizeof(*this));
           }
          fin.close();
          fout.close();
          if(found==true)
          {
              textcolor(LIGHTGREEN);
              gotoxy(36,20);
              cout<<"Question Removed Suecssfully!";
              getch();
              textcolor(WHITE);
              gotoxy(32,20);
              cout<<"         Press Any Key To Go Back";
              getch();
              remove("question.bin");
              rename("temp.bin","question.bin");
          }
          else
          {
              textcolor(RED);
              gotoxy(36,20);
              cout<<"Question ID Not Found!";
              getch();
              textcolor(WHITE);
              gotoxy(36,20);
              cout<<"Press Any Key To Go Back";
              remove("temp.bin");
              getch();
          }
       }
      }while(valid==false);
}
void Admin::removeStudent()
{
    Student studObj;
    studObj.Remove();
    clrscr();
}
void Student::Remove()
{
       int i;
       clrscr();
       textcolor(LIGHTGREEN);
       for(i=1;i<=96;i++)
          cout<<"*";
       cout<<endl;
       for(i=1;i<=96;i++)
         cout<<"*";
       textcolor (RED);
       gotoxy(42,2);
       cout<<"QUIZ APP";
       gotoxy(74,4);
       textcolor(WHITE);
       cout<<"Press 0 to Exit/Go back";
       gotoxy(35,5);
       cout<<"**** REMOVE STUDENT DETAILS ****";
       ifstream fin("student.bin",ios::in|ios::binary);
        if(!fin)
      {
       gotoxy(35,15);
       textcolor(RED);
       cout<<"Sorry! File Cannot Be Opened!";
       getch();
       return ;
      }
      fin.seekg(0,ios::end);
       if(fin.tellg()==0)
      {
        gotoxy(35,15);
       textcolor(RED);
       cout<<"No Student Has Been Added!";
       getch();
       fin.close();
       return;
      }
       ofstream fout("temp.bin",ios::out|ios::binary);
        if(!fout)
      {
       gotoxy(35,15);
       textcolor(RED);
       cout<<"Sorry! Removal Not Possible!";
       fout.close();
       getch();
       return ;
      }
      fin.seekg(0);
      bool found=false,valid=true;
      char id[20];
      do
      {
       gotoxy(1,8);
       textcolor(YELLOW);
       cout<<"Enter Student ID:";
       textcolor(WHITE);
       cin.ignore();
       cin.getline(id,20);
       if(strcmp(id,"0")==0)
       {
           fin.close();
           fout.close();
           remove("temp.bin");
           return;
       }
       else
       {
           while(true)
           {
               fin.read((char*)this,sizeof(*this));
               if(fin.eof())
                  break;
               if(strcmp(id,userid)==0)
               {
                    found=true;
                    continue;
               }
               else
                    fout.write((char*)this,sizeof(*this));
           }
          fin.close();
          fout.close();
          if(found==true)
          {
            textcolor(LIGHTGREEN);
              gotoxy(36,20);
              cout<<"Student Removed Suecssfully!";
              getch();
              textcolor(WHITE);
              gotoxy(34,20);
              cout<<"        Press Any Key To Go Back";
              getch();
              remove("student.bin");
              rename("temp.bin","student.bin");
          }
          else
          {
             textcolor(RED);
              gotoxy(36,20);
              cout<<"Student ID Not Found!";
              getch();
              textcolor(WHITE);
              gotoxy(36,20);
              cout<<"Press Any Key To Go Back";
              remove("temp.bin");
              getch();
          }
       }
      }while(valid==false);
}
void Student::quiz()
{
    Question quesObj;
    quesObj.startQuiz(userid);
    clrscr();
}
void Question::startQuiz(string id)
{
    int i;
    ifstream fin("question.bin",ios::in|ios::binary);
    if(fin.fail())
    {
        gotoxy(30,20);
        textcolor(RED);
        cout<<"No Question Have Been Added Yet!";
        getch();
        return;
    }
    vector <Question> vecQues;
    while(1)
    {
      fin.read((char*)this,sizeof(*this));
      if(fin.eof())
        break;
      vecQues.push_back(*this);
    }
    fin.close();
    vector <int> vecRand;
    srand((unsigned int)time(NULL));
    int randno;
    while(1)
    {
        randno=rand()%vecQues.size();
        if(ispresent(vecRand,randno)==true)
              continue;
        vecRand.push_back(randno);
        if(vecQues.size()==vecRand.size())
              break;
    }
    int count=0;
    int local_marks=0;
    int local_tot_marks=0;
    User userObj;
    string name=userObj.getName(id);
    for(int i=0;i<vecQues.size();i++)
    {
       int index=vecRand.at(i);
       *this=vecQues.at(index);
       clrscr();
       textcolor (RED);
       gotoxy(45,2);
       cout<<"QUIZ APP";
       gotoxy(1,4);
       textcolor(YELLOW);
       for(int j=1;j<=96;j++)
          cout<<"*";
        textcolor(WHITE);
       gotoxy(75,5);
       cout<<name;
       gotoxy(10,5);
        cout<<"TOTAL QUESTION: "<<vecQues.size();
         gotoxy(1,6);
         textcolor(YELLOW);
         for(int j=1;j<=96;j++)
         cout<<"*";
         count++;
         gotoxy(1,8);
         textcolor(LIGHTBLUE);
         cout<<count<<")";
         gotoxy(4,8);
         cout<<this->ques<<endl<<endl;
         textcolor(LIGHTGRAY);
         cout<<"a. "<<this->op1<<endl<<endl;
         cout<<"b. "<<this->op2<<endl<<endl;
         cout<<"c. "<<this->op3<<endl<<endl;
         cout<<"d. "<<this->op4<<endl<<endl;
         bool valid;
         char uans;
         do
         {
             textcolor(YELLOW);
             cout<<"Enter Your Option(a/b/c/d):  \b";
             textcolor(WHITE);
             cin>>uans;
             if(uans>='a'&&uans<='d')
                valid=true;
             else
             {
                 valid=false;
                 gotoxy(32,23);
            textcolor(RED);
            cout<<"Invalid Option Entered, Please Try Again";
            getch();
            gotoxy(32,23);
            cout<<"\t\t\t\t\t\t\t\t\t\t";
            gotoxy(1,18);
             }
         }while(valid==false);
         local_tot_marks+=this->tot_marks;
         if(this->ans==uans)
             local_marks+=this->tot_marks;
    }
       clrscr();
       textcolor(LIGHTGREEN);
       for(i=1;i<=96;i++)
          cout<<"*";
       cout<<endl;
       for(i=1;i<=96;i++)
         cout<<"*";
       textcolor (RED);
       gotoxy(42,2);
       cout<<"QUIZ APP";
       gotoxy(38,14);
       cout<<"** TEST FINISHED **";
       gotoxy(30,18);
       textcolor(WHITE);
       cout<<"Press Any Key To Go Back To Main Menu";
       getch();
       StudentPerformance sp;
       sp.setMarksDetails(id,local_marks,local_tot_marks);
}
bool ispresent (vector<int> & v,int value)
{
    for(int i=0;i<v.size();i++)
    {
        if(v.at(i)==value)
             return true;
    }
    return false;
}
string User::getName(string id)
{
    ifstream fin("student.bin",ios::in|ios::binary);
    if(!fin)
    {
        cout<<"Sorry! File Canot Open";
    }
    while(1)
    {
        fin.read((char*)this,sizeof(*this));
        if(fin.eof())
        {
            cout<<"No match of record found";
            break;
        }
        int result=strcmp(this->getUserID().c_str(),id.c_str());
        if(result==0)
        {
            fin.close();
            return this->username;
        }
    }
    fin.close();
    return NULL;
}
void StudentPerformance::setMarksDetails(string id,int marks,int tot_marks)
{
    strcpy(studid,id.c_str());
    this->marks=marks;
    this->tot_marks=tot_marks;
    saveMarksDetails();
}
void StudentPerformance::saveMarksDetails()
{
    ofstream fout("performance.bin",ios::app|ios::binary);
    if(!fout)
    {
        textcolor (RED);
        gotoxy(36,20);
        cout<<"Error in creating/Opening file";
        getch();
        return;
    }
    fout.write((char*)this,sizeof(*this));
    fout.close();
}
void Student::viewPerformance()
{
    StudentPerformance stuper;
    string stid(userid);
    stuper.viewDetails(stid);
}
void StudentPerformance::viewDetails(string id)
{
    textcolor (RED);
    gotoxy(46,2);
    cout<<"QUIZ APP"<<endl;
    textcolor(LIGHTGREEN);
    for(int i=1;i<=96;i++)
        cout<<"*";
    textcolor(YELLOW);
    gotoxy(35,5);
    cout<<"***** VIEW REPORT CARD *****"<<endl;
    for(int i=1;i<=96;i++)
        cout<<"-";
    User userObj;
    string name=userObj.getName(id);
    cout<<endl<<"Name :"<<name;
    ifstream fin("performance.bin",ios::in|ios::binary);
    if(!fin)
    {
       gotoxy(34,15);
       textcolor(RED);
       cout<<"No Test Have Been Given By You";
       getch();
       return ;
    }
    gotoxy(1,10);
    textcolor(LIGHTGREEN);
    cout<<"   SNO\t\t\t\t    MARKS OBTAINED\t\t\t\t  TOTAL MARKS"<<endl;
    int count=1;
    int x=11;
    while(1)
    {
       fin.read((char*)this,sizeof(*this));
       if(fin.eof())
       {
           textcolor(YELLOW);
           gotoxy(1,x);
           for(int i=1;i<=96;i++)
               cout<<"-";
           x=x+2;
           gotoxy(38,x);
           textcolor(RED);
           cout<<"NO RECORD MORE !";
           break;
       }
       if(strcmp(this->studid,id.c_str())==0)
       {
        textcolor(WHITE);
        gotoxy(5,x);
        cout<<count;
        gotoxy(43,x);
        cout<<marks;
        gotoxy(86,x);
        cout<<tot_marks;
        x++;
        count++;
       }
    }
    fin.close();
    getch();
}
void Admin::editQuestion()
{
    Question queObj;
    queObj.editQuestion();
}
void Question::editQuestion()
{
       int i;
       clrscr();
       textcolor(LIGHTGREEN);
       for(i=1;i<=96;i++)
          cout<<"*";
       cout<<endl;
       for(i=1;i<=96;i++)
         cout<<"*";
       textcolor (RED);
       gotoxy(42,2);
       cout<<"QUIZ APP";
       gotoxy(74,4);
       textcolor(WHITE);
       cout<<"Press 0 to Exit/Go back";
       gotoxy(35,5);
       cout<<"**** EDIT QUESTIONS ****"<<endl;
       for(i=1;i<=96;i++)
         cout<<"*";
        ifstream fin("question.bin",ios::in|ios::binary);
        if(!fin)
      {
       gotoxy(36,14);
       textcolor(RED);
       cout<<"Sorry! File cannot be opened!";
       getch();
       return ;
      }
      fin.seekg(0,ios::end);
       if(fin.tellg()==0)
      {
        gotoxy(32,15);
       textcolor(RED);
       cout<<"No Questions Available For Deletion!";
       getch();
       fin.close();
       return;
      }
       ofstream fout("temp.bin",ios::out|ios::binary);
        if(!fout)
      {
       gotoxy(36 ,15);
       textcolor(RED);
       cout<<"Sorry! Removal not possible!";
       fout.close();
       getch();
       return ;
      }
      fin.seekg(0);
      bool found=false,valid1=true;
      int id;
      do
      {
       gotoxy(1,8);
       textcolor(YELLOW);
       cout<<"Enter Question ID:";
       textcolor(WHITE);
       cin>>id;
       if(id==0)
       {
           fin.close();
           fout.close();
           remove("temp.bin");
           return;
       }
       if(id<0)
       {
         valid1=false;
         gotoxy(38,18);
         textcolor(RED);
         cout<<"Invalid Question ID";
         getch();
         gotoxy(38,18);
         cout<<"\t\t\t\t\t\t\t";
         gotoxy(19,8);
         cout<<"\t\t\t\t\t\t\t";
         gotoxy(19,8);
       }
       else
       {
           while(true)
           {
               fin.read((char*)this,sizeof(*this));
               if(fin.eof())
                  break;
               if(id==quesid)
               {
                    show();
                    gotoxy(70,4);
                    textcolor(WHITE);
                    cout<<"Use * To Terminate Question";
                    gotoxy(73,5);
                    cout<<"Press 0* to Exit/Go back";
                    gotoxy(1,19);
                    textcolor(YELLOW);
                    string str;
                    cout<<"Enter Correct Question:";
                    cin.ignore();
                    textcolor(WHITE);
                    getline(cin,str,'*');
                    if(strcmp(str.c_str(),"0")==0)
                    {
                       gotoxy(38,25);
                       textcolor(RED);
                       cout<<"Exit Edit Question...";
                       getch();
                       fin.close();
                       fout.close();
                       remove("temp.bin");
                       return;
                    }
                    strncpy(ques,str.c_str(),499);
                    textcolor(LIGHTGREEN);
                    cout<<"Carries marks:";
                    textcolor(YELLOW);
                    cin>>tot_marks;
                    textcolor(YELLOW);
                    cout<<endl<<"(a)" ;
                    cin.ignore();
                    textcolor(WHITE);
                    getline(cin,str);
                    strncpy(op1,str.c_str(),99);
                    textcolor(YELLOW);
                    cout<<"(b)" ;
                    textcolor(WHITE);
                    getline(cin,str);
                    strncpy(op2,str.c_str(),99);
                    textcolor(YELLOW);
                    cout<<"(c)" ;
                    textcolor(WHITE);
                    getline(cin,str);
                    strncpy(op3,str.c_str(),99);
                    textcolor(YELLOW);
                    cout<<"(d)" ;
                    textcolor(WHITE);
                    getline(cin,str);
                    strncpy(op4,str.c_str(),99);
                    bool valid2;
                    do
                   {
                    gotoxy(1,27);
                    textcolor(YELLOW);
                    cout<<"Enter Correct Ans(a/b/c/d) :";
                    textcolor(WHITE);
                    cin>>ans;
                    if(ans>='a'&&ans<='d')
                       valid2=true;
                    else
                    {
                      gotoxy(36,28);
                      textcolor(RED);
                      cout<<"Invalid choice, Please try again";
                      getch();
                      gotoxy(36,28);
                      cout<<"\t\t\t\t\t\t\t\t\t\t";
                      gotoxy(29,27);
                      cout<<"\t\t\t\t\t\t\t\t\t\t";
                      valid2=false;
                    }
                    }while(valid2==false);
                    fout.write((char*)this,sizeof(*this));
                    found=true;
                    continue;
               }
               else
                    fout.write((char*)this,sizeof(*this));
           }
          fin.close();
          fout.close();
          if(found==true)
          {
              gotoxy(34,28);
              textcolor(LIGHTGREEN);
              cout<<"QUESTION EDITED SUCESSFULLY!";
              getch();
              remove("question.bin");
              rename("temp.bin","question.bin");
          }
          else
          {
              textcolor(RED);
              gotoxy(36,20);
              cout<<"Question ID Not Found!";
              getch();
              textcolor(WHITE);
              gotoxy(36,20);
              cout<<"Press Any Key To Go Back";
              remove("temp.bin");
              getch();
          }
       }
      }while(valid1==false);
}
