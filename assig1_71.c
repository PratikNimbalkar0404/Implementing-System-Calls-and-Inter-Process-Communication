#include "types.h"
#include "stat.h"
#include "user.h"

#define MSGSIZE 8

int main(int argc, char const *argv[]) {
  int pid;
  int processes = 5;  // 1 parent, 4 child
  int thread_ids[8] = {-1};  // -1 means illegal pid
  int parent = getpid();
  int tid = 0;

  for (int i = 1; i < processes; i++) {
    tid = i;
    pid = fork();
    if (pid == 0) {
      // child process
      break;
    } else {
      thread_ids[i - 1] = pid;
      tid = 0;
    }
  }
  if (pid == 0) {
    // child process (receive)
    char *msg = (char *)malloc(MSGSIZE);
    int stat = -1;
    while(stat == -1){
      stat = recv(msg);
    }
    printf(1,"CHILD: message received is %s %d \n", msg, tid);
    exit();
  } else {
    // parent process (send)
    char *msg_child = (char *)malloc(MSGSIZE);
    msg_child = "@";
    printf(1,"PARENT: message sent is %s %d \n", msg_child, tid);
    send_multi(parent, thread_ids, msg_child);
    free(msg_child);
  }

  for (int i = 1; i < processes; i++) {
	wait();
  }
  exit();
  return 0;
}

/*
#include "types.h"
#include "stat.h"
#include "user.h"

#define MSGSIZE 8

int main(void)
{
	toggle(); 
	printf(1,"%s\n","IPC Test case");
	// char *msg = (char *)malloc(20);
	// int myid;
	// int from;	
	
int cid = fork();
	if(cid==0){
		// This is child
		char *msg = (char *)malloc(MSGSIZE);
		char *msg1 = (char *)malloc(MSGSIZE);
		char *msg2 = (char *)malloc(MSGSIZE);
		int stat=-1;
		int stat1=-1;
		int stat2=-1;
		while(stat==-1){
			stat = recv(msg);
		}
		while(stat1==-1){
			stat1 = recv(msg1);
		}
		while(stat2==-1){
			stat2 = recv(msg2);
		}
		printf(1,"2 CHILD: msg recv is: %s \n", msg );
		printf(1,"2 CHILD: msg recv is: %s \n", msg1 );
		printf(1,"2 CHILD: msg recv is: %s \n", msg2 );
		exit();
	}else{
		// This is parent
		char *msg_child = (char *)malloc(MSGSIZE);
		char *msg_child1 = (char *)malloc(MSGSIZE);
		char *msg_child2 = (char *)malloc(MSGSIZE);
		msg_child = "P";
		printf(1,"1 PARENT: msg sent is: %s \n", msg_child );
		msg_child1 = "Q";
		printf(1,"1 PARENT: msg sent is: %s \n", msg_child1 );
		msg_child2 = "R";
		printf(1,"1 PARENT: msg sent is: %s \n", msg_child2 );
		send(getpid(),cid,msg_child);	
		sleep(200);
		send(getpid(),cid,msg_child);
		sleep(200);
		send(getpid(),cid,msg_child);
		
		
		free(msg_child);
	}
	wait();
	
	exit();
}



#include "types.h"
#include "stat.h"
#include "user.h"

#define MSGSIZE 8

int main(void)
{
	toggle(); 
	printf(1,"%s\n","IPC Test case");
	// char *msg = (char *)malloc(20);
	// int myid;
	// int from;	
	
int cid = fork();
	if(cid==0){
		// This is child
		char *msg = (char *)malloc(MSGSIZE);
		char *msg1 = (char *)malloc(MSGSIZE);
		char *msg2 = (char *)malloc(MSGSIZE);
		int stat=-1;
		int stat1=-1;
		int stat2=-1;
		while(stat==-1){
			stat = recv(msg);
		}
		while(stat1==-1){
			stat1 = recv(msg1);
		}
		while(stat2==-1){
			stat2 = recv(msg2);
		}
		printf(1,"2 CHILD: msg recv is: %s \n", msg );
		printf(1,"2 CHILD: msg recv is: %s \n", msg1 );
		printf(1,"2 CHILD: msg recv is: %s \n", msg2 );
		exit();
	}else{
		// This is parent
		char *msg_child = (char *)malloc(MSGSIZE);
		char *msg_child1 = (char *)malloc(MSGSIZE);
		char *msg_child2 = (char *)malloc(MSGSIZE);
		msg_child = "P";
		printf(1,"1 PARENT: msg sent is: %s \n", msg_child );
		msg_child1 = "Q";
		printf(1,"1 PARENT: msg sent is: %s \n", msg_child1 );
		msg_child2 = "R";
		printf(1,"1 PARENT: msg sent is: %s \n", msg_child2 );
		send(getpid(),cid,msg_child);	
		sleep(200);
		send(getpid(),cid,msg_child1);	
		sleep(200);
		send(getpid(),cid,msg_child2);	
		
		free(msg_child);
	}
	wait();
	
	exit();
}
*/


