#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
using namespace std;

class book
{
    private:
        int bookid;
        char bookname[50];
        char authorname[50];
        int edition;
        int issuedto;
        char issuedon[15];
        char returnedon[15];
        friend void search();
        friend void removebook();
        friend void issuebook();
        friend void returnbook();
    public:
        void accept()
        {
            cout<<endl<<"Enter Bookid: ";
            cin>>bookid;
            cout<<"Enter Book Name: ";
            cin>>bookname;
            cout<<"Author Name: ";
            cin>>authorname;
            cout<<"Edition: ";
            cin>>edition;
            issuedto=-1;
            strcpy(issuedon," ");
            strcpy(returnedon," ");
        }

        void display()
        {
            cout<<bookid<<"\t\t";
            int p=strlen(bookname);
            int diff=25-p;
            for(int i=1;i<=diff;i++)
            {
                strcat(bookname," ");
            }
            cout<<bookname;

            int z=strlen(authorname);
            int diff2=25-z;
            for(int i=1;i<diff2;i++)
            {
                strcat(authorname," ");
            }
            cout<<authorname<<"\t"<<edition<<"\t\t"<<issuedto<<"        "<<issuedon<<"      "<<returnedon<<endl;
        }


};

book obj;

void addbook()
{
    fstream ad;
    ad.open("d:\\books.txt",ios::app);
    obj.accept();
    ad.write((char *)&obj,sizeof(obj));
    ad.close();
    cout<<endl<<"Book Added Successfully";
}

void search()
{
    char bk[50];
    fstream se;
    se.open("d:\\books.txt",ios::in);
    se.seekg(0,ios::end);
    cout<<endl<<"Enter Book Name: ";
    cin>>bk;

    int n=se.tellg();
    se.seekg(0,ios::beg);
    cout<<endl<<"Book ID          Book Name               Author Name                 Edition         Issued To       Issued On       Returned On       ";
    cout<<endl<<"************************************************************************************************************************************"<<endl;
    for(int i=1;i<=n/sizeof(obj);i++)
        {
            se.read((char *)&obj,sizeof(obj));
            if (stricmp(obj.bookname,bk)==0)
            {
                obj.display();
            }
        }
    cout<<endl<<"************************************************************************************************************************************";
}

void readall()
{
    fstream rd;
    rd.open("d:\\books.txt",ios::in);
    rd.seekg(0,ios::end);
    int n=rd.tellg();
    rd.seekg(0,ios::beg);
    cout<<endl<<"Book ID          Book Name               Author Name                 Edition         Issued To       Issued On       Returned On       ";
    cout<<endl<<"************************************************************************************************************************************"<<endl;
    for(int i=1;i<=n/sizeof(obj);i++)
    {
        rd.read((char *)&obj,sizeof(obj));
        obj.display();
    }
    cout<<endl<<"************************************************************************************************************************************";

}

void removebook()
{
    int bid,n,size;
    cout<<endl<<"Enter Book ID to remove book: ";
    cin>>bid;
    fstream rd;
    rd.open("d:\\books.txt",ios::in);
    rd.seekg(0,ios::end);
    n=rd.tellg();
    size=n/sizeof(obj);
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
    int bid,n,size;
    char date[15];
    cout<<endl<<"Enter Book ID: ";
    cin>>bid;
    fstream rd;
    rd.open("d:\\books.txt",ios::in);
    rd.seekg(0,ios::end);
    n=rd.tellg();
    size=n/sizeof(obj);
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
            cout<<endl<<"Enter Member ID: ";
            cin>>mid;
            cout<<endl<<"Enter Issue Date: ";
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

void returnbook()
{
    int bid,n,size;
    cout<<endl<<"Enter Book ID: ";
    cin>>bid;
    int mid;
    cout<<endl<<"Enter Member ID: ";
    cin>>mid;
    fstream rd;
    rd.open("d:\\books.txt",ios::in);
    rd.seekg(0,ios::end);
    n=rd.tellg();
    size=n/sizeof(obj);
    rd.seekg(0,ios::beg);
    fstream wr;
    wr.open("d:\\temp.txt",ios::out);
    for(int i=1;i<=size;i++)
    {
        rd.read((char *)&obj,sizeof(obj));
        if(obj.bookid==bid && obj.issuedto==-1)
        {
            cout<<endl<<"Cannot Return Book";
        }
        else if(obj.bookid==bid && obj.issuedto!=mid)
        {
            cout<<endl<<"Cannot Return Book";
        }
        else if(obj.bookid==bid && obj.issuedto==mid)
        {
            obj.issuedto=-1;
            char date2[15];
            cout<<endl<<"Enter Return Date: ";
            cin>>date2;
            strcpy(obj.returnedon,date2);
            cout<<endl<<"Book Returned";
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
        cout<<endl<<"-------------------------------------";
        cout<<endl<<"Enter 1 to Add New Book";
        cout<<endl<<"Enter 2 to View All Books";
        cout<<endl<<"Enter 3 to Search Book";
        cout<<endl<<"Enter 4 to Issue Book";
        cout<<endl<<"Enter 5 to Return Book";
        cout<<endl<<"Enter 6 to Remove Book";
        cout<<endl<<"Enter 7 to Exit";
        int choice;
        cout<<endl<<"Enter Choice: ";
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
            returnbook();
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
