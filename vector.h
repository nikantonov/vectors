//
//  vector.h
//  Vektor projekt
//
//  Created by Никита on 12.02.18.
//  Copyright (c) 2018 Никита. All rights reserved.
//

#include <iostream>
#include <initializer_list>
using namespace std;

class Vector {
  private:
    size_t sz;
    size_t max_sz;
    double* values;
    
  public:
    
    Vector ()  //Defaultkonstruktor
    {
        sz = 0;
        max_sz = 0;
        values = new double [max_sz];
    }
    
    Vector (int m) //Konstruktor mit Größenangabe
    {
        max_sz = m;
        sz = 0;
        if(max_sz > 0)
            values = new double[max_sz];
        else
            values = nullptr;
    }
    
    Vector(initializer_list <double> li) //Konstruktor mit Initialisierungsliste
    {
        if (li.size() > 0)
        {
            values = new double[li.size()];
        }
        else
        {
            values = nullptr;
        }
        
        sz = 0;
        max_sz = li.size();
        
        for (const auto& elem : li)
        {
            values[sz++] = elem;
        }
    }
    
    Vector (const Vector &arr) //Kopierkonstruktor
    {
        values = new double[arr.max_sz];
        size_t new_size = 0;
        for (size_t i = 0; i < arr.size(); i++)
        {
            values[i] = arr.values[i];
            new_size++;
        }
        sz = new_size;
        max_sz = arr.max_sz;
        
    }
    
    Vector &operator=(const Vector &exp) //Kopierzuweisungsoperator
    {
        delete[] values;
        values = new double[exp.max_sz];
        max_sz = exp.max_sz;
        sz = exp.sz;
        for (size_t i = 0; i < sz; i++)
        {
            values[i] = exp.values[i];
        }
        
        return *this;
        
    }
    
    ~Vector() {             //Destructor
        delete[] values;
    }
    
    size_t size() const{ //liefert size
        return sz;
    }
    
    bool empty()  //liefert true, falls der Vektor leer ist, false sonst
    {
        if (sz == 0)
            return true;
        else
            return false;
    }
    
    void clear() //loescht
    {
        sz = 0;
    }
    
    void reserve(size_t n)  //Vergroesert Kapazitaet
    {
        if (n <= max_sz)
            throw runtime_error("Error");
        
        double *arr = new double[n];
        
        for (size_t i = 0; i < sz; i++)
        {
            arr[i] = values[i];
        }
        
        delete [] values;
        values = arr;
        max_sz = n;
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
        
        double *arr = new double[sz];
        
        for (size_t i = 0; i < sz; i++)
        {
            arr[i] = values[i];
        }
        delete [] values;
        values = arr;
        max_sz = sz;
    }
    
    void push_back(double i)   // fügt ein neues Element am Ende hinzu
    {
        if (sz > max_sz)
            throw runtime_error("Error");
        
        if (sz == max_sz)
            max_sz = max_sz + 1;
        
        values[sz] = i;
        
        sz++;
    }
    
    void pop_back() //entfernt ein Element vom Ende
    {
        if (sz > 0)
        {
            size_t s = sz - 1;
            values[s] = NULL;
            sz = s;
        }
        
        if (sz == 0)
        {
            cout << " Vector ist leer ";
            return;
        }
    }
    
    
    double &operator[](size_t i)
    {
        if (i < sz)
        {
            return values[i];
        }
        else
        {
            throw runtime_error("Error");
        }
    }
    
    const double &operator[](size_t i) const
    {
        if (i < sz)
        {
            return values[i];
        }
        else
        {
            throw runtime_error("Error");
        }
    }
    
};





