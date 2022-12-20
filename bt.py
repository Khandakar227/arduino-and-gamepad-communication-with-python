import bluetooth

bt_addr = "MAC_ADDRESS_OF_YOUR_BT_MODULE"
port = 1
# Create a bluetooth socket
socket = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
# connect to your module on a specified port
socket.connect((bt_addr, port))
