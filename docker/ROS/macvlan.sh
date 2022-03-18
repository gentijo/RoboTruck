docker network create -d macvlan \
  --subnet=192.168.50.0/24 \
  --ip-range=192.168.50.100/25 \
  --gateway=192.168.50.1 \
  -o parent=eth0 macnet32
