set(feature2input_exe_name
    pos_bareinput1_classification_f2i_no_merge
)

set(specific_headers
    ${feature2input_exe_name}_model.h
)
set(specific_libs
    ${feature2input_exe_name}_model.cpp
)

add_executable(${feature2input_exe_name}
               ${feature2input_exe_name}.cpp
               ${pos_feature_module_headers}
               ${single_input_with_feature_modelhandler_hpp} # model handler
               ${specific_headers} # model
               ${bareinput1_feature2input_layer_no_merge_model_hpp}        # feature to input base model 
               ${pos_common_headers}                # common header
               ${specific_libs}
               ${pos_common_libs}
               ${pos_feature_module_libs}
               ${pos_reader_module}
               )
               
target_link_libraries(${feature2input_exe_name}
                      cnn
                      ${Boost_LIBRARIES})

############# feature2output  ###########   
                      
set(feature2output_exe_name
    pos_bareinput1_classification_f2o_no_merge
)

set(specific_headers
    ${feature2output_exe_name}_model.h
)
set(specific_libs
    ${feature2output_exe_name}_model.cpp
)

add_executable(${feature2output_exe_name}
               ${feature2output_exe_name}.cpp
               ${pos_feature_module_headers}
               ${single_input_with_feature_modelhandler_hpp} # model handler
               ${specific_headers} # model
               ${bareinput1_feature2output_layer_no_merge_model_hpp}        # feature to output base model 
               ${pos_common_headers}                # common header
               ${specific_libs}
               ${pos_common_libs}
               ${pos_feature_module_libs}
               ${pos_reader_module}
               )
               
target_link_libraries(${feature2output_exe_name}
                      cnn
                      ${Boost_LIBRARIES})
                      
########### feature2output + nonlinear #######

set(feature2output_exe_name
    pos_bareinput1_f2o_nonlinear
)

set(specific_headers
    ${feature2output_exe_name}_model.h
)
set(specific_libs
    ${feature2output_exe_name}_model.cpp
)

add_executable(${feature2output_exe_name}
               ${feature2output_exe_name}.cpp
               ${pos_feature_module_headers}
               ${single_input_with_feature_modelhandler_hpp} # model handler
               ${specific_headers} # model
               ${bareinput1_feature2output_layer_nonlinear_model_hpp}        # feature to output base model 
               ${pos_common_headers}                # common header
               ${specific_libs}
               ${pos_common_libs}
               ${pos_feature_module_libs}
               ${pos_reader_module}
               )
               
target_link_libraries(${feature2output_exe_name}
                      cnn
                      ${Boost_LIBRARIES})