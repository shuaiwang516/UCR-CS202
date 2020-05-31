#include "types.h"
#include "stat.h"
#include "user.h"
#include "thread.h"
#define DEBUG 0
struct lock_t *lock;
static int output =0;
static int numofthread;
static int passnum;
static int workpid=0;

void* worker();
int main ( int argc , char * argv [])
{
	numofthread =atoi(argv[1]);
	passnum = atoi(argv[2]);
	int i = 0 ;
	lock_init(lock);
	for(i=0;i<numofthread;i++)
	{
		thread_create(worker,(void *)i);
	}
	for(i=0;i<numofthread;i++)
	{
		wait();
        //        printf(1,"wait = %d\n",i);
	}
        //printf(1,"wait finish\n");
	exit();
#if DEBUG
	if(pid >0)
		printf(1,"parent's pid num is %d\n",getpid());
	if(pid ==0)
		printf(1,"child's pid num is %d\n",getpid());
#endif


#if DEBUD
	printf(1,"lock_test = %d\n",lock->locked);
#endif 

}
void* worker(void *arg)
{
	int pidnum = (int)arg;
#if DEBUG
	printf(1,"child's pid num is %d\n",pidnum);
#endif
	while(output<passnum)
	{
		lock_acquire(lock);
		if(output==passnum)
			break;
		if(pidnum==workpid)
		{
			output++;
			printf(1,"pass number no:%d is thread %d is passing the token to ",output,pidnum);
			workpid++;
			if(workpid ==  numofthread)// because thread num is start from 0 
				workpid = 0 ;	
			printf(1," %d\n",workpid);
			lock_release(lock);
		 	sleep(1);
		}
		else
		{
			lock_release(lock);
			sleep(1);
		}
	}
	
	//printf(1,"time to end\n");
	exit();
	
}
