# Phonebook

A simple **Contact Management Application** built in C++ with a terminal-based user interface. This application allows you to manage contacts (phone numbers) using add, view, search, and delete operations.

## Features

- **View All Contacts** - Display all saved contacts in a formatted list
- **Search Contacts** - Find contacts by name
- **Add New Contact** - Create new contact entries with validation
-  **Delete Contact** - Remove contacts from the contact storage.

## Requirements

- **Some C++ Compiler:**  The app is developed and tested on **GCC 6.3.0**.

- **Operating System:** Windows 

    > The app currently relies on `conio.h` which is Windows-specific. For cross-platform support, see [Cross-Platform Guide](#cross-platform-support) section below.

## Setup

### Using G++
```bash
g++ -o app.exe app.cpp
```

## Usage

### Run the Application

```bash
./app.exe
```


### Main Menu

When you launch the application, you'll see the main menu:

```
					MAIN MENU

 [V] => View List of all contacts
 [S] => Search for a contact 
 [N] => Add a new contact 
 [D] => Delete a contact 
 [A] => About the application 
 [X] => Close the application 

 Press any key >>
```

### Operations

#### 1️⃣ View All Contacts (Press V)

This displays all your saved contacts in a formatted table with phone number and name:

```
# ALL CONTACTS #

1234567890	JOHN DOE
9876543210	JANE SMITH
5555555555	BOB JOHNSON
```

**Press any key to return to main menu**

---

#### 2️⃣ Add New Contact (Press N)

Create a new contact with validation:

**Input Prompts:**
- **Name Requirements:**
  - Must start with a letter
  - Can contain alphabets and spaces only
  - Length: 2-20 characters
  - Uppercase conversion applied automatically

- **Phone Number Requirements:**
  - Exactly 10 digits
  - Numbers only
  - Must be unique (no duplicates allowed)

**Example Flow:**
```
# CREATE CONTACT #

*Name should contain alphabets only and should be 2 to 20 characters long*
Enter Contact Name >>alice johnson

*Number should be numeric and 10 digits long*
Enter Contact Number >>9876543210

~ The contact is added successfully ~

Proceed with pressing:
Key [N] to add another contact
Any other key to open MAIN MENU
```

---

#### 3️⃣ Search for a Contact (Press S)

Find contacts by name with partial matching:

```
# SEARCH CONTACTS #

Enter name of the contact >>john

Search Results:
1234567890	JOHN DOE
```

**Features:**
- Case-insensitive search (automatic uppercase conversion)
- Partial name matching supported
- Shows all matching results
- Returns "~ Contact not present ~" if no match found

---

#### 4️⃣ Delete a Contact (Press D)

Remove a contact from your database:

```
# DELETE A CONTACT #

Enter name of the contact >>jane smith

~ The contact is deleted successfully ~

Proceed with pressing:
Key [D] to delete another contact
Any other key to open MAIN MENU
```

**Notes:**
- Contact name must match exactly (case-insensitive)
- Action is permanent and cannot be undone
- Returns "~ Contact not present ~" if contact not found

---

#### 5️⃣ About (Press A)

Displays information about the application

---

#### ❌ Exit (Press X)

Closes the application and saves all data

## Contact Storage

Contacts are stored in `contacts.txt` in the same directory as the executable. Each contact is stored on a single line in the format:

```
[10-digit-phone-number][CONTACT-NAME]
```

**Example contacts.txt:**
```
1234567890JOHN DOE
9876543210JANE SMITH
5555555555BOB JOHNSON
```

## Validation Rules

| Field | Rules |
|-------|-------|
| **Name** | • First character must be a letter<br>• Only letters and spaces allowed<br>• Length: 2-20 characters<br>• Must be unique<br>• Automatically converted to uppercase |
| **Phone** | • Exactly 10 digits required<br>• Numbers only<br>• Must be unique<br>• No duplicates allowed |


## Cross-Platform Support

> ⚠️ **Warning:** The cross-platform support options below are **not tested**. Use them at your own risk. They are provided as guidance only.

The application currently requires **Windows** due to its dependency on `conio.h`. If you want to adapt this for **Linux/macOS**, you can replace `conio.h` with platform-specific alternatives:

**Option 1: Using Preprocessor Directives**

Replace the `#include <conio.h>` line with:

```cpp
#ifdef _WIN32
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
    
    // Linux/macOS implementation of getch()
    int getch() {
        struct termios oldattr, newattr;
        int ch;
        tcgetattr(STDIN_FILENO, &oldattr);
        newattr = oldattr;
        newattr.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
        return ch;
    }
#endif
```

Also replace `system("CLS")` with platform-specific equivalents:

```cpp
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
```

**Option 2: Using ncurses Library (Recommended for Production)**

A more robust cross-platform alternative. Install ncurses:
- Linux: `sudo apt-get install libncurses-dev`
- macOS: `brew install ncurses`
- Windows: `pacman -S mingw-w64-x86_64-ncurses` (MinGW)

Then modify the code to use ncurses functions instead of conio.h.
