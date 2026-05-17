// Copyright 2021 NNTU-CS
#include "train.h"
#include <cstddef>

Train::Train() : countOp(0), first(nullptr) {}

void Train::addCar(bool light) {
    Car* newCar = new Car{light, nullptr, nullptr};
    if (!first) {
        first = newCar;
        first->next = first;
        first->prev = first;
    } else {
        Car* last = first->prev;
        last->next = newCar;
        newCar->prev = last;
        newCar->next = first;
        first->prev = newCar;
    }
}

int Train::getLength() {
    if (!first) return 0;
    countOp = 0;
    first->light = true;
    Car* current = first;
    int stepsToCurrent = 0;
    while (true) {
        current = current->next;
        stepsToCurrent++;
        countOp++;
        if (current->light) {
            current->light = false;
            const Car* returnPointer = current;
            for (int i = 0; i < stepsToCurrent; i++) {
                returnPointer = returnPointer->prev;
                countOp++;
            }
            if (!returnPointer->light) {
                return stepsToCurrent;
            }
            for (int i = 0; i < stepsToCurrent; i++) {
                returnPointer = returnPointer->next;
                countOp++;
            }
        }
    }
}

int Train::getOpCount() {
    return countOp;
}
