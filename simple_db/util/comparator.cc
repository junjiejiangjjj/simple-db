#include "slice.h"
#include "comparator.h"
#include "no_destructor.h"

BEGIN_SIMPLE_DB_NS(util)

//匿名空间，外部无法使用
namespace {

class BytewiseComparatorImpl : public Comparator {
public:
    BytewiseComparatorImpl() = default;

    const char* Name() const override { return "simpledb.BytewiseComparator"; }

    int Compare(const Slice& l, const Slice& r) const override {
        return l.Compare(r);
    }

    // TODO: 后续用到后实现
    void FindShortestSeparator(std::string* start, const Slice& limit) const override {
    }

    // TODO: 后续用到后实现
    void FindShortestSuccessor(std::string* key) const override {
    }

};

} // end namespace

const Comparator* BytewiseComparator() {
    static NoDestructor<BytewiseComparatorImpl> singleton;
    return singleton.get();
}


END_SIMPLE_DB_NS(util)

