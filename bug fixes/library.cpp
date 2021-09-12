
#include<fstream>
#include<iostream>
#include<string.h>
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
        cout<<authorname<<"\t"<<edition<<"\t"<<issuedto<<"\t\t"<<issuedon<<endl;
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
main()
{
 search();
}
