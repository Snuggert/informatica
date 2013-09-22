## Netwerken en Systeembeveiliging Lab 3 - Chat Room (Client)
## NAME:
## STUDENT ID:
from gui import MainWindow
import time
import socket
import select

def loop(host, port, cert):
    """
    GUI loop.
    port: port to connect to.
    cert: public certificate (bonus task)
    """
    sock = None
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.connect((host, port))

    except socket.error, e:
        print 'Could not connect to server @%d' % port
        sys.exit(1) 


    # The following code explains how to use the GUI.
    w = MainWindow()
    # update() returns false when the user quits or presses escape.
    while w.update():
        line = w.getline()
        if line:
            sock.send(line)    

        inputready, outputready, exceptrdy = select.select([sock], [],[], 0.3)
        for i in inputready:
            if i == sock:
                data = sock.recv(1024)
                if not data:
                    print 'Shutting down.'
                    w.quit()
                else:
                    w.writeln(data)
            

## Command line parser.
if __name__ == '__main__':
    import sys, argparse
    p = argparse.ArgumentParser()
    p.add_argument('--host', help='server ip port', default='127.0.0.1')
    p.add_argument('--port', help='port to connect to', default=12345, type=int)
    p.add_argument('--cert', help='server public cert', default='')
    args = p.parse_args(sys.argv[1:])
    loop(args.host, args.port, args.cert)