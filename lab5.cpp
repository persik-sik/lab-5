#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <set>
using namespace std;

struct Student {
    string Name;
    string GroupId;
    vector<unsigned> Ratings;
    vector<string> Subjects;
};

void SortByName(vector<Student>& st) {
    sort(st.begin(), st.end(), [](const Student& a, const Student& b) {
        return a.Name < b.Name;
    });
}

double Calc(const Student& st) {
    float sum = 0;
    for (int i = 0; i < st.Ratings.size(); ++i){
        sum += st.Ratings[i];
    }
    return sum / st.Ratings.size();
}

void SortByRating(vector<Student>& st) {
    sort(st.begin(), st.end(), [](const Student& a, const Student& b) {
        return Calc(a) > Calc(b);
    });
}

size_t CountTwoness(const vector<Student>&st){
    int c = 0;
    for(const auto& student : st){
        for(const auto& rating : student.Ratings){
            if (rating <= 2) {
                ++c;
                break;
            }
        }
    }
    return c;
}

size_t CountExcellent(const vector<Student>& st){
    int c = 0;
    for(const auto& student : st){
        if (all_of(student.Ratings.begin(), student.Ratings.end(), [](unsigned rating) {
            return rating == 5;
        })) {
            c++;
        }
    }
    return c;
}

vector<Student> VectorMathExcellent(const vector<Student>& st) {
    vector<Student> vec;
    for (const auto& student : st) {
        auto i = find(student.Subjects.begin(), student.Subjects.end(), "Math");
        if (i != student.Subjects.end()) {
            int index = student.Subjects.begin() - i;
            if (student.Ratings[index] == 5) vec.push_back(student);
        }
    }
    return vec;
}

vector<string> GroupsId(const vector<Student>& st){
    set<string> group;
    for (const auto& student : st) group.insert(student.GroupId);
    vector<string> res(group.begin(), group.end());
    return res;
}

struct Group {
    string Id;
    vector<Student> Students;
};

vector<Group> Groups(const vector<Student>& st){
    vector<Group> groups;
    for (const auto& student : st) {
        bool groupFound = false;
        for (auto& group : groups) {
            if (group.Id == student.GroupId) {
                group.Students.push_back(student);
                groupFound = true;
                break;
            }
        }
        if (!groupFound) {
            Group newGroup;
            newGroup.Id = student.GroupId;
            newGroup.Students.push_back(student);
            groups.push_back(newGroup);
        }
    }

    return groups;
}
