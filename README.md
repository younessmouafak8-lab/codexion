*This project has been created as part of the 42 curriculum by ymouafak.*
 
---
 
# Codexion
 
Coders / Threads sitting in a circle, sharing dongles, trying not to burn out. A simulation built with pthreads in C.
 
---
 
## Description
 
Each coder needs two dongles to compile. There are exactly as many dongles as coders, one between each pair. Coders cycle through compile → debug → refactor, and if one goes too long without compiling, they burn out and the simulation ends.
 
The interesting part is making sure that never happens, no deadlocks, no starvation, burnout detected within 10ms. Two scheduling modes: `fifo` and `edf`.
 
---

## Instructions
 
```bash
make
./codexion <coders> <burnout_ms> <compile_ms> <debug_ms> <refactor_ms> <compiles_required> <cooldown_ms> <fifo|edf>
```
 
Example:
```bash
./codexion 4 800 200 200 400 5 50 fifo
```
 
---
 
## Blocking cases handled
 
**Deadlock** — broken by never letting coders each grab one dongle and wait on the other. The scheduler queue controls who gets to attempt acquisition, so circular wait can't form.
 
**Starvation** — under EDF, deadlines get closer as a coder waits, so it naturally rises in priority also adding a tie breaker insures that the case of equal deadlines gets sorted. Under FIFO, arrival order is strict.
 
**Cooldown** — after releasing the dongles. Coders stay spinning while waiting for cooldown to expire and for them to have the dongles available and also them having the highest priority.
 
**Burnout detection** — a dedicated monitor thread polls every ~1ms using `gettimeofday()` and logs burnout immediately under the print mutex.
 
**Log interleaving** — every `printf()` call is wrapped in a print mutex. Nothing else holds that mutex, so contention stays minimal.
 
---
 
## Thread synchronization mechanisms
 
- **Per-dongle mutex + sleeping while waiting** — protects availability and the scheduler queue. Coders wait on the dongles to be marked available when freed.
- **Per-coder mutex** — protects `last_compile` and `compile_count`, read by the monitor concurrently.
- **Global stop flag mutex** — monitor writes it, every coder reads it at the top of their loop.
- **Custom min-heap** — one per dongle, sorted by timestamp (FIFO) or deadline (EDF). All heap operations happen inside the dongle lock.

**Race condition example — dongle logic:**
```c
//Before:
	pthread_mutex_lock(&first->lock);
	if (first->is_available
		&& ft_clock(coder->args->start_time) >= first->cooldown
		&& first->arr[0].id == coder->id)
		i = 1;
	pthread_mutex_unlock(&first->lock);
	pthread_mutex_lock(&second->lock);
	if (second->is_available
		&& ft_clock(coder->args->start_time) >= second->cooldown
		&& second->arr[0].id == coder->id && i)
		i = 1;
	else
		i = 0;
	pthread_mutex_unlock(&second->lock);
	return (i);
// After:
	pthread_mutex_lock(&first->lock);
	pthread_mutex_lock(&second->lock);
	if (check_availability(coder, first, second))
	{
		poping_coder(first, second);
		pthread_mutex_unlock(&first->lock);
		pthread_mutex_unlock(&second->lock);
		return ;
	}
	pthread_mutex_unlock(&first->lock);
	pthread_mutex_unlock(&second->lock);
```
**Thread-safe communication between coders and monitor:**
```c
// monitor sets the stop flag
pthread_mutex_lock(&args->lock_flag);
args->stop = 1;
pthread_mutex_unlock(&args->lock_flag);
 
// every coder checks it at the top of their loop
int	temp;
pthread_mutex_lock(&c->args->lock_flag);
temp = c->args->stop_it;
pthread_mutex_unlock(&c->args->lock_flag);
return (temp);
```
---
 
## Resources
 
- *What is concurrent programming?* — https://www.educative.io/answers/what-is-concurrent-programming
- *Priority queue / Heap data structure explained* — https://youtu.be/HqPJF2L5h9U?si=v9hkKGR0JIWR9bQR
- *Multithreading explained* — https://youtu.be/7ENFeb-J75k?si=eciNPFftNDsiWF9-
- POSIX man pages — `pthread_create`, `pthread_mutex_init`, `pthread_join`

**AI usage** — used Ai throughout to understand pthread internals (TCB, context switching, lifecycle of a thread), review code for norm compliance and error handling, and prepare for evaluation questions. also optimizing the structure of the Readme.
 