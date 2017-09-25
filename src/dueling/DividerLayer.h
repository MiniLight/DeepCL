#ifndef DIVIDERLAYER_H
#define DIVIDERLAYER_H

#include <vector>
#include "layer/Layer.h"
#include "dueling/DividerMaker.h"

class DividerLayer : public Layer
{
    std::vector<Layer*> nextLayers;
    int batchSize;
    const int numPlanes;
    const int inputSize;
    float *gradInput;
public:
    DividerLayer(Layer *previousLayer, DividerMaker *maker);
    ~DividerLayer();

    VIRTUAL void setNextLayer(Layer * nextLayer) override;

    /// \brief Get the size of array needed for persisting to/from an array
    PUBLICAPI virtual int getPersistSize(int version) const override;
    virtual std::string getClassName() const override;
    VIRTUAL bool needsBackProp() override;
    VIRTUAL int getOutputNumElements() const override;
    VIRTUAL int getOutputSize() const override;
    VIRTUAL int getOutputPlanes() const override;
    PUBLICAPI VIRTUAL void setBatchSize(int batchSize) override;

    VIRTUAL void backward() override;
    VIRTUAL bool providesGradInputWrapper() const override;
    VIRTUAL CLWrapper *getGradInputWrapper() override;
    VIRTUAL float *getGradInput() override;

    VIRTUAL void forward() override;
    VIRTUAL bool hasOutputWrapper() const override;
    VIRTUAL CLWrapper *getOutputWrapper() override;
    VIRTUAL float *getOutput() override;
private:
    int getInputNumElements();
};

#endif // DIVIDERLAYER_H
