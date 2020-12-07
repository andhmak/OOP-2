/* File: school.h */

#include <iostream>
#include <string>

class Person {
    std::string name;       // όνομα του μαθητή
    short floor_num;        // αριθμός οροόφου όπου βρίσκεται η τάξη/προορισμός του
    short classroom_num;    // αριθμός/θέση της τάξης/προορισμού του στον όροφο
    protected:
        bool in;            // αν βρίσκεται μέσα στην τάξη ή όχι
        int tiredness;      // βαθμός κούρασης
    public:
        Person(const char* init_name, short init_floor_num, short init_classroom_num); // Constructor
        virtual ~Person() = 0;
        void set_in() { in = true; }                                                // Mutator
        std::string get_name() const { return name; }                               // +
        short get_floor_num() const { return floor_num; }                           // |  Accessors
        short get_classroom_num() const { return classroom_num; }                           // +
};

// Κλάση που αναπαριστά έναν μαθητή
class Student : public Person {
    public:
        Student(const char* init_name, short init_floor_num, short init_classroom_num); // Constructor
        ~Student();                                                                 // Destructor (εκτυπώνει και τα δεδομένα του μαθητή)
        virtual void attend(int hours) = 0;
        void print() const { std::cout << get_name() << ", tiredness: " << tiredness << std::endl; }    // Συνάρτηση εκτύπωσης (εκτυπώνει το όνομα)
};

class Junior : public Student {
    static int lj;
    public:
        Junior(const char* init_name, short init_floor_num, short init_classroom_num)
        :   Student(init_name, init_floor_num, init_classroom_num) { }
        ~Junior() { }
        static void set_lj(int new_lj) { lj = new_lj; }
        void attend(int hours) { tiredness += lj*hours; }
};

class Senior : public Student {
    static int ls;
    public:
        Senior(const char* init_name, short init_floor_num, short init_classroom_num)
        :   Student(init_name, init_floor_num, init_classroom_num) { }
        ~Senior() { }
        static void set_ls(int new_ls) { ls = new_ls; }
        void attend(int hours) { tiredness += ls*hours; }
};

// Κλάση που αναπαριστά έναν δάσκαλο
class Teacher : public Person {
    static int lt;
    public:
        Teacher(const char* init_name, short init_floor_num, short init_classroom_num); // Constructor
        ~Teacher();                                                                     // Destructor (εκτυπώνει και τα δεδομένα του δασκάλου)
        static void set_lt(int new_lt) { lt = new_lt; }
        void teach(int hours) { tiredness += lt*hours; }
        void print() const { std::cout << "The teacher is: " << get_name() << ", tiredness: " << tiredness << std::endl; }  // Συνάρτηση εκτύπωσης (εκτυπώνει το όνομα)
};

class Area {
    Student* student;   // πίνακας μαθητών (δεικτών σε αντικείμενα μαθητών) στην αυλή
    public:
        Area() : student(NULL) { }          // Constructor
        virtual ~Area() = 0;                // Destructor
        void enter(Student& new_student) { student = &new_student; }    // Βάζει τον μαθητή/όρισμα στην αυλή
        Student* exit() { return student; } // Αφαιρεί τον τελευταίο μαθητή από την αυλή και επιστρέφει δείκτη σε αυτόν
};

// Κλάση που αναπαριστά μια αυλή
class Yard : public Area {
    public:
        Yard() { std::cout << "A New Yard has been created!" << std::endl; }    // Constructor
        ~Yard() { std::cout << "A Yard to be destroyed!" << std::endl; }        // Destructor
        void enter(Student& new_student);   // Βάζει τον μαθητή/όρισμα στην αυλή
        Student* exit();                    // Αφαιρεί τον τελευταίο μαθητή από την αυλή και επιστρέφει δείκτη σε αυτόν
};

// Κλάση που αναπαριστά ένα κλιμακοστάσιο
class Stairs : public Area {
    public:
        Stairs() { std::cout << "New Stairs has been created!" << std::endl; }  // Constructor
        ~Stairs() { std::cout << "Stairs to be destroyed!" << std::endl; }      // Destructor
        void enter(Student& new_student);   // Βάζει τον μαθητή/όρισμα στην αυλή
        Student* exit();            // Αφαιρεί τον τελευταίο μαθητή από την αυλή και επιστρέφει δείκτη σε αυτόν
};

// Κλάση που αναπαριστά έναν διάδρομο
class Corridor : public Area {
    public:
        Corridor() { std::cout << "A New Corridor has been created!" << std::endl; }    // Constructor
        ~Corridor() { std::cout << "A Corridor to be destroyed!" << std::endl; }        // Destructor
        void enter(Student& new_student);   // Βάζει τον μαθητή/όρισμα στην αυλή
        Student* exit();                // Αφαιρεί τον τελευταίο μαθητή από την αυλή και επιστρέφει δείκτη σε αυτόν
};

// Κλάση που αναπαριστά μια τάξη
class Classroom {
    int capacity;       // χωρητικότητα σε μαθητές
    Student** students; // πίνακας μαθητών (δεικτών σε αντικείμενα μαθητών) που βρίσκονται στην τάξη
    Teacher* teacher;   // ο δάσκαλος που βρίσκεται στην τάξη (δείκτης στο αντικείμενο του δασκάλου, αν δεν έχει φτάσει NULL)
    int student_num;    // πλήθος μαθητών που βρίσκονται στην τάξη
    public:
        Classroom(int init_capacity);   // Constructor
        ~Classroom();                   // Destructor
        void enter(Student& student);           // Βάζει τον μαθητή/όρισμα στην τάξη
        void place(Teacher& teacher_in);        // Θέτει τον δάσκαλο/όρισμα ως τον δάσκαλο της τάξης, ενημερώνοντάς τον πως εισήλθε
        void operate(int hours);
        void print(short classroom_number) const;   // Συνάρτηση εκτύπωσης (εκτυπώνει τους μαθητές και τον δάσκαλο που βρίσκονται στην τάξη)
};

// Κλάση που αναπαριστά έναν όροφο
class Floor {
    Classroom* classrooms[6];  // πίνακας τάξεων (δεικτών σε αντικείμενα τάξεων) του ορόφου 
    Corridor corridor;  // ο διάδρομος του ορόφου
    public:
        Floor(int cclass);                  // Constructor
        ~Floor();                           // Destructor
        void enter(Student& student);       // Βάζει τον μαθητή/όρισμα στον όροφο, βάζοντάς τον στον διάδρομο αν χωράει
        void place(Teacher& teacher) { classrooms[teacher.get_classroom_num()]->place(teacher); }  // Τοποθετεί τον δάσκαλο/όρισμα στον όροφό του,
                                                                                            // τοποθετώντας τον στην τάξη του
        void operate(int hours);
        void print(short floor_number) const;   // Συνάρτηση εκτύπωσης (εκτυπώνει τον διάδρομο και τις τάξεις του ορόφου)
};

// Κλάση που αναπαριστά ένα σχολείο
class School {
    Yard yard;          // η αυλή του σχολείου
    Stairs stairs;      // το κλιμακοστάσιο του σχολείου
    Floor* floors[3];   // πίνακας ορόφων (δεικτών σε αντικείμενα ορόφων) του σχολείου
    public:
        School(int cclass); // Constructor
        ~School();          // Destructor
        void enter(Student& student);   // Βάζει τον μαθητή/όρισμα στο σχολείο, πηγαίνοντάς τον όσο πιο κοντά γίνεται
                                        // στην τάξη του. Επιστρέφει το αν μπόρεσε να μπει τουλάχιστον στην αυλή ή όχι.
        void place(Teacher& teacher) { floors[teacher.get_floor_num()]->place(teacher); }   // Τοποθετεί τον δάσκαλο/όρισμα . στο σχολείο,
                                                                                            // τοποθετώντας τον στο όροφό του
        void operate(int hours);
        void print() const; // Συνάρτηση εκτύπωσης (εκτυπώνει την αυλή, το κλιμακοστάσιο και τους ορόφους του σχολείου)
};