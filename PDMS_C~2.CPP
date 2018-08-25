
/* Computer Science Project: Diet Management in a Hospital

    Compiled using Turbo C++ compiler

   Code by:

   Ananya Ravikumar

   Deepti R.

   Ragul Viknesh

   Saumya Suri

   class: XII

*/

/*

Patient Diet Management System allows a hospital patient’s diet to be planned according
to his or her medical requirements.

It is intended for use by the patient’s dietician and the hospital record keeper.

It is capable of storing patient details and meal orders and can perform basic functions such as addition, deletion and modification of the same.

*/



#include<graphics.h>

#include<dos.h>

#include<fstream.h>

#include<conio.h>

#include<stdio.h>

#include<string.h>

#include<iomanip.h>

#include<process.h>

#include <stdlib.h>

#include<ctype.h>

#define MAXMENU 10

#define MAXCHAR 20

#define MAXDISLEN 50

#define MAXCONT 11





#define ENTER_PATIENT 1

#define EDIT_PATIENT 2

#define ORDER_MEAL 3

#define VIEW_ORDERS  4

#define VIEW_PATIENT  5

#define DELETE_PATIENT 6

#define DUMP_PATIENT  7

#define EXIT 8

#define REMOVE 9

#define TRUE 1

#define FALSE 0



#define BREAKFAST 1

#define LUNCH 2

#define DINNER 3

#define OTHER 4



ifstream ifile;

ofstream ofile;

fstream efile;

struct dt
{ int d,m,y;};

dt getdt()	// function for date validation
{
	dt d1;
	char dtbuff[5];

	enterDAY:
	cout<<endl<<"Enter day:";
	cin>>dtbuff;

	for(int i=0; i<strlen(dtbuff); ++i)
	{
	if(!isdigit(dtbuff[i]))
	   {
		cout<<"Invalid Day. Re-Enter";
		goto enterDAY;
	    }
	}
	d1.d=atoi(dtbuff);

	enterMONTH:

	cout<<"Enter month :";
	cin>>dtbuff;
	for(i=0; i<strlen(dtbuff); ++i)
	{
		if(!isdigit(dtbuff[i]))

		{ cout<<"Invalid Month. Re-Enter";
		  goto enterMONTH;
		}
	}

	 d1.m=atoi(dtbuff);

	enterYEAR:

	cout<<"Enter Year:";
	cin>>dtbuff;
	for(i=0; i<strlen(dtbuff); ++i)
	{
		if(!isdigit(dtbuff[i]))

		{
		cout<<"Invalid Year. Re-Enter";
		goto enterYEAR;
		}
	}
	d1.y=atoi(dtbuff);

	return d1;
}

int checkdt(int d , int m , int y)   // function for date validation
{

	if (d<0 || d>31 || m<0 || m>12 ||y<0)
	return 0;

	if((m==4 || m==6 || m==9 || m==11) && d>30)
	 return 0;

	 if (m==2)
	 {
		if (y%4==0)
		{
		if (d>29) return 0;
		}
		else
		if (d>28) return 0;
	}
	return 1;
}





class patient_record

{

protected:

	char name[MAXCHAR];

	int pat_ID;	// patient ID

	int ward_no;

	int age;

	char sex;

	char disease[MAXDISLEN];

	dt doa;             // struct of type dt.

	char contact[MAXCONT];

	public:

		void print_record();     // to print patient details

		void new_entry();	 // to enter a new record

		void edit_record();	 // to edit patient record

		void delete_record();	 //to delete record

		void genid();	 // to generate patient it.

		int  getid(){ return pat_ID; }    //accessor

};

void patient_record :: print_record()
{
	

	cout<<"\t\t\t\tPatient record(s):\n\n";

	cout<<"Patient ID: "<<pat_ID << '\n';

	cout<<"Name: ";puts(name);

	cout<<"Sex: "; putchar(sex); cout << '\n';

	cout<<"Ward number: "<<ward_no << '\n';

	cout<<"Age: "<<age << '\n';

	cout<<"Date of admission [ddmmyy]: "<<doa.d<<"-"<<doa.m<<"-"<<doa.y << '\n';

	cout<<"Diseases/allergies: ";puts(disease);

	cout<<"Contact no: "<<contact<<'\n';

}

void patient_record::new_entry()

{
	char buf[80];
	int i;

	cout<<"\nEnter new patient record below.";

	enterNAME:

	cout<<"\nName: ";

	gets(buf);
	int nameflag=0;
	 for( i=0; i<strlen(buf); ++i)
	     {
		if (!isalpha(buf[i])||(strlen(buf)==0))
		    nameflag=-1; break;
	      }
	if (nameflag==-1)
	{
	 cout<<"Invalid Name. Re-Enter Name";
	 goto enterNAME;
	}

	strcpy(name,buf);

	enterSEX:

	cout<<"\nGender (m/f) : ";

	gets(buf);

	if (buf[0]!='m' && buf[0] != 'M'&& buf[0]!='f'&& buf[0]!='F')
	{  cout<<"Invalid Entry. Re-Enter gender";
	   goto enterSEX;
	}

	if (buf[0] == 'm' || buf[0] == 'M')
		sex = 'm';
	else
		sex = 'f';



	enterWARD:
	//int wardflag=1;

	cout<<"\nWard number: (DDD) :";

	gets(buf);
	if(strlen(buf)!=3)	{cout<<"\nInvalid ward number"; goto enterWARD;}
	for( i=0; i<strlen(buf); ++i)
	{
	if (isdigit(buf[i]))
		{break;}
	}

	ward_no = atoi(buf);

	enterAGE:

	cout<<"\nAge: ";
	gets(buf);

	int ageflag=0;
	for( i=0; i<strlen(buf); ++i)
	{
	if (isdigit(buf[i]))
	ageflag=1;
	else
	{ ageflag=0; break;}
	}
	if (ageflag ==0)
	{
	 cout<<"Enter only positive integers";
	getch();
	goto enterAGE;
	}
	age = atoi(buf);

	enterDISEASE:

	cout<<"\nDisease / Allergies: ";

	gets(buf);
	int disflag = 0;
	for( i=0; i<strlen(buf); ++i)
	{
	 if (!isalpha(buf[i])||(strlen(buf)==0))
	      disflag=-1; break;
	}
	if (disflag==-1)
	{
	cout<<"Invalid disease. Re-enter disease/ allergy\n";
	goto enterDISEASE;
	}

	strcpy(disease,buf);

	enterDOA:

	dt buffdt;

	cout<<"\nDate of admission(ddmmyy) :";

	buffdt=getdt();

	if (checkdt(buffdt.d, buffdt.m, buffdt.y)==0)
	{
	 cout<<"Invalid dt. Re-Enter";
	 goto enterDOA;
	     }

	doa.d=buffdt.d;
	doa.m=buffdt.m;
	doa.y=buffdt.y;


	enterPHONE:
	//int phoneflag=0;

	cout<<"\nEmergency Phone (10 digits) : ";

	gets(buf);
	if(strlen(buf)!=10)	{cout<<"\nInvalid phone number"; goto enterPHONE;}
	for( i=0; i<strlen(buf); ++i)
	{
	if (!isdigit(buf[i]))
		{break;}

	}

	strcpy(contact,buf);

	genid();

	cout<<"\nPatient ID: "<<pat_ID<<'\n';

}


void patient_record :: edit_record()

{       char edit, buf[80];

	cout<<"Edit patient name? yes:y, no:n  ";

	cin>>edit;

	if(edit=='y')
	{
		enterNAME:

		cout<<"\nName: ";

		gets(buf);

		int nameflag=0;
		for(int i=0; i<strlen(buf); ++i)
			{
		if (!isalpha(buf[i])||(strlen(buf)==0))
		    nameflag=-1; break;
			}
		if (nameflag==-1)
		{
		 cout<<"Invalid Name. Re-Enter Name";
		goto enterNAME;
		}

		strcpy(name,buf);
	}



	cout<<"Edit sex of patient? yes:y, no:n";

	cin>>edit;

	if(edit=='y')
	{
		enterSEX:
		cout<<"\nGender (m/f) : ";

		gets(buf);

		if (buf[0]!='m' && buf[0] != 'M'&& buf[0]!='f'&& buf[0]!='F')
		{  cout<<"Invalid Entry. Re-Enter gender";
		 goto enterSEX;
		}

		if (buf[0] == 'm' || buf[0] == 'M')
		sex = 'm';
		else
		sex = 'f';

	}



	cout<<"Edit ward no? yes:y, no:n  ";

	cin>>edit;

	if(edit=='y')
	{
		enterWARD:
		//int wardflag=1;

		cout<<"\nWard number: (DDD) :";

		gets(buf);
		if(strlen(buf)!=3)
			{cout<<"\nInvalid ward number"; goto enterWARD;}
		for(int i=0; i<strlen(buf); ++i)
		{
			if (isdigit(buf[i]))
				{ break;}
		}
		ward_no = atoi(buf);

	}



	cout<<"Edit age? yes:y, no:n  ";

	cin>>edit;

	if(edit=='y')
	{

		enterAGE:

		cout<<"\nAge: ";
		gets(buf);

		int ageflag=0;
		for(int i=0; i<strlen(buf); ++i)
		{
			if (isdigit(buf[i]))
			ageflag=1;
			else
			{ ageflag=0; break;}
		}
		if (ageflag ==0)
		{
		 cout<<"Enter only positive integers";
		 getch();
		 goto enterAGE;
		}
		age = atoi(buf);
	}



	cout<<"Edit disease? yes:y, no:n  ";

	cin>>edit;

	if(edit=='y')
	{
		enterDISEASE:

		cout<<"\nDisease/Allergies: ";

		gets(buf);
		int disflag = 0;
		for(int i=0; i<strlen(buf); ++i)
		{
			if (!isalpha(buf[i])||(strlen(buf)==0))
			disflag=-1; break;
		}
		if (disflag==-1)
		{
		cout<<"Invalid Name. Re-Enter Disease/ Allergy\n";

		goto enterDISEASE;
		}

		strcpy(disease,buf);

	}



	cout<<"Edit date of admission? yes:y, no:n  ";

	cin>>edit;

	if(edit=='y')
	{
		enterDOA:

		dt buffdt;

		cout<<"\nDate of admission(ddmmyy) :";

		buffdt=getdt();

		if (checkdt(buffdt.d, buffdt.m, buffdt.y)==0)
		{
		cout<<"Invalid date. Re-Enter";
		goto enterDOA;
		}

		doa.d=buffdt.d;
		doa.m=buffdt.m;
		doa.y=buffdt.y;
	}



	cout<<"Edit emergency contact number ? yes:y, no:n  ";

	cin>>edit;

	if(edit=='y')
	{
		enterPHONE:
		//int phoneflag=0;

		cout<<"\n Emergency Phone (10 digits) : ";

		gets(buf);
		if(strlen(buf)!=10)
			{cout<<"\nInvalid number"; goto enterPHONE;}
		for(int i=0; i<strlen(buf); ++i)
		{
			if (!isdigit(buf[i]))
				{break;}
		}

		strcpy(contact,buf);
	}

	cout<<"\nPatient ID: "<<pat_ID<<'\n';

}

void patient_record :: genid()		//for patient ID

{
	efile.open("idfile.DAT",ios::in|ios::nocreate);

	if (!efile)
	{

		pat_ID = 1;

	} else

	{

		efile >> pat_ID;

		pat_ID +=1;



	}

	efile.close();

	remove("idfile.DAT");

	efile.open("idfile.DAT",ios::out);
	if (!efile)
	{
		cout << "Grave error! idfile.DAT open failure\n";
		getch();
		exit(-1);
	}
	efile >> pat_ID;

	efile.close();





}



class mealOrder

{       protected:

	int pat_id;

	char typemeal[MAXCHAR];

	char bev[MAXCHAR];

	char maincourse[MAXCHAR];

	char comments[100]; //for extra comments by dietician

	int choiceofmeal;



public:



	void print_meal();

	void order_meal(int);

	int  getid(){ return pat_id;}

	void setid(int i){ pat_id=i;};

	void get_choiceofmeal();

	int ret_cmeal();

};







void mealOrder:: print_meal()

{



     cout<<"Your order for patient ID " << pat_id << '\n';



     cout <<setw(MAXCHAR)<<"Meal Type:"<<setw(MAXCHAR)<< typemeal<<'\n'

	  <<setw(MAXCHAR)<<"Beverage:"<<setw(MAXCHAR)<< bev<<'\n'

	 <<setw(MAXCHAR)<<"Main course:"<<setw(MAXCHAR)<<maincourse<<'\n';



     cout<<"Comments: "<<comments<<'\n';

     cout<<"Press enter key to continue..."<<'\n';

     getch();

}





void mealOrder:: order_meal(int pid)

{
	pat_id = pid;

	get_choiceofmeal();



	char dinner_maincourse[][20] = {"Pasta Salad", "Chapati",  "Ragi Mudde", "Dal and Rice", "Dalia"};
	char dinner_beverage[][20] = {"Buttermilk", "Juice of the day", "Tea", "Coffee", "Coconut water"};



	char lunch_maincourse[][20] = {"Veg Pulao", "Roti", "Rajma and Rice", "Dal and Rice", "Broken Wheat"};
	char lunch_beverage[][20] = {"Juice of the day", "Tea", "Coffee", "Coconut water"};



	char breakfast_maincourse[][20] = {"Idli Vada", "Plain Dosa", "Corn Flakes"};
	char breakfast_beverage[][20] = {"Tea", "Coffee", "Milk", "Juice of the day"};

	char other_maincourse[][20]={"Salad","Biscuits","Yoghurt"};
	char other_beverage[][20]={"Tea","Coffee","Juice of the day"};

	int bev_index;

	switch (choiceofmeal) {

		case BREAKFAST:

			int i;

			int num_breakfast, breakfast_index;

			num_breakfast = sizeof(breakfast_maincourse) /

			    sizeof(breakfast_maincourse[0]);



			cout << "Breakfast items\n";

			for (i=0;i<num_breakfast;i++) {

				cout << i+1 <<". "<< breakfast_maincourse[i] <<'\n';

			}

			cin >> breakfast_index;

			breakfast_index = breakfast_index - 1;

			num_breakfast = sizeof(breakfast_beverage)/sizeof(breakfast_beverage[0]);

			for (i=0;i<num_breakfast;i++) {

				cout << i+1 <<". "<< breakfast_beverage[i] << '\n';

			}

			cin >> bev_index;

			bev_index = bev_index - 1;

			strcpy(typemeal , "Breakfast");

			strcpy(maincourse , breakfast_maincourse[breakfast_index]);

			strcpy(bev , breakfast_beverage[bev_index]);



			break;

		case LUNCH:



			int num_lunch, lunch_index;

			num_lunch = sizeof(lunch_maincourse) /

			    sizeof(lunch_maincourse[0]);



			cout << "Lunch items\n";

			for (i=0;i<num_lunch;i++) {

				cout << i+1 << lunch_maincourse[i] <<'\n';

			}

			cin >> lunch_index; lunch_index = lunch_index - 1;

			num_lunch= sizeof(lunch_beverage)/sizeof(lunch_beverage[0]);

			for (i=0;i<num_lunch;i++) {

				cout << i+1 << lunch_beverage[i] << '\n';

			}

			cin >> bev_index; bev_index = bev_index - 1;

			strcpy(typemeal , "Lunch");

			strcpy(maincourse , lunch_maincourse[lunch_index]);

			strcpy(bev , lunch_beverage[bev_index]);



			break;

		case DINNER:



			int num_dinner, dinner_index;

			num_dinner = sizeof(dinner_maincourse) /

			    sizeof(dinner_maincourse[0]);



			cout << "Dinner items\n";

			for (i=0;i<num_dinner;i++) {

				cout << i+1 << dinner_maincourse[i] <<'\n';

			}

			cin >> dinner_index; dinner_index = lunch_index - 1;

			num_dinner= sizeof(dinner_beverage)/sizeof(dinner_beverage[0]);

			for (i=0;i<num_dinner;i++) {

				cout << i+1 << dinner_beverage[i] << '\n';

			}

			cin >> bev_index; bev_index = bev_index - 1;

			strcpy(typemeal , "Dinner");

			strcpy(maincourse , dinner_maincourse[dinner_index]);

			strcpy(bev , dinner_beverage[bev_index]);




			break;

		case OTHER: int num_other, other_index;

			num_other = sizeof(other_maincourse) /

			    sizeof(other_maincourse[0]);



			cout << "Miscellaneous items\n";

			for (i=0;i<num_other;i++) {

				cout << i+1 <<". "<< other_maincourse[i] <<'\n';

			}

			cin >> other_index;

			other_index = other_index - 1;

			num_other = sizeof(other_beverage)/sizeof(other_beverage[0]);

			for (i=0;i<num_other;i++) {

				cout << i+1 <<". "<< other_beverage[i] << '\n';

			}

			cin >> bev_index;

			bev_index = bev_index - 1;

			strcpy(typemeal , "Other");

			strcpy(maincourse , other_maincourse[other_index]);

			strcpy(bev , other_beverage[bev_index]);



			break;



		default:  cout<<"Invalid option\n"; break;

	}



	cout<<endl<<endl;





	cout<<"Enter special comments if any:"; gets(comments);

}









void mealOrder::get_choiceofmeal()

   { cout<<"Enter meal type"<<'\n'

	 <<"1.Breakfast"<<'\n'

	 <<"2.Lunch"<<'\n'

	 <<"3.Dinner"<<'\n'

	 <<"4.Other"<<'\n';

	 do {

		cin>>choiceofmeal;

		if (choiceofmeal <1 || choiceofmeal > 4) cout << "Invalid choice!";

	    } while(choiceofmeal <1 || choiceofmeal > 4)  ;



   }

int mealOrder:: ret_cmeal() { return choiceofmeal;}





void main()

{
	ifile.open("pat_rec.DAT",ios::in|ios::binary);
	ifile.close();
	ifile.open("pmeal.DAT",ios::in|ios::binary);
	ifile.close();

       int gd=DETECT,gm;

       initgraph(&gd,&gm,"c:\\tc\\bgi");

	int opt,id;

	int found;

	mealOrder  mlist;

	patient_record plist;


		settextstyle(0,0,5.5);

		outtextxy(150,100,"PATIENT");

		outtextxy(200,150,"DIET");
		outtextxy(100,200,"MANAGEMENT");
		outtextxy(170,250,"SYSTEM");
	delay(3000);



	  begin:

clrscr();

	  textmode(2);
	  textbackground(BLACK);
	  textcolor(BLUE);

	  clrscr();
	  gotoxy(25,3);
	  cprintf("*** Patient Diet Management System ***");

	  gotoxy(25,6);
	  cprintf("Please select an option:");

	  gotoxy(25,8);
	  cprintf("1. Patient registration");

	  gotoxy(25,10);
	  cprintf("2. Edit patient record");

	  gotoxy(25,12);
	  cprintf("3. Order meals");

	  gotoxy(25,14);
	  cprintf("4. View meal orders");

	  gotoxy(25,16);
	  cprintf("5. View patient records");

	  gotoxy(25,18);
	  cprintf("6. Delete patient records");

	  gotoxy(25,20);
	  cprintf("7. Dump  patient records");

	  gotoxy(25,22);
	  cprintf("8. Exit");

	  gotoxy(25,24);
	  cprintf("9. Remove database!");

	cin>>opt;




	switch (opt)    {

		  case ENTER_PATIENT:          //to enter patient details

			/*
				- Calls function to allow input of patient details.
				- Stores entered information in patient database, pat_rec.DAT
			*/



			ofile.open("pat_rec.DAT",ios::binary|ios::app); /* patient database */

			if (!ofile) {
				cout << "Grave error! pat_rec.DAT open failure\n";
				getch();
				goto begin;
				    }
			plist.new_entry();

			ofile.write((char*)&plist, sizeof(plist));

			ofile.close();

			cout << "Enter to continue ..."; getch();

			clrscr();

			goto begin;





		     case EDIT_PATIENT:           //to edit patient details

			/*
				- Takes patient ID of record to be modified from user.
				- Reads pat_rec.DAT to find a match.
				- If match is found, a function to edit patient details is called.
			*/

			long  p;

			cout<<"Enter patient ID"<<'\n';

			cin>>id;

			efile.open("pat_rec.DAT",ios::binary|ios::in|ios::out);
			if (!efile) {
				cout << "Grave error! Database failure\n";
				getch();
				goto begin;
				     }


			while(!efile.eof())

			{

				p=efile.tellg();

				efile.read((char*)&plist,sizeof(plist));

				if(efile.eof()){break;}

				if(id==plist.getid())

				{       cout << "Existing Record:\n";

					plist.print_record();

					cout << "Now enter new data:\n";

					plist.edit_record();

					efile.seekp(p);  cout<<p<<endl;

					efile.write((char*)&plist,sizeof(plist));

					plist.print_record();

					cout << "Enter to continue ...";

					getch();

					found=TRUE;

					break;

				}

			}



			if(!found){ cout<<"No ID matches given ID";}

			efile.close();

			cout << "Enter to continue ...";

			getch();

			clrscr();

			goto begin;



		case ORDER_MEAL:         //  to order a meal

			/*   -Takes patient ID from user, looks for this patient's record
				  in the pat_rec.DAT  and obtains the details.

				 -Prints the details so that dietician is aware of patient's
				  allergies, etc. and can select a meal.
				
				- Stores meal ordered in pmeal.DAT

			*/



			int pat_id;

			cout<<"Enter patient ID"<<'\n'; cin>>pat_id;

			ifile.open("pat_rec.DAT",ios::binary|ios::in);
			if (!ifile) {
				cout << "Grave error! Database failure\n";
				getch();
				goto begin;
				    }
			efile.open("pmeal.DAT",ios::binary|ios::app|ios::in);

			if (!efile) {
				cout << "Grave error! pmeal.DAT failure\n";
				getch();
				goto begin;
			}
			found = FALSE;

			while(!ifile.eof() && !found)

				{  ifile.read((char*)&plist,sizeof(plist));

					if(ifile.eof())	break;

					if(pat_id==plist.getid()) { /* Found the patient! */

						found = TRUE;

						plist.print_record();      //prints pat details

						mlist.order_meal(pat_id);

						mlist.print_meal();

					   }

			       }

			if (ifile.eof() && !found) {

				cout<<"Sorry, patient ID " << pat_id << " was not found" << "\n";

			} else {

				efile.write((char*)&mlist,sizeof(mlist));//writes order to file

			}

			efile.close();



			ifile.close();



			cout << "Enter to continue ..."; getch();

			clrscr();

			goto begin;



	case VIEW_ORDERS:   			// To view all patient orders for a given meal type.


			/*
				- Takes meal type (breakfast/lunch/dinner)from user.
				- Reads file meal.DAT for find orders with matching meal type.
				- All such orders are printed.
				-‘found’ keeps track of number of matching orders found.
			*/

			int meal_type;



			cout<<"Printing all patient orders - select the meal type :"<<'\n'

			    <<"1. Breakfast"<<'\n'

			    <<"2. Lunch"<<'\n'

			    <<"3. Dinner"<<'\n';



			cin>>meal_type;

			ifile.open("pmeal.DAT",ios::binary|ios::in);
			if (!ifile) {
				cout << "Grave error! pmeal.DAT open failure\n";
				getch();
				goto begin;
			}
			found = 0;

			while(!ifile.eof())

			{



				ifile.read((char*)&mlist,sizeof(mlist));

				if(ifile.eof())		break;

				if(meal_type==mlist.ret_cmeal())

				 {

					mlist.print_meal();

					found++;

				 }



			 }



			if(found <1){cout<<"No patient orders match meal type"<<'\n';}

			else
			{

				cout << found << " meals of selected type were found." << '\n';

			}

			cout << "Enter to continue ..."; getch();

			clrscr();

			goto begin;



	case VIEW_PATIENT:         //to view given patient record

			/*
				-Takes Patient ID of patient record to be viewed from user.
				- Reads pat_re.DAT and searches for a match,
				-If match is found, record is printed.
			*/


			found=0;

			cout<<"Enter patient ID"<<'\n';

			cin>>id;

			ifile.open("pat_rec.DAT",ios::binary|ios::in);

			if (!ifile) {
				cout << "Grave error! No database!\n";
				getch();
				goto begin;
			}

			while(!ifile.eof() && !found)

			{            ifile.read((char*)&plist,sizeof(plist));
				     if(ifile.eof()){break;}
				if(id==plist.getid())

				{	plist.print_record();

					found = 1;

				}

			}

			ifile.close();

			if(found==0)

			{

				cout<<"Sorry, patient id"<< id << " could not be found" << '\n';

			}



			cout << "Enter to continue ..."; getch();

			clrscr();

			goto begin;



	case DELETE_PATIENT:         //to delete a record


			/*
				-Takes Patient ID of record to be deleted from user.
				-Reads file pat_rec.DAT and meal.DAT to find entries with a matching patient ID.
				- If a match is found, the record is printed under ‘Record to be deleted’.
				-All entries in except matching ones are copied into temporary files (temp1.DAT for patient 					 records and temp2.DAT for meal orders). 
				-pat_rec.DAT and meal.DAT are deleted
				-temp1.DAT is renamed as pat_rec.DAT and temp2.DAT is renamed as pmeal.DAT
			*/

			int foundrec=0,foundmeal=0;
			cout<<"Enter patient ID"<<'\n';

			cin>>id;

			ifile.open("pat_rec.DAT",ios::binary|ios::in);

			if (!ifile) {
				cout << "Grave error! Database failure\n";
				getch();
				goto begin;
			}
			ofile.open("temp.DAT",ios::binary|ios::app);

				if (!ofile) {
				cout << "Grave error! temp.DAT open failure\n";
				getch();
				goto begin;
			}
			

			while(!ifile.eof())

			{     ifile.read((char*)&plist,sizeof(plist));

				if (ifile.eof()) break;

				if(id==plist.getid())
				{
					foundrec=1; 

					cout << "Record to be deleted...\n";

					plist.print_record();	

				}

				else 

				{       ofile.write((char*)&plist,sizeof(plist)); 		}


			}              //end of while

			if (foundrec==0) { cout<<"Patient record corresponding to given ID not found";
								goto begin;
							}

			ofile.close();

			ifile.close();

			remove("pat_rec.DAT");

			rename("temp.DAT","pat_rec.DAT");

			ifile.open("pmeal.DAT",ios::binary|ios::in);

			if(!ifile){ cout<<"No meals ordered. Patient details deleted. \n ";
				    getch();
				    goto begin;
				    }

			ofile.open("temp1.DAT",ios::binary|ios::app);
			if (!ofile) {
				cout << "Grave error! temp1.dat open failure\n";
				getch();
				goto begin;
			}




			while(!ifile.eof())

			{       ifile.read((char*)&mlist,sizeof(mlist));

				if (ifile.eof()) break;

				if(id==mlist.getid()){ foundmeal=1;}



				else

				{       ofile.write((char*)&mlist,sizeof(mlist));   }



			}

			ofile.close();

			ifile.close();



			remove("pmeal.DAT");

			rename("temp1.DAT","pmeal.DAT");

			if(foundrec==1&& foundmeal==1) cout<<"Record " << "for id " << id << "successfully deleted"<<'\n';

			else cout<<"No meals match given ID. Patient Details deleted."<<'\n';

			cout << "Enter to continue ..."; getch();

			clrscr();
			ifile.open("pat_rec.DAT",ios::in|ios::binary);
			ifile.close();
			ifile.open("pmeal.DAT",ios::in|ios::binary);
			ifile.close();


			goto begin;





	case DUMP_PATIENT:
			
			/* 
				-Reads file pat_rec.DAT and prints all patient records found.
			     -total stores number of records found.
			*/

			int done = FALSE;

			int total = 0;

			ifile.open("pat_rec.DAT",ios::in|ios::binary);
			if (!ifile) {
				cout << "Grave error! Database failure\n";
				getch();
				goto begin;
			}
			do {

				ifile.read((char *)&plist,sizeof(plist));

				if (ifile.eof()) done = TRUE; else {

					cout << "--------------\n";

					plist.print_record();				

					total++;

					cout << "Enter return ...";

					getch();

				}

			} while (!done);

			cout << "\n\n *** Found " << total << " records" << "\n\n";

			cout << "Enter return to continue ..."; getch();

			clrscr();

			ifile.close();

			goto begin;



	  case EXIT:       // to exit

			

			clrscr();

			cout << "Hospital Information System shutting down.";

			cout << "Hit <CR> to continue ..."; getch();

			exit(0);

	  case REMOVE:  		

              // To delete all patient details and meal orders stored in database.
			
			char buf[5];

			clrscr();

			cout << "Are you sure you wish to remove database?";

			gets(buf);

			if (buf[0] == 'y' || buf[0] == 'Y') {

				remove("pmeal.DAT");

				remove("pat_rec.DAT");

				remove("idfile.DAT");

				cout<<"Removed database." << '\n';

			} else {

				cout << "Not removing database." << '\n';

			}
			getch();

			goto begin;

	  default:cout<<"Please enter valid option"<<'\n';getch(); goto begin;



	}//closes switch

}

