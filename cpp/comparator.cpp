// Writing custom comparator is useful for some cases. Ex: when creating our own data Type

// For a class, we can use function overloading and overload "operator<" or "operator>"
// As any of < or > is suffcient enough to sort the type so overloading obe is suffcient.

// it should be marked as "const"
struct Task {
    int start, ptime, idx;
    Task(int s, int t, int i): start(s), ptime(t), idx(i) {}
     bool operator<(const Task& other) const {
         return (ptime == other.ptime) ? idx > other.idx : ptime > other.ptime;
     }

    friend ostream& operator<<(ostream& oo, const Task& task);
};

ostream& operator<<(ostream& oo, const Task& task) {
    oo << task.start << ", " << task.ptime << ", " << task.idx << "\n";
    return oo;
}


// But what If I want to use this Type and I need it to perform comparison one time on ptime and idx and in one case ptime and start ?
// In that case writing comparator inside the class itself won't work. But we can define separate custom comparator
// But while writing separate comparator, we need to overload "operator()"

struct Comparator1 {
    bool operator()(const Task& t1, const Task& t2) {
        return (t1.ptime == t2.ptime) ? t1.idx > t2.idx : t1.ptime > t2.ptime;
    }
};

struct Comparator2 {
    bool operator()(const Task& t1, const Task& t2) {
        return (t1.start == t2.start) ? t1.ptime < t2.ptime : t1.start < t2.start;
    }
};


// We can use it like
priority_queue<Task, vector<Task>, Comparator1> pq_tasks; // for PQ we need to provide comparator during its declaration

vector<Task> tasks;
sort(begin(tasks), end(tasks), Comparator2()); // we need to call operator() unlike in above queue

// We can also use lambda function in C++ to write anonymous comparator on the fly
sort(begin(tasks), end(tasks), [](const Task& t1, const Task& t2) {
         return (t1.start == t2.start) ? t1.ptime < t2.ptime : t1.start < t2.start;
     });

