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



// Vector works with passing a function as well which return bool
bool VectorComparator(const Task& t1, const Task& t2) {
    return (t1.start == t2.start) ? t1.ptime < t2.ptime : t1.start < t2.start;
}

sort(begin(tasks), end(tasks), VectorComparator);


------------------------------------------------------------------------------------------------------------------------
// Usually we would require custom comparator for PQ, Set, Map or STL functions like std::sort()

// As discussed for PQ, Set and Map these too also take such comparator
std::set<Type, Comparator2> my_set; // similar for Map

// There are new approaches where we don't need to create a struct just to define operator()
// we can also have a free function which returns bool and we can wrap it

bool CustomComparator(Type a, Type b) { return ....; }

// Before C++ 20, we can decltype on function but we also need to pass the comparator as ctor to the Set/Map/PQ
priority_queue<Task, vector<Task>, decltype(CustomComparator)*> pq_tasks(CustomComparator); // Either pass pointer or reference to function (functor) and also to ctor of PQ
set<Task, decltype(&CustomComparator)> ss(&CustomComparator); // Using reference

// But with lambda function we don't need to explict adding "*" or "&"
auto LambdaCustomComparator = [](Type& a, Type& b) -> bool { return ...; };
set<Task, decltype(LambdaCustomComparator)> ss(LambdaCustomComparator);

// With C++ 20 (we can avoid passing comparator to ctor of PQ/Set/Map)
auto LambdaCustomComparator = [](Type& a, Type& b) -> bool { return ...; };
set<Task, decltype(LambdaCustomComparator)> ss;












