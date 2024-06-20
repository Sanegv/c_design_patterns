#include "Decorator.h"

// "private" functions declarations

void baseNotify(char message[]);
void smsNotify(char message[]);
void emailNotify(char message[]);
void discordNotify(char message[]);
void stackNotify(NotifierInterface* self, char message[]);



// "public" functions definitions

NotifierInterface* newNotifier(enum type type){
    NotifierInterface* result;
    if ((result = malloc(sizeof(NotifierInterface))) == NULL) // allocation & safety check
        return NULL;

    //adding common variables & methods
    result->type = type;
    result->stack = NULL;
    result->addDecorator = addDecorator;
    result->send = stackNotify;
    result->NotifierPtr = malloc(sizeof(union notifierPtr));

    //adding specific variables & methods
    void* ptr;
    switch (type) { //calling the right method depending on the type
        case NOTIFIER:
            if ((ptr = malloc(sizeof(Notifier))) == NULL) // allocation & safety check
                return NULL;
            ((Notifier*)ptr)->notify = baseNotify;
            result->NotifierPtr->notifier = (Notifier*)ptr;
            break;
        case SMS:
            if ((ptr = malloc(sizeof(SmsDecorator))) == NULL) // allocation & safety check
                return NULL;
            ((Notifier*)ptr)->notify = smsNotify;
            result->NotifierPtr->sms = (SmsDecorator *)ptr;
            break;
        case EMAIL:
            if ((ptr = malloc(sizeof(EmailDecorator))) == NULL) // allocation & safety check
                return NULL;
            ((Notifier*)ptr)->notify = emailNotify;
            result->NotifierPtr->email = (EmailDecorator *)ptr;
            break;
        case DISCORD:
            if ((ptr = malloc(sizeof(DiscordDecorator))) == NULL) // allocation & safety check
                return NULL;
            ((Notifier*)ptr)->notify = discordNotify;
            result->NotifierPtr->discord = (DiscordDecorator *)ptr;
            break;
        default:
            return NULL;
    }

    return result;
}

void deleteNotifier(NotifierInterface* notifierPtr){
    if(notifierPtr == NULL)
        return;
    if(notifierPtr->stack != NULL)
        deleteNotifier(notifierPtr->stack);
    free(notifierPtr->NotifierPtr);
}

void addDecorator(NotifierInterface* self, NotifierInterface* decorator){
    if(self == NULL || self->NotifierPtr == NULL)
        return;
    if(decorator->stack != NULL) // conflict if decorator.stack isn't empty, cancel
        return;
    decorator->stack = self->stack;
    self->stack = decorator;
}



// functions definitions

void stackNotify(NotifierInterface* self, char message[]){
    if(self == NULL || self->NotifierPtr == NULL) // security checks to prevent segfaults
        return;
    void *instance = NULL;
    switch (self->type) { //calling the right method depending on the type
        case NOTIFIER:
            instance = self->NotifierPtr->notifier;
            ((Notifier*)instance)->notify(message);
            break;
        case SMS:
            instance = self->NotifierPtr->sms;
            ((SmsDecorator *)instance)->notify(message);
            break;
        case EMAIL:
            instance = self->NotifierPtr->email;
            ((EmailDecorator *)instance)->notify(message);
            break;
        case DISCORD:
            instance = self->NotifierPtr->discord;
            ((DiscordDecorator *)instance)->notify(message);
            break;
        default:
            return;
    }
    if(self->stack != NULL) // security check to prevent segfault
        stackNotify(self->stack, message); // we do the same all the way through the stack
}

void baseNotify(char message[]){
    printf("This is a standard notification:\n");
    printf("%s\n", message);
};

void smsNotify(char message[]){
    printf("This is an SMS notification:\n");
    printf("%s\n", message);
};

void emailNotify(char message[]){
    printf("This is an email notification:\n");
    printf("%s\n", message);
};

void discordNotify(char message[]){
    printf("This is a discord notification:\n");
    printf("%s\n", message);
};
