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

redirect() {
  #How to redirect port 80 request to port 3000 https://stackoverflow.com/questions/16573668/best-practices-when-running-node-js-with-port-80-ubuntu-linode

  # removing iptable entries
  #http://lubos.rendek.org/remove-all-iptables-prerouting-nat-rules/

  # to redirect a port to another port
  sudo iptables -t nat -A PREROUTING -i eth0 -p tcp --dport 80 -j REDIRECT --to-port 3000
  # to list all prerouting maps
  sudo iptables -t nat --line-numbers -L
  # the list of prerouting redirects look like this
  Chain PREROUTING (policy ACCEPT)
  num  target     prot opt source               destination
  1    REDIRECT   tcp  --  anywhere             anywhere             tcp dpt:http redir ports 3000

  # to remove a prerouting entry num
  iptables -t nat -D PREROUTING 1 # 1 is the num entry from the list above
}

Use the forever module to launch your Node.js with. It will make sure that it restarts if it ever crashes and it will
redirect console logs to a file.


# use forever to start npm server
[sudo] npm install forever -g
[sudo] npm install forever-monitor

# forever command -c command command-options
# for learn-indi
forever start -c "npm start" ./
# for other react ones.
forever start -c "node"  ./app.js

# to see all the running processes
forever list
# ssh to amazon aws or ec2
ssh -i ~/.ssh/kp-one.pem ubuntu@xxxxxx.compute.amazonaws.com



nginx_for_multiple_proxy() {
  http://randomdotnext.com/host-multiple-sites-on-single-ec2-instance-nginx-node/

  sudo vi /etc/nginx/sites-available/default
# make entries like this, you can make multiple entries one for each domain name
# --------------------------------------------
server {
    listen 80;
    server_name example1.com; # domain
    location / {
        proxy_pass http://localhost:3030; # port
        proxy_http_version 1.1;
        proxy_set_header Upgrade $http_upgrade;
        proxy_set_header Connection 'upgrade';
        proxy_set_header Host $host;
        proxy_cache_bypass $http_upgrade;
    }
}
# --------------------------------------------
# after that reload nginx
  sudo nginx -s reload
}
