#include "C_InstanceID.h"

C_InstanceID::C_InstanceID(Object *owner) : Component(owner), id(count++) { }

C_InstanceID::~C_InstanceID() { }

int C_InstanceID::Get() const { return id; }
