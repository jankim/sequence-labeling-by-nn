#ifndef POSTAGGER_POS_INPUT1_MLP_WITHOUT_TAG_POSTAG_INPUT1_MLP_WITHOUT_TAG_NO_FEATURE_MODEL_H_
#define POSTAGGER_POS_INPUT1_MLP_WITHOUT_TAG_POSTAG_INPUT1_MLP_WITHOUT_TAG_NO_FEATURE_MODEL_H_
#include <boost/log/trivial.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include "postagger/base_model/input1_mlp_model_no_feature.h"
#include "modelmodule/hyper_layers.h"
namespace slnn{

class Input1MLPWithoutTagNoFeatureModel : public Input1MLPModelNoFeature
{
    friend class boost::serialization::access;
public :
    Input1MLPWithoutTagNoFeatureModel();
    ~Input1MLPWithoutTagNoFeatureModel();
    Input1MLPWithoutTagNoFeatureModel(const Input1MLPWithoutTagNoFeatureModel &) = delete ;
    Input1MLPWithoutTagNoFeatureModel &operator=(const Input1MLPWithoutTagNoFeatureModel &) = delete ;

    void set_model_param(const boost::program_options::variables_map &var_map) override;
    void build_model_structure() override;
    void print_model_info() override;

    cnn::expr::Expression  build_loss(cnn::ComputationGraph &cg,
        const IndexSeq &input_seq, 
        const POSContextFeature::ContextFeatureIndexGroupSeq &context_feature_gp_seq,
        const IndexSeq &gold_seq)  override ;
    void predict(cnn::ComputationGraph &cg ,
        const IndexSeq &input_seq, 
        const POSContextFeature::ContextFeatureIndexGroupSeq &context_feature_gp_seq,
        IndexSeq &pred_seq) override ;

    template <typename Archive>
    void serialize(Archive &ar, unsigned version);

private :
    BareInput1 *input_layer;
    MLPHiddenLayer *mlp_hidden_layer;
    SoftmaxLayer *output_layer;
    ContextFeatureLayer<POSContextFeature::ContextSize> *pos_context_feature_layer;
};

template <typename Archive>
void Input1MLPWithoutTagNoFeatureModel::serialize(Archive &ar, unsigned version)
{
    ar & boost::serialization::base_object<Input1MLPModelNoFeature>(*this);
}

}


#endif