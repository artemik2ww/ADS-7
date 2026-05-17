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
    int stepsToCurrent = 1;
    while (true) {
        Car* current = first;
        for (int i = 0; i < stepsToCurrent; i++) {
            current = current->next;
            countOp++;
        }
        if (current->light) {
            current->light = false;
            for (int i = 0; i < stepsToCurrent; i++) {
                current = current->prev;
                countOp++;
            }
            if (!current->light) {
                return stepsToCurrent;
            }
            for (int i = 0; i < stepsToCurrent; i++) {
                current = current->next;
                countOp++;
            }
            current->light = true;
            for (int i = 0; i < stepsToCurrent; i++) {
                current = current->prev;
                countOp++;
            }
        } else {
            for (int i = 0; i < stepsToCurrent; i++) {
                current = current->prev;
                countOp++;
            }
        }
        stepsToCurrent++;
    }
}

int Train::getOpCount() {
    return countOp;
}
