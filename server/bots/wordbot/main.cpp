#include <stdio.h>
#include <iostream>
#include <server.h>

int main()
{
    server s = server();
    s.handle_connections();
    /*python_connect c = python_connect();
    std::cout<<c.getRezult("get_like человек");
    std::cout<<c.getRezult("get_not_mach человек собака волк дерево")<<'\n';
    std::cout<<c.getRezult("get_summ человек собака")<<'\n';
    std::cout<<c.getRezult("get_raz король мужчина")<<'\n';
    */
}
