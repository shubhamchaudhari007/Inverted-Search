# 🔎 Inverted Search – C Project

## 🚀 Overview

The **Inverted Search** project is a command-line application developed in **C** that builds an **inverted index** from multiple text files.

Instead of storing data as:

```
File → Words
```

It stores as:

```
Word → Files → Frequency
```

This technique is widely used in:

* Search engines
* Document indexing systems
* Information retrieval

---

## 🎯 Features

### 🗂️ Database Creation

* ✅ Accept multiple `.txt` files as input
* ✅ Validate file format and content
* ✅ Avoid duplicate files
* ✅ Build inverted index using hashing

### 📊 Display Mode

* ✅ Display indexed words
* ✅ Show number of files containing each word
* ✅ Show word frequency per file
* ✅ Proper aligned output format

### 🔍 Search Mode *(Extendable)*

* ✅ Search word in database
* ✅ Display file locations

### 💾 Save & Update *(Extendable)*

* ✅ Save database to file
* ✅ Reload database

---

## 🧠 Concepts Used

* Hashing (Indexing technique)
* Linked Lists (Single & Multi-level)
* File Handling in C
* Dynamic Memory Allocation (`malloc`)
* String Manipulation
* Data Structures Design

---

## ⚙️ Technologies Used

* **Language:** C
* **Platform:** Linux / Windows
* **Compiler:** GCC

---

## 🏗️ Project Structure

```id="invstruct"
Inverted_Search/
│── main.c
│── validate.c
│── file_utils.c
│── create_db.c
│── display_db.c
│── Inverted.h
```

---

## ▶️ How to Run

### 1. Compile

```bash id="inv1"
gcc *.c -o search
```

### 2. Run Program

```bash id="inv2"
./search file1.txt file2.txt file3.txt
```

---

## 📋 Menu Options

```id="invmenu"
1. Create DataBase
2. Display DataBase
3. Search DataBase
4. Save Database
5. Update DataBase
```

---

## 💻 Sample Output

```id="invsample"
Index  | Word                 | File Count | Files (FileName : Count)
---------------------------------------------------------------------
0      | apple                | 2          | file1.txt : 3
                                        | file2.txt : 1
1      | ball                 | 1          | file2.txt : 5
```

---

## ⚠️ Limitations

* ❌ Only supports `.txt` files
* ❌ Case-sensitive words
* ❌ No GUI (CLI-based)
* ❌ Limited punctuation handling

---

## 🔮 Future Enhancements

* 🔹 Case-insensitive search
* 🔹 Sorting (alphabetical / frequency-based)
* 🔹 Save & load database
* 🔹 GUI version
* 🔹 Stop-word removal (like "the", "is")

---

## 🧩 Challenges Faced

* Handling multiple linked structures
* Avoiding segmentation faults
* Designing efficient hashing logic
* Managing dynamic memory safely

---

## 📚 Learning Outcomes

* Strong understanding of **hash tables**
* Practical use of **linked lists**
* Experience with **file processing in C**
* Improved debugging and memory handling

---

## 📌 Author

**Shubham Chaudhari**
