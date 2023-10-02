import websocket

ws = websocket.WebSocket()
ws.connect("ws://192.168.0.135")
print("Connected to WebSocket server")

while(True):
    str = input("Say something: ")
    if str=="exit":
        break
    ws.send(str)
    result = ws.recv()
    print("Received: " + result)

ws.close()