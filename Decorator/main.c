#include "Decorator.h"

int main() {
    NotifierInterface* n = newNotifier(NOTIFIER);
    n->addDecorator(n, newNotifier(SMS));
    n->send(n, "test");
    deleteNotifier(n);
    return 0;
}
