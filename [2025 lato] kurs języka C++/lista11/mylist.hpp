
#pragma once
#include <iostream>
#include <initializer_list>
#include <stdexcept>

namespace adt
{

template<typename T> class mylist
{
protected:
    class mynode
    {
    public:
        T data;
        mynode* next;

        mynode(const T& value) : data(value), next(nullptr) {};
    };

    mynode* head;
    size_t size;

    void delete_list()
    {
        while (head != nullptr)
        {
            mynode* temp = head;
            head = head -> next;
            delete temp;
        }
        size = 0; 
    }

    void copy_list(const mylist& other)
    {
        head = nullptr;
        size = 0;
        mynode* curr = other.head;
        while (curr != nullptr) 
        {
            insert_at_end(curr -> data);
            curr = curr -> next;
        }   
    }

public:
    mylist() : head(nullptr), size(0) {}
    mylist(std::initializer_list<T> initList) : head(nullptr), size(0)
    {
        for (const T& value : initList) 
        {
            insert_at_end(value);
        }
    }
    // konstruktor kopiujacy
    mylist(const mylist& other) : head(nullptr), size(0)
    {
        copy_list(other);
    }
    // konstruktor przenoszacy
    mylist(mylist&& other) noexcept : head(other.head), size(other.size)
    {
        other.head = nullptr;
        other.size = 0;
    }
    ~mylist()
    {
        delete_list();
    }
    // przypisanie kopiujace
    mylist& operator=(const mylist& other)
    {
        if (this != &other)
        {
            delete_list();
            copy_list(other);
        }
        return *this;
    }
    // przypisanie przenoszace
    mylist& operator=(mylist&& other) noexcept
    {
        if (this != &other)
        {
            delete_list();
            head = other.head;
            size = other.size;
            other.head = nullptr;
            other.size = 0;
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const mylist& list) 
    {
        os << "{ ";
        mynode* curr = list.head;
        while (curr != nullptr) {
            if (curr -> next != nullptr) os << curr -> data << " -> ";
            else os << curr -> data << " ";
            curr = curr -> next;
        }
        os << "}";
        return os;
    }

    void insert_at_beginning(const T& value)
    {
        mynode* new_node = new mynode(value);
        new_node -> next = head;
        head = new_node;
        size++;
    }
    void insert_at_end(const T& value)
    {
        mynode* new_node = new mynode(value);
        if (head == nullptr)
        {
            head = new_node;
            size++;
            return;
        }
        mynode* curr = head;
        while (curr -> next != nullptr)
        {
            curr = curr -> next;
        }
        curr -> next = new_node;
        size++;
    }
    void insert_at_position(size_t position, const T& value)
    {
        if (position > size) 
        {
            throw std::out_of_range("invalid position");
        }
        if (position == 0) 
        {
            insert_at_beginning(value);
            return;
        }

        mynode* new_node = new mynode(value);
        mynode* curr = head;
        for (size_t i = 1; i < position; i++) 
        {
            curr = curr->next;
        }
        new_node -> next = curr -> next;
        curr -> next = new_node;
        size++;
    }

    void delete_from_start()
    {
        if (head == nullptr) 
        {
            throw std::out_of_range("list is empty");
        }
        mynode* temp = head;
        head = head -> next;
        delete temp;
        size--;
    }
    void delete_from_end()
    {
        if (head == nullptr) 
        {
            throw std::out_of_range("list is empty");
        }
        if (head -> next == nullptr) 
        {
            delete head;
            head = nullptr;
        } else 
        {
            mynode* curr = head;
            while (curr -> next && curr -> next -> next) 
            {
                curr = curr -> next;
            }
            delete curr -> next;
            curr -> next = nullptr;
        }
        size--;
    }
    void delete_from_position(size_t position)
    {
        if (position >= size) 
        {
            throw std::out_of_range("invalid position");
        }
        if (position == 0) 
        {
            delete_from_start();
            return;
        }
        mynode* curr = head;
        for (size_t i = 1; i < position; ++i) 
        {
            curr = curr -> next;
        }
        mynode* temp = curr -> next;
        curr -> next = curr -> next -> next;
        delete temp;
        size--;
    }
    void delete_value_first(const T& value)
    {
        if (head == nullptr) 
        {
            throw std::out_of_range("list is empty");
        }
        if (head -> data == value) 
        {
            delete_from_start();
            return;
        }
        mynode* curr = head;
        while (curr -> next != nullptr && curr -> next -> data != value) 
        {
            curr = curr -> next;
        }
        if (curr -> next != nullptr) 
        {
            mynode* temp = curr -> next;
            curr -> next = curr -> next -> next;
            delete temp;
            size--;
        } else 
        {
            throw std::invalid_argument("value not found");
        }
    }
    void delete_value_all(const T& value)
    {
        while (head != nullptr && head->data == value) 
        {
            delete_from_start();
        }
        if (head == nullptr) return;
        mynode* curr = head;
        while (curr -> next != nullptr) 
        {
            if (curr -> next -> data == value) 
            {
                mynode* temp = curr -> next;
                curr -> next = curr -> next -> next;
                delete temp;
                size--;
            } else 
            {
                curr = curr -> next;
            }
        }
    }

    size_t find_position(const T& value)
    {
        mynode* curr = head;
        size_t position = 0;
        while (curr != nullptr) 
        {
            if (curr -> data == value) 
            {
                return position;
            }
            curr = curr -> next;
            position++;
        }
        throw std::invalid_argument("value not found");
    }
    size_t count_value(const T& value)
    {
        size_t count = 0;
        mynode* curr = head;
        while (curr != nullptr) 
        {
            if (curr -> data == value) 
            {
                count++;
            }
            curr = curr -> next;
        }
        return count;
    }
    
    size_t count_all()
    {
        return size;
    }
    bool is_empty()
    {
        return size == 0;
    }
};
}