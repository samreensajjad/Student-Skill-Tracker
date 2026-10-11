#include<iostream>
#include<string>
#include<fstream>
using namespace std;
//Stores information about a single skill
class Skill
{
private:
    string name;
    double level;
public:
    Skill()
    {
        name="";
        level=0;
    }

    Skill(string n, double l)
    {
        name=n;
        level=l;
    }
//Displays skill name and level
    void display()
    {
        cout<<"Skills:"<<name<<endl;
        cout<<"Level:"<<level<<"/10"<<endl;
    }
    string getName()
{
    return name;
}
void setLevel(double newLevel)
{
    level = newLevel;
}
double getLevel()
{
    return level;
}
};
//Manages all student skills
class SkillTracker
{
private:
    Skill skills[50]; 
    int skillCount;
public:

    SkillTracker()
    {
        skillCount = 0;
        loadSkills();
    }
//Adds a new skill with validation
    void addSkill()
{
    if (skillCount >= 50)
    {
        cout << "Skill list is full!" << endl;
        return;
    }
	string name;
    double level;
    cout<<"Enter skills name:";
    cin.ignore();
    getline(cin, name);
    if (name=="")
    {
        cout<<"Skill name cannot be empty."<<endl;
        return;
    }
    for (int i = 0; i < skillCount; i++)
{
    if (name == skills[i].getName())
    {
        cout<<"This skill already exists!"<<endl;
        return;
    }
}
    cout<<"Enter skill level (1-10):";
    cin>>level;
    while (cin.fail() || level < 1 || level > 10)
{
    cin.clear();
    cin.ignore(1000, '\n');

    cout<<"Invalid level! Please enter a number from 1 to 10:";
    cin>>level;
}
    skills[skillCount]=Skill(name, level);
    skillCount++;
    cout<<"Skill added successfully!"<<endl;
}
//Displays all saved skills
void viewSkills()
{
    if(skillCount == 0)
    {
        cout<<"No skills added yet."<<endl;
        return;
    }
    cout<<"\nMY SKILLS\n";
    for (int i = 0; i < skillCount; i++)
    {
        cout << "\nSkill #" << i + 1 << endl;
        skills[i].display();
    }
}
// Searches for a skill by name
void searchSkill()
{
    string searchName;
    bool found = false;
    cout<<"Enter skill name to search:";
    cin.ignore();
    getline(cin, searchName);
    for (int i = 0; i < skillCount; i++)
    {
        if (searchName == skills[i].getName())
        {
            cout<<"\nSkill Found!"<<endl;
            skills[i].display();
            found = true;
            break;
        }
    }
    if (!found)
    {
        cout<<"Skill not found."<<endl;
    }
}
// Updates the level of an existing skill
void updateSkill()
{
    string searchName;
    double newLevel;
    bool found = false;
    cout<<"Enter skill name to update: ";
    cin.ignore();
    getline(cin, searchName);
    for (int i = 0; i < skillCount; i++)
    {
        if (searchName == skills[i].getName())
        {
            cout<<"Current skill information:"<<endl;
            skills[i].display();
            cout<<"Enter new level (1-10): ";
            cin>>newLevel;

        while (cin.fail() || newLevel < 1 || newLevel > 10)
{
            cin.clear();
            cin.ignore(1000, '\n');

            cout<<"Invalid level! Please enter a number from 1 to 10: ";
            cin>>newLevel;
}

            skills[i].setLevel(newLevel);
            cout<<"Skill updated successfully!"<<endl;
            found = true;
            break;
        }
        
    }
    if (!found)
    {
        cout << "Skill not found." << endl;
    }
}
// Deletes a skill from list
void deleteSkill()
{
    string deleteName;
    bool found = false;
    cout<<"Enter skill name to delete: ";
    cin.ignore();
    getline(cin, deleteName);
    for (int i = 0; i < skillCount; i++)
    {
        if (deleteName == skills[i].getName())
        {
            for (int j = i; j < skillCount - 1; j++)
            {
                skills[j] = skills[j + 1];
            }
            skillCount--;
            cout << "Skill deleted successfully!" << endl;
            found = true;
            break;
        }
    }
    if (!found)
    {
        cout<<"Skill not found."<<endl;
    }
}
// Calculates and Displays overall progress
void showProgress()
{
    if (skillCount == 0)
    {
        cout<<"No skills added yet."<<endl;
        return;
    }
    double total = 0;
    for(int i = 0; i < skillCount; i++)
    {
        total=total + skills[i].getLevel();
    }
    double average = (double) total / skillCount;
    double percentage = average * 10;
    cout<<"\n--------- OVERALL PROGRESS ---------"<<endl;
    cout<<"Total Skills: "<<skillCount<<endl;
    cout<<"Overall Level: "<<average<<"/10"<<endl;
    cout<<"Overall Progress: "<<percentage<<"%"<<endl;
}
// Saves skills to a file
void saveSkills()
{
    ofstream file("skills.txt");
    for (int i = 0; i < skillCount; i++)
    {
        file<< skills[i].getName() << "|" << skills[i].getLevel() <<endl;
    }
    file.close();
    cout<< "Skills saved successfully!" <<endl;
}
// Loads saved skills from a file
void loadSkills()
{
    ifstream file("skills.txt");
    if (!file)
    {
        return;
    }
    string name;
    double level;
    while (getline(file, name, '|') && file >> level)
    {
        file.ignore();
        if(skillCount < 50)
        {
            skills[skillCount] = Skill(name, level);
            skillCount++;
        }
    }
    file.close();
}
};
int main()
{
    SkillTracker tracker;
    int choice;
    do
    {
        cout<<"_________________ STUDENT SKILL TRACKER _________________"<<endl;
        cout<< "1. Add Skill"<<endl;
        cout<< "2. View Skills"<<endl;
        cout<< "3. Search Skill"<<endl;
        cout<< "4. Update Skill"<<endl;
        cout<< "5. Delete Skill" << endl;
        cout<< "6. Show Progress" << endl;
        cout<< "7. Exit"<<endl;
        cout<< "\nEnter your choice: ";
        cin>>choice;
        while (cin.fail() || choice < 1 || choice > 7)
       {
        cin.clear();
        cin.ignore(1000, '\n');
        cout<<"Invalid choice! Please enter a number from 1 to 7: ";
        cin>>choice;
       }
        switch(choice)
        {
        case 1:
            tracker.addSkill();
            break;
        case 2:
            tracker.viewSkills();
            break;
        case 3:
            tracker.searchSkill();
            break;
        case 4:
            tracker.updateSkill();
            break;
        case 5:
            tracker.deleteSkill();
            break;
        case 6:
            tracker.showProgress();
            break;
        case 7:
        	tracker.saveSkills();
            cout<< "Thank you for using Student Skill Tracker!" <<endl;
            break;
        default:
            cout<< "Invalid choice. Please try again."<<endl;
        }
    } while(choice != 7);
    return 0;
}
