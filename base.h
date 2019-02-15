#ifndef __BASE_H__
#define __BASE_H__

class nocopyable{
public:
    nocopyable(const nocopyable&)=delete;
    //operator=(const nocopyable&)=delete;
protected:
    nocopyable()  = default;
    ~nocopyable() = default;
};







#endif


