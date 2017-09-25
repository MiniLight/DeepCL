#include "DividerLayer.h"

#include <string>

DividerLayer::DividerLayer(Layer *previousLayer, DividerMaker *maker) :
    Layer(previousLayer, maker),
    numPlanes(previousLayer->getOutputPlanes()),
    inputSize(previousLayer->getOutputSize())
{
    gradInput = NULL;
}

DividerLayer::~DividerLayer()
{
    delete[] gradInput;
}

void DividerLayer::setNextLayer(Layer *nextLayer)
{
    nextLayers.push_back(nextLayer);
}

int DividerLayer::getPersistSize(int version) const
{
    return 0;
}

std::string DividerLayer::getClassName() const
{
    return "DividerLayer";
}

bool DividerLayer::needsBackProp()
{
    return true;
}

int DividerLayer::getOutputNumElements() const
{
    return previousLayer->getOutputNumElements();
}

float *DividerLayer::getGradInput()
{
    return gradInput;
}

float *DividerLayer::getOutput()
{
    return previousLayer->getOutput();
}

int DividerLayer::getOutputSize() const
{
    return previousLayer->getOutputSize();
}

int DividerLayer::getOutputPlanes() const
{
    return numPlanes;
}

void DividerLayer::setBatchSize(int batchSize)
{
    this->batchSize = batchSize;
}

void DividerLayer::forward()
{
    return;
}

bool DividerLayer::providesGradInputWrapper() const
{
    return false;
}

CLWrapper *DividerLayer::getGradInputWrapper()
{
    return NULL;
}

bool DividerLayer::hasOutputWrapper() const
{
    return false;
}

CLWrapper *DividerLayer::getOutputWrapper()
{
    return NULL;
}

void DividerLayer::backward()
{
    size_t gradSize = getInputNumElements();

    delete[] gradInput;
    gradInput = new float[gradSize];
    std::memset(gradInput, 0, sizeof(float)*gradSize);

    for (auto layer = nextLayers.begin(); layer != nextLayers.end(); ++layer)
        for (uint i = 0; i < gradSize; ++i)
            gradInput[i] += (*layer)->getGradInput()[i];

    for (uint i = 0; i < gradSize; ++i)
        gradInput[i] = gradInput[i] / nextLayers.size();
}

int DividerLayer::getInputNumElements() {
    return batchSize * numPlanes * inputSize * inputSize;
}
