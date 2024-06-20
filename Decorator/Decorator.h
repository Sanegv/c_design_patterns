#ifndef DEF_PATTERN_DECORATOR
#define DEF_PATTERN_DECORATOR

#include <stdlib.h>
#include <stdio.h>

typedef struct notifierInterface NotifierInterface;

typedef struct notifier{
    void (*notify)(char[]);
} Notifier;

typedef struct smsDecorator{
    void (*notify)(char[]);
} SmsDecorator;

typedef struct emailDecorator{
    void (*notify)(char[]);
} EmailDecorator;

typedef struct discordDecorator{
    void (*notify)(char[]);
} DiscordDecorator;

struct notifierInterface {
    // ATTRIBUTES
    NotifierInterface* stack;

    enum type {
        NOTIFIER = 0,
        SMS = 1,
        EMAIL = 2,
        DISCORD = 3
    } type;

    union notifierPtr{
        Notifier* notifier;
        SmsDecorator* sms;
        EmailDecorator* email;
        DiscordDecorator* discord;
    } *NotifierPtr;

    // METHODS
    void (*addDecorator)(NotifierInterface*, NotifierInterface*);
    void (*send)(NotifierInterface*, char[]);
};

NotifierInterface* newNotifier(enum type type);
void deleteNotifier(NotifierInterface* notifierPtr);
void addDecorator(NotifierInterface* self, NotifierInterface* decorator);

#endif