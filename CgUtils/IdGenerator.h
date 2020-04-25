#ifndef UUID_H
#define UUID_H

class IdGenerator {
private:
    static unsigned int currentId = 1;
public:
    unsigned int getId() { return currentId++; }
}

#endif
