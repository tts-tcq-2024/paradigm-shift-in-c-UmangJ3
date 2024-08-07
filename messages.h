#ifndef MESSAGES_H
#define MESSAGES_H

typedef struct {
    const char* english;
    const char* german;
} Message;

typedef struct {
    Message outOfRange;
    Message lowWarning;
    Message highWarning;
} Messages;

extern Messages messages[];

#endif

