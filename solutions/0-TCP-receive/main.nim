import std/net
let socket = newSocket()
socket.bindAddr(Port(6924))
socket.listen

while true:
    var client: Socket
    var address = ""

    socket.acceptAddr(client, address)
    echo "Client connected from:", address
    var buffer = ""
    try:
      buffer = client.recvLine()
      #buffer = client.recv(1024)
    except OSError:
      echo "Error receiving data from client"

    echo "Received: ", buffer
