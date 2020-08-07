#include<iostream>
#include<stdexcept>
#include<initializer_list>
#include<cstddef>
using namespace std;

const size_t initial_size = 4;

template<typename T>
class Vector{
  
  
 public:
    using value_type = T;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    
    class Const_iterator {
     public:
        using value_type = Vector::value_type;
        using difference_type = Vector::difference_type;
        using reference = Vector::const_reference;
        using pointer = Vector::const_pointer;
        using iterator_category = std::forward_iterator_tag;
        
    private:
        pointer ptr;
        const Vector* v;
        size_type i{0};
    public:
        Const_iterator(){};
        Const_iterator(pointer ptr, const Vector* v)
        {
            this->ptr = ptr;
            this->v = v;
        }
        Const_iterator& operator++(){
            if (ptr >= ((*v).end()).ptr) throw runtime_error ("Out of Bounds");
            this->ptr = this->ptr + 1;
            return *this;
        }
        
        Const_iterator operator++(int){
            Const_iterator old = *this;
            ++*this;
            return old;
        }
        
        reference operator*()const{
            if (ptr >= ((*v).end()).ptr) throw runtime_error ("Out of Bounds");
            return *ptr;
        }
        
        pointer operator->()const{
            if (ptr >= ((*v).end()).ptr) throw runtime_error ("Out of Bounds");
            return ptr;
        }
        
        friend bool operator!=(const Const_iterator& lop, const Const_iterator& rop)
        {
            if(lop.ptr == rop.ptr)
                return false;
            else
                return true;
            
        }
        
        friend bool operator==(const Const_iterator& lop, const Const_iterator& rop)
        {
            if(lop.ptr == rop.ptr)
                return true;
            else
                return false;
        }
        
        friend difference_type operator-(const Const_iterator& lop, const Const_iterator& rop) {
            return lop.ptr-rop.ptr;
        }
        
    
        size_type count() const;/*{
            throw runtime_error("Error!");
        }*/
        
    };
    
    
    class Iterator {
        
    public:
        using value_type = Vector::value_type;
        using difference_type = Vector::difference_type;
        using reference = Vector::reference;
        using pointer = Vector::pointer;
        using iterator_category = std::forward_iterator_tag;
        
    private:
        pointer ptr;
        Vector* v;
        int i{0};
    public:
        Iterator (){};
        Iterator(pointer ptr, Vector* v)
        {
            this->ptr = ptr;
            this->v = v;
        }
        
        Iterator& operator++(){
            if (ptr >= ((*v).end()).ptr) throw runtime_error ("Out of Bounds");
            ptr = ptr + 1;
            i++;
            return *this;
        }
        
        Iterator operator++(int){
            Iterator old = *this;
            ++*this;
            return old;
        }
        
        reference operator*()const{
            if (ptr >= ((*v).end()).ptr) throw runtime_error ("Out of Bounds");
            return *ptr;
        }
        
        pointer operator->()const{
            if (ptr >= ((*v).end()).ptr) throw runtime_error ("Out of Bounds");
            return ptr;
        }
        
        
        friend bool operator!=(const Iterator& lop, const Iterator& rop)
        {
            if(lop.ptr == rop.ptr)
                return false;
            else
                return true;
            
        }
        
        friend bool operator==(const Iterator& lop, const Iterator& rop)
        {
            if(lop.ptr == rop.ptr)
                return true;
            else
                return false;
        }
        
        friend difference_type operator-(const Iterator& lop, const Iterator& rop) {
            return lop.ptr-rop.ptr;
        }
        
        operator Const_iterator(){
          return Const_iterator{ptr,v};
        }
        
        int count () {
            return i;
        }
        
    };
    
    
using const_iterator = Const_iterator;
using iterator = Iterator;
   
    
    
private:
    size_t sz;
    size_t max_sz;
    pointer values;
public:
  Vector():Vector(initial_size){};
  Vector(size_t newsz):sz{0}{
    if(newsz < initial_size)
      newsz = initial_size;
   
    values = new T [newsz];
    max_sz = newsz;
  }

  Vector(initializer_list <T> li):Vector(li.size()){
    for(auto& elem : li)
        push_back(elem);
  }

  ~Vector(){delete[] values;}

  Vector(const Vector& copy):Vector(copy.size()){
    for(size_t i = 0; i < copy.size(); ++i)
      push_back(copy[i]);
  }

  void push_back(T value){
    if(sz == max_sz)
       reserve(sz*2);
    values[sz++] = value;
  }

  void reserve(size_t newsz){
     T* zwischen = new T[newsz];

     for(size_t i = 0; i < sz; ++i)
      zwischen[i] = values[i];
     delete[] values;
     values = zwischen;
     max_sz = newsz;
   }
    
   void shrink_to_fit()
    {
        if (sz > max_sz)
            throw runtime_error("This size is not possible");
        
        if (sz == max_sz)
        {
            cout << "Kapazitaet ist schon reduziert" << endl;
            return;
        }
        
        T *arr = new T[sz];
        
        for (size_t i = 0; i < sz; i++)
        {
            arr[i] = values[i];
        }
        delete [] values;
        values = arr;
        max_sz = sz;
    }

  T& operator[](size_t index){
    if(index < 0 || index >= sz)
       throw runtime_error("Out of Bounds");
     
    return values[index];
  } 

  const T& operator[](size_t index) const {
    if(index < 0 || index >= sz)
       throw runtime_error("Out of Bounds");
     
    return values[index];
  } 

  Vector operator=(Vector src){
     delete [] values;
     sz = 0;
     max_sz = src.size();

     values = new T[src.size()];
     for(size_t i = 0; i < src.size(); ++i)
       push_back(src[i]);
     return *this;
  }

  size_t size() const {
     return sz;
  }

  size_t get_max_size() const {return max_sz;}

  bool empty() const {return sz == 0;}
  
  void clear() {sz = 0;}

  void pop_back() {
  if(sz == 0)
    return;
     --sz;
  }
    
    
   
    iterator begin(){return Iterator{values, this};}
    iterator end(){return Iterator{values+sz, this};}
    
    
    const_iterator begin() const {return Const_iterator{values, this};}
    const_iterator end() const {return Const_iterator{values+sz, this};}


    
    iterator erase(const_iterator pos)
    {
        auto diff = pos-begin();
        
        if (diff<0 || static_cast<size_type>(diff)>=sz)
            throw runtime_error("Iterator out of bounds");
        
        
        size_type current{static_cast<size_type>(diff)};
        for (size_type i{current}; i<sz-1; ++i)
            values[i]=values[i+1]; --sz;
        return iterator{values+current, this};
    }
    
    iterator insert(const_iterator pos, const_reference val)
    {
        auto diff = pos-begin();
        
        if (diff<0 || static_cast<size_type>(diff)>sz)
            throw runtime_error("Iterator out of bounds");
        
        size_type current{static_cast<size_type>(diff)};
        
        if (sz>=max_sz)
            reserve(max_sz*2);
        
        for (size_t i {sz}; i-->current;) values[i+1]=values[i];
        values[current]=val;
        ++sz;
        
        return iterator{values+current, this};
    }
    
    
    ostream& print(ostream& o) const {
        o<<"[";
        for(size_t i=0; i<sz; i++)
            if(i==sz-1){
                o << values[i];
            }else{
                o << values[i] << ",";
            }
        o<<"]";
        
        return o;
    }
    
};

template<typename T>
size_t Vector<T>::Const_iterator::count()const{throw runtime_error("Error");};




/*
Const_iterator& operator++(){
    if (ptr >= ((*v).end()).ptr) throw runtime_error ("Out of Bounds");
    this->ptr = this->ptr + 1;
    return *this;
}

Const_iterator operator++(int){
    Const_iterator old = *this;
    ++*this;
    return old;
}*/



template<typename T>
ostream& operator<<(ostream& o, const Vector<T>& t) {
    return t.print(o);
}

