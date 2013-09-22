## Netwerken en Systeembeveiliging Lab 3 - Chat Room (Server)
## NAME: Abe Wiersma
## STUDENT ID: 10433120

import socket
import select
import re

class Server(object):
    """ Server object """
    
    def __init__(self, port, cert, key):
        """
        Chat server entry point.
        port: The port to listen on.
        cert: public certificate (bonus task)
        key: private key (bonus task)
        """
        self.cert = cert
        self.key =  key

        self.clients = {}
        self.outputs = []

        HOST = ''
        PORT = port
        # start up the server.
        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.server.bind((HOST,PORT))
        self.server.listen(5)

        self.commands = ['nick', 'say', 'list', 'whisper']

    def serve(self):
        inputs = [self.server, sys.stdin]
        while True:

            try:
                ready_to_read, ready_to_write, in_error = select.select(inputs, self.outputs, [], 0.3)
            except select.error, e:
                print('select error')
                break
            except socket.error, e:
                print('socket error')
                break

            for ready_socket in ready_to_read:
                # set up connection
                if ready_socket == self.server:
                    conn, addr = self.server.accept()
                    print 'Server: connection %d from %s' % (conn.fileno(), addr)
                    self.clients[conn] = ServerClient(conn, addr)
                    self.outputs.append(conn)
                    inputs.append(conn)
                    for socketobj, clientobj in self.clients.iteritems():
                        clientobj.send_message('Server: connection from %s' % (str(addr)))

                # maintain connection
                else:
                    data = ''
                    try:
                        data = ready_socket.recv(1024)
                    except socket.error, e:
                        # remove client
                        ready_socket.close()
                        inputs.remove(ready_socket)
                        self.outputs.remove(ready_socket)
                        del self.clients[ready_socket]

                    # send data
                    if data:
                        data_regex = re.search('^/', data)
                        if data_regex:
                            data_regex = re.search('^/(.*)', data)
                            if not data_regex:
                                self.clients[ready_socket].send_message('Command not recognised')
                                break
                            command = data_regex.group(1)
                            rest = command.split()[1]
                            command = command.split()[0]

                            if not command in self.commands:
                                print(command)
                                self.clients[ready_socket].send_message('Command not recognised')
                                break

                            data_regex = re.search('^/.* (.*)', data)
                            command_data = ''
                            if data_regex:
                                command_data = data_regex.group(1)

                            # test commands
                            if command == 'nick':
                                self.clients[ready_socket].set_name(command_data)
                            elif command == 'say':
                                info = self.clients[ready_socket].get_info()
                                for socketobj, clientobj in self.clients.iteritems():
                                    clientobj.send_message(info + ': ' + command_data)
                            elif command == 'list':
                                client_list = []
                                for socketobj, clientobj in self.clients.iteritems():
                                    client_list.append(clientobj.get_info())
                                ready_socket.send(str(client_list))
                            elif command == 'whisper':
                                receiver = ''
                                message = ''
                                try:
                                    receiver = rest
                                    message = command_data
                                except IndexError:
                                    self.clients[ready_socket].send_message('Command not recognised')
                                    break

                                info = self.clients[ready_socket].get_info()
                                for socketobj, clientobj in self.clients.iteritems():
                                    if clientobj.get_name() == receiver:
                                        clientobj.send_message(info + ': ' + message)
                            else:
                                self.clients[ready_socket].send_message('Command not recognised')

                        else:
                            self.clients[ready_socket].send_message('No command sent')
                    else:
                        print('chatserver: %d hung up' % ready_socket.fileno())
                        # remove client
                        ready_socket.close()
                        inputs.remove(ready_socket)
                        self.outputs.remove(ready_socket)
                        del self.clients[ready_socket]

                        # Send client leaving information to others
                        for socketobj, clientobj in self.clients.iteritems():
                            clientobj.send_message('Server: disconnect by %s' % (clientobj.get_info()))


class ServerClient(object):
    """ Client Object"""
    def __init__(self, conn, address, name='NoName'):
        self.conn = conn
        self.address = address
        self.name = name
    def get_info(self):
        return self.name + ' at ' + str(self.address)
    def get_name(self):
        return self.name
    def set_name(self, name):
        self.name = name
    def send_message(self, message):
        self.conn.send(message)
    def receive_message(self):
        return self.conn.recv(1024)


## Command line parser.
if __name__ == '__main__':
    import sys, argparse
    p = argparse.ArgumentParser()
    p.add_argument('--port', help='port to listen on', default=12345, type=int)
    p.add_argument('--cert', help='server public cert', default='')
    p.add_argument('--key', help='server private key', default='')
    args = p.parse_args(sys.argv[1:])
    Server(args.port, args.cert, args.key).serve()