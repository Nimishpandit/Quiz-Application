#include <iostream>
#include"conio2.h"
#include"quiz.h"
using namespace std;
int main()
{
    int i,type,c,choice;
    textcolor(LIGHTGREEN);
    for(i=1;i<=96;i++)
        cout<<"*";
    cout<<endl;
    for(i=1;i<=96;i++)
        cout<<"*";
    textcolor(RED);
    gotoxy(60,2);
    cout<<"QUIZ APPLICATION";
    gotoxy(28,13);
    textcolor(YELLOW);
    cout<<"WELCOME TO TECH TEST - QUIZ APPLICATION";
     gotoxy(28,17);
    textcolor(LIGHTGREEN);
    cout<<"TEST YOUR SKILLS ! IMPROVE YOUR KNOWLEDGE";
    textcolor(WHITE);
    gotoxy(1,24);
    cout<<"Press any key to continue";
    getch();
    Admin::createAdmin("admin","abc","Nimish");
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
        gotoxy(42,13);
        cout<<"1. ADMIN";
        gotoxy(42,15);
        cout<<"2. STUDENT";
        gotoxy(40,18);
        textcolor(WHITE);
        cout<<"Select your role:";
        cin>>type;
        if(type==0)
        {
            clrscr();
            break;
        }
        cin.ignore();
        if(type==1)
        {
            Admin adminobj;
            do
            {
               c=adminobj.input();
               if(c==0)
               {
                  gotoxy(38,19);
                  textcolor(RED);
                  cout<<"Login Cancelled";
                  gotoxy(1,25);
                  textcolor(WHITE);
                  cout<<"Press any key to continue";
                  getch();
                  break;
               }
               c=adminobj.checkUserExists("admin");
               if(c==1)
               {
                  gotoxy(40,22);
                  textcolor(LIGHTGREEN);
                  cout<<"Login Accepted!";
                  gotoxy(40,24);
                  cout<<"Welcome "<<adminobj.getName();
                  gotoxy(1,25);
                  textcolor(WHITE);
                  cout<<"Press any key to continue";
                  getch();
                  while(1)
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
                            cout<<"QUIZ APPLICATION";
                            textcolor(LIGHTGREEN);
                            gotoxy(43,8);
                            cout<<"ADMIN MENU"<<endl;
                            textcolor (YELLOW);
                            for(i=1;i<=96;i++)
                                cout<<"*";
                            gotoxy(42,10);
                            cout<<"1.Add Question";
                            gotoxy(42,11);
                            cout<<"2.Add Student";
                            gotoxy(42,12);
                            cout<<"3.Show Question";
                            gotoxy(42,13);
                            cout<<"4.Edit Question";
                            gotoxy(42,14);
                            cout<<"5.Show Student";
                            gotoxy(42,15);
                            cout<<"6.Remove Question";
                            gotoxy(42,16);
                            cout<<"7.Remove Student";
                            gotoxy(42,17);
                            cout<<"8.Exit";
                            gotoxy(42,19);
                            cout<<"Enter Choice:";
                            textcolor(WHITE);
                            cin>>choice;
                            if(choice==8)
                                break;
                            switch(choice)
                            {
                             case 1:
                                   clrscr();
                                   adminobj.addQuestion();
                                   break;
                            case 2:
                                   clrscr();
                                   adminobj.addStudent();
                                   break;
                            case 3:
                                   clrscr();
                                   adminobj.viewQuestion();
                                   break;
                            case 4:
                                   clrscr();
                                   adminobj.editQuestion();
                                   break;
                            case 5:
                                   clrscr();
                                   adminobj.viewStudent();
                                   break;
                            case 6:
                                   clrscr();
                                   adminobj.removeQuestion();
                                   break;
                            case 7:
                                   clrscr();
                                   adminobj.removeStudent();
                                   break;
                            default:
                                    gotoxy(38,22);
                                    textcolor(RED);
                                    cout<<"Wrong choice, Try again";
                                    getch();
                             }
                        }
                        if(choice==8)
                            break;
               }
            }while(c==0);
          }
        else if(type==2)
        {
            Student studObj;
            do
            {
               c=studObj.input();
               if(c==0)
               {
                  gotoxy(38,19);
                  textcolor(RED);
                  cout<<"Login Cancelled";
                  gotoxy(1,25);
                  textcolor(WHITE);
                  cout<<"Press any key to continue";
                  getch();
                  break;
               }
               c=studObj.checkUserExists("student");
               if(c==1)
               {
                  gotoxy(40,22);
                  textcolor(LIGHTGREEN);
                  cout<<"Login Accepted!";
                  gotoxy(40,24);
                  cout<<"Welcome "<<studObj.getName();
                  gotoxy(1,25);
                  textcolor(WHITE);
                  cout<<"Press any key to continue";
                  getch();
                  while(1)
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
                            cout<<"QUIZ APPLICATION";
                            textcolor(LIGHTGREEN);
                            gotoxy(43,8);
                            cout<<"STUDENT MENU"<<endl;
                            textcolor (YELLOW);
                            for(i=1;i<=96;i++)
                                cout<<"*";
                            gotoxy(42,10);
                            cout<<"1.Start Quiz";
                            gotoxy(42,11);
                            cout<<"2.View Performance";
                            gotoxy(42,12);
                            cout<<"3.Exit";
                            gotoxy(42,14);
                            cout<<"Enter Choice:";
                            textcolor(WHITE);
                            cin>>choice;
                            if(choice==3)
                                break;
                            switch(choice)
                            {
                             case 1:
                                   clrscr();
                                   studObj.quiz();
                                   break;
                            case 2:
                                   clrscr();
                                   studObj.viewPerformance();
                                   break;
                            default:
                                    gotoxy(38,22);
                                    textcolor(RED);
                                    cout<<"Wrong choice, Try again";
                                    getch();
                             }
                        }
                        if(choice==3)
                            break;
               }
            }while(c==0);
        }
        else
        {
            gotoxy(40,18);
            cout<<"\t\t\t\t\t\t\t";
            gotoxy(42,18);
            textcolor(RED);
            cout<<"Invalid User Type";
            getch();
        }
    }while(1);
    return 0;
}
