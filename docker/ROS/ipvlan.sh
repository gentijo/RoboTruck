docker network create -d ipvlan \
    --subnet=192.168.50.0/24 \
    --gateway=192.168.50.1 \
     -o ipvlan_mode=l2 my-ipvlan2
