/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * Institution: Technische Universität München
 * Department: Realtime Computer Systems (RCS)
 * 
 * Module: MavLink Data Buffer
 * Authors: Emanuel Regnath (emanuel.regnath@tum.de)
 * Description: general purpose circular static array buffer
 * 
 * @encoded: UTF-8, tabwidth = 4, newline = LF
 ** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
 
#ifndef CIRCULARARRAYBUFFER_H_
#define CIRCULARARRAYBUFFER_H_
 
/* Internals:
 * head points to first element, tail to the field before last element
 * head gets incremented by push_front
 * tail gets decremented by push_back
 *
 *   0   1   2   3   4   5
 * | - | - | A | B | C | - |
 *       ^t          ^h
 */


// provide your own assert or include <assert.h>
#define assert(condition) ((void)0)


/** General Type CircularBuffer
 */
template <typename T> class CircularArrayBuffer{

private:
    const int MAX_ELEMENTS = 10;  ///< MAX_ELEMENTS in number of elements
    int head = MAX_ELEMENTS - 1;  ///< the head field of the buffer
    int tail = MAX_ELEMENTS - 1;  ///< the tail field of the buffer
    bool hasElements = false;


    /** calculate position +1
    * @param position the current field
    * @return new position
    */
    int calcNextPosition(int position){
            if(position < MAX_ELEMENTS-1){
                    position++;
            } else {
                    position = 0;
            }
            return position;
    }

    /** calculate position -1
    * @param position the current field
    * @return new position
    */
    int calcPrevPosition(int position){
            if(position > 0){
                    position--;
            } else {
                    position = MAX_ELEMENTS-1;
            }
            return position;
    }

    /** caclulate modulo position
    * @param position the current field
    * @param deltaPosition number of fields to add or substract
    * @return new position
    */
    int calcWarp(int position, int deltaPosition){
            position = (position + deltaPosition) % MAX_ELEMENTS;
            if(position < 0){
                    position += MAX_ELEMENTS;
            }
            return position;
    }

public:
    T Buffer[MAX_ELEMENTS];

    /** constructor
    */
    CircularArrayBuffer(){

    }

    bool empty(){
        return !hasElements;
    }

    bool full(){
        return ( hasElements && (head == tail) );
    }

    /** get the actual number of elements
    * @return number of elements
    */
    int size(){
        if ( full() ){
            return MAX_ELEMENTS;
        } else {
            return calcWarp(head, -tail);
        }
    }

    /** add a new element to the buffer
    * @param element the new element
    */
    void push_front(T element){
        if( full() ){ // overflow
           tail = calcNextPosition(tail);
        }
        head = calcNextPosition(head);
        Buffer[ head ] = element;
        hasElements = true;
    }

    /** add a new element to the buffer
    * @param element the new element
    */
    void push_back(T element){
        Buffer[ tail ] = element;
        if ( full() ){
            head = calcPrevPosition(head);
        }
        tail = calcPrevPosition(tail);
        hasElements = true;
    }


    /** reads and removes e
    * @param position which element, 0 is latest element
    */
    T pop_front(){
        assert(hasElements);
        int elementPosition = 0;
        elementPosition = head;
        head = calcPrevPosition(head);
        if (head == tail){
            hasElements = false;
        }
        return Buffer[ elementPosition ];
    }

    T pop_back(){
        assert(hasElements);
        tail = calcNextPosition(tail);
        if (head == tail){
            hasElements = false;
        }
        return Buffer[ tail ];
    }


    T back(){
        assert(hasElements);
        return Buffer[ calcNextPosition(tail) ];
    }

    T front(){
        assert(hasElements);
        return Buffer[ head ];
    }

    /** reads element without removing
    * @param position which element, 0 is latest element
    */
    T at(unsigned int previousPosition){
            previousPosition = calcWarp(head, -previousPosition);
            return Buffer[ previousPosition ];
    }

};

#endif //CIRCULARARRAYBUFFER_H_
