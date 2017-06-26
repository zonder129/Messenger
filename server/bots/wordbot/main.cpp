#include <stdio.h>
#include <cmath>
#include <Python.h>

#include <python_connect.h>
#include <iostream>
int main()
{
    python_connect c = python_connect();
    std::cout<<c.getRezult("get_like человек");
    std::cout<<c.getRezult("get_not_mach человек собака волк дерево");
    std::cout<<c.getRezult("get_summ человек собака");
    std::cout<<c.getRezult("get_raz король мужчина");

}
