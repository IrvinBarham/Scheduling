#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"
#include "param.h"

void spin(){
	int i = 0;
	int j = 0;
	int k = 0;
	for(i = 0; i < 50; ++i){
		for(j = 0; j < 400000; ++j){
			k = j % 10;
			k = k + 1;
		}
    }
}

int main(int argc, char *argv[]){
	int pids[3];
	int tickets[3] = {20,30,10};
	struct pstat p;
	pids[0]=getpid();
	settickets(tickets[0]);

	int i;
	for(i=1;i<3;i++){
  		pids[i]=fork();
  		if(pids[i]==0){
			for(;;)
				spin();
    	}else{
			settickets(tickets[i]);
		}
	}
	int time=0;
	int ticks[3]={0,0,0};

	while(time<1000){
		if(getpinfo(&p)!=0)
			printf(1,"check failed: getpinfo\n");
		int j;
		int pid;
		for(i=0;i<3;i++){
			pid=pids[i];
			for(j=0;j<NPROC;j++){
				if(p.pid[j]==pid && pid > 0){
					ticks[i]=p.ticks[j];
					if(time == 0){printf(1,"PID: %d has %d tickets and %d ticks\n",p.pid[j],p.tickets[j],p.ticks[j]);}
				}
			}
		}
		for(i=0;i<3;i++){
			printf(1,"%d ",ticks[i]);
		}
		printf(1,"\n");

		spin();
		time++;
  	}

	for (i = 0; pids[i] > 0; i++){
    		kill(pids[i]);
  	}
	while(wait() > -1);
	exit();
	return 0;
}
