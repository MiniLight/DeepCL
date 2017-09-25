#ifndef COMBINERLAYER_H
#define COMBINERLAYER_H

#include <vector>
#include "layer/Layer.h"
#include "dueling/CombinerMaker.h"

class CombinerLayer : public Layer
{
protected:
    std::vector<Layer*> previousLayers;
    int batchSize;
    const int numPlanes;
    const int outputSize;
    float *output;
public:
    CombinerLayer(std::vector<Layer*> previousLayers, CombinerMaker *maker);
    ~CombinerLayer();



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


};

#endif // COMBINERLAYER_H
