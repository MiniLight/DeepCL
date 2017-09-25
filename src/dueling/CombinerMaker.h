#ifndef COMBINERMAKER_H
#define COMBINERMAKER_H

#include "layer/LayerMaker.h"
#include <vector>
#include <algorithm>

class CombinerMaker : public LayerMaker2
{
    std::vector<Layer*> _previousLayers;
public:
    PUBLICAPI CombinerMaker();

    PUBLICAPI CombinerMaker *addPrevious(Layer *previous) {
        if(std::find(this->_previousLayers.begin(), this->_previousLayers.end(), previous) == this->_previousLayers.end())
            this->_previousLayers.push_back(previous);
        return this;
    }
    PUBLICAPI static CombinerMaker *instance() {
        return new CombinerMaker();
    }
    virtual CombinerMaker *clone() const {
        return new CombinerMaker(*this);
    }
    virtual Layer *createLayer(Layer *previousLayer);
};

#endif // COMBINERMAKER_H
