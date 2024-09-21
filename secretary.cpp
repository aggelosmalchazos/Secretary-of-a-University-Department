#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>

using namespace std;

// Άγγελος Νικόλαος Μαλχάζος (sdi2200091)

#include <iostream>
#include <string>
#include <vector>
using namespace std;
int pcount = 0; // person count

class Person
{
    // academic id, age,gender, name

public:
    string Fname;
    string Lname;
    string Prop;
    long int tel;

    // constructor with id
    Person(string fname, string lname, string prop, long int teln) : Fname(fname), Lname(lname), Prop(prop), tel(teln)
    {
        pcount++;
    }
    // constructor without id
    Person(string fname, string lname) : Fname(fname), Lname(lname), tel(0), Prop(0)
    {
        pcount++;
    }
    long int getTel()
    {
        return tel;
    }
    ~Person()
    {
        //  cout << "Deconstructor has been called" << endl;
    }

    // overloading the << operator
    friend std::ostream &operator<<(std::ostream &out, const Person &person)
    {
        out << "Name: " << person.Fname << " " << person.Lname << endl;
        out << "Phone Number: " << person.tel << endl;
        if (person.Prop == "P")
        {
            out << "Property : Professor" << endl;
        }
        else
        {
            out << "Property : Student" << endl;
        }
        return out;
    }

    // overloading the >> operator
    friend std::istream &operator>>(std::istream &input, Person &obj)
    {
        input >> obj.Fname >> obj.Lname >> obj.Prop >> obj.tel;
        return input;
    }
};

class Student;

// το struct studentCourseData κρατάει τα στοιχεία που θα μπουν στο academic transcript του κάθε μαθητή
struct studentCourseData
{
    string courseName;
    float studentScore;
    int ects;
    int semester;
    bool mandatory;
};

// το struct courseData αποθηκεύει έναν pointer σε student, και τη βαθμολογία του σε float
struct courseData
{
    Student *student;
    float score;
};

class Course
{
private:
    string name;
    int semester;
    int ects;
    bool mandatory;
    string professor;
    vector<courseData> enrolled;

public:
    Course(string name1, int semester1, int ects1, bool mandatory1, string professor1) : name(name1), semester(semester1), ects(ects1), mandatory(mandatory1), professor(professor1){};

    ~Course();

    // student enrolls in the course
    void enroll(Student *student)
    {
        courseData data;
        data.student = student;
        enrolled.push_back(data);
    }

    // overload << operator
    friend ostream &operator<<(ostream &out, const Course &course)
    {
        out << "Name: " << course.name << endl;
        out << "Professor: " << course.professor << endl;
        out << "ECTS: " << course.ects << endl;
        out << "Is mandatory: " << (course.mandatory ? "Yes" : "No") << endl;
        return out;
    }

    void addProfessorToCourse(string newProfessorName)
    {
        professor = newProfessorName;
    }
    // ζητούμενο Β6
    void printSuccessfullScores();

    void changeSemester(int newSemester)
    {
        this->semester = newSemester;
    }

    int getEcts()
    {
        return ects;
    }
    int getSemester()
    {
        return semester;
    }
    bool isMandatory()
    {
        return mandatory;
    }
    string getProfessor()
    {
        return professor;
    }
    string getName()
    {
        return name;
    }
    const vector<courseData> getEnrolledconst()
    {
        return enrolled;
    }
    vector<courseData> &getEnrolled()
    {
        return enrolled;
    }

    void printEnrolled();
};

class Secretary;

class Student : public Person
{
private:
    int semester;
    vector<studentCourseData> acTranscript;
    int ects;

public:
    // function to enroll in a course
    void enroll(Course *course);

    Student(string fname, string lname, string prop, long int teln, int Semester, int Ects) : Person(fname, lname, prop, teln), semester(Semester), ects(Ects)
    {
    }

    void display()
    {
        cout << "Student: " << Fname << " " << Lname << endl
             << "Telephone: " << tel << endl
             << "Semester: " << semester << endl
             << "ECTS: " << ects << endl;
        cout << endl;
    }

    int getSemester()
    {
        return semester;
    }
    void updateSemester()
    {
        semester++;
    }
    void updateEcts(int num)
    {
        ects += num;
    }

    int getEcts()
    {
        int sum = 0;
        for (studentCourseData data : acTranscript)
        {
            if (data.studentScore >= 5)
            {
                sum += data.ects;
            }
        }
        return ects;
    }
    // ελέγχει αν έχουν περαστεί τα υποχρεωτικά μαθήματα που έχει κάνει εγγραφή ο φοιτητής
    bool hasPassedMandatory()
    {
        for (studentCourseData data : acTranscript)
        {
            if (data.studentScore < 5 && data.mandatory)
            {
                return false;
            }
        }
        return true;
    }
    void printAllscores()
    {
        for (const auto &obj : acTranscript)
        {
            cout << endl
                 << "Name of course: " << obj.courseName << endl;
            cout << "Student score: " << obj.studentScore << endl;
            cout << "ECTS: " << obj.ects << endl;
            cout << "Is mandatory: " << (obj.mandatory ? "Yes" : "No") << endl;
            cout << endl;
        }
    }
    vector<studentCourseData> &getCourseData()
    {
        return acTranscript;
    }
    string getFname()
    {
        return Fname;
    }
    string getLname()
    {
        return Lname;
    }
    void changeFname()
    {
        string newFname;
        cout << "Enter new name: ";
        cin >> newFname;
        cout << endl;
        Fname = newFname;
    }
    void changeLname()
    {
        string newLname;
        cout << "Enter new name: ";
        cin >> newLname;
        cout << endl;
        Lname = newLname;
    }
};
void Course::printSuccessfullScores()
{

    ofstream outFile("scores.txt");
    outFile << "Professor " << professor << endl;
    for (courseData obj : enrolled)
    {
        if (obj.student)
        {
            if (obj.score >= 5)
            {

                outFile << "Name: " << obj.student->Fname << " " << obj.student->Lname << endl;
                outFile << "Score: " << obj.score << endl;
            }
        }
        else
        {
            cout << "ERROR: Null pointer in courseData." << endl;
        }
    }
    outFile.close();
}
void Student::enroll(Course *course)
{
    int x = course->getSemester();
    if (course && course->getSemester() <= semester)
    {
        course->enroll(this);
        studentCourseData data;
        data.courseName = course->getName();
        data.studentScore = 0;
        data.ects = course->getEcts();
        data.mandatory = course->isMandatory();
        acTranscript.push_back(data);
    }
    else
    {
        cout << "Cannot enroll, this course is for later semesters" << endl;
    }
}
Course::~Course()
{

    for (courseData &course : enrolled)
    {
        delete course.student;
    }
    enrolled.clear();
};
void Course::printEnrolled()
{
    cout << endl
         << endl;
    // cout << "Name of course: " << this->getName() << endl;
    cout << "Professor name: " << this->getProfessor() << endl;
    cout << "Enrolled in the course " << this->getName() << " :" << endl;
    for (courseData data : enrolled)
    {
        cout << "Name: " << data.student->Fname << " " << data.student->getLname() << endl;
    }
    cout << endl
         << endl;
}
class Professor : public Person
{
private:
    // αποθηκεύω ποια μαθήματα κάνει ο καθηγητής
    vector<Course *> courses;
    Secretary *secretary;

public:
    Professor(string fname, string lname, string prop, long int teln, Secretary *secretary) : Person(fname, lname, prop, teln), secretary(secretary)
    {
    }

    void addCourseToProfessor(Course *course)
    {
        courses.push_back(course);
    }

    void display()
    {
        cout << "Professor: " << Fname << " " << Lname << endl
             << "Telephone: " << tel << endl;
        cout << endl;
    }

    Course *findCourse(string name)
    {

        auto it = courses.begin();
        while (it != courses.end())
        {

            Course *course = *it;

            if (course->getName() == name)
            {
                return course;
            }
            else
            {
                ++it;
            }
        }
        return nullptr;
    }
    // ζητούμενο Β7
    void printAllScores();
};

class Secretary
{
    string uni;
    string dept; // which department of the uni
    int ects;
    int years;
    // ed;v
    vector<Person *> people;
    vector<Course *> courses;

public:
    Secretary(string uni1, string dept1, int ects1, int years1) : uni(uni1), dept(dept1), ects(ects1), years(years1)
    {
        cout << "Secretary constructed" << endl;
    }
    void message()
    {
        cout << "Enter information following the format: " << endl;
        cout << "FirstName LastName Property(S or P) PhoneNumber" << endl;
    }

    ~Secretary()
    {
        for (const Person *person : people)
        {
            delete person;
        }
        for (const Course *course : courses)
        {
            delete course;
        }
        people.clear();
        courses.clear();
        // cout << "Deconstructor has been called" << endl;
    }

    void operator+(Person *person)
    {
        people.push_back(person);
    }

    void addStudent(string fname, string lname, string prop, long int tel, int semester, int ects, Secretary &secretary)
    {
        Student *newPerson = new Student(fname, lname, prop, tel, semester, ects);
        secretary + newPerson; // using the overloaded + operator
    }

    void addProfessor(string fname, string lname, string prop, long int tel, Secretary &secretary)
    {
        Professor *newPerson = new Professor(fname, lname, prop, tel, &secretary);
        secretary + newPerson;
    }

    // όταν προσθέτει η γραμματεία μάθημα, τότε δεν έχει ακόμα κανέναν εγγεγραμένο φοιτητή
    void addCourse(string name, int semester, int ects, bool mandatory, string professor)
    {
        Course *course = new Course(name, semester, ects, mandatory, professor);
        courses.push_back(course);
        course->addProfessorToCourse(professor);
    }

    void addCourse(Course *course)
    {
        courses.push_back(course);
    }

    Student *findStudent(string fname, string lname)
    {
        auto it = people.begin();
        while (it != people.end())
        {

            Person *person = *it;

            if (person->Lname == lname && person->Prop == "S")
            {
                Student *nonConstStudent = const_cast<Student *>(static_cast<const Student *>(person)); //*it works**
                return nonConstStudent;
            }
            else
            {
                ++it;
            }
        }
        return nullptr;
    }
    Course *findCourse(string name)
    {
        auto it = courses.begin();
        while (it != courses.end())
        {

            Course *course = *it;

            if (course->getName() == name)
            {
                return course;
            }
            else
            {
                ++it;
            }
        }
        return nullptr;
    }
    Professor *findProfessor(string lname)
    {
        auto it = people.begin();

        while (it != people.end())
        {

            Person *person = *it;

            if (person->Lname == lname && person->Prop == "P")
            {
                Professor *nonConstProfessor = const_cast<Professor *>(static_cast<const Professor *>(person)); //*it works**
                return nonConstProfessor;
            }
            else
            {
                ++it;
            }
        }
        return nullptr;
    }
    // ζητούμενο Β6
    void printSuccessfullScoresSecr(string name)
    {
        for (Course *course : courses)
        {
            if (course->getName() == name)
            {
                course->printSuccessfullScores();
            }
        }
    }
    friend std::ostream &operator<<(std::ostream &out, const Secretary &secretary)
    {
        out << "Department members:" << endl;
        for (const Person *person : secretary.people)
        {
            if (person->Prop == "S")
            {
                Student *nonConstStudent = const_cast<Student *>(static_cast<const Student *>(person)); //*it works**
                nonConstStudent->display();
            }
            else
            {
                Professor *nonConstProfessor = const_cast<Professor *>(static_cast<const Professor *>(person)); //*it works**
                nonConstProfessor->display();
            }
        }

        out << "Courses:" << endl;
        for (const Course *course : secretary.courses)
        {
            out << *course << endl;
        }
        return out;
    }

    friend std::istream &operator>>(std::istream &input, Secretary &secretary)
    {

        string fname, lname, prop;
        long int tel;
        int semester, ects;
        // Read data directly into variables
        input >> fname >> lname >> prop >> tel;
        Person *newPerson;
        if (prop == "S")
        {
            input >> semester >> ects;
            // Student *newPerson = new Student(fname, lname, prop, tel, semester, ects);
            // secretary + newPerson; // using the overloaded + operator
            secretary.addStudent(fname, lname, prop, tel, semester, ects, secretary);
        }
        else if (prop == "P")
        {
            secretary.addProfessor(fname, lname, prop, tel, secretary);
        }
        else
        {
            Person *newPerson = new Person(fname, lname, prop, 0);
            secretary + newPerson; // using the overloaded + operator
        }

        return input;
    }

    // searching by telephone number
    void findPerson(long int key)
    {
        int f = 0;

        for (const Person *i : people)
        {
            // cout << i->id<< endl;
            if (i->tel == key)
            {
                cout << "FOUND BY PHONE" << endl;
                f++;
            }
        }
        if (f == 0)
        {
            cout << "NOT FOUND BY PHONE" << endl;
        }
    }

    // searching by name
    void findPerson(string Fname, string Lname)
    {
        int f = 0;

        for (const Person *i : people)
        {
            if (i->Fname == Fname && i->Lname == Lname)
            {
                cout << "FOUND BY NAME" << endl;
                f++;
            }
        }
        if (f == 0)
        {
            cout << "NOT FOUND BY NAME" << endl;
        }
    }

    // searching for person
    void findPerson(Person &key)
    {
        int f = 0;
        for (const Person *i : people)
        {
            // cout << i->id<< endl;
            if (i->Fname == key.Fname && i->Lname == key.Lname && i->Prop == key.Prop && i->tel == key.tel)
            {
                cout << "FOUND BY PERSON" << endl;
                f++;
            }
        }
        if (f == 0)
        {
            cout << "NOT FOUND BY PERSON" << endl;
        }
    }

    void deleteProfessor(string Fname, string Lname)
    {
        auto it = people.begin();

        while (it != people.end())
        {
            Person *person = *it;

            if (person->Prop == "P" && person->Fname == Fname && person->Lname == Lname)
            {

                delete person;
                it = people.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
    void deleteStudent(string Fname, string Lname)
    {
        auto it = people.begin();

        while (it != people.end())
        {
            Person *person = *it;

            if (person->Prop == "S" && person->Fname == Fname && person->Lname == Lname)
            {

                delete person;
                it = people.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
    string getUni()
    {
        return uni;
    }
    string getDept()
    {
        return dept;
    }

    vector<Course *> getCourses()
    {
        return courses;
    }
    // copy constructor with overloaded = operator, it creates new object with same data because otherwise the pointers would be the same for two or more people
    Secretary &
    operator=(Secretary &newSecr)
    {
        // uni = newSecr.uni;
        // dept = newSecr.dept;
        for (const Person *person : newSecr.people)
        {
            if (person->tel != 0)
            {
                people.push_back(new Person(person->Fname, person->Lname, person->Prop, person->tel));
            }
            else
            {
                people.push_back(new Person(person->Fname, person->Lname));
            }
        }
        return *this;
    }

    void displayMenu()
    {
        int num;
        do
        {
            cout << "Choose one of the following options" << endl;
            cout << "0.Exit menu and terminate program" << endl;
            cout << "1.Add a professor or a student" << endl;
            cout << "2.Delete a professor or a student" << endl;
            cout << "3.Add or delete a course" << endl;
            cout << "4.Assign a professor to a course" << endl;
            cout << "5.Enroll a student to a course" << endl;
            cout << "6.Print and save the students that passed a specific course" << endl;
            cout << "7.Print your students' scores in your courses" << endl;
            cout << "8.Print your scores for this semester and for all semesters" << endl;
            cout << "9.Print all graduates" << endl;
            cout << "10.Display and save secretary contents" << endl;
            cout << "11.Print enrolled students of a specific course" << endl;
            cout << "12.Print academic transcript of a specific student" << endl;
            cout << "13.Start semester" << endl;
            cout << "14.End semester" << endl;
            cout << "Input the number:" << endl;
            cin >> num;
            actionMenu(num);
        } while (num != 0);
    }
    void actionMenu(int num)
    {
        // if (num == 0)
        // {
        //     cout << "TESTTESTTESTTEST" << endl;
        //     ofstream outFile("people.txt");
        //     // Fname Lname S TELEPHONE SEMESTER ECTS
        //     for (Person *person : people)
        //     {
        //         if (person->Prop == "S")
        //         {
        //             Student *student = const_cast<Student *>(static_cast<const Student *>(person)); //*it works**
        //             cout << student->getFname() << " " << student->getLname() << " " << student->getTel() << " " << student->getSemester() << " " << student->getEcts() << endl;
        //         }
        //         else if (person->Prop == "P") // PROFESSOR FORMAT // FNAME LNAME P TELEPHONE
        //         {
        //             Professor *professor = const_cast<Professor *>(static_cast<const Professor *>(person)); //*it works**
        //             cout << professor->Fname << " " << professor->Lname << " "
        //                  << "P"
        //                  << " " << professor->getTel() << endl;
        //         }
        //     }
        //     outFile.close();
        // }
        if (num == 1)
        {
            cout << "Input 0 if you want to add a professor and 1 if you want to add a student: ";

            int x;
            cin >> x;
            // cout << "VALUE OF X IS " << x << endl;
            string fname;
            string lname;
            long int tel;
            cout << "Enter first name: ";
            cin >> fname;
            cout << endl;
            cout << "Enter last name: ";
            cin >> lname;
            cout << endl;
            cout << "Enter telephone number: ";
            cin >> tel;
            cout << endl;
            if (x == 0)
            {

                this->addProfessor(fname, lname, "P", tel, *this);
            }
            else
            {
                int semester;
                cout << "Enter semester:";
                cin >> semester;
                cout << endl;
                int ects;
                cout << "Enter ECTS:";
                cin >> ects;
                cout << endl;
                this->addStudent(fname, lname, "S", tel, semester, ects, *this);
            }
        }
        else if (num == 2)
        {
            cout << "Input 0 if you want to delete a professor and 1 if you want to delete a student: ";
            int x;
            cin >> x;
            string fname;
            string lname;
            cout << "Enter first name: ";
            cin >> fname;
            cout << endl;
            cout << "Enter last name: ";
            cin >> lname;
            cout << endl;
            auto it = people.begin();

            while (it != people.end())
            {
                Person *person = *it;

                if (((person->Prop == "P" && x == 0) || (person->Prop == "S" && x == 1)) && person->Fname == fname && person->Lname == lname)
                {

                    delete person;
                    it = people.erase(it);
                }
                else
                {
                    ++it;
                }
            }
        }
        else if (num == 3)
        {
            cout << "Enter 0 if you want to add a course or 1 if you want to delete one: ";
            int x;
            cin >> x;
            cout << "Enter name of course:";
            string name;
            cin >> name;
            if (x == 1)
            {
                auto it = courses.begin();

                while (it != courses.end())
                {
                    Course *course = *it;

                    if (course->getName() == name)
                    {

                        delete course;
                        it = courses.erase(it);
                    }
                    else
                    {
                        ++it;
                    }
                }
            }
            else
            {
                int semester;
                int ects;
                bool mandatory;
                string professor;
                cout << "Enter semester:";
                cin >> semester;
                cout << endl;
                cout << "Enter ECTS:";
                cin >> ects;
                cout << endl;
                cout << "Is it mandatory? true/false :";
                string mandatoryStr;
                cin >> mandatoryStr;
                cout << endl
                     << "Enter last name of professor: ";
                cin >> professor;
                mandatory = (mandatoryStr == "true");
                cout << endl;
                cout << "Enter name of professor:";
                cout << endl;
                this->addCourse(name, semester, ects, mandatory, professor);
            }
        }
        else if (num == 4)
        {
            cout << "Enter last name of professor you want to add to a course: ";
            string lname;
            cin >> lname;
            cout << endl;

            cout << "Enter name of course:";
            string name;
            cin >> name;
            Course *coursef = findCourse(name);

            coursef->addProfessorToCourse(lname);
        }
        else if (num == 5)
        {

            string fname;
            string lname;
            cout << "Enter first name: ";
            cin >> fname;
            cout << endl;
            cout << "Enter last name: ";
            cin >> lname;
            cout << endl;

            cout << "Enter name of course: ";
            string name;
            cin >> name;
            Course *coursef = findCourse(name);
            Student *student = findStudent(fname, lname);
            if (student)
                student->display();
            student->enroll(coursef);
        }
        else if (num == 6)
        {
            cout << "Enter name of course:";
            string name;
            cin >> name;
            Course *coursef = findCourse(name);
            coursef->printSuccessfullScores();
        }
        else if (num == 7)
        {
            string fname;
            string lname;
            cout << "Enter first name: ";
            cin >> fname;
            cout << endl;
            cout << "Enter last name: ";
            cin >> lname;
            cout << endl;
            Professor *professor = findProfessor(lname);
            cout << "FOUND PROFESSOR" << endl;
            professor->display();
            cout << endl
                 << endl;
            professor->printAllScores();
        }
        else if (num == 8)
        {
            string fname;
            string lname;
            cout << "Enter first name: ";
            cin >> fname;
            cout << endl;
            cout << "Enter last name: ";
            cin >> lname;
            cout << endl;
            Student *student = findStudent(fname, lname);
            student->printAllscores();
        }
        else if (num == 9)
        {
            this->getGraduates();
        }
        else if (num == 10)
        {
            cout << *this;
        }
        else if (num == 11)
        {
            cout << "Enter name of course:";
            string name;
            cin >> name;
            Course *coursef = findCourse(name);
            coursef->printEnrolled();
        }
        else if (num == 12)
        {
            cout << "Enter first name: ";
            string fname;
            cin >> fname;
            cout << "Enter last name: ";
            string lname;
            cin >> lname;
            cout << endl;
            Student *student = findStudent(fname, lname);
            student->printAllscores();
        }
        else if (num == 13)
        {
            startSemester();
        }
        else if (num == 14)
        {
            endSemester();
        }
    }
    // η συνάρτηση που ενημερώνει ουσιαστικά τα αρχεία με τους φοιτητές, καθηγητές, και μαθήματα. Διαγράφει το περιέχομενο των αρχείων, οπότε υπάρχει αντίγραφο αυτών των αντίγραφων στον υποφάκελο
    void outputToFiles()
    {
        ofstream outFile("people.txt");
        // Fname Lname S TELEPHONE SEMESTER ECTS
        for (Person *person : people)
        {
            if (person->Prop == "S")
            {
                Student *student = const_cast<Student *>(static_cast<const Student *>(person)); //*it works**
                outFile << student->getFname() << " " << student->getLname() << " "
                        << "S"
                        << " " << student->getTel() << " " << student->getSemester() << " " << student->getEcts() << endl;
            }
            else if (person->Prop == "P") // PROFESSOR FORMAT // FNAME LNAME P TELEPHONE
            {
                Professor *professor = const_cast<Professor *>(static_cast<const Professor *>(person)); //*it works**
                outFile << professor->Fname << " " << professor->Lname << " "
                        << "P"
                        << " " << professor->getTel() << endl;
            }
        }
        outFile << "END OF INPUT" << endl;
        outFile.close();

        ofstream outcourses("courses.txt");
        // format for courses: Name Semester ECTS ismandatory Professor
        for (Course *course : courses)
        {
            outcourses << course->getName() << " " << course->getSemester() << " " << course->getEcts() << " " << (course->isMandatory()?"true":"false") << " " << course->getProfessor() << endl;
        }
        outcourses << "END OF INPUT" << endl;
        outcourses.close();
    }

    void startSemester()
    {
        string answer;
        for (Person *person : people)
        {
            if (person->Prop == "S")
            {
                do
                {
                    Student *nonConstStudent = const_cast<Student *>(static_cast<const Student *>(person)); //*it works**
                    nonConstStudent->display();
                    cout << "In which courses will he/she enroll? Enter name: ";
                    string name;
                    cin >> name;
                    cout << endl;
                    Course *course = findCourse(name);
                    // cout << "MIDDLE" << endl;
                    // cout << course->getName() << endl;
                    nonConstStudent->enroll(course);
                    cout << endl;

                    cout << "Will the student be enrolled in more courses? yes/no ";
                    cin >> answer;
                    cout << endl;
                } while (answer == "yes");
            }
        }
    }

    // όταν τελειώνει το εξάμηνο, οι καθηγητές βάζουν βαθμούς στους φοιτητές που είναι enrolled στα μαθήματά τους,
    //  ενημερώνονται τα academic transcripts των φοιτητών, ενημερώνονται και τα ects τους και το εξάμηνο στο οποίο βρίσκονται
    void endSemester()
    {
        for (Person *person : people)
        {
            if (person->Prop == "P")
            {
                Professor *professor = const_cast<Professor *>(static_cast<const Professor *>(person)); //*it works**

                for (Course *course : courses)
                {
                    if (course->getProfessor() == professor->Lname)
                    {
                        //    cout << "Professor " << professor->Fname << " " << professor->Lname << " , enter your grades: " << endl;

                        vector<courseData> &enrolledData = course->getEnrolled();
                        if (enrolledData.empty())
                        {
                            continue;
                        }
                        cout << endl
                             << "Course : " << course->getName() << endl;
                        for (courseData &obj : enrolledData)
                        {
                            cout << "Name: " << obj.student->Fname << " " << obj.student->Lname << endl;
                            cout << "Grade :";
                            int x;
                            cin >> x;
                            obj.score = x;
                            // cout << "GRADE IS " << obj.score << endl;
                            cout << endl;
                            vector<studentCourseData> &transcript = obj.student->getCourseData();
                            for (studentCourseData &trans : transcript)
                            {
                                if (trans.courseName == course->getName())
                                {
                                    trans.studentScore = x;
                                }
                                if (trans.studentScore >= 5)
                                {
                                    trans.ects += course->getEcts();
                                    obj.student->updateEcts(course->getEcts());
                                    obj.student->updateSemester();
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    void getGraduates()
    {
        cout << "GRADUATES: " << endl;
        for (Person *person : people)
        {
            if (person->Prop == "S")
            {
                Student *graduate = const_cast<Student *>(static_cast<const Student *>(person)); //*it works**
                if (graduate->getSemester() > 8 && graduate->getEcts() >= 240 && graduate->hasPassedMandatory())
                {
                    cout << graduate->Fname << " " << graduate->Lname << endl;
                }
            }
        }
    }
};

void Professor::printAllScores()
{
    vector<Course *> courses = secretary->getCourses();
    for (Course *course : courses)
    {
        if (course->getProfessor() == this->Lname)
        {
            vector<courseData> scores = course->getEnrolled();
            if (scores.empty())
            {
                continue;
            }
            cout << "COURSE: " << course->getName() << endl;
            for (courseData &student : scores)
            {
                cout << "Name: " << student.student->Fname << " " << student.student->Lname << endl;
                cout << "Score: " << student.score << endl;
            }
        }
    }
}
int main()
{
    Secretary Secr("UOA", "DIT", 240, 4);

    try
    {
        ifstream peopleFile("people.txt");

        // Check if the file is open
        if (!peopleFile.is_open())
        {
            // Throw an exception if the file couldn't be opened
            throw runtime_error("Error opening the file!");
        }

        // Loop through each line in the file
        string line;
        while (getline(peopleFile, line))
        {
            istringstream iss(line);
            if (line.find("END OF INPUT") != string::npos)
            {
                // cout << "FOUND END OF INPUT" << endl;
                break; // Exit the loop if "COURSES" is found
            }
            iss >> Secr;
        }
    }
    catch (const exception &sfalma)
    {
        // Handle the exception (e.g., print an error message)
        cerr << "Exception: " << sfalma.what() << endl;
        return 1; // Exit with an error code
    }

    // τώρα θα διαβάσουμε τα courses
    //  //  Open the file
    ifstream coursesFile("courses.txt");

    // Check if the file is opened successfully
    if (!coursesFile.is_open())
    {
        cerr << "Error opening the file!" << endl;
        return 1; // Exit with an error code
    }

    string name;
    int semester;
    int ects;
    bool mandatory;
    string professor;
    while (coursesFile >> name >> semester >> ects >> boolalpha >> mandatory >> professor)
    {

        Secr.addCourse(name, semester, ects, mandatory, professor);
    }
    coursesFile.close();

    Secr.displayMenu();
    cout << endl;

    Secr.outputToFiles();

    return 0;
}
