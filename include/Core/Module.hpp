#ifndef MODULE_HPP
#define MODULE_HPP

class Module
{
public:
    Module(){}
    ~Module(){}

    virtual void Init() = 0;
    virtual void Shutdown() = 0;
};

#endif
