    #include <iostream>
    struct Student {
        std::string fio;
        char gender;
        int age;
    };
    template <typename T>
    bool operator!=(T first, T second) {
        if(first.fio == second.fio) {
            if ((first.gender == second.gender) && (first.age == second.age));
        }
    }
template <class T>
struct Node{
Node<T>*previos;
Node<T>*next;
T value;
};
template<class T>
struct Circle{
    Node<T>*first;
    Node<T>*last;
    int size;
};
template<class T>
void constructor(Circle<T>&list)
{
    list.size=0;
    list.first=nullptr;
    list.last=nullptr;
}
template<class T>
void destructor(Circle<T>&list){
    for (int i = 1; i < list.size; i++)
    {
        list.first = list.first->next;
        delete list.first->previos;
    }
    delete list.first;
    list.first = nullptr;
    list.size = 0;
}
template<typename T>
int size(Circle<T>& list)
{
    return list.size;
}
template <class T>
void push_front(Circle<T>&list,T value){
    auto*ptr = new Node<T>;
    ptr->value = value;//связываем
    if (list.first == nullptr)
    {
        list.first = ptr;//связка с самим с собой
        list.last=ptr;//связка с последним потому что первый последний связаны
        ptr->next = ptr;
        ptr->previos = ptr;
    }
    else
    {
        ptr->next=list.begin;
        list.begin->previos=ptr;
        ptr->previos=list.end;
        list.end->next=ptr;
        list.begin=ptr;
    }
}
template<typename T>
void push_back(Circle <T> &list, T value) {
    auto*ptr = new Node<T>;
    ptr->value = value;
    if (list.first == nullptr)
    {
        list.first = ptr;
        ptr->next = ptr;
        ptr->previos = ptr;
    }
    else
    {
        list.first->previos->next = ptr;
        ptr->previos = list.first->previos;
        list.first->previos = ptr;
        ptr->next = list.first;
    }
    list.size++;
}
template <typename T>
void insert_index(Circle<T>& list, T data, int index)
{
    //если инлекс 0 вызывавем пущ фронт
    //если индекс равен размеру то буш бэк
    //в ином случае
        int count = 0;
        if (index == 0)
            push_front(list, data);
        else if (index == list.size)
            push_back(list, data);
        else {
            list.size++;
            Node<T>* ptr = list.first;
            while (count != index - 1)
            {
                ptr = ptr -> next;
                count ++;
            }
            auto element = new Node<T>;
            element->value = data;
            element->previos = ptr;
            ptr->next->previos = element;
            element->next = ptr->next;
            ptr->next = element;
        }
    }
    std::ostream& operator << (std::ostream& output,const Student& st) {
        output << "Full name: " << st.fio << "\nGender: " << st.gender << "\nAge: "<< st.age <<std::endl << std::endl;
        return output;
    }
template <typename T>
void print(Circle<T>& list)
{
    Node<T>* a = list.first;
    for (int i = 0; i < list.size; ++i)
    {
        std::cout << a->value << ' ';
        a = a->next;
    }
}
template <typename T>
void insert_pointer
        (Circle<T>& list, T data, Node<T>* z)//указатель куда я вставляю
{
    auto* ptr = new Node<T>;
    ptr->value = data;
    ptr->next = z->next;
    ptr->previos = z;
    ptr->next->previos = ptr;
    ptr->previos->next = ptr;
    list.size++;
}
template<typename T>
T pop_first(Node<T>& list)//УСЛОВИЕ
{
    if (list.size == 0) {
        std::cout<<"Circle is empty"<<std::endl;
        T exit;
        return exit;
    }
    if (list.first != nullptr) {
        //присваиваем
        Node<T> *z = list.first;
        Node<T> *y = list.first->next;
        T data = z->value;//запоминаем значение в тип переменной,потому что потом его вернуть
        y->previos=list.last;
        list.last->next=y;
        delete z;
        list.first=y;
        return data;
    }
}
template<typename T>
T pop_end(Circle<T>& list) {
    if (list.size == 0) {
        std::cout << "Circle is empty" << std::endl;
        T exit;
        return exit;
    }
    else
    {
        list.first=list.first;//begin
        Node<T> *z = list.first->previos;
        list.first->previos = list.first->previos->previos;
        T data = z->value;
        delete z;
        return data;
    }
}
    template<typename T>
    T get(Circle<T> &list, int index) {
        T data;
        Node<T> *ptr = list.first;
        for (int i = 0; i < index; ++i) {
            ptr = ptr->next;
        }
        {
            ptr->next->previos = ptr->previos;
            ptr->previos->next = ptr->next;
            data = ptr->value;
            delete ptr;
            list.size--;
        }
        return data;
    }
    template<typename T>
    T get_by_pointer(Circle<T> &list, Node<T> *a) {
        T data;
        Node<T> *ptr;
        if (a == list.first) {
            a = list.first->next;
        }
        {
            ptr = a;
            ptr->next->previos = ptr->previos;
            ptr->previos->next = ptr->next;
            data = ptr->value;
            delete ptr;
            list.size--;
        }
        return data;
    }
    template<typename T>
    T get_by_index(Circle<T> &list, int index) {
        T data = 0;
        Node<T> *ptr = list.first;
        if (ptr != nullptr) {
            for (int i = 0; i < index; ++i) {
                ptr = ptr->next;
            }
            data = ptr->value;
            std::cout << data << std::endl;
        }
        return data;
    }
    int main() {
        Circle<int> group{};
        constructor(group);
        destructor(group);
     std::cout<<"The size of the list is: "<<size(group)<<std::endl;
        push_front(group, 5);
        push_back(group, 3);
        int index = 3;
        insert_index(group, 3, index);
        print(group);
        insert_pointer(group, 4, group.first->next->next);
        insert_index(group, 13, 14);
        get(group, index);
        get_by_index(group, 2);
        get_by_pointer(group, group.first);
        pop_end(group);
        Student stud1 = {"Valiev  Vali Samedovich",'m', 20};
        Student stud2 = {"Jordan Michael Dmitrievich",'m', 55};
        Student stud3 = { "Grr Mmmm Zzzzz",'m', 35};
        Student stud4 = {"Yasenko Sofia Dmitrievna", 'f', 19};
        Student stud5 = {"Dratuti Misha Valievich",'m', 47};
        Circle<Student> circle1;
        constructor (circle1);
        push_front(circle1, stud1);
        push_front(circle1, stud2);
        std::cout << "Circle of citizens: ";
        std::cout << std::endl;
        print(circle1);
        push_back(circle1, stud3);
        std::cout << "Circle with pushed person to the end: " << std::endl;
        print(circle1);
        insert_index(circle1, stud4,2);
        std::cout << "Circle with pushed person to index 2: " << std::endl;
        print(circle1);
        Node<Student>* people = circle1.last->next->next;
        std::cout << "Circle with pushed person number 4 using pointer at the second element: " << std::endl;
        insert_pointer(circle1,stud5,people);
        print(circle1);
        std::cout << "Size of circle: " << size(circle1) << std::endl;
        std::cout << "Popped person from the beginning: " << std::endl;
        print(circle1);
       std::cout << std::endl;
        return 0;
    }
