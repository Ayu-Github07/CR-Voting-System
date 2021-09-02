
#include<stdio.h>
#include<string.h>

int input_section, input_gender, ch, n, i, viewtype;
int ids, idr,k;
char un[10], pw[10], g[6];
void welcome_screen();
void teacher_login();
void student_login();
void result();
void compare();

struct candidates
{
    int roll_number;
    char name[15];
    char descripton[50];
    int section;
    int gender;
}c;
	
void welcome_screen(){
	printf("\n\t\t1.  Teacher login");
	printf("\n\t\t2.  Student login");
	printf("\n\t\t3.  Result");
	printf("\n\t\tEnter your choice : ");	
	scanf("%d",&ch);
	switch(ch){
		case 1:
			teacher_login();
			break;
		case 2:
			student_login();
			break;
		case 3:
			printf("Result still counting...");	//result();
			break;
		default:
			printf("\n\t\twrong choice, try again");
			welcome_screen();
	}
}

void input_login(){
	printf("\nUsername: ");
	scanf("%s",&un);
	printf("\nPassword: ");
	scanf("%s",&pw);
}

void teacher_login(){
	input_login();
	if(strcmp(un,"taru")==0 && strcmp(pw,"psw")==0 || strcmp(un,"tnik")==0 && strcmp(pw,"paas")==0){
		printf("\n\t\t\t\tWelcome to teacher login!");
		do{
			ch=0;
			printf("\n\t\tEnter 1 to add candidate(s)");
			printf("\n\t\tEnter 2 to search a candidate");
			printf("\n\t\tEnter 3 to view candidates(s)");
			printf("\n\t\tEnter your choice : ");
			scanf("%d",&ch);
			switch(ch){
				case 1:		//1 to add candidate(s)
					add_candidate();					
					break;
				case 2:	//to search a candidate
					search_candidates();
					break;
				case 3:		//3 to view candidates(s)
					view_candidates();				
					break;
				default:
				printf("\n\t\twrong choice, try again");
			}
		}while(ch!=0);
	}
	else{
       	printf("\n Invalid username or password. Please try again.\n");
	    teacher_login();
	}
}
void add_candidate();
void add_candidate(){
	printf("");		//This is to make FILE *ac to run without declaration error
	FILE *ac;		//ac=append candidate
	ac=fopen("CR_candidates","a");
	printf("\nCandidate's section:-");					
	printf("\nEnter 1 for Section A");
	printf("\nEnter 2 for Section B");
	printf("\nEnter 3 for Section C");
	printf("\nEnter your choice : ");
	scanf("%d",&input_section);
	printf("\nEnter 1 to add boy candidate(s)");
	printf("\nEnter 2 to add girl candidate(s)");
	printf("\nEnter your choice : ");
	scanf("%d",&input_gender);				
	printf("\nEnter number of cadidates to add in this section: ");
	scanf("%d",&n);
	for(i=0;i<n;i++){
		c.section = input_section;
		c.gender = input_gender;
		printf("\n\nEnter name: ");
		scanf("%s",&c.name);
		printf("Enter roll no.: ");
		scanf("%d",&c.roll_number);
		printf("Enter descripton: ");
		scanf("%s",&c.descripton);
	}
	fwrite(&c,sizeof(c),1,ac);
	fclose(ac);
}

void search_candidates();
void search_candidates(){
	printf("\nEnter roll no. of the candidate to search: ");
	scanf("%d",&idr);
	printf("\nEnter section of the candidate to search: ");
	scanf("%d",&ids);
	FILE*scr;   //scr= search candidate's roll number!
	scr=fopen("CR_candidates","r");
	while(!feof(scr)){
		fread(&c,sizeof(c),1,scr);
		if(idr==c.roll_number && ids==c.section){
			printf("\nThe student having the roll no %d and section %d has been found!",idr,ids);
			fclose(scr); k=1;
                        break; 
		}
	}
        if(k==0)
      {
	printf("\nThe student having the roll no %d and section %d has not been found!",idr,ids);
	fclose(scr);
      }
}

void view_candidates();
void view_candidates(){
	printf("\nEnter 1 to view all candidates(s)");
	printf("\nEnter 2 to view candidates(s) of a section");
	printf("\nEnter 3 to view candidates(s) gender wise");
	printf("\nEnter your choice : ");
	scanf("%d",&viewtype);
	switch(viewtype){
		case 1:							
			printf("");		//This is to make FILE *dac to run without declaration error
			FILE*dac;		//dac=display all candidates
			dac=fopen("CR_candidates","r");
			printf("\n\t\t\tName\t\tGender\t\tRoll no.\t\tSection\n");//	c.descripton, c.gender, c.name, c.roll_number, c.section
			while(fread(&c,sizeof(c),1,dac)){
				/*if(c.gender==1){
					g[6]='Male';
				}
				else{
					g[6]='Female';
				}
				printf("\n\t\t\t%s\t%s\t%d\t\t%d",c.name,g,c.roll_number,c.section);*/
				printf("\n\t\t\t%s\t\t%d\t\t%d\t\t\t%d",c.name,c.gender,c.roll_number,c.section);
			}
			fclose(dac);
			break;
		case 2:
			printf("\nCandidate's section:-");					
			printf("\nEnter 1 for Section A");
			printf("\nEnter 2 for Section B");
			printf("\nEnter 3 for Section C");
			printf("\nEnter your choice : ");
			scanf("%d",&input_section);
			FILE*dcs;		//dcs=display candidates sectionwise
			dcs=fopen("CR_candidates","r");
			printf("\n\t\t\tName:\tGender:\tRoll no.:\tDescription");//	c.descripton, c.gender, c.name, c.roll_number, c.section
			while(fread(&c,sizeof(c),1,dcs)){
				if(c.section==input_section){
					printf("\n\t\t\t%s\t%d\t%d\t%s",c.name,c.gender,c.roll_number,c.descripton);
				}
			}
			fclose(dcs);
			break;
		case 3:
			printf("\nEnter 1 to display all boy candidates");
			printf("\nEnter 2 to display all girl candidates");
			printf("\nEnter your choice : ");
			scanf("%d",&input_gender);
			FILE*dcg;		//dcs=display candidates genderwise
			dcg=fopen("CR_candidates","r");
			printf("\n\t\t\tName:\t\tRoll no.:\t\tSection:\t\tDescription");//	c.descripton, c.gender, c.name, c.roll_number, c.section
			while(fread(&c,sizeof(c),1,dcs)){
				if(c.gender==input_gender){
					printf("\n\t\t\t%s\t\t%d\t\t%d\t\t\t%s",c.name,c.roll_number,c.section,c.descripton);
				}
			}
			fclose(dcg);	
		default:
			printf("\n\t\twrong choice, try again");					
			view_candidates();
	}
}

void student_login(){
	input_login();
	if(un[0]=='a'){
		if(un[1]=='g'){
			if(strcmp(un,"agashi")==0 && strcmp(pw,"pws")==0 || strcmp(un,"agurvi")==0 && strcmp(pw,"paas")==0){
				printf("\nBranch: CSE\tYear: 2nd\tSection: A");
				
				//view all candidates list
				//caste your vote
			}
			else{
				printf("\n Invalid username or password. Please try again.\n");
				student_login();
			}
		}
		else if(un[1]=='b'){
			if(strcmp(un,"abashu")==0 && strcmp(pw,"pws")==0 || strcmp(un,"abdhruv")==0 && strcmp(pw,"paas")==0){
				printf("\nBranch: CSE\tYear: 2nd\tSection: A");
				//view all candidates list
				//caste your vote
			}
			else{
				printf("\n Invalid username or password. Please try again.\n");
				student_login();
			}
		}
		else{
			printf("\n Invalid username or password. Please try again.\n");
			student_login();
		}
	}
	else{
		printf("\n Invalid username or password. Please try again.\n");
		student_login();
	}
}


void main(){
	printf("\n\t*** Project : CR voting system ***\n");
	welcome_screen();	
}
