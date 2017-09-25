#include "CombinerLayer.h"

#include <string>

CombinerLayer::CombinerLayer(std::vector<Layer *> previousLayers, CombinerMaker *maker) :
    Layer(*previousLayers.begin(), maker),
    numPlanes (previousLayer->getOutputPlanes()),
    outputSize(previousLayer->getOutputSize())
{
    for (auto layer = previousLayers.begin(); layer != previousLayers.end(); ++layer)
    {
        (*layer)->nextLayer = this;
        this->previousLayers.push_back(*layer);
    }
//    this->previousLayers = previousLayers;
    output = NULL;
}

CombinerLayer::~CombinerLayer()
{
    delete[] output;
}

int CombinerLayer::getPersistSize(int version) const
{
    return 0;
}

std::string CombinerLayer::getClassName() const
{
    return "CombinerLayer";
}

bool CombinerLayer::needsBackProp()
{
    return true;
}

int CombinerLayer::getOutputNumElements() const
{
    return batchSize * numPlanes * outputSize * outputSize;
}

int CombinerLayer::getOutputSize() const
{
    return outputSize;
}

int CombinerLayer::getOutputPlanes() const
{
    return numPlanes;
}

void CombinerLayer::setBatchSize(int batchSize)
{
    this->batchSize = batchSize;
}

void CombinerLayer::backward()
{
    return;
}

bool CombinerLayer::providesGradInputWrapper() const
{
    return false;
}

CLWrapper *CombinerLayer::getGradInputWrapper()
{
    return NULL;
}

float *CombinerLayer::getGradInput()
{
    return nextLayer->getGradInput();
}

void CombinerLayer::forward()
{
    size_t outputSize = getOutputNumElements();

    delete[] output;
    output = new float[outputSize];

    std::memset(output, 0, sizeof(float)*outputSize);

    for (auto layer = previousLayers.begin(); layer != previousLayers.end(); ++layer)
        for (uint i = 0; i < outputSize; ++i)
            output[i] += (*layer)->getOutput()[i];

    for (uint i = 0; i < outputSize; ++i)
        output[i] = output[i] / previousLayers.size();
}

bool CombinerLayer::hasOutputWrapper() const
{
    return false;
}

CLWrapper *CombinerLayer::getOutputWrapper()
{
    return NULL;
}

float *CombinerLayer::getOutput()
{
    return output;
}
