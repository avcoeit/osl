#!/bin/bash

FILE="addressbook.txt"

# 1) Create Address Book
createBook() {
    if [ -e "$FILE" ]; then
        echo "Address book already exists."
    else
        touch "$FILE"
        echo "Address book created."
    fi
}

# 2) View Address Book
viewBook() {
    if [ ! -s "$FILE" ]; then
        echo "Address book is empty."
    else
        echo "----- Address Book -----"
        cat "$FILE"
    fi
}

# 3) Add a Record
addRecord() {
    echo "Enter: LastName,FirstName,Email,Phone"
    read record
    echo "$record" >> "$FILE"
    echo "Record added."
}

# 4) Delete a Record
deleteRecord() {
    echo "Enter name or email to search:"
    read search
    grep -n "$search" "$FILE"       # show matching lines with numbers

    echo "Enter line number to delete:"
    read line
    sed -i "${line}d" "$FILE"       # delete that line
    echo "Record deleted."
}

# 5) Modify a Record
modifyRecord() {
    echo "Enter name or email to search:"
    read search
    grep -n "$search" "$FILE"

    echo "Enter line number to change:"
    read line
    echo "Enter new record (LastName,FirstName,Email,Phone):"
    read new

    sed -i "${line}s/.*/$new/" "$FILE"    # replace full line
    echo "Record updated."
}

# 6) Exit
exitProgram() {
    echo "Goodbye!"
    exit 0
}

# Menu Loop
while true; do
    echo "------ Address Book Menu ------"
    echo "1. Create Address Book"
    echo "2. View Address Book"
    echo "3. Add Record"
    echo "4. Delete Record"
    echo "5. Modify Record"
    echo "6. Exit"
    echo "Enter your choice: "
    read choice

    case $choice in
        1) createBook ;;
        2) viewBook ;;
        3) addRecord ;;
        4) deleteRecord ;;
        5) modifyRecord ;;
        6) exitProgram ;;
        *) echo "Invalid choice! Please pick 1-6." ;;
    esac
done

# save file addressbook.sh
#open terminal where file is save run commond >>>>     bash addressbook.sh

