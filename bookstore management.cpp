#include <iostream>
#include<string.h>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
class account{
  char username[20];
  char password[20];
  public:
  account(){
  strcpy(username,"000");
  strcpy(password,"111");
  }
  void getdata(){
    cout<<"Enter Username:";
    cin>>username;
    cout<<"Enter password:";
    cin>>password;
  }
  int checkcredentials()
  {
    getdata();
    if( strcmp(username , "bookstore") == 0 && strcmp(password , "modyuni") == 0)
    return 1;
    else
    return 0;
  }
}a;
class book{
  int serial_no;
  char name[20];
  char author[20];
  char genre[20];
  public:
  book(){
  serial_no = 0;
  strcpy(name,"000");
  strcpy(author,"111");
  strcpy(genre,"222");
  }
 int getserial(){
  return serial_no;
 }
 char* getgen(){
    return genre;
  }
  char* getaut(){
    return author;
  }
  char* getnam(){
    return name;
  }
 void getdata(){
  cout<<"Enter Serial Number Of Book\t:";
  cin>>serial_no;
  cout<<"Enter Name Of Book\t\t\t:";
  cin>>name;
  cout<<"Enter Name Of Author\t\t:";
  cin>>author;
   cout<<"Enter Genre\t\t:";
  cin>>genre;
  }
 void show(){ 
  cout<<"\nSERIAL NO.\t:"<<serial_no;
  cout<<"\nBOOK\t\t:"<<name;
  cout<<"\nAUTHOR\t\t:"<<author;
  cout<<"\nGENRE\t\t:"<<genre;
  }
};
class add_book:public virtual book{
  int number;
  int issue_date[8];
  int reissue_date[8];
  int return_date[8];
  double price;
  public:
 void in(){
  getdata();
  cout<<"Enter number of copies:";
  cin>>number;
  cout<<"Issue date (in ddmmyyyy format):";
  for(int i = 0; i < 8; i ++)
  cin>>issue_date[i];
  cout<<"Enter price of book:";
  cin>>price;
  }
 void calculate_date(){
  for(int i = 0 ; i < 8 ; i ++)
  reissue_date[i] = issue_date[i];
  reissue_date[1] += 5;
  reissue_date[0] += 1;
  if( reissue_date[1] > 9){
    reissue_date[0]++;
    reissue_date[1] %= 10;
  }
  if(reissue_date[0] >3){
    reissue_date[3]++;
    reissue_date[0] %= 3;
  }
  for(int i = 0 ; i < 8 ; i ++)
  return_date[i] = reissue_date[i];
 }
 void details(){
  calculate_date();
  show();
  cout<<"\nNumber of copies:"<<number;
  cout<<"\nIssue date (in d d m m y y y y format):";
  for(int i = 0 ; i < 8 ; i ++)
  cout<<" "<<issue_date[i];
  cout<<"\nReissue date (in ddmmyyyy format):";
  for(int i = 0 ; i < 8 ; i ++)
  cout<<" "<<reissue_date[i];
  cout<<"\nReturn date (in ddmmyyyy format):";
  for(int i = 0 ; i < 8 ; i ++)
  cout<<" "<<return_date[i];
  cout<<"\nPrice:"<<price;
 }
}b[5];
class remove_book:public virtual book, public virtual add_book{
  int s_no;
  public:
  remove_book(){
  s_no = 0;
  }
 void r_in(){
   cout<<"Enter serial number of book:";
  cin>>s_no;
 }
 int getsno(){
  return s_no;
  }
 void output(){
  show();
  details();
  }
}r;
class search_book:public virtual book, public virtual add_book{
  int search_no;
  char gen[20];
  char aut[20];
  char nam[20];
  public:
  search_book(){
    search_no = 0;
    strcpy(gen, "000");
    strcpy(nam, "000");
    strcpy(aut, "000");
  }
  int getsearch(){
    return search_no;
  }
  char* getgenre(){
    return gen;
  }
  char* getauthor(){
    return aut;
  }
  char* getbookname(){
    return nam;
  }
  void sno_in(){
    cout<<"Enter serial number of book:";
  cin>>search_no;
  }
  void sname_in(){
    cout<<"Enter Name of book:";
  cin>>nam;
  }
  void sauthor_in(){
    cout<<"Enter Author of book:";
  cin>>aut;
  }
  void sgenre_in(){
    cout<<"Enter Genre of book:";
  cin>>gen;
  }
  
}s;
int main(){
  int n, i, choice, ch;
  char found = 'f', confirm = 'n';
  fstream f,f1,ff;
  f.open("book.txt",ios::out);
  ff.open("cart.txt",ios::in|ios::out);
  A: if(a.checkcredentials() == 1)
  cout<<"WELCOME TO MODY BOOK STORE";
  
  else
  {
    cout<<"The username or password entered is wrong!!!\nWant to try again?";cin>>choice;
    if(choice == 1)
    goto A;
    else
    exit(0);
  }
  cout<<"\nEnter n:";
  cin>>n;
  for( i = 0 ; i < n ; i ++ )
  {
    b[i].in();
    f.write((char*)&b[i],sizeof(b[i]));
  }
  f.close();
  
  do{
    cout<<"\nWant to add a book or delete a book or search a book:";
    cin>>choice;
    switch(choice){
      case 1: f.open("book.txt",ios::app);
              b[n+1].in();
              n += 1;
              f.write((char*)&b[n],sizeof(b[n]));
              f.close();
              f.open("book.txt",ios::in);
              for( i = 0 ; i < n ; i ++ )
              {f.read((char*)&b[i],sizeof(b[i]));
                b[i].details();
              }
              f.close();
              break;
      case 2: f.open("book.txt",ios::in);
              f1.open("temp.txt",ios::out);
              r.r_in();
              for( i = 0 ; i < n ; i ++ )
              {  f.read((char*)&b[i],sizeof(b[i]));
                 if(r.getsno() == b[i].getserial())
                 {
                    found = 'y';
                    cout<<"Are you sure you want to delete this record (y/n)?"; 
                    cin>>confirm;
                    if(confirm == 'n')
                    {
                      f1.write((char*)&b[i],sizeof(b[i]));
                    }
                  }
                 else 
                 f1.write((char*)&b[i],sizeof(b[i]));
              }
             
              if ( found == 'f' )
              cout<<"Record not found!";
              f.close();
              f1.close();
              remove("book.txt");
              rename("temp.txt" , "book.txt");
              n--;
              cout<<"Now the bag contains:";
              f1.open("book.txt",ios::in);
              for( i = 0 ; i < n ; i ++ )
              {
                f1.read((char*)&b[i],sizeof(b[i]));
                b[i].details();
              }
              f1.close();
              break;
      case 3: cout<<"Enter choice for the basis of your       search:\n1.Serial number\n2.Book name\n3.Author's name\n4.Genre:";
              cin>>ch;
              f.open("book.txt",ios::in);
    switch(ch){
      case 1: s.sno_in();
              for( i = 0 ; i < n ; i ++ )
              { f.read((char*)&b[i],sizeof(b[i])); 
                if(s.getsearch() == b[i].getserial())
                b[i].details(); 
              }
              break;
      case 2: s.sname_in();
              for( i = 0 ; i < n ; i ++ )
              {  f.read((char*)&b[i],sizeof(b[i]));
                if(strcmp(s.getbookname() , b[i].getnam()) == 0)
                b[i].details();    
              }
              break;
      case 3: s.sauthor_in();
              for( i = 0 ; i < n ; i ++ )
              {  f.read((char*)&b[i],sizeof(b[i]));
                if(strcmp(s.getauthor() , b[i].getaut()) == 0)
                b[i].details();    
              }
              break;
      case 4: s.sgenre_in();
              for( i = 0 ; i < n ; i ++ )
              {  f.read((char*)&b[i],sizeof(b[i]));
                if(strcmp(s.getgenre() , b[i].getgen()) == 0)
                b[i].details();    
              }
              break;                
      default:cout<<"Wrong choice entered!!!";
              break;
    }
    break;
  f.close();
              break;
      default:cout<<"Wrong choice entered!!!";
              break;
    }
    cout<<"\nWant to add or delete or search more?: (1 - yes || 0 - no):";
    cin>>choice;
  }while( choice );
  return 0;
}