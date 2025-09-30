#pragma once
#include <stdexcept>
#include <string>
using namespace std;

class wyjatek_samotnika : public logic_error 
{
public:
    wyjatek_samotnika(const string& msg) : logic_error(msg) {}
};
    
class niepoprawna_komenda : public wyjatek_samotnika 
{
public:
    niepoprawna_komenda() : wyjatek_samotnika("Niepoprawna komenda!") {}
    niepoprawna_komenda(const std::string& msg) : wyjatek_samotnika("Niepoprawna komenda - " + msg) {}
};
    
class nieprawidlowy_ruch : public wyjatek_samotnika 
{
public:
    nieprawidlowy_ruch() : wyjatek_samotnika("Nieprawidłowy ruch!") {}
    nieprawidlowy_ruch(const std::string& msg) : wyjatek_samotnika("Nieprawidłowy ruch -" + msg) {}
};