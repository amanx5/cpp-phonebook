#define filepath "contacts.txt"
using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>   //for getch()
#include <algorithm> //for transform()

class utility
{
public:
    static const int num_size = 10;
    static const int name_size = 20;

    static bool isfileempty()
    {
        ifstream reader(filepath, ios::in);
        reader.seekg(0, ios::end);
        if (!reader || 0 == reader.tellg()) // if file doesnt exist or is empty
            return true;
        else
            return false;
    }

    static bool isvalidname(string s)
    {
        // check for invalid first character
        if (isalpha(s[0]) == 0)
        {
            cout << "*First character should be an alphabet*\n";
            return false;
        }

        // check for non alphabets
        for (int i = 0; i < s.length(); i++)
            if (isalpha(s[i]) == 0 && s[i] != ' ')
                return false;

        // check for same name already in file
        if (!isfileempty()) // proceed only if file is not empty, if file is empty then name doesnt exist in file
        {
            ifstream reader(filepath, ios::in);
            reader.seekg(0, ios::beg);
            string line, name;

            while (!reader.fail())
            {
                getline(reader, line);
                if (line == "")
                    return true;        // no more lines in file, string s not found in file
                name = line.substr(10); // extract name from line, name starts from 10th index of string line as first 10 characters are for mobile number
                if (name == s)
                {
                    cout << "*Contact with this name already exists, Try a different name.*\n";
                    return false;
                }
                line = ""; // otherwise last line is coming twice
            }
        }
        return true; // passes all the checks
    }

    static bool isvalidnum(string s)
    {
        // check if string contains numbers only or not
        for (int i = 0; i < s.length(); i++)
        {
            if (int(s[i] - 48) >= 0 && int(s[i] - 48) <= 9)
                continue;
            else
                return false;
        }

        // check for same number already in file
        if (!isfileempty()) // proceed only if file is not empty, if file is empty then number doesnt exist in file
        {
            ifstream reader(filepath, ios::in);
            reader.seekg(0, ios::beg);

            string line, num;

            while (!reader.fail())
            {
                getline(reader, line);
                if (line == "")
                    return true;
                num = line.substr(0, 10);
                if (num == s)
                {
                    cout << "*Contact with this number already exists, Try a different number.*\n";
                    return false;
                }
                line = ""; // otherwise last line is coming twice
            }
        }
        return true; // passed both checks
    }
};

class application
{
public:
    static void read()
    {
        system("CLS");

        if (utility::isfileempty() == true)
            cout << "\n*No contacts found, Press key [N] to add contacts*\n\n";

        else
        {
            ifstream reader(filepath, ios::in);
            string s;
            reader.seekg(0, ios::beg);
            cout << "# ALL CONTACTS #\n\n";
            while (!reader.eof())
            {
                getline(reader, s);
                if (s != "")
                    cout << s.substr(0, 10) << "\t" << s.substr(10) << endl;
            }
            reader.close();
            cout << "\nPress any key to open MAIN MENU >>";
            getch();
            system("CLS");
        }
    }

    static void add()
    {
        system("CLS");
        cout << "# CREATE CONTACT #\n";
        fstream appender(filepath, ios::app);
        string name, num;

        do
        {
            fflush(stdin);
            cout << "\n*Name should contain alphabets only and should be 2 to " << utility::name_size << " characters long*\n";
            cout << "Enter Contact Name >>";
            getline(cin, name); // use getline to read multiple words string
            transform(name.begin(), name.end(), name.begin(), ::toupper);

        } while (name.length() < 2 || name.length() > utility::name_size || utility::isvalidname(name) != true);

        do
        {
            fflush(stdin);
            cout << "\n*Number should be numeric and " << utility::num_size << " digits long*\n";
            cout << "Enter Contact Number >>";
            cin >> num;
        } while (num.length() != utility::num_size || utility::isvalidnum(num) != true); // disallow invalid numbers

        appender << num << name << "\n";
        appender.close();

        system("CLS");
        cout << "\n~ The contact is added successfully ~\n\n";

        char ch;
        cout << "Proceed with pressing:";
        cout << "\nKey [N] to add another contact";
        cout << "\nAny other key to open MAIN MENU ";
        ch = getch();

        if (ch == 'n' || ch == 'N')
            add();
        system("CLS");
    }

    static void search()
    {
        system("CLS");

        if (utility::isfileempty())
            cout << "\n*Can't Search:  No contacts are present*\n\n";

        else
        {
            bool found = false;
            string s;
            cout << "# SEARCH CONTACTS #\n\n";
            fflush(stdin);
            cout << "Enter name of the contact >>";
            getline(cin, s);
            transform(s.begin(), s.end(), s.begin(), ::toupper);

            ifstream reader(filepath, ios::in);
            reader.seekg(0, ios::beg);

            cout << "\nSearch Results:\n";
            string line, name;
            while (!reader.fail())
            {
                getline(reader, line);
                if (line == "")
                    break;
                name = line.substr(10);

                if (name.find(s, 0) != string::npos) // npos is a value that is returned if match is not found
                {
                    cout << line.substr(0, 10) << "\t" << line.substr(10) << endl; // print the result
                    found = true;
                    // break; dont break for getting multiple results
                }
                line = ""; // otherwise last line is coming twice
            }

            if (!found)
                cout << "\n~ Contact not present ~\n"; // if no matching name is found
            reader.close();
            char ch;
            cout << "\nProceed with pressing:";
            cout << "\nKey [S] to search another contact";
            cout << "\nAny other key to open MAIN MENU ";
            ch = getch();

            if (ch == 's' || ch == 'S')
                search();
            system("CLS");
        }
    }

    static void deleter()
    {
        system("CLS");

        if (utility::isfileempty())
            cout << "\n*Can't Delete:  No contacts are present*\n\n";

        else
        {
            string name, line;
            bool done = false;
            cout << "# DELETE A CONTACT #\n\n";
            fflush(stdin);
            cout << "Enter name of the contact >>";
            getline(cin, name);
            transform(name.begin(), name.end(), name.begin(), ::toupper);

            ifstream fin;
            fin.open(filepath);
            ofstream temp;
            temp.open("temp.txt");

            while (getline(fin, line))
            {
                if (line.substr(10) == name)
                {
                    done = true;
                    system("CLS");
                    cout << "\n~ The contact is deleted successfully ~\n\n";
                    continue;
                }
                temp << line << endl;
            }

            if (!done)
                cout << "\n~ Contact not present ~\n\n";
            temp.close();
            fin.close();
            remove(filepath);
            rename("temp.txt", filepath);

            char ch;
            cout << "Proceed with pressing:";
            cout << "\nKey [D] to delete another contact";
            cout << "\nAny other key to open MAIN MENU ";
            ch = getch();

            if (ch == 'd' || ch == 'D')
                deleter();
            system("CLS");
        }
    }
};

int main()
{
    char ch;
    do
    {
        cout << "\t\t\t\tMAIN MENU\n";
        cout << "\n [V] => View List of all contacts";
        cout << "\n [S] => Search for a contact ";
        cout << "\n [N] => Add a new contact ";
        cout << "\n [D] => Delete a contact ";
        cout << "\n [A] => About the application ";
        cout << "\n [X] => Close the application ";

        cout << "\n\n Press any key >>";
        ch = getch();

        if (ch == 'v' || ch == 'V')
            application::read();
        else if (ch == 's' || ch == 'S')
            application::search();
        else if (ch == 'n' || ch == 'N')
            application::add();
        else if (ch == 'd' || ch == 'D')
            application::deleter();
        else if (ch == 'a' || ch == 'A')
        {
            system("CLS");
            cout << "CONTACT MANAGEMENT APPLICATION\n\n"
                 << "This application is developed in C++ language.\n"
                 << "Press any key to open MAIN MENU >>";
            getch();
            system("CLS");
        }
        else if (ch != 'x' && ch != 'X')
        {
            system("CLS");
            cout << "\n*Invalid key! Please check the list of valid keys below* \n\n";
        }

    } while (!(ch == 'X' || ch == 'x'));
}
