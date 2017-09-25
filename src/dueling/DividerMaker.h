#ifndef DIVIDERMAKER_H
#define DIVIDERMAKER_H

#include "layer/LayerMaker.h"

class DividerMaker : public LayerMaker2
{
public:
    PUBLICAPI DividerMaker();
    PUBLICAPI static DividerMaker *instance() {
        return new DividerMaker();
    }
    virtual DividerMaker *clone() const {
        return new DividerMaker(*this);
    }
    virtual Layer *createLayer(Layer *previousLayer);
};

#endif // DIVIDERMAKER_H
