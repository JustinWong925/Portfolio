// $Id: util.tcc,v 1.3 2014-06-27 17:49:07-07 - - $

#include <sstream>
#include <typeinfo>
using namespace std;

template <typename item_t>
ostream& operator<< (ostream& out, const list<item_t>& vec) {
   bool want_space = false;
   for (const auto& item: vec) {
      if (want_space) cout << " ";
      cout << item;
      want_space = true;
   }
   return out;
}

template <typename type_t>
string to_string (const type_t& that) {
   ostringstream stream;
   stream << that;
   return stream.str();
}

template <typename type_t>
type_t from_string (const string& that) {
   stringstream stream;
   stream << that;
   type_t result;
   if (not (stream >> result and stream >> std::ws and stream.eof())) {
      throw domain_error (string (typeid (type_t).name())
            + " from_string (" + that + ")");
   }
   return result;
}

