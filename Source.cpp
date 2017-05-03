#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<cmath>
#include <ctime>
#include<vector>
#include<string>
#include <fstream>
#include <stdlib.h>
#include <conio.h>
#define input_client_db "D:\\banking system\\DataBases\\clientDB.txt"
#define input_loan_db "D:\\banking system\\DataBases\\loanDB.txt"
#define teller_db "D:\\banking system\\DataBases\\tellerDB.txt"
#define input_history_db "D:\\banking system\\DataBases\\historyDB.txt"
#define output_client_DB "D:\\banking system\\DataBases\\outputClient.txt"
#define output_loan_DB "D:\\banking system\\DataBases\\outputLoan.txt"
#define output_history_DB "D:\\banking system\\DataBases\\outputHistory.txt"
using namespace std;


class Transaction
{
public:  void deposit(float *balance, float amount)
{
	*balance += amount;
}

		 bool withdraw(float *balance, float amount)
		 {
			 bool flag;
			 if (amount > *balance) return flag = false;
			 else {
				 *balance -= amount;
				 return flag = true;
			 }
			 return flag;
		 }

		 bool transaction(float *From_Balance, float *To_Balance, float amount)
		 {
			 bool flag;
			 if (amount > *From_Balance) return flag = false;
			 else {
				 withdraw(From_Balance, amount);
				 deposit(To_Balance, amount);
				 return flag = true;
			 }
			 return flag;

		 }

};

class node_history
{
protected:
	node_history * next;
	vector <string> data;
	int data_size;
public:

	node_history()
	{
		next = NULL;
	}

	node_history(string createtime)
	{
		next = NULL;
		data.push_back(createtime); // time of creation
		data_size = data.size();
	}

	node_history(vector<string> info)
	{

		next = NULL;
		data = info;
		data_size = data.size();
	}

	node_history* getNext() { return next; }

	int getDataSize() { return data.size(); }

	vector <string> getData() { return data; }

	void setNext(node_history * n) { next = n; }

	friend class history;
};

class history
{

	node_history* chain;
	node_history * tail;
	time_t t = time(0);
	struct tm * now = localtime(&t);

public: history() { chain = NULL; }

		node_history * addb() {
			now->tm_hour;
			string timeS1 = to_string(now->tm_hour);
			string x = ":00";
			string time2 = "New account created at time : ";
			string timeS = time2 + timeS1 + x;
			if (chain == NULL)
			{
				node_history *temp = new node_history(timeS);
				temp->setNext(chain);
				chain = temp;
				tail = chain;

			}
			else {
				node_history *temp = tail;
				tail->next = new node_history(timeS);
				tail = tail->next;

			}

			return tail;
		}

		node_history * addb(vector<string> info) {
			if (chain == NULL)
			{
				node_history *temp = new node_history(info);
				temp->setNext(chain);
				chain = temp;
				tail = chain;

			}
			else {
				node_history *temp = tail;
				tail->next = new node_history(info);
				tail = tail->next;

			}

			return tail;
		}


		void newDeposit(node_history *client, float amount, float balanceAfter)
		{
			node_history * ptr = client;
			string amountString = to_string(amount);
			string balance = to_string(balanceAfter);
			string timeS = to_string(now->tm_hour);
			string x = ":00";
			string firstSent = "Deposite done by amount : ";
			string secondSent = " and balance become= ";
			string at = " at ";

			string trans = firstSent + amountString + secondSent + balance + at + timeS + x;
			ptr->data.push_back(trans);
		}

		void newWithDraw(node_history *client, float amount, float balanceAfter)
		{
			node_history * ptr = client;
			string amountString = to_string(amount);
			string balance = to_string(balanceAfter);
			string timeS = to_string(now->tm_hour);
			string firstSent = "Withdraw done by amount : ";
			string secondSent = " and balance become= ";
			string at = " at ";
			string x = ":00";

			string trans = firstSent + amountString + secondSent + balance + at + timeS + x;
			ptr->data.push_back(trans);
		}

		void  newTrans(node_history *from, float amount, string name)
		{
			node_history * ptr = from;
			string amountString = to_string(amount);
			string timeS = to_string(now->tm_hour);
			string firstSent = "transaction done by amount :";
			string secondSentence = " to ";
			string at = " at ";
			string x = ":00";
			string trans = firstSent + amountString + secondSentence + name + at + timeS + x;
			ptr->data.push_back(trans);
		}

		void newLoan(node_history *client, float loan)
		{
			node_history * ptr = client;
			string loanString = to_string(loan);
			string timeS = to_string(now->tm_hour);
			string firstSent = "Loan done by amount :";
			string at = " at ";
			string x = ":00";
			string trans = firstSent + loanString + at + timeS + x;
			ptr->data.push_back(trans);

		}

		void printNode(node_history * client)
		{
			node_history * ptr = client;
			for (int i = 0; i < ptr->data.size(); i++)
			{
				cout << ptr->data[i] << endl;
			}
		}

};


class clientLoan {
protected:
	struct loanData {
		float loan;
		//can add more variables when needed
	};
	loanData loanData;
	clientLoan *next;
public:

	//constructors start

	clientLoan() {
		loanData.loan = 0;
		next = NULL;
	}

	clientLoan(float money) {
		loanData.loan = money;
		next = NULL;
	}

	//constructors end

	//setters start

	void setLoan(float money) { loanData.loan = money; }

	void setNext(clientLoan *n) { next = n; }

	//setters end

	//getters start
	float getLoan() { return loanData.loan; }
	clientLoan * getNext() { return next; }
	//getters end

	//functions start 
	void addLoan(float money) { loanData.loan += money; }
	void removeLoan(float money) { loanData.loan -= money; }
	//functions end

	friend class Loan;
};

class Loan {

protected:
	clientLoan * chain;
	clientLoan * tail = chain;

public:
	//constructors start
	Loan() { chain = NULL; }
	//constructors end

	//getters start
	clientLoan * getChain() { return chain; }
	clientLoan * getTail() { return tail; }
	//getters end

	clientLoan * addf() {
		clientLoan * temp = new clientLoan();
		temp->setNext(chain);
		chain = temp;
		return chain;
	}

	clientLoan * addf(float money) {
		clientLoan * temp = new clientLoan(money);
		temp->setNext(chain);
		chain = temp;
		return chain;
	}

	clientLoan * addb() {										//add element to the back of list
		clientLoan * temp = tail;
		if (chain == NULL) {
			chain = new clientLoan();
			tail = chain;
			return tail;
		}
		else {
			tail->next = new clientLoan();
			tail = tail->next;
			return tail;
		}

	}

	clientLoan * addb(float money) {										//add element to the back of list
		clientLoan * temp = tail;
		if (chain == NULL) {
			chain = new clientLoan(money);
			tail = chain;
			return tail;
		}
		else {
			tail->next = new clientLoan(money);
			tail = tail->next;
			return tail;
		}
	}

};

class clientNode {

protected:
	struct clientData {
		int ID;
		string name;
		string mob;
		string mail;
		string address;
		string job;
		string nationality;
		string password;
		float  balance;
		bool   loan;
		bool   hold;

		clientLoan *clientLoan;			//change "node" to the node type of loan;
		node_history *clientHistory;		//change "node" to the node type of history;

	};
	clientData clientData;
	clientNode * next;
	clientNode *left, *right; //in case of tree usaging;
public:
	//clientNode constructor start....


	clientNode(int id, string name, float balance, string mob, string mail, string address, string job, string nationality, string password) {
		clientData.ID = id;
		clientData.name = name;
		clientData.mob = mob;
		clientData.mail = mail;
		clientData.address = address;
		clientData.job = job;
		clientData.nationality = nationality;
		clientData.password = password;
		clientData.balance = balance;

		next = NULL;

	}
	//clientNode constructor end....
protected:

	//clientNode setters start....
	void setID(int id) { clientData.ID = id; }
	void setName(string name) { clientData.name = name; }
	void setMob(string mob) { clientData.mob = mob; }
	void setMail(string mail) { clientData.mail = mail; }
	void setPassword(string password) { clientData.password = password; }
	void setJob(string job) { clientData.job = job; }
	void setAddress(string address) { clientData.address = address; }
	void setNationality(string nationality) { clientData.nationality = nationality; }
	void setBalance(float balance) { clientData.balance = balance; }
	void setHaveLoan(bool haveloan) { clientData.loan = haveloan; }
	void setHold(bool x) { clientData.hold = x; }
	void setNext(clientNode * n) { next = n; }
	void setLeft(clientNode *Left) { left = Left; }
	void setRight(clientNode *Right) { right = Right; }
	//clientNode setters end....

	//clientNode getters start....
	int	   getID() { return clientData.ID; }
	string getPassword() { return clientData.password; }
	string getName() { return clientData.name; }
	string getMob() { return clientData.mob; }
	string getMail() { return clientData.mail; }
	string getJob() { return clientData.job; }
	string getAddress() { return clientData.address; }
	string getNationality() { return clientData.nationality; }
	float  getBalance() { return clientData.balance; }
	bool   getHaveLoan() { return clientData.loan; }
	bool   getHold() { return clientData.hold; }
	clientNode * getNext() { return next; }
	clientNode * getLeft() { return left; }
	clientNode * getRight() { return right; }
	clientNode * getData() { return this; }
	//clientNode getters end....


	//print client data...
	void print() {
		cout << clientData.ID << "\t";
		cout << getName() << "\t";
		cout << getBalance() << "\t";
		cout << getNationality() << "\t";
		cout << getMob() << "\t";
		cout << getMail() << "\t";
		cout << getAddress() << "\t";
		cout << getJob() << "\t";
		cout << getHaveLoan() << "\t";
		cout << getHold() << "\n";

	}
	

	friend class client;
	friend class linker;
	friend class Loan;
	friend class transaction;
	friend class history;
	friend void main();
};

//hyprid class <tree and list functions included>
class client {

public:
	//constructor start....
	client() : chain(NULL) {};

	//constructor end....

protected:
	clientNode * chain;
	clientNode * tail = chain;
	clientNode * rootPtr = NULL;
	int size = 0;													//contain list size
	int currentID;							//have the current ID (is used to be increased and assign the new value to the new client)

	clientNode *getchain() { return chain; }							//returns list head
	clientNode *gettail() { return tail; }							//returns list tail
	bool isEmpty() { return (chain == NULL) ? true : false; }	//check if list is empty



	//search client by ID <as a list>
	clientNode	*searchByID(int id) {
		for (clientNode *temp = chain; temp != NULL; temp = temp->next)
			if (temp->clientData.ID == id)
				return temp;
		return NULL;

	}

	bool findID(int id) {
		if (searchByID(id) == NULL) {
			//cout << "ID notfound";
			return false;
		}
		else return true;
	}

	//add client <by all data> to the front of list
	clientNode *addb(string name, float balance, string mob, string mail, string address, string job, string nationality, string password) {										//add element to the back of list
		clientNode * temp = tail;
		if (chain == NULL) {
			while (findID(currentID))
				++currentID;
			chain = new clientNode(currentID, name, balance, mob, mail, address, job, nationality, password);
			tail = chain;
			return chain;
		}
		else {

			while (findID(currentID)) {
				++currentID;
			}
			tail->next = new clientNode(currentID, name, balance, mob, mail, address, job, nationality, password);
			tail = tail->next;
			return tail;
		}
		size++;
	}

	//add to back <from DB version> 
	clientNode * addbFile(int id, string name, float balance, string mob, string mail, string address, string job, string nationality, bool Loan, bool Hold, string password) {										//add element to the back of list
		clientNode * temp = tail;
		if (chain == NULL) {
			chain = new clientNode(id, name, balance, mob, mail, address, job, nationality, password);
			tail = chain;
			chain->clientData.loan = Loan;
			chain->clientData.hold = Hold;
			return chain;
		}
		else {
			tail->next = new clientNode(id, name, balance, mob, mail, address, job, nationality, password);

			//temp->clientData.ID = id;
															  //temp->clientData.clientHistory	 = History.addf();    //calls history's addb which returns its pointer;
			tail = tail->next;
			//tail->clientData.ID = currentID;
			tail->clientData.loan = Loan;
			tail->clientData.hold = Hold;
			return tail;

		}
	}
	//prints all list content (interface to "printall()")
	void printList() {
		printall(chain);
		cout << endl;
	}

	//search client by name <as a list>
	clientNode *searchByName(string name) {
		for (clientNode *temp = chain; temp != NULL; temp = temp->next)
			if (temp->clientData.name == name)
				return temp;
		return NULL;
	}

	//add client by ID <as a binary tree>(sorted)
	void treeAddByID(string type, int id, string name, float balance, string mob, string mail, string address, string job, string nationality, string password) {

		if (isEmpty()) { rootPtr = new clientNode(id, name, balance, mob, mail, address, job, nationality, password); }

		clientNode *p = rootPtr;

		while (p != NULL) {

			int a = p->getID();

			if (a == id) return;

			else if (id < a) {

				if (p->getLeft() == NULL) {

					clientNode *newNodePtr = new clientNode(id, name, balance, mob, mail, address, job, nationality, password);

					p->setLeft(newNodePtr);
				}

				else p = p->getLeft();

			}
			else {

				if (p->getRight() == NULL) {

					clientNode *newNodePtr = new clientNode(id, name, balance, mob, mail, address, job, nationality, password);

					p->setRight(newNodePtr);
				}

				else p = p->getRight();
			}

		}

	};

	//add client by name <as a binary tree>(sorted)
	void treeAddByName(string type, int id, string name, float balance, string mob, string mail, string address, string job, string nationality, string password) {

		if (isEmpty()) { rootPtr = new clientNode(id, name, balance, mob, mail, address, job, nationality, password); }

		clientNode *p = rootPtr;

		while (p != NULL) {

			string a = p->getName();

			if (a == name) return;

			else if (name < a) {

				if (p->getLeft() == NULL) {

					clientNode *newNodePtr = new clientNode(id, name, balance, mob, mail, address, job, nationality, password);

					p->setLeft(newNodePtr);
				}

				else p = p->getLeft();

			}
			else {

				if (p->getRight() == NULL) {

					clientNode *newNodePtr = new clientNode(id, name, balance, mob, mail, address, job, nationality, password);

					p->setRight(newNodePtr);
				}

				else p = p->getRight();
			}

		}
	}

	//search client by name <as a tree>
	clientNode *treeSearchByName(string name) {

		if (isEmpty()) { return rootPtr; } //error here

		clientNode *p = rootPtr;

		while (p != NULL) {

			string a = p->getName();

			if (a == name) return p;

			else if (name < a) p = p->getLeft();

			else p = p->getRight();

		}

		return NULL;
	}

	//search client by ID <as a tree>
	clientNode *treeSearchByID(int ID) {

		if (isEmpty()) { return rootPtr; } //error here

		clientNode *p = rootPtr;

		while (p != NULL) {

			int a = p->getID();

			if (a == ID) return p;

			else if (ID < a) p = p->getLeft();

			else p = p->getRight();

		}

		return NULL;
	}

private:

	void printall(clientNode * p) {
		if (p != NULL) {
			p->print();
			printall(p->next);
		}
	}

	friend class linker;
	friend class Loan;
	friend class transaction;
	friend class history;
	friend void main();

};

class linker {

protected:
	Loan loan;
public: Transaction transaction;
	history History;
	bool teller = false;
	client Client;
public: clientNode *currentClient;

public:

	linker() {}; //unused constructor

	void addClient(string name, float balance, string mob, string mail, string address, string job, string nationality, bool Loan, bool Hold, string password) {
		clientNode *temp;
		temp = Client.addb(name, balance, mob, mail, address, job, nationality, password);
		temp->clientData.clientLoan = loan.addb();
		temp->clientData.clientHistory = History.addb();
	}

	bool loginClient() {

		bool loggedIn = false;
		string name, passwords;
		bool nameCheck = false;
		bool passwordCheck = false;
		cout << "Please enter your username : ";
		cin >> name;
		if (Client.searchByName(name) == NULL) {
			while (!nameCheck) {
				cout << "User not found.Please try again" << endl;
				cout << "Please enter your user name : ";
				cin >> name;
				if (Client.searchByName(name) != NULL) nameCheck = true;
			}

		}

		currentClient = Client.searchByName(name);
		cout << "Password : ";
		cin >> passwords;
		if (currentClient->clientData.password == passwords) {
			system("CLS");
			if (currentClient->clientData.hold) {
				cout << "Sorry your account is held please contact your Bank for more info" << endl << endl;
				loggedIn = false;
			}
			else {
				cout << "Welcome =)" << endl;
				loggedIn = true;
			}
		}
		else {
			while (!passwordCheck) {
				cout << "Wrong password " << name << ".Please Try again" << endl;
				cout << "Password : ";
				cin >> passwords;
				if (currentClient->clientData.password == passwords) {
					system("CLS");
					if (currentClient->clientData.hold) {
						cout << "Sorry your account is held please contact your Bank for more info" << endl;
						loggedIn = false;
					}
					else {
						cout << "Welcome =)" << endl;
						loggedIn = true;
					}
				}
			}

		}
		return loggedIn;
	}


	bool tellerLogin() {
		cout << " Please enter your name then your password\n";
		string name, password;
		cin >> name >> password;
		ifstream in(teller_db);
		bool done = false;
		string inName, inPassword;
		while (!in.eof()) {
			in >> inName;
			in >> inPassword;

			if (name == inName&&password == inPassword)
			{
				done = true;
				break;
			}
			in.ignore();
		}
		if (done) {
			teller = true;
			return done;
		}
		else {
			system("CLS");
			cout << "Sorry, Wrong Access! " << endl << " Please try again...\n" << endl;
			return tellerLogin();
		}

	}

	clientNode* searchListByName(string name) {
		return Client.searchByName(name);
	}

	void listDBimport() {
		ifstream in, in2, in3;
		in.open(input_client_db);
		in2.open(input_loan_db);
		in3.open(input_history_db);
		int ID = -1;
		string name;
		string mob;
		string mail;
		string address;
		string job;
		string nationality;
		string password;
		float loans;
		float balance;
		int data_size;
		bool   have_loan;
		bool   hold = 0;
		int i = 0;
		while (!in.eof()) {
			int temp = ID;
			in >> ID;
			in >> name;
			in >> balance;
			in >> mob;
			in >> mail;
			in >> address;
			in >> job;
			in >> nationality;
			in >> have_loan;
			in >> hold;
			in >> password;

			if (temp == ID)break;
			clientNode *temps;
			temps = Client.addbFile(ID, name, balance, mob, mail, address, job, nationality, have_loan, hold, password);
			in2 >> loans;
			temps->clientData.clientLoan = loan.addb(loans);
			in3 >> data_size;
			vector<string> info;
			for (int j = 0; j < data_size; j++) {
				string line;
				in3 >> line;
				info.push_back(line);

			}
			temps->clientData.clientHistory = History.addb(info);
			in.ignore();

		}
		in.close();
		in2.close();
		in3.close();

	}

	clientNode* searchListByID(int id) {
		return Client.searchByID(id);
	}

	void listDBexport() {
		vector <string> info;
		int data_size;
		ofstream out(output_client_DB);
		ofstream out2(output_loan_DB);
		ofstream out3(output_history_DB);
		clientNode * temp = Client.getchain();
		while (temp != NULL) {
			out.clear();
			out << temp->clientData.ID << "\t";
			out << temp->getName() << "\t";
			out << temp->getBalance() << "\t";
			out << temp->getMob() << "\t";
			out << temp->getMail() << "\t";
			out << temp->getAddress() << "\t";
			out << temp->getJob() << "\t";
			out << temp->getNationality() << "\t";
			out << temp->getHaveLoan() << "\t";
			out << temp->getHold() << "\t";
			out << temp->getPassword() << "\n";
			out2 << temp->clientData.clientLoan->getLoan() << "\n";
			info = temp->clientData.clientHistory->getData();
			data_size = temp->clientData.clientHistory->getDataSize();
			out3 << data_size << "\n";

			for (int i = 0; i < data_size; i++) {
				out3 << info[i] << "\n";
			}
			temp = temp->next;
		}
	}



	void viewClient(bool * indicator2)
	{
	ClientEntry:
		cout << endl << endl;
		cout << "Kindly enter the number of the operation you want to make: " << endl << " 1) Withdraw an amount. " << endl << " 2) Deposit to your account" << endl << " 3) Make a Transaction. " << endl << " 4) View Your Balance"
			<< endl << " 5) Query about your loan. " << endl << " 6) View your History. " << endl << " 7) Logout. " << endl << " 8) Exit" << endl;

		char opNum;
		opNum = _getch();
		string tryAgain;
		string to_client;
		switch (opNum) {

		case '1':
		{	label1:
			float amount;
			system("CLS");
			cout << " Please enter the amount you want to take: " << "\t";
			cin >> amount;
			bool valid = transaction.withdraw(&currentClient->clientData.balance, amount);

			if (valid) {
				History.newWithDraw(currentClient->clientData.clientHistory, amount, currentClient->clientData.balance);
				cout << " Currently your balance is: " << currentClient->getBalance() << " L.E" << endl << "If you want to return back to the main page press(B)" << endl;
			}
			else cout << " Unfortunately, you can't withdraw this amount. If you want to try another amount press (Y) " << endl << " Else to return back to the main page press (B)" << endl;


			cin >> tryAgain;

			if (tryAgain == "Y") {
				system("CLS");
				goto label1;
			}
			else if (tryAgain == "B") {
				system("CLS");
				goto ClientEntry;
			}
			//system("CLS");
		}
				break;

		case '2':
		{
			float amount;
			cout << " Please enter the amount you want to deposit: " << "\t";
			cin >> amount;

			transaction.deposit(&currentClient->clientData.balance, amount);

			History.newDeposit(currentClient->clientData.clientHistory, amount, currentClient->clientData.balance);
			cout << " Currently your balance is: " << currentClient->getBalance() << " L.E" << endl << "If you want to return back to the main page press(B)" << endl;


			cin >> tryAgain;


			if (tryAgain == "B")
				system("CLS"); {
				goto ClientEntry;
			}
		}
		break;

		case '3':
		{   label2:
			bool TransactionValid;
			float amount1;
			float BalanceOfFirstUser = currentClient->getBalance();

			cout << "Please enter the name of the client you want to transfer an amount to: " << "\t";
		Label3:
			cin >> to_client;
			clientNode *otherClient;
			otherClient = Client.searchByName(to_client);
			if (otherClient == NULL) {
				cout << "Sorry please check the name you have entered and try again" << endl;
				goto Label3;

			}

			cout << "Please enter the amount you want to transfer: " << "\t";
			cin >> amount1;

			TransactionValid = transaction.transaction(&currentClient->clientData.balance, &otherClient->clientData.balance, amount1);
			if (TransactionValid) {
				History.newTrans(currentClient->clientData.clientHistory, amount1, to_client);
				cout << "Your transaction is done Successfully! " << endl << "If you want to return back to the main page press(B)" << endl;
			}
			else {
				cout << " Sorry, this transaction can't be done! The amount you've entered is more than your current balance." << endl << " If you want to try again press (Y) "
					<< endl << " Else to return back to the main page press (B)" << endl;
			}
			cin >> tryAgain;

			if (tryAgain == "Y") {
				system("CLS");
				goto label2;
			}
			else if (tryAgain == "B") {
				system("CLS");
				goto ClientEntry;
			}
		}
				break;

		case '4':
		{cout << " Your current balance is: " << currentClient->getBalance() << " L.E" << endl << " If you want to return back to the main page press (B)" << endl;

		cin >> tryAgain;

		if (tryAgain == "B") {
			system("CLS");
			goto ClientEntry;
		}}
		break;

		case '5':
		{	float loanData = currentClient->clientData.clientLoan->getLoan();
		cout << "Your current Loan is: " << loanData << " L.E" << endl;
		cout << " If you want to return back to the main page press (B)" << endl;
		cin >> tryAgain;

		if (tryAgain == "B") {
			system("CLS");
			goto ClientEntry;
		}

		}
		break;

		case '6':
		{	History.printNode(currentClient->clientData.clientHistory);

		cout << " If you want to return back to the main page press (B)" << endl;
		cin >> tryAgain;

		if (tryAgain == "B") {
			system("CLS");
			goto ClientEntry;
		}
		}
		break;

		case '7':
		{
			system("CLS");
			cout << "Your account has been closed successfully." << endl << endl << "                         *********** Goodbye************" << endl << endl;
			return;
		}

		case '8':
		{
			(*indicator2) = false;
			return;
		}

		}

	}

};



void main() {

	linker L;
	char accountType;
	L.listDBimport();

	bool indicator2 = true;
	while (indicator2) {
		cout << "Please choose your account type: \n\t 1) Teller\n\t 2) Client\n\n\n";
		accountType = _getch();
		system("CLS");
		if (accountType == '1') {

			if (L.tellerLogin()) { 
				system("CLS");
				cout << "Welcome...\n"; 
			}
			// while loop to goback to main page:
			bool indicator = true;
			while (indicator) {



				cout << endl << " Kindly enter the number of the operation you want to make: " << endl
					<< " 1) Create a New Account." << endl << " 2) Hold an Account. "
					<< endl << " 3) Make a Transaction. " << endl << " 4) Query about a Loan."
					<< endl << " 5) Check Client's Balance." << endl << " 6) Logout." << endl
					<< " 7) Exit" << endl;

				char operation = _getch();
				system("CLS");
				switch (operation)
				{
				case '1': {
					cout << endl << " Please enter Client's Name: ";
					string name;
					cin >> name;
					cout << " Mobile Number: ";
					string mob;
					cin >> mob;
					cout << " Client's Email: ";
					string mail;
					cin >> mail;
					cout << " Client's Address: ";
					string address;
					cin >> address;
					cout << " Client's Job: ";
					string job;
					cin >> job;
					cout << " Client's Nationality: ";
					string nationality;
					cin >> nationality;
					cout << " Client's Main Balance: ";
					float  balance;
					cin >> balance;
					cout << " Client's Password: ";
					string password;
					cin >> password;
					L.addClient(name,balance ,mob, mail, address, job, nationality, false, false,password);
					system("CLS");
					cout << "A new account has been created successfully.." << endl;
				
					break;
				}
				case '2': {
					bool  loan;
					bool  hold;
					char getby;
					cout << " Hold an account by Client's Name or ID : \n\t 1) ID  \n\t 2) Name\n";
					cin.clear();
					getby = _getch();
					system("CLS");
					if (getby == '1') {
						int id;
						cout << "Please enter the ID of the account you want to hold: ";
						cin.ignore();
						cin >> id;
						clientNode *temp = L.searchListByID(id);
						temp->setHold(true);
					}
					else if (getby == '2')
					{
						string name;
						cout << "Please enter the Name of the account you want to hold: ";
						cin >> name;
						clientNode *temp = L.searchListByName(name);
						temp->setHold(true);

					}
					cout << "\n Operation successful...Client account has been held\n";

					break;
				}

				case '3':
				{int ID1, ID2;
				float amt;
				bool trans = false;
				clientNode* temp1, *temp2;
				system("CLS");
					cout << "\n enter client(1)'s ID:\n";
					cin >> ID1;
					temp1 = L.searchListByID(ID1);
					cout << "\n enter client(2)'s ID:\n";
					cin >> ID2;
					temp2 = L.searchListByID(ID2);
					cout << "\n enter amount to be transfared:\n";
					cin >> amt;
					system("CLS");
					trans=L.transaction.transaction(&temp1->clientData.balance, &temp2->clientData.balance,amt);
					if (trans)
						cout << "transaction has been done successfully...\n";
					else cout<<"sorry check your inputs\n";


					break; }
				case '4':
				{
					char getby;
					cout << " Query about a Client's Loan by his name or ID : \n\t 1) ID  \n\t 2) Name\n";
					cin.clear();
					getby = _getch();
					system("CLS");
					if (getby == '1') {
						int id;
						cout << "Please enter the ID : ";
						cin.ignore();
						cin >> id;
						clientNode *temp = L.searchListByID(id);
						cout << temp->clientData.clientLoan->getLoan() << " L.E" << endl;
					}
					else if (getby == '2')
					{
						string name;
						cout << "Please enter the Name: ";
						cin >> name;
						clientNode *temp = L.searchListByName(name);
						cout << temp->clientData.clientLoan->getLoan() << " L.E" << endl;

					}
					break;
				}
				case '5':
				{
					char getby;
					cout << " Check Client's Balance by his name or ID : \n\t 1) ID  \n\t 2) Name\n";
					cin.clear();
					getby = _getch();
					system("CLS");
					if (getby == '1') {
						int id;
						cout << "Please enter the ID : ";
						cin.ignore();
						cin >> id;
						clientNode *temp = L.searchListByID(id);
						cout << temp->clientData.balance << " L.E" << endl;
					}
					else if (getby == '2')
					{
						string name;
						cout << "Please enter the Name: ";
						cin >> name;
						clientNode *temp = L.searchListByName(name);
						cout << temp->clientData.balance << " L.E" << endl;

					}
					break;
				}

				case '6':
				{  system("CLS");
				indicator = false;
				break; }
				case '7':
				{   system("CLS");
				indicator = false;
				indicator2 = false;
				break;
				}

				default:
					break;
				}
			}

		}
		else if (accountType == '2') {
			if ( L.loginClient()) {
				L.viewClient(&indicator2);
			}
			
		}
	}

	//	linker L;
	//	L.listDBimport();

	//L.searchid(8);

		/*L.addClient("Ahmed1",0, "01235478952", "ahmed@gmail.com", "22 ahmed el khashab", "accountat", "egyptian", false, true,"546464");
		L.addClient("Ahmed2",0, "01235478952", "ahmed@gmail.com", "22 ahmed el khashab", "accountat", "egyptian", false, true,"5646464");
		L.addClient("Ahmed3",0, "01235478952", "ahmed@gmail.com", "22 ahmed el khashab", "accountat", "egyptian", false, true,"64646464");
		L.addClient("Ahmed4",0, "01235478952", "ahmed@gmail.com", "22 ahmed el khashab", "accountat", "egyptian", false, true,"2121212");
*/
	/*L.loginClient();
	L.viewClient();*/

	L.listDBexport();
	cout << endl << " Bye =)" << "\n";
	system("pause");
}
