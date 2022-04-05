#include <iostream>
#include <string>
#include <map>
#include <sstream>
 using namespace std;

class Users{
public:
   string username;
   string password;

   int login(){
     cout<<"Enter the username and password:- ";
     string _username, _password;
     cin>>_username >>_password;
     cout<<endl;

     if(username==_username and password==_password){
        cout<<"Logged In successfully!!\n\n";
        return 1;
     }
     else
        cout<<"Wrong details!!\n\n";
     return 0;
    }

 };

class Case;
map<int, Case> database;

class Case{
public:
     int CIN;
     string defendant_name;
     string defendant_add;
     string crime_type;
     string crime_date;
     string crime_loc;
     string officer_name;
     string arrest_date;
     string lawyer_name;
     string judge_name;
     string prosecutor_name;
     string judgement_date;
     string starting_date;
     string case_status;
     string case_summary;

     Case(int _CIN=0, string _defendant_name="", string _defendant_add="", string _crime_type="", string _crime_date="", string _crime_loc="", string _officer_name="",
    string _arrest_date="", string _lawyer_name="", string _judge_name="", string _prosecutor_name="", string _starting_date="", string _case_status="", string _case_summary=""){
        CIN=_CIN;
        defendant_name=_defendant_name;
        defendant_add=_defendant_add;
        crime_type=_crime_type;
        crime_date=_crime_date;
        crime_loc=_crime_loc;
        officer_name=_officer_name;
        arrest_date=_arrest_date;
        lawyer_name=_lawyer_name;
        judge_name=_judge_name;
        prosecutor_name=_prosecutor_name;
        starting_date=_starting_date;
        case_status=_case_status;
        case_summary=_case_summary;
     }
 };

class Lawyer: public Users{
public:
    int amount;
    Lawyer(){
        username = "Shubham";
        password = "0000@";
    }
    void getCaseSummary(int CIN){
        string summary = database[CIN].case_summary;
        cout<<"The case summary is:- "<<summary<<endl<<endl;
    }
    void payCharge(int t){
        amount=t*10;
        cout<<"Total Amount to be paid:- Rs. "<<endl<<endl;
    }
 };

 class SlotDetails{
 public:
     static int section;
     static int day;
     int getSlot(){
        if(section%4==0){
            day++;
            section++;
        }

        if(section%4==1){
            cout<<"Slot is "<<day<<" days later in the morning slot"<<endl;
        }

        else if(section%4==2){

            cout<<"Slot is "<<day<<" days later in the afternoon slot"<<endl;
        }

        else if(section%4==3){
            cout<<"Slot is "<<day<<" days later in the evening slot"<<endl;
        }

        section++;
        return day;
     }
 };
int SlotDetails::section=1;
int SlotDetails::day=0;

class Registrar: public Users{
 public:
    Registrar(){
        username = "Shantanu";
        password = "1234";
    }
    string toDate(int d,string starting_date){
        int day=-1,month=-1,year=-1;
        int c=0;
        for(int i=0;i<starting_date.length();i++){
            int r=0,w=0;

            while(starting_date[i]!='/'&&i<starting_date.length()){
                r=starting_date[i];
                r-=48;
                w=w*10+r;
                i++;
            }
            if(c==0)
                day=w;
            else if(c==1)
                month=w;
            else
                year=w;
            c++;
        }
        if((day+d)/30==0)
            day+=d;
        else if((day+d)/30<12){
            month+=(day+d)/30;
            day=(day+d)%30+1;
        }
        else{
            year+=(day+d)/360;
            month+=((day+d)%360)/30;
            day=((day+d)%360)%30+1;
        }
        string judgement_date;
        ostringstream str1;
        str1<<day;
        judgement_date.append(str1.str());
        judgement_date.append("/");
        ostringstream str2;
        str2<<month;
        judgement_date.append(str2.str());
        judgement_date.append("/");
        ostringstream str3;
        str3<<year;
        judgement_date.append(str3.str());
        return judgement_date;
    }

    void registerCases(int CIN, string defendant_name, string defendant_add, string crime_type, string crime_date,
    string crime_loc, string officer_name, string arrest_date, string lawyer_name, string judge_name, string prosecutor_name, string starting_date, string case_status, string case_summary){

         Case new_case(CIN, defendant_name, defendant_add, crime_type, crime_date,
    crime_loc, officer_name, arrest_date, lawyer_name, judge_name, prosecutor_name, starting_date, case_status, case_summary);
         SlotDetails st;
         int d=st.getSlot();
         new_case.judgement_date=toDate(d,starting_date);
         database.insert({CIN, new_case});

         cout<<"Successfully Added!!\n\n";
     }

     void editAccounts(){
         cout<<"Enter 1 to add an account and 2 to delete an account:-\n";
         int op;
         cin>>op;
         cout<<endl;
         if(op==1){
			 cout<<"Enter 1 to add a judge account and 2 to add a lawyer account:-\n";
			 int ch;
			 cin>>ch;
             cout<<endl;
			 if(ch==1){
				 cout<<"Enter the new judge's username:-\n";
				 string new_username;
				 cin>>new_username;
                 cout<<endl;
				 cout<<"Enter the new judge's password:-\n";
				 string new_password;
				 cin>>new_password;
                 cout<<endl;
				 cout<<"Successfully added!!\n\n";
			 }
            else{
                 cout<<"Enter the new lawyer's username:-\n";
                 string new_username;
                 cin>>new_username;
                 cout<<endl;
                 cout<<"Enter the new lawyer's password:-\n";
                 string new_password;
                 cin>>new_password;
                 cout<<endl;
                 cout<<"Successfully added!!\n\n";
            }
         }
            else{
                 cout<<"Enter the username to be deleted:-\n";
                 string new_username;
                 cin>>new_username;
                 cout<<endl;
                 cout<<"Successfully deleted!!\n\n";
            }
    }

     void updateCaseSummary(int CIN){
         string new_summary;
         cout<<"Enter new summary:- ";
         getline(cin>>ws,new_summary);
         cout<<endl;
         database[CIN].case_summary=new_summary;
         cout<<"Enter new case status:- ";
         string new_case_status;
         cin>>new_case_status;
         cout<<endl;
         database[CIN].case_status=new_case_status;
         if(new_case_status=="Pending"){
            cout<<"Case still pending\nRescheduling\n";
            SlotDetails st;
            int d=st.getSlot();
            database[CIN].judgement_date=toDate(d,database[CIN].judgement_date);
         }
     }

     void getCaseSummary(int CIN){
         string summary = database[CIN].case_summary;
         cout<<"The case summary is:- "<<summary<<endl<<endl;
     }
     void getPendingCases(){
        for(auto it: database){
            if(it.second.case_status=="Pending")
                cout<<"Starting Date:- "<<it.second.starting_date<<" ,Judge Name:- "<<it.second.judge_name<<" ,Defendant Name:- "<<it.second.defendant_name<<" ,Defendant Address:- "<<
                it.second.defendant_add<<" ,Crime Type:- "<<it.second.crime_type<<" ,Crime Location:- "<<it.second.crime_loc<<" ,Prosecutor Name:- "<<it.second.prosecutor_name<<" ,Lawyer Name:- "<<
                it.second.lawyer_name<<"\n\n";
        }
     }
     void getResolvedCases(){
         for(auto it: database){
            if(it.second.case_status=="Resolved")
                cout<<"Starting Date:- "<<it.second.starting_date<<" ,CIN:- "<<it.first<<" ,Judge Name:- "<<it.second.judge_name<<" ,Judgement Date:- "<<it.second.judgement_date<<" ,Case Summary:- "<<
                it.second.case_summary<<"\n\n";
        }
     }
     void getUpcomingCase(string input_date){
         for(auto it: database){
            if(it.second.starting_date==input_date)
                cout<<"Starting Date:- "<<it.second.starting_date<<" ,Judge Name:- "<<it.second.judge_name<<" ,Defendant Name:- "<<it.second.defendant_name<<" ,Defendant Address:- "<<
                it.second.defendant_add<<" ,Crime Type:- "<<it.second.crime_type<<" ,Crime Location:- "<<it.second.crime_loc<<" ,Prosecutor Name:- "<<it.second.prosecutor_name<<" ,Lawyer Name:- "<<
                it.second.lawyer_name<<"\n\n";
        }
     }
 };

 class Judge: public Users{
 public:
     Judge(){
        username = "Himanshu";
        password = "qwerty";
     }
     void getCaseSummary(int CIN){
         string summary = database[CIN].case_summary;
         cout<<"The case summary is:- "<<summary<<endl<<endl;
     }
 };

 int main(){
     int start=100;
     while(1){
         cout<<"Enter 1 for Registrar, 2 for Judge, 3 for Lawyer and 4 to exit:- ";
         int choice;
         cin>>choice;
         cout<<endl;
         if(choice==1){
            Registrar registrar;

                if(registrar.login()){
                    while(1){
                        cout<<"Enter 1 for register new case, 2 for update case summary, 3 for query case, 4 for edit account and 5 for exit:-\n";
                        int option;
                        cin>>option;
                        cout<<endl;
                        if(option==1){
                            int CIN;
                            string defendant_name;
                            string defendant_add;
                            string crime_type;
                            string crime_date;
                            string crime_loc;
                            string officer_name;
                            string arrest_date;
                            string lawyer_name;
                            string judge_name;
                            string prosecutor_name;
                            string starting_date;
                            string case_status;
                            string case_summary;

                            cout<<"Enter the defendant name:- ";
                            getline(cin>>ws, defendant_name);
                            cout<<endl;

                            cout<<"Enter the defendant address:- ";
                            getline(cin>>ws, defendant_add);
                            cout<<endl;

                            cout<<"Enter the type of crime:- ";
                            cin>>crime_type;
                            cout<<endl;

                            cout<<"Enter the date of crime(dd/mm/yyyy):- ";
                            cin>>crime_date;
                            cout<<endl;

                            cout<<"Enter the location of crime:- ";
                            getline(cin>>ws, crime_loc);
                            cout<<endl;

                            cout<<"Enter the name of officer:- ";
                            getline(cin>>ws, officer_name);
                            cout<<endl;

                            cout<<"Enter the date of arrest(dd/mm/yyyy):- ";
                            cin>>arrest_date;
                            cout<<endl;

                            cout<<"Enter the name of lawyer:- ";
                            getline(cin>>ws, lawyer_name);
                            cout<<endl;

                            cout<<"Enter the name of judge:- ";
                            getline(cin>>ws, judge_name);
                            cout<<endl;

                            cout<<"Enter the name of officer:- ";
                            getline(cin>>ws, officer_name);
                            cout<<endl;

                            cout<<"Enter the name of prosecutor:- ";
                            getline(cin>>ws, prosecutor_name);
                            cout<<endl;

                            cout<<"Enter the starting date of case(dd/mm/yyyy):- ";
                            cin>>starting_date;
                            cout<<endl;

                            cout<<"Enter the status of case:- ";
                            cin>>case_status;
                            cout<<endl;

                            cout<<"Enter the summary of case:- ";
                            getline(cin>>ws, case_summary);
                            cout<<endl;

                            CIN=start;
                            start++;
                            cout<<"The CIN of this case is:- "<<CIN<<endl;
                            registrar.registerCases(CIN, defendant_name, defendant_add, crime_type, crime_date, crime_loc, officer_name, arrest_date, lawyer_name, judge_name, prosecutor_name, starting_date, case_status, case_summary);
                        }

                        else if(option==2){
                            int CIN;
                            cout<<"Enter the CIN of case:- ";
                            cin>>CIN;
                            cout<<endl;
                            registrar.updateCaseSummary(CIN);
                        }

                        else if(option==3){
                            cout<<"Enter 1 to view pending cases, 2 to view resolved cases, 3 to view upcoming case and 4 to get summary of a case:-\n";
                            int ch;
                            cin>>ch;
                            cout<<endl;
                            if(ch==1){
                                registrar.getPendingCases();
                            }

                            else if(ch==2){
                                registrar.getResolvedCases();
                            }

                            else if(ch==3){
                                string input_date;
                                cout<<"Enter the date:- ";
                                cin>>input_date;
                                cout<<endl;
                                registrar.getUpcomingCase(input_date);
                            }

                            else if(ch==4){
                                int CIN;
                                cout<<"Enter the CIN of case:- ";
                                cin>>CIN;
                                cout<<endl;
                                registrar.getCaseSummary(CIN);
                            }
                            else
                                cout<<"Invalid Selection\n";
                        }
                        else if(option==4){
                            registrar.editAccounts();
                        }
                        else if(option==5)
                            break;
                        else
                            cout<<"Invalid selection\n";
                    }
                }
        }

        else if(choice==2){
            Judge judge;
            if(judge.login()){
                int CIN;
                cout<<"Enter the CIN of case:- ";
                cin>>CIN;
                cout<<endl;
                judge.getCaseSummary(CIN);
            }
         }

        else if(choice==3){
            Lawyer lawyer;
            if(lawyer.login()){
                cout<<"Enter the number of case files to be viewed:- ";
                int n;
                cin>>n;
                cout<<endl;
                for(int i=1;i<=n;i++){
                int CIN;
                cout<<"Enter the CIN of case:- ";
                cin>>CIN;
                cout<<endl;
                lawyer.getCaseSummary(CIN);
                }
                lawyer.payCharge(n);
            }
         }

         else if(choice==4)
            break;

        else
            cout<<"Invalid Selection\n";
    }
     return 0;
 }
