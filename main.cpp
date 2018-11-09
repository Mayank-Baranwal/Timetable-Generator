#include<iostream>
#include<fstream>
#include<iomanip>
#include<conio.h>
#include<string.h>
#include<process.h>

#define true 1
#define false 0
//macros

using namespace std;

int N,N1,N2,N3;
int noOfTeachers;

int ceil(int n)
{
    if(n%3==0)return n/3;
    return (int)(n/3)+1;
}

char* conv(int n)
{
    if(n==1)return "Phy";
    if(n==2)return "Chem";
    if(n==3)return "Math";
    if(n==4)return "Eng";
    if(n==5)return "CS";
    if(n==6)return "Bio";
    if(n==7)return "Eco";
    if(n==8)return "PhyL";
    if(n==9)return "ChemL";
    if(n==10)return "Math";
    if(n==11)return "PT";
    if(n==12)return "CSL";
    if(n==13)return "BioL";
    if(n==14)return "Eco";
    if(n==15)return "Yoga";
    return " ";
}

class Section
{
    int id;
public:
    char name[5];
    int tt[5][9];
    int sub[10][2];

    Section();
    void getSub(int code);
    int hasSub(int a)
    {
	for(int i=0;i<10;i++)if(a==sub[i][0])
	    return true;
	return false;
    }
    void getId(int x){
        id=x;
    }
    int putId(){
        return id;
    }
}sec[25];

Section::Section()
{
    int i,j;
    strcpy(name,"0");
    for(i=0;i<5;i++)
	for(j=0;j<9;j++)
	    tt[i][j]=0;
    for(i=0;i<10;i++)
    {
	sub[i][0]=0;
	sub[i][1]=0;
    }
}

void Section::getSub(int code)
{
    sub[0][0]= 1 ;
    sub[1][0]= 2 ;
    sub[2][0]= 3 ;
    sub[3][0]= 4 ;
    sub[5][0]= 8 ;
    sub[6][0]= 9 ;
    sub[7][0]= 10;
    sub[8][0]= 11;
    if(code==1)
    {
        sub[4][0]= 5 ;
        sub[9][0]= 12;
    }
    if(code==2)
    {
        sub[4][0]= 6 ;
        sub[9][0]= 13;
    }
    if(code==3)
    {
        sub[4][0]= 7;
        sub[9][0]= 14;
    }
}

class Teacher
{
public :
        char name[20];
        int id;
        int sub;
        int tt[5][9];
        int noOfSectTaught;

        Teacher();
        int isFree(int d,int p)
        {
            return !tt[d][p];
        }
}teacher[50];

Teacher::Teacher()
{
    strcpy(name,"0");
    for(int i=0;i<5;i++)
        for(int j=0;j<9;j++)
            tt[i][j]=0;
    noOfSectTaught=0;
}

class Lab
{
    int sub;
public:
    int tt[5][9];
    Lab();
    void getSub(int x){
        sub =x;
    }
    int putSub(){
        return sub;
    }
}lab[7];

Lab::Lab()
{
    for(int i=0;i<5;i++)
        for(int j=0;j<9;j++)
            tt[i][j]=0;
}

int periodNotOver(int i,int j,int a)
{
    for(int k=0;k<9;k++)
        if(sec[i].tt[j][k]==a || sec[i].tt[j][k]==a+7)
            return false;
    return true;
}

void assignTeacher()
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<5;j++)
        {
            for(int k=0;k<noOfTeachers;k++)
            {
                if(teacher[k].noOfSectTaught<3 && teacher[k].sub==sec[i].sub[j][0])
                {
                    teacher[k].noOfSectTaught++;
                    sec[i].sub[j][1] =teacher[k].id;
                    break;
                }
            }
        }
    }
}
//Assign Labs
void populateTimeTable()
{
    int i,j,k,l,a,d,b=0;
    for(i=0;i<N;i++)
    {
	for(a=0;a<4;a++)
	{
	    b=0;
	    for(k=0;k<noOfTeachers;k++)
	    {
		if(teacher[k].id==sec[i].sub[a][1])
		{
		//for section i locate first unallocated last slot
		    for(d=a+i;d<a+5+i;d++)
		    {
			if(sec[i].tt[d%5][8]==0 &&teacher[k].isFree(d%5,8))
			{
			    sec[i].tt[d%5][7]=a+1;
			    sec[i].tt[d%5][8]=a+1;
			    teacher[k].tt[d%5][7]=sec[i].putId();
			    teacher[k].tt[d%5][8]=sec[i].putId();

			    sec[i].tt[(d+1)%5][4]=a+1;
			    sec[i].tt[(d+1)%5][5]=a+1;
			    teacher[k].tt[(d+1)%5][4]=sec[i].putId();
			    teacher[k].tt[(d+1)%5][5]=sec[i].putId();

			    sec[i].tt[(d+2)%5][2]=a+1;
			    sec[i].tt[(d+2)%5][3]=a+1;
			    teacher[k].tt[(d+2)%5][2]=sec[i].putId();
			    teacher[k].tt[(d+2)%5][3]=sec[i].putId();

			    sec[i].tt[(d+3)%5][0]=a+1;
			    sec[i].tt[(d+3)%5][1]=a+1;
			    teacher[k].tt[(d+3)%5][0]=sec[i].putId();
			    teacher[k].tt[(d+3)%5][1]=sec[i].putId();

			    sec[i].tt[(d+4)%5][6]=a+1;
			    teacher[k].tt[(d+4)%5][6]=sec[i].putId();

			    b=1;
			    break;
			}
		    }
		    if(b)break;
		}
	    }
	}
    }
    int t=0;
    for(i=0;i<N1;i++,t++)
    {
	for(l=0;l<noOfTeachers;l++)
	    if(teacher[l].id==sec[t].sub[4][1])
		break;
	for(j=0;j<5;j++)
	{
	    for(k=0;k<9;k++)
		if(!sec[t].tt[j][k])
		{
		    sec[t].tt[j][k] = 5;
		    teacher[l].tt[j][k] =sec[t].putId();
		}
	}
    }
    for(i=0;i<N2;i++,t++)
    {
	for(l=0;l<noOfTeachers;l++)
	    if(teacher[l].id==sec[t].sub[4][1])
		break;
	for(j=0;j<5;j++)
	{
	    for(k=0;k<9;k++)
		if(!sec[t].tt[j][k])
		{
		    sec[t].tt[j][k] = 6;
		    teacher[l].tt[j][k] =sec[t].putId();
		}
	}
    }
    for(i=0;i<N3;i++,t++)
    {
	for(l=0;l<noOfTeachers;l++)
	{
	    if(teacher[l].id==sec[t].sub[4][1])break;
	}
	for(j=0;j<5;j++)
	{
	    for(k=0;k<9;k++)
		if(!sec[t].tt[j][k])
		{
		    sec[t].tt[j][k] = 7;
		    teacher[l].tt[j][k] =sec[t].putId();
		}
	}
    }
    int flag=0;
    for(i=0;i<N;i++)
    {
	for(a=5;a<10;a++)
	{
	    flag=0;
	    for(l=0;l<7;l++)
		if(lab[l].putSub()==(sec[i].sub[a][0]))break;
	    for(j=0;j<5;j++)
	    {
		if(sec[i].tt[j][8]==(sec[i].sub[a][0]-7) && !lab[l].tt[j][8])
		{
		    sec[i].tt[j][7]+=7;
		    sec[i].tt[j][8]+=7;
		    lab[l].tt[j][7]=sec[i].putId();
		    lab[l].tt[j][8]=sec[i].putId();
		    flag =1;
		    break;
		}
	    }
	    if(!flag)
	    for(j=0;j<5;j++)
	    {
		if(sec[i].tt[j][5]==(sec[i].sub[a][0]-7) && !lab[l].tt[j][5])
		{
		    sec[i].tt[j][4]+=7;
		    sec[i].tt[j][5]+=7;
		    lab[l].tt[j][4]=sec[i].putId();
		    lab[l].tt[j][5]=sec[i].putId();
		    flag=1;
		    break;
		}
	    }
	    if(!flag)
	    for(j=0;j<5;j++)
	    {
		if(sec[i].tt[j][3]==(sec[i].sub[a][0]-7) && !lab[l].tt[j][3])
		{
		    sec[i].tt[j][2]+=7;
		    sec[i].tt[j][3]+=7;
		    lab[l].tt[j][2]=sec[i].putId();
		    lab[l].tt[j][3]=sec[i].putId();
		    flag=1;
		    break;
		}
	    }
	    if(!flag)
	    for(j=0;j<5;j++)
	    {
		if(sec[i].tt[j][1]==(sec[i].sub[a][0]-7) && !lab[l].tt[j][1])
		{
		    sec[i].tt[j][0]+=7;
		    sec[i].tt[j][1]+=7;
		    lab[l].tt[j][0]=sec[i].putId();
		    lab[l].tt[j][1]=sec[i].putId();
		    flag=1;
		    break;
		}
	    }
	}
    }
}


void gen()
{
    int i,j,t=0,a;
    cout<<"Enter Number of Computer science classes : ";
    cin>>N1;
    cout<<"Enter Number of Biology science classes : ";
    cin>>N2;
    cout<<"Enter Number of Economics science classes : ";
    cin>>N3;
    cout<<endl;

    N=N1+N2+N3;
    noOfTeachers = 4*ceil(N) +ceil(N1) +ceil(N2) + ceil(N3);

    for(i=0;i<N1;i++,t++)
    {
	cout<<"Enter name of Computer Science class "<<i+1<<" : ";
	cin>>sec[t].name;
    }
    for(i=0;i<N2;i++,t++)
    {
	cout<<"Enter name of Biology class "<<i+1<<" : ";
	cin>>sec[t].name;
    }
    for(i=0;i<N3;i++,t++)
    {
	cout<<"Enter name of Economics class "<<i+1<<" : ";
	cin>>sec[t].name;
    }
    t=0;

    cout<<endl;
    for(i=0; i<4; i++)
    {
	for(j=0; j<ceil(N); j++,t++)
	{
	    switch(i)
	    {
		case 0: cout<<"Enter name of Physics Teacher "<<j+1<<" : ";
			cin>>teacher[t].name;
			break;
		case 1: cout<<"Enter name of Chemistry Teacher "<<j+1<<" : ";
			cin>>teacher[t].name;
			break;
		case 2: cout<<"Enter name of Maths Teacher "<<j+1<<" : ";
			cin>>teacher[t].name;
			break;
		case 3: cout<<"Enter name of English Teacher "<<j+1<<" : ";
			cin>>teacher[t].name;
			break;
	    }
	}
    }
    for (i=0; i<ceil(N1); i++,t++)
    {
	cout<<"Enter name of Computer Science Teacher "<<i+1<<" : ";
	cin>>teacher[t].name;
    }
    for (i=0; i<ceil(N2); i++,t++)
    {
	cout<<"Enter name of Biology Teacher "<<i+1<<" : ";
	cin>>teacher[t].name;
    }
    for (i=0; i<ceil(N3); i++,t++)
    {
	cout<<"Enter name of Economics Teacher "<<i+1<<" : ";
	cin>>teacher[t].name;
    }
    t=0,a=0;
    for(i=0;i<N1;i++,a++)
    {
	sec[a].getId(a+1);
	sec[a].getSub(1);
    }
    for(i=0;i<N2;i++,a++)
    {
	sec[a].getId(a+1);
	sec[a].getSub(2);
    }
    for(i=0;i<N3;i++,a++)
    {
	sec[a].getId(a+1);
	sec[a].getSub(3);
    }
    for(i=0;i<ceil(N);i++,t++)
    {
	teacher[t].sub = 1;
	teacher[t].id = t+1;
    }
    for(i=0;i<ceil(N);i++,t++)
    {
	teacher[t].sub = 2;
	teacher[t].id = t+1;
    }
    for(i=0;i<ceil(N);i++,t++)
    {
	teacher[t].sub = 3;
	teacher[t].id = t+1;
    }
    for(i=0;i<ceil(N);i++,t++)
    {
	teacher[t].sub = 4;
	teacher[t].id = t+1;
    }
    for(i=0;i<ceil(N1);i++,t++)
    {
	teacher[t].sub = 5;
	teacher[t].id = t+1;
    }
    for(i=0;i<ceil(N2);i++,t++)
    {
	teacher[t].sub = 6;
	teacher[t].id = t+1;
    }
    for(i=0;i<ceil(N3);i++,t++)
    {
	teacher[t].sub = 7;
	teacher[t].id = t+1;
    }
    lab[0].getSub(8);
    lab[1].getSub(9);
    lab[2].getSub(10);
    lab[3].getSub(11);
    lab[4].getSub(12);
    lab[5].getSub(13);
    lab[6].getSub(14);

    assignTeacher();
    populateTimeTable();
}

void datafile()
{
    int i,j,k;
    ofstream fout ("Variables.txt",ios::out);
    fout<<N<<"\t"<<noOfTeachers;
    fout.close();

    ofstream fout2 ("Section.txt",ios::out);
    for(i=0; i<N; i++)
    {
	fout2<<sec[i].name<<"\t"<<sec[i].putId()<<"\t"<<sec[i].sub[4][0]<<endl;
	for(j=0; j<5; j++)
	{
	    for(k=0; k<9; k++)
		fout2<<sec[i].tt[j][k]<<"\t";
	    fout2<<endl;
	}
	fout2<<endl;
    }
    fout2.close();

    ofstream fout3 ("Teacher.txt",ios::out);
    for(i=0; i<noOfTeachers; i++)
    {
	fout3<<teacher[i].name<<"\t"<<teacher[i].id<<"\t"<<teacher[i].sub<<endl;
	for(j=0; j<5; j++)
	{
	    for(k=0; k<9; k++)
		fout3<<teacher[i].tt[j][k]<<"\t";
	    fout3<<endl;
	}
	fout3<<endl;
    }
    fout3.close();

    ofstream fout4 ("Lab.txt",ios::out);
    for(i=0; i<7; i++)
    {
	fout4<<lab[i].putSub()<<"\t"<<endl;
	for(j=0; j<5; j++)
	{
	    for(k=0; k<9; k++)
		fout4<<lab[i].tt[j][k]<<"\t";
	    fout4<<endl;
	}
	fout4<<endl;
    }
    fout4.close();
}

void disp()
{
    cout.setf(ios::left);
    int i,j,k,pt;
    ifstream fin ("Variables.txt",ios::in);
    fin>>N;

    cout<<"\n\nSections' Timetable\n\n";
    ifstream fin2 ("Section.txt",ios::in);
    for(i=0; i<N; i++)
    {
	pt=0;
	fin2>>sec[i].name;
	cout<<"Section Name: "<<setw(8)<<sec[i].name;
	int x;
	fin2>>x;
	sec[i].getId(x);
	cout<<"Section ID: "<<setw(6)<<sec[i].putId();
	fin2>>sec[i].sub[4][0];
	cout<<"Optional Subject: "<<setw(6)<<conv(sec[i].sub[4][0])<<endl;

	cout<<"||===========================================================================||"<<endl;
	cout<<"||Period||  I  |  II |      | III |  IV |  V  |  VI |      | VII | VIII|  IX ||"<<endl;
	cout<<"||Timing||8:20 |9:00 | 9:40 |9:55 |10:35|11:15|11:55|12:25 |13:00|13:40|14:10||"<<endl;
	cout<<"||      ||9:00 |9:40 | 9:55 |10:35|11:15|11:55|12:25|13:00 |13:40|14:10|14:40||"<<endl;
	cout<<"||---------------------------------------------------------------------------||"<<endl;
	for(j=0; j<5; j++)
	{
	    cout<<"||";
	    switch(j)
	    {
		case 0: cout<<setw(6)<<" Mon";   break;
		case 1: cout<<setw(6)<<" Tue";   break;
		case 2: cout<<setw(6)<<" Wed";   break;
		case 3: cout<<setw(6)<<" Thu";   break;
		case 4: cout<<setw(6)<<" Fri";   break;
	    }
	    cout<<"|";
	    for(k=0; k<9; k++)
	    {
		if(k==2)
		    cout<<"|Break ";
		if(k==6)
		    cout<<"|Lunch ";

		fin2>>sec[i].tt[j][k];
		if(sec[i].tt[j][k]==11)
		    pt++;
		if(sec[i].tt[j][k]==11 && pt>1)
		    cout<<"|"<<setw(5)<<conv(15);
		else
		    cout<<"|"<<setw(5)<<conv(sec[i].tt[j][k]);
	    }
	    cout<<"||"<<endl;
	}
	cout<<"||===========================================================================||"<<endl;
	cout<<endl;
	getch();
    }
    fin2.close();

    fin>>noOfTeachers;

    cout<<"\n\nTeachers' Timetable\n\n";
    ifstream fin3 ("Teacher.txt",ios::in);
    for(i=0; i<noOfTeachers; i++)
    {
	fin3>>teacher[i].name;
	cout<<"Teacher Name: "<<setw(10)<<teacher[i].name;
	fin3>>teacher[i].id;
	cout<<"Teacher ID: "<<setw(6)<<teacher[i].id;
	fin3>>teacher[i].sub;
	cout<<"Subject: "<<setw(6)<<conv(teacher[i].sub)<<endl;

	cout<<"||===========================================================================||"<<endl;
	cout<<"||Period||  I  |  II |      | III |  IV |  V  |  VI |      | VII | VIII|  IX ||"<<endl;
	cout<<"||Timing||8:20 |9:00 | 9:40 |9:55 |10:35|11:15|11:55|12:25 |13:00|13:40|14:10||"<<endl;
	cout<<"||      ||9:00 |9:40 | 9:55 |10:35|11:15|11:55|12:25|13:00 |13:40|14:10|14:40||"<<endl;
	cout<<"||---------------------------------------------------------------------------||"<<endl;
	for(j=0; j<5; j++)
	{
	    cout<<"||";
	    switch(j)
	    {
		case 0: cout<<setw(6)<<" Mon";   break;
		case 1: cout<<setw(6)<<" Tue";   break;
		case 2: cout<<setw(6)<<" Wed";   break;
		case 3: cout<<setw(6)<<" Thu";   break;
		case 4: cout<<setw(6)<<" Fri";   break;
	    }
	    cout<<"|";
	    for(k=0; k<9; k++)
	    {
		if(k==2)
		    cout<<"|Break ";
		if(k==6)
		    cout<<"|Lunch ";

		fin3>>teacher[i].tt[j][k];
		//temp=teacher[i].tt[j][k];
		if(teacher[i].tt[j][k]!=0)
		    cout<<"|"<<setw(5)<<sec[teacher[i].tt[j][k]-1].name;
		else
		    cout<<"|"<<setw(5)<<"";
	    }
	    cout<<"||"<<endl;
	}
	cout<<"||===========================================================================||"<<endl;
	cout<<endl;
	getch();
    }
    fin3.close();

    cout<<"\n\nLabs' Timetable\n\n";
    ifstream fin4 ("Lab.txt",ios::in);
    for(i=0; i<7; i++)
    {
     int x;
	fin4>>x;
	lab[i].getSub(x);
	if(lab[i].putSub()==10 || lab[i].putSub()==14)
    {
        for(j=0; j<5; j++)
            for(k=0; k<9; k++)
                fin4>>lab[i].tt[j][k];
    }
    else
    {
	cout<<"Subject: "<<setw(6)<<conv(lab[i].putSub())<<endl;

	cout<<"||===========================================================================||"<<endl;
	cout<<"||Period||  I  |  II |      | III |  IV |  V  |  VI |      | VII | VIII|  IX ||"<<endl;
	cout<<"||Timing||8:20 |9:00 | 9:40 |9:55 |10:35|11:15|11:55|12:25 |13:00|13:40|14:10||"<<endl;
	cout<<"||      ||9:00 |9:40 | 9:55 |10:35|11:15|11:55|12:25|13:00 |13:40|14:10|14:40||"<<endl;
	cout<<"||---------------------------------------------------------------------------||"<<endl;
	for(j=0; j<5; j++)
	{
	    cout<<"||";
	    switch(j)
	    {
		case 0: cout<<setw(6)<<" Mon";   break;
		case 1: cout<<setw(6)<<" Tue";   break;
		case 2: cout<<setw(6)<<" Wed";   break;
		case 3: cout<<setw(6)<<" Thu";   break;
		case 4: cout<<setw(6)<<" Fri";   break;
	    }
	    cout<<"|";
	    for(k=0; k<9; k++)
	    {
		if(k==2)
		    cout<<"|Break ";
		if(k==6)
		    cout<<"|Lunch ";

		fin4>>lab[i].tt[j][k];
		if(lab[i].tt[j][k]!=0)
		    cout<<"|"<<setw(5)<<sec[lab[i].tt[j][k]-1].name;
		else
		    cout<<"|"<<setw(5)<<"";
	    }
	    cout<<"||"<<endl;
	}
	cout<<"||===========================================================================||"<<endl;
	cout<<endl;
	getch();
    }
    }
    fin4.close();

    fin.close();
    cout.unsetf(ios::left);
}

int main()
{
    char ch='n';
    int opt;
    do
    {
        cout<<"\nWelcome to Timetable Generator";
        cout<<"\nWould you like to  \n1) Generate Timetable  \n2) Display Timetable \n3) Exit";
        cout<<"\nEnter Option: ";
        cin>>opt;
        switch(opt)
        {
		case 1: gen();
                datafile();
                break;
		case 2: disp();
                //display();
                break;
		case 3: cout<<"Thank you for using the program.";
                getch();
                return 0;
		default: cout<<"Incorrect option.";
                 getch();
                 main();
        }
        cout<<"Run program again? (y/n) ";
        cin>>ch;
    }while (ch=='y' || ch=='Y');

    return 0;
}
