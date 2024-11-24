//
// Generated file, do not edit! Created by opp_msgtool 6.0 from Block.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "Block_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

Block::Block()
{
}

Block::Block(const Block& other)
{
    copy(other);
}

Block::~Block()
{
    delete [] this->reputation;
}

Block& Block::operator=(const Block& other)
{
    if (this == &other) return *this;
    copy(other);
    return *this;
}

void Block::copy(const Block& other)
{
    delete [] this->reputation;
    this->reputation = (other.reputation_arraysize==0) ? nullptr : new int[other.reputation_arraysize];
    reputation_arraysize = other.reputation_arraysize;
    for (size_t i = 0; i < reputation_arraysize; i++) {
        this->reputation[i] = other.reputation[i];
    }
    this->timestamp = other.timestamp;
    this->last_hash = other.last_hash;
    this->hash = other.hash;
}

void Block::parsimPack(omnetpp::cCommBuffer *b) const
{
    b->pack(reputation_arraysize);
    doParsimArrayPacking(b,this->reputation,reputation_arraysize);
    doParsimPacking(b,this->timestamp);
    doParsimPacking(b,this->last_hash);
    doParsimPacking(b,this->hash);
}

void Block::parsimUnpack(omnetpp::cCommBuffer *b)
{
    delete [] this->reputation;
    b->unpack(reputation_arraysize);
    if (reputation_arraysize == 0) {
        this->reputation = nullptr;
    } else {
        this->reputation = new int[reputation_arraysize];
        doParsimArrayUnpacking(b,this->reputation,reputation_arraysize);
    }
    doParsimUnpacking(b,this->timestamp);
    doParsimUnpacking(b,this->last_hash);
    doParsimUnpacking(b,this->hash);
}

size_t Block::getReputationArraySize() const
{
    return reputation_arraysize;
}

int Block::getReputation(size_t k) const
{
    if (k >= reputation_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)reputation_arraysize, (unsigned long)k);
    return this->reputation[k];
}

void Block::setReputationArraySize(size_t newSize)
{
    int *reputation2 = (newSize==0) ? nullptr : new int[newSize];
    size_t minSize = reputation_arraysize < newSize ? reputation_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        reputation2[i] = this->reputation[i];
    for (size_t i = minSize; i < newSize; i++)
        reputation2[i] = 0;
    delete [] this->reputation;
    this->reputation = reputation2;
    reputation_arraysize = newSize;
}

void Block::setReputation(size_t k, int reputation)
{
    if (k >= reputation_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)reputation_arraysize, (unsigned long)k);
    this->reputation[k] = reputation;
}

void Block::insertReputation(size_t k, int reputation)
{
    if (k > reputation_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)reputation_arraysize, (unsigned long)k);
    size_t newSize = reputation_arraysize + 1;
    int *reputation2 = new int[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        reputation2[i] = this->reputation[i];
    reputation2[k] = reputation;
    for (i = k + 1; i < newSize; i++)
        reputation2[i] = this->reputation[i-1];
    delete [] this->reputation;
    this->reputation = reputation2;
    reputation_arraysize = newSize;
}

void Block::appendReputation(int reputation)
{
    insertReputation(reputation_arraysize, reputation);
}

void Block::eraseReputation(size_t k)
{
    if (k >= reputation_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)reputation_arraysize, (unsigned long)k);
    size_t newSize = reputation_arraysize - 1;
    int *reputation2 = (newSize == 0) ? nullptr : new int[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        reputation2[i] = this->reputation[i];
    for (i = k; i < newSize; i++)
        reputation2[i] = this->reputation[i+1];
    delete [] this->reputation;
    this->reputation = reputation2;
    reputation_arraysize = newSize;
}

int64_t Block::getTimestamp() const
{
    return this->timestamp;
}

void Block::setTimestamp(int64_t timestamp)
{
    this->timestamp = timestamp;
}

unsigned long Block::getLast_hash() const
{
    return this->last_hash;
}

void Block::setLast_hash(unsigned long last_hash)
{
    this->last_hash = last_hash;
}

unsigned long Block::getHash() const
{
    return this->hash;
}

void Block::setHash(unsigned long hash)
{
    this->hash = hash;
}

class BlockDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_reputation,
        FIELD_timestamp,
        FIELD_last_hash,
        FIELD_hash,
    };
  public:
    BlockDescriptor();
    virtual ~BlockDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(BlockDescriptor)

BlockDescriptor::BlockDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(Block)), "")
{
    propertyNames = nullptr;
}

BlockDescriptor::~BlockDescriptor()
{
    delete[] propertyNames;
}

bool BlockDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Block *>(obj)!=nullptr;
}

const char **BlockDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *BlockDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int BlockDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int BlockDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_reputation
        FD_ISEDITABLE,    // FIELD_timestamp
        FD_ISEDITABLE,    // FIELD_last_hash
        FD_ISEDITABLE,    // FIELD_hash
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *BlockDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "reputation",
        "timestamp",
        "last_hash",
        "hash",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int BlockDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "reputation") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "timestamp") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "last_hash") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "hash") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *BlockDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_reputation
        "int64_t",    // FIELD_timestamp
        "unsigned long",    // FIELD_last_hash
        "unsigned long",    // FIELD_hash
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **BlockDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *BlockDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int BlockDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Block *pp = omnetpp::fromAnyPtr<Block>(object); (void)pp;
    switch (field) {
        case FIELD_reputation: return pp->getReputationArraySize();
        default: return 0;
    }
}

void BlockDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Block *pp = omnetpp::fromAnyPtr<Block>(object); (void)pp;
    switch (field) {
        case FIELD_reputation: pp->setReputationArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Block'", field);
    }
}

const char *BlockDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Block *pp = omnetpp::fromAnyPtr<Block>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string BlockDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Block *pp = omnetpp::fromAnyPtr<Block>(object); (void)pp;
    switch (field) {
        case FIELD_reputation: return long2string(pp->getReputation(i));
        case FIELD_timestamp: return int642string(pp->getTimestamp());
        case FIELD_last_hash: return ulong2string(pp->getLast_hash());
        case FIELD_hash: return ulong2string(pp->getHash());
        default: return "";
    }
}

void BlockDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Block *pp = omnetpp::fromAnyPtr<Block>(object); (void)pp;
    switch (field) {
        case FIELD_reputation: pp->setReputation(i,string2long(value)); break;
        case FIELD_timestamp: pp->setTimestamp(string2int64(value)); break;
        case FIELD_last_hash: pp->setLast_hash(string2ulong(value)); break;
        case FIELD_hash: pp->setHash(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Block'", field);
    }
}

omnetpp::cValue BlockDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Block *pp = omnetpp::fromAnyPtr<Block>(object); (void)pp;
    switch (field) {
        case FIELD_reputation: return pp->getReputation(i);
        case FIELD_timestamp: return pp->getTimestamp();
        case FIELD_last_hash: return omnetpp::checked_int_cast<omnetpp::intval_t>(pp->getLast_hash());
        case FIELD_hash: return omnetpp::checked_int_cast<omnetpp::intval_t>(pp->getHash());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Block' as cValue -- field index out of range?", field);
    }
}

void BlockDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Block *pp = omnetpp::fromAnyPtr<Block>(object); (void)pp;
    switch (field) {
        case FIELD_reputation: pp->setReputation(i,omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_timestamp: pp->setTimestamp(omnetpp::checked_int_cast<int64_t>(value.intValue())); break;
        case FIELD_last_hash: pp->setLast_hash(omnetpp::checked_int_cast<unsigned long>(value.intValue())); break;
        case FIELD_hash: pp->setHash(omnetpp::checked_int_cast<unsigned long>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Block'", field);
    }
}

const char *BlockDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr BlockDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Block *pp = omnetpp::fromAnyPtr<Block>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void BlockDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Block *pp = omnetpp::fromAnyPtr<Block>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Block'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

