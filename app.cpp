#include	<iostream>
#include	<cstdlib>
#include	<cstdio>
#include    <fstream>
#include	<iomanip>
#include    <string>
#include	"List.h"
#include    "LibStudent.h"
#include    "LibBook.h"
#include    "Node.h"


using namespace std;

bool ReadFile(string, List*);
bool DeleteRecord(List*, char*);
bool Display(List*, int, int);
bool InsertBook(string, List*);
bool SearchStudent(List*, char* id, LibStudent&);
bool computeAndDisplayStatistics(List*);
bool printStuWithSameBook(List*, char*);
bool displayWarnedStudent(List*, List*, List*);
int menu();

//other
void calculateDueDate(LibBook book, int& Duedate);


int main() {
	Node* cur;
	int numRecords = 0;
	List myList;
	int choice;
	char callNum1;

	List list;


	do {
		int source, detail;
		choice = menu();
		if (choice == 1)
		{
			ReadFile("student", &myList);
			cur = myList.head;
			while (cur != NULL)
			{
				numRecords++;
				cur = cur->next;
			}
			cout << numRecords << " records have been successfully read." << endl;
			numRecords = 0;
		}
		if (choice == 2)
		{
			char id[10];
			cout << "Who you want to delete?: ";
			cin >> id;
			DeleteRecord(&myList, id);
		}
		if (choice == 3)
		{
			type output;
			char id[10];
			cout << "Who you want to find?: ";
			cin >> id;
			if (SearchStudent(&myList, id, output))
			{
				cout << "Student ID = " << output.id << endl;
				cout << "Name = " << output.name << endl;
				cout << "Course = " << output.course << endl;
				cout << "Phone No = " << output.phone_no << endl;
				cout << "Total fine = " << output.total_fine << endl;
			}

		}
		if (choice == 4)
		{
			InsertBook("book", &myList);
		}
		if (choice == 5)
		{
			cout << "Where do you want to display the output (1 - File/ 2 - Screen): ";
			cin >> source;
			cout << endl << endl;
			cout << "Do you want to display book list for every student (1 - YES / 2 - NO): ";
			cin >> detail;
			cout << endl << endl;
			Display(&myList, source, detail);

		}
		if (choice == 6)
		{
			computeAndDisplayStatistics(&myList);
		}
		if (choice == 7)
		{
			char callNum1[20];
			cout << "Please key in callNum of the book: ";
			cin >> callNum1;
			printStuWithSameBook(&myList, callNum1);

		}
		if (choice == 8)
		{
			List type1;
			List type2;
			displayWarnedStudent(&myList, &type1, &type2);
		}
		if (choice == 9)
		{
			system("cls");
			return 0;
		}
		system("pause");
		system("cls");
	} while (choice != 9);

	cout << "\n\n";
	system("pause");
	return 0;
}




//1 
bool ReadFile(string filename, List* list) {
	ifstream file(filename + ".txt");
	int node = 1;
	List toStoreInfo;
	type stu;
	int recordCount = 0;

	if (file.is_open()) {
		while (!file.eof()) {
			string ignore;
			type stu;
			for (int i = 0; i < 4; i++) {
				getline(file, ignore, '=');
				if (i == 0) {
					file >> stu.id;
				}
				else if (i == 1)
				{
					char name[30];
					char secand_name[30];
					file >> name;
					file >> secand_name;
					strncat_s(name, " ", 30);
					strncat_s(name, secand_name, 30);
					for (int num = 0; num < 30; num++) {
						stu.name[num] = name[num];
					}
				}
				else if (i == 2)
					file >> stu.course;
				else if (i == 3)
					file >> stu.phone_no;
			}
			toStoreInfo.insert(node, stu);
			node++;
			recordCount++;
		}
		file.close();

		*list = toStoreInfo;
		return true;
	}

	else
	{
		cout << "The file is unfound!!!\n";
		return false;
	}
}

//2
bool DeleteRecord(List* list, char* id) {
	int nodeDelete = 1;
	Node* cur = list->head;

	while (cur != NULL) {
		if (strcmp(id, cur->item.id) == 0) {		//compare ID
			list->remove(nodeDelete);
			cout << "Delete successfully" << endl;
			return true;
		}
		cur = cur->next;							//go to next node
		nodeDelete++;
	}
	cout << "Student cannot be found in the list" << endl;
	return false;
}

//3
bool SearchStudent(List* list, char* id, LibStudent& stu) {
	Node* cur = list->head;

	while (cur != NULL) {
		if (strcmp(id, cur->item.id) == 0) {		//compare ID
			stu = cur->item;
			return true;
		}
		cur = cur->next;							//go to next node
	}
	cout << "Student not found" << endl;
	return false;
}


//4
bool InsertBook(string filename, List* list) {
	ifstream file(filename + ".txt");
	string curID;
	int nodeNum = 1;

	if (file.is_open()) {

		while (file >> curID) {					//read ID from file

			Node* cur;
			cur = list->head;
			while (cur != NULL) {
				if (cur->item.id == curID) {		//compare student ID


					string authorIO;
					string temp;

					int bkNum = 0;
					while (cur->item.book[bkNum].yearPublished != 0) {			//if book is not empty
						bkNum++;
					}
					cur->item.totalbook = bkNum + 1;							//total book num


					file >> temp;



					int authorLength = 0;
					int numAtr = 0;



					//for (int i = 0;temp[i] != )) {
					//	if (temp[authorLength] == '/') {
					//		temp[numAtr] = temp[authorLength - 1];
					//		numAtr++;
					//	}
					//	authorLength++;
					//}

					


					while (authorLength < size(temp)) {
						if (temp[authorLength] == '/') {
							temp[numAtr] = temp[authorLength - 1];
							numAtr++;
						}
						authorLength++;
					}

					if (numAtr == 0)
						numAtr++;

					for (int i = 0; i < numAtr; i++) {
						cur->item.book[bkNum].author[i + 1] = &temp[i];
					}

					file >> cur->item.book[bkNum].title;				//store book info
					file >> cur->item.book[bkNum].publisher;
					file >> cur->item.book[bkNum].ISBN;
					file >> cur->item.book[bkNum].yearPublished;
					file >> cur->item.book[bkNum].callNum;
					file >> cur->item.book[bkNum].borrow.day;
					file >> curID[1];									//to skip '/'
					file >> cur->item.book[bkNum].borrow.month;
					file >> curID[1];
					file >> cur->item.book[bkNum].borrow.year;
					file >> cur->item.book[bkNum].due.day;
					file >> curID[1];
					file >> cur->item.book[bkNum].due.month;
					file >> curID[1];
					file >> cur->item.book[bkNum].due.year;
					//cout << bookInfo.book[bkNum].title << endl;

					//find the book due date
					int dueDate;
					calculateDueDate(cur->item.book[bkNum], dueDate);

					double fine = (dueDate) * 0.50;

					if (dueDate < 0) {									//no dueDate
						cur->item.book[bkNum].fine = 0;
					}
					else {
						cur->item.book[bkNum].fine = fine;
					}
					//store to list
					//cur->item.book = bookInfo.book;
					//list->head->item.book[1].print(cout);

					cur->item.calculateTotalFine();					//total fine



				}
				cur = cur->next;
				nodeNum++;
			}
		}
		file.close();
		//list->head->item.book->print(cout);
		cout << "Books inserted successfully to student list." << endl;
		return true;
	}

	else {
		cout << "The file is unfound!!!\n";
		cout << "don know why";
		return false;
	}
}

//5 
bool Display(List* list, int source, int detail)
{
	List newList;
	type stu;
	int node = 0;
	Node* cur;

	if (source == 1) //when source = 1 which means display in file
	{
		if (detail == 1) //need to display book list 
		{
			cur = list->head;
			// node is to know there is how many value in the list
			while (cur != NULL)
			{
				list->get(node + 1, stu);
				//newList is another linked list which use to sub in the studentname in alphabetical order
				newList.insert(stu);
				node++;
				cur = cur->next;
			}
			//open a new file to write in the data and name it student_booklist.txt as need to display book list
			ofstream inFile("student_booklist.txt");
			for (int i = 1; i < node + 1; i++)
			{
				inFile << endl << "STUDENT" << i;
				newList.get(i, stu);
				stu.print(inFile);

				inFile << endl << "BOOK LIST: " << endl << endl;

				for (int j = 0; j < stu.totalbook; j++) {
					inFile << "Book" << j + 1 << endl;
					stu.book[j].print(inFile);
					cout << endl;
				}
				inFile << endl << "*****************************************************************************" << endl;
			}

			cout << "Successfully display output to student_booklist.txt" << endl << endl;
			cout << "Successfully display output" << endl;
			return true;

		}
		else if (detail == 2) //no need to display book list
		{
			cur = list->head;
			// node is to know there is how many value in the list
			while (cur != NULL)
			{
				list->get(node + 1, stu);
				//newList is another linked list which use to sub in the studentname in alphabetical order
				newList.insert(stu);
				node++;
				cur = cur->next;
			}
			//open a new file to write in the data and name it student_info.txt as no need to display booklist
			ofstream inFile("student_info.txt");
			for (int i = 1; i < node + 1; i++)
			{
				inFile << endl << "STUDENT" << i;
				newList.get(i, stu);
				stu.print(inFile);

				inFile << endl;
				inFile << endl << "*****************************************************************************" << endl;
			}

			cout << "Successfully display output to student_info.txt" << endl << endl;
			cout << "Successfully display output" << endl;
			return true;
		}
		else
		{
			cout << "File cannot be displayed";
			return false;
		}
	}
	else if (source == 2) // display on screen (cout)
	{
		if (detail == 1) //need to display boook list
		{
			cur = list->head;
			// node is to know there is how many value in the list
			while (cur != NULL)
			{
				list->get(node + 1, stu);
				//newList is another linked list which use to sub in the studentname in alphabetical order
				newList.insert(stu);
				node++;
				cur = cur->next;
			}

			for (int i = 1; i < node + 1; i++)
			{
				cout << endl << "STUDENT" << i;
				newList.get(i, stu);
				stu.print(cout);

				cout << endl << "BOOK LIST: " << endl << endl;

				for (int j = 0; j < stu.totalbook; j++) {
					cout << "Book" << j + 1 << endl;
					stu.book[j].print(cout);
					cout << endl;
				}

				cout << endl << "*****************************************************************************" << endl;
			}
			return true;

		}
		else if (detail == 2) // no need to display book list
		{
			cur = list->head;
			//node is to know there is how many value in the list
			while (cur != NULL)
			{
				list->get(node + 1, stu);
				//newList is another linked list which use to sub in the studentname in alphabetical order
				newList.insert(stu);
				node++;
				cur = cur->next;
			}

			for (int i = 1; i < node + 1; i++)
			{
				cout << endl << "STUDENT" << i;
				newList.get(i, stu);

				stu.print(cout);
				cout << endl;
				cout << endl << "*****************************************************************************" << endl;

			}
			return true;

		}
		else
		{
			cout << "File cannot be displayed" << endl;
			return false;
		}
	}

	else {
		cout << "The file is unfound!!!\n";
		return false;
	}
}

//6 
bool computeAndDisplayStatistics(List* list)
{
	if (list->head == NULL)
		return false;
	// prepare a struct so that every course got its own datatype and not confused
	struct course {
		int noOfstudent;
		int totalBooks;
		int totalOverdue;
		double overdueFine;
	};

	course CScourse = { 0,0,0,0.0 };
	course IAcourse = { 0,0,0,0.0 };
	course IBcourse = { 0,0,0,0.0 };
	course CNcourse = { 0,0,0,0.0 };
	course CTcourse = { 0,0,0,0.0 };

	Node* cur = list->head;
	//to know the number of books in list
	int totalBooks = cur->item.totalbook;

	//title
	cout << "Course\t" << "Number of Students\t" << "Total Books Borrowed\t" << "Total Overdue Books\t" << "Total Overdue Fine(RM)\t" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	while (cur != NULL)
	{
		if (strcmp(cur->item.course, "CS") == 0) // if course is cs, record details
		{
			CScourse.noOfstudent++;
			CScourse.totalBooks += cur->item.totalbook;
			CScourse.overdueFine += cur->item.total_fine;
			for (int i = 0; i < cur->item.totalbook; i++)
			{
				int dueDate;
				calculateDueDate(cur->item.book[i], dueDate); //check whether the book is overdue?
				if (dueDate > 0)
					CScourse.totalOverdue++;
			}
		}
		else if (strcmp(cur->item.course, "IA") == 0) //if course is IA, record details
		{
			IAcourse.noOfstudent++;
			IAcourse.totalBooks += cur->item.totalbook;
			IAcourse.overdueFine += cur->item.total_fine;
			for (int i = 0; i < cur->item.totalbook; i++)
			{
				int dueDate;
				calculateDueDate(cur->item.book[i], dueDate);//check whether the book is overdue?
				if (dueDate > 0)
					IAcourse.totalOverdue++;
			}

		}
		else if (strcmp(cur->item.course, "IB") == 0) //if course is IB, record details
		{
			IBcourse.noOfstudent++;
			IBcourse.totalBooks += cur->item.totalbook;
			IBcourse.overdueFine += cur->item.total_fine;
			for (int i = 0; i < cur->item.totalbook; i++)
			{
				int dueDate;
				calculateDueDate(cur->item.book[i], dueDate);//check whether the book is overdue?
				if (dueDate > 0)
					IBcourse.totalOverdue++;
			}
		}
		else if (strcmp(cur->item.course, "CN") == 0) //if course is CN,record details
		{
			CNcourse.noOfstudent++;
			CNcourse.totalBooks += cur->item.totalbook;
			CNcourse.overdueFine += cur->item.total_fine;
			for (int i = 0; i < cur->item.totalbook; i++)
			{
				int dueDate;
				calculateDueDate(cur->item.book[i], dueDate); //check whether the book is overdue?
				if (dueDate > 0)
					CNcourse.totalOverdue++;
			}

		}
		else if (strcmp(cur->item.course, "CT") == 0)// if course is CT, record details
		{
			CTcourse.noOfstudent++;
			CTcourse.totalBooks += cur->item.totalbook;
			CTcourse.overdueFine += cur->item.total_fine;
			for (int i = 0; i < cur->item.totalbook; i++)
			{
				int dueDate;
				calculateDueDate(cur->item.book[i], dueDate); //check whether the book is overdue?
				if (dueDate > 0)
					CTcourse.totalOverdue++;
			}

		}
		//point to the next one, until the end
		cur = cur->next;

	}
	//print the recorded data line by line
	cout << "CS\t\t" << CScourse.noOfstudent << "\t\t\t" << CScourse.totalBooks << "\t\t\t" << fixed << setprecision(2) << CScourse.totalOverdue << "\t\t\t" << CScourse.overdueFine << endl;
	cout << "IA\t\t" << IAcourse.noOfstudent << "\t\t\t" << IAcourse.totalBooks << "\t\t\t" << fixed << setprecision(2) << IAcourse.totalOverdue << "\t\t\t" << IAcourse.overdueFine << endl;
	cout << "IB\t\t" << IBcourse.noOfstudent << "\t\t\t" << IBcourse.totalBooks << "\t\t\t" << fixed << setprecision(2) << IBcourse.totalOverdue << "\t\t\t" << IBcourse.overdueFine << endl;
	cout << "CN\t\t" << CNcourse.noOfstudent << "\t\t\t" << CNcourse.totalBooks << "\t\t\t" << fixed << setprecision(2) << CNcourse.totalOverdue << "\t\t\t" << CNcourse.overdueFine << endl;
	cout << "CT\t\t" << CTcourse.noOfstudent << "\t\t\t" << CTcourse.totalBooks << "\t\t\t" << fixed << setprecision(2) << CTcourse.totalOverdue << "\t\t\t" << CTcourse.overdueFine << endl;
	return true;

}

//7
bool printStuWithSameBook(List* list, char* callNum1) {

	List stu;

	Node* cur = list->head;
	int stuCount = 0;
	type stuInfo;

	while (cur != NULL) {
		stuInfo = cur->item;

		for (int i = 0; i < stuInfo.totalbook; i++) {
			if (strcmp(stuInfo.book[i].callNum, callNum1) == 0) { //compare the callNum that has store in the list with the cin callNum
				stuCount++;
				stu.insert(stuCount, stuInfo);
				// open a list to store studentinfo when their callNum are equel
			}
		}
		cur = cur->next;
	}


	cout << "There are " << stuCount << " student(s) that borrowed the book with call number " << callNum1 << " as shown below:" << endl;

	cur = stu.head;
	while (cur != NULL) {

		//looping the list that you open above to display info inside the node

		cout << "Student ID = " << cur->item.id << endl;
		cout << "Name = " << cur->item.name << endl;
		cout << "Course = " << cur->item.course << endl;
		cout << "Phone Number = " << cur->item.phone_no << endl;

		LibBook* curBook = cur->item.book;
		for (int i = 0; i < cur->item.totalbook; i++) {
			if (strcmp(curBook[i].callNum, callNum1) == 0) {
				cout << "Borrow Date = " << cur->item.book[i].borrow.day << "/" << cur->item.book[i].borrow.month << "/" << cur->item.book[i].borrow.year << endl;
				cout << "Due Date = " << cur->item.book[i].due.day << "/" << cur->item.book[i].due.month << "/" << cur->item.book[i].due.year << endl << endl;
			}

		}
		cur = cur->next;
	}


	if (stuCount == 0) {
		cout << "There are no student found." << endl;
		return false;
	}

	if (list->empty()) {
		cout << "Sorry. The list is empty." << endl;
		return false;
	}
	return true;
}

//8
bool displayWarnedStudent(List* list, List* type1, List* type2) {
	int a = 1;
	int b = 1;
	type stu;
	Node* cur = list->head;
	while (cur != NULL) {
		stu = cur->item;
		int BooksOverDue = 0;// the total books that are overdue 
		int BooksME10 = 0; //total books that are due more or equal to 10 only
		int DaysOverDue = 0; // Days each books borrowed by student overdue
		int totalbooks = stu.totalbook; //total book borrowed by students

		for (int i = 0; i < stu.totalbook + 1; i++) {
			calculateDueDate(stu.book[i], DaysOverDue);

			if (DaysOverDue >= 1) { //days book overdue
				BooksOverDue++;     //book overdue's number increase
			}

			else if (DaysOverDue >= 10) {
				BooksME10++; //book overdue >=10 number increase
			}
		}

		if (BooksME10 > 2) { //each book due days over or equal than 10
			
			type1->insert(a, stu);
			a++;
		}

		if (BooksOverDue == totalbooks && stu.total_fine > 50.00) {
		
			type2->insert(b, stu);
			b++;
		}
		cur = cur->next;
	}
	cout << "Type1: Students with more than 2 books overdue >= 10 days:" << endl << endl;
	if (type1->empty()) {
		cout << "No students found." << endl;
	}
	else {
		Node* cur1 = type1->head;
		int numStu = 1;
		while (cur1 != NULL) {
			cout << "Student " << numStu << endl << endl;
			cur1->item.print(cout);
			cur1 = cur1->next;
			numStu++;
		}

		cout << "BOOK LIST:" << endl << endl;

		cur = type1->head;
		for (int i = 1; i < cur1->item.totalbook; i++) {
			cout << "Book " << (i + 1) << endl;
			cur1->item.book[i].print(cout); // Print book details
			cout << endl;
		}
		cout << "*****************************************************************************" << endl << endl;
	}
	cout << "Type2: Students with total fine > RM50.00 and all books are overdue:" << endl << endl;
	if (type2->empty()) {
		cout << "No students found." << endl;
	}
	else {
		Node* cur2 = type2->head;
		int numStu = 1;
		while (cur2 != NULL) {
			cout << "Student " << numStu << endl << endl;
			cur2->item.print(cout);
			cur2 = cur2->next;
			numStu++;
		}

		cur2 = type2->head;
		cout << "BOOK LIST:" << endl << endl;
		for (int i = 1; i < cur2->item.totalbook; i++) {
			cout << "Book " << (i + 1) << endl;
			cur2->item.book[i].print(cout);
			cout << endl; // Print book details
		}
		cout << "*****************************************************************************" << endl << endl;
	}
	return true;
}


//9 done
int menu()
{
	int choice;
	cout << "1. Read file." << endl;
	cout << "2. Delete record." << endl;
	cout << "3. Search student." << endl;
	cout << "4. Insert book." << endl;
	cout << "5. Display output." << endl;
	cout << "6. Compute and Display Statistics" << endl;
	cout << "7. Student with Same Book" << endl;
	cout << "8. Display Warned Student" << endl;
	cout << "9. Exit." << endl;
	cout << "Enter your choice: ";
	cin >> choice;
	while (choice < 1 || choice > 9) {
		cout << "Invalid choice. Please select a number between 1 to 9" << endl;
		cout << "Please enter your choice again: ";
		cin >> choice;
		system("cls");
	}
	system("cls");
	return choice;
}

//other
void calculateDueDate(LibBook book, int& Duedate)
{
	int d = book.due.day;
	int m = book.due.month;
	int y = book.due.year;
	// let 29/3/2020 as the current date
	Duedate = (2020 - y) * (365 + 1 / 4 - 1 / 100 + 1 / 400) + (4 - m) * 30.6 + (29 - d);
}


