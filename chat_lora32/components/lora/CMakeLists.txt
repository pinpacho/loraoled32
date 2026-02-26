idf_component_register(
    SRCS "lora.c"
    PRIV_REQUIRES driver
    INCLUDE_DIRS "include"
)

#set(COMPONENT_ADD_INCLUDEDIRS include)
#set(COMPONENT_SRCS "lora.c")
#register_component()