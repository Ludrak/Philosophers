
#include "table.h"

uint8_t get_semlock_value(sem_t * sem_lock, void *locked_value)
{
    uint8_t value;

    sem_wait(sem_lock);
    value = *(uint8_t *)locked_value;
    sem_post(sem_lock);
    return (value);
}

void    set_semlock_value(sem_t * sem_lock, void * locked_value, uint8_t value)
{
    sem_wait(sem_lock);
    *(uint8_t *)locked_value = value;
    sem_post(sem_lock);
}
