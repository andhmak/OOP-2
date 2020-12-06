/* File: school.h */

#include <iostream>
#include <string>

class Person {
    std::string name;       // όνομα του μαθητή
    short floor_num;        // αριθμός οροόφου όπου βρίσκεται η τάξη/προορισμός του
    short classroom_num;    // αριθμός/θέση της τάξης/προορισμού του στον όροφο
    bool in;                // αν βρίσκεται μέσα στην τάξη ή όχι
    int tiredness;          // βαθμός κούρασης
    public:
        Person(const char* init_name, short init_floor_num, short init_classroom_num); // Constructor
        ~Person() = 0;
        void set_in() { in = true; }                                                // Mutator
        std::string get_name() const { return name; }                               // +
        short get_floor_num() const { return floor_num; }                           // |  Accessors
        short get_classroom_num() const { return classroom_num; }                           // +
};

// Κλάση που αναπαριστά έναν μαθητή
class Student : Person {
    public:
        Student(const char* init_name, short init_floor_num, short init_classroom_num); // Constructor
        ~Student();                                                                 // Destructor (εκτυπώνει και τα δεδομένα του μαθητή)
        virtual void attend(int hours) = 0;
        void print() const { std::cout << name << std::endl; }                      // Συνάρτηση εκτύπωσης (εκτυπώνει το όνομα)
};

class Junior : public Student {
    static int lj;
    public:
        Junior(const char* init_name, short init_floor_num, short init_classroom_num);
        ~Junior();
        void attend(int hours);
};

class Senior : public Student {
    static int ls;
    public:
        Senior(const char* init_name, short init_floor_num, short init_classroom_num);
        ~Senior();
        void attend(int hours);
};

// Κλάση που αναπαριστά έναν δάσκαλο
class Teacher : Person {
    static int lt;
    public:
        Teacher(const char* init_name, short init_floor_num, short init_classroom_num); // Constructor
        ~Teacher();                                                                     // Destructor (εκτυπώνει και τα δεδομένα του δασκάλου)                                          // Destructor (εκτυπώνει και τα δεδομένα του μαθητή)
        void teach(int hours);
        void print() const { std::cout << "The teacher is: " << name << std::endl; }    // Συνάρτηση εκτύπωσης (εκτυπώνει το όνομα)
};

class Area {
    Student* student;   // πίνακας μαθητών (δεικτών σε αντικείμενα μαθητών) στην αυλή
    public:
        Area();                         // Constructor
        ~Area();                        // Destructor
        void enter(Student& student);   // Βάζει τον μαθητή/όρισμα στην αυλή
        Student* exit();                // Αφαιρεί τον τελευταίο μαθητή από την αυλή και επιστρέφει δείκτη σε αυτόν
};

// Κλάση που αναπαριστά μια αυλή
class Yard {
    public:
        Yard();                         // Constructor
        ~Yard();                        // Destructor
};

// Κλάση που αναπαριστά ένα κλιμακοστάσιο
class Stairs {
    public:
        Stairs();                   // Constructor
        ~Stairs();                  // Destructor
};

// Κλάση που αναπαριστά έναν διάδρομο
class Corridor {
    public:
        Corridor();                     // Constructor
        ~Corridor();                    // Destructor
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
        bool enter(Student& student);   // Βάζει τον μαθητή/όρισμα στο σχολείο, πηγαίνοντάς τον όσο πιο κοντά γίνεται
                                        // στην τάξη του. Επιστρέφει το αν μπόρεσε να μπει τουλάχιστον στην αυλή ή όχι.
        void place(Teacher& teacher) { floors[teacher.get_floor_num()]->place(teacher); }   // Τοποθετεί τον δάσκαλο/όρισμα . στο σχολείο,
                                                                                            // τοποθετώντας τον στο όροφό του
        void operate(int hours);
        void print() const; // Συνάρτηση εκτύπωσης (εκτυπώνει την αυλή, το κλιμακοστάσιο και τους ορόφους του σχολείου)
};

/* File: school.cpp */

using namespace std;

// Συναρτήσεις της Student

// Constructor
Student::Student(const char* init_name, short init_floor_num, short init_classroom_num)
:   name(init_name), floor_num(init_floor_num), classroom_num(init_classroom_num)
{
    position = outside;
    cout << "A New Student has been created!" << endl;
    cout << name << endl;
    cout << "Floor " << floor_num + 1 << ", classroom " << classroom_num + 1 << endl;
}

// Destructor
Student::~Student() {
    cout << "A Student to be destroyed!" << endl;
    cout << name << endl;
    cout << "Floor " << floor_num + 1 << ", classroom " << classroom_num + 1<< endl;
    switch (position) {
        case at_yard:
            cout << "Situated in the yard" << endl;
            break;
        case at_stairs:
            cout << "Situated on the stairs" << endl;
            break;
        case at_corridor:
            cout << "Situated in the corridor" << endl;
            break;
        case at_classroom:
            cout << "Situated in the classroom" << endl;
            break;
        case outside:
            cout << "Situated outside" << endl;
    }
}

// Συναρτήσεις της Teacher

// Constructor
Teacher::Teacher(const char* init_name, short init_floor_num, short init_classroom_num)
:   name(init_name), floor_num(init_floor_num), classroom_num(init_classroom_num)
{
    in = false;
    cout << "A New Teacher has been created!" << endl;
    cout << name << endl;
    cout << "Floor " << floor_num + 1  << ", classroom " << classroom_num + 1 << endl;
}

// Destructor
Teacher::~Teacher() {
    cout << "A Teacher to be destroyed!" << endl;
    cout << name << endl;
    cout << "Floor " << floor_num + 1 << ", classroom " << classroom_num  + 1 << endl;
    cout << "Situated " << (in ? "in " : "outside ") << "the classroom" << endl;
}

// Συναρτήσεις της Yard

// Constructor
Yard::Yard(int init_capacity) : capacity(init_capacity) {
    students = new Student*[init_capacity];
    student_num = 0;
    cout << "A New Yard has been created!" << endl;
}

// Destructor
Yard::~Yard() {
    cout << "A Yard to be destroyed!" << endl;
    delete[] students;
}

// Βάζει τον μαθητή/όρισμα στην αυλή
void Yard::enter(Student& student) {
    cout << student.get_name() << " enters schoolyard!" << endl;
    students[student_num] = &student;
    student_num++;
    student.set_position(at_yard);
}

// Αφαιρεί τον τελευταίο μαθητή από την αυλή και επιστρέφει δείκτη σε αυτόν
Student* Yard::exit() {
    if (student_num == 0) {
        return NULL;
    }
    cout << students[student_num - 1]->get_name() << " exits schoolyard!" << endl;
    student_num--;
    return students[student_num];
}

// Συνάρτηση εκτύπωσης της Yard
void Yard::print() const {
    cout << "People in schoolyard are: " << endl;
    for (int i = 0 ; i < student_num ; i++) {
        students[i]->print();
    }
}

// Συναρτήσεις της Stairs

// Constructor
Stairs::Stairs(int init_capacity) : capacity(init_capacity) {
    students = new Student*[init_capacity];
    student_num = 0;
    cout << "New Stairs have been created!" << endl;
}

// Destructor
Stairs::~Stairs() {
    cout << "Stairs to be destroyed!" << endl;
    delete[] students;
}

// Βάζει τον μαθητή/όρισμα στο κλιμακοστάσιο
void Stairs::enter(Student& student) {
    cout << student.get_name() << " enters stairs!" << endl;
    students[student_num] = &student;
    student_num++;
    student.set_position(at_stairs);
}

// Αφαιρεί τον τελευταίο μαθητή του οποίου η τάξη βρίσκεται στον
// όροφο/όρισμα από το κλιμακοστάσιο και επιστρέφει δείκτη σε αυτό
Student* Stairs::exit(short floor_num) {
    for (int i = student_num - 1 ; i >= 0 ; i--) {
        if (students[i]->get_floor_num() == floor_num) {
            Student* temp = students[i];
            students[i] = students[student_num - 1];
            students[student_num - 1] = temp;
            cout << students[student_num - 1]->get_name() << " exits stairs!" << endl;
            student_num--;
            return students[student_num];
        }
    }
    return NULL;
}

// Συνάρτηση εκτύπωσης της Stairs
void Stairs::print() const {
    cout << "People in stairs are: " << endl;
    for (int i = 0 ; i < student_num ; i++) {
        students[i]->print();
    }
}

// Συναρτήσεις της Corridor

// Constructor
Corridor::Corridor(int init_capacity) : capacity(init_capacity) {
    students = new Student*[init_capacity];
    student_num = 0;
    cout << "A New Corridor has been created!" << endl;
}

// Destructor
Corridor::~Corridor() {
    cout << "A Corridor to be destroyed!" << endl;
    delete[] students;
}

// Βάζει τον μαθητή/όρισμα στον διάδρομο
void Corridor::enter(Student& student) {
    cout << student.get_name() << " enters corridor!" << endl;
    students[student_num] = &student;
    student_num++;
    student.set_position(at_corridor);
}

// Αφαιρεί τον τελευταίο μαθητή από τον διάδρομο και επιστρέφει δείκτη σε αυτόν
Student* Corridor::exit() {
    if (student_num == 0) {
        return NULL;
    }
    cout << students[student_num - 1]->get_name() << " exits corridor!" << endl;
    student_num--;
    return students[student_num];
}

// Συνάρτηση εκτύπωσης της Corridor
void Corridor::print() const {
    cout << "People in corridor are: " << endl;
    for (int i = 0 ; i < student_num ; i++) {
        students[i]->print();
    }
}

// Συναρτήσεις της Classroom

// Constructor
Classroom::Classroom(int init_capacity) : capacity(init_capacity) {
    students = new Student*[init_capacity];
    student_num = 0;
    teacher = NULL;
    cout << "A New Classroom has been created!" << endl;
}

// Destructor
Classroom::~Classroom() {
    cout << "A Classroom to be destroyed!" << endl;
    delete[] students;
}

// Βάζει τον μαθητή/όρισμα στην τάξη
void Classroom::enter(Student& student) {
    cout << student.get_name() << " enters classroom!" << endl;
    students[student_num] = &student;
    student_num++;
    student.set_position(at_classroom);
}

// Τοποθετεί τον δάσκαλο/όρισμα στην τάξη
void Classroom::place(Teacher& teacher_in) {
    teacher = &teacher_in;
    teacher_in.set_in();
}

// Συνάρτηση εκτύπωσης της Classroom
void Classroom::print(short classroom_number) const {
    cout << "People in class " << classroom_number + 1 << " are: " << endl;
    for (int i = 0 ; i < student_num ; i++) {
        students[i]->print();
    }
    if (teacher != NULL) {
        teacher->print();
    }
}

// Συναρτήσεις της Floor

// Constructor
Floor::Floor(int cclass, int ccorr) : corridor(ccorr) {
    for (char i = 0 ; i < 6 ; i++) {
        classrooms[i] = new Classroom(cclass);
    }
    cout << "A New Floor has been created!" << endl;
}

// Destructor
Floor::~Floor() {
    cout << "A Floor to be destroyed!" << endl;
    for (char i = 0 ; i < 6 ; i++) {
        delete classrooms[i];
    }
}

// Βάζει τον μαθητή/όρισμα στον όροφο, βάζοντάς τον στον διάδρομο αν χωράει
void Floor::enter(Student& student) {
    cout << student.get_name() << " enters floor!" << endl;
    corridor.enter(student);
    if (classrooms[student.get_classroom_num()]->full() == false) {
        corridor.exit();
        classrooms[student.get_classroom_num()]->enter(student);
    }
}

// Συνάρτηση εκτύπωσης της Floor
void Floor::print(short floor_number) const {
    cout << "Floor number " << floor_number + 1 << " contains: " << endl;
    corridor.print();
    for (char i = 0 ; i < 6 ; i++) {
        classrooms[i]->print(i);
    }
}

// Συναρτήσεις της School

// Constructor
School::School(int cclass, int cyard, int cstair, int ccorr)
:   yard(cyard), stairs(cstair)
{
    for (char i = 0 ; i < 3 ; i++) {
        floors[i] = new Floor(cclass, ccorr);
    }
    cout << "A New School has been created!" << endl;
}

// Destructor
School::~School() {
    cout << "A School to be destroyed!" << endl;
    for (char i = 0 ; i < 3 ; i++) {
        delete floors[i];
    }
}

// Βάζει τον μαθητή/όρισμα στο σχολείο, πηγαίνοντάς τον όσο πιο κοντά γίνεται
// στην τάξη του. Επιστρέφει το αν μπόρεσε να μπει τουλάχιστον στην αυλή ή όχι.
bool School::enter(Student& student) {
    cout << student.get_name() << " enters school!" << endl;
    if (yard.full()) {
        return false;
    }
    yard.enter(student);
    if (stairs.full()) {
        return true;
    }
    yard.exit();
    stairs.enter(student);
    if (floors[student.get_floor_num()]->can_fit()) {
        stairs.exit(student.get_floor_num());
        floors[student.get_floor_num()]->enter(student);
    }
    return true;
}

// Βάζει τους μαθητές/όρισμα στο σχολείο, μετακινόντας τους σε "κύματα",
// πηγαίνοντάς τους τελικά όσο κοντά γίνεται στις τάξεις τους. Επιστρέφει
// το αν μπόρεσαν όλοι οι μαθητές να μπουν τουλάχιστον στην αυλή ή όχι.
bool School::enter(Student** students, int size) {
    for (int i = 0 ; i < size ; i++) {
        cout << students[i]->get_name() << " enters school!" << endl;
    }
    int ammount_in = 0;
    while (true) {  // γίνεται διαρκώς η εξής διαδικασία
        Student* to_enter;
        bool stagnated = true;
        // μπαίνουν στην αυλή όσοι χωράνε
        for ( ; (yard.full() == false) && (ammount_in != size) ; ammount_in++) {
            yard.enter(*students[ammount_in]);
        }
        // μετά μπαίνουν όσοι χωράνε στο κλιμακοστάσιο
        while (stairs.full() == false) {
            to_enter = yard.exit();
            if (to_enter == NULL) {
                break;
            }
            stairs.enter(*to_enter);
            stagnated = false;
        }
        // μετά όσοι χωράνε στους ορόφους
        for (int i = 0 ; i < 3 ; i++) {
            while (floors[i]->can_fit()) {
                to_enter = stairs.exit(i);
                if (to_enter == NULL) {
                    break;
                }
                floors[i]->enter(*to_enter);
                stagnated = false;
            }
        }
        // μέχρι να μην κινείται κανείς
        if (stagnated) {
            return ammount_in == size;
        }
    }
}

// Συνάρτηση εκτύπωσης της School
void School::print() const {
    cout << "School life consists of: " << endl;
    yard.print();
    stairs.print();
    for (char i = 0 ; i < 3 ; i++) {
        floors[i]->print(i);
    }
}

/* File: main.cpp */

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "names.h"

//using namespace std;



// Συνάρτηση τυχαίας αναδιάταξης μονοδιάστατου πίνακα δεικτών σε Student
void shuffle(Student* array[], int size) {
	for (int i = 0; i < size; i++) {
		int new_pos = i + rand() / (RAND_MAX / (size - i) + 1);
		Student* temp = array[new_pos];
		array[new_pos] = array[i];
		array[i] = temp;
	}
}

int main(int argc, char* argv[]) {
    // αρχικοποίηση με ορίσματα από γραμμή εντολής
    if (argc != 5) {
        cerr << "Wrong number of arguments" << endl;
        return 1;
    }
    int cclass = atoi(argv[1]), cyard = atoi(argv[2]), cstair = atoi(argv[3]), ccorr = atoi(argv[4]);
    if (cclass < 1 || cyard < 1 || cstair < 1 || ccorr < 1) {
        cerr << "The capacities must be positive" << endl;
        return 2;
    }

    // αρχικοποίηση της rand()
    srand(time(NULL));

    // δημιουργία μαθητών, με τυχαία ονόματα
    const int student_num = cclass*18;
    Student* students[student_num];
    for (int i = 0 ; i < 3 ; i++) {
        for (int j = 0 ; j < 6 ; j++) {
            for (int k = 0 ; k < cclass ; k++) {
                students[cclass*6*i + cclass*j + k] = new Student(names[rand() % 48], i, j);
            }
        }
    }

    // δημιουργία δασκάλων, με τυχαία ονόματα
    Teacher* teachers[18];
    for (int i = 0 ; i < 18 ; i++) {
        teachers[i] = new Teacher(names[rand() % 48], i / 6, i % 6);
    }

    // δημιουργία σχολείου
    School school(cclass, cyard, cstair, ccorr);

    // "ανακάτεμα" μαθητών
    shuffle(students, student_num);

    // είσοδος στο σχολείο
    for (int i = 0 ; i < student_num ; i++) {   // όλοι τους μαθητές
        if ((rand() % 2) || (i + student_num/9 > student_num)) {    // μπαίνουν τυχαία
            if (!school.enter(*students[i])) {  // ένας - ένας
                break;  // μέχρι να γεμίσει το σχολείο
            }
        }
        else {
            if (!school.enter(students + i, student_num/9)) {   // ή πολλοί μαζί
                break;  // μέχρι να γεμίσει το σχολείο
            }
            i += student_num/9 - 1;
        }
        if (!(rand() % (student_num/8))) {  // κάποιες φορές
            int teacher_num = rand() % 4;   // ένας τυχαίος αριθμός δασκάλων
            for (int j = 0 ; j < teacher_num ; j++) {
                Teacher* to_be_placed = teachers[rand() % 18];
                if (to_be_placed->is_in() == false) {
                    school.place(*to_be_placed);    // τοποθετείται στο σχολείο
                }
            }
        }
    }

    // εκτύπωση του σχολείου
    school.print();

    // απελευθέρωση μνήμης μαθητών
    for (int i = 0 ; i < student_num ; i++) {
        delete students[i];
    }

    // απελευθέρωση μνήμης δασκάλων
    for (int i = 0 ; i < 18 ; i++) {
        delete teachers[i];
    }

    return 0;
}