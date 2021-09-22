#include <string>
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<cstring>
using namespace std;

struct client   
{ /*client*/
	char name[20];          /*name*/
	int ordering_number;    /* Booking amount*/
	int grade;             /* class rating*/
	client *next;
};
class airline
{ /*flight information*/
private:
	char username[20];
	char password[20];
	char hanh_trinh[20];   /* Ten hanh trinh*/
	char air_num[10];       /*so hieu chuyen bay*/
	char plane_num[10];     /*so hieu may bay*/
	char day[50];            /* Flight Day (day of the week)*/
	int people_quota;       /* gioi han so nguoi*/
	double price;           /*fare*/
	int more_ticket;        /* so ve con lai*/
	char passenger_list[50];  
	char waiting_list[50];     /*A list of customers waiting for the replacement*/   
	static int number;       /*tong so chuyen bay*/
public:
	void print()
	{/*Print flight information*/
	    cout<<" Hanh Trinh::"<<hanh_trinh<<" \t So chuyen bay:"<<air_num<<"\t So hieu may bay:"<<plane_num
			<<"\n Thoi gian:"<<day<<"\t\t So ghe toi da:"<<people_quota<<"\n Gia ve:"<<price<<"\t\t So ve con lai:"<<more_ticket<<"\n\n";
	} 
	friend airline* get_airline();                   /*Read flight information in the file*/
	friend void client_list();
	friend void put_airline(airline*);
	friend void print_airline();
	friend void xacminh();
	friend void search();
	friend void booking();
	friend void refund();
	friend client* get_passenger(airline);
	friend client* get_wait(airline);
	friend void put_passenger(airline,client*);
	friend void put_wait(airline,client*);
	friend void re_price();
	friend void createaccount();
	
};

int airline::number=0;
char Name[20]="";            /*ten cua khach de dang nhap*/
airline *L;                  /* global variable, route pointer */      

void app_client(client *c,client *q)
{/*Add passengers*/
	client *p=c;
	while(p->next) p=p->next;
	p->next=q;
	q->next=NULL;
}
void xacminh()
{
	char login_password[20];
	char file_password[20];   
	char login_username[20];
	char file_username[20];
	
	fstream pull("logininfo.txt",ios::in);
	if (!pull) { 
	    cout<<"Tai file khong thanh cong!"<<endl;
	
	}
	cout<<"\nMoi dang nhap: ";
	cout<<"\nUsername: ";
	cin>>login_username;
	while(strcmp(login_username,file_username)){ 
	    pull>>file_username;
	    if(pull.eof()){   //neu den cuoi dong trong file khong tim thay
	        cout<<"Khong tim thay ten nay.Nhap lai "<<endl;
	        cout<<"Username: ";
			cin>>login_username;
			break;
	    }
	}
	pull>>file_password; 
	cout<<"Password: ";   
	cin>>login_password;
	while(strcmp(file_password,login_password)){
	    cout<<"Sai mat khau. "<<endl;
	    cout<<"Nhap lai mat khau: ";
	    cin>>login_password;
	}
	cout<<"Dang nhap thanh cong."<<endl;
	strcpy(Name,login_username);
}
void createaccount(){
	
    ofstream OFile1;  // Create Object of Ofstream
    ofstream OFile2;
    OFile1.open ("accountinfo.txt", ios::app); // Append mode
    OFile2.open ("logininfo.txt", ios::app);
    string u,p,ngaysinh,diachi,hoten;
    cout<<"Nhap username: ";cin>>u;
    cout<<"Nhap password: ";cin>>p;fflush(stdin);
    cout<<"Nhap hoten day du: ";getline (cin, hoten);fflush(stdin);
    cout<<"Nhap ngaysinh: ";getline (cin, ngaysinh);fflush(stdin);
    cout<<"Nhap diachi: ";getline (cin, diachi);fflush(stdin);

    OFile1 <<u<<" "<<hoten<<" "<<ngaysinh<<" "<<diachi<<"\n"; // Writing data to file
    OFile2<<"\n"<<u<<" "<<p;
	cout<<"Da tao thanh cong";
    OFile1.close(); 
    OFile2.close();
}
int login()
{/*log in*/
	int f;
	char password[20];       /*Administrator password*/
	cout<<"*************************log in*********************** ******\n\n";
	cout<<" 1. Khach Hang 2. Quan tri vien \n Moi Chon:";
	fflush(stdin);   /* Refresh input stream buffer */
	while(f=int(getchar())-48)
	{
		if(f==1) 
		{ 
		//	cout<<"Name:";
		cout<<"1. Tao tai khoan moi  2.Dang nhap"<<"\nMoi chon: ";
		int chon;
		cin>>chon;fflush(stdin);
		switch(chon)
		{
			case 1:
				createaccount();
				xacminh();
				cout<<"\n\t\tDang nhap thanh cong!!\n\n*********************************** ***********************\n\n";
				return 1;
				break;
			case 2:
				xacminh();	
			//cin>>Name;
				cout<<"\n\t\tDang nhap thanh cong!!\n\n*********************************** ***********************\n\n";
				return 1;
				break;
				
		}
			
		}
		else if(f==2) 
		{
		
			fflush(stdin);
		
			   
				cout<<"\n\t\tDang nhap thanh cong!!\n\n*********************************** ***********************\n\n";
				return 2;
			    
				
			
		}
		else cout<<"Moi nhap lai:";
	}
}

void search()
{/*Query operation*/
	char s[20];
	int i=0;
	cout<<"*************************Inquire*********************** ******\n\n\t\tterminal name:";
	cin>>s;
	while(i<L->number&&strcmp(s,L[i].hanh_trinh)) i++;    /* matches the terminal name in the order of the linked list */
	if(i<L->number)          
		L[i].print();
	else cout<<"\nKhong co thong tin chuyen bay nay!\n\n";
	cout<<"**********************************************************\n\n";
}
void refund()
{/* Refund operation*/
	char s[20];
	int i=0,n;
	cout<<"************************* Tra ve*********************** ******\n\n\t\tSo hieu chuyen bay:";
	cin>>s;
	while(i<L->number&&strcmp(s,L[i].air_num)) i++;       /* matches by flight number*/
	if(i<L->number)
	{/* Find this flight*/
	    client *c1=get_passenger(L[i]),*c2=get_wait(L[i]),*p=c1,*q,*r;
		while(p->next&&strcmp(Name,p->next->name)) p=p->next;  
		if(p->next)
		{/*Found the user name*/
			cout<<"Ban dang o "<<L[i].air_num<<"Chuyen bay (Hanh Trinh:"<<L[i].hanh_trinh<<")Booked"
				<<p->next->ordering_number<<"\n Nhap so luong ve van huy:";
			do
			{/*Enter the number of refunds*/
			    cin>>n;
				if(n>0&&n<=p->next->ordering_number) break;
				else cout<<"\n input error!! Please re-enter:";
			}while(1);
			if(n==p->next->ordering_number) 
			{/*All refunds*/
				r=p->next;
				q=r->next;
				p->next=q;
				delete r;	
			}
			else if(n<p->next->ordering_number) p->next->ordering_number-=n;  /*Return part of the ticket*/
			L[i].more_ticket+=n;   /* increase in votes*/
			int f=1;
			while(L[i].more_ticket&&f)
			{/* has more than one ticket and has not visited all alternate passengers*/
				p=c2;
				while(p->next&&L[i].more_ticket<p->next->ordering_number) p=p->next; 
				if(p->next)
				{
					L[i].more_ticket-=p->next->ordering_number;
					r=p->next;
				    q=r->next;
				    p->next=q;
					app_client(c1,r);
				}
				else f=0;  /*Visit */
			}
			put_passenger(L[i],c1);   /* Refresh passenger list*/
			put_wait(L[i],c2);
		}
		else cout<<"\n Loi tra ve!! Ban da khong dat ve chuyen bay nay\n";
	}
	else cout<<"\nKhong co thong tin chuyen bay !\n\n";
	cout<<"\n Tra ve thanh cong!\n";
	cout<<"**********************************************************\n\n";
	put_airline(L);
}
void booking()
{/* Booking operation*/
	char s[20];
	int i=0,n,y,g;
	cout<<"************************* Booking ************************ *******\n\n\t\tFlight number:";
	cin>>s;
	while(i<L->number&&strcmp(s,L[i].air_num)) i++;
	if(i<L->number)
	{/* Find the flight*/
		L[i].print();
		client *c1=get_passenger(L[i]);
		client *c2=get_wait(L[i]);
		cout<<" Lua chon hang ghe (1: First class, 2: Normal class, 3: Economy class):";cin>>g;
		cout<<"nhap so luong ve: ";
	    do
	    {
		
	
			cin>>n;
	        if(n<=L[i].people_quota) break;
			else
				cout<<"Loi!! Da vuot qua so ghe con lai: ("<<L[i].people_quota<<"),nhap lai:";
		}while(1);

		if(L[i].more_ticket)
		{
			if(n<=L[i].more_ticket) 
			{
				client *p=new client;
				strcpy(p->name,Name);
				p->ordering_number=n;
				L[i].more_ticket-=n;
				p->grade=g;

				app_client(c1,p);
				cout<<"\n Hoan tat mua ve!\n";
			}
			else if (n>L[i].more_ticket)
			{
				int x;
				client *p1=new client,*p2=new client;
			    cout<<"\n\n1. Mua nhung ve con lai:  "<<L[i].more_ticket<<"\n2. Mua va vao hang doi:  "<<L[i].more_ticket<<" "<<n-L[i].more_ticket<<"\n3. Vao hang doi:  "<<n<<"\n, Ban co muon tiep tuc?:";
				cin>>x;
				switch(x)
				{
				case 1:
			        strcpy(p1->name,Name);
					p1->ordering_number=L[i].more_ticket;
					L[i].more_ticket=0;
		            p1->grade=g;
					app_client(c1,p1);
					cout<<"\n Hoan thanh mua ve!\n";
					break;
				case 2:
			        strcpy(p1->name,Name);
					p1->ordering_number=L[i].more_ticket;
		            p1->grade=g;
					app_client(c1,p1);

					strcpy(p2->name,Name);
				    p2->ordering_number=n-L[i].more_ticket;
					L[i].more_ticket=0;
				    p2->grade=g;
					app_client(c2,p2);

					cout<<"\n Hoan thanh mua ve!\n";
					break;
				}
			}
		}
		else 	
		{
			cout<<"\n Khong con ve! Ban co muon vao hang cho khong? (1: Co 0: Khong)";cin>>y;
			if(y) 
			{
				client *p=new client;
				strcpy(p->name,Name);
				p->ordering_number=n;
				p->grade=g;
				app_client(c2,p);
			}
		}
		put_passenger(L[i],c1);    
		put_wait(L[i],c2);
	}
	else cout<<"\nNo flight information!\n\n";
	cout<<"\n**********************************************************\n\n";
	put_airline(L);
}

void put_wait(airline l,client *c)
{

    fstream f;
	client *p=c->next;
	f.open(l.waiting_list,ios::out|ios::trunc);
	while(p)
	{
		f<<p->name<<" "<<p->ordering_number<<" "<<p->grade<<'\n';
		p=p->next;
	}
	f.close();
}
client* get_passenger(airline l)
{
	fstream f;int i=0;
	client *c=new client,*p=new client,*q=c;
	f.open(l.passenger_list,ios::in);
	while(f>>p->name>>p->ordering_number>>p->grade)
	{
		q->next=p;
		p=new client;
		q=q->next;
	}
	q->next=NULL;
	f.close();
	return c;
}
void put_passenger(airline l,client *c)
{
	fstream f;
	client *p=c->next;
	f.open(l.passenger_list,ios::out|ios::trunc);
	while(p)
	{
		f<<p->name<<" "<<p->ordering_number<<" "<<p->grade<<'\n';
		p=p->next;
	}
	f.close();
}
client* get_wait(airline l)
{
	fstream f;int i=0;
	client *c=new client,*p=new client,*q=c;
	f.open(l.waiting_list,ios::in);
	while(f>>p->name>>p->ordering_number>>p->grade)
	{
		q->next=p;
		p=new client;
		q=q->next;
	}
	q->next=NULL;
	f.close();
	return c;
}
airline* get_airline()
{
	fstream f;int i=0;
	airline *line=new airline [100];
	f.open("Flight Information.txt",ios::in);
	while(f>>line[i].hanh_trinh>>line[i].air_num>>line[i].plane_num>>
		line[i].day>>line[i].people_quota>>line[i].price>>line[i].more_ticket
		>>line[i].passenger_list>>line[i].waiting_list)
			i++;
	line->number=i;
	f.close();
	return line;
}
void put_airline(airline *L)
{
	fstream f;int i;
	f.open("Flight Information.txt",ios::out);
	
	for(i=0;i<L->number;i++)  f<<L[i].hanh_trinh<<" "<<L[i].air_num<<" "
		<<L[i].plane_num<<" "<<L[i].day<<" "<<L[i].people_quota<<" "<<
		L[i].price<<" "<<L[i].more_ticket<<" "<<L[i].passenger_list<<" "<<L[i].waiting_list<<'\n';
	f.close();
}
void print_airline()
{
	L=get_airline();
	int i=0;
	cout<<"*************************flight information********************** ***\n\n";
	for(int i=0;i<L->number;i++)
		L[i].print();
	cout<<"\n**********************************************************\n\n";
}
void client_list()
{
	int i=0;char s[20];
	char g[30];
	cout<<"************************* Passenger List********************** ***\n\n\t\tFlight number:";
	cin>>s;
	while(i<L->number&&strcmp(s,L[i].air_num)) i++;
	if(i<L->number)
	{
        client c;
	    fstream f;
	    f.open(L[i].passenger_list,ios::in);
		cout<<"\n List of passengers who have purchased tickets: \n";
		while(f>>c.name>>c.ordering_number>>c.grade)
		{
			switch(c.grade)
			{
			case 1: strcpy(g,"First Class");break;
			case 2: strcpy(g,"normal cabin");break;
			case 3: strcpy(g,"Economy class");
			}
			cout<<"\tName:"<<c.name<<"\t class rating:"<<g<<"\tBuy tickets:"<<c.ordering_number<<endl;
		}
		f.close();
		f.open(L[i].waiting_list,ios::in);
		cout<<"\n Danh sach khach hang doi dat ve: \n";
		while(f>>c.name>>c.ordering_number>>c.grade)
		{
			switch(c.grade)
			{
			case 1:strcpy(g,"First Class");break;
			case 2:strcpy(g,"normal cabin");break;
			case 3:strcpy(g,"Economy class");
			}
			cout<<"\tName:"<<c.name<<"\t class rating:"<<g<<"\t booked votes:"<<c.ordering_number<<endl;
		}
	    f.close();
	}
	else cout<<"\nNo flight information!\n\n";
	cout<<"\n**********************************************************\n\n";
	
}
void re_price()
{
	int i=0,p;char s[20];
	cout<<"*************************Modify fares********************* ****\n\n\t\tFlight number:";
	cin>>s;
	while(i<L->number&&strcmp(s,L[i].air_num)) i++;
	if(i<L->number)
	{
		cout<<" Terminal name:"<<L[i].hanh_trinh<<"\t Aircraft number:"<<L[i].plane_num
			<<"\n\n\t Original fare:"<<L[i].price<<"\n\t New fare:";
		cin>>p;
		L[i].price=p;
		cout<<"\n Modify fare completion \n";
	}
	else cout<<"\nNo flight information!\n\n";
	put_airline(L);
	cout<<"\n**********************************************************\n\n";
}
int form1()
{
	int s;
	cout<<"*************************User Interface********************** ***\n\n";
	cout<<" 1. Tim chuyen bay \t 2.Thong tin tat ca chuyen bay \t 3. Booking \t 4. Huy ve 0. Logout \n\n\t\tSelect operation:";
	fflush(stdin);
	while(s=int(getchar())-48)
	{
	    if(s>=0&&s<=3) 		
		{
			cout<<"\n**********************************************************\n\n";
			return s;
		}
		else cout<<"\tEnter error!! \n\tPlease re-select the operation:";
	}
	
}
int form2()
{
	int s;
	cout<<"***********************Administrator interface*********************** **\n\n";
	cout<<" 1. Flight Information\t 2. Passenger List\t 3. Modify Ticket Price 0. Logout \n\n\t\tSelect Operation:";
	fflush(stdin);
	while(s=int(getchar())-48)
	{
	    if(s>=0&&s<=3) 		
		{
			cout<<"\n**********************************************************\n\n";
			return s;
		}
		else cout<<"\tEnter error!! \n\tPlease re-select the operation:";
	}
}
int main()
{
	L=get_airline();
	do
	{
		int f=1;
	    switch(login())
	    {
	    case 1:
			system("pause");
			system("cls");
			do
			{
		        switch(form1())
	            {
		        case 1: 
					system("cls");
				    search();
					system("pause");
					system("cls");
					break;
				case 2:
					system("cls");
				    print_airline();
					system("pause");
					system("cls");
					break;
				case 3: 
					system("cls");
					booking();
					system("pause");
					system("cls");
					break;
				case 4:/*Refund*/
					system("cls");
					refund();
					system("pause");
					system("cls");
					break;
				case 0:
					f=0;
					system("cls");
	            }
			}while(f);
			break;
		case 2:
			system("pause");
			system("cls");
			do
			{
		        switch(form2())
	            {
		        case 1:
					system("cls");
				    print_airline();
					system("pause");
					system("cls");
					break;
				case 2:
					system("cls");
					client_list();
					system("pause");
					system("cls");
					break;
				case 3:
					system("cls");
					re_price();
					system("pause");
					system("cls");
					break;
				case 0:
					f=0;
					system("cls");
	            }
			}while(f);
	    }

	}while(1);
}

