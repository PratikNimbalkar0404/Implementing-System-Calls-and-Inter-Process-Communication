#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"



extern int trace;
extern int sysc_count[28];
extern char sysc_name[28][20];
extern int alternate[28];
extern void send_msg();
extern void rcv_msg();
extern void send_msg_multi();


int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}


int
sys_toggle(void)
{
  if(trace==0) {
    for(int i=0; i<=27 ; i++)
    	sysc_count[i] = 0;
    trace = 1;
    }
  else{
    trace = 0;
   }
  return trace;
}





int
sys_print_count(void)
{ 
	for(int j=0; j<=27; j++)
  	{	
    		if( sysc_count[alternate[j]-1] != 0 && (alternate[j]!=23)&&(alternate[j]!=22))
     			cprintf("sys_%s %d\n", sysc_name[alternate[j]-1], sysc_count[alternate[j]-1]);
  	}
  
  
  return 0;
}

int
sys_add(void)
{
    int p,q;
    argint(0,&p);
    argint(1,&q);
    return p+q;
}

int 
sys_ps(void)
{
	return ps();

}




int
sys_send(void)
{
  int sender_pid, receiver_pid; 
  char *msg;

  if((argint(0, &sender_pid) < 0)||(argint(1, &receiver_pid) < 0)||(argstr(2, &msg) < 0)){
    return -1;
    }
  send_msg(sender_pid,receiver_pid, msg);
  
 
return 0;
}

int 
sys_recv(void)       
{  
  char *msg;
 
  if(argstr(0, &msg) < 0){
    return -1;
}  

  rcv_msg(msg);
  return 0;

}




int
sys_send_multi(void)
{

  int sender_pid;
  int *rec_pids;
  char *msg;
 
  argint(0, &sender_pid);
  argptr(2, &msg, 8);
  void* rec_multi;
  argptr(1, &rec_multi, 8);
  rec_pids = (int*) rec_multi;
  

  send_msg_multi(sender_pid, rec_pids,msg);
  return 0;
}
    
    
    
     
    
