//
//  Macros.hpp
//  SevenMonkeys
//

#ifndef Macros_hpp
#define Macros_hpp

#define NS_SM_BEGIN namespace sevenmonkeys {
#define NS_SM_END   }
#define USING_NS_SM using namespace sevenmonkeys

// getter and setter for boolean fields will be is + functionName and set + functionName
#define CC_SYNTHESIZE_BOOL(varName, functionName) \
    protected: bool varName; \
    public: virtual bool is##functionName(void) const { return varName; } \
    public: virtual void set##functionName(const bool var) { varName = var; }

#define CREATE_FUNC_1(__TYPE__, __PARAMETER_TYPE__) \
static __TYPE__* create(__PARAMETER_TYPE__ parameter_type) \
{ \
    __TYPE__ *pRet = new(std::nothrow) __TYPE__(); \
    if (pRet && pRet->init(parameter_type)) \
    { \
        pRet->autorelease(); \
        return pRet; \
    } \
    else \
    { \
        delete pRet; \
        pRet = nullptr; \
        return nullptr; \
    } \
}

#endif /* Macros_hpp */
