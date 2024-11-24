//
// Generated file, do not edit! Created by opp_msgtool 6.0 from Block.msg.
//

#ifndef __BLOCK_M_H
#define __BLOCK_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// opp_msgtool version check
#define MSGC_VERSION 0x0600
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgtool: 'make clean' should help.
#endif

class Block;
/**
 * Class generated from <tt>Block.msg:15</tt> by opp_msgtool.
 * <pre>
 * //
 * // This program is free software: you can redistribute it and/or modify
 * // it under the terms of the GNU Lesser General Public License as published by
 * // the Free Software Foundation, either version 3 of the License, or
 * // (at your option) any later version.
 * // 
 * // This program is distributed in the hope that it will be useful,
 * // but WITHOUT ANY WARRANTY; without even the implied warranty of
 * // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * // GNU Lesser General Public License for more details.
 * // 
 * // You should have received a copy of the GNU Lesser General Public License
 * // along with this program.  If not, see http://www.gnu.org/licenses/.
 * //
 * class Block
 * {
 *     int reputation[];
 *     int64_t timestamp;
 *     unsigned long last_hash;
 *     unsigned long hash;
 * }
 * </pre>
 */
class Block
{
  protected:
    int *reputation = nullptr;
    size_t reputation_arraysize = 0;
    int64_t timestamp = 0;
    unsigned long last_hash = 0;
    unsigned long hash = 0;

  private:
    void copy(const Block& other);

  protected:
    bool operator==(const Block&) = delete;

  public:
    Block();
    Block(const Block& other);
    virtual ~Block();
    Block& operator=(const Block& other);
    virtual void parsimPack(omnetpp::cCommBuffer *b) const;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b);

    virtual void setReputationArraySize(size_t size);
    virtual size_t getReputationArraySize() const;
    virtual int getReputation(size_t k) const;
    virtual void setReputation(size_t k, int reputation);
    virtual void insertReputation(size_t k, int reputation);
    [[deprecated]] void insertReputation(int reputation) {appendReputation(reputation);}
    virtual void appendReputation(int reputation);
    virtual void eraseReputation(size_t k);

    virtual int64_t getTimestamp() const;
    virtual void setTimestamp(int64_t timestamp);

    virtual unsigned long getLast_hash() const;
    virtual void setLast_hash(unsigned long last_hash);

    virtual unsigned long getHash() const;
    virtual void setHash(unsigned long hash);
};


namespace omnetpp {

inline any_ptr toAnyPtr(const Block *p) {if (auto obj = as_cObject(p)) return any_ptr(obj); else return any_ptr(p);}
template<> inline Block *fromAnyPtr(any_ptr ptr) { return ptr.get<Block>(); }

}  // namespace omnetpp

#endif // ifndef __BLOCK_M_H

