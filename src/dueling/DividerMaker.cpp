#include "DividerMaker.h"
#include "DividerLayer.h"

DividerMaker::DividerMaker()
{

}

Layer *DividerMaker::createLayer(Layer *previousLayer)
{
    return new DividerLayer(previousLayer , this);
}
