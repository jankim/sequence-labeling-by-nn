#ifndef HYPER_LAYERS_H_INCLUDED_
#define HYPER_LAYERS_H_INCLUDED_

#include "hyper_input_layers.h"
#include "hyper_output_layers.h"

/* original hyper_layers.h content now has split to hyper_input_layers.h and hyper_output_layers.h */

/* following is the new layer , which is dependent from input or output layer*/
namespace slnn{

struct Index2ExprLayer
{
    Index2ExprLayer(cnn::Model *m, unsigned vocab_size, unsigned embedding_dim);
    void new_graph(cnn::ComputationGraph &cg);
    void index_seq2expr_seq(const IndexSeq &indexSeq, std::vector<cnn::expr::Expression> &exprs);
    cnn::expr::Expression index2expr(Index index);
    cnn::LookupParameters* get_lookup_param(){ return lookup_param; }
protected:
    cnn::LookupParameters *lookup_param;
    cnn::ComputationGraph *pcg;
};

struct ShiftedIndex2ExprLayer : public Index2ExprLayer
{
    // Shift Index2Expr Layer 
    // for pre-tag , we'need an expr of [SOS] Tag1 Tag2 ... Tag[N-1] ,
    // so we build an more flexible shift layer , such that we can build any shift position and direction 
    using ShiftDirection = int;
    static constexpr ShiftDirection LeftShift = -1;
    static constexpr ShiftDirection RightShift = 1;
    ShiftedIndex2ExprLayer(cnn::Model *m, unsigned vocab_size, unsigned embedding_dim, ShiftDirection direction=RightShift,
        unsigned shift_distance=1);
    void index_seq2expr_seq(const IndexSeq &indexSeq, std::vector<cnn::expr::Expression> &exprs);
    cnn::expr::Expression get_padding_expr(unsigned padding_position = 0);
private:
    ShiftDirection shift_direction;
    unsigned shift_distance;
    std::vector<cnn::Parameters *> padding_parameters;
};


struct StaticConcatenateLayer
{
    static void concatenate_exprs(const std::vector<std::vector<cnn::expr::Expression> *> &multi_exprs, std::vector<cnn::expr::Expression> &exprs);
    static cnn::expr::Expression concatenate_exprs(const std::vector<cnn::expr::Expression> &to_be_concated_exprs);
};


/* Inline Function Implementation */

inline 
void Index2ExprLayer::new_graph(cnn::ComputationGraph &cg)
{
    pcg = &cg;
}

inline
void Index2ExprLayer::index_seq2expr_seq(const IndexSeq &indexSeq, std::vector<cnn::expr::Expression> &exprs)
{
    using std::swap;
    size_t sz = indexSeq.size();
    std::vector<cnn::expr::Expression> tmp_exprs(sz);
    for( size_t i = 0; i < sz; ++i )
    {
        tmp_exprs[i] = cnn::expr::lookup(*pcg, lookup_param, indexSeq[i]);
    }
    swap(exprs, tmp_exprs);
}

inline
cnn::expr::Expression Index2ExprLayer::index2expr(Index index)
{
    return cnn::expr::lookup(*pcg, lookup_param, index);
}

inline
cnn::expr::Expression ShiftedIndex2ExprLayer::get_padding_expr(unsigned padding_position)
{
    assert(padding_position < shift_distance);
    return cnn::expr::parameter(*pcg, padding_parameters[padding_position]);
}


inline
cnn::expr::Expression StaticConcatenateLayer::concatenate_exprs(const std::vector<cnn::expr::Expression> &to_be_concated_exprs)
{
    return cnn::expr::concatenate(to_be_concated_exprs);
}

inline
void StaticConcatenateLayer::concatenate_exprs(const std::vector<std::vector<cnn::expr::Expression> *> &multi_exprs,
    std::vector<cnn::expr::Expression> &exprs)
{
    using std::swap;
    size_t nr_expr_variety = multi_exprs.size();
    // assert(nr_expr_variety > 0)
    size_t len = multi_exprs.back()->size();
    std::vector<cnn::expr::Expression> tmp_exprs(len);
    std::vector<cnn::expr::Expression> concatenate_exprs(nr_expr_variety);
    for( size_t i = 0; i < len; ++i )
    {
        for( size_t j = 0; j < nr_expr_variety; ++j )
        {
            concatenate_exprs[j] = multi_exprs[j]->at(i);
        }
        tmp_exprs[i] = cnn::expr::concatenate(concatenate_exprs);
    }
    swap(exprs, tmp_exprs);
}

} // end of namespace slnn


#endif
