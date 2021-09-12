#include<fstream>
#include<iostream>
#include<string.h>
#include<stdlib.h>
using namespace std;
class book
{
    int bookid;//unique for every book
    char bookname[50];
    char authorname[50];
    int edition;
    int issuedto;
    char issuedon[10];
    friend void search();
    friend void removebook();
    friend void issuebook();
public:
    void accept()
    {
        cout<<endl<<"Enter Bookid: ";
        cin>>bookid;
        cout<<endl<<"Enter Book Name: ";
        cin>>bookname;
        cout<<endl<<"Author Name: ";
        cin>>authorname;
        cout<<endl<<"Edition";
        cin>>edition;
        issuedto=-1;
        strcpy(issuedon,"");
    }
    void display()
    {
        cout<<bookid<<"\t";
        int p=strlen(bookname);
        int diff=30-p;
        for(int i=1;i<=diff;i++)
        {
            strcat(bookname," ");
        }
        cout<<bookname;

        int z=strlen(authorname);
        int diff2=25-z;
        for(int i=1;i<=diff2;i++)
        {
            strcat(authorname," ");
        }
        cout<<authorname<<"\t"<<edition<<"\t"<<issuedto<<"   "<<issuedon<<endl;
    }
};

//Class Ends here
book obj; // global object
////////
void addbook()
{
    fstream wr;
    wr.open("d:\\books.txt",ios::app);
    obj.accept();
    wr.write((char *)&obj,sizeof(obj));
    wr.close();
    cout<<endl<<"Book Added Successfully";
}
void search()
{
    fstream rd;
    rd.open("d:\\books.txt",ios::in);//connect
    rd.seekg(0,ios::end);//take cursor to end
    char bk[50];
    cout<<endl<<"Enter Book Name";
    cin>>bk;

    int n=rd.tellg();//get location of cursor which will also be size of file
    rd.seekg(0,ios::beg);//bring cursor to first position
    cout<<"Bookid     BookName                Author Name      Edition    Issued to";
    cout<<endl<<"****************************************************************"<<endl;

    for(int i=1;i<=n/sizeof(obj);i++) // apply loop to print all objects
    {
        rd.read((char *)&obj,sizeof(obj)); //read object
        if(stricmp(obj.bookname,bk)==0)
        {
        obj.display();//print object
        }
    }
    cout<<endl<<"*******************************************************";

}

void readall()
{
    fstream rd;
    rd.open("d:\\books.txt",ios::in);//connect
    rd.seekg(0,ios::end);//take cursor to end

    int n=rd.tellg();//get location of cursor which will also be size of file
    rd.seekg(0,ios::beg);//bring cursor to first position
    cout<<"Bookid     BookName                Author Name      Edition    Issued to";
    cout<<endl<<"****************************************************************"<<endl;

    for(int i=1;i<=n/sizeof(obj);i++) // apply loop to print all objects
    {
        rd.read((char *)&obj,sizeof(obj)); //read object
        obj.display();//print object
    }
    cout<<endl<<"*******************************************************";

}
void removebook()
{
    int bid;
    cout<<endl<<"Enter Book ID to remove book";
    cin>>bid;
    fstream rd;
    rd.open("d:\\books.txt",ios::in);
    rd.seekg(0,ios::end);
    int n=rd.tellg();
    int size=n/sizeof(obj);
    rd.seekg(0,ios::beg);
    fstream wr;
    wr.open("d:\\temp.txt",ios::out);
    for(int i=1;i<=size;i++)
    {
        rd.read((char *)&obj,sizeof(obj));
        if(obj.bookid==bid)
        {
            cout<<endl<<"Book Removed";
        }
        else
        {
            wr.write((char *)&obj,sizeof(obj));
        }
    }
    rd.close();
    wr.close();
    remove("d:\\books.txt");
    rename("d:\\temp.txt","d:\\books.txt");
}
void issuebook()
{
    int bid;
    cout<<endl<<"Enter Book id";
    cin>>bid;
    fstream rd;
    rd.open("d:\\books.txt",ios::in);
    rd.seekg(0,ios::end);
    int n=rd.tellg();
    int size=n/sizeof(obj);
    rd.seekg(0,ios::beg);
    fstream wr;
    wr.open("d:\\temp.txt",ios::out);
    for(int i=1;i<=size;i++)
    {
        rd.read((char *)&obj,sizeof(obj));
        if(obj.bookid==bid && obj.issuedto!=-1)
        {
            cout<<endl<<"Cannot Issue Book";
        }
        else if(obj.bookid==bid)
        {
            int mid;
            cout<<endl<<"Enter Member id";
            cin>>mid;
            char date[20];
            cout<<endl<<"Enter Issue Date";
            cin>>date;
            obj.issuedto=mid;
            strcpy(obj.issuedon,date);
            cout<<endl<<"Book Issued";
        }

        wr.write((char *)&obj,sizeof(obj));
    }
    rd.close();
    wr.close();
    remove("d:\\books.txt");
    rename("d:\\temp.txt","d:\\books.txt");
}

main()
{
    while(1)
    {
        cout<<endl<<"---------------------------------------------";
        cout<<endl<<"Enter 1 to Add New Book";
        cout<<endl<<"Enter 2 to View All Books";
        cout<<endl<<"Enter 3 to Search Books";
        cout<<endl<<"Enter 4 to Issue Book";
        cout<<endl<<"Enter 5 to Return Book";
        cout<<endl<<"Enter 6 to Remove Book";
        cout<<endl<<"Enter 7 to Exit";
        int choice;
        cout<<endl<<"Enter Choice";
        cin>>choice;
        if(choice==1)
        {
            addbook();
        }
        else if(choice==2)
        {
        readall();
        }
        else if(choice==3)
        {
            search();
        }
        else if(choice==4)
        {
            issuebook();
        }
        else if(choice==5)
        {


        }
        else if(choice==6)
        {

            removebook();
        }
        else
        {

            break;
        }

    }
}
