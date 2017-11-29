#https://www.quora.com/How-do-I-route-my-GoDaddy-domain-name-to-my-Amazon-EC2-web-server
#https://www.youtube.com/watch?v=Gy-Cmjat-Ec

#curl -sL https://deb.nodesource.com/setup_8.x | sudo -E bash -
apt-get update
curl -sL https://deb.nodesource.com/setup_9.x | sudo -E bash -
sudo apt-get install -y nodejs
sudo apt-get install -y build-essential

#ssh -i ~/.ssh/kp-one.pem ubuntu@ec2-54-213-1-2.us-west-2.compute.amazonaws.com
# who is using port 80
#netstat -tulpn | grep --color :80

#How to redirect port 80 request to port 3000 https://stackoverflow.com/questions/16573668/best-practices-when-running-node-js-with-port-80-ubuntu-linode

sudo iptables -t nat -A PREROUTING -i eth0 -p tcp --dport 80 -j REDIRECT --to-port 3000
Use the forever module to launch your Node.js with. It will make sure that it restarts if it ever crashes and it will
redirect console logs to a file.


# use forever to start npm server
[sudo] npm install forever -g
[sudo] npm install forever-monitor

forever start -c "npm start" ./
