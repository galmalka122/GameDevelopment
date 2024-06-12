#ifndef C_InstanceID_h
#define C_InstanceID_h

#include "Component.h"

class C_InstanceID : public Component{

public:

    C_InstanceID(Object* owner);
    ~C_InstanceID();

    int Get() const;

private:
    static int count;
    int id;

};


#endif // C_InstanceID_h
