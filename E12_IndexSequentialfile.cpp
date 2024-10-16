/*Company maintains employee information as employee 
ID, name, designation, and salary. Allow user to add delete information of particular employee. 
If employee does not exist an appropriate message is displayed. If it is, then system displays 
the employee details. Use index sequential file to maintain the data*/

#include<iostream>
#include<cstring>
#include<fstream>
using namespace std;

class employee 
{
    public:
    int id;
    int salary;
    char name[50];
    char designation[50];
};

class employeedata 
{
    public:
  string filename="employedata.dat";
  employeedata()
  {
    fstream f;
    f.open(filename,ios::out);
    f.close();
  }
    void addEmployee();
    void searchEmployee();
    void displayemployee();
    void deletemployee(); 
};

void employeedata::deletemployee()
{
  employee e;
  int count=0,n;
  ifstream fin(filename,ios::in|ios::binary);
  cout<<"enter employee id"<<endl;
  cin>>n;
  ofstream fout("temp.dat",ios::out|ios::binary);

  while(fin.read((char*)&e,sizeof(e)))
  {  
    if(e.id!=n)
    {
      fout.write((char*)&e,sizeof(e));   
    }
  }
  fin.close();
  fout.close();
  remove("employedata.dat");//built in function syntex remove(filename)
  rename("temp.dat","employedata.dat");//built in rename filename rename(oldfilename,newfilename)
}
void employeedata::searchEmployee()
 {
  employee e;
  int count=0,n;
  ifstream fin(filename,ios::in|ios::binary);
  cout<<"enter employee id"<<endl;
  cin>>n;

  while(fin.read((char*)&e,sizeof(e)))
  {
    if(e.id==n)
    {
      count=1;
      break;
    }
  }
  fin.close();
  if(count==1)
  {
    cout<<"records  found as fillow data"<<endl;
    cout<<"employee id:"<<e.id<<" \n " ;
    cout<<"employee name:"<<e.name<<" \n";
    cout<<"employee designation:"<<e.designation<<" \n ";
    cout<<"employee sallary:"<<e.salary<<" \n";
  }
 }
void employeedata::addEmployee()
{    
    static int i=0;
    int id;
    employee e;
    static int data[10];
    cout<<"enter id of employee"<<endl;
    cin>>id;
    int n=0;
    for(int i=0;i<10;i++)
    {
      if(data[i]==id)
      {
        n=1;
         cout<<"index file unique index  only";
        exit(0);
      }
    }
    data[i++]=id;
    if(!n)
    {
      e.id=id;
      cout<<"enter name of employee:"<<endl;
      cin.get();
      cin.getline(e.name,50);
      cout<<"enter employee designation:"<<endl;
      //cin.get();
      cin.getline(e.designation,50);
      cout<<"enter salary of employee"<<endl;
      cin>>e.salary;
      ofstream fout(filename,ios::out|ios::app|ios::binary);
      fout.write((char*)&e, sizeof(e));
      if(fout.fail())
      {
        cout<<"fail to add records"<<endl;
      }
      else 
      {
        cout<<"records added succesfully"<<endl;
      }
      fout.close();
    }
}
void employeedata:: displayemployee()
{
  employee e;
  int count=0;
  ifstream fin(filename,ios::in|ios::binary);
  cout<<count<<") ";
    cout<<"ID"<<" | " ;
    cout<<"NAME"<<" | ";
    cout<<"DESIGNATION"<<" | ";
    cout<<"SALARY"<<" | ";

  while(fin.read((char*)&e,sizeof(e)))
  {
    count++;
    cout<<"\n"<<count<<") ";
    cout<<e.id<<" | " ;
    cout<<e.name<<" | ";
    cout<<e.designation<<" | ";
    cout<<e.salary<<" | \n";
  }
  if(count==0)
  {
    cout<<"records not found"<<endl;
  }
 fin.close();
}

int main()
{
  employeedata e;
  int c;
  do
  {cout<<"1.add records\n2.search records\n3.display records\n4.delete records\n5.exit"<<endl;
   cout<<"enter your choice"<<endl;
   cin>>c;
   switch(c)
   {
    case 1:e.addEmployee(); break;
    case 2:cout<<"\nsearch records->:\n"<<endl;
           e.searchEmployee();break;
    case 3: e.displayemployee();break;
    case 4:
           e.deletemployee();
           cout<<"\nrecords deleted succesfully"<<endl;
           break;
    case 5:exit(0);
           break;
    default:cout<<"enter valid choice:"<<endl;
           break;
   }
  }while(c<=5);  
}