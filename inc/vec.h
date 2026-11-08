#ifndef VEC_H
#define VEC_H

#include <stddef.h>

/**
 * @brief A growable array of fixed-size elements.
 *
 * The vector owns its storage; release it with vec_free(). Fields are
 * managed by the library, so callers must not modify them directly.
 * A freshly initialized vector is empty and holds no allocation.
 * This type is not thread-safe.
 *
 * @note @c cap and @c len count elements, not bytes.
 */
typedef struct
{
	void* elems; /**< Heap block which holds the elements, NULL if none are
	                allocated. */
	size_t elem_size; /**< Size of one element in bytes. Set once by
	                     vec_init(); always > 0. */
	size_t cap;       /**< Number of elements the vector can hold. */
	size_t len; /**< Number of elements that are currently in the vector.
	               len <= cap. */
} vec;

/**
 * @brief Initializes an empty vector, nothing is allocated yet.
 *
 * @param[in,out] v          The vector
 * @param[in]     elem_size  The size of a member element.
 *
 * @retval 0                 The vector is successfully initialized.
 * @retval -1                v is NULL or elem_size is 0
 */
int vec_init(vec* v, size_t elem_size);

/**
 * @brief Copies an input element and pushes it to the end of the vector.
 *
 * @param[in,out] v          The vector
 * @param[in]     elem       The element pointer.
 *
 * @retval 0                 The element was succesfully pushed to the vector.
 * @retval -1                v or elem is NULL, allocation fails, or the size
 * calculation overflows
 */
int vec_push(vec* v, const void* elem);

/**
 * @brief Removes an element from the end of the vector and copies it in a user
 * supplied pointer.
 *
 * @param[in,out] v          The vector
 * @param[out] out           The element pointer, pointing to a element of
 * elem_size.
 *
 * @retval 0                 The element was successfully popped from the
 * vector.
 * @retval -1                v or out is NULL, or the vector is empty
 */
int vec_pop(vec* v, void* out);

/**
 * @brief Returns an element from the vector using its index.
 *
 * @param[in] v              The vector
 * @param[in] index	     Index of the element
 * @param[out] out           The element pointer, pointing to a element of
 * elem_size.
 *
 * @retval 0                 The element was found and returned.
 * @retval -1                v or out is NULL, or index >= len
 */
int vec_get(const vec* v, size_t index, void* out);

/**
 * @brief Changes an element in the vector using its index.
 *
 * @param[in,out] v          The vector
 * @param[in] 	  index	     Index of the element
 * @param[in] in  	     The element pointer, pointing to a element of
 * elem_size.
 *
 * @retval 0                 The element was found and changed.
 * @retval -1                v or in is NULL, or index >= len
 */
int vec_set(vec* v, size_t index, const void* in);

int vec_insert(vec* v, size_t index, const void* in);

int vec_remove(vec* v, size_t index);

int vec_reserve(vec* v, size_t cap);

int vec_shrink_to_fit(vec* v);

/**
 * @brief Sets the length of vector to 0, but does NOT free the memory used by
 * the vector
 *
 * @param[in,out] v          The vector
 *
 * @retval 0                 Vector length set to 0
 * @retval -1                v is NULL
 */
int vec_clear(vec* v);

/**
 * @brief Frees / De-allocates memory used by the vector
 *
 * @param[in,out] v          The vector
 *
 * @retval 0                 Vectors memory freed / de-allocated
 * @retval -1                v is NULL
 *
 * @note A double free does NOT cause unexpected behaviour.
 */
int vec_free(vec* v);

/**
 * @brief Returns the number of elements currently in the vector.
 *
 * @pre @p v is not NULL and was initialized with vec_init().
 *
 * @param[in,out] v          The vector
 *
 * @return Number of elements in use; 0 for an empty vector.
 */
size_t vec_len(const vec* v);

/**
 * @brief Returns the number of elements the vector can hold without growing.
 *
 * @pre @p v is not NULL and was initialized with vec_init().
 *
 * @param[in,out] v          The vector
 *
 * @return Current capacity in elements; always at least vec_len(v).
 */
size_t vec_cap(const vec* v);

#endif
