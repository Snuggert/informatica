# Student name: Abe Wiersma
# Student number: 10433120\
# Institute: University of Amsterdam
# Course: Networking and System security
# 
# File: assignment 1 and 2 for lab2
# Date: 9-9-2013

import socket, os, sys, argparse, signal, sys, re

# handle SIGINT for smooth exit
def signal_handler(signal, frame):
    print 'Server Closing.'
    server.close()
    sys.exit()

def serve(port, public_html, cgibin):
    signal.signal(signal.SIGINT, signal_handler)
    """
    The entry point of the HTTP server.
    port: The port to listen on.
    public_html: The directory where all static files are stored.
    cgibin: The directory where all CGI scripts are stored.
    """
    HOST = ''
    PORT = port
    global server 
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM, socket.IPPROTO_TCP)
    server.bind((HOST,PORT))
    server.listen(1)

    while 1:

        # connection to client and address to client
        conn, addr = server.accept()
        data = conn.recv(1024)
        if not data:
            continue

        # communication protocol
        response_proto = ''
        response_status = ''

        # Use regex to find the type of request and location
        request_regex = re.search('([A-Z]{3,7}) (/.*)(?= ) (.*)', data)
        if not request_regex:
            response_status = '501'
            conn.send('%s %s' % (response_proto, response_status))
            conn.send('\n')
            conn.close()
            continue

        if not request_regex.group(1):
            response_status = '501'
            conn.send('%s %s' % (response_proto, response_status))
            conn.close()
            continue

        # set request type.
        request = request_regex.group(1)
        
        if request != 'GET':
            response_status = '501'
            conn.send('%s %s' % (response_proto, response_status))
            conn.close()
            continue

        if not request_regex.group(2):
            continue

        # set location.
        location = request_regex.group(2)
        if(location == '/'):
            location = '/index.hmtl'

        # set/check response_proto
        if not request_regex.group(3):
            response_proto = request_regex.group(3)
            if response_proto != 'HTTP/1.1' or response_proto != 'CGI/1.1':
                response_status = '501'
                conn.send('%s %s' % (response_proto, response_status))
                conn.close()
                continue

        requested_type = ''
        requested_type_re = re.search('(\.[^.]*)$', location) 
        if requested_type_re != None:
            requested_type = requested_type_re.group(0)

        # logging
        print('request for : ' + location + ' by: ', addr)

        # try and retrieve file requested
        content = None
        try:
            if requested_type == '.png':
                content = open(public_html+location, 'rb')
            else:
                content = open(public_html+location, 'r')
            content = content.read()
        except IOError:
            print('File not found')

        # if server can't find requested file in public_html send 404
        if not content:
            response_status = '404'
            conn.send('%s %s' % (response_proto, response_status))
            conn.close()
            continue
        # else return requested file in html format
        else:
            

            # Set response headers for different file types
            response_headers = None
            if requested_type == '.html':
                response_status = '200'
                response_headers = {
                    'Content-Type': 'text/html; encoding=utf8',
                    'Content-Length': len(content),
                    'Connection': 'close',
                }
                pass
            else:
                response_status = '304'
                response_headers = {
                    'Content-Type': 'image/x-png',
                    'Content-Length': len(content),
                    'Connection': 'close'
                }

            response_headers_raw = ''.join('%s: %s\n' % (k, v) for k, v in \
                response_headers.iteritems())

            conn.send('%s %s' % (response_proto, response_status))
            conn.send('\n')
            conn.send(response_headers_raw)
            conn.send('\n')
            conn.sendall(content)
            conn.close()
            continue
            

## This the entry point of the script.
## Do not change this part.
if __name__ == '__main__':
    p = argparse.ArgumentParser()
    p.add_argument('--port', help='port to bind to', default=8080, type=int)
    p.add_argument('--public_html', help='home directory', default='./public_html')
    p.add_argument('--cgibin', help='cgi-bin directory', default='./cgi-bin')
    args = p.parse_args(sys.argv[1:])
    public_html = os.path.abspath(args.public_html)
    cgibin = os.path.abspath(args.cgibin)
    serve(args.port, public_html, cgibin)