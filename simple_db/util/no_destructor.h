/*
  leveldb中NoDestructor实现
 */
#ifndef SIMPLE_DB_NO_DESTRUCTOR_H
#define SIMPLE_DB_NO_DESTRUCTOR_H

#include "simple_db/common/common.h" 

BEGIN_SIMPLE_DB_NS(util)

template <typename InstanceType>
class NoDestructor {
public:
    
    //构造了一个内存对齐的空间，放入InstanceType对象
    template <typename... ConstructorArgTypes>
    explicit NoDestructor(ConstructorArgTypes&&... constructor_args) {
        // 确保对齐内存的空间大于类所需要的空间
        static_assert(sizeof(instance_storage_) >= sizeof(InstanceType),
                      "instance_storage_ is not large enough to hold the instance");
        // decltype(instance_storage_)编译期间推导出instance_storage_的类型
        // 确保内存对齐后的instance_storage_类型空间 >= InstanceType内存对齐的空间
        static_assert(
                      alignof(decltype(instance_storage_)) >= alignof(InstanceType),
                      "instance_storage_ does not meet the instance's alignment requirement");
        // placement new，将InstanceType实例放到instance_storage_空间中
        new (&instance_storage_)
        InstanceType(std::forward<ConstructorArgTypes>(constructor_args)...);
    }
    
    ~NoDestructor() = default;
    
    NoDestructor(const NoDestructor&) = delete;
    NoDestructor& operator=(const NoDestructor&) = delete;
    
    //获取对象指针
    InstanceType* get() {
        return reinterpret_cast<InstanceType*>(&instance_storage_);
    }
    
private:
    //分配一块内存对齐的空间
    typename std::aligned_storage<sizeof(InstanceType),
    alignof(InstanceType)>::type instance_storage_;
};

END_SIMPLE_DB_NS(util)

#endif
