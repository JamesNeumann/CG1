#include "IdGenerator.h"

unsigned int IdGenerator::currentId = 1;

unsigned int IdGenerator::getId() {
    return currentId++;
}
