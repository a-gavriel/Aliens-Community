extern void Lthread_q_init(mythread_private_t *node);
extern void Lthread_q_add(mythread_private_t *node);
extern void Lthread_q_delete(mythread_private_t *node);
extern void Lthread_q_state_display();
extern mythread_private_t *Lthread_q_search(unsigned long);
extern void Lthread_q_lock(unsigned long new_tid);
extern void Lthread_q_unlock(unsigned long new_tid);
extern void Lthread_q_lock_all();
