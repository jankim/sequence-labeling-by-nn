#include "layers.h" 

using namespace cnn;
using namespace std;
namespace slnn {

// DenseLayer

DenseLayer::DenseLayer(Model *m , unsigned input_dim , unsigned output_dim)
    :w(m->add_parameters({output_dim , input_dim})) ,
    b(m->add_parameters({output_dim}))
{}

DenseLayer::~DenseLayer(){}

// Merge 2 Layer

Merge2Layer::Merge2Layer(Model *m, unsigned input1_dim, unsigned input2_dim,unsigned output_dim)
    :w1(m->add_parameters({ output_dim , input1_dim })),
    w2(m->add_parameters({ output_dim , input2_dim })),
    b(m->add_parameters({ output_dim}))
{}

Merge2Layer::~Merge2Layer() {}


// Merge 3 Layer

Merge3Layer::Merge3Layer(Model *m ,unsigned input1_dim , unsigned input2_dim , unsigned input3_dim , unsigned output_dim )
    :w1(m->add_parameters({output_dim , input1_dim})) ,
    w2(m->add_parameters({output_dim , input2_dim})) ,
    w3(m->add_parameters({output_dim , input3_dim})) ,
    b(m->add_parameters({output_dim}))
{}

Merge3Layer::~Merge3Layer(){}

// MLPHiddenLayer

MLPHiddenLayer::MLPHiddenLayer(Model *m, unsigned input_dim, const initializer_list<unsigned> &layers_dim)
    :nr_hidden_layer(layers_dim.size()),
    w_list(nr_hidden_layer),
    b_list(nr_hidden_layer),
    w_expr_list(nr_hidden_layer),
    b_expr_list(nr_hidden_layer)
{
    assert(nr_hidden_layer > 0);
    initializer_list<unsigned>::const_iterator dim_iter = layers_dim.begin();
    w_list[0] = m->add_parameters({ *dim_iter, input_dim });
    b_list[0] = m->add_parameters({ *dim_iter });
    for( unsigned i = 1; i < nr_hidden_layer ; ++i)
    {
        ++dim_iter;
        assert(dim_iter != layers_dim.end());
        w_list[i] = m->add_parameters({ *dim_iter, layers_dim[i - 1] });
        b_list[i] = m->add_parameters({ *dim_iter });
    }
}

inline
void MLPHiddenLayer::new_graph(ComputationGraph &cg)
{
    for( unsigned i = 0 ; i < nr_hidden_layer; ++i )
    {
        w_expr_list[i] = parameter(cg, w_list[i]);
        b_expr_list[i] = parameter(cg, b_list[i]);
    }
}

inline
cnn::expr::Expression
MLPHiddenLayer::build_graph(const cnn::expr::Expression &input_expr)
{
    cnn::expr::Expression tmp_expr = tmp_expr = input_expr;
    for( unsigned i = 0 ; i < nr_hidden_layer; ++i )
    {
        cnn::expr::Expression net_expr = affine_transform({
            b_expr_list[i],
            w_expr_list[i], tmp_expr });

    }
}

} // end namespace slnn