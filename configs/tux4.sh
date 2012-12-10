clear
echo "#########################################"
echo "####          EXPERIENCIA 1          ####"
echo "#########################################"
echo
ifconfig eth0 172.16.30.254/24
echo "Configurado o tux 4 com o ip 172.16.30.254"
read -p "Pressione 'Enter' para pingar tux1..."
echo
ping -c 4 172.16.30.1
read -p "Pressione 'Enter' para continuar..."
echo
route -n
echo
arp -a
read -p "Pressione 'Enter' para comecar a proxima experiencia..."
clear
echo "#########################################"
echo "####          EXPERIENCIA 2          ####"
echo "#########################################"
echo
read -p "Configurar a vlan 30 e 31 para continuar ..."
wireshark&
read -p "Pressione 'Enter' para comecar a proxima experiencia..."
clear
echo "#########################################"
echo "####          EXPERIENCIA 3          ####"
echo "#########################################"
echo
ifconfig eth2 172.16.31.253/24
read -p "Configurar a nova porta na vlan 31 ..."
read -p "Pressione 'Enter' para pingar tux2..."
echo
ping -c 4 172.16.31.1
echo
read -p "Pressione 'Enter' para activar o 'IP forwarding' e desactivar o 'ICMP echo-ignore-broadcast'..."
echo 1 > /proc/sys/net/ipv4/ip_forward
echo 0 > /proc/sys/net/ipv4/icmp_echo_ignore_broadcasts
echo
route -n
echo
wireshark&
read -p "Pressione 'Enter' para apagar as tabelas ARP dos tuxs..."
arp -d 172.16.30.1
arp -d 172.16.31.253
arp -d 172.16.31.1
read -p "Pressione 'Enter' para comecar a proxima experiencia..."
clear
echo "#########################################"
echo "####          EXPERIENCIA 4          ####"
echo "#########################################"
echo
route add default gw 172.16.31.254
route -n
echo
read -p "Pressione 'Enter' para comecar a proxima experiencia..."
clear
echo "#########################################"
echo "####          EXPERIENCIA 5          ####"
echo "#########################################"
echo
read -p "Pressione enter para adicionar o servidor DNS 'lixa.netlab.fe.up.pt' ao tux 4"
echo "search lixa.netlab.fe.up.pt \n nameserver 192.168.109.2" > /etc/resolv.coonf
read -p "Pressione 'Enter' para pingar o Google..."
ping -c 4 google.com

