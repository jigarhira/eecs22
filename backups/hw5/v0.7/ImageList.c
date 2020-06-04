/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* ImageList.c: source file for image list manipulations             */
/*                                                                   */
/*********************************************************************/

#include <stdlib.h>
#include <assert.h>
#include "ImageList.h"

/* Create a new image entry */
IENTRY *CreateImageEntry(void)
{
	/* Allocates memory for the new Image Entry */
	IENTRY *entry = NULL;
	entry = malloc(sizeof(IENTRY));

	if (!entry)	/* Checks if memory was allocated */
	{
		return NULL;
	}

	/* Sets all pointers inside structure to NULL */
	entry->List = NULL;
	entry->Next = NULL;
	entry->Prev = NULL;
	entry->RGBImage = NULL;
	entry->YUVImage = NULL;
	
	return entry;
}

/* Delete image entry (and image objects)*/
void DeleteImageEntry(IENTRY *entry)
{
	assert(entry);  /* Check if assert exists */
	
	/* Checks for RGB Image */
	if (entry->RGBImage)
	{
		/* Delete the RGB Image */
		DeleteImage(entry->RGBImage);
	}

	/* Checks for YUV Image */
	if (entry->YUVImage)
	{
		/* Delete the YUV Image */
		DeleteYUVImage(entry->YUVImage);
	}

	assert(entry->List);

	entry->List = NULL;
	entry->Next = NULL;
	entry->Prev = NULL;
	
	free(entry);
	entry = NULL;
}

/* Create a new image list */
ILIST *CreateImageList(void)
{
	ILIST *list = NULL;
	list = malloc(sizeof(ILIST));

	if (!list)
	{
		return NULL;
	}

	list->length = 0;	/* Initial length set to 0 */
	list->First = NULL;	/* First and Last pointers are NULL */
	list->Last = NULL;

	return list;
}

/* Delete an image list (and all entries) */
void DeleteImageList(ILIST *list)
{
	assert(list);	/* Checks if list exists */

	int entries = list->length;	/* get the number of entries */
	IENTRY *current = list->First;	/* start at the first entry */
	IENTRY *next = NULL;		/* next entry */

	/* Iterates through entries */
	while (entries > 0)
	{
		assert(current);

		next = current->Next;	/* Set the next entry pointer */

		DeleteImageEntry(current);	/* delete current entry */

		current = next;	/* Move to the next entry */

		entries--;
	}

	list->First = NULL;
	list->Last = NULL;

	free(list);
	list = NULL;
}

/* Insert a RGB image to the image list at the end */
void AppendRGBImage(ILIST *list, IMAGE *RGBimage)
{
	IENTRY *last = list->Last;	/* Last image in current list */
	IENTRY *entry = CreateImageEntry();	/* Create new image entry */

	entry->List = list;	/* attach entry to the list */
	entry->Prev = last;	/* make the previous the current last entry */
	entry->RGBImage = RGBimage;	/* attach the RGB image to the image entry */
	
	/* checks if this is the first entry in the list */
	if (last != NULL)
	{
		last->Next = entry;	/* make the next the new entry */		
	}
	else
	{
		list->First = entry;
	}

	list->length++;		/* Increment the list length */
	list->Last = entry;	/* update entry as the new last */

}

/* Insert a YUV image to the image list at the end */
void AppendYUVImage(ILIST *list, YUVIMAGE *YUVimage)
{
	IENTRY *last = list->Last;	/* Last image in current list */
	IENTRY *entry = CreateImageEntry();	/* Create new image entry */

	entry->List = list;	/* attach entry to the list */
	entry->Prev = last;	/* make the previous the current last entry */
	entry->YUVImage = YUVimage;	/* attach the RGB image to the image entry */
	
	/* checks if this is the first entry in the list */
	if (last != NULL)
	{
		last->Next = entry;	/* make the next the new entry */
	}
	else
	{
		list->First = entry;
	}
	
	list->length++;	/* Increment the list length */
	list->Last = entry;	/* update entry as the new last */

}

/* Fast forward an image list */
void FastImageList(ILIST *list, unsigned int factor)
{
	unsigned int newFrameNum = 0;
	unsigned int counter = 0;
	IENTRY *curr = NULL; /* current entry in the list */
	IENTRY *prev = NULL; /* previous kept entry in the list */
	IENTRY *next = NULL; /* next entry in the list */

	assert(list);
	assert(factor > 0);

	curr = list->First;

	while (curr != NULL) {
		next = curr->Next;

		if (counter % factor == 0) {
			newFrameNum ++;

			curr->Prev = prev;
			if (prev != NULL) {
				prev->Next = curr;
			}
			prev = curr;
		} else {
			if (curr->RGBImage != NULL) {
				DeleteImage(curr->RGBImage);
			}

			if (curr->YUVImage != NULL) {
				DeleteYUVImage(curr->YUVImage);
			}

			curr->List = NULL;
			curr->Next = NULL;
			curr->Prev = NULL;
			curr->RGBImage = NULL;
			curr->YUVImage = NULL;
			free(curr);
		}

		curr = next;
		counter ++;
	}

	list->Last = prev;
	if (prev != NULL) {
		prev->Next = NULL;
	}
	list->length = newFrameNum;
}

/* Reverse an image list */
void ReverseImageList(ILIST *list)
{
	int entries = list->length;
	
	/* Current entry */
	IENTRY *current = NULL;
	IENTRY *temp = NULL;	/* temporary variable */

	
	current = list->Last;		/* start at the end of the list */

	/* Iterate through the list (except for the first and last entry) */
	while(entries > 0)	/* loops through the entries */
	{
		/* swap next and prev pointers */
		temp = current->Next;
		current->Next = current->Prev;
		current->Prev = temp;

		current = current->Next;	/* current->Prev has been swapped so the next entry is current->Next */
	
		entries--;			/* decrement the counter */
	}

	/* swap the first and last pointers */
	temp = list->First;
	list->First = list->Last;
	list->Last = temp;

}


/* EOF */
