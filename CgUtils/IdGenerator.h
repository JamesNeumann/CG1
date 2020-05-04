#ifndef IDGENERATOR_H
#define IDGENERATOR_H


class IdGenerator {
public:
    static unsigned int getId();
private:
    static unsigned int currentId;

};

#endif // IDGENERATOR_H
