## Netwerken en Systeembeveiliging Lab 3 - Chat Room (Server)
## NAME: Abe Wiersma
## STUDENT ID: 10433120

import socket

class Server(object):
    """ Server object """
    
    def __init__(self, port, backlog=5):
        self.clients = 0
        # Output socket list
        self.outputs = []

        # start up the server.
        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.server.bind(('',port))
        self.server.listen(backlog)

    def serve():
	"""
	Chat server entry point.
	port: The port to listen on.
	cert: public certificate (bonus task)
	key: private key (bonus task)
	"""
	pass



class ServerClient(object):
	""" Client Object"""
	def __init__(self, name, address):
		self.name = name
		self.address = address
	def get_info():
		return name + ' at ' + address


## Command line parser.
if __name__ == '__main__':
	import sys, argparse
	p = argparse.ArgumentParser()
	p.add_argument('--port', help='port to listen on', default=12345, type=int)
	p.add_argument('--cert', help='server public cert', default='')
	p.add_argument('--key', help='server private key', default='')
	args = p.parse_args(sys.argv[1:])
	serve(args.port, args.cert, args.key)

