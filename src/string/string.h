#ifndef STRING_H
#define STRING_H

#define SP_DEFAULT_SIZE 1000    //Default size for StringPool
#define SP_INCREASE_SIZE 250    //Size to increase StringPool data

#define SA_DEFAULT_SIZE 50      //Default size for StringArr
#define SA_INCREASE_SIZE 50     //Size to increase StringArr data

/*Stores all text data*/
typedef struct {
    unsigned long size;         //Size allocated in memory
    unsigned long length;       //Space used
    char* data;                 //String data
} StringPool;

/*Points to a specific place in String pool*/
typedef struct {
    unsigned long length;       //Length of a string, assigned automatically
    char* start;                //Pointer to starting char of string
    char* end;                  //Pointer to ending char of string
   StringPool* sp;              //Pointer to this string's data container StringPool
} String;

/*Stores array of strings*/
typedef struct {
    unsigned long size;         //Size allocated in memory
    unsigned long count;        //Count of elements
    String* data;               //StringArr data
} StringArr;

StringPool* stringpool_create(void); /*Creates StringPool, sets it's data to c and returns StringPool*/
void stringpool_clean(StringPool* sp); /*Frees data in StringPool* sp, and frees StringPool* sp*/
void stringpool_data_append(StringPool* sp, char* c); /*Frees StringPool* sp old data sets StringPool* sp data to c*/

String* string_create(StringPool* sp, char* start, char* end); /*Creates String and assigns it to start & end in StringPool* sp, automatically sets String length*/
void string_clean(String* s); /*Frees String* s*/
char* string_read(String* s); /*Reads and returns String* s data*/

StringArr* stringarr_create(void); /*Creates StringArr and returns it*/
void stringarr_clean(StringArr* sa); /*Frees all StringArr* sa data elements and frees itself*/
void stringarr_add(StringArr* sa, String* s); /*Adds String* s to StringArr* sa data*/

#endif
