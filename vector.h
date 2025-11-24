/**
 * \brief Dynamic storage of data (unknown type)
 */
struct Vector;
/**
 *  \brief Creates Vector where ellement size is first argument
 *  \param ellement_size Size of one ellement
 *  \return returnes a Vector object withh malloced data
 */
Vector* CreateVector(int ellement_size);
/**
 * \brief Changes size of Vector
 * \param v Vector pointer
 * \param newsize The new size of Vector
 */
void Vector_Resize(Vector* v,int newsize);
/**
 * \brief Adds element to the end of Vector
 * \param v Vector pointer
 * \param ell pointer to the object
 * \note Do not worry ellement_size data from ell will be copyed
 */
void Vector_PushBack(Vector* v,const void* ell);
/**
 * \brief Its seems obvious
 * \param v Vector pointer
 * \return Returns how many ellements of element_size are alredy in Vector
 */
int Vector_Size(Vector* v);
/**
 * \brief This one returns the size of memory that reserved to Vector
 * \param v You know
 * \return how many elements under the memory reserved
 */
int Vector_Capacity(Vector* v);
/**
 * \brief Due to C is not OOP language that the alternate of operator[]
 * \param v Use your brain
 * \param index Just an index
 * \note Returns NULL in case of out-of-range access
 */
void* Vector_Get(Vector* v,int index);
/**
 * \brief Free memory
 * \param v Kinda obvious
 * \note After you free Vector can not be used
 */
void Vector_Free(Vector *v);
/**
 * \brief deletes the last element of vector
 * \param v Dont ask me
 */

void Vector_PopBack(Vector* v);
