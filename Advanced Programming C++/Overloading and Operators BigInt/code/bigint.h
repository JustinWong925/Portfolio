// $Id: bigint.h,v 1.1 2014-07-18 02:03:07-07 - - $

#ifndef __BIGINT_H__
#define __BIGINT_H__

#include <exception>
#include <iostream>
#include <utility>
using namespace std;

#include "debug.h"

//
// Define class bigint
//
class bigint {
      friend ostream& operator<< (ostream&, const bigint&);
   private:
      //long long_value {};
      typedef unsigned char digit_t;
      typedef vector<digit_t> bigvalue_t;
      bool negative;
      bigvalue_t big_value;
      typedef pair<bigint,bigint> quotient_remainder;
      quotient_remainder divide (const bigint&) const;

      bigvalue_t do_bigadd (const bigvalue_t& left, 
                            const bigvalue_t& right) const; 
      bigvalue_t do_bigsub (const bigvalue_t& left, 
                            const bigvalue_t& right) const; 
      bigvalue_t do_bigmul (const bigvalue_t& left, 
                            const bigvalue_t& right) const;     
      bool do_bigless      (const bigvalue_t& left, 
                            const bigvalue_t& right) const; 
      bigvalue_t clear_zeros(bigvalue_t bignum) const;
      bigvalue_t mul_by_2 (bigvalue_t& big_value) const;
      bigvalue_t div_by_2 (bigvalue_t& big_value) const;

   public:
bigint zero_clear(bigint big) const;
      bigvalue_t get_value() { return big_value; }
      void set_value(bigvalue_t val) { big_value = val; }
      //
      // Override implicit members.
      //
      bigint();
      bigint (const bigint&);
      bigint& operator= (const bigint&);
      ~bigint();
      //
      // Extra ctors to make bigints.
      //
      bigint (const long);
      bigint (const string&);
      //
      // Basic add/sub operators.
      //
      bigint operator+ (const bigint&) const;
      bigint operator- (const bigint&) const;
      bigint operator-() const;
      long to_long() const;
      //
      // Extended operators implemented with add/sub.
      //
      bigint operator* (const bigint&) const;
      bigint operator/ (const bigint&) const;
      bigint operator% (const bigint&) const;
      //
      // Comparison operators.
      //
      bool operator== (const bigint&) const;
      bool operator<  (const bigint&) const;
      //
      // Mutators (added)
      //
      void set_sign(bool neg) { this->negative = neg;}
};

//
// The rest of the operators do not need to be friends.
// Make the comparisons inline for efficiency.
//

bigint pow (const bigint& base, const bigint& exponent);

inline bool operator!= (const bigint &left, const bigint &right) {
   return not (left == right);
}
inline bool operator>  (const bigint &left, const bigint &right) {
   return right < left;
}
inline bool operator<= (const bigint &left, const bigint &right) {
   return not (right < left);
}
inline bool operator>= (const bigint &left, const bigint &right) {
   return not (left < right);
}

#endif

