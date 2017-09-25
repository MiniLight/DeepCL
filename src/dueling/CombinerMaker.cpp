#include "CombinerMaker.h"
#include "CombinerLayer.h"

CombinerMaker::CombinerMaker()
{

}

Layer *CombinerMaker::createLayer(Layer *previousLayer)
{
    this->addPrevious(previousLayer);
    return new CombinerLayer(_previousLayers, this);
}
