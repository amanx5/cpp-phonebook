# contact_manager

The “Contact Manager” is an console based standalone application developed using C++. It is based on various C++ features such as file handling, classes functions, streams, etc. It’s source code contains 2 classes that are:

class utility: Contains all the helper functions and variables.

•	static const int num_size=10;      //determines contact number length

•	static const int name_size=20;	    //determines contact name length

•	static bool isfileempty()	         //checks whether the textfile is empty

•	static bool isvalidname(string s) //checks whether the name is valid

•	static bool isvalidnum(string s)  //checks whether the number is valid


class application: Contains all the functions for the main menu.

•	static void read()		//displays all the contacts stored in textfile

•	static void add()		//adds a new contact in the textfile 

•	static void search()	//searches for a contact in the textfile

•	static void deleter()	//deletes a contact from the textfile

From User’s Perspective
It is a menu driven application that allows user to manage contacts stored in a local textfile. Main menu allows user to perform some action based on the key he or she presses on the keyboard. 

V	On pressing this key, all the contacts are displayed on the screen.

S	It allows user to search for a contact by simply inputting it’s name.

N	It allows user to add a contact by inputting contact name & number.

D	It allows user to delete a contact by simply inputting it’s name.

A	On pressing this key, information about the application is displayed.

X	This key terminates the application.
