include_guard()

set(FGM_COMMON_DIR "common/")
set(FGM_COMMON_HEADERS
        Config.h
        Constants.h
        MathTraits.h
        Messages.h
        OperationStatus.h
        PreprocessorDefinitions.h
        Types.h
        Utils.h
        Utils.tpp
        Wrappers.h
        Wrappers.tpp
)
list(TRANSFORM FGM_COMMON_HEADERS PREPEND ${FGM_COMMON_DIR})