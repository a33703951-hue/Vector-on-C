/**
 * \brief Dynamic storage of data (unknown type)
 */
struct Vector;
/**
 *  \brief Creates Vector where ellement size is first argument
 *  \param ellement_size Size of one ellement
 *  \return returnes a Vector object with malloced data
 */
Vector* CreateVector(int __ellement_size);
/**
 * \brief Changes size of Vector
 * \param v Vector pointer
 * \param newsize The new size of Vector
 */
void Vector_Resize(Vector* _v,int __newsize);
/**
 * \brief Adds element to the end of Vector
 * \param v Vector pointer
 * \param ell pointer to the object
 * \note Do not worry ellement_size data from ell will be copyed
 */
void Vector_PushBack(Vector* _v,const void* __ell);
/**
 * \brief Its seems obvious
 * \param v Vector pointer
 * \return Returns how many ellements of element_size are alredy in Vector
 */
int Vector_Size(Vector* _v);
/**
 * \brief This one returns the size of memory that reserved to Vector
 * \param v You know
 * \return how many elements under the memory reserved
 */
int Vector_Capacity(Vector* _v);
/**
 * \brief Due to C is not OOP language that the alternate of operator[]
 * \param v Use your brain
 * \param index Just an index
 * \note Returns NULL in case of out-of-range access
 */
void* Vector_Get(Vector* _v,int __index);
/**
 * \brief Free memory
 * \param v Kinda obvious
 * \note After you free Vector can not be used
 */
void Vector_Free(Vector* _v);
/**
 * \brief deletes the last element of vector
 * \param v Dont ask me
 */
void Vector_PopBack(Vector* _v);

/**
 * \brief dynamic storage of text
 */
struct string;

/**
 * \brief creates a string object
 * \return a pointer to object
 */
string* CreateString();

/**
 * \brief turn string object to a const char*
 * \param obj the string object itself
 * \return the C string
 */
const char* String_cstr(string* __obj);

/**
 * \brief Frees the memory locked by string
 * \param obj string object
 */
void String_Free(string* __obj);

/**
 * \brief adds string object with const char*
 * \param obj the string object
 * \param s the C string
 */
void String_addc(string* __obj,const char* _s);

/**
 * \brief adds two string objects together
 * \param obj Dst object
 * \param other Src object
 */
void String_adds(string* obj,string* other);

/**
 * \brief Returns size of string
 * \param o object
 * \return size of o
 */
int String_size(string* o);
