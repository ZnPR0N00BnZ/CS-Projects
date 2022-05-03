bool somePredicate(string s);

bool allFalse(const string a[], int n) {
    {
        string ending = a[n-1];
        if (n==1 && somePredicate(ending) == false) {
            return true;
        }
        if (somePredicate(ending) == true) {
        return false;
    }
    return allFalse(a, n-1);
    }
}

// Return the number of elements in the array for which the
    // somePredicate function returns false.
  int countFalse(const string a[], int n)
  {
      int current = 0;
      string ending = a[n-1];
      if (n==1 && somePredicate(ending) == false) {
          return 1;
      }
      else if (n==1 && somePredicate(ending) == true) {
          return 0;
      }
      if (somePredicate(ending) == false) {
          current++;
      }
      current += countFalse(a, n-1);
      
      return current;
          
  }

// Return the subscript of the first element in the array for which
// the somePredicate function returns false.  If there is no such
// element, return -1.

int firstFalse(const string a[], int n)
{
    string start = a[0];
    if (n == 0) {
        return -1;
    }
    if(somePredicate(start) == false) {
        return 0;
    }
    int rest = firstFalse(a+1,n-1);
    if (rest == -1) {
        return rest;
    }
    else {
        return 1+rest;
    }
}

// Return the subscript of the least string in the array (i.e.,
// return the smallest subscript m such that a[m] <= a[k] for all
// k from 0 to n-1).  If the function is told that no strings are to
// be considered in the array, return -1.
int positionOfLeast(const string a[], int n)
{
    if (n == 0) {
        return -1;
    }
    if (n == 1) {
        return 0;
    }
    if (a[n-1] <a[positionOfLeast(a, n-1)]) {
        return n-1;
    }
    else {
        return positionOfLeast(a, n-1);
    }
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    "merida" "tiana" "raya" "belle" "tiana" "raya" "moana"
// then the function should return true if a2 is
//    "tiana" "belle" "moana"
// or
//    "tiana" "raya" "raya"
// and it should return false if a2 is
//    "tiana" "moana" "belle"
// or
//    "merida" "belle" "belle"
bool has(const string a1[], int n1, const string a2[], int n2)
{
    if (n2 == 0) {
        return true;
    }
    if (n1 == 0 && n2 >= 1) {
        return false;
    }
    
    string test = a2[n2-1];
    
    if (a1[n1-1] == test) {
        return has(a1, n1-1,a2,n2-1);
    }
    else {
        return has(a1, n1-1,a2,n2);
    }
}





